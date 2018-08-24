#include "client.h"
#include "basicIE.h"
#include <sys/un.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

SctpClient::SctpClient():echoToAll(0) {}
SctpClient::~SctpClient() { close(sendSocket); }

void SctpClient::start(void) { makeSocket(); }

void SctpClient::makeSocket(void) {
	int sockfd, ret, len;
	void* buf;
	struct sockaddr_un server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sun_family = AF_UNIX;
	strcpy(server_addr.sun_path, "/home/richsoap/workspace/select.socket");
	sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if(sockfd < 0) {
		printf("New sockfd wrong\n");
		exit(1);
	}
	ret = connect(sockfd, (struct sockaddr *) (&server_addr), sizeof(server_addr));
	if(ret < 0) {
		printf("Connect wrong\n");
		exit(2);
	}
	buf = malloc(sizeof(char) * 1024);
	while(true) {
		std::cin.getline((char*)buf, 1023);
		len = strlen((char*)buf);
		printf("Try to send(%d) %s\n", len, (char*)buf);
		len = send(sockfd, buf, len, MSG_DONTWAIT);
		if(len < 0)
			printf("Send error\n");
		else
			printf("Send length %d\n", len);
	}
}
