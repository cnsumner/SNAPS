#include "parser.hpp"

#include <stdlib.h>

Parser::Parser(string filename)
{
    ifstream file(filename);

    if (file.is_open())
    {
	for (string s; getline(file, s);)
	{
	    _instructions.push_back(s);
	}
    }
}

bool Parser::ok()
{
    return (_instructions.size() > 0 ? true : false);
}

int Parser::parse(Program &program)
{
    int err = 0;
    int count = 0;

    for (auto instr : _instructions)
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
			Instruction instruction = {tokens[0], encode(tokens[0]), strtol(tokens[1].c_str(), NULL, 16)};
			program._instructions.push_back(instruction);
		}
		else
		{
			err = -1;
			break;
		}
    }

    return err;
}

int Parser::encode(string mnemonic)
{
    for (auto &c : mnemonic) c = toupper(c);

    int opcode = 100; //if we ever see opcode 100 elsewhere, we have problems

    if (mnemonic == "LOAD")
	opcode = 0x00;
    else if (mnemonic == "LOADI")
	opcode = 0x01;
    else if (mnemonic == "STORE")
	opcode = 0x02;
    else if (mnemonic == "STOREI")
	opcode = 0x03;
    else if (mnemonic == "ADD")
	opcode = 0x04;
    else if (mnemonic == "ADDI")
	opcode = 0x05;
    else if (mnemonic == "AND")
	opcode = 0x06;
    else if (mnemonic == "OR")
	opcode = 0x07;
    else if (mnemonic == "NOT")
	opcode = 0x08;
    else if (mnemonic == "XOR")
	opcode = 0x09;
    else if (mnemonic == "JUMP")
	opcode = 0x0A;
    else if (mnemonic == "BZERO")
	opcode = 0x0B;
    else if (mnemonic == "SEQ")
	opcode = 0x0C;
    else if (mnemonic == "SNE")
	opcode = 0x0D;
    else if (mnemonic == "SGT")
	opcode = 0x0E;
    else if (mnemonic == "SLT")
	opcode = 0x0F;
    else if (mnemonic == "SGE")
	opcode = 0x10;
    else if (mnemonic == "SLE")
	opcode = 0x11;
    else if (mnemonic == "PUSH")
	opcode = 0x12;
    else if (mnemonic == "POP")
	opcode = 0x13;
    else if (mnemonic == "CALL")
	opcode = 0x14;
    else if (mnemonic == "RET")
	opcode = 0x15;

    return opcode;
}