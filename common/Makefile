# Makefile
# 10 january 2001

include ../common.mk

all: common.o _socket.o

%.o:%.c
	$(CC) -c $(CFLAGS) -o $@ $<

common.o: ../common.mk Makefile common.c ../include/common.h

socket.o: ../common.mk Makefile _socket.c ../include/_socket.h

clean: 
	rm -f *.o
