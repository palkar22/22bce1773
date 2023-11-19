#include <stdio.h>
 #include <stdlib.h>
 #include <string.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <unistd.h>
int main() {
int UDP_client_socket, sport = 6006, len, n; 
char sendmsg[100],rcvmsg[100];
UDP_client_socket = socket (AF_INET, SOCK_DGRAM, 0);
if (UDP_client_socket < 0)
 { perror("Can't Create Socket"); 
exit(1);
} 
else {
printf("Socket Created\n");
}
struct sockaddr_in servaddr; servaddr.sin_family = AF_INET; 
servaddr.sin_port = htons (sport); 
servaddr.sin_addr.s_addr =INADDR_ANY;
len = sizeof(servaddr);
while (1) {
bzero(sendmsg, sizeof(sendmsg)); printf("Input message: ");
n = 0;
while ((sendmsg[n++] = getchar()) != '\n');
sendto(UDP_client_socket, sendmsg, strlen(sendmsg), 0, (struct sockaddr *)&servaddr, len);
bzero(rcvmsg, sizeof(rcvmsg));
len = sizeof(servaddr);
recvfrom(UDP_client_socket, rcvmsg, sizeof(rcvmsg), 0, (struct sockaddr *)&servaddr, &len); printf("From server: %s\n", rcvmsg);
if (strncmp("bye", rcvmsg, 3) == 0) { break;
}
}
return 0;
}
