//
// Created by javif on 10/8/2019.
//

#include  <stdio.h>
#include  <string.h>
#include  <sys/types.h>
#include  <unistd.h>
#include <pthread.h>
#include  <stdlib.h>
#include  <sys/wait.h>
#include  <time.h>
#include <sys/syscall.h>

#define   BUF_SIZE   100
#define   FALSE 0
#define   TRUE 1
int t1_ready = FALSE;
int t2_ready = FALSE;

void handle_sigalrm();
void *thfun1();
void *thfun2();
void handle_sigint();

int main(){

    signal(SIGALRM, handle_sigalrm);
    signal(SIGINT, handle_sigint);

    alarm(5);

    pthread_t thread_id[2];
    pthread_create(&thread_id[0], NULL, thfun1, NULL);
    pthread_create(&thread_id[1], NULL, thfun2, NULL);

    // Waiting for threads to finish
    pthread_join(thread_id[0], NULL);
    pthread_join(thread_id[1], NULL);

    return 0;
}

void handle_sigint(){
    printf("this is sigint \n");

}
void handle_sigalrm(){
    char buffer[BUF_SIZE];
    pid_t TID = (pid_t) syscall (SYS_gettid);
    sprintf(buffer, "I'm a thread and this is my TID: %d\n", TID);
    write(1, buffer, strlen(buffer));
}

void *thfun1(){
    t1_ready = TRUE;
    while(t2_ready == FALSE)
        ;
    char buffer[BUF_SIZE];
    pid_t TID = (pid_t) syscall (SYS_gettid);
    sprintf(buffer, "Thread %d ready\n", TID);
    write(1, buffer, strlen(buffer));

    //signal(SIGALRM, handle_sigalrm);
   // alarm(3);
   //raise(SIGUSR1);
   pause();
   //raise(SIGUSR1);

}

void *thfun2(){
    t2_ready = TRUE;

    while(t1_ready == FALSE)
        ;
    char buffer[BUF_SIZE];
    pid_t TID = (pid_t) syscall (SYS_gettid);
    sprintf(buffer, "Thread %d ready\n", TID);
    write(1, buffer, strlen(buffer));
    
    pause();
}