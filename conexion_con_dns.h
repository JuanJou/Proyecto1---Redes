#include<stdio.h> //printf
#include<string.h>    //strlen
#include<stdlib.h>    //malloc
#include<sys/socket.h>    //you know what this is for
#include<arpa/inet.h> //inet_addr , inet_ntoa , ntohs etc
#include<netinet/in.h>
#include<unistd.h>
#include "./dnsquery.h"

void ngethostbyname (unsigned char* , int);
void ChangetoDnsNameFormat(unsigned char* dns,unsigned char* host);