# Makefile
# 20 february 2002

CC = gcc

ODBC = /opt/sapdb/interfaces/odbc
INCLUDE = ../../include

CFLAGS_P1 = -g -DPHASE1 -I$(INCLUDE) -I$(ODBC)/incl
CFLAGS_P2 = -g -DPHASE2 -I$(INCLUDE) -I$(ODBC)/incl

all: \
	odbc_interaction_admin_confirm_p1.o \
	odbc_interaction_admin_request_p1.o \
	odbc_interaction_best_sellers_p1.o \
	odbc_interaction_buy_confirm_p1.o \
	odbc_interaction_buy_request_p1.o \
	odbc_interaction_home_p1.o \
	odbc_interaction_new_products_p1.o \
	odbc_interaction_order_display_p1.o \
	odbc_interaction_order_inquiry_p1.o \
	odbc_interaction_product_detail_p1.o \
	odbc_interaction_search_request_p1.o \
	odbc_interaction_search_results_p1.o \
	odbc_interaction_shopping_cart_p1.o \
	odbc_interaction_p1.o \
	odbc_interaction_admin_confirm_p2.o \
	odbc_interaction_admin_request_p2.o \
	odbc_interaction_best_sellers_p2.o \
	odbc_interaction_buy_confirm_p2.o \
	odbc_interaction_buy_request_p2.o \
	odbc_interaction_home_p2.o \
	odbc_interaction_new_products_p2.o \
	odbc_interaction_order_display_p2.o \
	odbc_interaction_order_inquiry_p2.o \
	odbc_interaction_product_detail_p2.o \
	odbc_interaction_search_request_p2.o \
	odbc_interaction_search_results_p2.o \
	odbc_interaction_shopping_cart_p2.o \
	odbc_interaction_p2.o

odbc_interaction_admin_confirm_p1.o: Makefile $(INCLUDE)/common.h \
	$(INCLUDE)/odbc_interaction.h odbc_interaction_admin_confirm.c \
	$(INCLUDE)/odbc_interaction_admin_confirm.h
	$(CC) -c $(CFLAGS_P1) odbc_interaction_admin_confirm.c \
		-o odbc_interaction_admin_confirm_p1.o

odbc_interaction_admin_request_p1.o: Makefile $(INCLUDE)/common.h \
	$(INCLUDE)/odbc_interaction.h odbc_interaction_admin_request.c \
	$(INCLUDE)/odbc_interaction_admin_request.h
	$(CC) -c $(CFLAGS_P1) odbc_interaction_admin_request.c \
		-o odbc_interaction_admin_request_p1.o

odbc_interaction_best_sellers_p1.o: Makefile $(INCLUDE)/common.h \
	$(INCLUDE)/odbc_interaction.h odbc_interaction_best_sellers.c \
	$(INCLUDE)/odbc_interaction_best_sellers.h
	$(CC) -c $(CFLAGS_P1) odbc_interaction_best_sellers.c -o \
		odbc_interaction_best_sellers_p1.o

odbc_interaction_buy_confirm_p1.o: Makefile $(INCLUDE)/common.h \
	$(INCLUDE)/odbc_interaction.h odbc_interaction_buy_confirm.c \
	$(INCLUDE)/odbc_interaction_buy_confirm.h
	$(CC) -c $(CFLAGS_P1) odbc_interaction_buy_confirm.c -o \
		odbc_interaction_buy_confirm_p1.o

odbc_interaction_buy_request_p1.o: Makefile $(INCLUDE)/common.h \
	$(INCLUDE)/odbc_interaction.h odbc_interaction_buy_request.c \
	$(INCLUDE)/odbc_interaction_buy_request.h
	$(CC) -c $(CFLAGS_P1) odbc_interaction_buy_request.c -o \
		odbc_interaction_buy_request_p1.o

odbc_interaction_home_p1.o: Makefile $(INCLUDE)/common.h \
	$(INCLUDE)/odbc_interaction.h odbc_interaction_home.c \
	$(INCLUDE)/odbc_interaction_home.h
	$(CC) -c $(CFLAGS_P1) odbc_interaction_home.c -o \
		odbc_interaction_home_p1.o

