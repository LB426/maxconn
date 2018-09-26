CC = gcc
CFLAGS = -std=c99 -std=gnu99 -g -Og -D_REENTRANT -Wall 
LIBS = -lpthread
CLEANFILES = core core.* *.core *.o temp.* typescript* \
	*.lc *.lh *.bsdi *.sparc *.uw
BUILD_DATE = $(shell date +"%Y-%m-%d_%H:%M:%S")
PROGS = client server

.PHONY: all clean

all: ${PROGS} 

clean:
	rm -rf ${PROGS} ${CLEANFILES}

client.o: client.c
	${CC} ${CFLAGS} -c client.c -o client.o

client: client.o
	${CC} ${CFLAGS} -o client client.o ${LIBS}

server.o: server.c
	${CC} ${CFLAGS} -c server.c -o server.o

server: server.o
	${CC} ${CFLAGS} -o server server.o ${LIBS}
