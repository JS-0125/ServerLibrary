#pragma once
#include"defaultHeader.h"
#include"PacketType.h"
#include"Session.h"
#include"MasterManager.h"

typedef void(*SessionFunction)(shared_ptr<Session>);

static SessionFunction packetHandlerTable[MAX_PACKET_TYPE];

struct SetPacketTable
{
	SetPacketTable(int x, SessionFunction sessionFunc) {
		packetHandlerTable[x] = sessionFunc;
		cout << "SetPacketTable - " << x << endl;
	}
};

#define PACKET_HANDLER(x) \
static void Packet_Handler_##x(shared_ptr<Session>); \
static SetPacketTable _setPacketTable_##x(x, Packet_Handler_##x); \
static void Packet_Handler_##x(shared_ptr<Session> sessionSP)


PACKET_HANDLER(PACKET_CS_CHAT)
{
	cout << "PACKET_CS_CHAT" << endl;
	CSPacketChat recvPacket;
	sessionSP->GetPacket(recvPacket);

	// Broadcast
	SCPacketChat sendPacket;
	memcpy(sendPacket.m_msg, recvPacket.m_msg, sizeof(sendPacket.m_msg));
	memcpy(sendPacket.m_ownerId, recvPacket.m_ownerId, sizeof(sendPacket.m_ownerId));
	cout << recvPacket.m_roomName<< " - " << sendPacket.m_ownerId << ": " << sendPacket.m_msg << endl;
	masterManager.matchManager.Broadcast(recvPacket.m_roomName, &sendPacket);
}

PACKET_HANDLER(PACKET_CS_LOGIN)
{
	cout << "PACKET_CS_LOGIN" << endl;
	CSPacketLogin recvPacket;
	sessionSP->GetPacket(recvPacket);
	
	// Send Login
	if (masterManager.loginManager.Login(recvPacket.m_id, sessionSP)) 
		// Send RoomList
		masterManager.matchManager.SendRoomList(sessionSP);
}

PACKET_HANDLER(PACKET_CS_CREATE_ROOM)
{
	cout << "PACKET_CS_CREATE_ROOM" << endl;
	CSPacketCreateRoom recvPacket;
	sessionSP->GetPacket(recvPacket);

	if (masterManager.matchManager.CreateRoom(recvPacket.m_roomName, sessionSP)) // create room
		masterManager.matchManager.EnterRoom(recvPacket.m_roomName, recvPacket.m_id, sessionSP); // 방 바로 들어가고 패킷 전송
	else // 실패 
		masterManager.matchManager.SendRoomList(sessionSP); // 방 리스트 재전송
}

PACKET_HANDLER(PACKET_CS_ENTER_ROOM)
{
	cout << "PACKET_CS_ENTER_ROOM" << endl;
	CSPacketEnterRoom recvPacket;
	sessionSP->GetPacket(recvPacket);

	masterManager.matchManager.EnterRoom(recvPacket.m_roomName, recvPacket.m_id, sessionSP);
}