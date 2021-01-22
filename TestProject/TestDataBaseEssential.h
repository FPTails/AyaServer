#pragma once

#include <string>
#include "../AyaServerFramework/Core/DataBase/DBConnectData.h"

namespace TestDataBase
{
	enum TEST_ACCOUNT_COLUMN
	{
		ID = 0,
		AUTH_TOKEN = 1
	};

	const std::wstring Test_User_Id = L"test_user";
	const std::wstring Test_User_Auth_Token = L"test_token_string";
	const AYA::DBConnectData valid_connect_data = { "127.0.0.1"  , "root" , "1q2w3e4r" , "ayagamedb" , 3306 };
}
