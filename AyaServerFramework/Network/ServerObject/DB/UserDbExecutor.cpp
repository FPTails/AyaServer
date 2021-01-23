#include "UserDbExecutor.h"
#include <atlstr.h> 
// #include <atlconv.h>

bool UserDBExecutor::SelectPassword(std::wstring& user_id, std::wstring& out_selected_password)
{
	std::string converted_user_id (CW2A(user_id.c_str()));

	char query_str_buffer[4096];
	sprintf_s(query_str_buffer, "select id, auth_token from useraccount where id = '%s'", converted_user_id.c_str());

	AYA::IDBQueryResult* query_result = Query(query_str_buffer);

	if (nullptr == query_result)
	{
		return false;
	}

	for (auto curr_row = query_result->Next(); nullptr != curr_row; curr_row = query_result->Next())
	{
		out_selected_password = CA2W(curr_row->Get(USER_DB_COLUMN::AUTH_TOKEN));
		break;
	}

	return true;
}