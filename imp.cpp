#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <algorithm>

//namespaces
using namespace std;
namespace fs = std::filesystem;

int main(int argc, char** argv)
{
	if( argc != 3 )
	{
		cout << "ERROR: wrong number of arguments,\n Syntax: <filename> <argument>\n";
		return 1;
	}

	//args comes as filename, destination

	ifstream i; //input
	ifstream i2; //input 2, imported file
	ofstream o; //output

	i.open(argv[1], ios::out);
	o.open(argv[2]);

	int blogstatus = 0;
	string blogfolder[16];
	string line;
	string command;
	string impfile;
	string impline;

	while(line.find("!start:") == std::string::npos) //stuck in the loop til we find the start
	{
		if(!getline(i, line)) 
		{
			break; //wtf, no !start: in the file :oooo
		}
	}
	
	i2.open("materials/head");
	while(getline(i2, line))
	{
		o << line << endl;
	}
	i2.close();

	i2.open("materials/menu");
	while(getline(i2, line))
	{
		o << line << endl;
	}
	i2.close();
	
	i2.open("materials/closemenu");
	while(getline(i2, line))
	{
		o << line << endl;
	}
	i2.close();

	while(getline(i, line))
	{
		size_t pos;
		pos = line.find("!");
		if( pos == 0 )
		{
			command.assign(line, 1, line.find(":")-1);
			if (command == "impblog")
			{
				o << line << endl;
				blogfolder[0].assign(line, line.find(":")+1, line.rfind(":")-line.find(":")-1);
				blogstatus++;
			}
			else
			{
				impfile.assign("gen/");
				impfile.append(line, line.find(":")+1, line.rfind(":")-1);


				if (command == "impsub")
				{
					impfile.append(".sub");
				}
				if (command == "impcat")
				{
					impfile.append(".cat");
				}

				i2.open(impfile, ios::out);
				if(!i2)
				{
					cout << "ERROR: missing file: " << impfile << endl;
				}
				else
				{
					while(getline(i2, impline))
					{
						o << impline << endl;
					}
					i2.close();
				}
			}
		}
		else
		{

			o << line << endl;
		}
	}
	i.close();

	i2.open("materials/footer");
	while(getline(i2, line))
	{
		o << line << endl;
	}
	i2.close();
	//close main filoe since it is done

	o.close();

	//import blog entries here
	if( blogstatus != 0 )
	{
		int blogpages;
		int entriesperpage = 5;
		int numofpages;
		string blogpage[32767];
		if(blogstatus > 1)
		{
			cout << "you have more than 1 blog import on this webpage, only the first will be imported" << endl;
		}
		cout << "blog folder is: " << blogfolder[0] << endl;
	//-------------	Read blogpage dir and store filenames in array
		string dirpath;
		dirpath.assign(blogfolder[0]);
		for (const auto & entry : fs::directory_iterator(dirpath))
		{
			std::cout << entry.path() << std::endl;
			blogpage[numofpages].assign(entry.path());
			numofpages++;
		}
		sort(blogpage, blogpage+numofpages);
		blogpages = (numofpages / entriesperpage);
		if(numofpages % entriesperpage != 0){blogpages++;}
		cout << to_string(blogpages) << endl;

		string filenametogetextentionfrom;
		filenametogetextentionfrom.assign(argv[2]);
		size_t extentionstart = filenametogetextentionfrom.find(".md.temp");
		i.open(argv[2]);
		string file2[32767];
		int currententry = 0;
		int currentpage = 1;
		for( int y = 0; y < blogpages; y++)
		{
			file2[currentpage].assign(argv[2], 0, extentionstart);
			string file2destination = file2[currentpage];
			file2[currentpage].append(to_string(currentpage));
			if(currentpage != 1)
			{
				file2destination.append(to_string(currentpage));
			}
			file2destination.append(".html");

			cout << file2[currentpage] << endl;
			o.open(file2[currentpage]);
			while(getline(i, line))
			{
				if(line.find("!impblog") != string::npos)
				{
				//------------- this imports blogpages until the limit of entries per page
					while( currententry <= (entriesperpage * (currentpage)) )
					{
						ifstream i3;
						i3.open("materials/blogprefix");
						while(getline(i3, line))
						{
							o << line << endl;
						}
						i3.close();

						i3.open(blogpage[currententry]);
						while(getline(i3, line))
						{
							o << line << endl;
						}
						i3.close();

						i3.open("materials/suffix");
						while(getline(i3, line))
						{
							o << line << endl;
						}
						i3.close();

						cout << blogpage[currententry] << " imped" << endl;
						currententry++;
					}
				}
				else
				{
				      	o << line << endl;
				}
			}
			string mdcommand = "./cshg-md ";
			mdcommand.append(file2[currentpage]);
			mdcommand.append(" > ");
			mdcommand.append(file2destination);
			std::system((mdcommand.c_str()));
			currentpage++;

			o.close();
			i.clear();
			i.seekg(0);
		}
		i.close();
	}
	return 0;
}
