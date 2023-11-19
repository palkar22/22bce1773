#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

int main() {
    int sock, cport, val, count, i;
    char sentdata[50], recvdata[50];
    struct sockaddr_in servaddr;

    printf("Enter the port: ");
    scanf("%d", &cport);

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Can't create socket");
        return 1;
    } else {
        printf("Socket is created\n");
    }

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    servaddr.sin_port = htons(cport);

    if (connect(sock, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        perror("Can't connect");
        close(sock);
        return 1;
    } else {
        printf("Connected\n");
    }

    while (1) {
        printf("\nEnter Frame Number: ");
        scanf("%d", &val);
        send(sock, &val, sizeof(val), 0);

        printf("Enter data: ");
        scanf("%s", sentdata);
        send(sock, sentdata, strlen(sentdata), 0);

        if (strcmp(sentdata, "end") == 0)
            break;

        recv(sock, &count, sizeof(count), 0);
        i = recv(sock, recvdata, sizeof(recvdata) - 1, 0);

        if (i < 0) {
            perror("recv error");
            break;
        }

        recvdata[i] = '\0';
        printf("\nReceived: %s Count: %d\n", recvdata, count);
    }

    close(sock);
    return 0;
}
