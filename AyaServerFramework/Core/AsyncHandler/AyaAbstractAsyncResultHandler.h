#pragma once

#include <WinSock2.h>

namespace AYA
{
	// �񵿱� ó�� �������� ��� ������. iocp ���� �� ó���� �ʿ��� �����͸� ����ش�. 
	struct AsyncResultData
	{
		DWORD RecieveBytes;
	};
	
	

	// �񵿱� ó�� ����� �ڵ鸵 �ϱ� ���� �߻� Ŭ����. 
	// �⺻���� overlapped ����� ���� �Ķ���͵��� ������ ������, 
	// ����ڰ� OnAsyncResult�� ������ �Ͽ� �ڽ��� ���ϴ� �̺�Ʈ�� �ڵ鸵 �� �� �ִ�. 
	class AbstractAsyncResultHandler
	{
	public:
		AbstractAsyncResultHandler() 
		{ 
		}
		
		virtual ~AbstractAsyncResultHandler() {}

	public:
		virtual void OnAsyncResult(AsyncResultData& async_result_data) {}

	protected:
	};
}