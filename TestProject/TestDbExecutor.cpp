#include "pch.h"
#include "CppUnitTest.h"
#include <mysql.h>
#include <atlstr.h> 
#include "../AyaServerFramework/Core/DataBase/Mysql/MysqlExecutor.h"
#include "../AyaServerFramework/Core/DataBase/Mysql/MysqlQueryResult.h"
#include "TestDataBaseEssential.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestDataBase
{
	class TestUserQueryExecutor : public AYA::MysqlExecutor
	{
	public:
		

		bool SelectUser(std::wstring& user_id, std::wstring& out_selected_user_id, std::wstring& out_selected_password)
		{
			std::string converted_user_id = CW2A(user_id.c_str());

			char query_str_buffer[4096];
			sprintf_s(query_str_buffer, "select id, auth_token from useraccount where id = '%s'", converted_user_id.c_str());

			AYA::IDBQueryResult* query_result = Query(query_str_buffer);

			if (nullptr == query_result)
			{
				return false;
			}

			AYA::IDBRow* curr_row = query_result->Next();

			while ((curr_row = query_result->Next()) != nullptr )
			{
				out_selected_user_id = CA2W(curr_row->Get(TEST_ACCOUNT_COLUMN::ID));
				out_selected_password = CA2W(curr_row->Get(TEST_ACCOUNT_COLUMN::AUTH_TOKEN));
				break;
			}

			return true;
		}
	};

	TEST_CLASS(MysqlExecutorBasicCase)
	{
	public:
		TEST_METHOD(InitValid)
		{
			TestUserQueryExecutor user_query_executor;
			bool init_result = user_query_executor.Init(valid_connect_data);
			int error_code = user_query_executor.GetError();

			WCHAR logger_buffer[512];
			wsprintf(logger_buffer, L"result:%d, error_code:%d", (int)init_result, error_code);
			Assert::IsTrue(init_result, logger_buffer);
		}

		TEST_METHOD(QueryValid)
		{
			TestUserQueryExecutor user_query_executor;
			user_query_executor.Init(valid_connect_data);

			std::wstring target_user_id = L"test_id";

			std::wstring selected_user_id = L"";
			std::wstring selected_auth_token = L"";

			bool query_result = user_query_executor.SelectUser(target_user_id, selected_user_id, selected_auth_token);
			int error_code = user_query_executor.GetError();

			WCHAR logger_buffer[512];
			wsprintf(logger_buffer, L"result:%d, error_code:%d", (int)query_result, error_code);
			Assert::IsTrue(query_result, logger_buffer);
		}

		TEST_METHOD(QueryReuseValid)
		{
			TestUserQueryExecutor user_query_executor;
			user_query_executor.Init(valid_connect_data);

			std::wstring target_user_id = L"test_user";

			std::wstring selected_user_id = L"";
			std::wstring selected_auth_token = L"";

			bool query_result = user_query_executor.SelectUser(target_user_id, selected_user_id, selected_auth_token);
			int error_code = user_query_executor.GetError();

			WCHAR logger_buffer[512];
			wsprintf(logger_buffer, L"result:%d, error_code:%d", (int)query_result, error_code);
			Assert::IsTrue(query_result, logger_buffer);

			query_result = user_query_executor.SelectUser(target_user_id, selected_user_id, selected_auth_token);
			error_code = user_query_executor.GetError();

			wsprintf(logger_buffer, L"result:%d, error_code:%d", (int)query_result, error_code);
			Assert::IsTrue(query_result, logger_buffer);

		}

	};

}