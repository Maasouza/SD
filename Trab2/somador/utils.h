#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

#ifndef QTT_ELEMENTS
#define QTT_ELEMENTS 1000000000
#endif

char elements[QTT_ELEMENTS];
long accumulator = 0;
char lock = 0;

int test_and_set(char * lock){
	char prev_lock = *lock;
	*lock = 1;
	return prev_lock;
}

void acquire()
{
	while(test_and_set(&lock));
}

void release()
{
	lock = 0;
}

struct thread_arguments
{
	unsigned int first_num;
	unsigned int step;
};

void * sum(void * tArgs)
{
	struct thread_arguments * args = (struct thread_arguments *) tArgs;
	long t_sum = 0;
	int item = args->first_num;

	while(item < QTT_ELEMENTS)
	{
		t_sum += elements[item];
		item += args->step;
	}

	acquire();
	accumulator += t_sum;
	release();

	return NULL;
}
