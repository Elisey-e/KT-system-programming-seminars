#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    int semid;
    char pathname[] = "08-1a.c";
    key_t key;
    struct sembuf mybuf;
    if ((key = ftok(pathname, 0)) < 0){
        printf("Cant generate key\n");
        exit(-1);
    }

    if ((semid = semget(key, 1, 0666 | IPC_CREAT)) < 0){
        printf("cant get semid\n");
        exit(-1);
    }

    mybuf.sem_op = -5;
    mybuf.sem_flg = 0;
    mybuf.sem_num = 0;

    if (semop(semid, &mybuf, 1) < 0){
        printf("cant wait for condition");
        exit(-1);
    }
    printf("condition is present\n");
    return 0;

    
}