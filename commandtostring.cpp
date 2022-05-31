#include <iostream>
#include <stdio.h>
#include <string>
#include <stdexcept>

using namespace std;

int CommandToString( string &Command, string &Output )
{
	char buffer[128];
	FILE* pipe = popen(Command.c_str(), "r");
	if (!pipe)
	{
		return 1;
	}
	while (!feof(pipe))
	{
		if( fgets(buffer, 128, pipe) != NULL )
		{
			Output += buffer;
		}
	}
	pclose(pipe);
	return 0;
}
