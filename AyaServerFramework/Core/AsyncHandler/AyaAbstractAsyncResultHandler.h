#pragma once

#include <WinSock2.h>

namespace AYA
{
	// 비동기 처리 데이터의 결과 데이터. iocp 종료 후 처리에 필요한 데이터를 담아준다. 
	struct AsyncResultData
	{
		DWORD RecieveBytes;
	};
	
	

	// 비동기 처리 결과를 핸들링 하기 위한 추상 클래스. 
	// 기본적인 overlapped 사용을 위한 파라미터들을 가지고 있으며, 
	// 사용자가 OnAsyncResult를 재정의 하여 자신이 원하는 이벤트를 핸들링 할 수 있다. 
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