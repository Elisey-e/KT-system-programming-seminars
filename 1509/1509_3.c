#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

    int main(){
        int fd[2], result;
        size_t size;
        char resstring[14];

        if(pipe(fd) < 0){
            printf("Cant create pipe\n");
            exit(-1);
        }

        result = fork();

        if (result){
            printf('Cant fork child\n');
            exit(-1);
        }
        else if (result <= 0){
            close(fd[0]);

            size = write(fd[1], "Hello world\n", 14);

            if (size != 14){
                printf("Cant wtite all strings\n");
                exit(-1);
            }
            close(fd[1]);
            printf("parent exited\n");
        }
        else{
            close(fd[1]);
            size = read(fd[0], resstring, 14);
            if (size <= 0){
                printf("Cant read string\n");
                exit(-1);
            }
            printf("%s\n", resstring);
            close(fd[0]);
        }
        return 0;

    }