#include "parser.hpp"

#include <regex>

using std::regex;
using std::regex_match;
using std::ssub_match;
using std::smatch;

Parser::Parser(string filename)
{
    ifstream file(filename);

    if (file.is_open())
    {
	for (string s; getline(file, s);)
	{
	    instructions.push_back(s);
	}
    }
}

bool Parser::Ok()
{
    return (instructions.size() > 0 ? true : false);
}

int Parser::Parse()
{
    regex token_regex("(\\S+)\\s?", std::regex::ECMAScript);
    smatch token_matches;
    int err = 0;
    for (auto instr : instructions)
    {
		auto r = regex_match(instr, token_matches, token_regex);
	if (regex_match(instr, token_matches, token_regex))
	{
		ssub_match match = token_matches[0];
		string token = match.str();
	}
	else
	{
	    err = -1;
	    break;
	}
    }

    return err;
}