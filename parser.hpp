#pragma once

#include <fstream>
#include <utility>
#include <string>
#include <vector>

#include "program.hpp"

using std::string;
using std::vector;
using std::ifstream;
class Parser
{
public:
  Parser(string filename, Program *&program);
  bool ok();
  int parse();

private:
  vector<string> instructions;
  Program *_program;

  int encode(string opcode, string param);
};