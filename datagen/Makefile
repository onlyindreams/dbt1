# Makefile
# 10 january 2001

CC = gcc

CFLAGS = -g -I../include -I../wgen

all: orders.o address.o author.o customer.o item.o datagen

orders.o: Makefile orders.c ../include/datagen.h ../wgen/tpcw.h
	$(CC) -c $(CFLAGS) orders.c -o orders.o

address.o: Makefile address.c ../include/datagen.h ../wgen/tpcw.h
	$(CC) -c $(CFLAGS) address.c -o address.o

author.o: Makefile author.c ../include/datagen.h ../wgen/tpcw.h
	$(CC) -c $(CFLAGS) author.c -o author.o

customer.o: Makefile customer.c ../include/datagen.h ../wgen/tpcw.h
	$(CC) -c $(CFLAGS) customer.c -o customer.o

item.o: Makefile item.c ../include/datagen.h ../wgen/tpcw.h
	$(CC) -c $(CFLAGS) item.c -o item.o

datagen: Makefile main.c orders.o address.o author.o customer.o item.o ../include/datagen.h ../include/common.h ../common/common.o ../wgen/tpcw.o ../wgen/text.o ../wgen/rnd.o ../wgen/bm_utils.o
	$(CC) $(CFLAGS) main.c -o datagen ../common/common.o orders.o address.o author.o customer.o item.o ../wgen/tpcw.o ../wgen/text.o ../wgen/rnd.o ../wgen/bm_utils.o -lm
