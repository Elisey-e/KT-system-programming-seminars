#include "tasklib.h"


int main()
{
    int got_type;
    int i;
    int maxtable;
    int readstream;

    scanf("%d", &maxtable);
    int in_types = open("types.txt", O_RDONLY | __O_CLOEXEC);
    check(in_types > 0, "Can\'t open() input file \"%s\": m", "types.txt");

    FILE *in_file_types = fdopen(in_types, "readstream");
    check(in_file_types, "Can\'t open() input fd %d: m", in_types);

    int * wash_time = (int *) mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS,      -1, 0);
    int * wipe_time = (int *) mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS,      -1, 0);
    int * table     = (int *) mmap(NULL, maxtable, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS,  -1, 0);
    for (i = 0; i < maxtable; i++)
        table[i]=(-1);

    for (i = 0; i < SIZE; i++)
    {
        readstream = fscanf(in_file_types, "%d %d\n", &wash_time[i], &wipe_time[i]);
        if (readstream == EOF)
        {
            check(!ferror(in_file_types), "Failed to read next input line: m");
            return 0;
        }
    }
    
    int child_pid = fork();
    if (child_pid == 0)//дочерний процесс - мойщик
    {
        int in_fd = open("income.txt", O_RDONLY | __O_CLOEXEC);
        check(in_fd > 0, "Can\'t open() input file \"%sm", "income.txt");
        FILE *in_file = fdopen(in_fd, "readstream");
        check(in_file, "Can\'t open() input fd %d: m", in_fd);
        while(1)
        {
            readstream = fscanf(in_file, "%d\n", &got_type);
            if (readstream == EOF)
            {
                check(!ferror(in_file_types),"Failed to read next input line: m");
                table[maxtable - 1] = (-2); //даем знать род. процессу, что мы закончили.
                printf("Закончил мыть\n");
                return 0;
            }
            printf("Мою посуду типа %d, %d секунду(ы)\n", got_type, wash_time[got_type]);
            sleep(wash_time[got_type]);
            printf("Домыл, ищу куда поставить\n");
            while (1)
            {
                for(i = 0; i < maxtable; i++)
                {
                    if (table[i] == -1){
                        table[i]=got_type; printf("Поставил посуду типа %d, на %d-e место\n", got_type, i);
                        break;
                    }
                }
                if (i < maxtable)
                    break;
                else {
                    printf("Некуда поставить, жду\n");
                    sleep(1);
                }
            }
        }
    }
    else if (child_pid < 0)	{
        // не получилось создать дочернин процесс* .
        killpr("Failed to fork() off a child: m");
    }
    if(child_pid > 0)//вытирание:
    {
        while(1)
        {
            for(i = 0; i < maxtable; i++)
            {
                if (table[i]>=0)
                {
                    got_type = table[i];
                    table[i] = -1;
                    printf("Взял посуду типа %d, c %d-ro места\n", got_type, i);
                    printf("Вытираю %d секунду(ы)\n", wipe_time[got_type]);
                    break;
                }
            }
            if (i == maxtable)
            {
                {
                    // ждем посуды
                    printf("Подождем...\n");
                    sleep(1);
                }
                if (table[maxtable - 1] == -2)
                {
                    printf("Закончил вытирать\n");
                    break;
                }
                continue;
            }
            sleep(wipe_time[got_type]);
            printf("Вытер, ищу посуду на столе\n");
        }
    }
    return 0;
    
}