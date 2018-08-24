server:server.o main.o
	cc -o server server.o main.o -lsctp

server.o:server.h

clean:
	rm server.o server main.o
