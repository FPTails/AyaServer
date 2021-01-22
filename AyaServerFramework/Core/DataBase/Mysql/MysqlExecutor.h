#pragma once

#include "MysqlConnector.h"
#include "../IDbQueryExecutor.h"
#include "MysqlQueryResult.h"

namespace AYA
{
	class MysqlExecutor : public IDBQueryExecutor
	{
	public:
		MysqlExecutor();
		virtual ~MysqlExecutor();

	public:
		virtual bool Init(const DBConnectData& db_connnect_data) override;
		virtual IDBQueryResult* Query(const char* query_str) override;
		virtual int GetError() override;

	private:
		MysqlConnector m_connector;
		MysqlQueryResult m_query_result;
	};
}