#include "program.hpp"

Program::Program()
{
	_instructions = vector<Instruction>();
	_dataMemory = vector<int>(4096);
	_endOfMemory = 0;
	_labels = map<string, int>();
}