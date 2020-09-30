//
// Created by javif on 12/19/2019.
//
#include <stdio.h>
#include <errno.h>
#include <sys/msg.h>

typedef struct{
    long idmis;
    int n1,n2;
} Missatge1;

typedef struct{
    long idmis;
    int resultat;
} Missatge2;

int main(){
    key_t Clau;
    int id_cua;
    Missatge1 M1;
    Missatge2 M2;

    Clau = ftok("EntraNombres.c",12);
    if (Clau==(key_t)-1){
        printf("Error Clau\n\n");
        exit(-1);
    }

    id_cua = msgget(Clau,0600|IPC_CREAT);
    if(id_cua==-1){
        printf("Error Creant cua\n\n");
        exit(-1);
    }
    M1.idmis=1;
    M1.n1=1;
    M2.idmis=2;
    for(;;){
        msgrcv(id_cua,(struct msgbuf *)&M1,sizeof(int)*2,1,0);
        printf("rebuts:%d,%d\n",M1.n1,M1.n2);
        if (M1.n1!=0){
            M2.resultat=M1.n1+M1.n2;
            msgsnd(id_cua,(struct msgbuf *)&M2,sizeof(int),IPC_NOWAIT);
            printf("enviat = %d\n",M2.resultat);
        }else exit(1);
    }
    printf("Programa finalitzat\n\n");
    msgctl (id_cua, IPC_RMID, (struct msqid_ds *)NULL);
}

