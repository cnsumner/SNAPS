#pragma once

#include <fstream>
#include <utility>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::ifstream;
class Parser
{
    vector<string> instructions;

  public:
    Parser(string filename);
	bool Ok();
    int Parse();

  private:
};