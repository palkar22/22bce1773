#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include<string.h>
int main()
{
	int sd,nsd;
	unsigned int clilen;
	sd=socket(AF_INET,SOCK_STREAM,0);
	if(sd<0){
	printf("SOCKET NOT CREATED\n");
	}
	else{
	printf("SOCKET CREATED\n");
	}
	struct sockaddr_in servaddr,cliaddr;
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(6000);
	if(bind(sd,(struct sockaddr *)&servaddr,sizeof(servaddr))<0)
	{
	printf("CANNOT BIND\n");
	}
	else{
	printf("BINDED SUCCESSFULLY\n");
	}
	listen(sd,5);
	clilen=sizeof(cliaddr);
	nsd=accept(sd,(struct sockaddr *)&cliaddr,&clilen);
	if(nsd<0){
	printf("CANT ACCEPT\n");
	}
	else{
	printf("ACCEPT\n");
	}
	close(sd);
	close(nsd);
	return 0;
	
}

