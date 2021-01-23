#pragma once

#include "./AyaBufferStream.h"
#include "../../Core/Memory/MemoryBlockPool.h"

namespace AYA
{
	class Buffer
	{
	public:
		friend BufferStream;

		Buffer();
		Buffer(unsigned int reserved_size);
		Buffer(char* original_buffer_address, unsigned int original_buffer_data_size);
		Buffer(const Buffer& p);
		~Buffer();

		Buffer& operator = (const Buffer& other) {
			
			Copy(other);

			return *this;
		}

	public:
		bool Resize(unsigned short new_size);
		bool Reserve(unsigned short reserve_size); // 추가로 확보할 메모리 사이즈
		void Clear(); // 재사용을 위한 초기화. 
		bool Copy(const Buffer& org_buffer);
		void Release();
	public:
		char* GetBuffer() const { return m_memory_block.GetMemoryAddress(); }
		const unsigned short GetBufferSize() const { return m_memory_block.GetBlockSize(); }
		const unsigned short GetDataSize() const { return m_data_size; }
		
	private:
		bool HasEnoughBufferSize(unsigned short size);
		void InitDefaultMember();
		bool CheckValidBufferSize(unsigned short size);
		bool IncreateDataSize(unsigned short size);
	private:
		unsigned short m_data_size;

		MemoryBlock m_memory_block;

		/*unsigned int m_buffer_size;
		char* m_buffer_array;*/

	private:
		const int DEFAULT_BUFFER_RESERVE_SIZE = 512;
	};
}
