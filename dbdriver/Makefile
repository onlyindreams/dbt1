# Makefile
# 30 january 2002

include ../common.mk

CFLAGS_P1 = -g -I../include -I$(SAPDBROOT)/incl -DPHASE1
CFLAGS_P2 = -g -I../include -DPHASE2

LIBS = $(SAPDBROOT)/lib/libsqlod.so -lm -lpthread

all: eu_p1.o eu_p2.o tm_interface.o dbdriver_p1 dbdriver_p2

dbdriver_p1: Makefile main.c ../include/eu.h eu_p1.o ../common/common.o \
	$(DBOBJS_P1)
	$(CC) $(CFLAGS_P1) main.c -o dbdriver_p1 eu_p1.o \
		../common/common.o  $(DBOBJS_P1) \
		$(LIBS)

eu_p1.o: Makefile eu.c ../include/eu.h ../include/common.h 
	$(CC) -c $(CFLAGS_P1) eu.c -o eu_p1.o

eu_p2.o: Makefile eu.c ../include/eu.h ../include/common.h 
	$(CC) -c $(CFLAGS_P2) eu.c -o eu_p2.o

tm_interface.o: Makefile tm_interface.c ../include/tm_interface.h \
	../include/common.h ../include/_socket.h
	$(CC) -c $(CFLAGS_P2) -I$(SAPDBROOT)/incl tm_interface.c -o tm_interface.o

dbdriver_p2: Makefile eu.c ../include/eu.h ../include/common.h main.c \
	eu.c ../common/_socket.o tm_interface.o tm_interface.c
	$(CC) $(CFLAGS_P2) main.c -o dbdriver_p2 eu_p2.o ../common/common.o \
		../common/_socket.o tm_interface.o -lpthread -lm

$(COMMONOBJS):$(COMMONPRGS)
	cd ../common; $(MAKE)

$(DBOBJS_P1): $(DBPRGS)
	cd ../interfaces/odbc; $(MAKE)

clean:
	rm *.o dbdriver_p1 dbdriver_p2
