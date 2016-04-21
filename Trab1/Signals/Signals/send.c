#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <limits.h>

#define COLOR_RED     "\x1b[31m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"

int main(int argc, char * argv[])
{
	if (argc < 3)
	{
		printf(COLOR_RED "ERROR - Parameter Missing. Expecting PID and SIGNAL values" COLOR_RESET "\n");
		exit(EXIT_FAILURE);
	}

	unsigned long proc_id = strtoul(argv[1], NULL, 10);
	unsigned long sig_value = strtoul(argv[2], NULL, 10);

	if (((proc_id == 0) && (argv[1][0] == '0') && (argv[1][1] == '\0')) || (proc_id == ULONG_MAX))
	{
		perror(COLOR_RED "ERROR - Invalid PID value");
		printf(COLOR_RESET);
		exit(EXIT_FAILURE);
	}

	if (((sig_value == 0) && (argv[2][0] == '0') && (argv[2][1] == '\0')) || (sig_value == ULONG_MAX))
	{
		perror(COLOR_RED "ERROR - Invalid SIGNAL value");
		printf(COLOR_RESET);
		exit(EXIT_FAILURE);
	}

	if (kill(proc_id, sig_value) != 0)
	{
		printf(COLOR_RED "ERROR - Process with PID = %s does not exist\n" COLOR_RESET, argv[1]);
		exit(EXIT_FAILURE);
	}

	printf(COLOR_CYAN "Signal %d sent to process %d\n" COLOR_RESET, (int)sig_value, (int)proc_id);
	return 0;
}