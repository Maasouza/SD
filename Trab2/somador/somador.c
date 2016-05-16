#include "utils.h"

int main(int argc, char * argv[])
{
  	clock_t time_start, time_end;
  	double time_elapsed;

	unsigned int itt, qtt_threads = atoi(argv[1]);
	pthread_t tid[qtt_threads];	
	struct thread_arguments args[qtt_threads];
	long correct_answer = 0;

	if(argc != 2)
	{
		printf("ERROR - Invalid argument count. Please, provide (ONLY!) \"Number of threads\" parameter");
		exit(EXIT_FAILURE);
	}

	srand(time(NULL));

	//populate elements array
	printf("Populating array...\n");
	time_start = clock();
	for (itt = 0; itt < QTT_ELEMENTS; itt++)
	{
		elements[itt] = (char)((mrand48() % 200) - 100);
		correct_answer += elements[itt];
	}
	time_end = clock();
	time_elapsed = (double)(time_end - time_start)/CLOCKS_PER_SEC;
	printf("Array populated in %fs\n\n", time_elapsed);
	
	//create threads
	for(itt = 0; itt < qtt_threads; itt++)
	{	
		args[itt].first_num = itt;
		args[itt].step = qtt_threads;

		if (pthread_create(&tid[itt], NULL, &sum, (void *)&args[itt]) != 0) {
	    	perror("Failed to create thread: ");
	    	exit(EXIT_FAILURE);
    	}
	}

	// wait for threads to exit
	for(itt = 0; itt < qtt_threads; itt++)
	{
		pthread_join(tid[itt], NULL);
	}
	
	printf("Sum Result:\t%ld\nCorrect Answer:\t%ld\n", accumulator, correct_answer);
	
	pthread_exit(NULL);

	return 0;
}