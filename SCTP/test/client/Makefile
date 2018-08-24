cxx = g++
client:client.o main.o basicIE.o blank.o
	$(cxx) -o client client.o main.o basicIE.o blank.o -lsctp

client.o:client.h basicIE.o
blank.o:blank.h
basicIE.o:basicIE.h

clean:
	rm client.o client main.o basicIE.o blank.o
