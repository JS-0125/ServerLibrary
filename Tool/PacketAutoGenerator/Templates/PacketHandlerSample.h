{%- for packet in parser.total_packets %}
	{%- if parser.handlers.count(packet.name) == 0 %}

PACKET_HANDLER({{packet.name}})
{
	cout << "PACKET: {{packet.name}}" << endl;
	STRUCT_{{packet.name}} recvPacket;
	sessionSP->GetPacket(recvPacket);
}
	{%- endif %}
{%- endfor %}