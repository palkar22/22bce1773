#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

int main() {
    int sd, sd2, clilen, sport, i, connect, count = 0, val = 0;
    int port;
    char data[50];
    char senderdata[50];
    struct sockaddr_in servaddr, cliaddr;
    printf("Enter server port\n");
    scanf("%d", &sport);
    printf("%d\n", sport);
    sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd < 0) {
        printf("can't create socket\n");
        exit(1);
    } else
        printf("Socket created\n");

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(sport);
    sd2 = bind(sd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    if (sd2 < 0) {
        printf("can't bind\n");

        exit(1);
    } else
        printf("Binded\n");
    listen(sd, 5);

    clilen = sizeof(cliaddr);
    connect = accept(sd, (struct sockaddr*)&cliaddr, &clilen);
    if (connect < 0) {
        printf("can't accept\n");

        exit(1);
    } else
        printf("Accepted \n");
    bzero(senderdata, 50);
    while (1) {
        recv(connect, &val, sizeof(val), 0);
        i = recv(connect,&data, sizeof(data), 0);
        data[i] = '\0';
        if (strcmp(data, "end") == 0) {
            printf("\n Finished");
            break;
        }
        if (count != val) {
            strcpy(senderdata, "frame missing");
            send(connect, &count, sizeof(count), 0);
            send(connect, senderdata, strlen(senderdata), 0);
        } else {
            printf("\n The frame Number is: %d", val);
            printf("\n The data is: %s", data);
            count++;
            strcpy(senderdata, "send nextdata");
            send(connect, &count, sizeof(count), 0);
            send(connect, senderdata, strlen(senderdata), 0);
        }
        printf("\n The Expected frame now is: %d\n", count);
    }
    return 0;
}
