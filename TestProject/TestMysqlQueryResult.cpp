#include "pch.h"
#include "CppUnitTest.h"
#include <mysql.h>
#include <atlstr.h> 
#include "../AyaServerFramework/Core/DataBase/DBConnectData.h"
#include "../AyaServerFramework/Core/DataBase/Mysql/MysqlConnector.h"
#include "../AyaServerFramework/Core/DataBase/Mysql/MysqlQueryResult.h"
#include "TestDataBaseEssential.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestDataBase
{
	TEST_CLASS(MysqlQueryResultBasicCase)
	{
	public:
		TEST_METHOD(NextValid)
		{
			MYSQL my_sql;
			mysql_init(&my_sql);

			mysql_real_connect(&my_sql, valid_connect_data.Host.c_str(), valid_connect_data.User.c_str(), valid_connect_data.Password.c_str(), valid_connect_data.Database.c_str(), valid_connect_data.Port, NULL, 0);

			AYA::MysqlQueryResult mysql_query_result;
			mysql_query_result.SetMysql(&my_sql);

			int query_result = mysql_query(&my_sql, "select id, auth_token from useraccount where id = 'test_user'");
			auto mysql_error_code = mysql_errno(&my_sql);
			auto result_row = mysql_query_result.Next();

			std::wstring selected_id = CA2W( result_row->Get(TEST_ACCOUNT_COLUMN::ID) );
			std::wstring selected_auth_token = CA2W( result_row->Get(TEST_ACCOUNT_COLUMN::AUTH_TOKEN) );

			bool test_result = (selected_id == Test_User_Id) && (selected_auth_token == Test_User_Auth_Token);

			WCHAR logger_buffer[512];
			wsprintf(logger_buffer, L"query_result:%d, selected_id:%s, selected_token:%s", (int)query_result, selected_id.c_str(), selected_auth_token.c_str());
			Assert::IsTrue(test_result, logger_buffer);

			mysql_close(&my_sql);
		}

		TEST_METHOD(ResetValid)
		{
			MYSQL my_sql;
			mysql_init(&my_sql);

			mysql_real_connect(&my_sql, valid_connect_data.Host.c_str(), valid_connect_data.User.c_str(), valid_connect_data.Password.c_str(), valid_connect_data.Database.c_str(), valid_connect_data.Port, NULL, 0);

			AYA::MysqlQueryResult mysql_query_result;
			mysql_query_result.SetMysql(&my_sql);

			int query_result = mysql_query(&my_sql, "select id, auth_token from useraccount where id = 'test_user'");
			auto mysql_error_code = mysql_errno(&my_sql);

			auto result_row = mysql_query_result.Next();

			std::wstring selected_id = CA2W(result_row->Get(TEST_ACCOUNT_COLUMN::ID));
			std::wstring selected_auth_token = CA2W(result_row->Get(TEST_ACCOUNT_COLUMN::AUTH_TOKEN));

			bool test_result = (selected_id == Test_User_Id) && (selected_auth_token == Test_User_Auth_Token);
			WCHAR logger_buffer[512];
			wsprintf(logger_buffer, L"query_result:%d, selected_id:%s, selected_token:%s", (int)query_result, selected_id.c_str(), selected_auth_token.c_str());
			Assert::IsTrue(test_result, logger_buffer);

			mysql_query_result.ResetResult();

			query_result = mysql_query(&my_sql, "select id, auth_token from useraccount where id = 'test_user'");
			mysql_error_code = mysql_errno(&my_sql);
			result_row = mysql_query_result.Next();

			selected_id = CA2W(result_row->Get(TEST_ACCOUNT_COLUMN::ID));
			selected_auth_token = CA2W(result_row->Get(TEST_ACCOUNT_COLUMN::AUTH_TOKEN));

			bool test_result_after_reset_result = (selected_id == Test_User_Id) && (selected_auth_token == Test_User_Auth_Token);
			wsprintf(logger_buffer, L"query_result:%d, selected_id:%s, selected_token:%s", (int)query_result, selected_id.c_str(), selected_auth_token.c_str());
			Assert::IsTrue(test_result_after_reset_result, logger_buffer);


			mysql_close(&my_sql);
		}

		TEST_METHOD(IteratorValid)
		{
			MYSQL my_sql;
			mysql_init(&my_sql);

			mysql_real_connect(&my_sql, valid_connect_data.Host.c_str(), valid_connect_data.User.c_str(), valid_connect_data.Password.c_str(), valid_connect_data.Database.c_str(), valid_connect_data.Port, NULL, 0);

			AYA::MysqlQueryResult mysql_query_result;
			mysql_query_result.SetMysql(&my_sql);

			int query_result = mysql_query(&my_sql, "select id, auth_token from useraccount where id = 'test_user'");
			auto mysql_error_code = mysql_errno(&my_sql);

			for (auto curr_row = mysql_query_result.Next(); nullptr != curr_row; curr_row = mysql_query_result.Next())
			{
				std::wstring selected_id = CA2W(curr_row->Get(TEST_ACCOUNT_COLUMN::ID));
				std::wstring selected_auth_token = CA2W(curr_row->Get(TEST_ACCOUNT_COLUMN::AUTH_TOKEN));
				bool test_result = (selected_id == Test_User_Id) && (selected_auth_token == Test_User_Auth_Token);
				WCHAR logger_buffer[512];
				wsprintf(logger_buffer, L"query_result:%d, selected_id:%s, selected_token:%s", (int)query_result, selected_id.c_str(), selected_auth_token.c_str());
				Assert::IsTrue(test_result, logger_buffer);
			}
			
			mysql_close(&my_sql);
		}
	};

}