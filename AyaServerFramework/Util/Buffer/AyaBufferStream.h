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

#pragma region Shift Opertor Overloading

		friend AYA::BufferStream& operator<<(AYA::BufferStream& stream, int& write)
		{
			stream.SetInt(write);

			return stream;
		}

		friend AYA::BufferStream& operator<<(AYA::BufferStream& stream, long& write)
		{
			stream.SetLong(write);

			return stream;
		}

		friend AYA::BufferStream& operator<<(AYA::BufferStream& stream, std::wstring& write)
		{
			stream.SetString(write);

			return stream;
		}

		friend AYA::BufferStream& operator<<(AYA::BufferStream& stream, short& write)
		{
			stream.SetShort(write);

			return stream;
		}

		friend AYA::BufferStream& operator>>(AYA::BufferStream& stream, int& read)
		{
			stream.GetInt(read);

			return stream;
		}

		friend AYA::BufferStream& operator>>(AYA::BufferStream& stream, long& read)
		{
			stream.GetLong(read);

			return stream;
		}

		friend AYA::BufferStream& operator>>(AYA::BufferStream& stream, std::wstring& read)
		{
			stream.GetString(read);

			return stream;
		}

		friend AYA::BufferStream& operator>>(AYA::BufferStream& stream, short& read)
		{
			stream.GetShort(read);

			return stream;
		}

#pragma endregion

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