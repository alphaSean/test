#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>

#ifdef OPEN_MAX
static int openmax = OPEN_MAX;
#else
static int openmax = 0;
#endif

#define OPEN_MAX_GUESS   256

static int g_max_fd = 0;
static pid_t *childpid = NULL;

int open_max()
{
    if (openmax == 0) 
    {
        errno = 0;

        if((openmax = sysconf(_SC_OPEN_MAX)) < 0) 
        {
            if ( errno == 0 )
                openmax = OPEN_MAX_GUESS;
            else    
                printf("sysconf error for _SC_OPEN_MAX");
        }
    }

    return openmax;
}

FILE* my_popen(const char *pszCmdStr, const char *pszType)
{
    pid_t pid;
    int fd[2];
    FILE *pRet = NULL;
    
    if((pszType[0] != 'r' &&  pszType[0] != 'w') || pszType[1] != '\0')
    {
        printf("invalid pszType param!\n");
        return NULL;
    }

    // 
    if (!childpid)
    {
        g_max_fd = open_max();
        childpid = calloc(g_max_fd, sizeof(pid_t));
        if (!childpid)
        {
            return NULL;
        }
    }

    if (pipe(fd) < 0)
    {
        printf("pipe fd failed!\n");
        return NULL;
    }

    if ((pid = fork()) == 0)
    {
        if (pszType[1] == 'r')
        {
            close(fd[0]);
            if (fd[1] != STDOUT_FILENO)
            {
                dup2(fd[1], STDOUT_FILENO);
                close(fd[1]);
            }
        }
        else
        {
            close(fd[1]);
            if (fd[0] != STDIN_FILENO)
            {
                dup2(fd[0], STDIN_FILENO);
                close(fd[0]);
            }
        }

        execl("/bin/sh", "sh", "-c", pszCmdStr, NULL);
        exit(0);
    }
    else if(pid > 0)
    {
        if (pszType[0] == 'r')
        {
            close(fd[1]);
            if (!(pRet = fdopen(fd[0], pszType)))
            {
                printf("fdopen fd[0] failed!\n");
            }
        }
        else
        {
            close(fd[0]);
            if (!(pRet = fdopen(fd[1], pszType)))
            {
                printf("fdopen fd[0] failed!\n");
            }
        }

        childpid[fileno(pRet)] = pid;
    }
    else
    {
        printf("fork failed!\n");
    }

    return pRet;
}

int my_pclose(FILE *fp)
{
    pid_t pid;
    int fd = fileno(fp);
    int status;

    if (!childpid)
    {
        errno = EINVAL;
        return -1;
    }

    if (!(pid = childpid[fd]))
    {
        errno = EINVAL;
        return -1;
    }

    fclose(fp);
    childpid[fd] = 0;
    if (waitpid(pid, &status, 0) < 0)
    {
        printf("wait pid failed!\n");
        return -1;
    }
    
    return 0;
}
