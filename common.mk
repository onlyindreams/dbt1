
CC = gcc

SAPDBROOT=/opt/sapdb/interfaces/odbc
CFLAGS = -g -I../include -I$(SAPDBROOT)/incl
INCLUDEDIR = ../include
DBTXNDIR=../interfaces/odbc
COMMONDIR=../common
DBDRIVERDIR=../dbdriver
COMMONOBJS = $(COMMONDIR)/common.o \
	$(COMMONDIR)/_socket.o
COMMONPRGS = $(COMMONDIR)/common.c \
	$(COMMONDIR)/_socket.c
DBOBJS_P1 = \
	$(DBTXNDIR)/odbc_interaction_p1.o \
	$(DBTXNDIR)/odbc_interaction_admin_confirm_p1.o \
	$(DBTXNDIR)/odbc_interaction_admin_request_p1.o \
	$(DBTXNDIR)/odbc_interaction_best_sellers_p1.o \
	$(DBTXNDIR)/odbc_interaction_buy_confirm_p1.o \
	$(DBTXNDIR)/odbc_interaction_buy_request_p1.o \
	$(DBTXNDIR)/odbc_interaction_home_p1.o \
	$(DBTXNDIR)/odbc_interaction_new_products_p1.o \
	$(DBTXNDIR)/odbc_interaction_order_display_p1.o \
	$(DBTXNDIR)/odbc_interaction_order_inquiry_p1.o \
	$(DBTXNDIR)/odbc_interaction_product_detail_p1.o \
	$(DBTXNDIR)/odbc_interaction_search_request_p1.o \
	$(DBTXNDIR)/odbc_interaction_search_results_p1.o \
	$(DBTXNDIR)/odbc_interaction_shopping_cart_p1.o 
DBOBJS_P2 = $(DBTXNDIR)/odbc_interaction_home_p2.o \
	$(DBTXNDIR)/odbc_interaction_p2.o \
	$(DBTXNDIR)/odbc_interaction_shopping_cart_p2.o \
	$(DBTXNDIR)/odbc_interaction_buy_request_p2.o \
	$(DBTXNDIR)/odbc_interaction_new_products_p2.o \
	$(DBTXNDIR)/odbc_interaction_best_sellers_p2.o \
	$(DBTXNDIR)/odbc_interaction_buy_confirm_p2.o \
	$(DBTXNDIR)/odbc_interaction_order_inquiry_p2.o \
	$(DBTXNDIR)/odbc_interaction_order_display_p2.o \
	$(DBTXNDIR)/odbc_interaction_product_detail_p2.o \
	$(DBTXNDIR)/odbc_interaction_search_request_p2.o \
	$(DBTXNDIR)/odbc_interaction_admin_request_p2.o \
	$(DBTXNDIR)/odbc_interaction_admin_confirm_p2.o \
	$(DBTXNDIR)/odbc_interaction_search_results_p2.o
DBPRGS = $(DBTXNDIR)/odbc_interaction_home.c \
	$(DBTXNDIR)/odbc_interaction.c \
	$(DBTXNDIR)/odbc_interaction_shopping_cart.c \
	$(DBTXNDIR)/odbc_interaction_buy_request.c \
	$(DBTXNDIR)/odbc_interaction_new_products.c \
	$(DBTXNDIR)/odbc_interaction_best_sellers.c \
	$(DBTXNDIR)/odbc_interaction_buy_confirm.c \
	$(DBTXNDIR)/odbc_interaction_order_inquiry.c \
	$(DBTXNDIR)/odbc_interaction_order_display.c \
	$(DBTXNDIR)/odbc_interaction_product_detail.c \
	$(DBTXNDIR)/odbc_interaction_search_request.c \
	$(DBTXNDIR)/odbc_interaction_admin_request.c \
	$(DBTXNDIR)/odbc_interaction_admin_confirm.c \
	$(DBTXNDIR)/odbc_interaction_search_results.c
DBINCLUDE = $(INCLUDEDIR)/odbc_interaction_home.h \
	$(INCLUDEDIR)/odbc_interaction.h \
	$(INCLUDEDIR)/odbc_interaction_shopping_cart.h \
	$(INCLUDEDIR)/odbc_interaction_buy_request.h \
	$(INCLUDEDIR)/odbc_interaction_new_products.h \
	$(INCLUDEDIR)/odbc_interaction_best_sellers.h \
	$(INCLUDEDIR)/odbc_interaction_buy_confirm.h \
	$(INCLUDEDIR)/odbc_interaction_order_inquiry.h \
	$(INCLUDEDIR)/odbc_interaction_order_display.h \
	$(INCLUDEDIR)/odbc_interaction_product_detail.h \
	$(INCLUDEDIR)/odbc_interaction_search_request.h \
	$(INCLUDEDIR)/odbc_interaction_admin_request.h \
	$(INCLUDEDIR)/odbc_interaction_admin_confirm.h \
	$(INCLUDEDIR)/odbc_interaction_search_results.h
