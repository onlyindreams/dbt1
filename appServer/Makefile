# Makefile
# 20 february 2002

include ../common.mk

EXE = appServer
APPPRGS = appServer.c app_txn_array.c app_threadpool.c \
	app_txn_queue.c app_interface.c
APPOBJS = appServer.o app_txn_array.o app_threadpool.o \
	app_txn_queue.o app_interface.o
LIBS = $(SAPDBROOT)/lib/libsqlod.so -lm -lpthread
OBJS = $(COMMONOBJS) $(DBOBJS_P2) $(APPOBJS)
PRGS = $(COMMONPRGS) $(DBPRGS) $(APPPRGS)

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LIBS)

%.o:%.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(COMMONOBJS):$(COMMONPRGS)
	cd ../common; $(MAKE)

$(DBOBJS_P2): $(DBPRGS)
	cd ../interfaces/odbc; $(MAKE)

clean:
	rm $(EXE) *.o

explain:
	@echo "$(OBJS)"

$(EXE): \
	../common.mk \
	Makefile \
	$(OBJS) \
	$(INCLUDEDIR)/app_interaction.h \
	$(INCLUDEDIR)/common.h \
	$(INCLUDEDIR)/eu.h \
	$(INCLUDEDIR)/odbc_interaction.h \
	$(INCLUDEDIR)/app_interface.h \
	$(INCLUDEDIR)/app_threadpool.h \
	$(INCLUDEDIR)/app_txn_array.h \
	$(INCLUDEDIR)/app_txn_queue.h \
	$(DBINCLUDE)

$(APPOBJS): \
	../common.mk \
	Makefile \
	$(INCLUDEDIR)/app_interaction.h \
	$(INCLUDEDIR)/common.h \
	$(INCLUDEDIR)/eu.h \
	$(INCLUDEDIR)/odbc_interaction.h \
	$(INCLUDEDIR)/app_interface.h \
	$(INCLUDEDIR)/app_threadpool.h \
	$(INCLUDEDIR)/app_txn_array.h \
	$(INCLUDEDIR)/app_txn_queue.h \
	$(APPPRGS)
