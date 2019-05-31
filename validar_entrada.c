#include "validar_entrada.h"

int validar_argumentos(int argc , char *argv[]) {
    if ((argc > 6) || (argc < 2)) {
        return 0;
    }
    if (strcmp(argv[1],"-h") == 0 ) {
        printf("Ejecutar el programa con la siguiente sintaxis: dnsquery  consulta @servidor[:puerto] [-a | -mx | -loc] [-r | -t] [-h]\n");
        ayuda = 1;
        return 1;
    }

    consulta = argv[1];
    int i;
    for (i = 2; i < argc ; i++) {
        if (argv[i][0] == '@') {
            nameServer = argv[2]+1;
            continue;
        }
        if (((strcmp(argv[i],"-mx") == 0) || (strcmp(argv[i],"-loc") == 0) || (strcmp(argv[i],"-a") == 0))) {
            tipoDeConsulta = argv[i];
            continue;
        }

        if ((strcmp(argv[i],"-r") == 0) || (strcmp(argv[i],"-t")) == 0) {
            formaConsulta = argv[i];
            continue;
        }

    }
    return 1;
    
}


/*
 * Get the DNS servers from /etc/resolv.conf file on Linux
 * */
void get_dns_from_resolv()
{
    FILE *fp;
    char line[200];
    char p;
    if((fp = fopen("/etc/resolv.conf" , "r")) == NULL)
    {
        printf("Failed opening /etc/resolv.conf file \n");
    }
     
    while(fgets(line , 200 , fp))
    {
        if(line[0] == '#')
        {
            continue;
        }
        if(strncmp(line , "nameserver" , 10) == 0)
        {
            p = strtok(line , " ");
            p = strtok(NULL , " ");
             
            //p now is the dns ip :)
            //????
        }
    }
     
    strcpy(dns_servers[0] , "208.67.222.222");
    strcpy(dns_servers[1] , "208.67.220.220");
}