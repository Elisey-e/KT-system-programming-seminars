#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

void daemon_process ()
{
    int i;

    fprintf(stderr, "Daemon started!\n");

    for (i = 0; i < 10; i++){
        fprintf(stderr, "Hello %d!\n", i);
        sleep(2);
    }

    fprintf(stderr, "Daemon finished\n");
}

int main(){
    pid_t pid;

    pid = fork();
    if (pid == -1){
        fprintf(stderr, "cannot fork!\n");
        return 1;
    }
    else if (pid != 0){
        return 0;
    }

    pid = fork();
    if (pid == -1){
        fprintf(stderr, "Cannot fork!\n");
        return 1;
    }
    else if (pid != 0){
        return 0;
    }

    daemon_process();
    return 0;
}