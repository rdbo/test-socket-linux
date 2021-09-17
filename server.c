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
	int client_sock;
	char databuf[1024] = { 0 };
	struct sockaddr_in server;
	socklen_t socklen;
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1)
		return -1;
	
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_family = AF_INET;
	server.sin_port = htons(1337);
	socklen = sizeof(server);

	bind(sockfd, (const struct sockaddr *)&server, socklen);
	listen(sockfd, 1);

	client_sock = accept(sockfd, (struct sockaddr *)&server, &socklen);
	for (;;) {
		if (read(client_sock, databuf, sizeof(databuf) - 1) > 0) {
			printf(databuf);
			send_msg(client_sock, "wassup\n");
		}
	}

	return 0;
}
