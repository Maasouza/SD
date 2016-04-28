#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

// Useful definitions
#define PORT_NUM 5001
#define BUFFER_SIZE 32
#define FAILED 1

//colors
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define RESET "\x1b[0m"


// Control Definitions (don't change)
#define TCP_PROTOCOL 6
#define DEFAULT_IP_ADDR "127.0.0.1"

