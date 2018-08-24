#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/sctp.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SERVER_PORT 6666
#define MAXLINE 1024

void sctp_sendFile(FILE *fp, int sock_fd, struct sockaddr *target, socklen_t len);

class SctpClient {
	public:
		SctpClient();
		~SctpClient();
		void start(void);
	private:
		void makeSocket(void);
		int sendSocket;
		struct sockaddr_in serverAddr;
		struct sctp_event_subscribe events;
		int echoToAll;
};
