#include "stdafx.h"
#include "UserDbConfig.h"
#include "../../../Util/Path/SystemPath.h"

UserDBConfig::UserDBConfig()
{
	wchar_t temp_buffer[256] = { NULL , };

	GetPrivateProfileString(L"USER_DB", L"HOST", L"", temp_buffer, 256, INI_FILE_DIRECTORY);
	m_host = CW2A(temp_buffer);

	GetPrivateProfileString(L"USER_DB", L"USER", L"", temp_buffer, 256, INI_FILE_DIRECTORY);
	m_user = CW2A(temp_buffer);

	GetPrivateProfileString(L"USER_DB", L"PASSWORD", L"", temp_buffer, 256, INI_FILE_DIRECTORY);
	m_password = CW2A(temp_buffer);

	GetPrivateProfileString(L"USER_DB", L"DATABASE", L"", temp_buffer, 256, INI_FILE_DIRECTORY);
	m_database = CW2A(temp_buffer);

	m_port = GetPrivateProfileInt(L"USER_DB", L"PORT", 0, INI_FILE_DIRECTORY);
}

bool UserDBConfig::IsLoaded()
{
	if (m_host.empty())
	{
		return false;
	}

	if (m_user.empty())
	{
		return false;
	}

	if (m_password.empty())
	{
		return false;
	}

	if (m_database.empty())
	{
		return false;
	}

	if (0 == m_port)
	{
		return false;
	}

	return true;
}

bool UserDBConfig::ConvertTo(AYA::DBConnectData& out_connect_data)
{
	if (false == IsLoaded())
	{
		return false;
	}

	out_connect_data.Host = m_host;
	out_connect_data.User = m_user;
	out_connect_data.Password = m_password;
	out_connect_data.Database = m_database;
	out_connect_data.Port = m_port;

	return true;
}