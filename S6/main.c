/*
 * @author: Olivia Rey
 * @login: olivia.rey
 *
 * @author: Javier Mérida
 * @login: javier.merida
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#define MSG_A "[PROCESS A]"
#define MSG_B "[PROCESS B]"
#define MSG_C "[PROCESS C]"

#define SHMSZ sizeof(int)*2
#define FALSE 0
#define TRUE 1
int received = FALSE;
void handle_sigusr1()
{
    received = TRUE;
}
int main() {
    signal(SIGUSR1, handle_sigusr1);
    // declaring variables for shared memory
    int shmid;
    key_t key = 5678;
    int *shm;
    // declaring variables for pipes
    int fd1[2];  // Used to store two ends of first pipe [A <-> B]
    int fd2[2];  // Used to store two ends of second pipe [A <-> C]

    // setting pipe
    if (pipe(fd1)==-1)
    {
        write(1, "pipe Failed" , strlen("pipe Failed"));
        exit(EXIT_FAILURE);
    }
    if (pipe(fd2)==-1)
    {
        write(1, "pipe Failed" , strlen("pipe Failed"));
        exit(EXIT_FAILURE);
    }
    // forks info
    pid_t p, p2;  // p for B, p2 for C
    p = fork();

    // number
    int N, M;

    if (p < 0)
    {
        write(1, "fork Failed" , strlen("fork Failed"));
        exit(EXIT_FAILURE);
    }else if (p > 0){
        p2 = fork();
        if (p2 < 0) {
            write(1, "fork Failed" , strlen("fork Failed"));
            exit(EXIT_FAILURE);
        }else if (p2 > 0){
            // PROCESS A
            while(1) {
                write(1, MSG_A, strlen(MSG_A));
                write(1, "Enter N\n", strlen("Enter N\n"));
                char buffer[50];
                read(0, buffer, sizeof(buffer));
                N = atoi(buffer);
                // send it to B
                if (N > 0 || N < 0) {
                    write(fd1[1], &N, sizeof(N));
                    read(fd2[0], &M, sizeof(M));
                    write(1, MSG_A, strlen(MSG_A));
                    sprintf(buffer,"N= %d received from C\n",M);
                    write(1, buffer, strlen(buffer));
                } else if (N == 0) {
                    write(fd1[1], &N, sizeof(N));
                    // ensure b and c finished
                    wait(NULL);
                    wait(NULL);

                    break;
                }
            }
        }else if(p2 == 0){
            // PROCESS C
            // setting shared memory
            /*
                * Locate the segment.
                */
            if ((shmid = shmget(key, SHMSZ, 0666)) < 0) {
                perror("shmget");
                exit(1);
            }

            /*
             * Now we attach the segment to our data space.
             */
            if ((shm = shmat(shmid, NULL, 0)) == (void *) -1) {
                perror("shmat");
                exit(1);
            }
            int *N2;
            char buffer[50];
            N2 = shm;
            N2++;
            while(1){
                while(received == FALSE)
                    ;

                if(*N2 > 0 || *N2 < 0){
                    write(1, MSG_C, strlen(MSG_C));
                    sprintf(buffer,"N= %d received from B\n",*N2);
                    write(1, buffer, strlen(buffer));
                    M = (*N2) * (*N2);
                    write(fd2[1], &M, sizeof(M));
                }else if(*N2 == 0){
                    break;
                }
                received = FALSE;
            }
            //detach from shared memory
            shmdt(shm);
            // destroy the shared memory
            shmctl(shmid,IPC_RMID,NULL);
        }
    }else if(p == 0){
        // PROCESS B
        // setting shared memory
        if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
            perror("shmget");
            exit(1);
        }

        /*
         * Now we attach the segment to our data space.
         */
        if ((shm = shmat(shmid, NULL, 0)) == (void *) -1) {
            perror("shmat");
            exit(1);
        }
        int *N2;
        char buffer[50];
        N2 = shm;
        N2++;

        while(1){
            read(fd1[0], &N, sizeof(N));

            if(N > 0 || N < 0){
                write(1, MSG_B, strlen(MSG_B));
                sprintf(buffer,"N= %d received from A\n",N);
                write(1, buffer, strlen(buffer));
                N = N*N;
                *N2 = N;

                kill(p, SIGUSR1);
            }else if(N == 0){
                *N2 = 0;
                kill(p, SIGUSR1);

                break;
            }
        }
        //detach from shared memory
        shmdt(shm);
    }

    close(fd1[0]);
    close(fd1[1]);
    close(fd2[1]);
    close(fd2[0]);

    return 0;
}