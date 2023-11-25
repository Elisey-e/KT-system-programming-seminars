#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>

int main(){
    int flags, fd[2];
    if (pipe(fd) < 0){
        exit(-1);
    }
    flags |= O_NONBLOCK;
    if (fcntl(fd[1], F_SETFL, flags)){
        exit(-1);
    }
    int i = 0;
    while (write(fd[1], "1", 1) >= 0){
        i++;
    }
    if (errno = EAGAIN){
        printf("pipe size = %d\n", i);
    }
    close(fd[0]);
    close(fd[1]);
    return 0;
}