#include<stdio.h>
#include<arpa/inet.h>
#include <unistd.h>
#define port 4000

int fact(int n){
	
	if(n==0){
		return 1;
	}
	return n*fact(n-1);	
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

	int x;
	
	x=fact(n);
	
	sendto(sersocket,&x,sizeof(x),0,(struct sockaddr*)&newaddr,sizeof(newaddr));
	
	close(sersocket);
}



