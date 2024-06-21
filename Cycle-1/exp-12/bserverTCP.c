#include<stdio.h>
#include<arpa/inet.h>
#include <unistd.h>
#include<string.h>
#define port 5000
void main()
{
	int i,n;
	printf("Enter the no of clients:");
	scanf("%d",&n);
	int sersocket,newsocket[n],s,size;
	char buffer[100];
	struct sockaddr_in serveraddr,newaddr;
	sersocket=socket(PF_INET,SOCK_STREAM,0);
	if(sersocket>0)
		printf("\n[+]server socket is created");
	serveraddr.sin_family= PF_INET;
	serveraddr.sin_port= htons(port);
	serveraddr.sin_addr.s_addr=htonl(INADDR_ANY);
	s=bind(sersocket,(struct sockaddr *)&serveraddr,sizeof(serveraddr));
	if(s==0)
		printf("\n[+]bind success");
	listen(sersocket,n);
	size=sizeof(newaddr);
	printf("\n[+]Broadcast Server is ready");
	for(i=0;i<n;i++)
		{
		newsocket[i]=accept(sersocket,(struct sockaddr *)&newaddr,&size);
		printf("\n[+]Connection accepted from %s:%d\n", inet_ntoa(newaddr.sin_addr),ntohs(newaddr.sin_port));
		}
	while(1)
	{
	printf("\nEnter Broadcast Message:");
	scanf("%s",buffer);
	for(i=0;i<n;i++)
	{
		send(newsocket[i],buffer,sizeof(buffer),0);
	}
	if(strcmp(buffer,"bye")==0)
		break;
	}
for(i=0;i<n;i++)
	close(newsocket[i]);
}
