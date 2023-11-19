/*#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<string.h>
//#include<time.h>
int main(){
//time_t ticks;
int sd,sd2,sport=6006,nsd,len,clilen;
sd=socket(AF_INET,SOCK_STREAM,0);
char sendmsg[100],rcvmsg[100];
//ticks =time(NULL);
//strcpy(sendmsg,ctime(&ticks));
if(sd<0){
printf("Cannot create a socket.\n");
}
else{
printf("Socket is created.\n");
}
struct sockaddr_in servaddr,cliaddr;
servaddr.sin_family=AF_INET;
servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
servaddr.sin_port=htons(sport);
sd2=bind(sd,(struct sockaddr*)&servaddr,sizeof(servaddr));
if(sd2<0){
printf("Cannot bind.\n");
}
else{
printf("Binded.\n");
}
listen(sd,5);
clilen=sizeof(cliaddr);
nsd=accept(sd,(struct sockaddr*)&cliaddr,&clilen);
if(nsd<0){
printf("Cannot Accept.\n");
}
else{
printf("Accepted.\n");
send(nsd,sendmsg,100,0);
do{
recv(nsd,rcvmsg,20,0);
printf("%s\n",rcvmsg);
fgets(sendmsg,20,stdin);
len=strlen(sendmsg);
sendmsg[len-1]='\0';
send(nsd,sendmsg,20,0);
printf("%s\n",sendmsg);
}
while(strcmp(rcvmsg,"bye")!=0);
close(sd);
close(nsd);
}
return 0;
}
*/
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<string.h>
int main()
{
	int sd,nsd,len,sport=6006;
	unsigned int clilen;
	char sendmsg[100],rcvmsg[100];
	sd=socket(AF_INET,SOCK_STREAM,0);
	if(sd<0)
	{
	printf("not ACCEPT");
	}
	else
	{
	printf("ACCELPT\n");
	}
	struct sockaddr_in servaddr,cliaddr;
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(sport);
	if(bind(sd,(struct sockaddr *)&servaddr,sizeof(servaddr))<0)
	{
	printf("CANT BIND\n");
	}
	else{
	printf("BIND\n");
	}
	listen(sd,5);
	clilen=sizeof(cliaddr);
	nsd=accept(sd,(struct sockaddr *)&cliaddr,&clilen);
	if(nsd<0)
	{
	printf("CANT ACCEPT\n");}
	
else{
printf("Accepted.\n");
send(nsd,sendmsg,100,0);
do{
recv(nsd,rcvmsg,20,0);
printf("%s\n",rcvmsg);
fgets(sendmsg,20,stdin);
len=strlen(sendmsg);
sendmsg[len-1]='\0';
send(nsd,sendmsg,20,0);
printf("%s\n",sendmsg);
}
while(strcmp(rcvmsg,"bye")!=0);
close(sd);
close(nsd);
}
return 0;
}
	
	
