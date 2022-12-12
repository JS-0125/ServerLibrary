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
	cout << "connect OK" << endl;
	Sleep(3000);

	for(int i =0;i<sessions.size();++i) {
		STRUCT_CS_NONE packet;
		packet.m_size = sizeof(packet);
		packet.m_type = CS_NONE ;

		send(sessions[i].GetSocket(), (char*)&packet, packet.m_size, 0);
	}
	while (1) {};
}
