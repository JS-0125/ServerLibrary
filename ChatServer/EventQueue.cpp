#include "pch.h"
#include "EventQueue.h"


void EventQueue::Enqueue(shared_ptr<Session> session)
{
	q.push(session);
}

int EventQueue::Count()
{
	return q.size();
}

thread_local EventQueue eventQueue;