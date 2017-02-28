#pragma once

class Processor
{
  public:
  	Processor(int* instrMemory);
	
  private:
    unsigned int PC; //program counter
	unsigned int stackPtr; //stack pointer register
    int accumulator; //accumulator register
    int *instrMemory; //instruction memory
    void *dataMemory; //data memory

};