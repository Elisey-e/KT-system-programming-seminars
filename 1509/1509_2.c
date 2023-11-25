#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

    int main(){
        int fd[2];
        size_t size;
        char string[] = "Hello world!";
        char resstring[14];

        if(pipe(fd) < 0){
            printf("Cant create pipe\n");
            exit(-1);
        }

        size = write(fd[1], string, 14);

        if (size != 14){
            printf("Cant write all strings\n");
            exit(-1);
        }

        size = read(fd[0], resstring, 14);

        if (size < 0){
            printf("Cant read string\n");
            exit(-1);
        }
        printf("%s\n", resstring);

        char tmp[15] = "";

        if (close(fd[0]) < 0){
            printf("Cant close input stream\n");
        }

        if (close(fd[1]) < 0){
            printf("Cant close output stream\n");
        }

        return 0;

    }