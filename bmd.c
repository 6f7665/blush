#include <stdio.h>
#include <unistd.h>
#include <ctype.h>

int main( int argc, char *argv[] )
{
	if( argc > 2 )
	{
		printf("ERROR: Too many filenames.\n");
		return 1;
	}
	else
	{
		printf("ERROR: Missing argument - No filename.\n");
		return 1;
	}

	FILE *fp;
	char ch;	
	fp = fopen(argv[1], "r");
	
	if( fp==NULL )
	{
		printf("ERROR: File couldn't be opened.");
		return 1;
	}
	
	ch = fgetc(fp);

	//declare variables for headers
	int header;
	int headern;
	header = 0;
	headern = 0;

	//declare variables for spaces // <br>
	int spacen;
	spacen = 0;

	while( ch!=EOF )
	{
		while( ch == ' ' ) // counting spaces
		{
			spacen++;
			printf(" ");

			ch = fgetc(fp);

			if( ch == '\n' ) // if it's new row we add a <br>
			{
				printf("\n");
				if( spacen >= 2 )
				{
					printf("<br>"); // add <br> cuz it was two spaces
				}
				spacen = 0;
			}
		}
		while( ch == '#' ) //counting hashtags
		{
			headern++;
			ch = fgetc(fp);
		}
		if( headern != 0 ) //if the hashtags stop
		{
			int a;
			if( ch == '\n' ) //it was just an empty line, print out hashtags and skip
			{
				for( a = 0; a != headern; a++ ) //print out all the lost hashtags
				{
					printf("#");
				}
				printf("\n");
				headern = 0;
			}
			if( ch == ' ' ) //if there is a space after the hashtags, start a <h[x]>
			{
				printf("<h%i>", headern);
				header = 1;
				ch = fgetc(fp);
				while ( ch != '\n')
				{
					printf("%c", ch );
					ch = fgetc(fp);
				}
			}
			if ( ch == '\n' ) //close the header at end of line
			{
				printf("</h%i>\n", headern);
				header = 0;
				headern = 0;
			}
			else //there is no header just a comment
			{
				for( a = 0; a != headern; a++ ) //print out all the lost hashtags
				{
					printf("#");
				}
				//printf("\n");
				printf("%c", ch);
				headern = 0;
			}
		}
		else
		{
			printf("%c", ch );
		}
		ch = fgetc(fp); //next char
	}
	
	//printf("Det finns inget mer i %s\n", argv[1]);
	fclose(fp);

	return 0;
}

