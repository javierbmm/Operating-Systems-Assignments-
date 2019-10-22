//
// Created by Javier Mérida  on 10/20/2019.
//
// This program return the maximum number of threads that can be created, using Linux as OS.
// I didn't created this code. I just copypasted from GeeksForGeeks. For more information, visit:
// https://www.geeksforgeeks.org/maximum-number-threads-can-created-within-process-c/
// Also note that the number of pthreads created by this program should be the same as the output of
// "cat /proc/sys/kernel/threads-max" command. I strongly recommend to try the command before executing this program.
// NOTE: For compiling, please use: gcc maxthreads.c -pthread -o maxthreads

#include<stdio.h>
#include<pthread.h>

// This function demonstrates the work of thread
// which is of no use here, So left blank
void *thread ( void *vargp){     }

int main()
{
    int err = 0, count = 0;
    pthread_t tid;

    // on success, pthread_create returns 0 and
    // on Error, it returns error number
    // So, while loop is iterated until return value is 0
    while (err == 0)
    {
        err = pthread_create (&tid, NULL, thread, NULL);
        count++;
    }
    printf("Maximum number of thread within a Process"
           " is : %d\n", count);
}