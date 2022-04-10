#pragma once
#include"DefaultStruct.h"


class Session : public std::enable_shared_from_this<Session>
{
private:
	EX_OVER m_exover;
	SOCKET m_socket;

	void SetSocket(SOCKET&);
public:
	void Accept(HANDLE, int, SOCKET);
	int Send();
	int Recv();
	void RecvCompletion(size_t);
	void ProcessPacket();

	SOCKET& GetSocket();
	template<class T>
	void GetPacket(T&);
};