odbc_interaction_new_products_p1.o: Makefile $(INCLUDE)/common.h \
	$(INCLUDE)/odbc_interaction.h odbc_interaction_new_products.c \
	$(INCLUDE)/odbc_interaction_new_products.h
	$(CC) -c $(CFLAGS_P1) odbc_interaction_new_products.c -o \
		odbc_interaction_new_products_p1.o

odbc_interaction_order_display_p1.o: Makefile $(INCLUDE)/common.h \
	$(INCLUDE)/odbc_interaction.h odbc_interaction_order_display.c \
	$(INCLUDE)/odbc_interaction_order_display.h
	$(CC) -c $(CFLAGS_P1) odbc_interaction_order_display.c -o \
		odbc_interaction_order_display_p1.o

odbc_interaction_order_inquiry_p1.o: Makefile $(INCLUDE)/common.h \
	$(INCLUDE)/odbc_interaction.h odbc_interaction_order_inquiry.c \
	$(INCLUDE)/odbc_interaction_order_inquiry.h
	$(CC) -c $(CFLAGS_P1) odbc_interaction_order_inquiry.c -o \
		odbc_interaction_order_inquiry_p1.o

odbc_interaction_product_detail_p1.o: Makefile $(INCLUDE)/common.h \
	$(INCLUDE)/odbc_interaction.h odbc_interaction_product_detail.c \
	$(INCLUDE)/odbc_interaction_product_detail.h
	$(CC) -c $(CFLAGS_P1) odbc_interaction_product_detail.c \
		-o odbc_interaction_product_detail_p1.o

odbc_interaction_search_request_p1.o: Makefile $(INCLUDE)/common.h \
	$(INCLUDE)/odbc_interaction.h odbc_interaction_search_request.c \
	$(INCLUDE)/odbc_interaction_search_request.h
	$(CC) -c $(CFLAGS_P1) odbc_interaction_search_request.c -o \
		odbc_interaction_search_request_p1.o

odbc_interaction_search_results_p1.o: Makefile $(INCLUDE)/common.h \
	$(INCLUDE)/odbc_interaction.h odbc_interaction_search_results.c \
	$(INCLUDE)/odbc_interaction_search_results.h
	$(CC) -c $(CFLAGS_P1) odbc_interaction_search_results.c -o \
		odbc_interaction_search_results_p1.o

odbc_interaction_shopping_cart_p1.o: Makefile $(INCLUDE)/common.h \
	$(INCLUDE)/odbc_interaction.h odbc_interaction_shopping_cart.c\
	 $(INCLUDE)/odbc_interaction_shopping_cart.h
	$(CC) -c $(CFLAGS_P1) odbc_interaction_shopping_cart.c -o \
		odbc_interaction_shopping_cart_p1.o

odbc_interaction_p1.o: Makefile $(INCLUDE)/common.h \
	$(INCLUDE)/odbc_interaction.h odbc_interaction.c \
	$(INCLUDE)/odbc_interaction.h 
	$(CC) -c $(CFLAGS_P1) odbc_interaction.c -o \
		odbc_interaction_p1.o

odbc_interaction_admin_confirm_p2.o: Makefile $(INCLUDE)/common.h \
	$(INCLUDE)/odbc_interaction.h odbc_interaction_admin_confirm.c \
	$(INCLUDE)/odbc_interaction_admin_confirm.h
	$(CC) -c $(CFLAGS_P2) odbc_interaction_admin_confirm.c \
		-o odbc_interaction_admin_confirm_p2.o

odbc_interaction_admin_request_p2.o: Makefile $(INCLUDE)/common.h \
	$(INCLUDE)/odbc_interaction.h odbc_interaction_admin_request.c \
	$(INCLUDE)/odbc_interaction_admin_request.h
	$(CC) -c $(CFLAGS_P2) odbc_interaction_admin_request.c \
		-o odbc_interaction_admin_request_p2.o

odbc_interaction_best_sellers_p2.o: Makefile $(INCLUDE)/common.h \
	$(INCLUDE)/odbc_interaction.h odbc_interaction_best_sellers.c \
	$(INCLUDE)/odbc_interaction_best_sellers.h
	$(CC) -c $(CFLAGS_P2) odbc_interaction_best_sellers.c -o \
		odbc_interaction_best_sellers_p2.o

