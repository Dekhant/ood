#pragma once
#include "stdafx.h"

class IOutputStream
{
public:
	virtual void WriteByte(uint8_t data) = 0;
	virtual void WriteBlock(const void* srcData, std::streamsize size) = 0;

	virtual ~IOutputStream() = default;
};

typedef std::unique_ptr<IOutputStream> IOutputStreamPtr;

class CFileOutputStream : public IOutputStream
{
public:
	CFileOutputStream(const std::string& fileName)
	{
		m_stream.open(fileName, std::ios::binary);
		if (!m_stream.is_open())
		{
			throw std::ios::failure("Cannot open file: " + fileName);
		}
	}
	void WriteByte(uint8_t data) override
	{
		char byte = static_cast<uint8_t>(data);
		if (!m_stream.write(&byte, 1))
		{
			throw std::ios_base::failure("Cannot write byte.");
		}
	}
	void WriteBlock(const void* srcData, std::streamsize size) override
	{
		const char* block = static_cast<const char*>(srcData);
		if (!m_stream.write(block, size))
		{
			throw std::ios_base::failure("Cannot write block.");
		}
		m_stream.flush();
	}

private:
	std::ofstream m_stream;
};

class CMemoryOutputStream : public IOutputStream
{
public:
	CMemoryOutputStream(std::vector<uint8_t>& stream)
		: m_stream(stream)
	{
	}
	void WriteByte(uint8_t data) override
	{
		try
		{
			m_stream.push_back(data);
		}
		catch (std::exception&)
		{
			throw std::ios_base::failure("Cannot write byte");
		}
	}
	void WriteBlock(const void* srcData, std::streamsize size) override
	{
		const uint8_t* buffer = static_cast<const uint8_t*>(srcData);
		for (std::streamsize i = 0; i < size; i++)
		{
			try
			{
				WriteByte(buffer[i]);
			}
			catch (std::exception&)
			{
				throw std::ios_base::failure("Cannot write block of bytes");
			}
		}
	}
private:
	std::vector<uint8_t>& m_stream;
};