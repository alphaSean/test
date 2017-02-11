#include <unistd.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#define SHM_SIZE 100000
#define SHM_FLAG 0600

#define ARRAY_SIZE 40000
#define MALLOC_SIZE 100000

char array[ARRAY_SIZE];

int main(int argc, char** argv)
{
    int shmid;
    char *ptr, *shmptr;

    printf("array[] from %p to %p\n", (void*)&array[0],
            (void*)&array[ARRAY_SIZE]);
    printf("stack around %p\n", (void*)&shmid);

    if (!(ptr = malloc(MALLOC_SIZE)))
    {
        printf("malloc error!\n");
        return -1;
    }

    printf("malloc from %p to %p\n", (void*)&ptr,
            (void*)&ptr+MALLOC_SIZE);

    if ((shmid = shmget(IPC_PRIVATE, SHM_SIZE, SHM_FLAG)) == -1)
    {
        printf("shmget failed! errno = %d\n", errno);
        return -1;
    }

    if ((shmptr = shmat(shmid, 0, 0)) == (void*)-1)
    {
        printf("shmat failed! error = %d\n", errno);
        return -1;
    }

    printf("shared memory attached from %p to %p \n", (void*)shmptr,
            (void*)shmptr + SHM_SIZE);

    if ( shmdt(shmptr) == -1)
    {
        printf("shmdt failed! errno = %d\n", errno);
        return -1;
    }
/*
    if (shmctl(shmid, IPC_RMID, 0) < 0)
    {
        printf("shmctl error! errorno = %d\n", errno);
        return -1;
    }
*/
    return 0;
}
