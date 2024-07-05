#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>
#define port 5000

void main(){
	struct sockaddr_in serveraddr,newaddr;
	int sersocket,newsocket,s;
	int size = sizeof(newaddr);
	pid_t child;
	char buffer[100];
	
	sersocket = socket(AF_INET,SOCK_STREAM,0);
	
	if(sersocket>0)
	{
		printf("\nSocket is created");
	}
	
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(port);
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	s = bind(sersocket,(struct sockaddr *)&serveraddr,sizeof(serveraddr));
	
	if(s==0)
	{
		printf("\nBind success\n");
	}
	
	
	if(listen(sersocket,10)==0)
	{
		printf("Listening...\n");
	}
	else{
		printf("\nError in binding");
	}
		

	
	while(1)
	{
		
		newsocket = accept(sersocket,(struct sockaddr *)&newaddr,&size);
		if(newsocket<0)
		{
			exit(1);
		}
		printf("\nConnected from client address:%s PORT:%d\n",inet_ntoa(newaddr.sin_addr),ntohs(newaddr.sin_port));
		
		
		
		if((child=fork())==0)
		{
			close(sersocket);
			while(1)
			{
				recv(newsocket,buffer,sizeof(buffer),0);
				if(strcmp(buffer,"exit\n")==0)
				{
					printf("\nDisconnecting from client address:%s PORT:%d",inet_ntoa(newaddr.sin_addr),ntohs(newaddr.sin_port));
					break;
				}
				else
				{
					printf("\nClient: %s",buffer);
					send(newsocket,buffer,sizeof(buffer),0);
				}
			}
		}
		
	}
	close(newsocket);
}
