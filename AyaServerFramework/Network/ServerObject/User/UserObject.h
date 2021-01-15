#pragma once

#include <memory>

typedef unsigned long USERKEY;
typedef int SESSIONKEY;

struct UserLoginData
{
	SESSIONKEY SessionKey = 0;
	USERKEY UserKey = 0;
};

class UserObject
{
public:
	UserObject();
	~UserObject();

public:
	inline const USERKEY GetUserKey() const { return m_user_key; }
	inline const SESSIONKEY GetSessionKey() const { return m_session_key; }
	inline const bool IsLoginSuccess() const { return m_is_login_success; }

public:
	bool InitAtConnect(SESSIONKEY session_key);
	bool ClearAtDisconnect();
	bool Login(const UserLoginData& login_data);

private:
	USERKEY m_user_key;
	SESSIONKEY m_session_key;
	bool m_is_login_success;
};

typedef std::shared_ptr<UserObject> UserObjectSmartPointer;