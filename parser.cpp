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

bool Parser::Ok()
{
    return (instructions.size() > 0 ? true : false);
}

int Parser::Parse()
{
    int err = 0;

    for (auto instr : instructions)
    {
		size_t size = instr.size();
		for (size_t i = 0; i < size;)
		{
			size_t spacePos = instr.find(' ', i);
			if (spacePos == string::npos)
			{
				if (i < size - 1)
				{
					spacePos = size;
				} else
				{
					err = -1;
					break;
				}
			}

			string token = instr.substr(i, spacePos - i);

			

			i = spacePos + 1;
		}
    }

    return err;
}