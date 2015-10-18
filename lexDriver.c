//simple driver that opens a file and sends test to lex to scan

#include <stdio.h>
#include <string.h>

int main (int argc, char* argv[])
{
	int args = 1;
	int debugLevel = 0;
	char outFileName[30];
	FILE* outFile;
	
	//current name of the output file, can be changed by -o option
	strcpy(outFileName, "lexDriver.out");
	//run through commandline arguments if there are any
	if (argc > 1)
	{
		for (args; args < argc; args++)
		{
			if (strcmp(argv[args],"-o") == 0)
			{
			    strcpy(outFile, argv[args+1]);
			    printf("writing tokens to file %s...\n", outFile);
			    args+=1;				
			}
			
			else if (strcmp(argv[args],"-d") == 0)
			{
				printf("setting debug levels -d, no debug\n");
				//no debugging, just runs lex
				debugLevel = 0;
			}
			
			else if (strcmp(argv[args],"-dl") == 0)
			{
				printf("setting debug levels -dl, lex debug\n");
				//lex debugging, 
				debugLevel = 1;
			}
			
			else if (strcmp(argv[args],"-ds") == 0)
			{
				printf("setting debug levels -ds, symbol table debug\n");
				debugLevel = 2;
			}
			
			else if (strcmp(argv[args],"-dls") == 0 || strcmp(argv[args],"-dsl") == 0)
			{
				printf("setting debug levels %s, lex and symbol debug\n");
				debugLevel = 3;
			}
			
			else
			    printf("ignoring unrecognized option %s\n", argv[args]);
		}
	}

    
    //open input file and copy to ?
    //print first line of file input to outfile
    //request tokens from lex yylex() until newline token returned
    //write this token to file    
    //on newline write next line of file input
	return 0;
}
