#include<pthread.h>
#include<stdio.h>
#include<unistd.h>

void* MakeH(void* arg){
    while (1)
    {
        sleep(2);
        printf("H\n");
    }
    
}

void* MakeO(void* arg){
    while (2)
    {
        sleep(1);
        printf("O\n");
    }
    
}

void* MakeH2O(void* arg){
    while (1)
    {
        sleep(1);
        printf("->H2O\n");
    }
    
}

int main(void){
    pthread_t p1, p2, p3, p4;

    pthread_create(&p1, NULL, MakeH, NULL);
    pthread_create(&p2, NULL, MakeH, NULL);
    pthread_create(&p3, NULL, MakeO, NULL);
    pthread_create(&p4, NULL, MakeH2O, NULL);

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    pthread_join(p3, NULL);
    pthread_join(p4, NULL);
    return 0;
}