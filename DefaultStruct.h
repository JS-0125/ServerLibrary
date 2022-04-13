#pragma once
#include"defaultHeader.h"

enum class OBJECT_STATE { OBJST_FREE, OBJST_CONNECTED, OBJST_INGAME };

struct Server_Detail {
	int server_id;
	string server_ip;
	int server_port;
	int network_protocol;
};