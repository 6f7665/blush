#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>
//#include <vector>

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

	ifstream i; //input
	ifstream i2; //input 2, imported file
	ofstream o; //output

	i.open(argv[1], ios::out);
	o.open(argv[2]);

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
		o << line;
	}
	i2.close();

	i2.open("materials/menu");
	while(getline(i2, line))
	{
		o << line;
	}
	i2.close();
	
	i2.open("materials/closemenu");
	while(getline(i2, line))
	{
		o << line;
	}
	i2.close();

	while(getline(i, line))
	{
		size_t pos;
		pos = line.find("!");
		if( pos == 0 )
		{
			impfile.assign("gen/");
			impfile.append(line, line.find(":")+1, line.rfind(":")-1);

			command.assign(line, 1, line.find(":")-1);

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
		else
		{

			o << line << endl;
		}
	}

	i2.open("materials/footer");
	while(getline(i2, line))
	{
		o << line;
	}
	i2.close();

	//import blog entries here

	return 0;
}
