C=client.c
S=server.c

CC=gcc
.PHONY:all
all:client server
client:$(C) comm.c comm.h
	@$(CC) -o $@ $^
server:$(S) comm.c comm.h
	@$(CC) -o $@ $^
.PHONY:clean
clean:
	@rm -f server client
