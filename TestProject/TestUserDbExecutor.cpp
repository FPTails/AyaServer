#include "pch.h"
#include "CppUnitTest.h"
#include <mysql.h>
#include <atlstr.h> 
#include "../AyaServerFramework/Core/DataBase/Mysql/MysqlExecutor.h"
#include "../AyaServerFramework/Core/DataBase/Mysql/MysqlQueryResult.h"
#include "../AyaServerFramework/Network/ServerObject/DB/UserDbExecutor.h"
#include "TestDataBaseEssential.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestDataBase
{

	TEST_CLASS(UserExecutorBasicCase)
	{
	public:
		
		TEST_METHOD(InitValid)
		{
			UserDBExecutor user_query_executor;
			bool init_result = user_query_executor.Init(valid_connect_data);
			int error_code = user_query_executor.GetError();

			WCHAR logger_buffer[512];
			wsprintf(logger_buffer, L"result:%d, error_code:%d", (int)init_result, error_code);
			Assert::IsTrue(init_result, logger_buffer);
		}

		TEST_METHOD(QueryValid)
		{
			UserDBExecutor user_query_executor;
			user_query_executor.Init(valid_connect_data);

			std::wstring target_user_id = L"test_id";

			std::wstring selected_auth_token = L"";

			bool query_result = user_query_executor.SelectPassword(target_user_id, selected_auth_token);
			int error_code = user_query_executor.GetError();

			bool test_result = Test_User_Auth_Token == selected_auth_token;
			WCHAR logger_buffer[512];
			wsprintf(logger_buffer, L"result:%d, error_code:%d", (int)query_result, error_code);
			Assert::IsTrue(test_result, logger_buffer);
		}

		TEST_METHOD(QueryReuseValid)
		{
			UserDBExecutor user_query_executor;
			user_query_executor.Init(valid_connect_data);

			std::wstring target_user_id = L"test_user";

			std::wstring selected_auth_token = L"";

			bool query_result = user_query_executor.SelectPassword(target_user_id, selected_auth_token);
			int error_code = user_query_executor.GetError();

			WCHAR logger_buffer[512];
			wsprintf(logger_buffer, L"result:%d, error_code:%d", (int)query_result, error_code);
			Assert::IsTrue(query_result, logger_buffer);

			query_result = user_query_executor.SelectPassword(target_user_id, selected_auth_token);
			error_code = user_query_executor.GetError();

			bool test_result = Test_User_Auth_Token == selected_auth_token;
			wsprintf(logger_buffer, L"result:%d, error_code:%d", (int)query_result, error_code);
			Assert::IsTrue(test_result, logger_buffer);

		}

	};

}