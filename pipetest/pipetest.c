#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINE 40

int main()
{
    int n = 0;
    int fd[2];

    pid_t pid;
    char line[MAX_LINE];
    memset(line, 0, MAX_LINE);

    char *psz = "hello world!";
    
    if (pipe(fd) < 0)
    {
        printf("pipe error!\n");
        return -1;
    }
    if ((pid = fork()) < 0)
    {
        printf("fork error!\n");
        return -2;
    }
    else if (pid > 0)
    {
        close(fd[0]);
        write(fd[1], psz, strlen(psz));
    }
    else
    {
        close(fd[1]);
        n = read(fd[0], line, MAX_LINE);
        write(STDOUT_FILENO, line, n);
    }
    
    return 0;
}
