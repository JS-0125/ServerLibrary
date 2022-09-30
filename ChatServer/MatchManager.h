#pragma once
#include"Room.h"

class MatchManager
{
private:
	map<string, shared_ptr<Room>> m_rooms;
public:

	bool CreateRoom();
	bool CreateRoom(char*, shared_ptr<Session>);
	bool EnterRoom(char* roomName, char*, shared_ptr<Session>);
	bool RemoveRoom(char*);
	void SendRoomList(shared_ptr<Session>);
	char** GetRoomNameList();
	int GetRoomsCnt();

	template<class T>
	void Broadcast(char*, T*);
};

template<class T>
void MatchManager::Broadcast(char* roomName, T* packet)
{
	m_rooms.find(roomName)->second->Broadcast(packet);
}