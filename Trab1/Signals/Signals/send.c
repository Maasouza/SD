#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>

#define SUCCESS 0


int main(int argc, char * argv[])
{
	
	printf("pid = %d\n", getpid());
	//if (proc_id == )

	if (argc < 3)
	{
		printf("Parameter Missing - Expecting PID and SIGNAL values\n");
	}
	else
	{
		long proc_id = strtol(argv[1], NULL, 10);
		long sig_value = strtol(argv[2], NULL, 10);

		if (kill(proc_id, sig_value) != 0)
		{
			printf("ERROR - Process with PID = %s does not exist\n", argv[1]);
		}
	}

	return 0;
}