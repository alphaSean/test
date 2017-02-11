#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "my_func.h"

#define MAX_BUF_SIZE 256 

static void sigpipe_func(int sig);

int main()
{
    pid_t pid;
    int fd1[2];
    int fd2[2];
    char szBuf[MAX_BUF_SIZE];
    int n;

    if (my_signal(SIGPIPE, sigpipe_func) == SIG_ERR)
    {
        printf("my_signal SIGPIPE failed!\n");
        exit(1);
    }

    if (pipe(fd1) == -1 || pipe(fd2) == -1)
    {
        printf("pipe failed!\n");
        return -1;
    }

    if ((pid = fork()) > 0)
    {
        close(fd1[0]);
        close(fd2[1]);
        while (fgets(szBuf, MAX_BUF_SIZE, stdin))
        {
            n = strlen(szBuf);
            if (write(fd1[1], szBuf, n) != n)
            {
                printf("write msg error to pipe n = %d!\n", n);
                exit(1);
            }
            if ((n = read(fd2[0], szBuf, MAX_BUF_SIZE)) < 0)
            {
                printf("read from pipe error!\n");
                exit(1);
            }
            if (n == 0)
            {
                printf("child pipe close\n");
                break;
            }
            szBuf[n] = 0;
            if (fputs(szBuf, stdout) == EOF)
            {
                printf("fputs to stdout error!\n");
                exit(0);
            }
        }


        if (ferror(stdin))
        {
            printf("fget error from stdin!\n");
        }
    }
    else if (pid == 0)
    {
        if (fd1[0] != STDIN_FILENO)
        {
            dup2(fd1[0], STDIN_FILENO);
        }
        
        if (fd2[1] != STDOUT_FILENO)
        {
            dup2(fd2[1], STDOUT_FILENO);
        }

        if (execl("./my_filter3", "my_filter3", NULL) == -1)
        {
            printf("execl failed!\n");
        }
        exit(0);
    }
    else
    {
        printf("fork failed!\n");
        return -1;
    }
    
    return 0;
}

static void sigpipe_func(int sig)
{
    printf("child finished!\n");
}
