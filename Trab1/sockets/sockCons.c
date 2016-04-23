#include "sockUtils.h"

int createSocket(struct sockaddr_in * address, int port_num)
{
	int newSocket = socket(AF_INET, SOCK_STREAM, TCP_PROTOCOL);
	if (newSocket < 0)
	{
		perror("ERROR - Failed to Create Socket");
		exit(EXIT_FAILURE);
	}

	// NECESSÁRIO?
	bzero((char *) address, sizeof(*address));

	address->sin_family = AF_INET;
	address->sin_addr.s_addr = INADDR_ANY;
	address->sin_port = htons(port_num);

	if (bind(newSocket, address, sizeof(*address)) < 0)
	{
		perror("ERROR - Failed to Bind Socket");
		exit(EXIT_FAILURE);
	}

	return newSocket;
}

int main()
{
	struct sockaddr_in server_addr, client_addr;
	char buffer[BUFFER_SIZE];
	int port_num = PORT_NUM;

	int csocket = createSocket(&server_addr, port_num);

	if (listen(csocket, 1) < 0)
	{
		perror("CONSUMER ERROR - Failed Listen");
		exit(EXIT_FAILURE);
	}

	int size_buffer = sizeof(client_addr);

	int file_descriptor = accept(csocket, (struct sockaddr *) &client_addr, &size_buffer);
	if (file_descriptor < 0)
	{
		perror("ERROR - Failed to accept connection");
		exit(EXIT_FAILURE);
	}

	bzero(buffer, BUFFER_SIZE);

	if (read(file_descriptor, buffer, BUFFER_SIZE -1) < 0) // certeza q eh BUFFER_SIZE - 1???
	{
		perror("ERROR - Failed to read from socket\n");
		exit(EXIT_FAILURE);
	}

	// FALTA CHECAR SE NUMERO É PRIMO

	printf("Mensagem: %s", buffer);


    return 0;
}
