# Makefile
# 20 february 2002

include ../common.mk

ODBC_DIR=../interfaces/odbc
COMMON_DIR=../common
INCLUDE_DIR=../include

EXE = appCache 
CACHE_PRGS = cache.c cache_interface.c
CACHE_OBJS = $(CACHE_PRGS:.c=.o)

LIBS = $(SAPDBROOT)/lib/libsqlod.so -lm -lpthread
OBJS = $(COMMON_OBJS) $(CACHE_OBJS) $(ODBC_DIR)/odbc_interaction.o \
	$(ODBC_DIR)/odbc_interaction_search_results.o
PRGS = $(COMMON_PRGS) $(CACHE_PRGS) $(ODBC_DIR)/odbc_interaction.o \
	$(ODBC_DIR)/odbc_interaction_search_results.o

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

