# Makefile
# 20 february 2002

include ../common.mk

COMMON_DIR=../common
DBDRIVER_DIR=../dbdriver
ODBC_DIR=../interfaces/odbc
INCLUDE_DIR=../include

CFLAGS_P1 = $(CFLAGS) -DPHASE1
CFLAGS_P2 = $(CFLAGS) -DPHASE2
LIBS = $(SAPDBROOT)/lib/libsqlod.so -lm

all: odbc_test_p1 odbc_test_p2 results load_db_proc

odbc_test_p1: Makefile ../common.mk odbc_test.c ../common/common.so \
	$(ODBC_OBJS) 
	$(CC) $(CFLAGS_P1) odbc_test.c -o odbc_test_p1 \
		$(COMMON_DIR)/common.so \
		$(ODBC_OBJS) \
		$(LIBS)

odbc_test_p2: Makefile ../common.mk odbc_test.c $(COMMON_OBJS) \
	$(DBDRIVER_DIR)/tm_interface.so \
	$(ODBC_OBJS)
	$(CC) $(CFLAGS_P2) odbc_test.c -o \
		odbc_test_p2 \
		$(DBDRIVER_DIR)/tm_interface.so \
		$(COMMON_OBJS) \
		$(ODBC_OBJS) \
		$(LIBS)

results: Makefile results.c ../include/common.h
	$(CC) -g -I../include results.c -o results -lm

load_db_proc: Makefile load_db_proc.c ../include/odbc_interaction.h \
		../interfaces/odbc/odbc_interaction.so ../include/common.h
	$(CC) -g -I../include -I$(SAPDBROOT)/incl load_db_proc.c -o load_db_proc \
		../interfaces/odbc/odbc_interaction.so ../common/common.so \
		$(SAPDBROOT)/lib/libsqlod.so -lm

$(COMMON_OBJS):$(COMMON_PRGS)
	cd $(COMMON_DIR); $(MAKE)

$(ODBC_OBJS): $(ODBC_PRGS)
	cd $(ODBC_DIR); $(MAKE)

explain:
	@echo "$(ODBC_OBJS)"

clean:
	rm -f odbc_test_p1 odbc_test_p2 results load_db_proc
