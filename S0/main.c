#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
// Own libraries:
#include <driversManager.h>
#include <fileManager.h>

#define EOL "\n"
#define MENU "Menu:\n"
#define MENU1 "1. Search information of a pilot.\n"
#define MENU2 "2. Find fastest driver in the competition.\n"
#define MENU3 "3. Find the driver with more laps in the competition.\n"
#define MENU4 "4. Store information of the pilot.\n"
#define MENU5 "5. Exit the program\n"
#define NAME "Name: "
#define COMPETITION "Competition: "
#define LAPS " laps"
#define PILOTSEARCH "Which pilot do you want to look for?"
#define PILOTSEARCH2 "Name of the pilot: "
#define FASTEST "The fastest pilot in "
#define FASTEST2 "is : "
#define LAPSWINNER "The pilot with more laps in "
#define LAPSWINNER2 "is : "
#define ERROR "Error!"
#define OPTIONERROR "Error, you must select an option between 1-5.\n"
#define OPTION4 "All information for "
#define OPTION42 "has been stored in"

int main() {
    int file;
    file = open("info.dat", O_RDONLY);

    void *line = calloc(0,0);
    int sizeOfLine = 0;

    Driver * drivers = calloc(0,sizeof(Driver));
    int i = 0;
    char * namePilot = (char*)malloc(sizeof(char)*100);
    char option = '0', aux;
    Driver * winners = (Driver*) malloc (3*sizeof(Driver));//matrix to define on each slot, the competition and the winner
    //F.E: winners[0][0] is the competition, [0][1] is the winner...
    int numberOfElements = 0;
    while( (sizeOfLine = readPilotName(file, line) ) > 0) {
        numberOfElements++;
        drivers = realloc(drivers,sizeof(Driver)*numberOfElements);
        // Pilot name:
        char* pilotName = (char*)malloc(sizeof(char)*(sizeOfLine+1));
        strncpy(pilotName, (char*)line, sizeOfLine);
        pilotName[sizeOfLine] = '\n';
        drivers[i].name = pilotName;
        drivers[i].sizeOfName = sizeOfLine;
        skipDelimiter(file, '-');
        // Competition ID:
        readPilotName(file, line);
        char* compID = (char*)malloc(sizeof(char)*(3)); // 2 characters plus '\0'
        compID[0] = ((char*)line)[0];
        compID[1] = ((char*)line)[1];
        compID[2] = '\0';
        drivers[i].id = compID;
        skipDelimiter(file, '-');

        // Hour/s :
        sizeOfLine = readUntilLimit(file, line, ':');
        int hours = *(int*)line;
        drivers[i].hour = hours;

        read(file,line,1);
        // Minutes:
        sizeOfLine = readUntilLimit(file, line, ':');
        int min = *(int*)line;
        drivers[i].min = min;
        read(file,line,1);
        // Seconds:
        sizeOfLine = readUntilLimit(file, line, '-');
        int secs = *(int*)line;
        drivers[i].sec = secs;

        read(file,line,1);

        // Number of laps:
        float* auxLaps = malloc(sizeof*auxLaps *1);
        sizeOfLine = read(file, auxLaps, sizeof*auxLaps);
        drivers[i].n_laps = *auxLaps;
        free(auxLaps);
        auxLaps = NULL;

       //readUntilLimit(file, line, '/');
        skipDelimiter(file, '/');
        i++;

    }
    do {
        write (1, MENU, sizeof(MENU));
        write (1, MENU1, sizeof(MENU1));
        write (1, MENU2, sizeof(MENU2));
        write (1, MENU3, sizeof(MENU3));
        write (1, MENU4, sizeof(MENU4));
        write (1, MENU5, sizeof(MENU5));

        read (0, &option, sizeof(option));
        read ( 0, &aux, 1); // getting over the enter
        switch (option) {
            case '1':
                write(1, PILOTSEARCH, sizeof(PILOTSEARCH));
                read(0, namePilot, 100);
                namePilot[strlen(namePilot)-1] = '\0';
                showInfoPilot(searchInfoPilot(namePilot, drivers, numberOfElements));
                namePilot[0] = '\0';
                break;
            case '2':
                findWinners(drivers, winners);
                showWinners(winners, 0);
                break;
            case '3':
                findMoreLaps(drivers, winners);

                showWinners(winners, 1);
                break;
            case '4':
                write(1, PILOTSEARCH2, sizeof(PILOTSEARCH2));
                read(0, namePilot, 100);
                namePilot[strlen(namePilot) - 1] = '\0';
                storeInfo(searchInfoPilot(namePilot,drivers,numberOfElements));
                namePilot[0] = '\0';
                break;
            case '5':
                write(1, "SEE YOU!", strlen("SEE YOU!"));
                break;
            default:
                write(1, OPTIONERROR, strlen(OPTIONERROR));
        }
    } while (option != '5');

    close(file);
    free(line);
    return 0;
}
