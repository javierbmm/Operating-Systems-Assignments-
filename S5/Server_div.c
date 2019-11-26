//
// @Author: Olivia Rey
// @Login: olivia.rey
// @Author: Javier Mérida
// @Login: javier.merida
//
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <string.h>

#define MAX_SIZE 50


// Print function for simple strings (NO %d %f %s etc)
void myprint(char* msg){
    char buffer[MAX_SIZE];
    sprintf(buffer, "%s", msg);
    write(1, buffer, strlen(buffer));
}

int main(int argc, char *argv[])
{
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr;

    char sendBuff[1025];

    if(argc != 2){
        myprint("ERROR: incorrect number of parameters");
        exit(EXIT_FAILURE);
    }
    /* creates an UN-named socket inside the kernel and returns
     * an integer known as socket descriptor
     * This function takes domain/family as its first argument.
     * For Internet family of IPv4 addresses we use AF_INET
     */
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("0.0.0.0");
    serv_addr.sin_port = htons(atoi(argv[1]));

    /* The call to the function "bind()" assigns the details specified
     * in the structure 'serv_addr' to the socket created in the step above
     */
    if(bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
        myprint("ERROR: bind error\n");
        exit(EXIT_FAILURE);
    }
    /* The call to the function "listen()" with second argument as 10 specifies
     * maximum number of client connections that server will queue for this listening
     * socket.
     */
    if(listen(listenfd, 100) == -1) {
        myprint("ERROR: listen error\n");
        close(listenfd);
        exit(EXIT_FAILURE);
    }

    char rwBuffer[500];
    float ioNumber = 0, result = 0;
    /* In the call to accept(), the server is put to sleep and when for an incoming
 * client request, the three way TCP handshake* is complete, the function accept()
 * wakes up and returns the socket descriptor representing the client socket.
 */

    connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
    while(1)
    {
        // First float
        read(connfd, &ioNumber, sizeof(ioNumber));
        result = ioNumber;
        // Ignoring middle char
        read(connfd, rwBuffer, 1);
        // Second float
        read(connfd, &ioNumber, sizeof(ioNumber));
        result /= ioNumber;

        if(strncmp(rwBuffer, "s", 1) == 0 && result == 1) {
            myprint("Bye!\n");
            break;
        }
        // Sending result
        write(connfd, &result, sizeof(result));


    }

    close(listenfd);
    close(connfd);
}

