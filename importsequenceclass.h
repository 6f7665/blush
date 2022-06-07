#include <string>

using namespace std;

class ImportSequence
{
	public:
	vector<string> impvtr;
	int vtrsize = 0;

	void init(string &scannedstr)
	{
		int prevpos = 0;
		string item;
		for( int i = 0; i <= scannedstr.length(); i++ )
		{
			if( scannedstr[i] == ',' )
			{
				item.assign(scannedstr, prevpos, i-prevpos);
				prevpos = i;
				impvtr.push_back(item);
			}
		}
	}
};
