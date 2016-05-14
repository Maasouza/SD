#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <semaphore.h>
#include <pthread.h>



#define NC 1 //# of consumer 
#define NP 1 //# of producer 
#define MEMORY_SIZE 10
#define MAX_CONSUME 10E4
#define MAX_VAL 10E7
#define BUFFER_SIZE 32
#define TRUE 1
#define FALSE 0


sem_t full,empty;
pthread_mutex_t mutex_memory;

int mSize,i,time_index,countP,countC;
int memory_index=0;
long int sMemory[BUFFER_SIZE];

countC = 0;
countP = 0;

int isPrime(long value)
{
	unsigned int value_sqrt = (int)sqrt(value), itt;
	
	if(!(value & 0x1)){ // ---> if ![value % 2 == 0]
		for (itt = 3; itt < value_sqrt; itt += 2)
		{
			if(value % itt == 0)
			{
				return 0; // not prime
			}
		}
	}
	return 1; // is prime
}

void* prod(){
	long int value;
	while(countP<MAX_CONSUME){
		value = rand()+1;
		sem_wait(&empty);
		pthread_mutex_lock(&mutex_memory);
		if (memory_index < BUFFER_SIZE){
			sMemory[memory_index]=value;
			memory_index += 1;
		}		
		countP+=1;
		pthread_mutex_unlock(&mutex_memory);
		sem_post(&full);
		printf("producer %ld\n",value);
	}
}

void* cons(){
	long int value;
	while(countC<MAX_CONSUME){		
		sem_wait(&full);
		pthread_mutex_lock(&mutex_memory);
		
		if(memory_index < 0){
			memory_index -= 1;
			value=sMemory[memory_index];
		}		
		countC+=1;
		pthread_mutex_unlock(&mutex_memory);
		sem_post(&empty);
		printf("id: %d consumer: %ld\tisPrime: %d\n",countC,value, isPrime(value));
	}
}
/*---------------------------------------------------|
|                                                    |
| (Np,Nc) ={(1,1),(2,2),(5,5),(10,10),(2,10),(10,2)} |
| MEMORY_SIZE = {2,4,8,16,32}                        |
|                                                    |
|---------------------------------------------------*/ 