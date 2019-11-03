#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <fileManager.h>
#include <commandsActions.h>
#include <parsingInputs.h>


#define FILENAME_ERROR "Error! You must introduce the name of the configuration file.\n\n"
#define START "Starting Trinity...\n\n"
#define PERSEFONE "$Persefone:  "
#define BUFF_SIZE 500

int close_1 = 0;

void writeUser(char * username) {
    write(1, "$", strlen ("$"));
    write(1, username, strlen(username));
    write(1, ":\n", strlen (":\n"));
}

void kctrlc() {
    write (1, "DISCONNECTING TRINITY...\n", strlen("DISCONNECTING TRINITY...\n"));
    close_1 = 1;
}
int main(int arg, const char* argv[]) {
    FileData data;
    char *user = malloc(1);
    int command, file;
    char buffer[BUFF_SIZE];
    user [0] =  '\0';

    //signal(SIGINT, kctrlc);
    if (arg != 2) {
        write(1, FILENAME_ERROR, strlen(FILENAME_ERROR));
        exit(1);
    }

    write(1, START, strlen(START));
    file = open (argv[1], O_RDONLY);
    if(file < 0) {
        sprintf(buffer,"<%s>: Error opening file. Check it and try again\n", argv[1]);
        write(1, &buffer, strlen(buffer));

        exit(1);
    }

    data = getFileData(file);
    user = realloc(user, (BUFF_SIZE)*sizeof(user));

    while (close_1 == 0) {
        writeUser(data.user_name);

        read(0, user, BUFF_SIZE);
        command = parseInput(user);
        if (command >= 0 && command != 6) {
            getCommand(command, user);
            printf("flag\n");
        }else
            break;

        // Empty-ing the buffer
        memset(user,0,strlen(user));
        user[0] = '\0';
    }

    close(file);
    return 0;
}