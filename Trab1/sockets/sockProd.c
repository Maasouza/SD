#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>

int main(){
	int mysocket;
	mysocket = socket(AF_INET,SOCK_STREAM,6);
	if(mysocket == -1){
		printf("Fail to create\n");
	}
	printf("%d\n",mysocket);

	return 0;
}
