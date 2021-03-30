#include "stdafx.h"
#include "MysqlQueryResult.h"

namespace AYA
{
	MysqlQueryResult::MysqlQueryResult()
	{
		m_mysql_result = nullptr;
		m_mysql = nullptr;
		m_is_result_exist = false;
	}
	
	MysqlQueryResult::~MysqlQueryResult()
	{
		if (nullptr != m_mysql_result)
		{
			mysql_free_result(m_mysql_result);
		}
	}

	void MysqlQueryResult::ResetResult()
	{
		m_is_result_exist = false;
		mysql_free_result(m_mysql_result);
	}

	void MysqlQueryResult::SetMysql(MYSQL* mysql)
	{
		m_mysql = mysql;
	}

	IDBRow* MysqlQueryResult::Next()
	{
		if (false == m_is_result_exist)
		{
			m_mysql_result = mysql_store_result(m_mysql);
			m_is_result_exist = true;
		}

		auto sql_row = mysql_fetch_row(m_mysql_result) ;

		if (NULL == sql_row)
		{
			return nullptr;
		}

		m_row.Set(sql_row);
		return &m_row;
	}
}