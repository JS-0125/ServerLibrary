#pragma once
#include<queue>
#include<Session.h>

class EventQueue
{
	queue<shared_ptr<Session>> q;
public:
	void Enqueue(shared_ptr<Session>);
	int Count();
};

