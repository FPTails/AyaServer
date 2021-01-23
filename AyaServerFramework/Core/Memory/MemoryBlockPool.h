#pragma once

#include "./MemoryBlock.h"
#include <list>
#include "../../Util/Singleton/Singleton.h"
#include <mutex>

namespace AYA
{
	class MemoryBlockPool : public Singleton<MemoryBlockPool>
	{
	public:
		static const BlockSize DEFAULT_BLOCK_SIZE = 512;
		static const int DEFAULT_BLOCK_POOL_SIZE = 10;

	public:
		MemoryBlockPool();
		~MemoryBlockPool();

		MemoryBlock Pop(BlockSize size = DEFAULT_BLOCK_SIZE);
		void Push(MemoryBlock memory_block);
		inline size_t GetCurrentPoolSize() { return m_memory_block_pool.size(); }

	
	private:
		MemoryBlock CreateBlock(BlockSize size);
	private:
		std::list<MemoryBlock> m_memory_block_pool;
		std::mutex m_memory_block_pool_lock;
	};
}