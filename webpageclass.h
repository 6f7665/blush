#include <string>

using namespace std;

class Webpage
{
	public:

	int num;
	string Filename;
	string Title;
	string Category;
	string SubCategory;
	string Tags;
	string Destination;
	
	int ScanPage(string &Filename, string &Title, string &Category, string &SubCategory, string &Tags);
//	int AddToMenu( char &Destination );
//      void ConvertPage( char &Filename, char &Destination );
};
