#include<stdio.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#define port 5000
void main()
{
	struct sockaddr_in serveraddr;
	int clisocket;
	
	
	clisocket=socket(PF_INET,SOCK_STREAM,0);
	
	if(clisocket>0)
		printf("\nclient socket created");
	
	
	serveraddr.sin_family= PF_INET;
	serveraddr.sin_port= htons(port);
	serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	connect(clisocket,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
	
	int n;
	
	printf("\nEnter the number:");
	scanf("%d",&n);
	
	send(clisocket,&n,sizeof(n),0);
	
	int i;
	char buffer[100];
	
	recv(clisocket,buffer,sizeof(buffer),0);
	
	sprintf(buffer+strlen(buffer),"\n");
	
	printf("Fibonacci series:");
	for(i=0;i<strlen(buffer);i++)
	{
		printf("%c ",buffer[i]);
	}
	

	
	close(clisocket);
}

