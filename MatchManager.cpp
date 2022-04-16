#include "MatchManager.h"
#include "PacketType.h"

bool MatchManager::CreateRoom(){}

bool MatchManager::CreateRoom(char* roomName, shared_ptr<Session> sessionSP)
{
    cout << "CreateRoom " << roomName << endl;
    // ��Ŷ �غ�
    SCPacketCreateRoomResult createRoomResultPacket;
    memcpy(createRoomResultPacket.m_roomName, roomName, sizeof(createRoomResultPacket.m_roomName));

    // �� ����� ����
    if (m_rooms.size() == MAX_ROOM || m_rooms.find(roomName) != m_rooms.end()) {
        cout << "�� ����� ����" << endl;

        createRoomResultPacket.result = false;
        sessionSP->Send(&createRoomResultPacket);
        return false;
    }
    // �� ����� ����
    cout << "�� ����� ����" << endl;

    m_rooms[roomName] = make_shared<Room>(roomName);
    createRoomResultPacket.result = true;
    sessionSP->Send(&createRoomResultPacket);

    return true;
}

bool MatchManager::EnterRoom(char* roomName, char* id, shared_ptr<Session> sessionSP)
{
    cout << "EnterRoom " << roomName<< endl;
    cout << "m_rooms size() : " << m_rooms.size() << endl;
 
    auto targetRoom = m_rooms.find(roomName);
    //�� ���� ����
    if (targetRoom == m_rooms.end()) {
        cout << "�� ���� ����" << endl;
        SCPacketEnterRoomResult enterRoomResultPacket;
        enterRoomResultPacket.result = false;
        sessionSP->Send(&enterRoomResultPacket);
        return false;
    }
    // �� ���� ����
    cout << "�� ���� ����" << endl;

    (*targetRoom).second->Join(id, sessionSP);
    return true;
}

bool MatchManager::RemoveRoom(char* roomName)
{
    if(m_rooms.find(roomName) == m_rooms.end())
        return false;
    m_rooms.erase(roomName);
    return true;
}

void MatchManager::SendRoomList(shared_ptr<Session> sessionSP)
{
    SCPacketRoomList roomListPacket;
    roomListPacket.m_roomCnt = m_rooms.size();
    int i = 0;

    for (auto& room : m_rooms) {
        memcpy(roomListPacket.m_roomNames[i], room.first.c_str(), sizeof(roomListPacket.m_roomNames[i]));
        cout << roomListPacket.m_roomNames[i] << endl;
        i++;
    }

    //for (int i = 0; i < m_rooms.size(); ++i)
        //memcpy(roomListPacket.m_roomNames[i], m_rooms[i].c_str(), sizeof(roomListPacket.m_roomNames[i]));
    sessionSP->Send(&roomListPacket);
}

//char** MatchManager::GetRoomNameList()
//{
//    return m_roomNames.data();
//}

int MatchManager::GetRoomsCnt()
{
    return m_rooms.size();
}

