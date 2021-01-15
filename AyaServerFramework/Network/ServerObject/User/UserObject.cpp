#include "UserObject.h"

UserObject::UserObject()
{
	m_user_key = 0;
	m_session_key = 0;
	m_is_login_success = false;
}

UserObject::~UserObject()
{

}

bool UserObject::InitAtConnect(SESSIONKEY session_key)
{
	m_session_key = session_key;

	return true;
}

bool UserObject::ClearAtDisconnect()
{
	m_user_key = 0;
	m_session_key = 0;
	m_is_login_success = false;

	return true;
}

bool UserObject::Login(const UserLoginData& login_data)
{
	const int INVALID_USER_KEY = 0;

	if (INVALID_USER_KEY >= login_data.UserKey)
	{
		return false;
	}

	m_user_key = login_data.UserKey;

	return true;
}