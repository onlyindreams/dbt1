# Makefile
# 30 january 2002

include ../common.mk

INCLUDE_DIR=../include
COMMON_DIR=../common
ODBC_DIR=../interfaces/odbc

CFLAGS_P1 = $(CFLAGS) -DPHASE1
CFLAGS_P2 = $(CFLAGS) -DPHASE2

LIBS = $(ODBC_LIB) -lm -lpthread

all: eu_p1.so eu_p2.so tm_interface.so dbdriver_p1 dbdriver_p2

dbdriver_p1: Makefile main.c $(INCLUDE_DIR)/eu.h eu_p1.so \
	$(COMMON_DIR)/common.so $(ODBC_OBJS) ../common.mk \
	$(INCLUDE_DIR)/cache.h ../cache/cache_interface.so \
	$(INCLUDE_DIR)/_socket.h
	$(CC) $(CFLAGS_P1) main.c -o dbdriver_p1 eu_p1.so \
		../common/common.so  $(ODBC_OBJS) ../cache/cache_interface.so \
		$(COMMON_DIR)/_socket.so $(LIBS)

eu_p1.so: Makefile eu.c ../include/eu.h ../include/common.h ../common.mk
	$(CC) -c $(CFLAGS_P1) eu.c -o eu_p1.so

eu_p2.so: Makefile eu.c ../include/eu.h ../include/common.h ../common.mk
	$(CC) -c $(CFLAGS_P2) eu.c -o eu_p2.so

tm_interface.so: Makefile tm_interface.c ../include/tm_interface.h \
	$(COMMON_PRGS) ../include/common.h ../include/_socket.h ../common.mk
	$(CC) -c $(CFLAGS_P2) -I$(SAPDBROOT)/incl tm_interface.c -o tm_interface.so

dbdriver_p2: Makefile eu.c ../include/eu.h ../include/common.h main.c \
	eu.c tm_interface.so tm_interface.c $(COMMON_OBJS) ../common.mk
	$(CC) $(CFLAGS_P2) main.c -o dbdriver_p2 eu_p2.so \
		$(COMMON_OBJS) tm_interface.so $(LIBS)

$(COMMON_OBJS):$(COMMON_PRGS)
	cd $(COMMON_DIR); $(MAKE)

$(ODBC_OBJS): $(ODBC_PRGS)
	cd $(ODBC_DIR); $(MAKE)

clean:
	rm -f *.so dbdriver_p1 dbdriver_p2
