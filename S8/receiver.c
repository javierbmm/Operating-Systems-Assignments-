/*
 * @program: receiver.c
 * @author: Javier Merida javier.merida
 *  Olivia Rey olivia.rey
 */
#include <stdio.h>
#include <errno.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include<signal.h>

#define TRUE 1
#define FALSE 0
#define OK "[OK]\n"
#define KO "[KO Unable to receive confirmation. Closing...]\n"

volatile int close_me;
// Print function for simple strings (NO %d %f %s etc)
void myprint(char* msg){
    char buffer[strlen(msg)+1];
    sprintf(buffer, "%s", msg);
    write(1, buffer, strlen(buffer));
}

void handle_sigint(){
    close_me = TRUE;
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

int main(){
    key_t Key;
    int id_cua;
    toSend  s_msg;
    toRcv r_msg;
    signal(SIGINT, handle_sigint);
    close_me = FALSE;
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

    char buffer[137];
    while(close_me == FALSE){
        memset(s_msg.msg, 0, sizeof(s_msg.msg));
        msgrcv(id_cua,(struct msgbuf *)&s_msg, sizeof(s_msg) - sizeof(long),1,0);
        sprintf(buffer, "[%s]: %s\n", s_msg.name, s_msg.msg);
        write(1, buffer, strlen(buffer));
        fflush(stdout);
        r_msg.idmis = s_msg.sender_pid;
        strcpy(r_msg.msg, OK);
        msgsnd(id_cua,(struct msgbuf *)&r_msg, sizeof(r_msg) - sizeof(long),IPC_NOWAIT);
    }
    myprint("[Closing]\0");
    msgctl (id_cua, IPC_RMID, (struct msqid_ds *)NULL);

}

