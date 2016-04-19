#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

void sig1_handler(int sig)
{
	signal(1, sig1_handler);
    printf("received 1\n");
    fflush(stdout);
}

void sig2_handler(int sig)
{
	signal(2, sig2_handler);
    printf("received 2\n");
    fflush(stdout);
}

void sig3_handler(int sig)
{
	signal(3, sig3_handler);
    printf("received 3\n");
    fflush(stdout);
}


int main()
{
	printf("PID = %d\n", getpid());

	signal(1, sig1_handler);
	signal(2, sig2_handler);
	signal(3, sig3_handler);

	for(;;)
	{
		pause();
	}
	return 0;
}