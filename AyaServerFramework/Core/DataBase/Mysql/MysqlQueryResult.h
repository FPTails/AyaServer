#pragma once

#include "./MysqlEssential.h"
#include "../IDbQueryResult.h"
#include "./MysqlRow.h"

namespace AYA
{
	class MysqlQueryResult : public IDBQueryResult
	{
	public:
		MysqlQueryResult();
		virtual ~MysqlQueryResult();

	public:
		virtual IDBRow* Next() override;
		void SetMysql(MYSQL* mysql);
		void ResetResult();
		
	private:
		MYSQL* m_mysql;
		MYSQL_RES* m_mysql_result;
		MysqlRow m_row;
		bool m_is_result_exist;
	};
}