# Makefile
# 20 february 2002

include ../../common.mk

INCLUDE_DIR=../../include
ODBC_DIR=.
CFLAGS_ODBC=$(CFLAGS) -DPHASE1

all: $(ODBC_OBJS)

%.o:%.c
	$(CC) -c $(CFLAGS_ODBC) -o $@ $<

clean:
	rm *.o

explain:
	@echo "$(ODBC_OBJS)"

DBOBJS: \
	Makefile \
	../../common.mk \
	$(ODBC_INCLUDE) \
	$(ODBC_PRGS)
