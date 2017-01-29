#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>

FILE *my_popen(const char *pszCmdStr, const char *pszType);
int my_pclose(FILE *fp);
