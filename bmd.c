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
	int italic = 0;
	int strikethrough = 0;
	char prev_ch;

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

	italic = 0;

	while( ch!=EOF )
	{
		if( ch == '<' ) //ignore existing html tags
		{
			int link = 0;
			printf("%c", ch);
			ch = fgetc(fp);
			if( ch == 'a')
			{
				link = 1;
			}
			while( ch != '>' && ch != EOF )
			{
				printf("%c", ch);
				ch = fgetc(fp);
			}
			while( link != 0 )
			{
				int lsn = 0;
				char linkstring[5] = {'<', '/', 'a', '>', '\0'};
				printf("%c", ch);
				ch = fgetc(fp);
				while( ch == linkstring[lsn] )
				{
					lsn++;
					printf("%c", ch);
					ch = fgetc(fp);
					if( lsn == 4 )
					{
						link = 0;
						break;
					}
				}
			}
		}
		//escape character prints out next character without formatting
		if( ch == '\\' )
		{
			ch = fgetc(fp);
			printf("%c", ch);
			ch = fgetc(fp);
		}

		//text formatting
		while( ( ch == '*' || ch == '_' || ch == '~' ) && ch != EOF )
		{
			//prevoius char definitions
			//int strong = 0;
			//int underline = 0;
			//int italic = 0;
			//int strikethrough = 0;
			//char prev_ch;
			//
			//tags
			//<em> = italic
			//<u> = underline
			//<del> = strikethrough
			//<strong> = bold
		
			int formattingchars;
			char new_ch;
			fpos_t position;

			fgetpos(fp, &position); //save the position
			new_ch = fgetc(fp); // read one character ahead
			fsetpos(fp, &position); //return to previous position
			
			if( new_ch == ch ) //check amout of formatting chars (if the next char is the same as current)
			{
				formattingchars = 2;
			}	
			if( new_ch != ch )
			{
				formattingchars = 1;
			}
		
			//put or clear formatting based on char amount
			if( formattingchars == 2 )
			{
				//clear formatting
				if( ch == '*' && strong == 1 ){ printf("</strong>"); strong = 0; }
				else if( ch == '_' && underline == 1 ){ printf("</u>"); underline = 0; }
				else if( ch == '~' && strikethrough == 1 ){ printf("</del>"); strikethrough = 0; }
	
				//put formatting
				else if( ch == '*' && strong == 0 ){ printf("<strong>"); strong = 1; }
				else if( ch == '_' && underline == 0 ){ printf("<u>"); underline = 1; }
				else if( ch == '~' && strikethrough == 0 ){ printf("<del>"); strikethrough = 1; }

				ch = fgetc(fp);
			}
			if( formattingchars == 1 )
			{
				if( ch == '*' && italic == 1 ){ printf("</em>"); italic = 0; }
				else if( ch == '_' && italic == 1 ){ printf("</em>"); italic = 0; }

				else if( ch == '*' && italic == 0 ){ printf("<em>"); italic = 1; }
				else if( ch == '_' && italic == 0 ){ printf("<em>"); italic = 1; }
			}
			ch = fgetc(fp);
		}

		//code blocks, everything but ` are ignored once it begins
		//``` has to be ended with ``` as a ` within two `` will be ignored too
		//input: `` ` `` will give: <code> ` </code>
		//input: `` ` ``` will give: <code> ` </code><code>
		
		//escape character prints out next character without formatting
		if( ch == '`' && prev_ch != '\\')
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
				else if( ch != '`' )
				{
					printf("%c", ch);
					ch = fgetc(fp);
				}
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
			}
			printf("</code>");
		}

		//<br> with space+space+\n
		if( ch == ' ' ) // counting spaces
		{
			int spacechars = 1;
			char new_ch;
			fpos_t position;

			fgetpos(fp, &position); //save the position
			new_ch = fgetc(fp); //go ahead anc read next char

			while( new_ch == ' ' ) //count spaces in a row
			{
				spacechars++;
				new_ch = fgetc(fp);
			}	
			if( new_ch == '\n' && spacechars >= 2 ) //if its new line after 2 or more spaces print <br>\n and dont go back to prev position
			{
				printf("<br>");
				printf("\n");
			}
			else //if there is no newline after spaces print out space and go back to previous position
			{
				fsetpos(fp, &position);
				printf(" ");
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

		else if( ch != ' ' )
		{
			printf("%c", ch );
		}
		prev_ch = ch;
		ch = fgetc(fp); //next char
	}
	
	fclose(fp);

	return 0;
}

