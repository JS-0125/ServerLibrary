#pragma once
#include"defaultHeader.h"
#include"Network.h"
#include"Ex_Over.h"

class IOCP: Network
{
	HANDLE h_iocp;
	SOCKADDR_IN m_serverAddr;
	EX_OVER_IO m_acceptOver;
	SOCKET m_listenSocket;
public:
	IOCP() = default;
	~IOCP();
	int Init() override;
	int StartAccept() override;
	int StartAccept(int n);
	int Disconnect(SOCKET& socket) override;

	int StartIoThreads(function<void()> func);
	void PostQueued(int eventType, WSAOVERLAPPED& over);
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
};
