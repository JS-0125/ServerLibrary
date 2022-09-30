#pragma once

class LoginManager
{
private:
	map<string, shared_ptr<Session>> m_loginSessions;
public:
	bool Login(char*, shared_ptr<Session>);
	bool Login(shared_ptr<Session>);
	bool Logout(char*, shared_ptr<Session>);
};

