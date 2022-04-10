#include "Session.h"
#include"PacketType.h"
#include"PacketHandler.h"

void Session::Accept(HANDLE h_iocp, int c_id, SOCKET socket)
{
	SetSocket(socket);
	m_exover.m_op = OP_TYPE::OP_RECV;
	CreateIoCompletionPort(reinterpret_cast<HANDLE>(m_socket), h_iocp, c_id, 0);
	Recv();
}

void Session::SetSocket(SOCKET& socket)
{
	m_socket = socket;
	int opt_val = true;
	setsockopt(m_socket, IPPROTO_TCP, TCP_NODELAY, (char*)&opt_val, sizeof(opt_val));
}

SOCKET& Session::GetSocket()
{
	return m_socket;
}

int Session::Recv()
{
	m_exover.m_wsabuf[0].buf = m_exover.m_packetbuf.GetBuffer();
	m_exover.m_wsabuf[0].len = m_exover.m_packetbuf.GetFreeSize();

	memset(&m_exover.m_over, 0, sizeof(m_exover.m_over));
	DWORD r_flag = 0;

	int ret = WSARecv(m_socket, m_exover.m_wsabuf, 1,
		NULL, &r_flag, &m_exover.m_over, NULL);

	if (0 != ret) {
		int err_no = WSAGetLastError();
		if (WSA_IO_PENDING != err_no)
			DisplayError("WSARecv : ", WSAGetLastError());
	}

	return 0;
}

void Session::RecvCompletion(size_t len)
{
	m_exover.m_packetbuf.Commit(len);
}

void Session::ProcessPacket()
{
	PacketHeader header;

	if (m_exover.m_packetbuf.Peek((char*)&header, sizeof(header)) <= 0)
		return;

	packetHandlerTable[(int)(header.m_type)](*this);
}

template<class T>
void Session::GetPacket(T& packet)
{
	m_exover.m_packetbuf.Dequeue((char*)&packet, sizeof(packet));
}