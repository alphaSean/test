#include <unistd.h>
#include <stdio.h>

#define MAXLINE 256 

int main()
{
    char line[MAXLINE];
    FILE *fpin;
    if (!(fpin = popen("./my_filter < pipetest5.c", "r")))
    {
        printf("popen failed!\n");
        return -1;
    }

    while (1)
    {
        fputs("prompt> ", stdout);
        fflush(stdout);

        if(!fgets(line, MAXLINE, fpin))
        {
            break;
        }

        if (fputs(line, stdout) < 0)
        {
            break;
        }
    }

    pclose(fpin);
    return 0;
}
