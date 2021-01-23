#include "pch.h"
#include "CppUnitTest.h"
#include <mysql.h>
#include <atlstr.h> 
#include "../AyaServerFramework/Core/Memory/MemoryBlockPool.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestMemoryBlockPool
{
	TEST_CLASS(MemoryBlockBasicCase)
	{
	public:
		TEST_METHOD(MemoryBlockPoolHasDefaultPool)
		{
			AYA::MemoryBlockPool memory_block_pool;
			bool test_result = 0 != memory_block_pool.GetCurrentPoolSize();

			Assert::IsTrue(test_result);
		}

		TEST_METHOD(MemoryBlockPopValid)
		{
			AYA::MemoryBlockPool memory_block_pool;

			auto memory_block = memory_block_pool.Pop();

			bool test_result = AYA::MemoryBlockPool::DEFAULT_BLOCK_SIZE == memory_block.GetBlockSize();

			memory_block.Release();

			Assert::IsTrue(test_result);

		}

		TEST_METHOD(MemoryBlockPushValid)
		{
			AYA::MemoryBlockPool memory_block_pool;

			auto memory_block = memory_block_pool.Pop();

			auto before_block_pool_size = memory_block_pool.GetCurrentPoolSize();

			memory_block_pool.Push(memory_block);

			auto after_block_pool_size = memory_block_pool.GetCurrentPoolSize();

			bool test_result = before_block_pool_size < after_block_pool_size;

			Assert::IsTrue(test_result);
		}
	};
	
}