#include "MysqlConnector.h"

namespace AYA
{
	MysqlConnector::MysqlConnector()
	{
		m_is_connect = false;
	}

	int MysqlConnector::GetLastError()
	{
		return mysql_errno(&m_my_sql);
	}

	bool MysqlConnector::Init()
	{
		if (nullptr == mysql_init(&m_my_sql))
		{
			return false;
		}

		return true;
	}

	bool MysqlConnector::Connect(const DBConnectData& db_connect_data)
	{
		if (m_is_connect)
		{
			return true;
		}

		auto mysql_connect_result = mysql_real_connect(&m_my_sql, 
			db_connect_data.Host.c_str(), 
			db_connect_data.User.c_str(),
			db_connect_data.Password.c_str(),
			db_connect_data.Database.c_str(),
			db_connect_data.Port,
			NULL, 
			0);

		m_is_connect = NULL != mysql_connect_result;

		return m_is_connect;
	}

	void MysqlConnector::Release()
	{
		mysql_close(&m_my_sql);

		m_is_connect = false;
	}
}