#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

#define MAX_BUF_SIZE 256
#define DEFAULT_PAGER "/bin/more"
int main(int argc, char** argv)
{
    pid_t pid;
    int fd[2];
    char buf[MAX_BUF_SIZE];
    FILE* pFile = NULL;
    char *pager = NULL;
    char *argv0 = NULL;
    
    if ((pFile = fopen(argv[1], "r")) < 0)
    {
        printf("can not open %s\n", argv[1]);
        return -1;
    }

    if (pipe(fd) < 0)
    {
        printf("pipe failed!\n");
        return 0;
    }

    if ((pid=fork()) < 0)
    {
        printf("fork failed!\n");
        return 0;
    }
    else if(pid == 0)
    {
        close(fd[1]);
        if (fd[0] != STDIN_FILENO)
        {
            if (dup2(fd[0], STDIN_FILENO) < 0)
            {
                printf("dup2 failed!\n");
            }
            close(fd[0]);
        }
        if ((pager = getenv("PAGER")) == NULL)
        {
            pager = DEFAULT_PAGER;
        }

        argv0 = strrchr(pager, '/');
        if(argv0)
        {
            argv0++;
        }
        else
        {
            argv0 = pager;
        }
        
        if (execl(pager, argv0, NULL) < 0)
        {
            printf("child execl failed!\n");
        }
    }
    else
    {
        close(fd[0]);

        while (fgets(buf, MAX_BUF_SIZE, pFile))
        {
            write(fd[1], buf, strlen(buf));
        }
        if (ferror(pFile))
        {
            printf("fgets error!\n");
        }

        if (waitpid(pid, NULL, 0) == -1)
        {
            printf("waitpid failed!\n");
        }
    }


    return 0;
}
