#pragma once
#include "defaultHeader.h"
#include "macro.h"
#include "PacketMacro.h"

class ClientSession
{
private:
	char m_roomName[MAX_ROOM_NAME];
	char m_ID[MAX_ID];
	shared_ptr<Session> session;
public:
	ClientSession();
	void Connect();
};


