//
// Created by javif on 11/14/2019.
//

#include "common.h"

int main(int argc, char *argv[])
{
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr;

    char sendBuff[1025];
    time_t ticks;

    /* creates an UN-named socket inside the kernel and returns
     * an integer known as socket descriptor
     * This function takes domain/family as its first argument.
     * For Internet family of IPv4 addresses we use AF_INET
     */
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);
    serv_addr.sin_port = htons(SERVER_PORT);

    /* The call to the function "bind()" assigns the details specified
     * in the structure 'serv_addr' to the socket created in the step above
     */
    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    /* The call to the function "listen()" with second argument as 10 specifies
     * maximum number of client connections that server will queue for this listening
     * socket.
     */
    listen(listenfd, 100);
    char rwBuffer[500];
    /* In the call to accept(), the server is put to sleep and when for an incoming
 * client request, the three way TCP handshake* is complete, the function accept()
 * wakes up and returns the socket descriptor representing the client socket.
 */
    connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
    while(1)
    {
        read(0, rwBuffer, sizeof(rwBuffer)-1);
        write(connfd, rwBuffer, strlen(rwBuffer));
        myprint(rwBuffer);
        if(strncmp(rwBuffer, "EXIT", 4) == 0)
            break;
        sleep(1);
    }

    /*
    int i;
    for(i=0; i<num_of_threads; i++){
        pthread_kill(thread_ids[i], SIGTERM);
        sleep(2);
        pthread_join(thread_ids[i], NULL);
    }*/

    close(listenfd);
}

