#include "stdafx.h"
#include "AyaBuffer.h"


namespace AYA
{
	void Buffer::InitDefaultMember()
	{
		m_data_size = 0;
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

	Buffer::Buffer(char* target_address, unsigned int target_data_size)
	{
		InitDefaultMember();
		
		Reserve(target_data_size);

		m_data_size = target_data_size;

		m_memory_block.CopyMemoryBlock(target_address, target_data_size);
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
		MemoryBlockPool::GetInstance()->Push(m_memory_block);
		m_data_size = 0;
	}


	bool Buffer::CheckValidBufferSize(unsigned short size)
	{
		if (0 >= size)
		{
			return false;
		}

		return true;
	}

	bool Buffer::HasEnoughBufferSize(unsigned short size)
	{
		unsigned short new_buffer_size = m_data_size + size;

		if (m_memory_block.GetBlockSize() < new_buffer_size)
		{
			return false;
		}

		return true;
	}

	bool Buffer::Copy(const Buffer& org_buffer)
	{
		if (m_memory_block.GetBlockSize() < org_buffer.GetDataSize())
		{
			Resize(org_buffer.GetDataSize());
		}

		m_memory_block.CopyMemoryBlock(org_buffer.GetBuffer(), org_buffer.GetDataSize());

		m_data_size = 0;
		m_data_size = org_buffer.GetDataSize();

		return true;
	}

	void Buffer::Clear()
	{
		m_data_size = 0;
	}

	bool Buffer::Resize(unsigned short new_size)
	{
		if (false == CheckValidBufferSize(new_size))
		{
			return false;
		}

		if (m_memory_block.GetBlockSize() >= new_size)
		{
			return true;
		
		}

		if (false == m_memory_block.Empty())
		{
			MemoryBlockPool::GetInstance()->Push(m_memory_block);
		}

		m_memory_block = MemoryBlockPool::GetInstance()->Pop(new_size);
		return true;
	}

	bool Buffer::Reserve(unsigned short reserve_size)
	{
		if (0 >=  reserve_size)
		{
			return false;
		}

		return Resize(m_memory_block.GetBlockSize() + reserve_size);
	}

	bool Buffer::IncreateDataSize(unsigned short size)
	{
		m_data_size += size;

		return true;
	}
	
}