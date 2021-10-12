#include <stdio.h>

int main()
{
    int lines;
    char c;

    do
    {
        c = getchar();
        if (c == '\n')
        {
            lines++;
        }
    } while (c != EOF);

    return 0;
}