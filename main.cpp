#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <stdlib.h>

//self coded functions and classes
#include "scanpage.h"
#include "builddata.h"
#include "webpageclass.h"

//namespaces
using namespace std; //kokplattan finns på riktigt!!!
namespace fs = std::filesystem;

int main(int argc, char** argv)
{
	if( argc == 1 )
	{
		cout << "ERROR: missing argument\n";
		return 1;
	}

	//runtime settings
	string destinationfolder = "html/";
	string foldername = "";

	string flagF = "-f";
	string flagS = "-s";
	string flagI = "-i";

	int foldermode = 0;
	int singlemode = 0;
	int indexmode = 0; //index off by default

	//initialize string array for pages to process
	string pagepath[32767];

//-------------	Get arguments from impcommandline

	int a;

	for( a = 1; a != argc; a++ )
	{
		if (flagF.compare(argv[a]) == 0)
		{
			foldermode = 1;
			a++;
			foldername.assign(argv[a]);
		}
		else if (flagS.compare(argv[a]) == 0)
		{
			singlemode = 1;
			a++;
			pagepath[1].assign(argv[a]);
		}
		else if (flagI.compare(argv[a]) == 0)
		{
			indexmode = 1;
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

//------------- Check configuration file

	ifstream Config;
	string ConfigLine;
	Config.open("~/.config/cshg/config");
	cout << "open config file" << endl;
	while(getline(Config, ConfigLine))
	{
		cout << ConfigLine << endl;
	}
	Config.close();
	cout << "close config file" << endl;


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
			//std::cout << entry.path() << std::endl;
			pagepath[numofpages].assign(entry.path());
			numofpages++;
		}
	}
	
//-------------	Iterate over all pages to scan and process them

	vector<Webpage*> pv;

	for( int x = 0; x < numofpages; x++)
	{
		Webpage *PageObj = new Webpage;
		PageObj->num = x;
		PageObj->Filename = pagepath[x];
		PageObj->Destination = pagepath[x];
		pv.push_back(PageObj);

		size_t pos;
		pos = pv[x]->Destination.rfind(".md");
		if( pos != std::string::npos )
		{
			pv[x]->Destination.erase(pos, pv[x]->Destination.size()-pos);
		}
		pos = pv[x]->Destination.rfind(".txt");
		if( pos != std::string::npos )
		{
			pv[x]->Destination.erase(pos, pv[x]->Destination.size()-pos);
		}
		pos = pv[x]->Destination.find(foldername);
		if( pos != std::string::npos )
		{
			pv[x]->Destination.erase(0, foldername.length()+pos);
		}
		pv[x]->Destination.append(".html");
	}

	if( indexmode == 1 )
	{

	//-------------	Flush old data
		
		fs::remove_all("gen");
		fs::create_directory("gen");

	//-------------	Iterate over files and create new data

		for( int x = 0; x < pv.size(); x++ )
		{

		//------------- Scan the page with references so it can return the data into the object

			pv[x]->ScanPage(pv[x]->Filename, pv[x]->Title, pv[x]->Category, pv[x]->SubCategory, pv[x]->Tags);	

		//------------- Create files from scanned data

			pv[x]->BuildData(pv[x]->Filename, pv[x]->Title, pv[x]->Category, pv[x]->SubCategory, pv[x]->Tags, pv[x]->Destination);
		}
	}

	for( int x = 0; x < pv.size(); x++ )
	{
		pv[x]->CallGenerate(pv[x]->Filename, pv[x]->Destination); 
	}

	return 0;
}

void Webpage::CallGenerate(string &Filename, string &Destination)
{
	string destinationfolder = "html/";

	string Tempfile = "gen/";
	Tempfile.append(Filename, Filename.find("/")+1, Filename.rfind(".")-1);
	Tempfile.append(".temp");

	string impcommand = "~/./cshg/cshg-imp ";
	impcommand.append(Filename);
	impcommand.append(" ");
	impcommand.append(Tempfile);
	//cout << impcommand << endl;
	std::system((impcommand.c_str()));
	
	string mdcommand = "~/./cshg/cshg-md ";
	mdcommand.append(Tempfile);
	mdcommand.append(" > ");
	mdcommand.append(destinationfolder);
	mdcommand.append(Destination);
	//cout << mdcommand << endl;
	std::system((mdcommand.c_str()));

	std::system("cp gen/*.html html/");
}
