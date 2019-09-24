//
// Created by javif on 9/22/2019.
//

#ifndef FIRSTPRACTICE1_DRIVERSMANAGER_H
#define FIRSTPRACTICE1_DRIVERSMANAGER_H
typedef struct{
    char* name;
    int sizeOfName;
    char* id;
    int hour;
    int min;
    int sec;
    float n_laps;
    char endline;
} Driver;

typedef struct{
    Driver* drivers;
    int size;  // Number of occurrences in the array
} DriverArray;

void showInfoPilot (DriverArray info) ;

DriverArray searchInfoPilot (char *name, Driver * drivers, int numberOfElements) ;

void showWinners (Driver * winners, int x) ;

void findWinners (Driver * drivers, Driver * winners) ; //pos 0 is for comp

void findMoreLaps(Driver* drivers, Driver *winners);

int compareTimes(Driver new, Driver old) ;

void storeInfo (DriverArray d) ;

#endif //FIRSTPRACTICE1_DRIVERSMANAGER_H
