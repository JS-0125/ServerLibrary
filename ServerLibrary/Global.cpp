#include "pch.h"
#include "global.h"

ObjectPool<EX_OVER_IO> exoverIoPool(50000);
SessionFunction packetHandlerTable[MAX_PACKET_TYPE] = {};