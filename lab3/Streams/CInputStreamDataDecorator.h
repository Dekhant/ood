#pragma once
#include "IInputDataStream.h"
#include "stdafx.h"
#include "CEncodingTable.h"
#include "Packet.h"

class CInputStreamDecorator : public IInputStream
{
public:
	bool IsEOF() const override
	{
		return m_stream->IsEOF();
	}
protected:
	CInputStreamDecorator(IInputStreamPtr&& stream)
		: m_stream(std::move(stream))
	{
	}

	IInputStreamPtr m_stream;
};

class CDecryptedInputStream : public CInputStreamDecorator
{
public:
	CDecryptedInputStream(IInputStreamPtr&& stream, uint32_t key)
		: CInputStreamDecorator(std::move(stream))
		, m_encodingTable(key)
	{
	}
	uint8_t ReadByte()
	{
		return m_encodingTable.GetDecrytedByte(m_stream->ReadByte());
	}

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size)
	{
		std::streamsize encryptedBytesSize = m_stream->ReadBlock(dstBuffer, size);
		uint8_t* buffer = static_cast<uint8_t*>(dstBuffer);
		for (std::streamsize i = 0; i < encryptedBytesSize; i++)
		{
			buffer[i] = m_encodingTable.GetDecrytedByte(buffer[i]);
		}
		return encryptedBytesSize;
	}

private:
	CEncodingByteTable m_encodingTable;
};

class CInputStreamDecompressor : public CInputStreamDecorator
{
public:
	CInputStreamDecompressor(IInputStreamPtr&& stream)
		: CInputStreamDecorator(std::move(stream))
	{
	}
	uint8_t ReadByte() override
	{
		if (m_packet.bytesCounter == 0)
		{
			m_packet.bytesCounter = m_stream->ReadByte();
			try
			{
				m_packet.dataByte = m_stream->ReadByte();
			}
			catch (std::ios_base::failure&)
			{
				throw std::logic_error("File size should be even so that can decompress data");
			}
		}
		m_packet.bytesCounter--;
		return m_packet.dataByte;
	}

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override
	{
		uint8_t* buffer = static_cast<uint8_t*>(dstBuffer);
		for (std::streamsize i = 0; i < size; i++)
		{
			try
			{
				buffer[i] = ReadByte();
			}
			catch (std::ios_base::failure&)
			{
				return i;
			}
		}
		return size;
	}

private:
	Packet m_packet;
	std::vector<uint8_t> decompressedData;
};
