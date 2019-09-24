//
// Created by javif on 9/22/2019.
//

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
// Own libraries
#include <driversManager.h>
#include <stringmanipulation.h>
#include "driversManager.h"

#define OPTION4 "All information for "
#define OPTION42 "has been stored in"
#define NAME "Name: "
#define COMPETITION "Competition:"
#define LAPS " laps"
#define PILOTSEARCH "Which pilot do you want to look for?"
#define PILOTSEARCH2 "Name of the pilot: "
#define FASTEST "\nThe fastest pilot in "
#define FASTEST2 " is : \n\t"
#define LAPSWINNER "\nThe pilot with more laps in "
#define LAPSWINNER2 " is : \n\t"
#define ERROR "Error!"
#define EOL "\n"
#define TAB "\t"


DriverArray searchInfoPilot (char *name, Driver * drivers, int numberOfElements) {
    Driver* container = calloc(0, sizeof(Driver));
    int numOfComp = 0;
    for (int i = 0; i < numberOfElements; i++) {
        if ( (strncmp( name, drivers[i].name, drivers[i].sizeOfName)) == 0) {
            numOfComp++;
            container = (Driver*)realloc(container, sizeof(Driver)*numOfComp);
            container[numOfComp-1] = drivers[i];
        }
    }
    DriverArray infoOfPilot = { container, numOfComp};
    return infoOfPilot;
}

void showInfoPilot(DriverArray info) {
    if(info.size < 1 || info.drivers == NULL) // Check if the pointers array is empty
        // TODO: Print error message
        return;
    write (1, NAME, sizeof(NAME));
    write(1, info.drivers[0].name, info.drivers[0].sizeOfName);
    write(1, EOL, 1);

    int i;
    for(i = 0; i<info.size; i++){
        write (1, COMPETITION, sizeof(COMPETITION));
        write (1, info.drivers[i].id, 2);
        write(1, EOL, 1);
        char buffer[10];
        snprintf(buffer, 3, "%d",info.drivers[i].hour);
        write(1, TAB, 1);
        write (1, buffer, strlen(buffer));
        write (1, ":", sizeof(":"));
        snprintf(buffer, 3, "%d",info.drivers[i].min);
        write (1, buffer, strlen(buffer));
        write (1, ":", sizeof(":"));
        snprintf(buffer, 3, "%d",info.drivers[i].sec);
        write (1, buffer, strlen(buffer));
        write(1, EOL, 1);
        snprintf(buffer, 10, "%.2f",info.drivers[i].n_laps);
        write(1, TAB, 1);
        write (1, buffer, strlen(buffer));
        write (1, LAPS, sizeof(LAPS));
        write(1, EOL, 1);

        fflush(stdout);
    }
}

void showWinners (Driver * winners, int x) {
    int i = 0;

    if (x) {
        for ( i = 0; i < 3 ; i ++) {
            write (1, LAPSWINNER, sizeof(LAPSWINNER));
            write (1, winners[i].id, strlen(winners[i].id));
            write (1, LAPSWINNER2, sizeof(LAPSWINNER2));
            write (1, winners[i].name, strlen(winners[i].name));
        }
    } else{
        for ( i = 0; i < 3 ; i ++) {
            write (1, FASTEST, sizeof(FASTEST));
            write (1, winners[i].id, strlen(winners[i].id));
            write (1, FASTEST2, sizeof(FASTEST2));
            write (1, winners[i].name, strlen(winners[i].name));
        }
    }
}

