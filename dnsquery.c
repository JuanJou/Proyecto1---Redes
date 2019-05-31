#include "./dnsquery.h"

int main( int argc , char *argv[])
{
    if (validar_argumentos(argc, argv)) {
        printf("%s %s %s %s\n", nameServer, tipoDeConsulta, formaConsulta, consulta );
        return 1;
    }
    else {
        printf("Error en los argumentos\n");
        return 0;
    }

    unsigned char hostname[100];
 
    //Get the DNS servers from the resolv.conf file
    get_dns_servers(argv);
     
    //Get the hostname from the terminal
    printf("Enter Hostname to Lookup : ");
    scanf("%s" , hostname);
     
    //Now get the ip of this hostname , A record
    ngethostbyname(hostname , T_A);
 
    return 0;
}

