#pragma once
#include"pch.h"
#include"PacketMacro.h"
#include"PacketType.h"

#pragma pack(push, 1)

// struct + packet header
// Login Packet----------------------------------------

struct STRUCT_CS_LOGIN : public PacketHeader {
	STRUCT_CS_LOGIN() {
		m_size = sizeof(STRUCT_CS_LOGIN);
		m_type = (short)PACKET_TYPE::CS_LOGIN;
	}
	char m_id[MAX_ID]{};
};


struct STRUCT_SC_LOGIN_RESULT : public PacketHeader {
	STRUCT_SC_LOGIN_RESULT() {
		m_size = sizeof(STRUCT_SC_LOGIN_RESULT);
		m_type = (short)PACKET_TYPE::SC_LOGIN_RESULT;
	}
	char m_id[MAX_ID]{};
	bool m_result = true;
};


// Room Packet

struct STRUCT_SC_ROOM_LIST : public PacketHeader {
	STRUCT_SC_ROOM_LIST() {
		m_size = sizeof(STRUCT_SC_ROOM_LIST);
		m_type = (short)PACKET_TYPE::SC_ROOM_LIST;
	}
	int m_roomCnt = 0;
	char m_roomNames[MAX_ROOM][MAX_ROOM_NAME]{};
};


struct STRUCT_SC_ROOM_CHANGE : public PacketHeader {
	STRUCT_SC_ROOM_CHANGE() {
		m_size = sizeof(STRUCT_SC_ROOM_CHANGE);
		m_type = (short)PACKET_TYPE::SC_ROOM_CHANGE;
	}
	char m_roomName[MAX_ROOM_NAME]{};
	bool isNew = true;
};

struct STRUCT_CS_CREATE_ROOM : public PacketHeader {
	STRUCT_CS_CREATE_ROOM() {
		m_size = sizeof(STRUCT_CS_CREATE_ROOM);
		m_type = (short)PACKET_TYPE::CS_CREATE_ROOM;
	}
	char m_id[MAX_ID]{};
	char m_roomName[MAX_ROOM_NAME]{};
};

struct STRUCT_SC_CREATE_ROOM_RESULT : public PacketHeader {
	STRUCT_SC_CREATE_ROOM_RESULT() {
		m_size = sizeof(STRUCT_SC_CREATE_ROOM_RESULT);
		m_type = (short)PACKET_TYPE::SC_CREATE_ROOM_RESULT;
	}
	char m_roomName[MAX_ROOM_NAME]{};
	bool result = true;
};

struct STRUCT_CS_ENTER_ROOM : public PacketHeader {
	STRUCT_CS_ENTER_ROOM() {
		m_size = sizeof(STRUCT_CS_ENTER_ROOM);
		m_type = (short)PACKET_TYPE::CS_ENTER_ROOM;
	}
	char m_id[MAX_ID]{};
	char m_roomName[MAX_ROOM_NAME]{};
};

struct STURCT_SC_ENTER_ROOM_RESULT : public PacketHeader {
	STURCT_SC_ENTER_ROOM_RESULT() {
		m_size = sizeof(STURCT_SC_ENTER_ROOM_RESULT);
		m_type = (short)PACKET_TYPE::SC_ENTER_ROOM_RESULT;
	}
	bool result = true;
	int m_sessionCnt = 0;
	char m_roomName[MAX_ROOM_NAME]{};
	char m_otherSessionsID[MAX_ROOM_SESSION][MAX_ID]{};
};

struct STRUCT_CS_EXIT_ROOM : public PacketHeader {
	STRUCT_CS_EXIT_ROOM() {
		m_size = sizeof(STRUCT_CS_EXIT_ROOM);
		m_type = (short)PACKET_TYPE::CS_EXIT_ROOM;
	}
};

struct STRUCT_SC_EXIT_ROOM_OK : public PacketHeader {
	STRUCT_SC_EXIT_ROOM_OK() {
		m_size = sizeof(STRUCT_SC_EXIT_ROOM_OK);
		m_type = (short)PACKET_TYPE::SC_EXIT_ROOM_OK;
	}
};

// Chat Pakcet -------------------------------

struct STRUCT_CS_CHAT : public PacketHeader {
	STRUCT_CS_CHAT() {
		m_size = sizeof(STRUCT_CS_CHAT);
		m_type = (short)PACKET_TYPE::CS_CHAT;
	}
	char m_msg[MAX_MESSAGE]{};
	char m_roomName[MAX_ROOM_NAME]{};
	char m_ownerId[MAX_ID]{};
};

struct STRUCT_SC_CHAT : public PacketHeader {
	STRUCT_SC_CHAT() {
		m_size = sizeof(STRUCT_SC_CHAT);
		m_type = (short)PACKET_TYPE::SC_CHAT;
	}
	char m_msg[MAX_MESSAGE]{};
	char m_ownerId[MAX_ID]{};
};

#pragma pack(pop)
#pragma pack(push, 1)
struct STRUCT_CS_NONE : public PacketHeader{
	STRUCT_CS_NONE() {
		m_size = sizeof(CS_NONE);
		m_type = (short)PACKET_TYPE::CS_NONE;
	}
};
#pragma pack(pop)
#pragma pack(push, 1)
struct STRUCT_SC_NONE : public PacketHeader{
	STRUCT_SC_NONE() {
		m_size = sizeof(SC_NONE);
		m_type = (short)PACKET_TYPE::SC_NONE;
	}
};
#pragma pack(pop)
#pragma pack(push, 1)
struct STRUCT_SC_ENTER_ROOM_RESULT : public PacketHeader{
	STRUCT_SC_ENTER_ROOM_RESULT() {
		m_size = sizeof(SC_ENTER_ROOM_RESULT);
		m_type = (short)PACKET_TYPE::SC_ENTER_ROOM_RESULT;
	}
};
#pragma pack(pop)