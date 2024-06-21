#include<stdio.h>
#include<arpa/inet.h>
#include <unistd.h>
#define port 5000

int fact(int n){
	
	if(n==0){
		return 1;
	}
	return n*fact(n-1);	
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
	
	int x;
	
	x=fact(n);
	
	send(newsocket,&x,sizeof(x),0);	
	
	close(sersocket);
}
