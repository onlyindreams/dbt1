# Makefile
# 10 january 2001

include ../common.mk

COMMON_DIR=../common
INCLUDE_DIR=../include

all: $(COMMON_OBJS)

%.o:%.c
	$(CC) -c $(CFLAGS) -o $@ $<

common.o: ../common.mk Makefile common.c ../include/common.h

socket.o: ../common.mk Makefile _socket.c ../include/_socket.h

clean: 
	rm -f *.o
