int Getstartflags( int argumentcount, char *argument[] )
{
	int ReturnValue;

	if( argumentcount == 0 )
	{
		printf("ERROR: Missing argument\n");
		return 1;
	}
	for( int n = 1; n != argumentcount; n++ )
	{
		if( argument[n] == "-f" ) { ReturnValue-=1; }
		if( argument[n] == "-i" ) { ReturnValue-=2; }
		if( argument[n] == "-n" ) { ReturnValue-=4; }
		else
		{
			printf("ERROR: Uknown argument\n");
			return 1;
		}
	}
	return ReturnValue;
}


		
