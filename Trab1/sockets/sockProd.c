#include "sockUtils.h"

int port_num = PORT_NUM;
char * ip_addr;


int createSocket(struct sockaddr_in * address, int port_num){
    int sock;
    sock = socket(AF_INET,SOCK_STREAM,TCP_PROTOCOL);

    if(sock == -1){
        printf("Couldn't create socket");
    }
    puts("Socket created");

    address->sin_addr.s_addr = inet_addr(ip_addr);
    address->sin_family = AF_INET;
    address->sin_port = htons(port_num);

    return sock;
}

int main(int argc , char *argv[]){
    srand(time(NULL));
    char randomNum[BUFFER_SIZE];
    int conn;
    char *color;
    unsigned int number = 0;
    char reply[BUFFER_SIZE];
    struct sockaddr_in server_addr;

    if(argc == 3){

        ip_addr = argv[1];
        port_num = atoi(argv[2]);        

    }else{
        ip_addr = DEFAULT_IP_ADDR;
        printf("Using default port and ip addres: %d ; %s \n",port_num,DEFAULT_IP_ADDR);

    }

   

    conn = createSocket(&server_addr, port_num);

    // Conecta ao socket
	if(connect(conn,(struct sockaddr * )&server_addr,sizeof(server_addr))<0)
	{
		perror("ERROR - Failed to Connect");
		exit(EXIT_FAILURE);
	}
	puts("Connected");

	while(1){

        number += rand()%11+1;
        sprintf(randomNum, "%d", number);
        if(send(conn,randomNum,strlen(randomNum),0)< 0)
        {
            puts("Write failed");
            close(conn);
            exit(FAILED);
        }

        printf("Number: %s\n",randomNum);
        if(recv(conn,reply,BUFFER_SIZE,0)<0){
            puts("Read failed");
            close(conn);
            exit(FAILED);
        }
        if(reply[0]=='N')
            color = RED;
        else if(reply[0]=='Y')
            color = GREEN;

        printf("Prime? %s%s\n\n" RESET,color,reply);
        fflush(stdout);
        sleep(1);

	}

	close(conn);


	return 0;
}
