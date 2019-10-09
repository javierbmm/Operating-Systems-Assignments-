#include  <stdio.h>
#include  <string.h>
#include  <sys/types.h>
#include  <unistd.h>
#include <pthread.h>
#include  <stdlib.h>
#include  <sys/wait.h>
#include  <time.h>

#define   MAX_COUNT  200
#define   BUF_SIZE   100

int main(void)
{
    pid_t   pid1, pid2, pid;
    int     status;
    char    buf[BUF_SIZE];

    sprintf(buf, "*** Parent is about to fork process 1 ***\n");
    write(1, buf, strlen(buf));
    if ((pid2 = fork()) < 0) {
        sprintf(buf, "Failed to fork process 2\n");
        write(1, buf, strlen(buf));
        exit(1);
    }
    else if (pid2 == 0) {
        execv("second", NULL);
    }


    sprintf(buf, "*** Parent enters waiting status .....\n");
    write(1, buf, strlen(buf));
    pid = wait(&status);
    sprintf(buf, "Done!\nBye :) \n");
    write(1, buf, strlen(buf));
    return 0;
}
