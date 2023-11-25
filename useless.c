#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int atimes[100];
char adata[100][256];

//функция для сортировки по возрастанию
int comp1 (const void * a, const void * b)
{
  return ( (atimes[*(int*)a]) - (atimes[*(int*)b]) );
}

int ma_x(int a, int b){
    if (a > b){
        return a;
    }
    else{
        return b;
    }
}

int main(int argc, char *argv[], char *envp[]) {

	const char* file_name = argv[1];                            // Open file
	FILE* file = fopen(file_name, "r");
	if (file == NULL) {
		printf("Не удалось открыть файл '%s'\n", file_name);
		return 1;
    }


    int anums[100];                                             // Generate range(1, 100)
    for (int i = 0; i < 100; i++){
        anums[i] = i;
    }


    int num_of_str = 0;
    while(fscanf(file, "%d %s\n", &atimes[num_of_str], adata[num_of_str]) == 2){
        ++num_of_str;                                                                         // Read all strings from file
    }
    qsort(anums, num_of_str, sizeof(int), comp1);               //sort all times



    int summ_time = 0;                
    for (int i = 0; i < num_of_str; ++i){
		int delay = atimes[anums[i]];
		char* program_name = adata[anums[i]];

		printf("Запуск программы '%s' с задержкой %d секунд\n", program_name, delay);

        // Запуск программы с задержкой
		sleep(ma_x(0, delay - summ_time));
        summ_time += ma_x(0, delay - summ_time);
		pid_t pid;
		pid = fork();
		if(pid == -1){
			printf("ERROR\n");
		} else if (pid == 0){
			execle(program_name, program_name, "2023", 0, NULL);
			exit(-1);
		}
	}
    

	fclose(file);
	printf("Все программы выполнены.\n");
	return 0;
}