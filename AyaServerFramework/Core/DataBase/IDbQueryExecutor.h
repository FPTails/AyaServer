#pragma once

#include "./IDbQueryResult.h"

namespace AYA
{
	class IDBQueryExecutor
	{
	public:
		virtual IDBQueryResult* Query(const char* query_str) = 0;
		virtual bool Init(const DBConnectData& db_connnect_data) = 0;
		virtual int GetError() = 0;
	};
}
