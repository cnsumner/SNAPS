#pragma once

#include "program.hpp"

class Processor
{
public:
  Processor(Program &program);
  void step();
  void info();
  bool complete();

private:
  bool complete_;
  unsigned int PC;       //program counter
  unsigned int stackPtr; //stack pointer register
  unsigned int cycleCount;
  int accumulator;       //accumulator register
  vector<int> stack;
  Program _program;

  void execute();
};