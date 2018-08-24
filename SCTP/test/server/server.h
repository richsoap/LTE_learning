#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/sctp.h>

#define PORT 6666
#define BUFFER_SIZE 1024
#define LISTEN_QUEUE 100

class SctpServer {
	public:
		SctpServer();
		void start(void);
	private:
		void listenSocket(void);
		void loop(void);

		int receiveSocket;
		int messageFlags;
		char buffer[BUFFER_SIZE];
		struct sockaddr_in clientAddr;
		struct sockaddr_in serverAddr;
		struct sctp_sndrcvinfo info;
		struct sctp_event_subscribe events;
		int streamNumber;
		socklen_t len;
		size_t readSize;
};
