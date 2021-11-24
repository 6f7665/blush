#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

int main( int argc, char *argv[] )
{
	int running = 0;
	//check if it's one argument and open if so
	if(argc == 2)
	{
		running = 1;
	}
	//abort if more than one argument
	else if( argc > 2 )
	{
		printf("ERROR: Du har angivit för många filnamn.\n");
		return 1;
	}
	//abort if there is no argument
	else
	{
		printf("ERROR: Du har inte angivit ett filnamn.\n");
		return 1;
	}

	//make a file pointer and open the file for reading
	FILE *fp;
	fp = fopen(argv[1], "r");

	//check if the file opened properly
	if( fp==NULL )
	{
		printf("ERROR: Något gick fel när filen öppnades");
		return 1;
	}

	//get the first char from the file
	char ch;	
	
	//setup chars to find patterns
	int n;
	int line;
	line = 1;
	char cs[8] = {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};
	char cat[8] = {'c', 'a', 't', '\0', '\0', '\0', '\0', '\0'};
	char tag[8] = {'t', 'a', 'g', '\0', '\0', '\0', '\0', '\0'};
	char sub[8] = {'s', 'u', 'b', '\0', '\0', '\0', '\0', '\0'};
	char map[8] = {'m', 'a', 'p', '\0', '\0', '\0', '\0', '\0'};
	char start[8] = {'s', 't', 'a', 'r', 't', '\0', '\0', '\0'};
	char pattern[511];

	int p;
	p = 0;
	while( p != 512 )
	{
		pattern[p] = '\0';
		p++;
	}

	//run through the entire file char by char or til we terminate
	while( ch!=EOF && running == 1 )
	{
		if( ch == '\n' )
		{
			line++;
		}
		ch = fgetc(fp); //load next char
		if( ch == '!' ) //check if we have a blush prefix
		{
			ch = fgetc(fp); //ignore the ! char and read next char
			n = 0;
			while( ch != ':' && ch != '\n' && n != 7)
			{
				cs[n] = ch;
				n++;
				ch = fgetc(fp);
			}
			if ( ch == '\n' )
			{
				//if this is true the rest is false so it goes back to the first while
				printf("found !, but there's no data on line %d\n", line);
			}
			if ( ch == ':' && n == 3 )
			{
				ch = fgetc(fp);
				p = 0;
				while( ch != ':' && p != 512 )
				{
					if( ch == ',' ) //check if patterns are separated and writes file if so
					{
						printf("adding %s ", argv[1]);
						printf("to file %s", pattern);
						printf(".%s\n", cs);
						while( p != 0 )
						{
							pattern[p] = '\0';
							p--;
						}
					}
					else if( ch != '\n' )
					{
						pattern[p] = ch;
						p++;
					}
					else if( ch == '\n' )
					{
						printf("missing : on line %d\n", line);
					}
					ch = fgetc(fp);
				}
				if( ch == ':' && p != 512 && p != 0 ) //check if it was just two ::
				{
					printf("adding %s ", argv[1]);
					printf("to file %s", pattern);
					printf(".%s\n", cs);
					while( p != 0 )
					{
						pattern[p] = '\0';
						p--;
					}
				}
//				if( strcmp( cs, cat ) == 0 )
//				{
//					scanpattern = 1;
//				}
//				else if( strcmp( cs, sub ) == 0 )
//				{
//					scanpattern = 1;
//				}
//				else if( strcmp( cs, tag ) == 0 )
//				{
//					scanpattern = 1;
//				}
//				else if( strcmp( cs, map ) == 0 )
//				{
//					scanpattern = 1;
//				}
			}
			else if( strcmp( cs, start ) == 0 )
			{
				printf("pattern found: %s ", cs);
				printf("on line %d\n", line);
				running = 0;
			}
			else
			{
				printf("strange pattern: %s ", cs);
				printf("on line %d\n", line);
				//printf(" in file: %s", argv);
			}
			cs[0] = '\0';
			cs[1] = '\0';
			cs[2] = '\0';
			cs[3] = '\0';
			cs[4] = '\0';
			cs[5] = '\0';
			cs[6] = '\0';
			cs[7] = '\0';
		}
	}
	
	//printf("Det finns inget mer i %s\n", argv[1]);
	fclose(fp);

	return 0;
}
