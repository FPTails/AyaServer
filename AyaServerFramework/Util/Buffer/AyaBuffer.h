#pragma once

#include "./AyaBufferStream.h"

namespace AYA
{
	class Buffer
	{
	public:
		friend BufferStream;

		Buffer();
		Buffer(unsigned int reserved_size);
		Buffer(char* original_buffer_address, unsigned int original_buffer_size);
		Buffer(const Buffer& p);
		~Buffer();

		Buffer& operator = (const Buffer& p) {
			
			Copy(p);

			return *this;
		}

	public:
		bool Resize(unsigned int new_size);
		bool Reserve(unsigned int reserve_size); // 추가로 확보할 메모리 사이즈
		void Clear(); // 재사용을 위한 초기화. 
		bool Copy(const Buffer& org_buffer);
		void Release();
	public:
		char* GetBuffer() const { return m_buffer_array; }
		const unsigned int GetBufferSize() const { return m_buffer_size; }
		const unsigned int GetDataSize() const { return m_data_size; }
		
	private:
		bool HasEnoughBufferSize(unsigned int size);
		void InitDefaultMember();
		bool CheckValidBufferSize(unsigned int size);
		bool IncreateDataSize(unsigned int size);
	private:
		unsigned int m_data_size;
		unsigned int m_buffer_size;
		char* m_buffer_array;

	private:
		const int DEFAULT_BUFFER_RESERVE_SIZE = 512;
	};
}
