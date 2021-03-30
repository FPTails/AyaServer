#include "stdafx.h"
#include "MemoryBlock.h"

namespace AYA
{
	MemoryBlock::MemoryBlock()
	{
		m_memory_block = nullptr;
		m_memory_block_size = 0;
	}

	MemoryBlock::~MemoryBlock()
	{

	}

	MemoryBlock::MemoryBlock(const MemoryBlock& other)
	{
		m_memory_block = other.m_memory_block;
		m_memory_block_size = other.m_memory_block_size;

	}

	MemoryBlock::MemoryBlock(MemoryBlock&& other) noexcept
	{

		m_memory_block = other.m_memory_block;
		m_memory_block_size = other.m_memory_block_size;

		other.m_memory_block = nullptr;
		other.m_memory_block_size = 0;
	}

	MemoryBlock& MemoryBlock::operator = (const MemoryBlock& other)
	{
		m_memory_block = other.m_memory_block;
		m_memory_block_size = other.m_memory_block_size;

		return *this;
	}

	MemoryBlock& MemoryBlock::operator=(MemoryBlock&& other) noexcept
	{

		m_memory_block = other.m_memory_block;
		m_memory_block_size = other.m_memory_block_size;

		other.m_memory_block = nullptr;
		other.m_memory_block_size = 0;

		return *this;
	}

	bool MemoryBlock::Init(char* memory_block, BlockSize size)
	{
		if (false == Empty())
		{
			return false;
		}

		m_memory_block = memory_block;
		m_memory_block_size = size;

		return true;
	}

	void MemoryBlock::Release()
	{
		if (m_memory_block)
		{
			delete[] m_memory_block;
			m_memory_block = nullptr;
		}

		m_memory_block_size = 0;
	}

	bool MemoryBlock::CopyMemoryBlock(const char* target_address, BlockSize size)
	{
		if (Empty())
		{
			return false;
		}

		std::memcpy(m_memory_block, target_address, size);

		return true;
	}

	
}