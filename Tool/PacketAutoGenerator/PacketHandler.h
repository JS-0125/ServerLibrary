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



PACKET_HANDLER( CS_LOGIN )
{
	cout << "PACKET: CS_LOGIN" << endl;
	STRUCT_CS_LOGIN recvPacket;
	sessionSP->GetPacket(recvPacket);
}

PACKET_HANDLER( SC_LOGIN_OK )
{
	cout << "PACKET: SC_LOGIN_OK" << endl;
	STRUCT_SC_LOGIN_OK recvPacket;
	sessionSP->GetPacket(recvPacket);
}