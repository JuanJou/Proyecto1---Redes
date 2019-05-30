

struct sockaddr_in a;
struct sockaddr_in dest;
s = socket(AF_INET , SOCK_DGRAM , IPPROTO_UDP);

void sendRequestToServer(struct DNS_INFO * dns,unsigned char buffer, struct argumentos* args) {
	unsigned char *qname;
	int s;

	struct QUESTION *qinfo = NULL;
 
    dest.sin_family = AF_INET;
    dest.sin_port = htons(53);
    dest.sin_addr.s_addr = inet_addr(dns_servers[0]);

    dns->id = (unsigned short) htons(getpid());
    dns->qr = 0; //This is a query
    dns->opcode = 0; //This is a standard query
    dns->aa = 0; //Not Authoritative
    dns->tc = 0; //This message is not truncated
    dns->rd = args->formaDeConsulta; //Recursion Desired
    dns->ra = 0; //Recursion not available! hey we dont have it (lol)
    dns->z = 0;
    dns->ad = 0;
    dns->cd = 0;
    dns->rcode = 0;
    dns->q_count = htons(1); //we have only 1 question
    dns->ans_count = 0;
    dns->auth_count = 0;
    dns->add_count = 0;

    qname = dns + sizeof(struct DNS_INFO);

    qinfo = qname + strlen((const char*)qname) + 1;

    qinfo->qtype = htons( args->tipoDeConsulta );
    qinfo->qclass = htons(1); 

    printf("\nEnviando paquete...");
    if( sendto(s,(char*)buffer,sizeof(struct DNS_INFO) + (strlen((const char*)qname)+1) + sizeof(struct QUESTION),0,(struct sockaddr*)&dest,sizeof(dest)) < 0)
    {
        perror("Error al enviar paquete");
    }
    printf("Listo...");

    return;
}

struct DNS_INFO* receiveRequestToServer(struct DNS_INFO * dns, unsigned char buffer) {
	i = sizeof dest;
    printf("\nRecibiendo answer...");
    if(recvfrom (s,(char*)buffer , 65536 , 0 , (struct sockaddr*)&dest , (socklen_t*)&i ) < 0)
    {
        perror("Error al recibir paquete");
    }
    printf("Listo...");
 
    return buffer;
}