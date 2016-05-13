#include "prodcon.h"



int main( int argc, const char* argv[] ){
	int nProd,nCons;
	/*----------------------|
	| arg[1] # of producer  |
	| arg[2] # of consumer  |
	| arg[3] Memory size    |
	-----------------------*/
	srand(time(NULL));

	if(argc == 4){

		nProd = atoi(argv[1]);
		nCons = atoi(argv[2]);
		mSize = atoi(argv[3]);
	
	}else{
	
		nProd = NP;
		nCons = NC;
		mSize = MEMORY_SIZE;
		printf("Missing parameters! Using default values\n");
	
	}

	sMemory = malloc(mSize*sizeof(long int));

	for(i = 0; i < mSize ; i++){
		sMemory[i]=0;
	}

	pthread_t p_Threads[nProd];
	pthread_t c_Threads[nProd];
	
	sem_init(&full,0,mSize);
	sem_init(&empty,0,0);
	pthread_mutex_init(&mutex_memory,NULL);

	for(i = 0;i<nProd;i++){
		pthread_create(&p_Threads[i],NULL,prod,NULL);
	}

	for(i = 0;i < nProd ; i++){
		pthread_join(p_Threads[i],NULL);
	}

	for(i = 0; i < nCons ; i++){
		pthread_create(&c_Threads[i],NULL,cons,NULL);
	}

	for(i = 0; i < nCons ; i++){
		pthread_join(c_Threads[i],NULL);
	}

	sem_destroy(&full);
	sem_destroy(&empty);
	pthread_mutex_destroy(&mutex_memory);

}