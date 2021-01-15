#include "AyaBuffer.h"

namespace AYA
{
	void Buffer::InitDefaultMember()
	{
		m_write_cursor = 0;
		m_read_cursor = 0;
		m_buffer_size = 0;
		m_buffer_array = nullptr;
	}

	Buffer::Buffer()
	{
		InitDefaultMember();

		Reserve(DEFAULT_BUFFER_RESERVE_SIZE);
	}
	
	Buffer::Buffer(int reserved_size)
	{
		InitDefaultMember();

		Reserve(reserved_size);
	}

	Buffer::Buffer(char* original_buffer_address, int original_buffer_size)
	{
		InitDefaultMember();
		
		Reserve(original_buffer_size);

		std::memcpy(m_buffer_array, original_buffer_address, original_buffer_size);
	}

	Buffer::Buffer(const Buffer& p)
	{
		InitDefaultMember();

		Copy(p);
	}

	Buffer::~Buffer()
	{
		Release();
	}

	void Buffer::Release()
	{
		if (nullptr != m_buffer_array)
		{
			delete[] m_buffer_array;
			m_buffer_array = nullptr;
		}
		
		m_write_cursor = 0;
		m_read_cursor = 0;
		m_buffer_size = 0;
	}

	bool Buffer::CheckValidCursor(int cursor) const
	{
		if (0 > cursor)
		{
			return false;
		}

		if (m_write_cursor < cursor)
		{
			return false;
		}

		return true;
	}

	bool Buffer::CheckValidBufferSize(int size)
	{
		if (0 >= size)
		{
			return false;
		}

		return true;
	}

	bool Buffer::HasEnoughBufferSize(int size)
	{
		if (m_buffer_size < size)
		{
			return false;
		}

		return true;
	}

	bool Buffer::Copy(const Buffer& org_buffer)
	{
		if (m_buffer_size < org_buffer.GetBufferDataSize())
		{
			Resize(org_buffer.GetBufferDataSize());
		}

		std::memcpy(m_buffer_array, org_buffer.GetBuffer(), org_buffer.GetBufferDataSize());

		m_write_cursor = 0;
		m_read_cursor = 0;
		m_write_cursor = org_buffer.GetBufferDataSize();

		return true;
	}

	void Buffer::Clear()
	{
		m_write_cursor = 0;
		m_read_cursor = 0;
	}

	bool Buffer::Resize(int new_size)
	{
		if (false == CheckValidBufferSize(new_size))
		{
			return false;
		}

		if (HasEnoughBufferSize(new_size))
		{
			return true;
		}

		if (nullptr == m_buffer_array)
		{
			m_buffer_array = new char[new_size];
		}
		else
		{
			m_buffer_array = (char*)std::realloc(m_buffer_array, new_size);
		}

		m_buffer_size = new_size;

		return true;
	}

	bool Buffer::Reserve(int reserve_size)
	{
		if (0 >=  reserve_size)
		{
			return false;
		}

		return Resize(m_buffer_size + reserve_size);
	}

	bool Buffer::MoveReadCursor(int data_size)
	{
		int new_cursor = m_read_cursor + data_size;

		// 커서를 옮기는게 불가능함 ( 들어가 있는 데이터 사이즈보다 크게 커서를 옮기려고 함 )
		if (m_write_cursor <= new_cursor)
		{
			return false;
		}

		m_read_cursor = new_cursor;

		return true;
	}

	bool Buffer::MoveWriteCursor(int data_size)
	{
		int new_cursor = m_write_cursor + data_size;

		// 커서를 옮기는게 불가능함 ( 쓰기 커서가 현재 버퍼 총 사이즈보다 커지려고 시도함)
		if (m_buffer_size <= new_cursor)
		{
			return false;
		}

		m_write_cursor = new_cursor;

		return true;
	}

	bool Buffer::GetInt(int& out_value)
	{
		int ret_value = 0;
		int data_size = sizeof(int);

		// 이전 커서 위치 획득 
		int prev_cursor = m_read_cursor;

		// 커서 이동 실패시 충분히 데이터가 들어있지 않은 것임.
		if (false == MoveReadCursor(data_size))
		{
			return false;
		}

		// 값을 복사. 
		std::memcpy(&ret_value, &m_buffer_array[prev_cursor], data_size);

		out_value = ret_value;

		return true;
	}

	const bool Buffer::FrontInt(int cursor, int& out_value) const
	{
		if (false == CheckValidCursor(cursor))
		{
			return false;
		}

		int ret_value = 0;
		int data_size = sizeof(int);

		std::memcpy(&ret_value, &m_buffer_array[cursor], data_size);

		out_value = ret_value;

		return true;
	}

	bool Buffer::GetBigInt(long& out_value)
	{
		return true;
	}

	bool Buffer::GetString(std::wstring& out_wstr)
	{
		return true;
	}

	bool Buffer::SetInt(int& value)
	{
		int data_size = sizeof(int);
		int new_buffer_size = m_write_cursor + data_size;

		if (false == HasEnoughBufferSize(new_buffer_size))
		{
			if (false == Reserve(DEFAULT_BUFFER_RESERVE_SIZE))
			{
				return false;
			}
		}

		int prev_write_cursor = m_write_cursor;

		if (false == MoveWriteCursor(data_size))
		{
			return false;
		}

		std::memcpy(&m_buffer_array[prev_write_cursor], &value, data_size);

		return true;
	}

	bool Buffer::SetBigInt(long& value)
	{
		return true;
	}

	bool Buffer::SetString(std::wstring& value)
	{
		return true;
	}
}