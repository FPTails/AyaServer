#pragma once

#include "IAyaJobInterface.h"
#include "../../Session/SessionObject.h"
#include <Client_To_Server_Packet/Client_To_Server_Packet.pb.h>


class GameServerJob : public AYA::IJobInterface
{
public:
	GameServerJob();
	virtual ~GameServerJob();

public:
	virtual void OnConnect(AYA::SessionObject* session) override;
	virtual void OnDisconnect(AYA::SessionObject* session) override;
	virtual void OnMessage(AYA::SessionObject* session, const AYA::Buffer& recieved_buffer) override;
	virtual void OnUpdate() override;
private:
	bool LoginRequest(AYA::SessionObject* session, const Client_To_Server::LoginRequest& login_request);
};
