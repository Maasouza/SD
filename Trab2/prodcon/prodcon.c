#include "prodcon.h"



int main( int argc, const char* argv[] ){
	/*-----------------------|
	| arg[1] # of producers  |
	| arg[2] # of consumers  |
	|-----------------------*/
	int itt;

	srand(time(NULL));

	// read parameters
	if(argc == 3){

		nProd = atoi(argv[1]);
		nCons = atoi(argv[2]);
	
	}else{
	
		nProd = NP;
		nCons = NC;
		printf("Missing parameters! Using default values\n");
	
	}

	// empty buffer
	for(itt = 0; itt < BUFFER_SIZE ; itt++){
		sMemory[itt]=0;
	}

	pthread_t p_Threads[nProd];
	pthread_t c_Threads[nCons];
	
	sem_init(&empty,0,BUFFER_SIZE);
	sem_init(&full,0,0);
	pthread_mutex_init(&mutex_memory,NULL);

	// create producers
	for(itt = 0;itt<nProd;itt++){
		pthread_create(&p_Threads[itt],NULL,prod,NULL);
	}

	// create consumers
	for(itt = 0; itt < nCons ; itt++){
		pthread_create(&c_Threads[itt],NULL,cons,NULL);
	}

	for(itt = 0;itt < nProd ; itt++){
		pthread_join(p_Threads[itt],NULL);
	}

	for(itt = 0; itt < nCons ; itt++){
		pthread_join(c_Threads[itt],NULL);
	}

	sem_destroy(&full);
	sem_destroy(&empty);
	pthread_mutex_destroy(&mutex_memory);

	pthread_exit(NULL);
	return 0;
}