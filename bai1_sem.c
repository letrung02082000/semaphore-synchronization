#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>

int x = 0;
sem_t mutex;

void *threadFn(void *arg)
{
	do
	{
        sem_wait(&mutex);

		x = x + 1;
        
		if(x == 20)
		{	
			sleep(1);
			x = 0;
		}
		else if(x > 20)
		{
		printf("%d\n", x);
		break;
		}

        printf("%d\n", x);

        sem_post(&mutex);
		
	}while(1);
}

int main(void)
{
	pthread_t p1, p2;
	int x = 0;
    sem_init(&mutex, 0, 1);
	pthread_create(&p2,NULL,threadFn,NULL);
	pthread_create(&p1,NULL,threadFn,NULL);
	
	pthread_join(p1,NULL);
	pthread_join(p2,NULL);
	sem_destroy(&mutex);
	return 0;
}