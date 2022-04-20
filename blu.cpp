#include <cstdio>
#include <startflags.h>

class Webpage
{
	public:

		char title[512];
		char category[512];
		char SubCategory[512];
		char tags[512];
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


	int NumOfPages = 1; //check contents of folder from arguments herer

	Webpage* WebpageObj = new Webpage[NumOfPages];
	
	//insert filename template
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
