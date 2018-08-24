#include "client.h"
#include "basicIE.h"
#include <sys/un.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

SctpClient::SctpClient():echoToAll(0) {}
SctpClient::~SctpClient() { close(sendSocket); }

void SctpClient::start(void) { makeSocket(); }

void SctpClient::makeSocket(void) {
	struct sctp_sndrcvinfo info;
	int result;
	sendSocket = socket(AF_INET, SOCK_SEQPACKET, IPPROTO_SCTP);
	if(sendSocket < 0) {
		printf("SCTP socket wrong\n");
		exit(1);
	}
	bzero(&serverAddr, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(SERVER_PORT);
	inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

	bzero(&events, sizeof(events));
	events.sctp_data_io_event = 1;
	result = setsockopt(sendSocket, IPPROTO_SCTP, SCTP_EVENTS, &events, sizeof(events));
	printf("set result: %d\n", result);
	
	sctp_sendFile(stdin, sendSocket, (struct sockaddr* )&serverAddr, sizeof(serverAddr));
}


void sctp_sendFile(FILE *fp, int sock_fd, struct sockaddr *target, socklen_t tolen) {
	struct sockaddr_in peeraddr;
	struct sctp_sndrcvinfo info;
	struct sockaddr_un mini_addr;
	int mini_fd, maxfd;
	fd_set read_fps, read_fps_cpy;
	sctp_assoc_t id;
	char sendline[MAXLINE];
	char recvline[MAXLINE];
	socklen_t len;
	int out_sz,rd_sz;
	int msg_flags;
	int result;
	char testS1ap[] = 
	{0x00,0x11,0x00,0x2d,0x00,0x00,0x04,0x00,0x3b,0x00,0x08,0x00,0x00,0xf1,0x10,0x00,
	0x1a,0x2d,0x00,0x00,0x3c,0x40,0x0a,0x03,0x80,0x65,0x6e,0x62,0x31,0x61,0x32,0x64,
	0x30,0x00,0x40,0x00,0x07,0x00,0x00,0x00,0x40,0x00,0xf1,0x10,0x00,0x89,0x40,0x01,0x40};
	basicIE testIE = basicIE(testS1ap);
	testIE.resetWorkspace();
	bzero(&info, sizeof(info));
	result = sctp_connectx(sock_fd, target, 1, &id);
	if(result != 0) {
		printf("connect error\n");
		exit(2);
	}
	info.sinfo_stream = sendline[1] - '0';
	info.sinfo_ppid = 0x12;
	info.sinfo_assoc_id = id;
		
	////
	remove("/home/richsoap/workspace/select.socket");
	memset(&mini_addr, 0, sizeof(mini_addr));
	mini_addr.sun_family = AF_UNIX;
	strcpy(mini_addr.sun_path, "/home/richsoap/workspace/select.socket");
	mini_fd = socket(AF_UNIX, SOCK_STREAM, 0);
	bind(mini_fd, (struct sockaddr*)&mini_addr, sizeof(mini_addr));
	listen(mini_fd,10);
	///
	maxfd = mini_fd>sock_fd?mini_fd:sock_fd;
	FD_ZERO(&read_fps);
	FD_SET(sock_fd, &read_fps);
	FD_SET(mini_fd, &read_fps);
	FD_SET(0, &read_fps);

	while(true) {
		/*fgets(sendline, MAXLINE, fp);
		if(sendline[0] != '[') {
			printf("ERROR\n");
			continue;
		}*/
		read_fps_cpy = read_fps;
		result = select(maxfd + 1, &read_fps_cpy,0,0,NULL);
		if(result < 0)
			printf("Something wrong with select\n");
		else if(result == 0)
			printf("Select timeout\n");
		else {
			for(int i = 1;i < maxfd + 1; i ++) {
				if(FD_ISSET(i, &read_fps_cpy)) {
					if(i == mini_fd) {
						result = accept(mini_fd, NULL, NULL);
						if(result < 0)
							printf("New fd wrong\n");
						else {
							FD_SET(result, &read_fps);
							maxfd=maxfd>result?maxfd:result;
							printf("New fd success\n");
						}
					}
					else if(i == 0) {
						cin.getline(recvline, MAXLINE);
						int count = sctp_send(sock_fd, recvline, rd_sz, &info, 0);
						printf("received from stdin: %s\nsend count is %d\n", recvline, count);
					}
					else if(i == sock_fd) {
						len = sizeof(peeraddr);
						rd_sz = sctp_recvmsg(sock_fd, recvline, MAXLINE, (struct sockaddr*) &peeraddr, &len, &info, &msg_flags);
						printf("From str:%d seq:%d (assoc:0x%x): ", info.sinfo_stream, info.sinfo_ssn, (u_int)info.sinfo_assoc_id);
						for(int j = 0;j < rd_sz;j ++) 
							printf("0x%x ", recvline[j]);
						printf("\n");
					}
					else {
						rd_sz = recv(i, recvline, MAXLINE,0);
						if(rd_sz == 0) {
							close(i);
							FD_CLR(i, &read_fps);
							printf("close client%d\n",i);
						}
						else {
							//int count = sctp_send(sock_fd, recvline, rd_sz, &info, 0);
							int count = sctp_sendmsg(sock_fd, recvline, rd_sz, (struct sockaddr*) target, tolen, 0x12, 0, 0, 0, 0);
							printf("received from %d: %s\nsend count is %d\n", (int)rd_sz, recvline, count);
						}
					}
				}
			}
		}
	}
}
