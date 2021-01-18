#include "AyaBufferStream.h"
#include "./AyaBuffer.h"

namespace AYA
{
	BufferStream::BufferStream(Buffer* buffer)
	{
		m_buffer = buffer;
		m_write_index = 0;
		m_read_index = 0;
	}

	BufferStream::~BufferStream()
	{
	}

	bool BufferStream::CheckValidIndex(unsigned int index) const
	{
		if (0 > index)
		{
			return false;
		}

		if (m_buffer->GetDataSize() < index)
		{
			return false;
		}

		return true;
	}

	bool BufferStream::MoveReadIndex(unsigned int data_size)
	{
		unsigned int new_index = m_read_index + data_size;

		if (m_buffer->GetDataSize() < new_index)
		{
			return false;
		}

		m_read_index = new_index;

		return true;
	}

	bool BufferStream::MoveWriteIndex(unsigned int data_size)
	{
		unsigned int new_index = m_write_index + data_size;

		if (m_buffer->GetBufferSize() < new_index)
		{
			return false;
		}

		m_write_index = new_index;

		return true;
	}

#pragma region Get Data Method 

	bool BufferStream::GetInt(int& out_value)
	{
		unsigned int data_size = sizeof(int);

		if (false == ReadData(&out_value, data_size))
		{
			return false;
		}

		return true;
	}

	bool BufferStream::FrontInt(int read_index, int& out_value)
	{
		if (false == CheckValidIndex(read_index))
		{
			return false;
		}

		int ret_value = 0;
		unsigned int data_size = sizeof(int);

		if (false == FrontData(read_index, &ret_value, data_size))
		{
			return false;
		}

		out_value = ret_value;

		return true;
	}

	bool BufferStream::GetLong(long& out_value)
	{
		unsigned int data_size = sizeof(long);

		if (false == ReadData(&out_value, data_size))
		{
			return false;
		}

		return true;
	}

	bool BufferStream::GetString(std::wstring& out_wstr)
	{
		short wstr_length = 0;

		if (false == GetShort(wstr_length))
		{
			return false;
		}

		const int WCHAR_BUFFER_MAX_SIZE = 1024;
		wchar_t wchar_buffer[WCHAR_BUFFER_MAX_SIZE];
		unsigned int wchar_data_size = sizeof(wchar_t);
		unsigned int read_size = wchar_data_size * wstr_length;

		if (false == ReadData(wchar_buffer, read_size))
		{
			return false;
		}

		// lengh 는 index보다 1이 크므로, length 부분을 null문자로 하면 맞다.
		wchar_buffer[wstr_length] = L'\0';

		out_wstr = wchar_buffer;

		return true;
	}

	bool BufferStream::GetShort(short& out_value)
	{
		unsigned int data_size = sizeof(short);

		if (false == ReadData(&out_value, data_size))
		{
			return false;
		}

		return true;
	}

#pragma endregion


#pragma region Set Data Method 

	bool BufferStream::SetShort(short& value)
	{
		unsigned int data_size = sizeof(short);

		if (false == WriteData(&value, data_size))
		{
			return false;
		}

		return true;
	}

	bool BufferStream::SetInt(int& value)
	{
		unsigned int data_size = sizeof(int);

		if (false == WriteData(&value, data_size))
		{
			return false;
		}

		return true;
	}

	bool BufferStream::SetLong(long& value)
	{
		unsigned int data_size = sizeof(long);

		if (false == WriteData(&value, data_size))
		{
			return false;
		}

		return true;
	}

	bool BufferStream::SetString(std::wstring& value)
	{
		// 1) wstr size 부터 삽입 . 
		short wstr_length =  value.length();

		if (false == SetShort(wstr_length))
		{
			return false;
		}
		
		auto wstr_buffer_pointer = value.c_str();

		unsigned int wchar_size = sizeof(wchar_t);

		if (false == WriteData((void*)wstr_buffer_pointer, wchar_size * wstr_length))
		{
			return false;
		}

		return true;
	}

#pragma endregion

#pragma region Buffer Access Method 
	bool BufferStream::WriteData(void* data, unsigned int data_size)
	{
		if (false == m_buffer->HasEnoughBufferSize(data_size))
		{
			return false;
		}

		auto buffer_array = m_buffer->GetBuffer();

		std::memcpy(&buffer_array[m_write_index], data, data_size);

		if (false == MoveWriteIndex(data_size))
		{
			return false;
		}

		if (false == m_buffer->IncreateDataSize(data_size))
		{
			return false;
		}

		return true;
	}

	bool BufferStream::FrontData(unsigned int index, void* target, unsigned int size)
	{
		if (m_buffer->GetDataSize() < index + size)
		{
			return false;
		}

		auto buffer_array = m_buffer->GetBuffer();

		std::memcpy(target, &buffer_array[index], size);

		return true;
	}

	bool BufferStream::ReadData(void* target, unsigned int size)
	{
		if (false == FrontData(m_read_index, target, size))
		{
			return false;
		}

		if (false == MoveReadIndex(size))
		{
			return false;
		}

		return true;
	}
#pragma endregion 
}