#include"IOCP.h"
#include"RingBuffer.h"
#include"Session.h"

IOCP server;
vector<Session> sessions;
int uniq_key = 1;

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
		EX_OVER* ex_over = reinterpret_cast<EX_OVER*>(over);

		switch (ex_over->m_op) {
		case OP_TYPE::OP_RECV: {
			cout << "RECV - "<< num_bytes << endl;
			sessions[key].RecvCompletion(num_bytes);
			sessions[key].ProcessPacket();
			sessions[key].Recv();
			break;
		}
		case OP_TYPE::OP_SEND:
			delete ex_over;
			break;
		case OP_TYPE::OP_ACCEPT: {
			cout << "accept" << endl;
			int c_id = uniq_key++;
			cout << "new id :" << c_id << endl;

			if (-1 != c_id) {
				sessions[c_id].Accept(h_iocp, c_id, ex_over->m_csocket);
			}
			else {
				//CloseSocket;
			}

			memset(&ex_over->m_over, 0, sizeof(ex_over->m_over));
			SOCKET c_socket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
			ex_over->m_csocket = c_socket;
			AcceptEx(l_socket, c_socket, (char*)(ex_over->m_packetbuf.GetBuffer()), 0, 32, 32, NULL, &ex_over->m_over);
			break;
		}
		}
	}
}


int main()
{
	sessions.resize(100);

	server.Init();
	server.StartAccept();
	function<void()> func = worker;
	server.StartIoThreads(func);
}