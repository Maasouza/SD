#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


//define
#define READ 0
#define WRITE 1


int fd[2];

//prototypes
void consume_prod(char*);
int isPrime(int);
void new_producer(int nP);

void producer(int nP){
    int value = 1;
    char sValue[8];

    close(fd[READ]); //Close read end.

    int i;
    for(i=0;i<nP;i++){
           srand (time(NULL));
           value+=rand()%101;
           sprintf(sValue, "%d", value);
           write(fd[WRITE],sValue,sizeof(sValue)); //Insert newprod.
    }
    value=0;
    sprintf(sValue, "%d", value);
    write(fd[WRITE],sValue,(strlen(sValue)+1)); //Insert last product.
    printf("End - Producer\n");
    close (fd[WRITE]); //Close write end.
    exit(0);
}

void consumer(){

    int i;
    int resp;
    char valueBuffer[8];
    close (fd[WRITE]); //Close write end.

    while( 1 ){
       //Read pipe
       resp = read(fd[READ],valueBuffer,sizeof(valueBuffer));
       if(resp==-1){
           printf("Read error\n");
       }
       else if(resp==0){
            printf("Pipe empty");
       }
       else{
           consume_prod(&valueBuffer);
       }
    }
    close (fd[READ]); //Close read end.
}


int isPrime(int v){
    int i;
    for(i=2;i<v;i++){
        if(v%i==0){
            return 0;
        }
    }
    if(i == v){
        return 1;
    }
}

void consume_prod(char* sValue){
    int prime;
    int value;
    value= atoi(sValue);
    if(value==0){
        printf("End - Consume\n");
        exit(0);
    }
    prime = isPrime(value);
    printf("\nValue: %d\nPrime Number: %d\n\n",value,prime);

}


int main(){

pipe(fd); //create pipe

int newprocess;

    newprocess = fork();
    if(newprocess==-1){
       printf("Fail to fork");
    }
    else if(newprocess==0){
       producer(50);
       exit(0);
    }else{
       consumer();
       exit(0);
    }

exit(0);
}
