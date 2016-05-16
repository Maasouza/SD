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
		sMemory[i]=0;
	}

	pthread_t p_Threads[nProd];
	pthread_t c_Threads[nCons];
	
	sem_init(&full,0,BUFFER_SIZE);
	sem_init(&empty,0,0);
	pthread_mutex_init(&mutex_memory,NULL);

	// create producers
	for(i = 0;i<nProd;i++){
		pthread_create(&p_Threads[i],NULL,prod,NULL);
	}

	// create consumers
	for(i = 0; i < nCons ; i++){
		pthread_create(&c_Threads[i],NULL,cons,NULL);
	}

	for(i = 0;i < nProd ; i++){
		pthread_join(p_Threads[i],NULL);
	}

	for(i = 0; i < nCons ; i++){
		pthread_join(c_Threads[i],NULL);
	}

	sem_destroy(&full);
	sem_destroy(&empty);
	pthread_mutex_destroy(&mutex_memory);

	pthread_exit(NULL);
	return 0;
}