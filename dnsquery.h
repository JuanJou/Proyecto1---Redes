//Author : Silver Moon (m00n.silv3r@gmail.com)
//Dated : 29/4/2009
 
//Header Files
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
//List of DNS Servers registered on the system

char dns_servers[10][100];
int dns_server_count = 0;
//Types of DNS resource records :)
 
#define T_A 1 //Ipv4 address
#define T_NS 2 //Nameserver
#define T_LOC 29 /* domain name pointer */
#define T_MX 15 //Mail server
 
//Function Prototypes

void ChangetoDnsNameFormat (unsigned char*,unsigned char*);
int validar_argumentos(int argc, char* argv[]);
unsigned char* ReadName (unsigned char*,unsigned char*,int*);
void get_dns_servers();
 
char* consulta;
char* nameServer;
char* puerto;
char* tipoDeConsulta = "a";
int a;
int mx;
int loc;
char* formaConsulta = "r";
int r;
int t;
int ayuda;

//DNS header structure
struct DNS_HEADER
{
    unsigned short id; // identification number
 
    unsigned char rd :1; // recursion desired
    unsigned char tc :1; // truncated message
    unsigned char aa :1; // authoritive answer
    unsigned char opcode :4; // purpose of message
    unsigned char qr :1; // query/response flag
 
    unsigned char rcode :4; // response code
    unsigned char cd :1; // checking disabled
    unsigned char ad :1; // authenticated data
    unsigned char z :1; // its z! reserved
    unsigned char ra :1; // recursion available
 
    unsigned short q_count; // number of question entries
    unsigned short ans_count; // number of answer entries
    unsigned short auth_count; // number of authority entries
    unsigned short add_count; // number of resource entries
};
 
//Constant sized fields of query structure
struct QUESTION
{
    unsigned short qtype;
    unsigned short qclass;
};
 
//Constant sized fields of the resource record structure
#pragma pack(push, 1)
struct R_DATA
{
    unsigned short type;
    unsigned short _class;
    unsigned int ttl;
    unsigned short data_len;
};
#pragma pack(pop)
 
//Pointers to resource record contents
struct RES_RECORD
{
    unsigned char *name;
    struct R_DATA *resource;
    unsigned char *rdata;
};
 
//Structure of a Query
typedef struct
{
    unsigned char *name;
    struct QUESTION *ques;
} QUERY;

struct SOA
{
    unsigned int serial;
    int refresh;
    int retry;
    int expire;
    unsigned int minimum;
};

void main(int argc, char* argv[]);