void findWinners (Driver * drivers, Driver * winners) { //pos 0 is for comp
    unsigned int i =0, r = 0, win = 1;
    winners[r] = drivers[i];
    for (i = 1; i< sizeof(drivers); i++) {
        if (drivers[i].id == winners[0].id && win == 1) {
            if (compareTimes(drivers[i], winners[0])) {
                winners[0] = drivers[i];
            }
        } else {
            if (win > 1) {
                if (drivers[i].id == winners[1].id) {
                    if (compareTimes(drivers[i], winners[1])) {
                        winners[1] = drivers[i];
                    }
                } else {
                    if (win > 2) {
                        if (drivers[i].id == winners[2].id) {
                            if (compareTimes(drivers[i], winners[2])) {
                                winners[2] = drivers[i];
                            }
                        }
                    } else{
                        winners[2] = drivers[i];
                        win++;
                    }
                }
            } else {
                winners[1] = drivers[i];
                win++;
            }
        }
    }
}
int compareTimes(Driver new, Driver old) {
    if (new.hour < old.hour) {
        return 1;
    } else{
        if (new.hour>old.hour) {
            return 0;
        } else{
            if (new.min < old.min) {
                return 1;
            } else{
                if (new.min > old.min) {
                    return 0;
                } else{
                    if (new.sec < old.sec) {
                        return 1;
                    } else{
                        return 0;
                    }
                }
            }
        }
    }
}

void findMoreLaps(Driver* drivers, Driver *winners){
    Driver *winner1 = NULL, *winner2 = NULL, *winner3 = NULL;
    char comp1[3] = "F1\0", comp2[3] = "GP\0", comp3[3] = "RL\0";
    unsigned int i;
    for (i = 0; i < sizeof(drivers); i++) {

        // F1 Competition
        if(strcmp(comp1, drivers[i].id) == 0){
            if(winner1 == NULL){
                winner1 = &drivers[i];
            }else if(winner1->n_laps < drivers[i].n_laps){
                winner1 = &drivers[i];
            }
        }

        // GP Competition
        if(strcmp(comp2, drivers[i].id) == 0){
            if(winner2 == NULL){
                winner2 = &drivers[i];
            }else if(winner2->n_laps < drivers[i].n_laps){
                winner2 = &drivers[i];
            }
        }

        // RL Competition
        if(strcmp(comp3, drivers[i].id) == 0){
            if(winner3 == NULL){
                winner3 = &drivers[i];
            }else if(winner3->n_laps < drivers[i].n_laps){
                winner3 = &drivers[i];
            }
        }
    } // end for

    winners = realloc(winners, sizeof winners * 3);
    if(winner1)
        winners[0] = *winner1;
    if(winner2)
        winners[1] = *winner2;
    if(winner3)
        winners[2] = *winner3;
}
void storeInfo (DriverArray d) {
    int f;
    if(d.size < 1 || d.drivers == NULL) // Check if the pointer array is empty
        // TODO: Print error message
        return;
    char* pilotName = (char*)malloc(sizeof(char)*d.drivers[0].sizeOfName);
    strcpyexcept(d.drivers[0].name, pilotName, ' ', '_');
    char* s = strcat(pilotName, "-results.txt");
    f = open( s, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU | S_IRWXG | S_IRWXO);
    if (f <0) {
        write(1, ERROR, sizeof(ERROR));
    } else {
        write(f, d.drivers[0].name, d.drivers[0].sizeOfName);
        write(f, "-", 1);
        int i;
        for(i = 0; i<d.size; i++) {
            write(f, d.drivers[i].id, 2);
            write(f, "-", 1);
            char buffer[10];
            snprintf(buffer, 3, "%d", d.drivers[i].hour);
            write(f, buffer, strlen(buffer));
            write(f, ":", sizeof(":"));
            snprintf(buffer, 3, "%d", d.drivers[i].min);
            write(f, buffer, strlen(buffer));
            write(f, ":", sizeof(":"));
            snprintf(buffer, 3, "%d", d.drivers[i].sec);
            write(f, buffer, strlen(buffer));
            write(f, "-", 1);
            snprintf(buffer, 10, "%.2f", d.drivers[i].n_laps);
            write(f, buffer, strlen(buffer));
            write(f, "/", 1);
        }
        close(f);
        write (1, OPTION4, sizeof(OPTION4));
        write (1, OPTION42, sizeof(OPTION42));
    }
}