# Makefile
# 10 january 2001

include ../common.mk

COMMON_DIR=../common
INCLUDE_DIR=../include

all: $(COMMON_OBJS)

%.so:%.c
	$(CC) -c -shared -fpic $(CFLAGS) -o $@ $<

common.so: ../common.mk Makefile common.c ../include/common.h

socket.so: ../common.mk Makefile _socket.c ../include/_socket.h

clean: 
	rm -f *.so
