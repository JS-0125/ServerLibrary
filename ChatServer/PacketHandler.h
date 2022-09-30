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

// packet handler �ڵ�ȭ
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
		masterManager.matchManager.EnterRoom(recvPacket.m_roomName, recvPacket.m_id, sessionSP); // �� �ٷ� ���� ��Ŷ ����
	else // ���� 
		masterManager.matchManager.SendRoomList(sessionSP); // �� ����Ʈ ������
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