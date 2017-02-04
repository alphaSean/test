#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

#include "my_func.h"


#define MAX_BUF_SIZE 256
#define PAGER "${PAGER:-less}"

void childsig_func(int sig)
{
    printf("in child sig handle func");
}


int main(int argc, char** argv)
{
    FILE *pIn = NULL;
    FILE *pOut = NULL;
    char szBuf[MAX_BUF_SIZE];
    memset(szBuf, 0, MAX_BUF_SIZE);


    if (argc < 2)
    {
        printf("not enough params!\n");
        return -1;
    }

    if (my_signal(SIGCHLD, childsig_func) == SIG_ERR)
    {
        perror("signal SIGCHLD failed!\n");
        return -1;
    }

    if (!(pIn = fopen(argv[1], "r")))
    {
        printf("open file %s failed!\n", argv[1]);
        return -1;
    }

    if (!(pOut = my_popen(PAGER, "w")))
    {
        printf("my_popen %s failed!", PAGER);
        return -1;
    }
    
    while (fgets(szBuf, MAX_BUF_SIZE, pIn))
    {
        fputs(szBuf, pOut);
    }

    if (my_pclose(pOut) == -1)
    {
        printf("my_pclose failed!\n");
    }

    return 0;
}
