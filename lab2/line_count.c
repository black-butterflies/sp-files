#include "line_functions.h"

int main()
{
    int lines = 0;

    int buf_size = 100;
    char buffer[buf_size];

    for (int i=0; i < 11; i++)
    {
        int chars_read = readline(buffer, buf_size);
        int chars_written = writeline(buffer);

        printf("Read %d characters and wrote %d characters\n", chars_read, chars_written);
    }

    return lines;
}
