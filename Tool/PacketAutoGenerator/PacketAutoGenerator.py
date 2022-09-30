import argparse
import jinja2
import Parser

def main():
    
    # jinja2 템플릿 엔진
    file_loader = jinja2.FileSystemLoader('Templates')
    env = jinja2.Environment(loader = file_loader)

    argParser = argparse.ArgumentParser(description = 'PacketAutoGenerator')
    argParser.add_argument('--path', type = str, default ='D:/document/Code/ServerLibrary/ChatServer/temp.txt',help ='path')
    argParser.add_argument('--output', type = str, default ='PacketType',help ='output file')
    argParser.add_argument('--recv', type = str, default ='CS_',help ='recv prefix')
    argParser.add_argument('--send', type = str, default ='SC_',help ='send prefix')
    arguments = argParser.parse_args();

    # PacketType
    parser = Parser.Parser(1000, arguments.recv, arguments.send)
    parser.parsePacket(arguments.path)

    template = env.get_template('PacketTypeSample.h')
    output = template.render(parser = parser, output=arguments.output)

    f = open(arguments.output+'.h', 'w+')
    f.write(output)
    f.close()

    # PacketStruct
    arguments.path = 'PacketStruct.h';
    arguments.output = 'PacketStruct';

    #parser = Parser.Parser(1000, arguments.recv, arguments.send)
    prevFileLines = parser.parseStruct(arguments.path)
    #for packet in parser.structs:
    #    print('struct name : ' +  packet)
    #for packet in parser.total_packets:
    #    print(parser.structs.count('STRUCT_'+packet.name))
    #    print(packet.name)

    template = env.get_template('PacketStructSample.h')
    output = template.render(parser = parser, output=arguments.output)

    f = open(arguments.output+'.h', 'w+')
    for line in prevFileLines:
        f.write(line)

    f.write(output)
    f.close()

    # PacketHandler
    arguments.path = 'PacketHandler.h';
    arguments.output = 'PacketHandler';

    #parser = Parser.Parser(1000, arguments.recv, arguments.send)
    prevFileLines = parser.parseHandler(arguments.path)
    template = env.get_template('PacketHandlerSample.h')
    output = template.render(parser = parser, output=arguments.output)

    f = open(arguments.output+'.h', 'w+')
    for line in prevFileLines:
        f.write(line)

    f.write(output)
    f.close()

    return

if __name__ == '__main__':
    main()