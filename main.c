

void main(int argc, char* argv[]) {

	unsigned char bufferForInfo[256];
	struct DNS_INFO* dnsInfo = (struct DNS_INFO*) $bufferForInfo;
	struct argumentos* argumentos = malloc(sizeof(struct argumentos));
	struct RES_RECORD answers[20],auth[20],addit[20];

	argumentos->tipoDeConsulta = T_A;
	argumentos->formaDeConsulta = RE;
	argumentos->nameserver = getNameServerFromResolv();
	
	if (!validarArgumentos(argc,argv)) {
		printf("Argumentos invalidos\n");
		return 1;
	}

    if (strcmp(argumentos->formaDeConsulta,2)) {
        argumentos->nameserver = ".";
    }

	sendRequestToTheServer(dnsInfo, bufferForInfo,argumentos);
	bufferForInfo = receiveRequestFromServer(dnsInfo, bufferForInfo);

	dnsInfo = (struct DNS_INFO*) bufferForInfo;

	unsigned char* reader = &bufferForInfo[sizeof(struct DNS_HEADER) + (strlen((const char*)qname)+1) + sizeof(struct QUESTION)];


	answers = readAnswers(dnsInfo,reader);
	auth = readAuthorities(dnsInfo,reader);
	addit = readAdditional(dnsInfo,reader);

	printResponse(dnsInfo,answers,auth,addit);

	free(dnsInfo);

}

int validarArgumentos(int argc, char* argv[]) {
	return 1;
}

unsigned char getNameServerFromResolv() {
	FILE *fp;
    char line[200];
    char* p;
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
        }
    }
     
    return *p;
}

int stop=0;

struct RES_RECORD[] readAnswers(struct DNS_INFO dns,unsigned char buff[]) {
	
 	struct RES_RECORD answers[20];

    for(i=0;i<ntohs(dns->ans_count);i++)
    {
        answers[i].name=ReadName(reader,buf,&stop);
        reader = reader + stop;
 
        answers[i].resource = (struct R_DATA*)(reader);
        reader = reader + sizeof(struct R_DATA);
        int response_type = ntohs(answers[i].resource->type);
        answers[i].rdata = (unsigned char*)malloc(ntohs(answers[i].resource->data_len));

        if(response_type == T_A)
        {
 
            for(j=0 ; j<ntohs(answers[i].resource->data_len) ; j++)
            {
                answers[i].rdata[j]=reader[j];
            }
 
            answers[i].rdata[ntohs(answers[i].resource->data_len)] = '\0';
 
            reader = reader + ntohs(answers[i].resource->data_len);
        }
        else
        {
            if (response_type == T_MX) {
                *answers[i].rdata = *(reader+1);
                reader += sizeof(short);
                answers[i].rdata += sizeof(short);
                ReadName(reader,buf,&stop,answers[i].rdata); 
                answers[i].rdata -= sizeof(short);
                reader += stop;
            }
            else {
                if (response_type == T_LOC)
                {
                    loc_ntoa(reader);
                }
                else {
                    printf("Wrong type\n");
                }
            }
        }
    }
    return answers;
}


struct RES_RECORD[] readAuthorities(struct DNS_INFO dns,unsigned char buff[]) {
	
	struct RES_RECORD auth[20];

    for(i=0;i<ntohs(dns->auth_count);i++)
    {
        auth[i].name=ReadName(reader,buf,&stop);
        reader+=stop;
 
        auth[i].resource=(struct R_DATA*)(reader);
        reader+=sizeof(struct R_DATA);
 
        auth[i].rdata=ReadName(reader,buf,&stop);
        reader+=stop;
    }
    return auth;
}

struct RES_RECORD[] readAdditional(struct DNS_INFO dns,unsigned char buff[]) {

	struct RES_RECORD addit[20];

	for(i=0;i<ntohs(dns->add_count);i++)
    {
        addit[i].name=ReadName(reader,buf,&stop);
        reader+=stop;
 
        addit[i].resource=(struct R_DATA*)(reader);
        reader+=sizeof(struct R_DATA);
 
        if(ntohs(addit[i].resource->type)==1)
        {
            addit[i].rdata = (unsigned char*)malloc(ntohs(addit[i].resource->data_len));
            for(j=0;j<ntohs(addit[i].resource->data_len);j++)
            addit[i].rdata[j]=reader[j];
 
            addit[i].rdata[ntohs(addit[i].resource->data_len)]='\0';
            reader+=ntohs(addit[i].resource->data_len);
        }
        else
        {
            addit[i].rdata=ReadName(reader,buf,&stop);
            reader+=stop;
        }
    }
    return addit;
}

printResponse(struct DNS_HEADER* dns, struct RES_RECORD* answers, struct RES_RECORD* answers, struct RES_RECORD* answers) {
    printf("\nAnswer Records : %d \n" , ntohs(dns->ans_count) );
    
    int i;

    for(i=0 ; i < ntohs(dns->ans_count) ; i++)
    {
        printf("Name : %s ",answers[i].name);
 
        if( ntohs(answers[i].resource->type) == T_A) //IPv4 address
        {
            long *p;
            p=(long*)answers[i].rdata;
            a.sin_addr.s_addr=(*p); //working without ntohl
            printf("has IPv4 address : %s",inet_ntoa(a.sin_addr));
        }
         
        if(ntohs(answers[i].resource->type)==5) 
        {
            //Canonical name for an alias
            printf("has alias name : %s",answers[i].rdata);
        }
 
        printf("\n");
    }

    
    //print authorities
    printf("\nAuthoritive Records : %d \n" , ntohs(dns->auth_count) );
    for( i=0 ; i < ntohs(dns->auth_count) ; i++)
    {
         
        printf("Name : %s ",auth[i].name);
        if(ntohs(auth[i].resource->type)==2)
        {
            printf("has nameserver : %s",auth[i].rdata);
        }
        printf("\n");
    }
 
    //print additional resource records
    printf("\nAdditional Records : %d \n" , ntohs(dns->add_count) );
    for(i=0; i < ntohs(dns->add_count) ; i++)
    {
        printf("Name : %s ",addit[i].name);
        if(ntohs(addit[i].resource->type)==1)
        {
            long *p;
            p=(long*)addit[i].rdata;
            a.sin_addr.s_addr=(*p);
            printf("has IPv4 address : %s",inet_ntoa(a.sin_addr));
        }
        printf("\n");
    }
    return;
}