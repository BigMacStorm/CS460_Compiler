//simple driver that opens a file and sends test to lex to scan

#include <stdio.h>

int main (int argc, char* argv[])
{
	int arg = 0;
	if (argc > 1)
	{
		for (arg = 1; arg < argc; arg++)
		{
			if (argv[arg] == "-o")
			{
				//if arg = argc-1 report error "include file name"
				//file open argv[arg+1]
			}
			else if (argv[arg] = "-d")
			{
				//set debug levels
			}
		}
	}

	return 0;
}
