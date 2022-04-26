#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>

//namespaces
using namespace std;

int main(int argc, char** argv)
{
	if( argc != 3 )
	{
		cout << "ERROR: wrong number of arguments,\n Syntax: <filename> <argument>\n";
		return 1;
	}
	
	//args comes as filename, destination
	
	string Filename = argv[1]; //assign these to variables to make it less confusing
	string Destination = argv[2];


	cout << "Filename/Destination is: " << Filename << "/" << Destination << "\n";
	return 0;
}
