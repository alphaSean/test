#include <unistd.h>
#include <stdio.h>

static int fd1[2], fd2[2];

void tell_wait()
{
    if (pipe(fd1) < 0 || pipe(fd2) < 0)
    {
        printf("pipe fd1 or fd2 failed!\n");
    }
}


void tell_parent()
{
    if (write(fd2[1], "c", 1) != 1)
    {
        printf("tell parent write p to fd2[1] failed!\n");
    }
}

void tell_child()
{
    if (write(fd1[1], "p", 1) != 1)
    {
        printf("tell parent write p to fd2[1] failed\n");
    }
}

void wait_parent()
{
    char c;
    if (read(fd2[0], &c, 1) == -1)
    {
        printf("wait parent read from fd2[0] failed!\n");
    }
}

void wait_child()
{
    char c;
    if (read(fd1[0], &c, 1) == -1)
    {
        printf("wait parent read from fd2[0] failed!\n");
    }

}


int main()
{
    pid_t pid;
    tell_wait();
    if ((pid = fork()) > 0)
    {
        wait_parent();
        tell_child();
    }
    else if(pid == 0)
    {
        tell_parent();
        wait_child();
    }
    else
    {
        printf("fork error!\n");
    }

    return 0;
}
