#include"pch.h"
#include "LoginManager.h"
#include "PacketType.h"
#include"PacketStructs.h"

bool LoginManager::Login(char* id, shared_ptr<Session> sessionSP)
{
    cout << id << endl;
    cout << "m_loginSessions size - " << m_loginSessions.size() << endl;
    STRUCT_SC_LOGIN_RESULT loginresultPacket;
    // �α��� ����
    if (m_loginSessions.find(id) == m_loginSessions.end()) {
        cout << "�α��� ����" << endl;
        m_loginSessions[id] = sessionSP;
        memcpy(loginresultPacket.m_id, id, sizeof(loginresultPacket.m_id));
        loginresultPacket.m_result = true;
        sessionSP->Send(&loginresultPacket);
        return true;
    }
    // �α��� ����
    cout << "�α��� ���� - "<< (*m_loginSessions.find(id)).first << endl;
    cout << "m_loginSessions size - " << m_loginSessions.size() << endl;
    cout << "??????" << endl;
    loginresultPacket.m_result = false;
    sessionSP->Send(&loginresultPacket);
    return false;
}

bool LoginManager::Logout(char* id, shared_ptr<Session> session)
{
    if (m_loginSessions.find(id) != m_loginSessions.end()) {
        m_loginSessions.erase(id);
        return true;
    }
    return false;
}
