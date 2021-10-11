#include "line_functions.h"

int main()
{
	char buffer[100];
	int chars_read = readline(buffer, 100);

	int chars_written = writeline(buffer);

	if (chars_read != chars_written) 
	{
		puts("There was a problem while reading the line. Try again");
		return 1;
	}

	return 0;
}
