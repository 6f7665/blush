#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

void katwrite( char *file, char *kw_pattern )
{
	int chaarpos = 0;
	int fnp = 0;
	char chaar;
	char filename[255];
	
	//chaar = file[chaarpos];
	while( chaarpos != 254 )
	{
		chaar = file[chaarpos];
		chaarpos++;
		if( chaar == '/' )
		{
			fnp = 0;
		}
		if( chaar != '.' && chaar != '/' )
		{
			filename[fnp] = chaar;
			fnp++;
		}
		if( chaar == '.' )
		{
			chaarpos = 254;
		}
	}

	while( fnp != 254 )
	{
		filename[fnp] = '\0';
		fnp++;
	}

	char kw_gen[68];
	kw_gen[0] = 'g';
	kw_gen[1] = 'e';
	kw_gen[2] = 'n';
	kw_gen[3] = '/';
	for (int num = 4; num != 68; num++)
	{
		kw_gen[num] = '\0';
	}
	strcat(kw_gen, kw_pattern);

	FILE *kw_fp; //declare filepointer and open file in "gen/" for appending
	kw_fp = fopen(kw_gen, "a");

	fputs(filename, kw_fp); //write the name of the file indexed in this program to pattern.extention
	fputc("\n", kw_fp);
	fclose(kw_fp);

	printf("added %s ", filename); //print out what we did
	printf("to %s\n", kw_pattern);
}

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
		printf("ERROR: Too many filenames.\n");
		return 1;
	}
	//abort if there is no argument
	else
	{
		printf("ERROR: Missing argument - No filename.\n");
		return 1;
	}

	//make a file pointer and open the file for reading
	FILE *fp;
	fp = fopen(argv[1], "r");

	//check if the file opened properly
	if( fp==NULL )
	{
		printf("ERROR: File couldn't be opened");
		return 1;
	}

	//get the first char from the file
	char ch;	
	
	//setup chars to find patterns
	int n;
	int line;
	line = 1;
	char dot[2] = {'.', '\0'};
	char cs[8] = {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};
	char cat[8] = {'c', 'a', 't', '\0', '\0', '\0', '\0', '\0'};
	char tag[8] = {'t', 'a', 'g', '\0', '\0', '\0', '\0', '\0'};
	char sub[8] = {'s', 'u', 'b', '\0', '\0', '\0', '\0', '\0'};
	char map[8] = {'m', 'a', 'p', '\0', '\0', '\0', '\0', '\0'};
	char start[8] = {'s', 't', 'a', 'r', 't', '\0', '\0', '\0'};
	char pattern[63];

	int p;
	p = 0;
	while( p != 63 )
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
			ch = fgetc(fp); //read next char
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
			if ( ch == ':' && n == 3 ) //check if it's a ":" after 3 characters
			{
				ch = fgetc(fp); //get the new char
				p = 0; //setup loop

				while( ch != ':' && p != 63 )
				{
					if( ch == ',' ) //check if patterns are separated and write file if so
					{
						strcat(pattern, dot);
						strcat(pattern, cs);
						p = (p + 4);
						katwrite( argv[1], pattern );
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
					ch = fgetc(fp); //get new char and return to start of loop
				}

				if( ch == ':' && p != 63 && p != 0 ) //check if it was just two ":"
				{
					strcat(pattern, dot);
					strcat(pattern, cs);
					p = (p + 4);
					katwrite( argv[1], pattern );
					while( p != 0 )
					{
						pattern[p] = '\0';
						p--;
					}
				}
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

				//count up till next line here
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

