#include<stdio.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#define port 5000

void str_reverse(char buffer[]) {
    
    char reverse[100];
    int length = strlen(buffer);
    
    for (int i = 0; i < length; i++) {
        reverse[i] = buffer[length - i - 1];
    }
    
    reverse[length] = '\0';
    strcpy(buffer,reverse);
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
	
	
	char buffer[100];
	
	recv(newsocket,buffer,sizeof(buffer),0);
	printf("\ndata received is %s\n",buffer);
	
	str_reverse(buffer);
	
	send(newsocket,buffer,sizeof(buffer),0);	
	
	close(sersocket);
}
