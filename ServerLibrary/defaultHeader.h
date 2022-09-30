#pragma once
#include <WS2tcpip.h>
#include <MSWSock.h>
#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
#include <array>
#include <mutex>
#include<queue>
#include <chrono>
#include<string>
#include <functional>
#include<memory>
#include<map>
#include<algorithm>


#include"Exception.h"

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "MSWSock.lib")

using namespace std;


#include"Exception.h"
#include"Network.h"
#include"Session.h"
#include"Timer.h"
#include"TimerEvent.h"
#include"ObjectPool.h"
#include"RingBuffer.h"
#include"Global.h"

// IOCP
#include"IOCP.h"

