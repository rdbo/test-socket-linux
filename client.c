#ifndef _GNU_SOURCE
#define _GNU_SOURCE 1
#endif

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

#define send_msg(sockfd, msg) write(sockfd, msg, strlen(msg))

int main()
{
	int sockfd;
	struct sockaddr_in server;
	socklen_t socklen;
	char databuf[1024] = { 0 };

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1)
		return -1;
	
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons(1337);
	socklen = sizeof(server);

	connect(sockfd, &server, socklen);
	for (;;) {
		send_msg(sockfd, "hello!\n");

		if (read(sockfd, databuf, sizeof(databuf) - 1) > 0) {
			printf(databuf);
		}

		sleep(1);
	}

	return 0;
}