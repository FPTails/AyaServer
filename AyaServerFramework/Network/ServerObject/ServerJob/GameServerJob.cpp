#include "GameServerJob.h"
#include <iostream>
#include <fstream>
#include "../../../Util/Buffer/AyaBufferStream.h"

using namespace google;

GameServerJob::GameServerJob()
{

}

GameServerJob::~GameServerJob()
{

}

void GameServerJob::OnConnect(AYA::SessionObject* session)
{
	// todo. 유저 객체 생성. 하지만 인증은 받지 않은 상태. 
}

void GameServerJob::OnDisconnect(AYA::SessionObject* session)
{
	// todo. 유저 객체 삭제. 
}

void GameServerJob::OnMessage(AYA::SessionObject* session, AYA::Buffer& recieved_buffer)
{
	// echo test 
	/*AYA::Buffer temp_echo_buffer;
	temp_echo_buffer.Copy(recieved_buffer);

	session->Send(temp_echo_buffer);*/

	Client_To_Server::ProcotolType protocol_number = Client_To_Server::ProcotolType::ProcotolType_INT_MIN_SENTINEL_DO_NOT_USE_;

	AYA::BufferStream buffer_stream(&recieved_buffer);

	int front_int_value = 0;

	if (false == buffer_stream.FrontInt(0, front_int_value))
	{
		return;
	}

	protocol_number = (Client_To_Server::ProcotolType)front_int_value;

	try
	{
		if (Client_To_Server::ProcotolType::LOGIN_REQUEST == protocol_number)
		{
			protobuf::io::ArrayInputStream is(recieved_buffer.GetBuffer(), recieved_buffer.GetBufferSize());
			Client_To_Server::LoginRequest src_login_request;
			src_login_request.ParseFromZeroCopyStream(&is);

			LoginRequest(session, src_login_request);
		}
	}
	catch (...)
	{
		printf("변조된 패킷으로 인해, 프로토콜 번호는 일치하지만 buffer deserialize 실패.\n");
	}

	
}

bool GameServerJob::LoginRequest(AYA::SessionObject* session, const Client_To_Server::LoginRequest& login_request)
{
	// todo. mysql을 통해 id / pw 조회하여 인증할 것. 단 , pw는 base64로 인코딩 되어 서버가 몰라야 함. 

	return true;
}

void GameServerJob::OnUpdate()
{
	// todo. broad cast를 위한 session container loop 가 가능하게 수정하기. 
}