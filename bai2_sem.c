#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
#include<semaphore.h>

sem_t mutex1;
sem_t mutex2;

void* processP1(void* arg){
    printf("A1\n");
    sem_post(&mutex1);
    sem_wait(&mutex2);
    printf("A2\n");
}

void* processP2(void* arg){
    printf("B1\n");
    sem_post(&mutex2);
    sem_wait(&mutex1);
    printf("B2\n");

}

int main(void){
    pthread_t p1, p2;

    sem_init(&mutex1, 1, 0);
    sem_init(&mutex2, 1, 0);

    pthread_create(&p1, NULL, processP1, NULL);
    pthread_create(&p2, NULL, processP2, NULL);

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    
    sem_destroy(&mutex1);
    sem_destroy(&mutex2);

    return 0;
}