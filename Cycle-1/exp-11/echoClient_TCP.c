#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<unistd.h>
#define port 5000

void main(){
	struct sockaddr_in serveraddr;
	int clisocket;
	
	clisocket = socket(AF_INET,SOCK_STREAM,0);
	if(clisocket>0)
	{
		printf("\nSocket is created");
	}

	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(port);
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	int ret = connect(clisocket,(struct sockaddr *)&serveraddr,sizeof(serveraddr));
	if(ret<0)
	{
		printf("Error in connection.\n");
		exit(1);
	}
	printf("\nConnected to server.");
	char buffer[100];
	while(1){
		printf("\nEnter the string: ");
		fgets(buffer,sizeof(buffer),stdin);
		
		send(clisocket,buffer,sizeof(buffer),0);

		if(strcmp(buffer,"exit\n")==0)
		{
			break;
		}
		recv(clisocket,buffer,sizeof(buffer),0);
		printf("\nServer: %s",buffer);
		
	}
	close(clisocket);
	
}
