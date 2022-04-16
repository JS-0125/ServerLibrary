#pragma once
#include"ObjectPool.h"

class Session;

enum class OP_TYPE { OP_NONE, OP_RECV, OP_SEND, OP_ACCEPT, OP_ATTACK, OP_POINT_MOVE, OP_DEAD, OP_HEARTBEAT };

class EX_OVER_IO
{
public:
	WSAOVERLAPPED	m_over{};
	OP_TYPE			m_op{};
	WSABUF			m_wsabuf[1]{};
	shared_ptr<Session> m_sessionSPtr{};

	void Reset(){ 
		ZeroMemory(&m_over, sizeof(m_over));
		m_op = OP_TYPE::OP_NONE;
		ZeroMemory(&m_wsabuf, sizeof(m_wsabuf));
		m_sessionSPtr = nullptr;
	};
};