odbc_interaction_buy_confirm_p2.o: Makefile $(INCLUDE)/common.h \
	$(INCLUDE)/odbc_interaction.h odbc_interaction_buy_confirm.c \
	$(INCLUDE)/odbc_interaction_buy_confirm.h
	$(CC) -c $(CFLAGS_P2) odbc_interaction_buy_confirm.c -o \
		odbc_interaction_buy_confirm_p2.o

odbc_interaction_buy_request_p2.o: Makefile $(INCLUDE)/common.h \
	$(INCLUDE)/odbc_interaction.h odbc_interaction_buy_request.c \
	$(INCLUDE)/odbc_interaction_buy_request.h
	$(CC) -c $(CFLAGS_P2) odbc_interaction_buy_request.c -o \
		odbc_interaction_buy_request_p2.o

odbc_interaction_home_p2.o: Makefile $(INCLUDE)/common.h \
	$(INCLUDE)/odbc_interaction.h odbc_interaction_home.c \
	$(INCLUDE)/odbc_interaction_home.h
	$(CC) -c $(CFLAGS_P2) odbc_interaction_home.c -o \
		odbc_interaction_home_p2.o

odbc_interaction_new_products_p2.o: Makefile $(INCLUDE)/common.h \
	$(INCLUDE)/odbc_interaction.h odbc_interaction_new_products.c \
	$(INCLUDE)/odbc_interaction_new_products.h
	$(CC) -c $(CFLAGS_P2) odbc_interaction_new_products.c -o \
		odbc_interaction_new_products_p2.o

odbc_interaction_order_display_p2.o: Makefile $(INCLUDE)/common.h \
	$(INCLUDE)/odbc_interaction.h odbc_interaction_order_display.c \
	$(INCLUDE)/odbc_interaction_order_display.h
	$(CC) -c $(CFLAGS_P2) odbc_interaction_order_display.c -o \
		odbc_interaction_order_display_p2.o

odbc_interaction_order_inquiry_p2.o: Makefile $(INCLUDE)/common.h \
	$(INCLUDE)/odbc_interaction.h odbc_interaction_order_inquiry.c \
	$(INCLUDE)/odbc_interaction_order_inquiry.h
	$(CC) -c $(CFLAGS_P2) odbc_interaction_order_inquiry.c -o \
		odbc_interaction_order_inquiry_p2.o

odbc_interaction_product_detail_p2.o: Makefile $(INCLUDE)/common.h \
	$(INCLUDE)/odbc_interaction.h odbc_interaction_product_detail.c \
	$(INCLUDE)/odbc_interaction_product_detail.h
	$(CC) -c $(CFLAGS_P2) odbc_interaction_product_detail.c \
		-o odbc_interaction_product_detail_p2.o

odbc_interaction_search_request_p2.o: Makefile $(INCLUDE)/common.h \
	$(INCLUDE)/odbc_interaction.h odbc_interaction_search_request.c \
	$(INCLUDE)/odbc_interaction_search_request.h
	$(CC) -c $(CFLAGS_P2) odbc_interaction_search_request.c -o \
		odbc_interaction_search_request_p2.o

odbc_interaction_search_results_p2.o: Makefile $(INCLUDE)/common.h \
	$(INCLUDE)/odbc_interaction.h odbc_interaction_search_results.c \
	$(INCLUDE)/odbc_interaction_search_results.h
	$(CC) -c $(CFLAGS_P2) odbc_interaction_search_results.c -o \
		odbc_interaction_search_results_p2.o

odbc_interaction_shopping_cart_p2.o: Makefile $(INCLUDE)/common.h \
	$(INCLUDE)/odbc_interaction.h odbc_interaction_shopping_cart.c\
	 $(INCLUDE)/odbc_interaction_shopping_cart.h
	$(CC) -c $(CFLAGS_P2) odbc_interaction_shopping_cart.c -o \
		odbc_interaction_shopping_cart_p2.o

odbc_interaction_p2.o: Makefile $(INCLUDE)/common.h \
	$(INCLUDE)/odbc_interaction.h odbc_interaction.c \
	$(INCLUDE)/odbc_interaction.h 
	$(CC) -c $(CFLAGS_P2) odbc_interaction.c -o \
		odbc_interaction_p2.o

clean:
	rm -f *.o
