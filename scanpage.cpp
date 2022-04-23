#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>

#include "webpageclass.h"

using namespace std;

int Webpage::ScanPage(string &Filename, string &Title, string &Category, string &SubCategory, string &Tags)
{
	ifstream filetoscan;
	filetoscan.open(Filename, ios::out);
	if (!filetoscan)
	{
		cout << "ERROR: File: " << Filename << "couldn't be opened\n";
		return 1;
	}

	cout << "DEBUG: Reading file: " << Filename << "\n";

	string line;
	string typeofdef;
	string definition;

	while(getline(filetoscan, line))
	{
		size_t exclaim = line.find("!");
		size_t colon = line.find(":");
		size_t lastcolon = line.rfind(":");
		if ((exclaim!=string::npos) && (colon!=string::npos))
		{
			lastcolon--;
			typeofdef.assign(line,exclaim+1,colon-1);
			definition.assign(line,colon+1,lastcolon-1);
		//debug	cout << line << "\n";
		//debug	cout << typeofdef << "\n";

			if(typeofdef == "cat")
			{
				Category = definition;
			}
			if(typeofdef == "sub")
			{
				SubCategory = definition;
			}
			if(typeofdef == "tag")
			{
				Tags = definition;
			}
			if(typeofdef == "title")
			{
				Title = definition;
			}
			if(typeofdef == "start")
			{
				return 0;
			}
		}
	}
	cout << "WARNING: File: " << Filename << "has no !start: command\n";
	return 0;
}
