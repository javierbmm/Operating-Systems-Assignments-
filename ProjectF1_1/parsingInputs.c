//
// Created by Olívia Rey Pellicer on 25/10/2019.
//

#include "parsingInputs.h"
#define SHOWCONNECTIONS "SHOW CONNECTIONS"
#define CONNECT "CONNECT"
#define SAY "SAY"
#define BROADCAST "BROADCAST"
#define SHOWAUDIOS "SHOW AUDIOS"
#define DOWNLOAD "DOWNLOAD"
#define EXIT "EXIT"
#define ERRORCOMMAND "ERROR! Not valid command."


int parseInput(char *user) {
    char *aux;
    aux = user;
    aux[strlen(SHOWCONNECTIONS)] = '\0';
    if (strcasecmp(aux, SHOWCONNECTIONS)) {
        return 0;
    } else {
        aux = user;
        aux[strlen(CONNECT)] = '\0';
        if (strcasecmp(aux, CONNECT)) {
            return 1;
        } else {
            aux = user;
            aux[strlen(SAY)] = '\0';
            if (strcasecmp(aux, CONNECT)) {
                return 2;
            } else {
                aux = user;
                aux[strlen(BROADCAST)] = '\0';
                if (strcasecmp(aux, BROADCAST)) {
                    return 3;
                } else {
                    aux = user;
                    aux[strlen(SHOWAUDIOS)] = '\0';
                    if (strcasecmp(aux, SHOWAUDIOS)) {
                        return 4;
                    } else {
                        aux = user;
                        aux[strlen(DOWNLOAD)] = '\0';
                        if (strcasecmp(aux, DOWNLOAD)) {
                            return 5;
                        } else {
                            aux = user;
                            aux[strlen(EXIT)] = '\0';
                            if (strcasecmp(aux, EXIT)) {
                                return 6;
                            } else {
                                write(1, ERRORCOMMAND, strlen(ERRORCOMMAND));
                            }
                        }
                    }
                }
            }
        }
    }
}