ROOT_PATH=$(shell pwd)
DEST=httpd
SRC=httpd.c
CC=gcc
OBJ=$(SRC:.c=.o)
DEBUG=-D_DEBUG_
PTHREAD=-lpthread
CGI=$(ROOT_PATH)/htdoc/cgi_math  $(ROOT_PATH)/htdoc/cgi_sql

.PHONY:all
all:$(DEST) cgi

$(DEST):$(OBJ)
	@$(CC) -o $@ $^ $(PTHREAD) #$(DEBUG)
%.o:%.c	
	@$(CC) -c $<
.PHONY:cgi
cgi:
	@for name in `echo $(CGI)`;\
	do\
	   cd $$name;\
	   make all;\
	   cd -;\
	done


.PHONY:clean
clean:
	@rm -f $(DEST) *.o
	@for name in `echo $(CGI)`;\
	do\
	   cd $$name;\
	   make clean;\
	   cd -;\
	done
	

