
CC = gcc

#ODBC_INCL=/usr/local/include
#ODBC_LIB=/usr/lib/libodbc.so
ODBC_INCL=/opt/sapdb/interfaces/odbc/incl
ODBC_LIB=/opt/sapdb/interfaces/odbc/lib/libsqlod.so
CFLAGS = -g -I$(INCLUDE_DIR) -I$(ODBC_INCL) -DGET_TIME -DSEARCH_RESULTS_CACHE -DAUTOCOMMIT_OFF

COMMON_PRGS = $(COMMON_DIR)/common.c $(COMMON_DIR)/_socket.c
COMMON_OBJS = $(COMMON_PRGS:.c=.so)

ODBC_PRGS = \
	$(ODBC_DIR)/odbc_interaction.c \
	$(ODBC_DIR)/odbc_interaction_admin_confirm.c \
	$(ODBC_DIR)/odbc_interaction_admin_request.c \
	$(ODBC_DIR)/odbc_interaction_best_sellers.c \
	$(ODBC_DIR)/odbc_interaction_buy_confirm.c \
	$(ODBC_DIR)/odbc_interaction_buy_request.c \
	$(ODBC_DIR)/odbc_interaction_home.c \
	$(ODBC_DIR)/odbc_interaction_new_products.c \
	$(ODBC_DIR)/odbc_interaction_order_display.c \
	$(ODBC_DIR)/odbc_interaction_order_inquiry.c \
	$(ODBC_DIR)/odbc_interaction_product_detail.c \
	$(ODBC_DIR)/odbc_interaction_search_request.c \
	$(ODBC_DIR)/odbc_interaction_search_results.c \
	$(ODBC_DIR)/odbc_interaction_shopping_cart.c 
ODBC_OBJS = $(ODBC_PRGS:.c=.so)

ODBC_INCLUDE = $(INCLUDE_DIR)/odbc_interaction_home.h \
	$(INCLUDE_DIR)/odbc_interaction.h \
	$(INCLUDE_DIR)/odbc_interaction_shopping_cart.h \
	$(INCLUDE_DIR)/odbc_interaction_buy_request.h \
	$(INCLUDE_DIR)/odbc_interaction_new_products.h \
	$(INCLUDE_DIR)/odbc_interaction_best_sellers.h \
	$(INCLUDE_DIR)/odbc_interaction_buy_confirm.h \
	$(INCLUDE_DIR)/odbc_interaction_order_inquiry.h \
	$(INCLUDE_DIR)/odbc_interaction_order_display.h \
	$(INCLUDE_DIR)/odbc_interaction_product_detail.h \
	$(INCLUDE_DIR)/odbc_interaction_search_request.h \
	$(INCLUDE_DIR)/odbc_interaction_admin_request.h \
	$(INCLUDE_DIR)/odbc_interaction_admin_confirm.h \
	$(INCLUDE_DIR)/odbc_interaction_search_results.h
