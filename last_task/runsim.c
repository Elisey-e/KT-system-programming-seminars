#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <fcntl.h>
#include <signal.h>


void error(const char* fmt, ...){
    fprintf(stderr, "Error: ");
    va_list list;
    va_start(list, fmt);
    vfprintf(stderr, fmt, list);
    va_end(list);
    exit(1);
}


typedef union
{
    int val;
    struct semid_ds* buf;
    unsigned short* array;
} semctl_param;


int main(int argc, char ** argv){
    int maxTasks;
    if (argc != 2 || sscanf(argv[1], "%d", &maxTasks) != 1 || maxTasks <= 0){
        error("Usage: program N\n");
    }
    key_t key;
    if ((key = ftok(argv[0], 0)) < 0){
        error("Failed to generate key\n");
    }
    int semaphore;
    if ((semaphore = semget(key, 1, 0666 | IPC_CREAT)) < 0)
        error("Failed to create semaphore\n");
    semctl_param maxTasksParam = { maxTasks };
    if (semctl(semaphore, 0, SETVAL, maxTasksParam) < 0)
        error("Failed to set initial semaphore value\n");
    signal(SIGCHLD, SIG_IGN);

    while (1)
    {
        char line[1024];
        if (fgets(line, 1024, stdin) <= 0)
            break;
        
        char* arguments[128] = {};
        int nArguments = 0;
        int length = strlen(line);
        char* argumentBegin = line;
        for (int i = 0; i <= length; i++){
            if (line[i] == 0 || line[i] == ' ' || line[i] == '\n')
            {
                line[i] = 0;
                if (argumentBegin != line + i)
                    arguments[nArguments++] = argumentBegin;
                argumentBegin = line + i + 1;
            }
        }
        int childPID = fork();
        if (childPID == 0){
            struct sembuf operation;
            operation.sem_num = 0;
            operation.sem_op = -1;
            operation.sem_flg = SEM_UNDO | IPC_NOWAIT;

            if (semop(semaphore, &operation, 1) < 0)
                error("Too many processes, only %d allowed.\n", maxTasks);
            if (execvp(arguments[0], arguments) < 0)
                error("Failed to execute '%s': %s\n", arguments[0], strerror(errno));
        }
        else if (childPID < 0)
        {
            error("Failed to fork: %s\n", strerror(errno));
        }
    }
    wait(0);

    return 0;
    
}
