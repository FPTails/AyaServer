#pragma once

namespace AYA
{
	typedef unsigned short BlockSize;

	class MemoryBlock
	{
	public:
		MemoryBlock();
		~MemoryBlock();
		
		MemoryBlock(const MemoryBlock& other);
		MemoryBlock(MemoryBlock&& other) noexcept;
		MemoryBlock& operator = (const MemoryBlock& other);
		MemoryBlock& operator = (MemoryBlock&& other) noexcept;

	public:
		bool Init(char* memory_block, BlockSize size);
		void Release();
		bool CopyMemoryBlock(const char* target_address, BlockSize size);

		inline const BlockSize GetBlockSize() const { return m_memory_block_size; }
		inline const bool Empty() const { return nullptr == m_memory_block; }
		inline char* GetMemoryAddress() const { return m_memory_block; }

	private:
		char* m_memory_block;
		unsigned short m_memory_block_size;
	};
}