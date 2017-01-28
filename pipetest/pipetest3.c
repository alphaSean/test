#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

#define MAX_BUF_SIZE 256
int main()
{
    pid_t pid;
    int fd[2];
    char buf[MAX_BUF_SIZE];
    FILE* pFile = NULL;
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
        
        if (execl("/bin/cat", "cat", (char*)0) < 0)
        {
            printf("father execl failed!\n");
        }
    }
    else
    {
        close(fd[0]);
        pFile = fopen("/home/sean/test.txt", "r");

        while (fgets(buf, MAX_BUF_SIZE, pFile))
        {
            write(fd[1], buf, strlen(buf));
        }

        if (waitpid(pid, NULL, 0) == -1)
        {
            printf("waitpid failed!\n");
        }
    }


    return 0;
}
