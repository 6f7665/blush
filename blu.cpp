#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>

using namespace std; //kokplattan finns på riktigt!!!
namespace fs = std::filesystem;

int main(int argc, char** argv)
{
	if( argc == 1 )
	{
		cout << "ERROR: missing argument\n";
		return 1;
	}

	class Webpage
	{
		public:
	
			string Title;
			string Category;
			string SubCategory;
			string Tags;
			string Filename;
			string Destination;
			
//			void TellDestination(){ cout << Destination; };
//			void ScanPage( char &Filename );
//			void AddToIndex( char &Destination );
//			void ConvertPage( char &Filename, char &Destination );
	};

	//runtime settings
	string destinationfolder = "";
	string foldername;
	string flagF = "-f";
	string singlename;
	string flagS = "-s";
	int foldermode = 0;
	int singlemode = 0;

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
			singlename.assign(argv[a]);
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

	string pagepath[4096];
	int numofpages = 0;
	if(singlemode == 1)
	{
		numofpages = 1;
	}
	else if(foldermode == 1)
	{
		std::string path = "txt";
		path.assign(foldername);
		for (const auto & entry : fs::directory_iterator(path)){
		//std::cout << entry.path() << std::endl;
		numofpages++;
		pagepath[numofpages].assign(entry.path());
		}
	}

	cout << numofpages;
	cout << pagepath[numofpages];
	return 0;

//-------------	Iterate over all pages to process and process them

	for( int x = 0; x != numofpages; x++ )
	{

	//-------------	Check extention of file

	string destinationfilename;
	destinationfilename.assign(singlename);

		if (singlename.compare(singlename.size()-3,3,".md") == 0)
		{
			destinationfilename.erase (destinationfilename.end()-3, destinationfilename.end());
			destinationfilename.append(".html");
		}
		else if (singlename.compare(singlename.size()-4,4,".txt") == 0)
		{
			destinationfilename.erase (destinationfilename.end()-4, destinationfilename.end());
			destinationfilename.append(".html");
		}
		else if (singlename.compare(singlename.size()-5,5,".html") == 0)
		{
			destinationfilename.append(".html");
		}

	//-------------	Create page object, assign variables and call functions

		Webpage Page[x];
		Page[x].Filename.assign(singlename);
		Page[x].Destination.assign(destinationfolder);
		Page[x].Destination.append(destinationfilename);

		cout << "DEBUG: filedest: " << Page[x].Destination << "\n";

		return 0; //done
	}

	return 0;
}
