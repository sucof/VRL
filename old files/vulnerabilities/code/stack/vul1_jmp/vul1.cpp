#include<iostream>
#include<stdio.h>
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<arpa/inet.h>
#define MAXSIZE 1024
using namespace std;

void testVul(char *buff)
{
	char str[10];
	__asm__ __volatile__(
			"jmp next\n\t"
			"jmp *%%esp\n\t"
			"next:"
			:
			);
	strcpy(str, buff);
}

int main()
{
	int listenfd, connfd;
	struct sockaddr_in servaddr;
	char buff[MAXSIZE];
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if(listenfd==-1)
	{
		printf("Error socket\n");
		exit(1);
	}
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = 0;         //随机端口号
	if(bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr))==-1)
	{
		printf("Error bind\n");
		exit(1);
	}
	if(listen(listenfd, 1)==-1)
	{
		printf("Error listen\n");
		exit(1);
	}
	unsigned int len;
	if(getsockname(listenfd, (struct sockaddr*)&servaddr, &len))
	{
		printf("Error getsockname\n");
		exit(1);
	}
	int listenPort = ntohs(servaddr.sin_port);
	while(true)
	{
		printf("waiting for connect...(port %d)\n", listenPort);
		connfd = accept(listenfd, (struct sockaddr*)NULL, 0);
		if(connfd==-1)
		{
			printf("Error accept\n");
			exit(1);
		}
		printf("wating for data...\n");
		int n;
		while((n=recv(connfd, buff, MAXSIZE, 0))>0)
		{
			buff[n] = '\0';
			testVul(buff);
			printf("%s\n", buff);
		}
		close(connfd);
	}
	close(listenfd);
	return 0;
}
