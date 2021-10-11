#include "line_functions.h"

int readline(char line[], int max)
{
	if (fgets(line, max, stdin) == NULL) 
	{
		return 0;
	}
	else
	{
		return strlen(line);
	}
}

int writeline(const char line[]) 
{
	fputs(line, stdout);
	return strlen(line);
}
