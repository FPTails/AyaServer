#include "AyaAccpetAsyncResultHandler.h"
#include "../../Network/Acceptor/AyaAccepter.h"

namespace AYA
{
	AccpetAsyncResultHandler::AccpetAsyncResultHandler()
	{
	}

	AccpetAsyncResultHandler::~AccpetAsyncResultHandler()
	{

	}

	void AccpetAsyncResultHandler::OnAsyncResult(AsyncResultData& async_result_data)
	{
		printf("On Accpet Async Result");
	}
}