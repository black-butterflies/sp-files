#include <stdio.h>
#include <string.h>

int readline(char line[], int max);
int writeline(const char line[]);

int main() {
	char buffer[100];
	int chars_read = readline(buffer, 100);

	printf("%d characters read\n", chars_read);

	return 0;
}

/* readline: read a line from statndard input, return its length or 0
 */
int readline(char line[], int max) {
	if (fgets(line, max, stdin) == NULL) {
		return 0
	} else {
		return strlen(line);
	}
}

/* writeline: write line to standard output, return number of chars written
 */
int writeline(const char line[]) {
	fputs(line, stdout);
	return strlen(line);
}
