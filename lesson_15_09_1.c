    #include <unistd.h>
    #include <sys/types.h>
    #include <stdlib.h>
    #include <fcntl.h>
    #include <stdio.h>

    int main(){
        int fd;

        size_t size;

        char string[] = "hello world!";

        (void) umask(0);

        if((fd = open("myfile", O_WRONLY | O_CREAT, 0666)) < 0){
            printf("Cant open\n");
            exit(-1);
        }
        size = write(fd, string, 14);

        if (size != 14){
            printf("Cant write all strings\n");
            exit(-1);
        }   
        if (close(fd) < 0){
            printf("Cant close\n");
        }
        printf("ok\n");

        char tmp[15] = "";

        if((fd = open("myfile", O_RDONLY | O_CREAT, 0666)) < 0){
            printf("Cant open\n");
            exit(-1);
        }

        read(fd, tmp, 14);

        printf("%s\n", tmp);

        return 0;

    }