#include <unistd.h>
#include "my_func.h"

char buf[500000];

int main()
{
    int ntowrite, nwrite;
    char *ptr;

    ntowrite = read(STDIN_FILENO, buf, sizeof(buf));
    fprintf(stderr, "read %d bytes\n", ntowrite);

    set_f1(STDOUT_FILENO, O_NONBLOCK);

    ptr = buf;
    while(ntowrite > 0)
    {
        errno = 0;
        nwrite = write(STDOUT_FILENO, ptr, ntowrite);
        fprintf(stderr, "nwrite = %d, errno = %d\n",
                nwrite, errno);

        if (nwrite > 0)
        {
            ptr += nwrite;
            ntowrite -= nwrite;
        }
    }

    clr_f1(STDOUT_FILENO, O_NONBLOCK);
    exit(0);
}
