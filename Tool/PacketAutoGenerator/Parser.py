class Parser():
    def __init__(self, id, cs_prefix, sc_prefix):
        self.cs_packets = []
        self.sc_packets = []
        self.total_packets = []
        self.id = id
        self.cs_prefix = cs_prefix
        self.sc_prefix = sc_prefix
        self.structs = []
        self.handlers = []


    def parsePacket(self, path):
        f = open(path, 'r')
        lines = f.readlines()

        for line in lines:
            if line.startswith('packet') == True:
                packet_name = line.split()[1].upper()
                if packet_name.startswith(self.cs_prefix):
                    self.cs_packets.append(Packet(packet_name,self.id))
                elif packet_name.startswith(self.sc_prefix):
                    self.sc_packets.append(Packet(packet_name,self.id))
                else:
                    continue
                self.total_packets.append(Packet(packet_name,self.id))
                self.id += 1

        f.close()

    def parseStruct(self, path):
        f = open(path, 'r')
        lines = f.readlines()
        for line in lines:
            if line.startswith('struct') == True:
                packet_name = line.split()[1].upper()
                if packet_name.startswith('STRUCT_'):
                    self.structs.append(packet_name)
        f.close()
        return lines

    def parseHandler(self, path):
        f = open(path, 'r')
        lines = f.readlines()
        for line in lines:
            if line.startswith('PACKET_HANDLER') == True:
               packet_name = line.split()[1].upper()
               if packet_name.startswith(self.cs_prefix) or packet_name.startswith(self.sc_prefix) :
                   self.handlers.append(packet_name)
        f.close()
        return lines



class Packet:
    def __init__(self, name, id):
        self.name = name
        self.id = id


