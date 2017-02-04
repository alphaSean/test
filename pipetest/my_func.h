#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>

typedef void (*Sigfunc)(int);

void pr_exit(int status);
FILE *my_popen(const char *pszCmdStr, const char *pszType);
int my_pclose(FILE *fp);
Sigfunc my_signal(int signo, Sigfunc func);
