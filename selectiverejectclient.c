#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
int main() {
    int csd,cport,len,windowsize=0,headersize=0,i=0,ack=0,sendframe=0;
    char sendmsg[100], rcvmsg[100];
    struct sockaddr_in servaddr, cliaddr;
    printf("Enter the server port\n");
    scanf("%d",&cport);
    printf("%d\n",cport);
    csd = socket(AF_INET, SOCK_STREAM, 0);
    if (csd < 0) {
        printf("Cannot create a socket.\n");
    } else {
        printf("Socket is created.\n");
    }
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(cport);
    if (connect(csd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        printf("Cannot connect.\n");
    }
    else {
        printf("Connected.\n");
    }
    printf("Enter the header size\n");
    scanf("%d",&headersize);
    printf("Enter the window size\n");
    scanf("%d",&windowsize);
    send(csd,&headersize,sizeof(headersize),0);
    send(csd,&windowsize,sizeof(headersize),0);
    while(1){
    	while(i<windowsize){
    		printf("Enter 1 to send or 0 to not send frame number : %d\n",i);
    		scanf("%d",&sendframe);
    		if(sendframe){
    			send(csd,&i,sizeof(i),0);
    		}
    		else{
    			send(csd,&headersize,sizeof(headersize),0);
    		}
    		i++;
    	}
    	printf("Waiting for acknowledgement\n");
    	recv(csd,&ack,sizeof(ack),0);
    	if(ack==0){
    		printf("Sending complete\n");
    		break;
    	}
    	if(ack==windowsize){
    		windowsize+=windowsize;
    	}
    	if(ack<=0){
    		ack=ack*-1;
    		printf("Enter 1 to send or 0 to not send frame number : %d\n",ack);
    		scanf("%d",&sendframe);
    		if(sendframe){
    			send(csd,&ack,sizeof(ack),0);
    		}
    		else{
    			send(csd,&headersize,sizeof(headersize),0);
    		}
    	}
    }
    close(csd);
    return 0;
}
