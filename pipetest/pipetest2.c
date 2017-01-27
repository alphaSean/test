#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    int fd[2];
    pid_t pid;

    if (pipe(fd) == -1)
    {
        printf("pipe failed!\n");
        return -1;
    }

    if ((pid = fork()) < 0)
    {
        printf("fork failed!\n");
        return -2;
    }
    else if (pid > 0)
    {
        close(fd[1]);
        dup2(fd[0], 0);
        sleep(3);
        if (execlp("wc", "-l", (char*)0) < 0)
        {
            printf("father execl failed!\n");
        }
    }
    else if (pid == 0)
    {
        close(fd[0]);
        dup2(fd[1], 1);
        if (execlp("ls", "-l", (char*)0) < 0)
        {
            printf("child execl fail\n");
        }
        sleep(2);
    }
    return 0;
}
