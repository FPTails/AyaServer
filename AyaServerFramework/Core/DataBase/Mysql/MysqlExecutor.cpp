#include "MysqlExecutor.h"

namespace AYA
{
	MysqlExecutor::MysqlExecutor()
	{
		
	}

	MysqlExecutor::~MysqlExecutor()
	{

	}

	bool MysqlExecutor::Init(const DBConnectData& db_connnect_data)
	{
		if (m_connector.IsConnected())
		{
			return true;
		}

		if (false == m_connector.Init())
		{
			return false;
		}

		if (false == m_connector.Connect(db_connnect_data))
		{
			return false;
		}
		
		m_query_result.SetMysql(m_connector.GetMysql());
		
		return true;
	}

	IDBQueryResult* MysqlExecutor::Query(const char* query_str)
	{
		if (false == m_connector.IsConnected())
		{
			return nullptr;
		}

		m_query_result.ResetResult();

		mysql_query(m_connector.GetMysql(), query_str);
		mysql_errno(m_connector.GetMysql());

		return &m_query_result;
	}

	int MysqlExecutor::GetError()
	{
		return m_connector.GetLastError();
	}
}