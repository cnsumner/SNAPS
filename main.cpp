/* Instruction set (22 instructions)

#	0b			0x		Instr.	Arg.	Description.
-----------------------------------------------------------
0	0b00000		0x00	LOAD 	addr
1	0b00001		0x01	LOADI 	addr
2	0b00010		0x02	STORE 	addr
3	0b00011		0x03	STOREI 	addr
4	0b00100		0x04	ADD 	addr
5	0b00101		0x05	ADDI 	const
6	0b00110		0x06	AND 	addr
7	0b00111		0x07	OR 		addr
8	0b01000		0x08	NOT
9	0b01001		0x09	XOR 	addr
10	0b01010		0x0A	JUMP 	const
11	0b01011		0x0B	BZERO	addr
12	0b01100		0x0C	SEQ		addr
13	0b01101		0x0D	SNE		addr
14	0b01110		0x0E	SGT		addr
15	0b01111		0x0F	SLT		addr
16	0b10000		0x10	SGE		addr
17	0b10001		0x11	SLE		addr
18	0b10010		0x12	PUSH
19	0b10011		0x13	POP
20	0b10100		0x14	CALL	addr
21	0b10101		0x15	RET
-----------------------------------------------------------

Instruction anatomy (bits)
-------------------------
[opcode(5)][Arguments(27)]

Processor anatomy
-------------------------
Program Counter (PC) 	32 bits
Accumulator				32 bits
Memory					(32 bits)*(2^32) = 137,438,953,472 bits = 17,179,869,184 bytes = 17 MB

*/

#include <iostream>
#include <string>

#include "parser.hpp"

using std::cout;
using std::endl;
using std::string;

int main(int argc, char *argv[])
{
	if (argc <= 1)
	{
		cout << "Please specify mode (-assemble or -run) and input file.\n";
		cout << "EXAMPLE: snaps -assemble test.asm" << endl << endl;
		return 0;
	}

	string flag;
	string filename;

	if (argc == 3)
	{
		flag = argv[1];
		filename = argv[2];
	} else 
	{
		cout << "Please specify mode (-assemble or -run) and input file.\n";
		cout << "EXAMPLE: snaps -assemble test.asm" << endl << endl;
		return 0;
	}

	if (flag == "-assemble")
	{
		Program *prog = nullptr;
		Parser p = Parser(filename, prog);

        if (p.ok())
		{
            int err = p.parse();

			if (err == 0)
			{
				//execute program
				//eventually save file;
			}
		}
	}




}