#include"pch.h"
#include <iostream>
#include "ClientSession.h"
#include "../ChatServer/PacketStructs.h"
#include "../ChatServer/PacketType.h"

int main()
{
	WSADATA WSAData;
	WSAStartup(MAKEWORD(2, 2), &WSAData);
	wcout.imbue(locale("korean"));

	Sleep(1000);
	vector<ClientSession> sessions;
	sessions.resize(10000);
}
