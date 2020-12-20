#include "GameServerJob.h"
#include <iostream>
#include <fstream>

using namespace google;

GameServerJob::GameServerJob()
{

}

GameServerJob::~GameServerJob()
{

}

void GameServerJob::OnConnect(AYA::SessionObject* session)
{

}

void GameServerJob::OnDisconnect(AYA::SessionObject* session)
{

}

void GameServerJob::OnMessage(AYA::SessionObject* session, const AYA::Buffer& recieved_buffer)
{
	// echo test 
	/*AYA::Buffer temp_echo_buffer;
	temp_echo_buffer.Copy(recieved_buffer);

	session->Send(temp_echo_buffer);*/

	Client_To_Server::ProcotolType protocol_number = Client_To_Server::ProcotolType::ProcotolType_INT_MIN_SENTINEL_DO_NOT_USE_;

	int front_int_value = 0;
	recieved_buffer.FrontInt(front_int_value);

	protocol_number = (Client_To_Server::ProcotolType)front_int_value;

	if (Client_To_Server::ProcotolType::LOGIN_REQUEST == protocol_number)
	{
		protobuf::io::ArrayInputStream is(recieved_buffer.GetBuffer(), recieved_buffer.GetBufferSize());
		Client_To_Server::LoginRequest src_login_request;
		src_login_request.ParseFromZeroCopyStream(&is);

		LoginRequest(session, src_login_request);
	}
}

bool GameServerJob::LoginRequest(AYA::SessionObject* session, const Client_To_Server::LoginRequest& login_request)
{
	return true;
}

void GameServerJob::OnUpdate()
{
	// todo. broad cast를 위한 session container loop 가 가능하게 수정하기. 
}