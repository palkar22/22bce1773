#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<stdlib.h>
int main(){
int sd,sd2, clilen, sport, client_socket, count=0,val;
int port;
char data [50], senderdata [50];
int window_size;
int frame=0;
int ACK;
struct sockaddr_in servaddr, cliaddr;
printf("Enter Server Port\n");
scanf("%d", &sport);
printf("%d", sport);
sd=socket(AF_INET, SOCK_STREAM, 0);
if(sd<0)
printf("Can't Create\n");
else
printf("Socket created\n");
servaddr.sin_family=AF_INET;
servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
servaddr.sin_port=htons (sport);
sd2-bind(sd, (struct sockaddr *)&servaddr,sizeof(servaddr));
if(sd2<0)
printf("Can't Create\n");
else
printf("Socket Created\n");
listen(sd, 5);
clilen=sizeof(cliaddr);
client_socket-accept(sd, (struct sockaddr *)&cliaddr,&clilen); if(client_socket<0)
printf("Can't Accept\n");
else
printf("Accept");
recv(client_socket, &window_size, sizeof(window_size),0);
while(frame<window_size)
{
for(int i=0;i<window_size; i++)
{
recv(client_socket,&frame, sizeof(frame),0);
printf("Transmitted frames received from the client is %d\n", frame);
frame++;
if(frame==window_size)
break;
}
printf("Enter the negative Acknowledgement to be sent to the client\n"); scanf("%d", &ACK);
send(client_socket, &ACK, sizeof (ACK),0);
if(ACK==window_size)
break;
else
frame=ACK;
}
return 0;
}
