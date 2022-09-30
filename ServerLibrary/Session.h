#pragma once
#include"defaultHeader.h"
#include"Global.h"
#include"RingBuffer.h"

enum class OP_TYPE { OP_NONE, OP_RECV, OP_SEND, OP_ACCEPT, OP_ATTACK, OP_POINT_MOVE, OP_DEAD, OP_HEARTBEAT };

class Session;

class EX_OVER_IO
{
public:
	WSAOVERLAPPED	m_over{};
	OP_TYPE			m_op{};
	WSABUF			m_wsabuf[1]{};
	shared_ptr<Session> m_sessionSPtr{};

	void Reset() {
		ZeroMemory(&m_over, sizeof(m_over));
		m_op = OP_TYPE::OP_NONE;
		ZeroMemory(&m_wsabuf, sizeof(m_wsabuf));
		m_sessionSPtr = nullptr;
	};
};

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



#pragma pack(push, 1)
struct PacketHeader
{
	short m_size = 0;
	short m_type = 0;
};
#pragma pack(pop)


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