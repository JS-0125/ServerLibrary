#include "pch.h"
#include "Session.h"
#include"RingBuffer.h"
#include "Global.h"

void Session::Accept(HANDLE h_iocp, SOCKET socket)
{
	SetSocket(socket);
	CreateIoCompletionPort(reinterpret_cast<HANDLE>(m_socket), h_iocp, (ULONG_PTR)this, 0);
	EX_OVER_IO* ex_overIo = exoverIoPool.GetObj();
	Recv(ex_overIo);
}

void Session::Disconnect(EX_OVER_IO* exoverIo)
{
	exoverIoPool.ReturnObj(exoverIo);
}

void Session::SetSocket(SOCKET& socket)
{
	m_socket = socket;
	int opt_val = true;
	setsockopt(m_socket, IPPROTO_TCP, TCP_NODELAY, (char*)&opt_val, sizeof(opt_val));
}

RingBuffer& Session::GetRingBuffer()
{
	return m_packetbuf;
}

SOCKET& Session::GetSocket()
{
	return m_socket;
}

int Session::Recv(EX_OVER_IO* exoverIo)
{
	exoverIo->m_op = OP_TYPE::OP_RECV;

	exoverIo->m_sessionSPtr = shared_from_this();

	exoverIo->m_wsabuf[0].buf = m_packetbuf.GetBuffer();
	exoverIo->m_wsabuf[0].len = m_packetbuf.GetFreeSize();

	memset(&exoverIo->m_over, 0, sizeof(exoverIo->m_over));
	DWORD r_flag = 0;

	int ret = WSARecv(m_socket, exoverIo->m_wsabuf, 1, NULL, &r_flag, (LPWSAOVERLAPPED)exoverIo, NULL);

	if (0 != ret) {
		int err_no = WSAGetLastError();
		if (WSA_IO_PENDING != err_no) {
			DisplayError("WSARecv : ", WSAGetLastError());
			return -1;
		}
	}
	return 0;
}

void Session::RecvCompletion(size_t len, EX_OVER_IO* exoverIo)
{
	m_packetbuf.Commit(len);
	ProcessPacket();
	if (Recv(exoverIo) < 0)
		Disconnect(exoverIo);
	cout << "RecvCompletion use count - " << exoverIo->m_sessionSPtr.use_count() << endl;
}

void Session::SendCompletion( EX_OVER_IO* exoverIo)
{
	exoverIoPool.ReturnObj(exoverIo);
}

void Session::ProcessPacket()
{
	PacketHeader header;

	if (m_packetbuf.Peek((char*)&header, sizeof(header)) <= 0)
		return;

	auto session = shared_from_this();
	packetHandlerTable[(int)(header.m_type)](session);
}