#pragma once
#include"DefaultStruct.h"

class ServerManager
{
	static HANDLE h_iocp;
	SOCKADDR_IN m_serverAddr;
	EX_OVER m_acceptOver;
	SOCKET m_listenSocket;
public:
	ServerManager();
	~ServerManager();
	void Init();

	void PostQueued(int eventType, WSAOVERLAPPED& over);
	bool Send(void* p, SOCKET& socket);
	void Recv(SOCKET& socket, EX_OVER& ex_over, int prev_size);
	void Disconnect(SOCKET& socket);
	int TcpSetKeepAlive(int nSockFd_, int nKeepAlive_, int nKeepAliveIdle_, int nKeepAliveCnt_, int nKeepAliveInterval_)
	{
		int nRtn;

		nRtn = setsockopt(nSockFd_, SOL_SOCKET, SO_KEEPALIVE, (const char*)&nKeepAlive_, sizeof(nKeepAlive_));
		if (nRtn == -1)
		{
			return -1;
		}

		nRtn = setsockopt(nSockFd_, IPPROTO_TCP, TCP_KEEPIDLE, (const char*)&nKeepAliveIdle_, sizeof(nKeepAliveIdle_));
		if (nRtn == -1)
		{
			return -1;
		}

		nRtn = setsockopt(nSockFd_, IPPROTO_TCP, TCP_KEEPCNT, (const char*)&nKeepAliveCnt_, sizeof(nKeepAliveCnt_));
		if (nRtn == -1)
		{
			return -1;
		}

		nRtn = setsockopt(nSockFd_, IPPROTO_TCP, TCP_KEEPINTVL, (const char*)&nKeepAliveInterval_, sizeof(nKeepAliveInterval_));
		if (nRtn == -1)
		{
			return -1;
		}
		return nRtn;
	}
	HANDLE GetIocpHandle();
	SOCKET GetListenSocket();
	void DisplayError(const char* msg, int err_no);
};
