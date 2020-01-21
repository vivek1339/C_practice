#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#define PORT 8080
int main(void)
{
	int sock=0,readval;
	struct sockaddr_in server_addr;
	char buffer[1024]={0};
	char *hello="Hello from client";
	if((sock=socket(AF_INET,SOCK_STREAM,0))<0)
	{
		printf("couldn't create socket\n");
		exit(1);
	}
	printf("Socket created\n");
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(PORT);
	if(inet_pton(AF_INET,"127.0.0.1",&server_addr.sin_addr)<0)
	{
		printf("Wrong address\n");
		exit(1);
	}
	printf("Address loaded\n");
	if(connect(sock,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
	{
		printf("couldn't connect\n");
		exit(1);
	}
	printf("connected to server\n");
	send(sock,hello,strlen(hello),0);
	printf("Sent hello message\n");
	readval=read(sock,buffer,1024);
	printf("%s\n",buffer);
	return 0;
}