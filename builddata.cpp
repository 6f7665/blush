#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>

#include "webpageclass.h"

using namespace std;
namespace fs = std::filesystem;

int Webpage::BuildData(string &Filename, string &Title, string &Category, string &SubCategory, string &Tags, string &Destination)
{

	ofstream o;

//------------- Generate files from entries

	if(Category.length() != 0)
	{
		string currentfilename = "gen/";
		cout << "\tCategory is: " << Category << "\n";
		currentfilename.append(Category);
		currentfilename.append(".cat");
		o.open(currentfilename, std::ios_base::app);
		o << "<a href=\"" << Destination << "\">" << Title << "</a>" << endl;
		o.close();
	}
	if(SubCategory.length() != 0)
	{
		string currentfilename = "gen/";
		cout << "\tSubCategory is: " << SubCategory << "\n";
		currentfilename.append(SubCategory);
		currentfilename.append(".sub");
		o.open(currentfilename, std::ios_base::app);
		o << "<a href=\"" << Destination << "\">" << Title << "</a><br>" << endl;
		o.close();
	}
	cout << "Tags are: " << Tags << "\n";

	if(Tags.length() != 0)
	{
		size_t commapos;
		string currentstring = Tags;
		while(currentstring.length() != 0 )
		{
			string currentfilename = "gen/";
			commapos = currentstring.find(",");
			if( commapos == std::string::npos )
			{
				commapos = currentstring.back();
			}

			currentfilename.append(currentstring, 0, commapos);
			currentstring.erase(0, commapos+1);

			currentfilename.append(".tag");

			cout << currentfilename << "\n";

			o.open(currentfilename, std::ios_base::app);
			o << "<a href=\"" << Destination << "\">" << Title << "</a>" << endl;
			o.close();
		}
	}
//	ifstream file;
//	file.open(Category, ios::out);
//	if (!filetoscan)
//	{
//		cout << "ERROR: File: " << Filename << "couldn't be opened\n";
//		return 1;
//	}
	return 0;
}
