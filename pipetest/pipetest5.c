#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_BUF_SIZE 256
#define PAGER "${PAGER:-less}"

int main(int argc, char** argv)
{
    FILE *pIn = NULL;
    FILE *pOut = NULL;
    char szBuf[MAX_BUF_SIZE];
    memset(szBuf, 0, MAX_BUF_SIZE);


    if (argc < 2)
    {
        printf("not enough params!\n");
    }

    if (!(pIn = fopen(argv[1], "r")))
    {
        printf("open file %s failed!\n", argv[1]);
        return -1;
    }

    if (!(pOut = popen(PAGER, "w")))
    {
        printf("popen %s failed!", PAGER);
        return -1;
    }
    
    while (fgets(szBuf, MAX_BUF_SIZE, pIn))
    {
        fputs(szBuf, pOut);
    }

    if (pclose(pOut) == -1)
    {
        printf("pclose failed!\n");
    }

    return 0;
}
