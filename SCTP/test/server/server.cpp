#include "server.h"
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <assert.h>

SctpServer::SctpServer():streamNumber(1) {}

void SctpServer::listenSocket(void) {
	int result;
	receiveSocket = socket(AF_INET, SOCK_SEQPACKET, IPPROTO_SCTP);
	assert(receiveSocket >= 0);
	bzero(&serverAddr, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(PORT);
	inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);
	result = bind(receiveSocket, (struct sockaddr*) &serverAddr, sizeof(serverAddr));
	assert(result == 0);
	bzero(&events, sizeof(events));
	events.sctp_data_io_event = 1;
	result = setsockopt(receiveSocket, IPPROTO_SCTP, SCTP_EVENTS, &events, sizeof(events));
	assert(result == 0);
	result = listen(receiveSocket, LISTEN_QUEUE);
	assert(result == 0);
}

void SctpServer::loop(void) {
	while(true) {
		printf("loop!\n");
		len = sizeof(struct sockaddr_in);
		readSize = sctp_recvmsg(receiveSocket, buffer, BUFFER_SIZE, (struct sockaddr*) &clientAddr, &len, &info, &messageFlags);
		if(readSize != 0)
			printf("%d: %s",(int)readSize , buffer);
		buffer[0] = ']';
		if(streamNumber)
			info.sinfo_stream ++;
		sctp_sendmsg(receiveSocket, buffer, readSize, (struct sockaddr *)&clientAddr, len, info.sinfo_ppid, info.sinfo_flags, info.sinfo_stream, 0, 0);
	}
}

void SctpServer::start(void) {
	listenSocket();
	loop();
}

