#pragma once
#include"ObjectPool.h"
#include"macro.h"

class EX_OVER_IO;

extern ObjectPool<EX_OVER_IO> exoverIoPool;

class Session;
typedef void(*SessionFunction)(shared_ptr<Session>);
extern SessionFunction packetHandlerTable[MAX_PACKET_TYPE];
