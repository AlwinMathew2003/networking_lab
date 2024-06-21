#include<stdio.h>
#include<arpa/inet.h>
#include <unistd.h>
#define port 5000

int prime(int n){
	if(n<=1)
	{
		return 0;
	}
	for(int i=2;i<n/2;i++)
	{
		if (n%i==0)
		{
			return 0;
		}
	}
	return 1;
}
	
	
	
int main()
{
	struct sockaddr_in serveraddr,newaddr;
	int sersocket,newsocket,s,size;
	
	int n;
	
	sersocket=socket(PF_INET,SOCK_STREAM,0);
	
	if(sersocket>0)
		printf("\nserver socket is created");
	
	
	serveraddr.sin_family= PF_INET;
	serveraddr.sin_port= htons(port);
	serveraddr.sin_addr.s_addr=htonl(INADDR_ANY);
	
	s=bind(sersocket,(struct sockaddr *)&serveraddr,sizeof(serveraddr));
	if(s==0)
		printf("\nbind success");
	
	listen(sersocket,1);
	
	size=sizeof(newaddr);
	
	printf("\nserver ready");
	
	newsocket=accept(sersocket,(struct sockaddr *)&newaddr,&size);
	
	if(newsocket>0)
		printf("\naccepted");
	
	
	recv(newsocket,&n,sizeof(n),0);
	printf("\ndata received is %d\n",n);
	
	char buffer[100];
	
	if(prime(n)==0)
	{
		sprintf(buffer,"not a prime");
	}
	else
	{
		sprintf(buffer,"prime");
	}
	
	send(newsocket,buffer,sizeof(buffer),0);	
	
	close(sersocket);
}
