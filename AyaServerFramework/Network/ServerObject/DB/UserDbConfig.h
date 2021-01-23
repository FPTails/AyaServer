#pragma once

#include "../../../Core/DataBase/DBConnectData.h"


class UserDBConfig
{
public:
	UserDBConfig();

	bool ConvertTo(AYA::DBConnectData& out_connect_data);

public:

	bool IsLoaded();
private:
	std::string m_host;
	std::string m_user;
	std::string m_password;
	std::string m_database;
	short m_port;
};
