#pragma once


using namespace std;

class Session;

struct TIMER_EVENT {
	shared_ptr<Session> m_eventOwner;
	function<void()> m_task;
	chrono::system_clock::time_point m_startTime;
	constexpr bool operator < (const TIMER_EVENT& L) const
	{
		return (m_startTime > L.m_startTime);
	}
};


class Timer
{
private:
	priority_queue<TIMER_EVENT> m_timerQueue;
	mutex m_timerLock;
public:
	void AddEvent(shared_ptr<Session>, function<void()>, int delay_ms);
	void DoTimer();
};