#include "Room.h"
#include "PacketType.h"

Room::Room(char* roomName)
{
    m_roomState = ROOM_STATE::OPEN;
    memcpy(m_roomName, roomName, sizeof(m_roomName));
}

void Room::CheckRoomState()
{
    if (m_sessions.empty())
        m_roomState = ROOM_STATE::EMPTY;
    else if(m_sessions.size() == MAX_ROOM_SESSION)
        m_roomState = ROOM_STATE::FULL;
    else
        m_roomState = ROOM_STATE::OPEN;
}


ROOM_STATE Room::Join(char* id, shared_ptr<Session> sessionSP)
{
    lock_guard<mutex> lock(m_roomMutex);

    if(m_sessions.find(id) != m_sessions.end() || m_roomState != ROOM_STATE::OPEN)
        return m_roomState;

    m_sessions.emplace(id, sessionSP);
    CheckRoomState();

    cout << m_roomName << " Room Join" << endl;
    SCPacketEnterRoomResult enterRoomResultPacket;
    enterRoomResultPacket.result = true;
    memcpy(enterRoomResultPacket.m_roomName, m_roomName, MAX_ROOM_NAME);
    enterRoomResultPacket.m_sessionCnt = GetRoomSessionsCnt();
    int i = 0;
    for (auto& room : m_sessions)
        memcpy(enterRoomResultPacket.m_otherSessionsID[i++], room.first.c_str()
            , sizeof(enterRoomResultPacket.m_otherSessionsID[i++]));
    sessionSP->Send(&enterRoomResultPacket);
    return m_roomState;
}

ROOM_STATE Room::Exit(char* id, shared_ptr<Session> session)
{
    lock_guard<mutex> lock(m_roomMutex);

    if (m_sessions.find(id) == m_sessions.end())
        return m_roomState;
    m_sessions.erase(id);

    CheckRoomState();

    return m_roomState;
}

bool Room::isRoomEmpty()
{
    if (m_roomState == ROOM_STATE::EMPTY) 
        return true;
    return false;
}

ROOM_STATE Room::GetRoomState()
{
    return m_roomState;
}

char* Room::GetRoomName()
{
    return m_roomName;
}

int Room::GetRoomSessionsCnt()
{
    return m_sessions.size();
}
