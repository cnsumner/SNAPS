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
11	0b01011		0x0B	BZERO	const
12	0b01100		0x0C	SEQ		addr
13	0b01101		0x0D	SNE		addr
14	0b01110		0x0E	SGT		addr
15	0b01111		0x0F	SLT		addr
16	0b10000		0x10	SGE		addr
17	0b10001		0x11	SLE		addr
18	0b10010		0x12	PUSH
19	0b10011		0x13	POP
20	0b10100		0x14	CALL	const
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
#include "processor.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::string;

int main(int argc, char *argv[])
{
	bool debug = false;
	if (argc != 2 && argc != 3)
	{
		cout << "Incorrect arguments. Please specify input file. Optionally specify debug mode.\n";
		cout << "EXAMPLE: snaps test.asm" << endl << endl;
		cout << "EXAMPLE: snaps test.asm true" << endl << endl;
		return 0;
	}

	if (argc == 3)
	{
		string d = argv[2];
		if (d == "true")
			debug = true;
	}

	string filename = argv[1];

	Parser p = Parser(filename);

	if (p.ok())
	{
		Program prog = Program();
		
		int err = p.parse(prog);

		if (err == 0)
		{
			Processor proc = Processor(prog);
			proc.info();
			cout << endl;

			int run = 1;
			
			while (!proc.complete())
			{
				proc.step();
				if (debug)
				{
					run--;
					proc.info();
					cout << endl;
					cout << "Press enter to step once, or enter a number to step that many times..." << endl;
				}

				if (run < 1 && debug)
				{
					run = 1;
					string s;
					getline(cin, s);
					if (s.size() > 0)
						run = atoi(s.c_str());
				}
			}

			proc.info();
		}
	} else
	{
		cout << "Error opening file." << endl;
	}
}