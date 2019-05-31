#include<stdio.h> //printf
#include<string.h>    //strlen
#include<stdlib.h>    //malloc
#include<sys/socket.h>    //you know what this is for
#include<arpa/inet.h> //inet_addr , inet_ntoa , ntohs etc
#include<netinet/in.h>
#include<unistd.h>    //getpid
#include "./validar_entrada.h"
#include "./conexion_con_dns.h"
#include "./location.h"

#define T_A 1
#define T_NS 2 
#define T_LOC 29
#define T_MX 15

#define RE 1
#define IT 2

void main(int argc, char* argv[]);
int validarArgumentos(int argc, char* argv[]);