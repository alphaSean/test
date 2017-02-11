#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_BUF_SIZE 256
int main()
{
    char szRecBuf[MAX_BUF_SIZE];
    char szRetBuf[MAX_BUF_SIZE];
    int nNum1 = 0;
    int nNum2 = 0;

    memset(szRecBuf, 0, MAX_BUF_SIZE);
    memset(szRetBuf, 0, MAX_BUF_SIZE);
    setvbuf(stdin, NULL, _IOLBF, 0);
    setvbuf(stdout, NULL, _IOLBF, 0);
    while ((fgets(szRecBuf, MAX_BUF_SIZE, stdin)))
    {
        if (sscanf(szRecBuf, "%d%d", &nNum1, &nNum2) != EOF)
        {
            sprintf(szRetBuf, "%d", nNum1 * nNum2);
            printf("%s", szRetBuf);
        }
        else
        {
            sprintf(szRetBuf, "invalid input params!");
            printf("%s", szRetBuf);
            exit(0);
        }
        memset(szRecBuf, 0, MAX_BUF_SIZE);
        memset(szRetBuf, 0, MAX_BUF_SIZE);
    }

    return 0;
}
