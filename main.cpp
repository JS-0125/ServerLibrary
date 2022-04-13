#include"IOCP.h"
#include"Session.h"

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

		int key = static_cast<int>(ikey);

		if (FALSE == ret) {
			if (SERVER_ID == key) {
				DisplayError("GQCS : ", WSAGetLastError());
				// exit(-1);
			}
			else {
				DisplayError("GQCS : ", WSAGetLastError());
				// disconnect
			}
		}
		if ((key != SERVER_ID) && (0 == num_bytes)) {
			// disconnect
			continue;
		}

		EX_OVER_IO* ex_over = reinterpret_cast<EX_OVER_IO*>(over);
		switch (ex_over->m_op) {
		case OP_TYPE::OP_RECV: {
			auto sessionSPtr = ex_over->m_sessionSPtr;
			cout << "RECV - "<< num_bytes << endl;
			sessionSPtr->RecvCompletion(num_bytes, ex_over);
			break;
		}
		case OP_TYPE::OP_SEND:
			delete ex_over;
			break;
		case OP_TYPE::OP_ACCEPT: {
			cout << "ACCEPT" << endl;
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