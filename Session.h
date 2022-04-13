#pragma once
#include"defaultHeader.h"
#include"RingBuffer.h"
#include"Ex_Over.h"

class Session : public enable_shared_from_this<Session>
{
private:
	RingBuffer		m_packetbuf{};
	SOCKET			m_socket{};
public:
	Session() {};
	void SetSocket(SOCKET&);
	void Accept(HANDLE, SOCKET);
	template<class T>
	int Send(T*);
	int Recv(EX_OVER_IO*);
	void RecvCompletion(size_t, EX_OVER_IO*);
	void SendCompletion(EX_OVER_IO*);

	void ProcessPacket();

	RingBuffer& GetRingBuffer();
	SOCKET& GetSocket();

	template<class T>
	void GetPacket(T&);
};