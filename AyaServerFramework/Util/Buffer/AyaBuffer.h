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
		bool Reserve(int reserve_size); // �߰��� Ȯ���� �޸� ������
		void Clear(); // ������ ���� �ʱ�ȭ. 
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
		int m_curr_buffer_read_cursor; // ���� ���۰� �а� �ִ� ��ġ�� ����Ű�� Ŀ�� 
		int m_curr_buffer_write_cursor; // ���� ���۰� ���� �ִ� ��ġ�� ����Ű�� Ŀ��. ���� ���ۿ� �����Ͱ� ������ ũ���̱⵵ ��. 

		int m_buffer_data_size;
		int m_buffer_size; // ������ ������ ( �Ҵ�� ũ�� )
		char* m_buffer_array;

	private:
		const int DEFAULT_BUFFER_RESERVE_SIZE = 512;
	};
}
