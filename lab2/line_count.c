#include "line_functions.h"

int main()
{
    int lines = 0;

    int buf_size = 100;
    char buffer[buf_size];

    int chars_read;
    while (1)
    {
        chars_read = readline(buffer, buf_size);
        if (chars_read > 0)
        {
            lines++;
        }
        else
        {
            break;
        }
    }

    printf("%d lines\n", lines);

    return lines;
}
