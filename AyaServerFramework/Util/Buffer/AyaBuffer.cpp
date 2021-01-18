#include "AyaBuffer.h"

namespace AYA
{
	void Buffer::InitDefaultMember()
	{
		m_data_size = 0;
		m_buffer_size = 0;
		m_buffer_array = nullptr;
	}

	Buffer::Buffer()
	{
		InitDefaultMember();

		Reserve(DEFAULT_BUFFER_RESERVE_SIZE);
	}
	
	Buffer::Buffer(unsigned int reserved_size)
	{
		InitDefaultMember();

		Reserve(reserved_size);
	}

	Buffer::Buffer(char* original_buffer_address, unsigned int original_buffer_size)
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
		
		m_data_size = 0;
		m_buffer_size = 0;
	}


	bool Buffer::CheckValidBufferSize(unsigned int size)
	{
		if (0 >= size)
		{
			return false;
		}

		return true;
	}

	bool Buffer::HasEnoughBufferSize(unsigned int size)
	{
		unsigned int new_buffer_size = m_data_size + size;

		if (m_buffer_size < new_buffer_size)
		{
			return false;
		}

		return true;
	}

	bool Buffer::Copy(const Buffer& org_buffer)
	{
		if (m_buffer_size < org_buffer.GetDataSize())
		{
			Resize(org_buffer.GetDataSize());
		}

		std::memcpy(m_buffer_array, org_buffer.GetBuffer(), org_buffer.GetDataSize());

		m_data_size = 0;
		m_data_size = org_buffer.GetDataSize();

		return true;
	}

	void Buffer::Clear()
	{
		m_data_size = 0;
	}

	bool Buffer::Resize(unsigned int new_size)
	{
		if (false == CheckValidBufferSize(new_size))
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

	bool Buffer::Reserve(unsigned int reserve_size)
	{
		if (0 >=  reserve_size)
		{
			return false;
		}

		return Resize(m_buffer_size + reserve_size);
	}

	bool Buffer::IncreateDataSize(unsigned int size)
	{
		m_data_size += size;

		return true;
	}
	
}