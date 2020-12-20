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
		~Buffer();

	public:
		bool Resize(int new_size);
		bool Reserve(int reserve_size); // 추가로 확보할 메모리 사이즈
		void Clear(); // 재사용을 위한 초기화. 
		bool Copy(const Buffer& org_buffer);
		void Release();
	public:
		char* GetBuffer() const { return m_buffer_array; }
		const int GetBufferSize() const { return m_buffer_size; }
		const int GetBufferDataSize() const { return m_buffer_data_size; }

	public:
		const bool FrontInt(int& out_value) const;
		bool GetInt(int& out_value);
		bool GetBigInt(long& out_value);
		bool GetString(std::wstring& out_wstr);

		bool SetInt(int& out_value);
		bool SetBigInt(long& out_value);
		bool SetString(std::wstring& out_wstr);
	private:
		bool MoveReadCursor(int data_size);
		bool MoveWriteCursor(int data_size);
	private:
		int m_curr_buffer_read_cursor; // 현재 버퍼가 읽고 있는 위치를 가리키는 커서 
		int m_curr_buffer_write_cursor; // 현재 버퍼가 쓰고 있는 위치를 가리키는 커서. 현재 버퍼에 데이터가 씌여진 크기이기도 함. 

		int m_buffer_data_size;
		int m_buffer_size; // 버퍼의 사이즈 ( 할당된 크기 )
		char* m_buffer_array;

	private:
		const int DEFAULT_BUFFER_RESERVE_SIZE = 512;
	};
}
