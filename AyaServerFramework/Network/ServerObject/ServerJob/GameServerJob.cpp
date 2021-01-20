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
	// todo. ���� ��ü ����. ������ ������ ���� ���� ����. 
}

void GameServerJob::OnDisconnect(AYA::SessionObject* session)
{
	// todo. ���� ��ü ����. 
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
		printf("������ ��Ŷ���� ����, �������� ��ȣ�� ��ġ������ buffer deserialize ����.\n");
	}

	
}

bool GameServerJob::LoginRequest(AYA::SessionObject* session, const Client_To_Server::LoginRequest& login_request)
{
	// todo. mysql�� ���� id / pw ��ȸ�Ͽ� ������ ��. �� , pw�� base64�� ���ڵ� �Ǿ� ������ ����� ��. 

	return true;
}

void GameServerJob::OnUpdate()
{
	// todo. broad cast�� ���� session container loop �� �����ϰ� �����ϱ�. 
}