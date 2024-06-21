#include<stdio.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#define port 5000

void fibo(int n,int array[]) {
    
    array[0]=0;
    array[1]=1;
    
    for(int i=2;i<=n;i++)
    {
        array[i]=array[i-1]+array[i-2];
    }
    
}

int main()
{
	struct sockaddr_in serveraddr,newaddr;
	int sersocket,newsocket,s,size;
	
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
	
	
	int n,a[100];
	
	recv(newsocket,&n,sizeof(n),0);
	printf("\ndata received is %d\n",n);
	
	fibo(n,a);
	
	char buffer[100];
	
	for(int i=0;i<n;i++)
	{
		sprintf(buffer+strlen(buffer),"%d",a[i]);
	}
	
	send(newsocket,buffer,sizeof(buffer),0);	
	
	close(sersocket);
}

