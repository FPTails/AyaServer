#pragma once

#include "./MysqlEssential.h"
#include "../IDbConnector.h"

namespace AYA
{
	class MysqlConnector : public IDBConnector
	{
	public:
		MysqlConnector();
		virtual ~MysqlConnector() = default;
	public:
		virtual bool Init() override;
		virtual bool Connect(const DBConnectData& db_connect_data) override;
		virtual void Release() override;
		virtual int GetLastError() override;

		inline MYSQL* GetMysql() { return &m_my_sql; }
		inline bool IsConnected() { return m_is_connect; }
	private:
		MYSQL m_my_sql;
		bool m_is_connect;
	};
}