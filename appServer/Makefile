# Makefile
# 20 february 2002

include ../common.mk

ODBC_DIR=../interfaces/odbc
COMMON_DIR=../common
INCLUDE_DIR=../include

EXE = appServer
APP_PRGS = appServer.c app_txn_array.c app_threadpool.c \
	app_txn_queue.c app_interface.c
APP_OBJS = $(APP_PRGS:.c=.o)

LIBS = $(SAPDBROOT)/lib/libsqlod.so -lm -lpthread
OBJS = $(COMMON_OBJS) $(ODBC_OBJS) $(APP_OBJS)
PRGS = $(COMMON_PRGS) $(ODBC_PRGS) $(APP_PRGS)

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LIBS)

%.o:%.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(COMMON_OBJS):$(COMMON_PRGS)
	cd $(COMMON_DIR); $(make)

$(ODBC_OBJS): $(ODBC_PRGS)
	cd $(ODBC_DIR); $(MAKE)

clean:
	rm $(EXE) *.o

explain:
	@echo "$(OBJS)"

$(EXE): \
	../common.mk \
	Makefile \
	$(OBJS) \
	$(INCLUDE_DIR)/app_interaction.h \
	$(INCLUDE_DIR)/common.h \
	$(INCLUDE_DIR)/eu.h \
	$(INCLUDE_DIR)/odbc_interaction.h \
	$(INCLUDE_DIR)/app_interface.h \
	$(INCLUDE_DIR)/app_threadpool.h \
	$(INCLUDE_DIR)/app_txn_array.h \
	$(INCLUDE_DIR)/app_txn_queue.h \
	$(ODBC_INCLUDE)

$(APPOBJS): \
	../common.mk \
	Makefile \
	$(INCLUDE_DIR)/app_interaction.h \
	$(INCLUDE_DIR)/common.h \
	$(INCLUDE_DIR)/eu.h \
	$(INCLUDE_DIR)/odbc_interaction.h \
	$(INCLUDE_DIR)/app_interface.h \
	$(INCLUDE_DIR)/app_threadpool.h \
	$(INCLUDE_DIR)/app_txn_array.h \
	$(INCLUDE_DIR)/app_txn_queue.h \
	$(APP_PRGS)

