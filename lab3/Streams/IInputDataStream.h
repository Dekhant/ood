#pragma once
#include "stdafx.h"


class IInputStream
{
public:
	virtual bool IsEOF() const = 0;
	virtual uint8_t ReadByte() = 0;
	virtual std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) = 0;

	virtual ~IInputStream() = default;
};

typedef std::unique_ptr<IInputStream> IInputStreamPtr;

class CFileInputStream : public IInputStream
{
public:
	CFileInputStream(const std::string& fileName)
	{
		m_inputFileStream.open(fileName, std::ios::binary);
		if (!m_inputFileStream.is_open())
		{
			throw std::ios::failure("Cannot open file: " + fileName);
		}
	}

	bool IsEOF()const override
	{
		return m_inputFileStream.eof();
	}

	uint8_t ReadByte() override
	{
		char readByte;
		m_inputFileStream.read(&readByte, 1);
		if (IsEOF())
		{
			throw std::ios_base::failure("Cannot read byte. Reached end of stream");
		}
		return (uint8_t)readByte;
	}
	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override
	{
		if (!m_inputFileStream.read(static_cast<char*>(dstBuffer), size))
		{
			throw std::ios_base::failure("Cannot read block");
		}
		return size;
	}

private:
	std::ifstream m_inputFileStream;
};

class CMemoryInputStream : public IInputStream
{
public:
	CMemoryInputStream(std::vector<uint8_t>& data)
		: m_memoryStream(data)
	{
	}

	bool IsEOF() const
	{
		return m_memoryStream.size() == m_pos;
	}

	uint8_t ReadByte() override
	{
		if (IsEOF() || m_pos > m_memoryStream.size())
		{
			throw std::ios_base::failure("Cannot read byte. Reached end of stream");
		}

		return m_memoryStream.at(m_pos++);
	}

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override
	{
		if (static_cast<std::size_t>(size) > m_memoryStream.size() - m_pos)
		{
			size = m_memoryStream.size() - m_pos;
		}
		uint8_t* bytesBuffer = static_cast<uint8_t*>(dstBuffer);
		for (std::streamsize i = 0; i < size; i++)
		{
			*(bytesBuffer++) = ReadByte();
		}
		return size;
	}

private:
	std::vector<uint8_t>& m_memoryStream;
	size_t m_pos = 0;
};