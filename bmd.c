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
	else if( argc < 1 )
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

	//text formatting bools (0 = inactive, 1 = active )
	int strong = 0;
	int underline = 0;
	int italics = 0;
	int strikethrough = 0;
	char prev_ch = '\0';

	//code blocks
	int codeblock = 0;

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
		//escape character prints out next character without formatting
		if( ch == '\\' )
		{
			ch = fgetc(fp);
			printf("%c", ch);
			ch = fgetc(fp);
		}

		//text formatting
		if( ch == '*' || ch == '_' || ch == '~' )
		{
			prev_ch = ch;
			ch = fgetc(fp);

			if( ch == prev_ch )
			{
				if( prev_ch == '*' ) //toggle "strong"
				{
					if( strong == 0 )
					{
						strong = 1;
						printf("<strong>");
					}
					else
					{
						strong = 0;
						printf("</strong>");
					}
				}
				if( prev_ch == '_' ) //toggle underline
				{
					if( underline == 0 )
					{
						underline = 1;
						printf("<u>"); //could be <ins> too
					}
					else
					{
						underline = 0;
						printf("</u>");
					}
				}
				if( prev_ch == '~' ) //toggle strikethrough
				{
					if( strikethrough == 0 )
					{
						strikethrough = 1;
						printf("<del>");
					}
					else
					{
						strikethrough = 0;
						printf("</del>");
					}
				}
			}
			else //ch wasn't equal to previous char
			{
				if( prev_ch == '*' || '_' ) //toggle italics <em>/<i>
				{
					if( italics == 0 )
					{
						italics = 1;
						printf("<em>");
					}
					else
					{
						italics = 0;
						printf("</em>");
					}
				}
				//the char ch will loop back to the beginning of the while loop if it is _*~,
			}

		}

		//code blocks, everything but ` are ignored once it begins
		//``` has to be ended with ``` as a ` within two `` will be ignored too
		//input: `` ` `` will give: <code> ` </code>
		//input: `` ` ``` will give: <code> ` </code><code>
		if( ch == '`')
		{
			while( ch == '`' )
			{
				codeblock++;
				ch = fgetc(fp);
			}
			printf("<code>");

			int codeesc = 0;

			while( codeblock != 0 && ch != EOF)
			{
				while( ch == '`' ) //close the code tag
				{
					codeesc++;
					ch = fgetc(fp);
					if( ch != '`' && codeblock == codeesc )
					{
						codeblock = 0;
						codeesc = 0;
					}
					else if( ch != '`' ) //fails to close code tag, not enough tics in escape sequence
					{
						while( codeesc != 0 )
						{
							printf("`");
							codeesc--;
						}
					}
				}
				if( ch == '\n' )
				{
					printf("<br>");
					ch = fgetc(fp);
				}
				else if( ch == '<' )
				{
					printf("&#60");
					ch = fgetc(fp);
				}
				else if( ch == '>' )
				{
					printf("&#62");
					ch = fgetc(fp);
				}
				if( ch != '`' )
				{
					printf("%c", ch);
					ch = fgetc(fp);
				}
			}
			printf("</code>");
		}

		//<br> with space+space+\n
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

		//headers using "#"
		while( ch == '#' ) //count up hashtags to get the [x] for <h[x]>
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

