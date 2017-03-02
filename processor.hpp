#pragma once

#include "program.hpp"

class Processor
{
public:
  Processor(Program *program);
  void step();

private:
  unsigned int PC;       //program counter
  unsigned int stackPtr; //stack pointer register
  int accumulator;       //accumulator register
  Program *_program;
  int *_dataMemory; //data memory

  void execute();
};