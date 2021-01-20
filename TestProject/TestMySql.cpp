#include "pch.h"
#include "CppUnitTest.h"
#include <mysql.h>
#include <atlstr.h> 

#pragma comment(lib, "libmysql.lib")

#pragma comment(lib, "ws2_32.lib")  

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestDataBase
{
	TEST_CLASS(MySqlBasic)
	{
	public:
		enum TEST_ACCOUNT_COLUMN
		{
			ID = 0,
			AUTH_TOKEN = 1
		};

		std::wstring Test_User_Id = L"test_user";
		std::wstring Test_User_Auth_Token = L"test_token_string";

		bool MySqlConnect(MYSQL& my_sql)
		{
			return mysql_real_connect(&my_sql, "127.0.0.1", "root", "1q2w3e4r", "ayagamedb", 3306, NULL, 0);
		}

		TEST_METHOD(ConnectFunction)
		{
			MYSQL my_sql;
			mysql_init(&my_sql);

			bool connect_result = MySqlConnect(my_sql);
			unsigned int mysql_error_code = mysql_errno(&my_sql);

			WCHAR logger_buffer[512];
			wsprintf(logger_buffer, L"result:%d, mysql_error_code:%d", (int)connect_result, mysql_error_code);
			Assert::IsTrue(connect_result, logger_buffer);

			mysql_close(&my_sql);
		}

		TEST_METHOD(SelectFucntionSuccess)
		{
			MYSQL my_sql;
			mysql_init(&my_sql);

			MySqlConnect(my_sql);
			

			int query_result = mysql_query(&my_sql, "select id, auth_token from useraccount where id = 'test_user'");
			auto mysql_error_code = mysql_errno(&my_sql);

			WCHAR logger_buffer[512];
			wsprintf(logger_buffer, L"query_result:%d, error:%d", (int)query_result, mysql_error_code);
			Assert::IsTrue(0 == query_result, logger_buffer);

			auto sql_result = mysql_store_result(&my_sql);
			
			MYSQL_ROW sql_row;
			std::wstring selected_id = L"";
			std::wstring selected_auth_token = L"";

			while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
			{
				selected_id = CA2W(sql_row[TEST_ACCOUNT_COLUMN::ID]);
				selected_auth_token = CA2W(sql_row[TEST_ACCOUNT_COLUMN::AUTH_TOKEN]);
				break;
			}

			mysql_free_result(sql_result);
			
			bool test_result = (selected_id == Test_User_Id) && (selected_auth_token == Test_User_Auth_Token);

			wsprintf(logger_buffer, L"query_result:%d, selected_id:%s, selected_token:%s", (int)query_result, selected_id.c_str(), selected_auth_token.c_str());
			Assert::IsTrue(test_result, logger_buffer);

			mysql_close(&my_sql);
		}

		TEST_METHOD(SelectFunctionEmptyResult)
		{
			MYSQL my_sql;
			mysql_init(&my_sql);

			MySqlConnect(my_sql);


			int query_result = mysql_query(&my_sql, "select id, auth_token from useraccount where id = 'ldkasfjalnf'");
			auto mysql_error_code = mysql_errno(&my_sql);

			WCHAR logger_buffer[512];
			wsprintf(logger_buffer, L"query_result:%d, error:%d", (int)query_result, mysql_error_code);
			Assert::IsTrue(0 == query_result, logger_buffer);

			auto sql_result = mysql_store_result(&my_sql);

			MYSQL_ROW sql_row;
			std::wstring selected_id = L"";
			std::wstring selected_auth_token = L"";

			while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
			{
				selected_id = CA2W(sql_row[TEST_ACCOUNT_COLUMN::ID]);
				selected_auth_token = CA2W(sql_row[TEST_ACCOUNT_COLUMN::AUTH_TOKEN]);
				break;
			}

			mysql_free_result(sql_result);

			bool test_result = (selected_id.empty()) && (selected_auth_token.empty());

			wsprintf(logger_buffer, L"query_result:%d, selected_id:%s, selected_token:%s", (int)query_result, selected_id.c_str(), selected_auth_token.c_str());
			Assert::IsTrue(test_result, logger_buffer);

			mysql_close(&my_sql);
		}
	};
}