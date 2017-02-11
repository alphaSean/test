#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_BUF_SIZE 256
int main()
{
    char szRecBuf[MAX_BUF_SIZE];
    char szRetBuf[MAX_BUF_SIZE];
    int n = 0;
    int nNum1 = 0;
    int nNum2 = 0;

    memset(szRecBuf, 0, MAX_BUF_SIZE);
    memset(szRetBuf, 0, MAX_BUF_SIZE);
    while ((n = read(STDIN_FILENO, szRecBuf, MAX_BUF_SIZE)) > 0)
    {
        if (sscanf(szRecBuf, "%d%d", &nNum1, &nNum2) != EOF)
        {
            sprintf(szRetBuf, "%d", nNum1 * nNum2);
            write(STDOUT_FILENO, szRetBuf, strlen(szRetBuf));
        }
        else
        {
            sprintf(szRetBuf, "invalid input params!");
            write(STDOUT_FILENO, szRetBuf, strlen(szRetBuf));
            exit(0);
        }
        memset(szRecBuf, 0, MAX_BUF_SIZE);
        memset(szRetBuf, 0, MAX_BUF_SIZE);
    }

    return 0;
}
