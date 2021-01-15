#pragma once

#include <string>

namespace AYA
{
	class Buffer
	{
	public:
		Buffer();
		Buffer(int reserved_size);
		Buffer(char* original_buffer_address, int original_buffer_size);
		Buffer(const Buffer& p);
		~Buffer();

		Buffer& operator = (const Buffer& p) {
			
			Copy(p);

			return *this;
		}

	public:
		bool Resize(int new_size);
		bool Reserve(int reserve_size); // 추가로 확보할 메모리 사이즈
		void Clear(); // 재사용을 위한 초기화. 
		bool Copy(const Buffer& org_buffer);
		void Release();
	public:
		char* GetBuffer() const { return m_buffer_array; }
		const int GetBufferSize() const { return m_buffer_size; }
		const int GetBufferDataSize() const { return m_write_cursor; }

	public:
		const bool FrontInt(int cursor, int& out_value) const;
		bool GetInt(int& out_value);
		bool GetBigInt(long& out_value);
		bool GetString(std::wstring& out_wstr);

		bool SetInt(int& value);
		bool SetBigInt(long& value);
		bool SetString(std::wstring& value);
	private:
		bool MoveReadCursor(int data_size);
		bool MoveWriteCursor(int data_size);
		void InitDefaultMember();

		bool CheckValidCursor(int cursor) const;
		bool CheckValidBufferSize(int size);
		bool HasEnoughBufferSize(int size);
	private:
		int m_read_cursor; 
		int m_write_cursor; 

		int m_buffer_size;
		char* m_buffer_array;

	private:
		const int DEFAULT_BUFFER_RESERVE_SIZE = 512;
	};
}
