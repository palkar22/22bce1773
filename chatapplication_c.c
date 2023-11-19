#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<string.h>
int main(){
int sd,sd2,sport=6006,nsd,len;
sd=socket(AF_INET,SOCK_STREAM,0);
char sendmsg[100],rcvmsg[100];
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
sd2=connect(sd,(struct sockaddr*)&servaddr,sizeof(servaddr));
if(sd2<0){
printf("Cannot connect.\n");
}
else{
printf("Connected.\n");
recv(sd,rcvmsg,100,0);
printf("Message read %s",rcvmsg);
do{
fgets(sendmsg,20,stdin);
len=strlen(sendmsg);
sendmsg[len-1]='\0';
send(sd,sendmsg,20,0);
recv(sd,rcvmsg,20,0);
printf("%s\n",rcvmsg);
}
while(strcmp(rcvmsg,"bye")!=0);
close(sd);
close(nsd);
}
close(nsd);
return 0;
}
