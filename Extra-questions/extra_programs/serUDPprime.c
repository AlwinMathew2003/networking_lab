#include<stdio.h>
#include<arpa/inet.h>
#include <unistd.h>
#define port 4000

int prime(int n){
	if(n<=1)
	{
		return 0;
	}
	for(int i=2;i<=n/2;i++)
	{
		if (n%i==0)
		{
			return 0;
		}
	}
	return 1;
}
	
void main()
{
	struct sockaddr_in serveraddr,newaddr;
	int sersocket,s,size;
	

	sersocket=socket(AF_INET,SOCK_DGRAM,0);
	
	if(sersocket>0)
		printf("\nServer socket created");
	
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(port);
	serveraddr.sin_addr.s_addr=htonl(INADDR_ANY);
	
	
	s=bind(sersocket,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
	if(s==0)
		printf("\nBind success");
	
	size=sizeof(newaddr);
	
	int n=0;
	
	recvfrom(sersocket,&n,sizeof(n),0,(struct sockaddr*)&newaddr,&size);
	
	printf("\nData recieved:%d\n",n);

	char buffer[100];
	
	if(prime(n)==0)
	{
		sprintf(buffer,"not a prime");
	}
	else
	{
		sprintf(buffer,"prime");
	}
	
	sendto(sersocket,buffer,sizeof(buffer),0,(struct sockaddr*)&newaddr,sizeof(newaddr));
	
	close(sersocket);
}


