#pragma once

#include <string>

namespace AYA
{
	class Buffer;

	class BufferStream
	{
	public:
		BufferStream(Buffer* buffer);
		~BufferStream();

		const int GetReadIndex() const { return m_read_index; }
		const int GetWriteIndex() const { return m_write_index; }
	public:
		bool FrontInt(int cursor, int& out_value);
		bool GetInt(int& out_value);
		bool GetLong(long& out_value);
		bool GetString(std::wstring& out_wstr);
		bool GetShort(short& out_value);

		bool SetShort(short& value);
		bool SetInt(int& value);
		bool SetLong(long& value);
		bool SetString(std::wstring& value);
	private:
		bool MoveReadIndex(unsigned int data_size);
		bool MoveWriteIndex(unsigned int data_size);

		bool CheckValidIndex(unsigned int index) const;

		bool WriteData(void* data, unsigned int data_size);
		bool ReadData(void* target, unsigned int size);
		bool FrontData(unsigned int index, void* target, unsigned int size);
	private:
		int m_read_index;
		int m_write_index;

		Buffer* m_buffer;
	};
}