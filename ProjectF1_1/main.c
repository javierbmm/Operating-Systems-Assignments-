#include <stdio.h>
#include <string.h>
#include "fileManager.h"
#include "commandsActions.h


#define FILENAME_ERROR "Error! You must introduce the name of the cofiguration file.\n\n"
#define START "Starting Trinity...\n\n"
#define PERSEFONE "$Persefone:  "


void writeUser(username) {
    write(1, "$", strlen ("$"));
    write(1, config.user_name, strlen(config.user_name));
    write(1, ":\n", strlen (":\n"));
}

void kctrlc() {
    write (1, "DISCONNECTING TRINITY...\n", strlen("DISCONNECTING TRINITY...\n"));
}
int main(int arg, const char* argv[]) {
    FileData data;
    char *user ;
    int i, command;
    user [0] =  '\0';
    signal(SIGINT, kctrlc);

    if (arg != 2) {
        write(1, FILENAME_ERROR, strlen(FILENAME_ERROR));
    } else {
        write(1, START, strlen(START));
    }
    data = getFileData(argv[1]);
    writeUser(config.user_name);


    read(0, user, 1);
    command = parseInput(user);
    if (command != 6) {
        getCommand(command, user);
    }
    return 0;
}