#pragma once

#define MAX_MESSAGE 128

enum PACKET_TYPE
{
	PACKET_NONE,

	PACKET_CS_LOGIN,
	PACKET_SC_LOGIN_OK,

	PACKET_CS_CHAT,
	PACKET_SC_CHAT,
};

#pragma pack(push, 1)

struct PacketHeader
{
	short m_size = 0;
	short m_type = PACKET_TYPE::PACKET_NONE;
};

struct CSPacketChat : public PacketHeader {
	CSPacketChat() {
		m_size = sizeof(CSPacketChat);
		m_type = (short)PACKET_TYPE::PACKET_CS_CHAT;
	}
	char m_msg[MAX_MESSAGE]{};
};

struct SCPacketChat : public PacketHeader {
	SCPacketChat(char* msg) {
		m_size = sizeof(SCPacketChat);
		m_type = (short)PACKET_TYPE::PACKET_SC_CHAT;
		std::memcpy(m_msg, msg, sizeof(m_msg));
	}
	char m_msg[MAX_MESSAGE]{};
};


#pragma pack(pop)