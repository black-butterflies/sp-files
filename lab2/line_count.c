#include "line_functions.h"

int main()
{
    int lines;

    int buf_size = 100;
    char buffer[buf_size];

    do
    {
        readline(buffer, buf_size);
        writeline(buffer);

        lines++;
    } while (buffer[0] != EOF);

    return 0;
}