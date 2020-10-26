#pragma once
#include "IOutputDataStream.h"
#include "CEncodingTable.h"
#include "Packet.h"
#include "stdafx.h"

class COutputStreamDecorator : public IOutputStream
{
protected:
	COutputStreamDecorator(IOutputStreamPtr&& stream)
		: m_stream(std::move(stream))
	{
	}

	IOutputStreamPtr m_stream;
};

class COutputStreamCompressor : public COutputStreamDecorator
{
public:
	COutputStreamCompressor(IOutputStreamPtr&& stream)
		: COutputStreamDecorator(std::move(stream))
	{
	}
	~COutputStreamCompressor()
	{
		try
		{
			FlushPacket();
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << "\n";
			std::cout << "Data could have been written wrong";
		}
	}

	void WriteByte(uint8_t data) override
	{
		if (m_packet.bytesCounter == 0)
		{
			m_packet.dataByte = data;
			m_packet.bytesCounter++;
			return;
		}
		if (data == m_packet.dataByte && m_packet.bytesCounter < MAX_PACK)
		{
			m_packet.bytesCounter++;
			return;
		}
		FlushPacket();
		m_packet.dataByte = data;
		m_packet.bytesCounter = 1;
	}
	void WriteBlock(const void* srcData, std::streamsize size) override
	{
		const uint8_t* pData = static_cast<const uint8_t*>(srcData);
		for (std::streamsize i = 0; i < size; i++)
		{
			WriteByte(pData[i]);
		}
	}

private:
	void FlushPacket()
	{
		uint8_t packetData[2] = { m_packet.bytesCounter, m_packet.dataByte };
		m_stream->WriteBlock(packetData, 2);
		m_packet.bytesCounter = 0;
		m_packet.dataByte = 0;
	}

private:
	Packet m_packet;
};


class CEncryptedOutputStream : public COutputStreamDecorator
{
public:
	CEncryptedOutputStream(IOutputStreamPtr&& stream, uint32_t key)
		: COutputStreamDecorator(std::move(stream))
		, m_encodingTable(key)
	{

	}

	void WriteByte(uint8_t data) override
	{
		m_stream->WriteByte(m_encodingTable.GetEncrytedByte(data));
	}
	void WriteBlock(const void* srcData, std::streamsize size) override
	{
		const uint8_t* block = static_cast<const uint8_t*>(srcData);
		for (std::streamsize i = 0; i < size; i++)
		{
			WriteByte(block[i]);
		}
	}
private:
	CEncodingByteTable m_encodingTable;
};
