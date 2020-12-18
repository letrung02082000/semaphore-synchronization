#include<pthread.h>
#include<stdio.h>
#include<unistd.h>

void* processP1(void* arg){
    sleep(1);
    printf("A1\n");
    sleep(1);
    printf("A2\n");

}

void* processP2(void* arg){
    sleep(1);
    printf("B1\n");
    sleep(1);
    printf("B2\n");

}

int main(void){
    pthread_t p1, p2;

    pthread_create(&p1, NULL, processP1, NULL);
    pthread_create(&p2, NULL, processP2, NULL);

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);

    return 0;
}