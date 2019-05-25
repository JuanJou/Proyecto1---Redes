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

void get_dns_name(int argc,char *argv[]) {
        

}

 
/*
 * This will convert www.google.com to 3www6google3com 
 * got it :)
 * */
void ChangetoDnsNameFormat(unsigned char* dns,unsigned char* host) 
{
    int lock = 0 , i;
    strcat((char*)host,".");
     
    for(i = 0 ; i < strlen((char*)host) ; i++) 
    {
        if(host[i]=='.') 
        {
            *dns++ = i-lock;
            for(;lock<i;lock++) 
            {
                *dns++=host[lock];
            }
            lock++; //or lock=i+1;
        }
    }
    *dns++='\0';
}
