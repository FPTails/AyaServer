#pragma once

#include "../../../Core/ThreadObject/IAyaJobInterface.h"
#include "../../Session/SessionObject.h"
#include <Client_To_Server_Packet/Client_To_Server_Packet.pb.h>
#include "../User/UserManager.h"
#include "../DB/UserDbExecutor.h"
#include "../DB/UserDbConfig.h"

class GameServerJob : public AYA::IJobInterface
{
public:
	GameServerJob();
	virtual ~GameServerJob();

public:
	virtual void OnConnect(AYA::SessionObject* session) override;
	virtual void OnDisconnect(AYA::SessionObject* session) override;
	virtual void OnMessage(AYA::SessionObject* session, AYA::Buffer& recieved_buffer) override;
	virtual void OnUpdate() override;
private:
	bool LoginRequest(AYA::SessionObject* session, const Client_To_Server::LoginRequest& login_request);

private:
	UserManager m_user_manager;
	UserDBExecutor m_user_db_executor;
};
