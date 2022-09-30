#include "pch.h"
#include "global.h"

ObjectPool<EX_OVER_IO> exoverIoPool(10);
SessionFunction packetHandlerTable[MAX_PACKET_TYPE] = {};