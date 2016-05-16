#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <semaphore.h>
#include <pthread.h>
#include <assert.h>


#define NC 1 //# of consumer 
#define NP 1 //# of producer 

#define MAX_CONSUME 10000
#define MAX_VAL 10000000
#define BUFFER_SIZE 32
#define TRUE 1
#define FALSE 0


sem_t full,empty;
pthread_mutex_t mutex_memory;

int time_index;
int nProd,nCons;
int memory_index=0;

long int sMemory[BUFFER_SIZE];


int isPrime(long value){
	unsigned int value_sqrt = (int)sqrt(value), itt;
	if(value & 0x1){ // ---> if ![value % 2 == 0]
		for (itt = 3; itt <= value_sqrt; itt += 2)
		{
			if(value % itt == 0)
			{
				return 0; // not prime
			}
		}
		return 1; // is prime
	} else if (value == 2){
		return 1; // prime
	}
	return 0; //not prime
}

void* prod(){
<<<<<<< HEAD
	long int value=1;
	int i = 0;
	while(i < MAX_CONSUME/nProd){
		//value = rand()+1;
		value+=1;
=======
	long int value;
	while(1){
		value = rand()+1;
>>>>>>> d5ba201cc81642ec4b194bd7f618784212a50c06
		sem_wait(&empty);
		pthread_mutex_lock(&mutex_memory);
		if (memory_index < BUFFER_SIZE && sMemory[memory_index]==0){
			sMemory[memory_index]=value;
			memory_index += 1;
<<<<<<< HEAD
			i+=1;
		}			
=======
		}		
>>>>>>> d5ba201cc81642ec4b194bd7f618784212a50c06
		pthread_mutex_unlock(&mutex_memory);
		sem_post(&full);
	}
}

void* cons(){
	long int value;
<<<<<<< HEAD
	int i = 0;
	while(i < MAX_CONSUME/nCons){		
=======
	while(1){		
>>>>>>> d5ba201cc81642ec4b194bd7f618784212a50c06
		sem_wait(&full);
		pthread_mutex_lock(&mutex_memory);
		if(memory_index >= 0 && sMemory[memory_index]!=0){
			memory_index -= 1;
			value=sMemory[memory_index];
			sMemory[memory_index]=0;
			i+=1;
			printf("consumer %d: %ld\tisPrime: %d\n",i,value, isPrime(value));
		}		
		pthread_mutex_unlock(&mutex_memory);
		sem_post(&empty);
<<<<<<< HEAD
=======
		printf("consumer: %ld\tisPrime: %d\n",value, isPrime(value));
>>>>>>> d5ba201cc81642ec4b194bd7f618784212a50c06
	}
}
/*---------------------------------------------------|
|                                                    |
| (Np,Nc) ={(1,1),(2,2),(5,5),(10,10),(2,10),(10,2)} |
| BUFFER_SIZE = {2,4,8,16,32}                        |
|                                                    |
|---------------------------------------------------*/ 