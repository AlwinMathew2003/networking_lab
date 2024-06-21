#include<stdio.h>
#include<arpa/inet.h>
#include <unistd.h>
#define port 4000
void main()
{
	struct sockaddr_in serveraddr,newaddr;
	int clisocket,size;
	

	clisocket=socket(AF_INET,SOCK_DGRAM,0);
	
	if(clisocket>0)
		printf("\nClient socket created");
		
		
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(port);
	serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	int n;
	
	printf("\nEnter the number:");
	scanf("%d",&n);
	
	sendto(clisocket,&n,sizeof(n),0,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
	
	size=sizeof(newaddr);

	char buffer[100];
	
	recvfrom(clisocket,buffer,sizeof(buffer),0,(struct sockaddr*)&newaddr,&size);
	
	printf("%d is %s\n",n,buffer);
	close(clisocket);
}


