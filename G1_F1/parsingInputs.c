//
// Created by Olívia Rey Pellicer on 25/10/2019.
//
#include <parsingInputs.h>

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>




int parseInput(char *user) {
    char *aux = malloc(strlen(user)+1);
    aux = strcpy(aux, user);
    aux[strlen(SHOWCONNECTIONS)] = '\0';
    if (strcasecmp(aux, SHOWCONNECTIONS) == 0) {
        return 0;
    } else {
        aux = strcpy(aux, user);
        aux[strlen(CONNECT)] = '\0';
        if (strcasecmp(aux, CONNECT) == 0) {
            return 1;
        } else {
            aux = strcpy(aux, user);
            aux[strlen(SAY)] = '\0';
            if (strcasecmp(aux, CONNECT) == 0) {
                return 2;
            } else {
                aux = strcpy(aux, user);
                aux[strlen(BROADCAST)] = '\0';
                if (strcasecmp(aux, BROADCAST) == 0) {
                    return 3;
                } else {
                    aux = strcpy(aux, user);
                    aux[strlen(SHOWAUDIOS)] = '\0';
                    if (strcasecmp(aux, SHOWAUDIOS) == 0) {
                        return 4;
                    } else {
                        aux = strcpy(aux, user);
                        aux[strlen(DOWNLOAD)] = '\0';
                        if (strcasecmp(aux, DOWNLOAD) == 0) {
                            return 5;
                        } else {
                            aux = strcpy(aux, user);
                            aux[strlen(EXIT)] = '\0';
                            if (strcasecmp(aux, EXIT) == 0) {
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

    free(aux);

    return -1;  // -1 for errors
}
