#include <unistd.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    char c = 0;
    while ((c = fgetc(stdin)) != EOF)
    {
        if (isupper(c))
        {
            c = tolower(c);
        }
        if (fputc(c, stdout) == EOF)
        {
            printf("output error!\n");
            return -1;
        }
        if (c == '\n')
        {
            fflush(stdout);
        }
    }

    return 0;
}
