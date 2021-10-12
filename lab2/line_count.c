#include "line_functions.h"

int main()
{
    int lines = 0;

    int buf_size = 100;
    char buffer[buf_size];

    do
    {
        int chars_read = readline(buffer, buf_size);
        writeline(buffer);

        lines++;
    } while (chars_read > 0);

    return lines;
}
