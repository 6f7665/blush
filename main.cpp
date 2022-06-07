#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <regex>
#include <stdlib.h>

//self coded functions and classes
#include "scanpage.h"
#include "builddata.h"
#include "webpageclass.h"
#include "commandtostring.h"
#include "importsequenceclass.h"

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

	string flagF = "-d";
	string flagS = "-s";
	string flagI = "-i";

	int foldermode = 0;
	int singlemode = 0;
	int indexmode = 0; //index off by default

	//initialize string array for pages to process
	string pagepath[32767];

//------------- Check configuration file

	ifstream Config;
	string ConfigLine;
	string HomeDir = "/home/";
	string UID = "id -nu $uid";
	if( CommandToString( UID, HomeDir ) != 0 )
	{
		cout << "WARNING: No user id found" << endl;
	}
	HomeDir.erase(HomeDir.find("\n"), HomeDir.length()-HomeDir.find("\n"));
	HomeDir.append("/.config/cshg/config");
	Config.open( HomeDir.c_str() );
	if( !Config )
	{
		cout << "NOTE: No Config file found at: " << HomeDir << endl;
	}
	while(getline(Config, ConfigLine))
	{
		size_t hashtagpos = ConfigLine.find("#");
		if( hashtagpos != string::npos )
		{
			ConfigLine.erase(hashtagpos, ConfigLine.length()-hashtagpos);
		}
		if( ConfigLine.find(":") != string::npos )
		{
			cout << ConfigLine << "\n";
		}
		else if( ConfigLine.find(" {") != string::npos )
		{
		//------------- Get the type of import sequence
			string importsequencetype;
			importsequencetype.assign(ConfigLine, 0, ConfigLine.find(" {"));
			cout << "importsequencetype: " << importsequencetype << "\n";
		//-------------	Get the contents between the curly braces
			string importfiles = "";
			ConfigLine.erase( 0, ConfigLine.find("{") );
			while(ConfigLine.find("}") == string::npos )
			{
				importfiles.append(ConfigLine);
				if( !getline(Config, ConfigLine) ){ break; }
			}
			importfiles.append(ConfigLine);
		//-------------- Clean up using regex to "file:command,file2:command2" format
			regex cleanstringregex ("[{|}| |\t]");
			importfiles = regex_replace(importfiles,cleanstringregex,"");
			cout << importfiles << "\n";
		//-------------- Create object for import sequence
			if(importsequencetype == "imp")
			{
				ImportSequence imp;
				imp.init(importfiles);
			}
			if(importsequencetype == "impcat")
			{
				ImportSequence impcat;
				impcat.init(importfiles);
			}
			if(importsequencetype == "impsub")
			{
				ImportSequence impsub;
				impsub.init(importfiles);
			}
			if(importsequencetype == "imptag")
			{
				ImportSequence imptag;
				imptag.init(importfiles);
			}
			if(importsequencetype == "impblog")
			{
				ImportSequence impblog;
				impblog.init(importfiles);
			}
		}
	}
	Config.close();

//-------------	Get arguments from commandline

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
