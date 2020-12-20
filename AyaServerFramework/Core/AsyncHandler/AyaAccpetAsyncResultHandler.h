#pragma once

#include "./AyaAbstractAsyncResultHandler.h"

namespace AYA
{
	class Accepter;

	class AccpetAsyncResultHandler : public AbstractAsyncResultHandler
	{
	public:
		AccpetAsyncResultHandler();
		virtual ~AccpetAsyncResultHandler();

		virtual void OnAsyncResult(AsyncResultData& async_result_data) override;
	private:
	};
}
