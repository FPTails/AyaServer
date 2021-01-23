#pragma once

#include <string>
#include "../../../Core/DataBase/Mysql/MysqlExecutor.h"
#include "../../../Core/DataBase/Mysql/MysqlQueryResult.h"

class UserDBExecutor : public AYA::MysqlExecutor
{
public:
	enum USER_DB_COLUMN
	{
		ID = 0,
		AUTH_TOKEN = 1
	};

	bool SelectPassword(std::wstring& user_id, std::wstring& out_selected_password);
};