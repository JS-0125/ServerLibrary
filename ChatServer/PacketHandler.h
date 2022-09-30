#pragma once
#include"pch.h"
#include"PacketStructs.h"
#include"PacketType.h"
#include"MasterManager.h"

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

// packet handler 자동화
// Examples
PACKET_HANDLER(CS_LOGIN)
{
	cout << "PACKET: CS_LOGIN" << endl;
	STRUCT_CS_LOGIN recvPacket;
	sessionSP->GetPacket(recvPacket);
	
	// Send Login
	if (masterManager.loginManager.Login(recvPacket.m_id, sessionSP)) 
		// Send RoomList
		masterManager.matchManager.SendRoomList(sessionSP);
}

PACKET_HANDLER(CS_CREATE_ROOM)
{
	cout << "PACKET: CS_CREATE_ROOM" << endl;
	STRUCT_CS_CREATE_ROOM recvPacket;
	sessionSP->GetPacket(recvPacket);

	if (masterManager.matchManager.CreateRoom(recvPacket.m_roomName, sessionSP)) // create room
		masterManager.matchManager.EnterRoom(recvPacket.m_roomName, recvPacket.m_id, sessionSP); // 방 바로 들어가고 패킷 전송
	else // 실패 
		masterManager.matchManager.SendRoomList(sessionSP); // 방 리스트 재전송
}

PACKET_HANDLER(CS_ENTER_ROOM)
{
	cout << "PACKET: CS_ENTER_ROOM" << endl;
	STRUCT_CS_ENTER_ROOM recvPacket;
	sessionSP->GetPacket(recvPacket);

	masterManager.matchManager.EnterRoom(recvPacket.m_roomName, recvPacket.m_id, sessionSP);
}

PACKET_HANDLER(CS_CHAT)
{
	cout << "PACKET: CS_CHAT" << endl;
	STRUCT_CS_CHAT recvPacket;
	sessionSP->GetPacket(recvPacket);

	// Broadcast
	STRUCT_SC_CHAT sendPacket;
	memcpy(sendPacket.m_msg, recvPacket.m_msg, sizeof(sendPacket.m_msg));
	memcpy(sendPacket.m_ownerId, recvPacket.m_ownerId, sizeof(sendPacket.m_ownerId));
	cout << recvPacket.m_roomName << " - " << sendPacket.m_ownerId << ": " << sendPacket.m_msg << endl;
	masterManager.matchManager.Broadcast(recvPacket.m_roomName, &sendPacket);
}