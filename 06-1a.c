#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(){
    int *array;
    int shmid;
    int new = 1;
    char pathname[] = "06-1a.c";
    key_t key;
    if ((key = ftok(pathname, 0)) < 0){
        printf("Cant generate key\n");
        exit(-1);
    }


    if ((shmid = shmget(key, 3 * sizeof(int), 0666 | IPC_CREAT | IPC_EXCL)) < 0){
        if (errno != EEXIST){
            printf("Cant cheate shared memory\n");
            exit(-1);
        }
        else{
            if((shmid = shmget(key, 3 * sizeof(int), 0)) < 0){
                printf("Cant find shared memory\n");
                exit(-1);
            }
            new = 0;
        }
    }

    if ((array  = (int *) shmat(shmid, NULL, 0)) == (int*)(-1)){
        printf("cant attach shared memory");
        exit(-1);
    }

    for (long long int i = 0; i < 10000000000LL; i++){
        int a = 0;
        a = "0";
    }

    if(new){
        array[0] = 1;
        array[1] = 0;
        array[2] = 1;
    }
    else{
        array[0] += 1;
        for (long long int i = 0; i < 10000000000LL; i++){
            int a = 0;
            a = "0";
        }
        array[2] += 1;
    }

    printf("Program 1 was shawn %d times, program 2 - %d times, total - %d times\n", array[0], array[1], array[2]);
    if(shmdt(array) < 0){
        printf("Cant detach shared memory\n");
        exit(-1);
    }
    return 0;
}