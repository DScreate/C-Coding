#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX 100

pthread_mutex_t theMutex;
pthread_cond_t condc, condp;
int buffer = 0;

void * consumer(void * ptr);
void * producer(void * ptr);

int main(int argc, char ** argv)
{
	pthread_t pro, con;
	pthread_mutex_init(&theMutex, 0);
	pthread_cond_init(&condc, 0);
	pthread_cond_init(&condp, 0);
	pthread_create(&pro, 0, producer,0);
	pthread_create(&con, 0, consumer,0);
	pthread_join(pro, 0);
	pthread_join(con, 0);
	pthread_cond_destroy(&condc);
	pthread_cond_destroy(&condp);
	pthread_mutex_destroy(&theMutex);


}// end main


void * producer(void * ptr)
{
	int x;
	for(x = 1; x <= MAX; x++)
	{
		pthread_mutex_lock(&theMutex);
		printf("Producer active, creating widget %d\n", x);
		// Here we are checking to see if there is anything in the buffer
		// if there is, we wait!
		while(buffer != 0)
		{
			printf("Producer for widget %d waiting, buffer != 0\n", x);
			pthread_cond_wait(&condp, &theMutex);
		}// end while

		buffer = x;
		printf("Production of widget %d over\n", x);
		pthread_cond_signal(&condc);
		pthread_mutex_unlock(&theMutex);
	}// end for
}// end producer


void * consumer(void * ptr)
{
	int y;
	for(y = 1; y <= MAX; y++)
	{
		pthread_mutex_lock(&theMutex);
		printf("Consumer active, consuming widget %d\n", y);
		// Check to see if there's anything we can consume in the buffer
		// if not, wait until there is
		while(buffer == 0)
		{
			printf("Consumer for widget %d waiting, buffer is empty\n", y);
			pthread_cond_wait(&condc, &theMutex);
		}
		buffer = 0;
		printf("Consumption for widget %d over\n", y);
		pthread_cond_signal(&condp);
		pthread_mutex_unlock(&theMutex);
	}


}// end consumer
