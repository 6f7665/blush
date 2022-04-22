#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>

//self coded functions and classes
#include "scanpage.h"
#include "webpageclass.h"

using namespace std; //kokplattan finns på riktigt!!!
namespace fs = std::filesystem;

//int ScanPage(string &Filename, string &Title, string &Category, string &SubCategory, string &Tags);

int main(int argc, char** argv)
{
	if( argc == 1 )
	{
		cout << "ERROR: missing argument\n";
		return 1;
	}


	//runtime settings
	string destinationfolder = "html/";
	string foldername;
	string flagF = "-f";
	string flagS = "-s";
	int foldermode = 0;
	int singlemode = 0;

	//initialize string array for pages to process
	string pagepath[32767];

//-------------	Get arguments from commandline

	int a;

	for( a = 1; a != argc; a++ )
	{
		if (flagF.compare(argv[a]) == 0)
		{
			foldermode = 1;
			a++;
			cout << "DEBUG: flagF: " << a << "/" << argc << argv[a] << "\n";
			foldername.assign(argv[a]);
		}
		else if (flagS.compare(argv[a]) == 0)
		{
			singlemode = 1;
			a++;
			cout << "DEBUG: flagS: " << a << "/" << argc << argv[a] << "\n";
			pagepath[1].assign(argv[a]);
		}
		else
		{
			cout << "ERROR: uknown arg " << a << " / " << argc << argv[a] << "\n";
			return 1;
		}
	}
	if((singlemode == 1) && (foldermode == 1))
	{
		cout << "ERROR, can't run single and folder at the same time\n";
		return 1;
	}


//-------------	Check amount of pages to process

	int numofpages = 0;
	if(singlemode == 1)
	{
		numofpages = 1;
	}
	else if(foldermode == 1)
	{
		std::string path;
		path.assign(foldername);
		for (const auto & entry : fs::directory_iterator(path))
		{
			std::cout << entry.path() << std::endl;
			numofpages++;
			pagepath[numofpages].assign(entry.path());
//			pagepath[numofpages].erase(0,1);
//			pagepath[numofpages].resize( pagepath[numofpages].size()-1 );
		}
	}

	cout << "The number of pages are: " << numofpages << "\n";
	
	int x;

//	for( x = numofpages; x != 0; --x )
//	{
//		cout << pagepath[x];
//	}

//-------------	Iterate over all pages to process and process them

	int interrupt = 0;
	
	x = numofpages;
	while( x != 0 )
	{

	//-------------	Create page object, assign variables and call functions

		Webpage Page[x];
		Page[x].Filename.assign(pagepath[x]);
//		Page[x].Destination.assign(destinationfolder);
//		Page[x].Destination.append(Page[x].Filename);

//		cout << "DEBUG: filedest: " << Page[x].Destination << "\n";

		if(Page[x].ScanPage(Page[x].Filename, Page[x].Title, Page[x].Category, Page[x].SubCategory, Page[x].Tags) != 0) { interrupt = 1; }
		//if()
		cout << "DEBUG: title: " << Page[x].Title << "\n";
		//if((interrupt = 0) && ())
		
		--x;
	}
	return 0;
}
