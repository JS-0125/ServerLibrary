#pragma once
#include"defaultHeader.h"
#include"PacketType.h"
#include"Session.h"

typedef void(*SessionFunction)(Session&);

static SessionFunction packetHandlerTable[MAX_PACKET_TYPE];

struct SetPacketTable
{
	SetPacketTable(int x, SessionFunction sessionFunc) {
		packetHandlerTable[x] = sessionFunc;
		cout << "SetPacketTable - " << x << endl;
	}
};

#define PACKET_HANDLER(x) \
static void Packet_Handler_##x(Session&); \
static SetPacketTable _setPacketTable_##x(x, Packet_Handler_##x); \
static void Packet_Handler_##x(Session& sessionSP)


PACKET_HANDLER(PACKET_CS_CHAT)
{
	CSPacketChat packet;
	sessionSP.GetPacket(packet);
	cout << packet.m_msg << endl;
}