#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
int main()
{
	int csd,len,cport=6009;
	char sendmsg[20],recvmsg[20];
	struct sockaddr_in servaddr;
	csd=socket(AF_INET,SOCK_STREAM,0);
	if(csd<0){
	printf("CANT socket\n");
	}
	else{
	printf(" socket created  \n");
	}
		servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(cport);
	if(connect(csd,(struct sockaddr*)&servaddr,sizeof(servaddr))>0)
	{
	printf("CANT CONNECT \n");
	}
	else{
	printf("CONNECTED \n");
	}
	recv(csd,recvmsg,20,0);
	printf("%s",recvmsg);
	send(csd,recvmsg,20,0);
	return 0;
	
}
