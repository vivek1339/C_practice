#include<stdlib.h>
#include<netinet/in.h>
#include<stdio.h>
#include <string.h>
#include<sys/socket.h>
#include <unistd.h>
#define PORT 8080
int main(void)
{
	int serverfd,new_socket,valread;
	char buffer[1024]={0};
	struct sockaddr_in address;
	int opt=1;
	int address_len=sizeof(address);
	char *hello="Hello from server";
	if((serverfd=socket(AF_INET,SOCK_STREAM,0))==0)
	{
		printf("Couldn't create Socket\n");
		exit(1);
	}
	printf("Created a Socket\n");
	if (setsockopt(serverfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
	{ 
		perror("setsockopt"); 
		exit(EXIT_FAILURE); 
	}
	printf("Set socket parameters");
	address.sin_family=AF_INET;
	address.sin_port=htons(PORT);
	address.sin_addr.s_addr=INADDR_ANY;
	if(bind(serverfd,(struct sockaddr *)&address,sizeof(address))<0)
	{
		printf("Couldn't bind\n");
		exit(1);
	}
	printf("binded Socket\n");
	if(listen(serverfd,3)<0)
	{
		printf("Couldn't listen\n");
		exit(1);
	}
	printf("Listning on Socket\n");
	if((new_socket=accept(serverfd,	(struct sockaddr*)&address,(socklen_t*)&address_len))<0)
	{
		printf("cannot accept connection\n");
		exit(1);
	}
	printf("Accepted connection\n");
	valread=read(new_socket,buffer,1024);
	printf("read done\n");
	printf("%s\n",buffer);
	send(new_socket,hello,strlen(hello),0);
	printf("Hello message sent\n");
	exit(0);

}