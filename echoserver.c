#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
int main() {
    int len, sfd, b, r, s, port;
    char buff[20];
    struct sockaddr_in servaddr, cliaddr;

    sfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sfd == -1) {
        perror("socket");
        exit(-1);
    }

    memset(servaddr.sin_zero, '\0', sizeof(servaddr.sin_zero));
    printf("\n Enter port number: ");
    scanf("%d", &port);
    printf("\n Port number is %d", port);

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(port);
    b = bind(sfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    
    if(b == -1) {
        perror("bind");
        exit(-1);
    }

    len = sizeof(cliaddr); // Initialize len
    do {
        r = recvfrom(sfd, buff, sizeof(buff), 0, (struct sockaddr*)&cliaddr, &len);
        if(r == -1) {
            perror("Receive Error");
            exit(0);
        }
        write(1, buff, r); // Print received message
        s = sendto(sfd, buff, r, 0, (struct sockaddr*)&cliaddr, sizeof(cliaddr));
        if(s == -1) {
            perror("Send Error");
            exit(0);
        }
    } while(strcmp(buff, "bye") != 0);

    return 0;
}
