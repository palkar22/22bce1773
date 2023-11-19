#include<sys/socket.h> 
#include<sys/types.h> 
#include<stdio.h>
#include<string.h>
#include<netinet/in.h>
 int main()
{
int sock,cport, val, count, i;
char sentdata [50], recvdata [50];
struct sockaddr_in servaddr;
int window_size,ACK, frame=0; printf("Enter the port number\n"); scanf("%d", &cport);
printf("Port number is %d\n", cport); sock=socket(AF_INET, SOCK_STREAM,0);
if(sock<0)
printf("Can't Create\n");
else
printf("Socket is created\n");
servaddr.sin_family=AF_INET;
servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
servaddr.sin_port=htons (cport);
if(connect (sock, (struct sockaddr *)&servaddr, sizeof(servaddr))<0)
 printf("Can't Connect\n");
else
printf("Connected\n");
printf("Enter the window size\n");
scanf("%d",&window_size);
send (sock, &window_size, sizeof(window_size),0); 
while(frame<window_size){
for(i=0;i<window_size; i++)
{
printf("Transmitted Frames to the Server %d\n", frame);
send(sock, &frame, sizeof(frame),0);
frame++;
if(frame==window_size)
break;
}
recv(sock, &ACK, sizeof(ACK),0);
printf("The Negative Acknowledgement recieved from the server is %d\n",ACK);
if(ACK==window_size)
break;
else
frame=ACK;
}
return 0;
}
