#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

#define RESULT "THE RESULT IS: "
#define MENU "DISTRIBUTED COMPUTED MENU.\n1. Input new operation.\n2. Exit.\n\nSelect a valid option:"
#define ERROR "INCORRECT OPTION.\n"
#define ERROR_I " ITHE INPUT PROVIDED IS INVALID. PLEASE TRY AGAIN...\n"

float getResult(int socket, float numberOne, float numberTwo, char delimiter){
    write(socket, &numberOne, sizeof(numberOne));
    write(socket, &delimiter, sizeof(delimiter));  // '-'
    write(socket, &numberTwo, sizeof(numberTwo));

    float result;
    read(socket, &result, sizeof(result));

    return result;
}

int exitServer(int socket){
    write(socket, "6s6", 3);

    int result;
    read(socket, &result, sizeof(result));

    return result;
}
int main(int argc, char *argv[]) {

    int sockfd = 0, sockfd2 = 0, n = 0;
    char recvBuff[1024];
    struct sockaddr_in mult_serv, div_serv;

    if(argc != 3)
    {
        printf("\n Usage: %s <ip of server> \n",argv[0]);
        return 1;
    }

    memset(recvBuff, '0',sizeof(recvBuff));

    // Server_mult connection:
    /* a socket is created through call to socket() function */
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        write (1, "\n Error : Could not create socket \n", strlen("\n Error : Could not create socket \n"));
        return 1;
    }

    memset(&mult_serv, '0', sizeof(mult_serv));

    mult_serv.sin_family = AF_INET;
    mult_serv.sin_port = htons(atoi(argv[2]));

    if(inet_pton(AF_INET, argv[1], &mult_serv.sin_addr)<=0)
    {
        write (1,"\n inet_pton error occured\n", strlen ("\n inet_pton error occured\n"));
        return 1;
    }

    /* Information like IP address of the remote host and its port is
     * bundled up in a structure and a call to function connect() is made
     * which tries to connect this socket with the socket (IP address and port)
     * of the remote host
     */
    if( connect(sockfd, (struct sockaddr *)&mult_serv, sizeof(mult_serv)) < 0)
    {
        write (1, "\n Error : Connect Failed \n", strlen ("\n Error : Connect Failed \n"));
        return 1;
    }

    // Serv_div connection:
    /* a socket is created through call to socket() function */
    if((sockfd2 = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    }

    memset(&div_serv, '0', sizeof(div_serv));

    div_serv.sin_family = AF_INET;
    div_serv.sin_port = htons(atoi(argv[2])+1);

    if(inet_pton(AF_INET, argv[1], &div_serv.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
        return 1;
    }

    /* Information like IP address of the remote host and its port is
     * bundled up in a structure and a call to function connect() is made
     * which tries to connect this socket with the socket (IP address and port)
     * of the remote host
     */
    if( connect(sockfd2, (struct sockaddr *)&div_serv, sizeof(div_serv)) < 0)
    {
        printf("\n Error : Connect Failed \n");
        return 1;
    }
    /* Once the sockets are connected, the server sends the data (date+time)
     * on clients socket through clients socket descriptor and client can read it
     * through normal read call on the its socket descriptor.
     */

/////////////////////////////////////////////////////////////
    char aux [20];
    char option[20];
    char result_c [20];
    int i = 0, o = 0, error = 0;
    float result = 1;
    int step = 0, div = 0, mult = 0;
    float firstNumber, secondNumber;
    char delimiter = '-';
    char buffer[20], buffer_msg[1000];
    aux [0] = '\0';

    do {
        do {
            write (1, MENU, strlen(MENU));
            read (1, option, 20);
            o = atoi(option);
            if (o < 1 || o > 2) {
                write (1, ERROR, strlen(ERROR));
            }
        } while (o < 1 || o > 2);

        if (o == 1) {

            while ( (n = read(0, buffer, sizeof(20)) > 0)) {
                if (step == 0) {
                    firstNumber = atof(buffer);
                    step++;
                } else if (step == 1) {
                    if(buffer[0] == '*'){
                        mult = 1;
                    }else if(buffer[0] == '/'){
                        div = 1;
                    }else{
                        sprintf(buffer_msg,"The input provided is invalid, try again");
                        write(1, buffer, strlen(buffer));
                    }
                    step++;
                } else if (step == 2) {
                    secondNumber = atof(buffer);
                    if (div == 1) {
                        result = getResult(sockfd2, firstNumber, secondNumber, delimiter);
                        div = 0;
                    } else if (mult == 1) {
                        result = getResult(sockfd, firstNumber, secondNumber, delimiter);
                        mult = 0;
                    }
                    step = 1;
                    firstNumber = result;
                }
                    if ( buffer[0] == '=') {
                        sprintf(buffer_msg, "The result is: %f", result);
                        break;
                    }
                    // Empty-ing the buffer
                    memset(buffer,0,sizeof(buffer));

                }

                i++;
                if (error == 1) {
                    write (1, ERROR_I, strlen(ERROR_I));
                }
                read(0, aux, 20);

            }

            write(1, RESULT, strlen(RESULT));
            sprintf(result_c, "%f", result);
            write (1, result_c, strlen(result_c));
            write (1, "\n", strlen ("\n"));

    } while (o != 2);
    write (1, "Exiting the program...\n", strlen ("Exiting the program...\n"));

    while(exitServer(sockfd) != 0)
        ;
    while(exitServer(sockfd2) != 0)
        ;
    close(sockfd);
    close(sockfd2);
    return 0;
}