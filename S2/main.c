#include  <stdio.h>
#include  <string.h>
#include  <sys/types.h>
#include  <unistd.h>
#include  <stdlib.h>
#include  <sys/wait.h>
#include <math.h>
#define   BUF_SIZE   100
#define FALSE 0
#define TRUE 1
#define ERROR "Error, you have to provide the N parameter.\n"
#define ERROR2 "Error, "
#define ERROR3 " is not a valid number of processes. N has to comply with the 2^M-1 formula.\n"
#define CREATING1 "Creating a "
#define CREATING2 " generations WaveTree ...\n"
int gotSIGCONT = FALSE;
/*
double log2(double x){
    return log(x) / log(2);
}*/

void sigcont_handler(){
    gotSIGCONT = TRUE;
}

int waveTree(int M, pid_t *child1, pid_t *child2){
    M = M-1;
    if(M <= 0)
        return M;

    char buf[BUF_SIZE];

    if ((*child1 = fork()) < 0) {
        sprintf(buf, "Failed to fork process 1\n");
        write(1, buf, strlen(buf));
        exit(1);
    }else if (*child1 > 0){
        //printf("child 1\n");
        //printf("child 1 of M: %d\n", M);

        return waveTree(M, child1, child2);
    }

    if ((*child2 = fork()) < 0) {
        sprintf(buf, "Failed to fork process 2\n");
        write(1, buf, strlen(buf));
        exit(1);
    }else if (*child2 > 0){
        return waveTree(M, child1, child2);
    }

    return M;
}

int main() {
    pid_t child1, child2;
    //signal(SIGALRM, sigalrm_handler);
    int M = 3;
    int auxM = waveTree(M, &child1, &child2)+1;
    signal(SIGCONT, sigcont_handler);

    printf("auxM = %d\n",auxM);
    fflush(stdout);

    if(M == auxM) {
        sleep(M);

        kill(child1, SIGCONT);
        kill(child2, SIGCONT);
        wait(NULL);
        wait(NULL);
    }else if(auxM < M && auxM > 1){

        while(gotSIGCONT == FALSE)
            pause();
        kill(child1, SIGCONT);
        kill(child2, SIGCONT);

        wait(NULL);
        wait(NULL);

    }else if(auxM == 1){
        while(gotSIGCONT == FALSE)
            pause();
    }

    char buf[BUF_SIZE];
    sprintf(buf, "I’m the generation %d and I finish the execution.\n", auxM);
    write(1, buf, strlen(buf));
    fflush(stdout);

    return 0;
}