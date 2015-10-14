//simple driver that opens a file and sends test to lex to scan

#include <stdio.h>
#include <string.h>

int main (int argc, char* argv[])
{
	int args = 0;
	char outFile[20];
	
	//run through commandline arguments if there are any
	if (argc > 1)
	{
		for (args = 1; args < argc; args++)
		{
			if (argv[args] == "-o")
			{
			     if (argc
			        strcpy(outFile, argv[args+1]);
			        printf("writing to file %s\n", outFile);
				    //if arg = argc-1 report error "include file name"
				
			}
			else if (argv[args] == "-d")
			{
				printf("setting debug levels\n");
				//set debug levels
			}
		}
	}

	return 0;
}
