#include "types.h"
#include "stat.h"
#include "user.h"

/*
Author: Eugene Kennedy
Purpose: Print first 10 (variable) lines of input. Given either a file(s) or has input piped in. Built w/ consultation w/ wc.c included with xv6. Prints to err instead of standard output in error cases.
If multiple files are input, prints first 10 lines from each.
Made for CS3224
2/3/16
*/




void head(int fd, char* name, int numLines)
{
	int i;
	char buffer[512];
	//Flag that stores status of file.
	int n;

	//Read into buffer while we can read the file. Loop until we get numLines lines or run out of lines to read
	while((n = read(fd, buffer, sizeof(buffer)))>0){
	for(i = 0; i < n; i++)
	{
		if(numLines == 0)
		{
			return;		
		}
		//If eol found, increment
		if(buffer[i] == '\n')
		{
			numLines--;
		}

		//Set up string pointer to print
		char toPrint[2];
		toPrint[0] = buffer[i];
		toPrint[1] = '\0';

		//Print current val
		printf(1, toPrint);

	}
	}
	//If read error (n=-1) print to std error
	if(n < 0)
	{
		printf(2, "Read Error!");
		exit();
	}

}







//Main for head. Only supports 1 file at the moment. Takes in a file and passes it to head function to do the printing, then returns and closes the file.
int main(int argc, char* argv[])
{
	int numLines = 10;
	int fd;
	printf(1, "%d", argc);	
	//Was a file passed or was it piped?
	if (argc <= 2)
	{
		//check for flag
		if(argc > 0)
		{
			//nested to prevent segfault
			if(argv[1][0] == '-')
			{
				numLines = atoi(argv[1]+1);
			}
			else if (argc == 2)
			{
				if((fd = open(argv[1], 0)) < 0)
	                        {
        	                        printf(2, "file failed to open!");
                	                exit();
                       		}
				head(fd, argv[1], numLines);
				close(fd);
				exit();
			}
		}
		head(0, "", numLines);	
	}
		int i;
	
		for(i = 1; i < argc; i++){
			//check for flag
			if(i==1 && argv[i][0]=='-')
			{
				numLines = atoi(argv[i]+1);
				continue;		
			}
			//Check if file opens correctly.
			else if((fd = open(argv[i], 0)) < 0)
			{
				printf(2, "file failed to open!");
				exit();	
			}
		head(fd, argv[i], numLines);
		//Close to prevent memory issues		
		close(fd);
		}
		
	
	exit();
	return 0;
}

