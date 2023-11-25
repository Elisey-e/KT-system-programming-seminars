#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#define N 2

#define WAITING 1
#define working 0
#define LEFT 0
#define RIGHT 0
int state[N];
int family[N] = { 0, 1};

sem_t mutex;
sem_t S[N];

void test(int phnum)
{
    if (state[phnum] == WAITING) {
        state[phnum] = working;
        printf("Vadim %d takes job");
        printf("Vadim %d is working\n", phnum + 1);
        sem_post(&S[phnum]);
    }
}

void take_work(int phnum)
{
    sem_wait(&mutex);
    state[phnum] = WAITING;
    printf("Vadim %d is WAITING!!!!!!!!!!!!!!!!!\n", phnum + 1);

    test(phnum);
    sem_post(&mutex);

    sem_wait(&S[phnum]);
    sleep(1);
}

void change_work(int phnum)
{
    sem_wait(&mutex);

    printf("son %d putting work %d and %d down\n",
    phnum + 1, LEFT + 1, phnum + 1);

    test(LEFT);
    test(RIGHT);

    sem_post(&mutex);
}


void* member(void* num)
{

    while (1) {
        //take_work(*i);
        //change_work(*i);
    }
}
int main()
{
    int i;
    pthread_t thread_id[N];

    sem_init(&mutex, 0, 1);
    for (i = 0; i < N; i++)
        sem_init(&S[i], 0, 0);

    for (i = 0; i < N; i++) {
        pthread_create(&thread_id[i], NULL,
        member, &family[i]);
        //member();
    }

    for (i = 0; i < N; i++)
        pthread_join(thread_id[i], NULL);
}