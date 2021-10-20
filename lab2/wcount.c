#include <ctype.h>
#include <stdio.h>

int main()
{
    int words = 0;
    char c = ' ';
    int is_word = 0;
    while (c != EOF)
    {
        c = getchar();
        if (isalpha(c))
        {
            is_word = 1;
        }
        else if (isspace(c))
        {
            if (is_word)
            {
                words++;
            }
            else
            {
                is_word = 0;
            }
        }
        else
        {
            is_word = 0;
        }
    }

    printf("Read %d words\n", words);

    return 0;
}