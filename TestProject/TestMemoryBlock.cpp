#include "pch.h"
#include "CppUnitTest.h"
#include <mysql.h>
#include <atlstr.h> 
#include "../AyaServerFramework/Core/Memory/MemoryBlock.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestMemoryBlock
{

	TEST_CLASS(MemoryBlockBasicCase)
	{
	public:
		const AYA::BlockSize TEST_MEMORY_SIZE = 512;

		TEST_METHOD(InitValid)
		{
			char* original_memory = new char[TEST_MEMORY_SIZE];

			AYA::MemoryBlock memory_block;

			bool test_result = memory_block.Init(original_memory, TEST_MEMORY_SIZE);

			memory_block.Release();

			Assert::IsTrue(test_result);
		}

		TEST_METHOD(NotDeletedOnDestructor)
		{
			char* original_memory = new char[TEST_MEMORY_SIZE];

			{
				AYA::MemoryBlock memory_block;

				memory_block.Init(original_memory, TEST_MEMORY_SIZE);
			}

			bool test_result = nullptr != original_memory;

			Assert::IsTrue(test_result);

			delete[] original_memory;
		}

		TEST_METHOD(MoveOperatorValid)
		{
			char* original_memory = new char[TEST_MEMORY_SIZE];
			AYA::MemoryBlock original_memory_block;
			original_memory_block.Init(original_memory, TEST_MEMORY_SIZE);

			AYA::MemoryBlock target_memory_block;

			target_memory_block = std::move(original_memory_block);

			bool test_result = !target_memory_block.Empty() && original_memory_block.Empty();

			Assert::IsTrue(test_result);

			target_memory_block.Release();
			original_memory_block.Release();
		}

		TEST_METHOD(MoveConstructorValid)
		{
			char* original_memory = new char[TEST_MEMORY_SIZE];
			AYA::MemoryBlock original_memory_block;
			original_memory_block.Init(original_memory, TEST_MEMORY_SIZE);

			AYA::MemoryBlock target_memory_block = std::move(original_memory_block);

			bool test_result = !target_memory_block.Empty() && original_memory_block.Empty();

			Assert::IsTrue(test_result);

			target_memory_block.Release();
			original_memory_block.Release();
		}

		TEST_METHOD(CopyOperatorValid)
		{
			char* original_memory = new char[TEST_MEMORY_SIZE];
			AYA::MemoryBlock original_memory_block;
			original_memory_block.Init(original_memory, TEST_MEMORY_SIZE);

			AYA::MemoryBlock target_memory_block;

			target_memory_block = original_memory_block;

			bool test_result = !target_memory_block.Empty() && !original_memory_block.Empty();

			Assert::IsTrue(test_result);

			target_memory_block.Release();
		}

		TEST_METHOD(CopyConstructorValid)
		{
			char* original_memory = new char[TEST_MEMORY_SIZE];
			AYA::MemoryBlock original_memory_block;
			original_memory_block.Init(original_memory, TEST_MEMORY_SIZE);

			AYA::MemoryBlock target_memory_block =original_memory_block;

			bool test_result = !target_memory_block.Empty() && !original_memory_block.Empty();

			Assert::IsTrue(test_result);

			target_memory_block.Release();
		}

		TEST_METHOD(CopyMemoryBlockValid)
		{
			const char TEST_CHAR_VALUE = 7;
			const int TEST_BUFFER_SIZE = 256;

			char original_buffer[TEST_BUFFER_SIZE];
			original_buffer[0] = TEST_CHAR_VALUE;

			char* original_memory = new char[TEST_MEMORY_SIZE];
			AYA::MemoryBlock memory_block;
			memory_block.Init(original_memory, TEST_MEMORY_SIZE);

			bool copy_result = memory_block.CopyMemoryBlock(original_buffer, (AYA::BlockSize)TEST_BUFFER_SIZE);

			auto memory_block_address = memory_block.GetMemoryAddress();

			bool test_result = memory_block_address[0] == TEST_CHAR_VALUE;

			Assert::IsTrue(test_result);
		}
		
		
	};

}