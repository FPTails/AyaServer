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
	// todo. 유저 객체 삭제. 
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
		printf("변조된 패킷으로 인해, 프로토콜 번호는 일치하지만 buffer deserialize 실패.\n");
	}

	
}

bool GameServerJob::LoginRequest(AYA::SessionObject* session, const Client_To_Server::LoginRequest& login_request)
{
	// todo. 임시 패킷 구조만 잡은 것이므로, 로그인 실패시 ack 해주는 패킷은 패킷 제너레이터 작성 이후에 붙이도록 한다. 

	std::wstring valid_password = L"";

	if (false == m_user_db_executor.SelectPassword(login_request.Id, valid_password))
	{
		// todo. 실패 패킷 전송. 
		return false;
	}

	// db에는 암호화된 password가 저장되어 있다. 클라도 암호화된 password를 보낸다. 
	if (valid_password != login_request.Password)
	{
		// todo. 실패 패킷 전송 ( 비밀번호 틀림 ) 
		return false;
	}

	UserLoginData login_data;

	if (false == m_user_manager.UserLogin(login_data))
	{
		// todo. 실패 패킷 전송 ( 로그인 실패 )
		return false;
	}

	return true;
}

void GameServerJob::OnUpdate()
{
	// todo. broad cast를 위한 session container loop 가 가능하게 수정하기. 
}