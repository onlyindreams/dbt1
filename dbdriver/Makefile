# Makefile
# 30 january 2002

include ../common.mk

INCLUDE_DIR=../include
COMMON_DIR=../common
ODBC_DIR=../interfaces/odbc

CFLAGS_P1 = $(CFLAGS) -DPHASE1
CFLAGS_P2 = $(CFLAGS) -DPHASE2

LIBS = $(SAPDBROOT)/lib/libsqlod.so -lm -lpthread

all: eu_p1.o eu_p2.o tm_interface.o dbdriver_p1 dbdriver_p2

dbdriver_p1: Makefile main.c ../include/eu.h eu_p1.o ../common/common.o \
	$(ODBC_OBJS) ../common.mk
	$(CC) $(CFLAGS_P1) main.c -o dbdriver_p1 eu_p1.o \
		../common/common.o  $(ODBC_OBJS) \
		$(LIBS)

eu_p1.o: Makefile eu.c ../include/eu.h ../include/common.h ../common.mk
	$(CC) -c $(CFLAGS_P1) eu.c -o eu_p1.o

eu_p2.o: Makefile eu.c ../include/eu.h ../include/common.h ../common.mk
	$(CC) -c $(CFLAGS_P2) eu.c -o eu_p2.o

tm_interface.o: Makefile tm_interface.c ../include/tm_interface.h \
	$(COMMON_PRGS) ../include/common.h ../include/_socket.h ../common.mk
	$(CC) -c $(CFLAGS_P2) -I$(SAPDBROOT)/incl tm_interface.c -o tm_interface.o

dbdriver_p2: Makefile eu.c ../include/eu.h ../include/common.h main.c \
	eu.c tm_interface.o tm_interface.c $(COMMON_OBJS) ../common.mk
	$(CC) $(CFLAGS_P2) main.c -o dbdriver_p2 eu_p2.o \
		$(COMMON_OBJS) tm_interface.o $(LIBS)

$(COMMON_OBJS):$(COMMON_PRGS)
	cd $(COMMON_DIR); $(MAKE)

$(ODBC_OBJS): $(ODBC_PRGS)
	cd $(ODBC_DIR); $(MAKE)

clean:
	rm *.o dbdriver_p1 dbdriver_p2
