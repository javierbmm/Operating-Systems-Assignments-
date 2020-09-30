/* @author: javier.merida
 * @author: olivia.rey
 */

#include <pthread.h>
#include "semaphore.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include<signal.h>

#define EATING 1
#define PLAYING 2
#define SLEEPING 3
#define LIVES 5
#define ERROR "Error, you need to specify the file you want to execute and the number of hamsters\n"

semaphore sem_eating;
semaphore sem_playing;
int num_hamsters;  // num of dead hamsters

void sighandler(){
    num_hamsters++;
    fflush(stdout);
}

// Print function for simple strings (NO %d %f %s etc)
void myprint(char* msg){
    char buffer[strlen(msg)+1];
    sprintf(buffer, "%s", msg);
    write(1, buffer, strlen(buffer));
}

void lifeCycle(int hamster){
    char buffer[50];

    SEM_wait(&sem_eating);
    sprintf(buffer, "Hamster %d eating!\n", hamster);
    myprint(buffer);
    sleep(EATING);
    SEM_signal(&sem_eating);

    SEM_wait(&sem_playing);
    sprintf(buffer, "Hamster %d playing!\n", hamster);
    myprint(buffer);
    sleep(PLAYING);
    SEM_signal(&sem_playing);

    sprintf(buffer, "Hamster %d sleeping!\n", hamster);
    myprint(buffer);
    sleep(SLEEPING);

    return;
}

int main (int argc, char *argv[]) {
    signal(SIGUSR1, sighandler);
    int hamsters;
    pid_t ppid = getpid();

    if (argc < 2) {
        write(1, ERROR, strlen(ERROR));
        exit(1);
    }

    num_hamsters = 0;
    hamsters = atoi(argv[1]);

    SEM_constructor(&sem_playing);
    SEM_init(&sem_playing, 3);

    SEM_constructor(&sem_eating);
    SEM_init(&sem_eating, 1);

    int i = 0;
    for (i = 0; i < hamsters; i++) {
        if (fork() == 0) { // CHILD
            int y = 0;
            for (y = 0; y < LIVES; y++) {
                lifeCycle(i);
            }
            kill(ppid, SIGUSR1);
            exit(EXIT_SUCCESS);
            myprint("u have a problem\n");  // unreached function
        }
    }

    if(getpid() == ppid) {
        while(1){
            if(num_hamsters >= hamsters)
                break;
        }

        myprint("Hamsters have died :D \n");
        SEM_destructor(&sem_eating);
        SEM_destructor(&sem_playing);
    }
    return 0;
}
