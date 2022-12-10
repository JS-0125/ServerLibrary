#pragma once
#include"defaultHeader.h"

#ifdef _DEBUG
#pragma comment(lib, "ServerLibrary\\Debug\\ServerLibrary.lib")
#else
#pragma comment(lib, "ServerLibrary\\Release\\ServerLibrary.lib")
#endif
//#include"../ChatServer/PacketMacro.h"
//#include"../ChatServer/PacketHandler.h"
//#include"../ChatServer/PacketStructs.h"
//#include"../ChatServer/PacketType.h"