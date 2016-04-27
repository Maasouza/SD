#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

#define COLOR_CYAN    "\x1b[36m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_RESET   "\x1b[0m"

#define EXIT_SIG 10
#define SIG1 11
#define SIG2 12
#define SIG3 13


void exit_sig_handler(int sig)
{
	signal(EXIT_SIG, exit_sig_handler);
    printf(COLOR_YELLOW "Sem você tá um caos...\n" COLOR_RESET "--Pixote\n\n");
    fflush(stdout);
    exit(EXIT_SUCCESS);
}

void sig1_handler(int sig)
{
	signal(SIG1, sig1_handler);
    printf( COLOR_YELLOW "Da um alô dá uma chance pro amor\nPois eu não tô legal\n" COLOR_RESET "Mande um sinal\n");
    fflush(stdout);
}

void sig2_handler(int sig)
{
	signal(SIG2, sig2_handler);
    printf(COLOR_YELLOW "Se a saudade aumentar vai ser golpe fatal\n" COLOR_RESET "Mande um sinal\n");
    fflush(stdout);
}

void sig3_handler(int sig)
{
	signal(SIG3, sig3_handler);
    printf(COLOR_YELLOW "Eu preciso dizer que a minha vida parou sem você\nTá um caos\n" COLOR_RESET "Mande um sinal\n");
    fflush(stdout);
}


int main(int argc, char * argv[])
{
	printf(COLOR_CYAN "PID = %d\n" COLOR_RESET, getpid());
	printf("Mande um sinal\n");

	signal(EXIT_SIG, exit_sig_handler);
	signal(SIG1, sig1_handler);
	signal(SIG2, sig2_handler);
	signal(SIG3, sig3_handler);

	if (argc > 1)
	{
		if ((argv[1][0] == '-') && (argv[1][1] == 'b') && (argv[1][2] == 'w') && (argv[1][3] == '\0'))
		{
			printf("USING BUSY WAIT\n");
			while(1);
		}
		else
		{
			printf("INVALID PARAMETER: \"%s\"\n", argv[1]);
			exit(EXIT_FAILURE);
		}
	} 
	
	while(1)
	{
		pause();
	}
		
	return 0;
}
