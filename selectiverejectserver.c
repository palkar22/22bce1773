#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
int main() {
    int sd,sd2,nsd,clilen,sport,len,port,i=0,j=0,k=0,windowsize=0,wsize=0,ack=0,headersize=0;
    char sendmsg[100],rcvmsg[100]="1";
    struct sockaddr_in servaddr,cliaddr;
    printf("Enter the server port :\n");
    scanf("%d",&sport);
    printf("%d\n",sport);
    sd=socket(AF_INET,SOCK_STREAM,0);
    if (sd < 0) {
        printf("Cannot create a socket.\n");
    } else {
        printf("Socket is created.\n");
    }
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(sport);
    sd2 = bind(sd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    if (sd2 < 0) {
        printf("Cannot bind.\n");
    } else {
        printf("Binded.\n");
    }
    listen(sd, 5);
    clilen = sizeof(cliaddr);
    nsd = accept(sd, (struct sockaddr*)&cliaddr, &clilen);
    if (nsd < 0) {
        printf("Cannot Accept.\n");
    } else {
        printf("Accepted.\n");
    }
    printf("client address : %s\n",inet_ntoa(cliaddr.sin_addr));
    recv(nsd,&headersize,sizeof(headersize),0);
    printf("Header size is %d\n",headersize);
    recv(nsd,&windowsize,sizeof(windowsize),0);
    printf("Window size is %d\n",windowsize);
    wsize=windowsize;
    int nakp=0,nak[wsize];
    while(1){
    	while(i<windowsize){
    		printf("Expecting frame %d\n",i);
    		recv(nsd,&j,sizeof(j),0);
    		if(j!=i || j==headersize){
    			if(nakp>wsize){
    				for(k=0;k<nakp;k++){
    					nak[k]=0;
    				}
    				nakp=0;
    			}
    			nak[nakp]=i;
    			nakp++;
    		}
    		else{
    			printf("correct frame received\n");
    		}
    		i++;
    	}
    	printf("The frames not received are : ");
    	for(k=0;k<nakp;k++){
    		if(nak[k]!=headersize){
    			printf("%d\n",nak[k]);
    		}
    	}
    	printf("Enter the ack to be sent :\n");
    	scanf("%d",&ack);
    	send(nsd,&ack,sizeof(ack),0);
    	if(i==headersize && ack==0){
    		printf("Received successfully\n");
    		break;
    	}
    	if(ack==i){
    		windowsize+=windowsize;
    	}
    	if(ack<=0){
    		ack=ack*-1;
    		printf("Waiting for frame %d\n",ack);
    		recv(nsd,&j,sizeof(j),0);
    		if(j==ack){
    			printf("Frame %d received successfully",ack);
    			for(k=0;k<nakp;k++){
    				if(nak[k]==ack){
    					nak[k]=headersize;
    				}
    			}
    		}
    	}
    }
    close(sd);
    close(nsd);
    return 0;
}
