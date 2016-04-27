#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

// Useful definitions
#define PORT_NUM 5001
#define BUFFER_SIZE 32
#define FAILED 1

// Control Definitions (don't change)
#define TCP_PROTOCOL 6
#define SERVER_ADDR "127.0.0.1"
