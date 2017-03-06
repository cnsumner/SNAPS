#pragma once

#include <vector>
using std::vector;
#include <string>
using std::string;

struct Instruction
{
  string mnemonic;
  int opcode;
  int param;
};

class Program
{
  public:
    vector<Instruction> _instructions;
    vector<int> _dataMemory;

    Program();
};