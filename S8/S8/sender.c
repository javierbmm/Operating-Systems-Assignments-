/*
 * @program: sender.c
 * @author: Javier Merida javier.merida
 * @author: Olivia Rey olivia.rey
 */

#include <stdio.h>
#include <errno.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define ERROR "Error, you need to write the name of the user\n"
#define OK "[OK]\n"
#define KO "[KO Unable to receive confirmation. Closing...]\n"


// Print function for simple strings (NO %d %f %s etc)
void myprint(char* msg){
    char buffer[strlen(msg)+1];
    sprintf(buffer, "%s", msg);
    write(1, buffer, strlen(buffer));
}


int readUntil(int file, char** word, char limit){
    int wordLength = 0;
    memset(*word, 0, strlen(*word));
    //char *word = (char*)malloc(0);
    //word = realloc(word, 0);
    char letter[1];
    while(1){
        if(read(file, letter, 1) > 0){
            // reading letter by letter (one byte at time) until limit
            if(letter[0] == limit || letter[0] == '\0') {
                //printf("|%c|", letter[0]);
                break;
            }
            *word = (char*)realloc(*word, ++wordLength);
            (*word)[wordLength-1] = letter[0];
        }else
            break;
    }
    //printf("word: %s\n", *word);

    return wordLength;
}

typedef struct{
    long idmis;
    pid_t sender_pid;
    char msg[100];
    char name[33];
} toSend;

typedef struct{
    long idmis;         // this one should be equal than my pid
    char msg[100];
} toRcv;

int main(int argc, char *argv[]){
    if (argc < 2 ) {
        write(1, ERROR, strlen(ERROR));
        exit(1);
    }

    char * username = malloc(strlen(argv[1]));
    strcpy(username, argv[1]);

    key_t Key;
    int id_cua;
    toSend  s_msg;
    toRcv r_msg;
    pid_t my_pid = getpid();

    Key = ftok("MailBox.c",12);
    if (Key==(key_t)-1){
        myprint("Error Key\n\n");
        exit(-1);
    }

    id_cua = msgget(Key,0600|IPC_CREAT);
    if(id_cua==-1){
        myprint("Error Creant cua\n\n");
        exit(-1);
    }
    s_msg.sender_pid = my_pid;
    s_msg.idmis = 1;
    strcpy(s_msg.name, username);
    char buffer[135];
    char *readBuffer = calloc(0,0);
    while(1){
        sprintf(buffer, "<%s>$", username);
        write(1, buffer, strlen(buffer));
        memset(s_msg.msg, 0, sizeof(s_msg.msg));
        int sizeOfMsg = 0;
        sizeOfMsg = readUntil(0, &readBuffer, '\n');
        int index = 0;
        while(sizeOfMsg >= 0){
            memset(s_msg.msg, 0, sizeof(s_msg.msg));
            strncpy(s_msg.msg, readBuffer+index, 100);
            sizeOfMsg -= 100;
            index += 100;
            msgsnd(id_cua,(struct msgbuf *)&s_msg, sizeof(s_msg) - sizeof(long),IPC_NOWAIT);
        }
        if(msgrcv(id_cua,(struct msgbuf *)&r_msg, sizeof(r_msg) - sizeof(long),my_pid,0) > 0) {
            myprint(OK);
        }else
            break;
    }
    myprint(KO);
    msgctl (id_cua, IPC_RMID, (struct msqid_ds *)NULL);
    free(username);
    free(readBuffer);
}


