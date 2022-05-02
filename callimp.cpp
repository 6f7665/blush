#include <string>
#include <iostream>
#include <cstdlib>
//#include <fstream>

#include "webpageclass.h"

//namespace
using namespace std;

void Webpage::callimp(string &Filename)
{
	string Tempfile = "gen/";
	Tempfile.append(Filename, Filename.find("/")+1, Filename.rfind(".")-1);
	Tempfile.append(".temp");
	string command = "./imp ";
	command.append(Filename + " " + Tempfile);
	cout << command << endl;
	system(command);
}
