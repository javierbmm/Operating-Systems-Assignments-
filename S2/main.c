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
    }else if (*child1 == 0){
        //printf("child 1\n");
        //printf("child 1 of M: %d\n", M);

        return waveTree(M, child1, child2);
    }

    if ((*child2 = fork()) < 0) {
        sprintf(buf, "Failed to fork process 2\n");
        write(1, buf, strlen(buf));
        exit(1);
    }else if (*child2 == 0){
        return waveTree(M, child1, child2);
    }

    return M;
}

int main(int arg, const char* argv[]) {
    int n, m;
    char buff [100], aux[100];
    sprintf(aux, "%d", arg);
    if (arg != 2) {
        write (1, ERROR, strlen(ERROR));
        return 0;
    }
    n = atoi(argv[1]);
    if (round(log2(n+1)) != log2(n+1)) {
        write (1, ERROR2, strlen(ERROR2));
        write (1, argv[1], strlen(argv[1]));
        write(1, ERROR3, strlen(ERROR3));
        return 0;
    }
    m = log2(n)+1;
    sprintf(buff, "%d", m);
    write(1, CREATING1, strlen(CREATING1));
    write(1, buff, strlen(buff));
    write(1, CREATING2, strlen(CREATING2));

    pid_t child1, child2;
    //signal(SIGALRM, sigalrm_handler);
    pid_t wpid;
    int M = m;
    int auxM = waveTree(M, &child1, &child2)+1;
    signal(SIGCONT, sigcont_handler);

    //printf("auxM = %d\n", M - auxM + 1);
    fflush(stdout);

    if(M == auxM) {
        sleep(M);

        kill(child1, SIGCONT);
        kill(child2, SIGCONT);
        while((wpid = wait(NULL) > 0))
            ;

    }else if(auxM < M && auxM > 1){
        pause();
        while(gotSIGCONT == FALSE)
            pause();
        kill(child1, SIGCONT);
        kill(child2, SIGCONT);

        while((wpid = wait(NULL) > 0))
            ;
    }else if(auxM == 1){
        pause();
        while(gotSIGCONT == FALSE)
            pause();
    }
    //sleep((M - auxM + 1)*4);
    char buf[BUF_SIZE];
    sprintf(buf, "I’m the generation %d and I finish the execution.\n", M - auxM + 1);
    write(1, buf, strlen(buf));
    fflush(stdout);
    exit(0);
    return 0;
}