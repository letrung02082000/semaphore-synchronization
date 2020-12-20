#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex, mutexO, mutexH;

int oxy=0, hidro=0;

pthread_t oxyThread,hidroThread1,hidroThread2;

int MakeH2O(void){
    static int i=0;
    i++;
    if((i%3)==0)
        printf("->H2O\n");
    sleep(1);
    return 0;
}

void* oxyFn(void* arg){

    while(1){
        sem_wait(&mutex);

        oxy+=1;

        if(hidro>=2){
            sem_post(&mutexH);
            sem_post(&mutexH);
            hidro-=2;
            sem_post(&mutexO);
            oxy-=1;
        }
        else {
            sem_post(&mutex);
        }

        sem_wait(&mutexO);
        printf("O\n");
        MakeH2O();

        sem_post(&mutex);
    }
}

void* hydroFn(void* arg){
    while(1){
        sem_wait(&mutex);

        hidro+=1;

        if(hidro>=2 && oxy>=1){
            sem_post(&mutexH);
            sem_post(&mutexH);
            hidro-=2;
            sem_post(&mutexO);
            oxy-=1;
        }
        else{
            sem_post(&mutex);
        }

        sem_wait(&mutexH);

        printf("H\n");
        MakeH2O();
        }

}

int main(){

    if(sem_init(&mutex,0,1)==-1){
        perror("Cannot init semaphore.\n");
    }
    if(sem_init(&mutexO,0,0)==-1){
        perror("Cannot init semaphore.\n");
    }
    if(sem_init(&mutexH,0,0)==-1){
        perror("Cannot init semaphore.\n");
    }

    pthread_create(&oxyThread,0,oxyFn, NULL);
    pthread_create(&hidroThread1,0,hydroFn, NULL);
    pthread_create(&hidroThread2,0,hydroFn, NULL);

    pthread_join(oxyThread, NULL);
    pthread_join(hidroThread1, NULL);
    pthread_join(hidroThread2, NULL);

    return 0;
}