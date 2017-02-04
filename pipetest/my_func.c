#include <unistd.h>
#include "my_func.h"


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
    else
    {
        pr_exit(status);
    }
    
    return 0;
}

Sigfunc my_signal(int signo, Sigfunc func)
{
    struct sigaction act, oact;
    act.sa_handler = func;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    if (signo == SIGALRM)
    {
#ifdef SA_INTERRUPT
        act.sa_flags |= SA_INTERRUPT;
#endif
    }
    else
    {
#ifdef SA_RESTART
        act.sa_flags |= SA_RESTART;
#endif
    }

    if (sigaction(signo, &act, &oact) < 0)
    {
        return SIG_ERR;
    }
    return oact.sa_handler;
}

void pr_exit(int status)
{
    if (WIFEXITED(status))
    {
        printf("nomal terminaltion, exit status = %d\n", 
                WEXITSTATUS(status));
    }
    else if(WIFSIGNALED(status))
    {
        printf("abnormal termination, signal number = %d%s\n",
                WTERMSIG(status),
#ifdef WCOREDUMP
                WCOREDUMP(status) ? " (core file generated)" : "");
#else
            "");
#endif
    }
    else if(WIFSTOPPED(status))
    {
        printf("child stopped, signal number = %d\n", 
                WSTOPSIG(status));
    }
}
