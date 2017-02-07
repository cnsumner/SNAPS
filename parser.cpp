#include "parser.hpp"

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

Parser::ok()
{
	return (instructions.size() > 0 ? true : false);
}