{%- for packet in parser.total_packets%}
	{%- if parser.structs.count('STRUCT_'+ packet.name) == 0 %}
#pragma pack(push, 1)
struct STRUCT_{{packet.name}} : public PacketHeader{
	STRUCT_{{packet.name}}() {
		m_size = sizeof({{packet.name}});
		m_type = (short)PACKET_TYPE::{{packet.name}};
	}
};
#pragma pack(pop)
	{%- endif %}
{%- endfor %}
