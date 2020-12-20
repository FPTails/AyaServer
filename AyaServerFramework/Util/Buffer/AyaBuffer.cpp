#include "AyaBuffer.h"

namespace AYA
{
	

	Buffer::Buffer()
	{
		m_curr_buffer_write_cursor = 0;
		m_curr_buffer_read_cursor = 0;
		m_buffer_size = 0;
		m_buffer_data_size = 0;
		m_buffer_array = nullptr;

		Reserve(DEFAULT_BUFFER_RESERVE_SIZE);
	}
	
	Buffer::Buffer(int reserved_size)
	{
		m_curr_buffer_write_cursor = 0;
		m_curr_buffer_read_cursor = 0;
		m_buffer_size = 0;
		m_buffer_data_size = 0;
		m_buffer_array = nullptr;

		Reserve(reserved_size);
	}

	Buffer::Buffer(char* original_buffer_address, int original_buffer_size)
	{
		m_curr_buffer_write_cursor = 0;
		m_curr_buffer_read_cursor = 0;
		m_buffer_size = 0;
		m_buffer_array = nullptr;

		if (DEFAULT_BUFFER_RESERVE_SIZE < original_buffer_size)
		{
			Reserve(original_buffer_size);
		}
		else
		{
			Reserve(DEFAULT_BUFFER_RESERVE_SIZE);
		}
		

		std::memcpy(m_buffer_array, original_buffer_address, original_buffer_size);

		m_buffer_data_size = original_buffer_size;
	}

	Buffer::~Buffer()
	{
		delete[] m_buffer_array;
	}

	void Buffer::Release()
	{
		if (nullptr != m_buffer_array)
		{
			delete[] m_buffer_array;
			m_buffer_array = nullptr;
		}
		
		m_curr_buffer_write_cursor = 0;
		m_curr_buffer_read_cursor = 0;
		m_buffer_size = 0;
	}

	bool Buffer::Copy(const Buffer& org_buffer)
	{
		if (m_buffer_size < org_buffer.GetBufferDataSize())
		{
			Resize(org_buffer.GetBufferDataSize());
			m_buffer_size = org_buffer.GetBufferSize();
		}

		std::memcpy(m_buffer_array, org_buffer.GetBuffer(), org_buffer.GetBufferDataSize());

		m_curr_buffer_write_cursor = 0;
		m_curr_buffer_read_cursor = 0;
		m_buffer_data_size = org_buffer.GetBufferDataSize();

		return true;
	}

	void Buffer::Clear()
	{
		m_curr_buffer_write_cursor = 0;
		m_curr_buffer_read_cursor = 0;
	}

	bool Buffer::Resize(int new_size)
	{
		if (0 >= new_size)
		{
			return false;
		}

		if (m_buffer_size >= new_size)
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
		int new_cursor = m_curr_buffer_read_cursor + data_size;

		// Ŀ���� �ű�°� �Ұ����� ( �� �ִ� ������ ������� ũ�� Ŀ���� �ű���� �� )
		if (m_curr_buffer_write_cursor <= new_cursor)
		{
			return false;
		}

		m_curr_buffer_read_cursor = new_cursor;

		return true;
	}

	bool Buffer::MoveWriteCursor(int data_size)
	{
		int new_cursor = m_curr_buffer_write_cursor + data_size;

		// Ŀ���� �ű�°� �Ұ����� ( ���� Ŀ���� ���� ���� �� ������� Ŀ������ �õ���)
		if (m_buffer_size <= new_cursor)
		{
			return false;
		}

		m_curr_buffer_write_cursor = new_cursor;

		return true;
	}

	bool Buffer::GetInt(int& out_value)
	{
		int ret_value = 0;
		int data_size = sizeof(int);

		// ���� Ŀ�� ��ġ ȹ�� 
		int prev_cursor = m_curr_buffer_read_cursor;

		// Ŀ�� �̵� ���н� ����� �����Ͱ� ������� ���� ����.
		if (false == MoveReadCursor(data_size))
		{
			return false;
		}

		// ���� ����. 
		std::memcpy(&ret_value, &m_buffer_array[prev_cursor], data_size);

		out_value = ret_value;

		return true;
	}

	const bool Buffer::FrontInt(int& out_value) const
	{
		int ret_value = 0;
		int data_size = sizeof(int);

		std::memcpy(&ret_value, &m_buffer_array[0], data_size);

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
		int new_buffer_size = m_curr_buffer_write_cursor + data_size;

		// ���� ���� ����� ���ο� ������� Ŀ����
		if (m_buffer_size < new_buffer_size)
		{
			// ���� ���� Ȯ�� 
			if (false == Reserve(DEFAULT_BUFFER_RESERVE_SIZE))
			{
				return false;
			}
		}

		int prev_write_cursor = m_curr_buffer_write_cursor;

		if (false == MoveWriteCursor(data_size))
		{
			return false;
		}

		std::memcpy(&m_buffer_array[prev_write_cursor], &value, data_size);

		m_buffer_data_size = new_buffer_size;

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