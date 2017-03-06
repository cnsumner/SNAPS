#include "program.hpp"

Program::Program()
{
	_instructions = vector<Instruction>();
	_dataMemory = vector<int>(128);
}