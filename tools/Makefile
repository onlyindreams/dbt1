# Makefile
# 20 february 2002

CC = gcc

ODBC=/opt/sapdb/interfaces/odbc
CFLAGS_P1 = -g -I../include -I$(ODBC)/incl -DPHASE1
CFLAGS_P2 = -g -I../include -I$(ODBC)/incl -DPHASE2
COMMONDIR=../common
DBDRIVERDIR=../dbdriver
LIBS = $(SAPDBROOT)/lib/libsqlod.so -lm

all: odbc_test_p1 odbc_test_p2 results load_db_proc

odbc_test_p1: Makefile odbc_test.c ../common/common.o \
	../interfaces/odbc/odbc_interaction_p1.o \
	../interfaces/odbc/odbc_interaction_admin_confirm_p1.o \
	../interfaces/odbc/odbc_interaction_admin_request_p1.o \
	../interfaces/odbc/odbc_interaction_best_sellers_p1.o \
	../interfaces/odbc/odbc_interaction_buy_confirm_p1.o \
	../interfaces/odbc/odbc_interaction_buy_request_p1.o \
	../interfaces/odbc/odbc_interaction_home_p1.o \
	../interfaces/odbc/odbc_interaction_new_products_p1.o \
	../interfaces/odbc/odbc_interaction_order_display_p1.o \
	../interfaces/odbc/odbc_interaction_order_inquiry_p1.o \
	../interfaces/odbc/odbc_interaction_product_detail_p1.o \
	../interfaces/odbc/odbc_interaction_search_request_p1.o \
	../interfaces/odbc/odbc_interaction_search_results_p1.o \
	../interfaces/odbc/odbc_interaction_shopping_cart_p1.o
	$(CC) $(CFLAGS_P1) odbc_test.c -o odbc_test_p1 \
		../common/common.o \
		../interfaces/odbc/odbc_interaction_p1.o \
		../interfaces/odbc/odbc_interaction_admin_confirm_p1.o \
		../interfaces/odbc/odbc_interaction_admin_request_p1.o \
		../interfaces/odbc/odbc_interaction_best_sellers_p1.o \
		../interfaces/odbc/odbc_interaction_buy_confirm_p1.o \
		../interfaces/odbc/odbc_interaction_buy_request_p1.o \
		../interfaces/odbc/odbc_interaction_home_p1.o \
		../interfaces/odbc/odbc_interaction_new_products_p1.o \
		../interfaces/odbc/odbc_interaction_order_display_p1.o \
		../interfaces/odbc/odbc_interaction_order_inquiry_p1.o \
		../interfaces/odbc/odbc_interaction_product_detail_p1.o \
		../interfaces/odbc/odbc_interaction_search_request_p1.o \
		../interfaces/odbc/odbc_interaction_search_results_p1.o \
		../interfaces/odbc/odbc_interaction_shopping_cart_p1.o \
		$(ODBC)/lib/libsqlod.so $(ODBC)/lib/libsqlrte.so

odbc_test_p2: Makefile odbc_test.c ../common/common.o \
	$(DBDRIVERDIR)/tm_interface.o \
	$(COMMONDIR)/_socket.o \
	../interfaces/odbc/odbc_interaction_p2.o \
	../interfaces/odbc/odbc_interaction_admin_confirm_p2.o \
	../interfaces/odbc/odbc_interaction_admin_request_p2.o \
	../interfaces/odbc/odbc_interaction_best_sellers_p2.o \
	../interfaces/odbc/odbc_interaction_buy_confirm_p2.o \
	../interfaces/odbc/odbc_interaction_buy_request_p2.o \
	../interfaces/odbc/odbc_interaction_home_p2.o \
	../interfaces/odbc/odbc_interaction_new_products_p2.o \
	../interfaces/odbc/odbc_interaction_order_display_p2.o \
	../interfaces/odbc/odbc_interaction_order_inquiry_p2.o \
	../interfaces/odbc/odbc_interaction_product_detail_p2.o \
	../interfaces/odbc/odbc_interaction_search_request_p2.o \
	../interfaces/odbc/odbc_interaction_search_results_p2.o \
	../interfaces/odbc/odbc_interaction_shopping_cart_p2.o
	$(CC) $(CFLAGS_P2) odbc_test.c -o \
		odbc_test_p2 \
		$(DBDRIVERDIR)/tm_interface.o \
		$(COMMONDIR)/_socket.o \
		../common/common.o \
		../interfaces/odbc/odbc_interaction_p2.o \
		../interfaces/odbc/odbc_interaction_admin_confirm_p2.o \
		../interfaces/odbc/odbc_interaction_admin_request_p2.o \
		../interfaces/odbc/odbc_interaction_best_sellers_p2.o \
		../interfaces/odbc/odbc_interaction_buy_confirm_p2.o \
		../interfaces/odbc/odbc_interaction_buy_request_p2.o \
		../interfaces/odbc/odbc_interaction_home_p2.o \
		../interfaces/odbc/odbc_interaction_new_products_p2.o \
		../interfaces/odbc/odbc_interaction_order_display_p2.o \
		../interfaces/odbc/odbc_interaction_order_inquiry_p2.o \
		../interfaces/odbc/odbc_interaction_product_detail_p2.o \
		../interfaces/odbc/odbc_interaction_search_request_p2.o \
		../interfaces/odbc/odbc_interaction_search_results_p2.o \
		../interfaces/odbc/odbc_interaction_shopping_cart_p2.o \
		$(ODBC)/lib/libsqlod.so $(ODBC)/lib/libsqlrte.so

results: Makefile results.c ../include/common.h
	$(CC) -g -I../include results.c -o results -lm

load_db_proc: Makefile load_db_proc.c ../include/odbc_interaction.h \
		../interfaces/odbc/odbc_interaction_p1.o ../include/common.h
	$(CC) -g -I../include -I$(ODBC)/incl load_db_proc.c -o load_db_proc \
		../interfaces/odbc/odbc_interaction_p1.o ../common/common.o \
		$(ODBC)/lib/libsqlod.so -lm
