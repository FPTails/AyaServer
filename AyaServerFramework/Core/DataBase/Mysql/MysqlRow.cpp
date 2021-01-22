#include "MysqlRow.h"

namespace AYA
{
	char* MysqlRow::Get(unsigned short index)
	{
		if (nullptr == m_mysql_row)
		{
			return nullptr;
		}

		if (nullptr == m_mysql_row[index])
		{
			return nullptr;
		}

		return m_mysql_row[index];
	}

	void MysqlRow::Set(char** data)
	{
		m_mysql_row = data;
	}

}