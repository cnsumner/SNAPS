#pragma once

#include "program.hpp"

class Processor
{
public:
  Processor(Program *program);
  void step();
  void info();

private:
  unsigned int PC;       //program counter
  unsigned int stackPtr; //stack pointer register
  int accumulator;       //accumulator register
  Program *_program;

  void execute();
};