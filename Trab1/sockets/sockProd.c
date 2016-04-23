/*#include <sys/socket.h>
#include <sys/types.h>
//#include <netinet/in.h>
//#include <netdb.h>*/
#include "sockUtils.h"

int main(){

	unsigned long randomNum = 0;

	// Conecta ao socket
	if (connect())
	{
		perror("ERROR - Failed to Connect");
		exit(EXIT_FAILURE);
	}

	// gera um numero
	// aguarda resposta
	// imprime

	return 0;
}
