#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include "./dnsquery.h"

int validar_argumentos(int argc, char*argv);
void get_dns_from_resolv();