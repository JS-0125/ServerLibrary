#pragma once
class Network 
{
private:
	virtual int Init() = 0;
	virtual int StartAccept() = 0;
	virtual int Disconnect(SOCKET& socket) = 0;
};