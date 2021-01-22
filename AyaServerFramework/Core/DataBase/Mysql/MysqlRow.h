#pragma once

#include "MysqlEssential.h"
#include "../IDbRow.h"

namespace AYA
{
	class MysqlRow : public IDBRow
	{
	public:
		MysqlRow() = default;
		~MysqlRow() = default;

	public:
		virtual char* Get(unsigned short index) override;
		virtual void Set(char** data) override;

	private:
		MYSQL_ROW m_mysql_row;
	};
}