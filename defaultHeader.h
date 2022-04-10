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

#include"Exception.h"

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "MSWSock.lib")

using namespace std;

#define SERVER_ID  0
#define MAX_BUFFER  1024
#define SERVER_PORT	49152
#define MAX_PACKET_TYPE 1024
