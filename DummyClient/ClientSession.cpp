#include "pch.h"
#include "ClientSession.h"


ClientSession::ClientSession()
{
	//cout << "Session make" << endl;
	session = make_shared<Session>();
	SOCKET sock = socket(PF_INET, SOCK_STREAM, 0);
	session->SetSocket(sock);
	Connect();
}

void ClientSession::Connect()
{
	SOCKADDR_IN addr;

	memset(&addr, 0, sizeof(SOCKADDR_IN));
	addr.sin_port = htons(SERVER_PORT);
	addr.sin_family = AF_INET;
	//addr.sin_addr.S_un.S_addr = inet_addr(SERVER_ADDR);
	inet_pton(AF_INET, SERVER_ADDR, &addr.sin_addr.S_un.S_addr);
	int ret = connect(session->GetSocket(), (SOCKADDR*)&addr, sizeof(addr));

	if (0 != ret) {
		int err_no = WSAGetLastError();
		if (WSA_IO_PENDING != err_no) {
			DisplayError("Connect : ", WSAGetLastError());
			return;
		}
	}
}