#include <stdio.h> 
#include <stdlib.h>
 #include <string.h> 
#include <unistd.h> 
#include <arpa/inet.h>
#include <time.h>
int main()
{
time_t ticks;
ticks=time(NULL);
int UDP_server_socket, bind_test, clilen, sport=6006, n; char sendmsg[40], rcmsg[40];
UDP_server_socket = socket (AF_INET, SOCK_DGRAM, 0);
if (UDP_server_socket < 0) {
printf("Can't create socket\n");
} else {
printf("Socket Created\n");
struct sockaddr_in servaddr, cli;
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr= htonl(INADDR_ANY);
servaddr.sin_port = htons(sport);
bind_test = bind(UDP_server_socket, (struct sockaddr *)&servaddr, sizeof(servaddr));
printf("Binded\n");
clilen=sizeof(servaddr);
bzero(rcmsg, 40);
while (1) {
recvfrom(UDP_server_socket, rcmsg, 40, 0, (struct sockaddr *)&servaddr, &clilen);
 printf("From client: %s\n", rcmsg);
bzero(rcmsg, 40);
n = 0;
bzero(sendmsg, 40);
printf("Input message: ");
while ((sendmsg[n++] = getchar()) != '\n');
sendto(UDP_server_socket, sendmsg, 40, 0, (struct sockaddr *)&servaddr, clilen);
 if (strncmp("bye", sendmsg, 3) == 0)
break;
}
close(UDP_server_socket);
}
return 0;
}
