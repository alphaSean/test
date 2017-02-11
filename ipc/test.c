#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv)
{
    pid_t pid;

    if ((pid = fork()) == 0)
    {
        execl("./test2", "test2", NULL);
    }
    else if (pid > 0)
    {
        while()
    }
}

