#include"Timer.h"

void Timer::AddEvent(shared_ptr<Session> event_owner, function<void()> task, int delay_ms)
{
	TIMER_EVENT ev;
	ev.m_eventOwner = event_owner;
	ev.m_task = task;
	ev.m_startTime = chrono::system_clock::now() + chrono::milliseconds(delay_ms);

	m_timerLock.lock();
	m_timerQueue.push(ev);
	m_timerLock.unlock();
}

void Timer::DoTimer()
{
	while (1) {
		m_timerLock.lock();
		if ((false == m_timerQueue.empty())
			&& (m_timerQueue.top().m_startTime <= chrono::system_clock::now())) {
			TIMER_EVENT ev = m_timerQueue.top();
			m_timerQueue.pop();
			m_timerLock.unlock();

			ev.m_task();
		}
		else {
			m_timerLock.unlock();
			this_thread::sleep_for(10ms);
		}
	}
}
