#pragma once
#include"defaultHeader.h"
#include"RingBuffer.h"

enum class OP_TYPE { OP_RECV, OP_SEND, OP_ACCEPT, OP_ATTACK, OP_POINT_MOVE, OP_DEAD, OP_HEARTBEAT };
enum class OBJECT_STATE { OBJST_FREE, OBJST_CONNECTED, OBJST_INGAME };

struct Server_Detail {
	int server_id;
	std::string server_ip;
	int server_port;
	int network_protocol;
};

struct EX_OVER
{
	WSAOVERLAPPED	m_over;
	WSABUF			m_wsabuf[1];
	RingBuffer			m_packetbuf;
	OP_TYPE			m_op;
	SOCKET			m_csocket;					// OP_ACCEPT에서만 사용
};