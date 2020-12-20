#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
#include<semaphore.h>

sem_t mutexH, mutexO;

void* MakeH(void* arg){
    while (1)
    {
        sleep(1);
        printf("H\n");
        sem_post(&mutexH);
    }
    
}

void* MakeO(void* arg){
    while (1)
    {
        sleep(2);
        printf("O\n");
        sem_post(&mutexO);
    }
    
}

void* MakeH2O(void* arg){
    while (1)
    {
        sem_wait(&mutexH);
        sem_wait(&mutexO);
        sem_wait(&mutexH);
        printf("->H2O\n");
    }
    
}

int main(void){
    pthread_t p1, p2, p3, p4;
    sem_init(&mutexH, 1, 0);
    sem_init(&mutexO, 1, 0);

    pthread_create(&p1, NULL, MakeH, NULL);
    pthread_create(&p2, NULL, MakeH, NULL);
    pthread_create(&p3, NULL, MakeO, NULL);
    pthread_create(&p4, NULL, MakeH2O, NULL);

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    pthread_join(p3, NULL);
    pthread_join(p4, NULL);

    sem_destroy(&mutexH);
    sem_destroy(&mutexO);
    return 0;
}