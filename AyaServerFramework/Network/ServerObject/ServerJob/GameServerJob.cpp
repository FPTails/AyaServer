#include "GameServerJob.h"
#include <iostream>
#include <fstream>
#include "../../../Util/Buffer/AyaBufferStream.h"
#include "../../../Util/Logger/Logger.h"

GameServerJob::GameServerJob()
{
	UserDBConfig user_db_config;
	AYA::DBConnectData userdb_connect_data;

	if (false == user_db_config.ConvertTo(userdb_connect_data))
	{
		AYA::g_AYALogger->Log("User DB ini file load failed");
		return;
	}

	if (false == m_user_db_executor.Init(userdb_connect_data))
	{
		AYA::g_AYALogger->Log("User Db connect failed");
		return;
	}
}

GameServerJob::~GameServerJob()
{

}

void GameServerJob::OnConnect(AYA::SessionObject* session)
{
	m_user_manager.CreateUserOnSessionConnect(session->GetSessionIndex());
}

void GameServerJob::OnDisconnect(AYA::SessionObject* session)
{
	// todo. ���� ��ü ����. 
	m_user_manager.ReleaseUserOnSessionDisconnect(session->GetSessionIndex());
}

void GameServerJob::OnMessage(AYA::SessionObject* session, AYA::Buffer& recieved_buffer)
{
	// echo test 
	/*AYA::Buffer temp_echo_buffer;
	temp_echo_buffer.Copy(recieved_buffer);

	session->Send(temp_echo_buffer);*/

	int protocol_number = 0;

	AYA::BufferStream buffer_stream(&recieved_buffer);

	if (false == buffer_stream.FrontInt(0, protocol_number))
	{
		return;
	}

	try
	{
		if (Client_To_Server::CLIENT_TO_SERVER_PROTOCOL_NUMBER::LOGIN_REQUEST == protocol_number)
		{
			Client_To_Server::LoginRequest login_request;
			buffer_stream >> login_request;
			LoginRequest(session, login_request);
		}
	}
	catch (...)
	{
		printf("������ ��Ŷ���� ����, �������� ��ȣ�� ��ġ������ buffer deserialize ����.\n");
	}

	
}

bool GameServerJob::LoginRequest(AYA::SessionObject* session, const Client_To_Server::LoginRequest& login_request)
{
	// todo. �ӽ� ��Ŷ ������ ���� ���̹Ƿ�, �α��� ���н� ack ���ִ� ��Ŷ�� ��Ŷ ���ʷ����� �ۼ� ���Ŀ� ���̵��� �Ѵ�. 

	std::wstring valid_password = L"";

	if (false == m_user_db_executor.SelectPassword(login_request.Id, valid_password))
	{
		// todo. ���� ��Ŷ ����. 
		return false;
	}

	// db���� ��ȣȭ�� password�� ����Ǿ� �ִ�. Ŭ�� ��ȣȭ�� password�� ������. 
	if (valid_password != login_request.Password)
	{
		// todo. ���� ��Ŷ ���� ( ��й�ȣ Ʋ�� ) 
		return false;
	}

	UserLoginData login_data;

	if (false == m_user_manager.UserLogin(login_data))
	{
		// todo. ���� ��Ŷ ���� ( �α��� ���� )
		return false;
	}

	return true;
}

void GameServerJob::OnUpdate()
{
	// todo. broad cast�� ���� session container loop �� �����ϰ� �����ϱ�. 
}