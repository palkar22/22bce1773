#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

int main() {
    int len, listenfd, i = 0, r, port;
    char buff[20], c;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t servlen;

    listenfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (listenfd == -1) {
        perror("socket");
        exit(-1);
    }

    memset(servaddr.sin_zero, '\0', sizeof(servaddr.sin_zero));
    printf("\n Enter the port number: ");
    scanf("%d", &port);
    printf("\n Port number is: %d", port);

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(port);

    printf("\n Client: ");

    do {
        int val = read(0, buff, sizeof(buff));
        if (val == -1) {
            perror("Read error");
            exit(-1);
        }

        int s = sendto(listenfd, buff, val, 0, (struct sockaddr*)&servaddr, sizeof(servaddr));
        if (s == -1) {
            perror("Send error");
            exit(-1);
        }

        len = sizeof(cliaddr);
        r = recvfrom(listenfd, buff, sizeof(buff), 0, (struct sockaddr*)&servaddr, &len);
        if (r == -1) {
            perror("Receive error");
            exit(-1);
        }
        write(1, buff, r);
    } while (strcmp(buff, "bye") != 0);

    return 0;
}
