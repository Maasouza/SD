#include "sockUtils.h"


int createSocket(struct sockaddr_in * address, int port_num)
{
	int newSocket = socket(AF_INET, SOCK_STREAM, TCP_PROTOCOL);
	if (newSocket < 0)
	{
		perror("ERROR - Failed to Create Socket");
		exit(EXIT_FAILURE);
	}
	puts("Socket created");

	bzero((char *) address, sizeof(*address));

	address->sin_family = AF_INET;
	address->sin_addr.s_addr = INADDR_ANY;
	address->sin_port = htons(port_num);

	if (bind(newSocket,address, sizeof(*address)) < 0)
	{
		perror("ERROR - Failed to Bind Socket");
		exit(EXIT_FAILURE);
	}

	return newSocket;
}

int isPrime(int v){
    int i;
    for(i=2;i<v;i++){
        if(v%i==0){
            return 0;
        }
    }
    return 1;
}

int main(int argc , char *argv[]){
	struct sockaddr_in server_addr, client_addr;
	char buffer[BUFFER_SIZE];
	int port_num = PORT_NUM;
	int reading;
	int value;
	char *msg;
	char *prime;

	if(argc >1){

        port_num = atoi(argv[1]);
        printf("Using port and ip: %d \n",port_num);    

    }else{

        printf("Using default port : %d \n",port_num);

    }

	int csocket = createSocket(&server_addr, port_num);

	puts("Waiting connection...\n");
	if (listen(csocket, 1) < 0)
	{
		perror("CONSUMER ERROR - Failed Listen");
		exit(EXIT_FAILURE);
	}

	int size_buffer = sizeof(client_addr);

	int file_descriptor = accept(csocket, (struct sockaddr *) &client_addr, (socklen_t * ) &size_buffer);
	if (file_descriptor < 0)
	{
		perror("ERROR - Failed to accept connection");
		exit(EXIT_FAILURE);
	}
	puts("connection accept\n");

	bzero(buffer, BUFFER_SIZE);

	while (1) {
		if ((reading = recv(file_descriptor, buffer, BUFFER_SIZE,0)) < 0) // certeza q eh BUFFER_SIZE - 1???
		{
			perror("ERROR - Failed to read from socket\n");
			exit(EXIT_FAILURE);
	  }
		if(reading == 0)
	  {
	    puts("Client disconnected\n");
	    fflush(stdout);
	    exit(0);
	  }

    value = atoi(buffer);
    if(value==0){
        printf("End - Consume\n");
        exit(0);
    }

    switch(isPrime(value)){
        case 0:
                prime = "No";
                break;
        case 1:
                prime = "Yes";
                break;
    }

		send(file_descriptor , prime , sizeof(msg),0);

		if(value==0){

			printf("Zero received!\n");
		}

	}



    return 0;
}
