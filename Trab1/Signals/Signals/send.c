#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <limits.h>

int main(int argc, char * argv[])
{

	if (argc < 3)
	{
		printf("ERROR - Parameter Missing. Expecting PID and SIGNAL values\n");
		exit(EXIT_FAILURE);
	}

	unsigned long proc_id = strtoul(argv[1], NULL, 10);
	unsigned long sig_value = strtoul(argv[2], NULL, 10);

	if (proc_id == 0 && !strcmp(argv[1], "0"))
	{
		perror("ERROR - Invalid PID value");
		exit(EXIT_FAILURE);
	}

	if (sig_value == 0 && strcmp(argv[2], "0") != 0)
	{
		perror("ERROR - Invalid SIGNAL value");
		exit(EXIT_FAILURE);
	}

	if (proc_id == ULONG_MAX || sig_value == ULONG_MAX)
	{
		perror("ERROR - Invalid parameter");
		exit(EXIT_FAILURE);
	}

	if (kill(proc_id, sig_value) != 0)
	{
		printf("ERROR - Process with PID = %s does not exist\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	return 0;
}