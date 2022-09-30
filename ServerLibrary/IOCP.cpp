#include "pch.h"
#include "IOCP.h"
#include"Session.h"
#include"Network.h"

IOCP::~IOCP() {
	closesocket(m_listenSocket);
	WSACleanup();
}

int IOCP::Init()
{
	WSADATA WSAData;
	WSAStartup(MAKEWORD(2, 2), &WSAData);

	wcout.imbue(locale("korean"));
	h_iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
	m_listenSocket = WSASocketW(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);

	CreateIoCompletionPort(reinterpret_cast<HANDLE>(m_listenSocket), h_iocp, SERVER_ID, 0);

	memset(&m_serverAddr, 0, sizeof(SOCKADDR_IN));
	m_serverAddr.sin_family = AF_INET;
	m_serverAddr.sin_port = htons(SERVER_PORT);
	m_serverAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	//bind
	int ret = ::bind(m_listenSocket, (struct sockaddr*)&m_serverAddr, sizeof(SOCKADDR_IN));
	if (0 != ret) {
		int err_num = WSAGetLastError();
		if (WSA_IO_PENDING != err_num)
			return DisplayError("bind : ", WSAGetLastError());
	}
	cout << "bind" << endl;

	//listen
	ret = listen(m_listenSocket, SOMAXCONN);
	if (0 != ret) {
		int err_num = WSAGetLastError();
		if (WSA_IO_PENDING != err_num)
			return DisplayError("listen : ", WSAGetLastError());
	}
	cout << "listen" << endl;
	return 0;
}

int IOCP::StartAccept()
{
	m_acceptOver.m_sessionSPtr = make_shared<Session>();
	memset(&m_acceptOver.m_over, 0, sizeof(m_acceptOver.m_over));
	SOCKET c_socket = WSASocketW(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	m_acceptOver.m_sessionSPtr->SetSocket(c_socket);
	m_acceptOver.m_op = OP_TYPE::OP_ACCEPT;

	BOOL ret = AcceptEx(m_listenSocket, c_socket,
		(char*)(m_acceptOver.m_sessionSPtr->GetRingBuffer().GetBuffer())
		, 0, 32, 32, NULL, (LPWSAOVERLAPPED)&m_acceptOver);

	if (0 == ret) {
		int err_num = WSAGetLastError();
		if (err_num != WSA_IO_PENDING)
			return DisplayError("AcceptEx Error", err_num);
	}
	return 0;
}


int IOCP::StartAccept(int n)
{
	memset(&m_acceptOver.m_over, 0, sizeof(m_acceptOver.m_over));
	SOCKET c_socket = WSASocketW(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	m_acceptOver.m_sessionSPtr->SetSocket(c_socket);
	m_acceptOver.m_op = OP_TYPE::OP_ACCEPT;

	BOOL ret = AcceptEx(m_listenSocket, c_socket,
		(char*)(m_acceptOver.m_sessionSPtr->GetRingBuffer().GetBuffer())
		, 0, 32, 32, NULL, (LPWSAOVERLAPPED)&m_acceptOver);

	if (0 == ret) {
		int err_num = WSAGetLastError();
		if (err_num != WSA_IO_PENDING)
			return DisplayError("AcceptEx Error", err_num);
	}
	return 0;
}

void IOCP::PostQueued(int eventType, WSAOVERLAPPED& over) {
	PostQueuedCompletionStatus(h_iocp, 1, eventType, &over);
}

int IOCP::Disconnect(SOCKET& socket)
{
	int ret = closesocket(socket);
	if (0 != ret) {
		int err_no = WSAGetLastError();
		if (WSA_IO_PENDING != err_no)
			return DisplayError("Disconnect : ", WSAGetLastError());
	}
	return 0;
}

int IOCP::StartIoThreads(function<void()> func)
{

	unsigned concurentThreadsSupported = std::thread::hardware_concurrency();
	if (concurentThreadsSupported == 0)
		return -1;
	cout << "StartIoThreads concurentThreadsSupported - " << concurentThreadsSupported << endl;

	vector <thread> worker_threads;
	for (int i = 0; i < concurentThreadsSupported; ++i) {
		worker_threads.emplace_back(func);
		cout << "StartIoThreads - emplace_back" << endl;
	}

	for (auto& th : worker_threads)
		th.join();
	return 0;
}

HANDLE IOCP::GetIocpHandle() {
	return h_iocp;
}

SOCKET IOCP::GetListenSocket() {
	return m_listenSocket;
}
