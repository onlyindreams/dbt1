# Makefile
# 10 january 2001

CC = gcc

CFLAGS = -g -I../include -I../wgen

all: orders.so address.so author.so customer.so item.so datagen

orders.so: Makefile orders.c ../include/datagen.h ../wgen/tpcw.h
	$(CC) -c -shared -fpic $(CFLAGS) orders.c -o orders.so

address.so: Makefile address.c ../include/datagen.h ../wgen/tpcw.h
	$(CC) -c -shared -fpic $(CFLAGS) address.c -o address.so

author.so: Makefile author.c ../include/datagen.h ../wgen/tpcw.h
	$(CC) -c -shared -fpic $(CFLAGS) author.c -o author.so

customer.so: Makefile customer.c ../include/datagen.h ../wgen/tpcw.h
	$(CC) -c -shared -fpic $(CFLAGS) customer.c -o customer.so

item.so: Makefile item.c ../include/datagen.h ../wgen/tpcw.h
	$(CC) -c -shared -fpic $(CFLAGS) item.c -o item.so

datagen: Makefile main.c orders.so address.so author.so customer.so item.so \
	../include/datagen.h ../include/common.h ../common/common.so \
	../wgen/tpcw.o ../wgen/text.o ../wgen/rnd.o ../wgen/bm_utils.o
	$(CC) $(CFLAGS) main.c -o datagen ../common/common.so orders.so address.so \
		author.so customer.so item.so ../wgen/tpcw.o ../wgen/text.o \
		../wgen/rnd.o ../wgen/bm_utils.o -lm

clean:
	rm -f *.so
