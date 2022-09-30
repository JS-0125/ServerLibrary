#pragma once
#include"pch.h"
#include"PacketMacro.h"
#include"PacketType.h"


#pragma pack(push, 1)
struct STRUCT_CS_LOGIN : public PacketHeader{
	STRUCT_CS_LOGIN() {
		m_size = sizeof(CS_LOGIN);
		m_type = (short)PACKET_TYPE::CS_LOGIN;
	}
};
#pragma pack(pop)
#pragma pack(push, 1)
struct STRUCT_SC_LOGIN_OK : public PacketHeader{
	STRUCT_SC_LOGIN_OK() {
		m_size = sizeof(SC_LOGIN_OK);
		m_type = (short)PACKET_TYPE::SC_LOGIN_OK;
	}
};
#pragma pack(pop)