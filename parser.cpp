#include "parser.hpp"

#include <stdlib.h>

Parser::Parser(string filename, Program *&program)
{
    ifstream file(filename);

    if (file.is_open())
    {
	for (string s; getline(file, s);)
	{
	    instructions.push_back(s);
	}
    }

    _program = new Program(instructions.size());
    program = _program;
}

bool Parser::ok()
{
    return (instructions.size() > 0 ? true : false);
}

int Parser::parse()
{
    int err = 0;
    int count = 0;

    for (auto instr : instructions)
    {
	vector<string> tokens = vector<string>();

	size_t size = instr.size();
	for (size_t i = 0; i < size;)
	{
	    size_t spacePos = instr.find(' ', i);
	    if (spacePos == string::npos)
	    {
		if (i < size - 1)
		{
		    spacePos = size;
		}
		else
		{
		    err = -1;
		    break;
		}
	    }

	    string token = instr.substr(i, spacePos - i);

	    tokens.push_back(token);

	    i = spacePos + 1;
	}

	if (tokens.size() >= 1)
	{
	    int instruction = encode(tokens[0], tokens[1]);
	    static_cast<int*>(_program->_instructions)[count] = instruction;
	}
	else
	{
	    err = -1;
	    break;
	}
    }

    return err;
}

int Parser::encode(string opcode, string param)
{
    for (auto &c : opcode)
	c = toupper(c);
    int instruction = -1;

    if (opcode == "LOAD")
	instruction = 0x00 << (31 - 5);
    else if (opcode == "LOADI")
	instruction = 0x01 << (31 - 5);
    else if (opcode == "STORE")
	instruction = 0x02 << (31 - 5);
    else if (opcode == "STOREI")
	instruction = 0x03 << (31 - 5);
    else if (opcode == "ADD")
	instruction = 0x04 << (31 - 5);
    else if (opcode == "ADDI")
	instruction = 0x05 << (31 - 5);
    else if (opcode == "AND")
	instruction = 0x06 << (31 - 5);
    else if (opcode == "OR")
	instruction = 0x07 << (31 - 5);
    else if (opcode == "NOT")
	instruction = 0x08 << (31 - 5);
    else if (opcode == "XOR")
	instruction = 0x09 << (31 - 5);
    else if (opcode == "JUMP")
	instruction = 0x0A << (31 - 5);
    else if (opcode == "BZERO")
	instruction = 0x0B << (31 - 5);
    else if (opcode == "SEQ")
	instruction = 0x0C << (31 - 5);
    else if (opcode == "SNE")
	instruction = 0x0D << (31 - 5);
    else if (opcode == "SGT")
	instruction = 0x0E << (31 - 5);
    else if (opcode == "SLT")
	instruction = 0x0F << (31 - 5);
    else if (opcode == "SGE")
	instruction = 0x10 << (31 - 5);
    else if (opcode == "SLE")
	instruction = 0x11 << (31 - 5);
    else if (opcode == "PUSH")
	instruction = 0x12 << (31 - 5);
    else if (opcode == "POP")
	instruction = 0x13 << (31 - 5);
    else if (opcode == "CALL")
	instruction = 0x14 << (31 - 5);
    else if (opcode == "RET")
	instruction = 0x15 << (31 - 5);

    if (instruction != -1)
    {
	instruction |= strtol(param.c_str(), NULL, 16);
    }

    return instruction;
}