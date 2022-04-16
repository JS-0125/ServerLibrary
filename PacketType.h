#pragma once
#include"../../ServerLibrary/ServerLibrary/protocol.h"

using namespace std;

enum PACKET_TYPE
{
	PACKET_NONE,

	// Login
	PACKET_CS_LOGIN,
	PACKET_SC_LOGIN_RESULT,

	// Room
	PACKET_SC_ROOM_LIST,

	PACKET_SC_ROOM_CHANGE,

	PACKET_CS_CREATE_ROOM,
	PACKET_SC_CREATE_ROOM_RESULT,

	PACKET_CS_ENTER_ROOM,
	PACKET_SC_ENTER_ROOM_RESULT,

	PACKET_CS_EXIT_ROOM,
	PACKET_SC_EXIT_ROOM_OK,

	// Chat
	PACKET_CS_CHAT,
	PACKET_SC_CHAT,
};

#pragma pack(push, 1)

struct PacketHeader
{
	short m_size = 0;
	short m_type = PACKET_TYPE::PACKET_NONE;
};

// Login Packet----------------------------------------

struct CSPacketLogin : public PacketHeader {
	CSPacketLogin() {
		m_size = sizeof(CSPacketLogin);
		m_type = (short)PACKET_TYPE::PACKET_CS_LOGIN;
	}
	char m_id[MAX_ID]{};
};


struct SCPacketLoginResult : public PacketHeader {
	SCPacketLoginResult() {
		m_size = sizeof(SCPacketLoginResult);
		m_type = (short)PACKET_TYPE::PACKET_SC_LOGIN_RESULT;
	}
	char m_id[MAX_ID]{};
	bool m_result = true;
};


// Room Packet

struct SCPacketRoomList : public PacketHeader {
	SCPacketRoomList() {
		m_size = sizeof(SCPacketRoomList);
		m_type = (short)PACKET_TYPE::PACKET_SC_ROOM_LIST;
	}
	int m_roomCnt = 0;
	char m_roomNames[MAX_ROOM][MAX_ROOM_NAME]{};
};


struct SCPacketRoomChange : public PacketHeader {
	SCPacketRoomChange() {
		m_size = sizeof(SCPacketRoomChange);
		m_type = (short)PACKET_TYPE::PACKET_SC_ROOM_CHANGE;
	}
	char m_roomName[MAX_ROOM_NAME]{};
	bool isNew = true;
};

struct CSPacketCreateRoom : public PacketHeader {
	CSPacketCreateRoom() {
		m_size = sizeof(CSPacketCreateRoom);
		m_type = (short)PACKET_TYPE::PACKET_CS_CREATE_ROOM;
	}
	char m_id[MAX_ID]{};
	char m_roomName[MAX_ROOM_NAME]{};
};

struct SCPacketCreateRoomResult : public PacketHeader {
	SCPacketCreateRoomResult() {
		m_size = sizeof(SCPacketCreateRoomResult);
		m_type = (short)PACKET_TYPE::PACKET_SC_CREATE_ROOM_RESULT;
	}
	char m_roomName[MAX_ROOM_NAME]{};
	bool result = true;
};

struct CSPacketEnterRoom : public PacketHeader {
	CSPacketEnterRoom() {
		m_size = sizeof(CSPacketEnterRoom);
		m_type = (short)PACKET_TYPE::PACKET_CS_ENTER_ROOM;
	}
	char m_id[MAX_ID]{};
	char m_roomName[MAX_ROOM_NAME]{};
};

struct SCPacketEnterRoomResult : public PacketHeader {
	SCPacketEnterRoomResult() {
		m_size = sizeof(SCPacketEnterRoomResult);
		m_type = (short)PACKET_TYPE::PACKET_SC_ENTER_ROOM_RESULT;
	}
	bool result = true;
	int m_sessionCnt = 0;
	char m_roomName[MAX_ROOM_NAME]{};
	char m_otherSessionsID[MAX_ROOM_SESSION][MAX_ID]{};
};

struct CSPacketExitRoom : public PacketHeader {
	CSPacketExitRoom() {
		m_size = sizeof(CSPacketExitRoom);
		m_type = (short)PACKET_TYPE::PACKET_CS_EXIT_ROOM;
	}
};

struct SCPacketExitRoomOK : public PacketHeader {
	SCPacketExitRoomOK() {
		m_size = sizeof(SCPacketExitRoomOK);
		m_type = (short)PACKET_TYPE::PACKET_SC_EXIT_ROOM_OK;
	}
};

// Chat Pakcet -------------------------------

struct CSPacketChat : public PacketHeader {
	CSPacketChat() {
		m_size = sizeof(CSPacketChat);
		m_type = (short)PACKET_TYPE::PACKET_CS_CHAT;
	}
	char m_msg[MAX_MESSAGE]{};
	char m_roomName[MAX_ROOM_NAME]{};
	char m_ownerId[MAX_ID]{};
};

struct SCPacketChat : public PacketHeader {
	SCPacketChat() {
		m_size = sizeof(SCPacketChat);
		m_type = (short)PACKET_TYPE::PACKET_SC_CHAT;
	}
	char m_msg[MAX_MESSAGE]{};
	char m_ownerId[MAX_ID]{};
};

#pragma pack(pop)