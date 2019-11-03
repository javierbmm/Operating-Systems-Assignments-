//
// Created by Olívia Rey Pellicer on 25/10/2019.
//

#include "commandsActions.h"

#define SHOWCONNECTIONS "SHOW CONNECTIONS"
#define CONNECT "CONNECT"
#define SAY "SAY"
#define BROADCAST "BROADCAST"
#define SHOWAUDIOS "SHOW AUDIOS"
#define DOWNLOAD "DOWNLOAD"
#define EXIT "EXIT"
#define ERRORCOMMAND "ERROR! Not valid command."
#define TESTING "Testing..."
#define NOCONNECTIONS "No conntections available.\n"
#define COULDNTCONNECT "Could not connect to the port.\n"

void getCommand(int i, char * user) {
    int j = 0, k = 0;
    char * aux, *text, *port, *user2, *audio;
    int port;
    switch (i) {
        case 0:
            write(1, TESTING, strlen(TESTING));
            write(1, NOCONNECTIONS, strlen(NOCONNECTIONS));
            break;
        case 1:
            j = strlen(CONNECT) + 1;
            k = 0;
            while (user[j] > '0' && user[j] < '9') {
                port[k] = user[j];
                k++;
                j++;
            }
            port[k] = '\0';
            sprintf(aux, NULL, port);
            write(1, COULDNTCONNECT, strlen(COULDNTCONNECT));

            break;
        case 2:
            j = strlen(SAY) + 1;
            k = 0;
            while (user[j] > '0' && user[j] < '9') {
                user2[k] = user[j];
                k++;
                j++;
            }
            user2[k] = '\0';
            while (user[j] != '"') {
                j++;
            }
            j++;
            k = 0;
            while (user[j] != '"') {
                text[k] = user[j];
                j++;
                k++;
            }
            text[k] = '\0';
            write(1, NOCONNECTIONS, strlen(NOCONNECTIONS));

            break;
        case 3:
            j = strlen(BROADCAST);
            while (user[j] != '"') {
                j++;
            }
            k = 0;
            while (user[j] != '"') {
                text[k] = user[j];
                j++;
                k++;
            }
            text[k] = '\0';
            write(1, NOCONNECTIONS, strlen(NOCONNECTIONS));

            break;
        case 4:
            j = strlen(SHOWAUDIOS) + 1;
            k = 0;
            while (user[j] > '0' && user[j] < '9') {
                user2[k] = user[j];
                k++;
                j++;
            }
            aux[k] = '\0';
            write(1, NOCONNECTIONS, strlen(NOCONNECTIONS));

            break;
        case 5:
            j = strlen(DOWNLOAD) + 1;
            while (user[j] != ' ') {
                user2[k] = user[j];
                k++;
                j++;
            }
            user2[k] = '\0';
            j++;
            while (user[j] != ' ') {
                audio[k] = user[j];
                k++;
                j++;
            }
            audio[k] = '\0';
            write(1, NOCONNECTIONS, strlen(NOCONNECTIONS));

            break;

    }
}