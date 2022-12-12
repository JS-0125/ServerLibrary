#include"pch.h"
#include"IOCP.h"
#include"Session.h"
#include"PacketHandler.h"
#include"EventQueue.h"
#define HAVE_STRUCT_TIMESPEC

IOCP server;

void worker()
{
	HANDLE h_iocp = server.GetIocpHandle();
	SOCKET l_socket = server.GetListenSocket();

	while (true) {
		DWORD num_bytes;
		ULONG_PTR ikey;
		WSAOVERLAPPED* over;

		BOOL ret = GetQueuedCompletionStatus(h_iocp, &num_bytes, &ikey, &over, INFINITE);

		EX_OVER_IO* ex_over = reinterpret_cast<EX_OVER_IO*>(over);
		switch (ex_over->m_op) {
		case OP_TYPE::OP_RECV: {
			cout << "RECV - "<< num_bytes << endl;
			auto sessionSPtr = ex_over->m_sessionSPtr;
			sessionSPtr->RecvCompletion(num_bytes, ex_over);
			//cout << "RECV - use count - " << sessionSPtr.use_count() << endl;
			break;
		}
		case OP_TYPE::OP_SEND: {
			cout << "SEND - " << num_bytes << endl;
			auto sessionSPtr = ex_over->m_sessionSPtr;
			sessionSPtr->SendCompletion(ex_over);
			break;
		}
		case OP_TYPE::OP_ACCEPT: {
			//cout << "ACCEPT" << endl;
			auto sessionSPtr = make_shared<Session>();
			sessionSPtr->Accept(h_iocp, ex_over->m_sessionSPtr->GetSocket());
			server.StartAccept(0);
			break;
		}
		}
	}
}


int main()
{
	server.Init();
	server.StartAccept();
	function<void()> func = worker;
	server.StartIoThreads(func);
}