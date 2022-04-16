#pragma once
#include<memory>
#include<map>
#include<vector>
#include<mutex>
#include<algorithm>
#include"Session.h"
#include"protocol.h"

using namespace std;

class Session;

enum class ROOM_STATE {
	OPEN,
	FULL,
	EMPTY,
};
class Room
{	
private:
	map<string, shared_ptr<Session>> m_sessions;

	ROOM_STATE m_roomState = ROOM_STATE::OPEN;
	mutex m_roomMutex;
	char m_roomName[MAX_ROOM_NAME]{};
	void CheckRoomState();
public:
	Room() {};
	Room(char*);
	ROOM_STATE Join(char*,shared_ptr<Session>);
	ROOM_STATE Exit(char*, shared_ptr<Session>);
	bool isRoomEmpty();
	ROOM_STATE GetRoomState();
	char* GetRoomName();
	int GetRoomSessionsCnt();

	template<class T>
	bool Broadcast(T*);
};

template<class T>
bool Room::Broadcast(T* packet)
{
	for (auto& session : m_sessions)
		session.second->Send(packet);
	return true;
}

