#pragma once
#include"defaultHeader.h"
#include"RingBuffer.h"
#include"Ex_Over.h"
#include"PacketType.h"

extern ObjectPool<EX_OVER_IO> exoverIoPool;

class Session : public enable_shared_from_this<Session>
{
private:
	RingBuffer		m_packetbuf{};
	SOCKET			m_socket{};
public:
	Session() {};
	void SetSocket(SOCKET&);
	void Accept(HANDLE, SOCKET);
	void Disconnect(EX_OVER_IO*);
	int Recv(EX_OVER_IO*);
	void RecvCompletion(size_t, EX_OVER_IO*);
	void SendCompletion(EX_OVER_IO*);

	void ProcessPacket();

	RingBuffer& GetRingBuffer();
	SOCKET& GetSocket();

	template<class T>
	int Send(T*);

	template<class T>
	void GetPacket(T&);
};

template<class T>
int Session::Send(T* packet)
{
	auto p = (PacketHeader)*packet;
	cout << "PacketType - " << p.m_type << " - " << p.m_size << endl;

	auto exoverIo = exoverIoPool.GetObj();

	exoverIo->m_op = OP_TYPE::OP_SEND;

	exoverIo->m_wsabuf[0].buf = reinterpret_cast<char*>(packet);
	exoverIo->m_wsabuf[0].len = p.m_size;
	memset(&(exoverIo->m_over), 0, sizeof(exoverIo->m_over));

	LPDWORD sentBytes = 0;

	int ret = WSASend(m_socket, exoverIo->m_wsabuf, 1, sentBytes, NULL, (LPWSAOVERLAPPED)exoverIo, NULL);
	//cout << "sentBytes - " << (int)sentBytes << endl;

	if (0 != ret) {
		int err_no = WSAGetLastError();
		if (WSA_IO_PENDING != err_no) {
			DisplayError("WSASend : ", WSAGetLastError());
			exoverIoPool.ReturnObj(exoverIo);
			return -1;
		}
	}
	return 0;
}

template<class T>
void Session::GetPacket(T& packet)
{
	m_packetbuf.Dequeue((char*)&packet, sizeof(packet));
}