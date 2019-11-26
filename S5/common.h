//
// Created by javif on 11/14/2019.
//

#ifndef S5_COMMON_H
#define S5_COMMON_H

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

#define MAX_SIZE 500
#define SERVER_PORT 5000
char SERVER_ADDRESS[] = "127.0.0.1";

typedef struct{
    int packet_id;
    int sizeof_packet;
    char* msg;
}packet;

// Print function for simple strings (NO %d %f %s etc)
void myprint(char* msg){
    char buffer[MAX_SIZE];
    sprintf(buffer, "%s", msg);
    write(1, buffer, strlen(buffer));
}
#endif //S5_COMMON_H
