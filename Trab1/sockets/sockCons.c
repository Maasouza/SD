#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>

#define TCP_PROTOCOL 6

int createSocket(struct sockaddr_in * address, int port_num)
{
	int newSocket = socket(AF_INET, SOCK_STREAM, TCP_PROTOCOL);
	if (newSocket < 0)
	{
		perror("ERROR - Failed to create socket\n");
		exit(EXIT_FAILURE);
	}

	// NECESSÁRIO?
	bzero((char *) address, sizeof(*address));

	address->sin_family = AF_INET;
	address->sin_addr.s_addr = INADDR_ANY;
	address->sin_port = htons(port_num);

	if (bind(newSocket, address, sizeof(*address)) < 0)
	{
		perror("ERROR - Failed to bind");
		exit(EXIT_FAILURE);
	}

	return newSocket;
}

int main()
{
	struct sockaddr_in server_addr, client_addr;
	char buffer[64];
	int port_num = 5001;

	int csocket = createSocket(&server_addr, port_num);
	listen(csocket, 1);

	int size_buffer = sizeof(client_addr);

	int file_descriptor = accept(csocket, (struct sockaddr *) &client_addr, &size_buffer);
	if (file_descriptor < 0)
	{
		perror("ERROR - Failed to accept connection");
		exit(EXIT_FAILURE);
	}

	bzero(buffer, 64);

	if (read(file_descriptor, buffer, 63) < 0)
	{
		perror("ERROR - Failed to read from socket\n");
		exit(EXIT_FAILURE);
	}

	// FALTA CHECAR SE NUMERO É PRIMO

	printf("Mensagem: %s", buffer);


    return 0;
}
