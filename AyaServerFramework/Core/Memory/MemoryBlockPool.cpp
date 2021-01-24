#include "MemoryBlockPool.h"
#include <Windows.h>

namespace AYA
{
	MemoryBlockPool::MemoryBlockPool()
	{
		for (int i = 0 ; i < DEFAULT_BLOCK_POOL_SIZE; ++i)
		{
			MemoryBlock block = CreateBlock(DEFAULT_BLOCK_SIZE);

			if (block.Empty())
			{
				continue;
			}

			m_memory_block_pool.emplace_back(block);
		}
	}

	MemoryBlock MemoryBlockPool::CreateBlock(BlockSize size)
	{
		MemoryBlock block;

		char* new_block_address = new char[size];
		ZeroMemory(new_block_address, size);

		if (false == block.Init(new_block_address, size))
		{
			delete[] new_block_address;
		}

		return block;
	}

	MemoryBlockPool::~MemoryBlockPool()
	{
		for (auto& block : m_memory_block_pool)
		{
			block.Release();
		}

		m_memory_block_pool.clear();
	}

	MemoryBlock MemoryBlockPool::Pop(BlockSize size)
	{
		std::lock_guard<std::mutex> lock(m_memory_block_pool_lock);

		auto block_finder = std::find_if(m_memory_block_pool.begin(), m_memory_block_pool.end(), 
			[size](const MemoryBlock& block) 
			{
				return block.GetBlockSize() >= size;
			});

		if (m_memory_block_pool.end() == block_finder)
		{
			return CreateBlock(size);
		}

		MemoryBlock finded_block = (*block_finder);

		m_memory_block_pool.erase(block_finder);

		return finded_block;
	}

	void MemoryBlockPool::Push(MemoryBlock memory_block)
	{
		std::lock_guard<std::mutex> lock(m_memory_block_pool_lock);

		if (memory_block.Empty())
		{
			return;
		}

		m_memory_block_pool.emplace_back(memory_block);
	}
}