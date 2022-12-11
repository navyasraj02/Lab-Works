#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

int item, buf[3], f = 0, r = 0;
sem_t mutex, empty, full;
void *producer(void *arg)
{
    int i;
    for (i = 1; i <= 10; i++)
    {
        sem_wait(&empty);
        sem_wait(&mutex);

        // Produce an item
        buf[(++r) % 3] = i;
        printf("Produced item :%d\n", i);
        sleep(3);

        sem_post(&mutex);
        sem_post(&full);
    }
}

void *consumer(void *arg)
{
    int i;
    for (i = 1; i <= 10; i++)
    {
        sem_wait(&full);
        sem_wait(&mutex);

        // Consume an item
        item = buf[(++f) % 3];
        printf("Consumed item :%d\n", i);
        sleep(1);

        sem_post(&mutex);
        sem_post(&empty);
    }
}

void main()
{
    pthread_t tid1, tid2;
    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, 3);
    sem_init(&full, 0, 0);
    pthread_create(&tid1, NULL, producer, NULL);
    pthread_create(&tid2, NULL, consumer, NULL);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
}