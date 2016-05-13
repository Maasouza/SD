#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <semaphore.h>
#include <pthread.h>



#define NC 1 //# of consumer 
#define NP 1 //# of producer 
#define MEMORY_SIZE 10
#define MAX_CONSUME 10000
#define MAX_VAL 10000000
#define TRUE 1
#define FALSE 0


sem_t full,empty;
pthread_mutex_t mutex_memory;

int mSize,i,time_index;
int memory_index=0;
long int *sMemory;




void* prod(){
	long int value;
	while(1){
		value = (rand()%10000000)+1;
		sem_wait(&empty);
		pthread_mutex_lock(&mutex_memory);
		sMemory[memory_index++]=value;
		pthread_mutex_unlock(&mutex_memory);
		sem_post(&full);
		printf("producer %ld\n",value);
		fflush(stdout);
	}
}

void* cons(){
	long int value;
	while(1){		
		sem_wait(&full);
		pthread_mutex_unlock(&mutex_memory);
		value=sMemory[--memory_index];
		pthread_mutex_unlock(&mutex_memory);
		sem_post(&empty);
		printf("consumer %ld\n",value );
	}
}
/*---------------------------------------------------|
|                                                    |
| (Np,Nc) ={(1,1),(2,2),(5,5),(10,10),(2,10),(10,2)} |
| MEMORU_SIZE = {2,4,8,16,32}                        |
|                                                    |
|---------------------------------------------------*/ 