/*#include <sys/socket.h>
#include <sys/types.h>
//#include <netinet/in.h>
//#include <netdb.h>*/
#include "sockUtils.h"
int createSocket(struct sockaddr_in * address, int port_num){
    int socket;
    socket = socket(AF_INET,SOCK_STREAM,TCP_PROTOCOL);

    if(conn == -1){
        printf("Couldn't create socket");
    }
    puts("Socket created");

    address->sin_addr.s_addr = inet_addr(SERVER_ADDR);
    address->sin_family = AF_INET;
    address->sin_port = htons(port_num);

    return socket;
}

int main(){

    srand(time(NULL));
	char randomNum[BUFFER_SIZE];
    int conn;
    unsigned int number = 0;
    char reply[BUFFER_SIZE];
    struct sockaddr_in server_addr;

    conn = createSocket(&server_addr, PORT_NUM);

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
//        if(recv(conn,reply,BUFFER_SIZE,0)<0){
//            puts("Read failed");
//            close(conn);
//            exit(FAILED);
//        }
        printf("Number: %s\n",randomNum);
        if(recv(conn,reply,BUFFER_SIZE,0)<0){
            puts("Read failed");
            send(conn,)
            close(conn);
            exit(FAILED);
        }
        printf("Prime? %s\n\n",reply);
        sleep(1);

	}

	close(conn);


	return 0;
}
