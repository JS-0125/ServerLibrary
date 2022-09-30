#pragma once
#include"MatchManager.h"
#include"LoginManager.h"

class MasterManager
{
public:
	LoginManager loginManager;
	MatchManager matchManager;
	Timer timer;
	ObjectPool<TIMER_EVENT> timerEventPool;
	MasterManager() {
		timerEventPool.Init(10);
	}
};

static MasterManager masterManager;