#include <cstdio>
#include <startflags.h>

class Webpage
{
	public:

		char Title[512];
		char Category[512];
		char SubCategory[512];
		char Tags[512];
		char Filename[1024];
		char Destination[1024];

		void ScanPage( char *Filename);
		void AddToIndex( char *Destination );
		void ConvertPage( char *Filename, char *Destination );
}

int main( int argc, char *argv[] )
{
	int Mode = Getstartflags( argc, argv );
	//-1 = folder
	//-2 = single
	//-4 = noindex
	//-3 = single + index


	int NumOfPages = 1; //check contents of folder from arguments here

	Webpage* WebpageObj = new Webpage[NumOfPages];
	
	int running = 1;

	while (running == 1)
	{
		for (int CurrentPage = 1; CurrentPage != NumOfPages; CurrentPage++; )
		{
			WebpageObj[CurrentPage] = new Webpage
			WebpageObj[CurrentPage].ScanPage();
			WebpageObj[CurrentPage].AddToIndex();
		}
		for (int CurrentPage = 1; CurrentPage != NumOfPages; CurrentPage++; )
		{
			WebpageObj[CurrentPage].ConvertPage();
			//add destruction of object here
		}
	}
}
