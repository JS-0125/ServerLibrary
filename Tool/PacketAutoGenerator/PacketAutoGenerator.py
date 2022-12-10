import argparse
import jinja2
import Parser

def main():
    
    # jinja2 
    file_loader = jinja2.FileSystemLoader('Templates')
    env = jinja2.Environment(loader = file_loader)

    defaultPath = 'D:/document/Code/ServerLibrary/ChatServer/'
    argParser = argparse.ArgumentParser(description = 'PacketAutoGenerator')
    argParser.add_argument('--path', type = str, default = defaultPath + 'protocol.txt',help ='path')
    argParser.add_argument('--output', type = str, default ='PacketType',help ='output file')
    argParser.add_argument('--recv', type = str, default ='CS_',help ='recv prefix')
    argParser.add_argument('--send', type = str, default ='SC_',help ='send prefix')
    arguments = argParser.parse_args();

    parser = Parser.Parser(1000, arguments.recv, arguments.send)
    parser.parsePacket(arguments.path)

    template = env.get_template('PacketTypeSample.h')
    output = template.render(parser = parser, output=arguments.output)

    f = open(defaultPath + arguments.output +'.h', 'w+')
    f.write(output)
    f.close()

    # PacketStruct
    arguments.path = defaultPath + 'PacketStructs.h';
    arguments.output = 'PacketStructs';

    prevFileLines = parser.parseStruct(arguments.path)

    template = env.get_template('PacketStructSample.h')
    output = template.render(parser = parser, output=arguments.output)

    f = open(arguments.path, 'w+')
    for line in prevFileLines:
        f.write(line)
    f.write(output)
    f.close()

    # PacketHandler
    arguments.path = defaultPath + 'PacketHandler.h';
    arguments.output = 'PacketHandler';

    prevFileLines = parser.parseHandler(arguments.path)

    template = env.get_template('PacketHandlerSample.h')
    output = template.render(parser = parser, output=arguments.output)

    f = open(arguments.path, 'w+')
    for line in prevFileLines:
        f.write(line)
    f.write(output)
    f.close()

    return

if __name__ == '__main__':
    main()