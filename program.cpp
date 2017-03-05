#include "program.hpp"

Program::Program()
{
	_instrCount = 0;
	_instructions = nullptr;
}

Program::Program(int instrCount)
{
	_instrCount = instrCount;
	_instructions = new int[instrCount*sizeof(int)];
	_dataMemory = new int[100*sizeof(int)];
}