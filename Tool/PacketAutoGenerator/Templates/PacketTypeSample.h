#pragma once
#include"pch.h"

enum PACKET_TYPE
{
	{%- for packet in parser.total_packets %}
	{{packet.name}} = {{packet.id}},
	{%- endfor %}
};
