/*
 * odbc_test.c
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2002 Mark Wong & Jenny Zhang &
 *                    Open Source Development Lab, Inc.
 *
 * 19 february 2002
 */

#include <stdio.h>
#include <odbc_interaction_admin_confirm.h>
#include <odbc_interaction_admin_request.h>
#include <odbc_interaction_best_sellers.h>
#include <odbc_interaction_buy_confirm.h>
#include <odbc_interaction_buy_request.h>
#include <odbc_interaction_home.h>
#include <odbc_interaction_new_products.h>
#include <odbc_interaction_order_display.h>
#include <odbc_interaction_order_inquiry.h>
#include <odbc_interaction_product_detail.h>
#include <odbc_interaction_shopping_cart.h>
#include <odbc_interaction_search_results.h>
#include <sql.h>
#include <sqlext.h>

#include "eu.h"

#ifdef PHASE1
#include "odbc_interaction.h"
#endif /* PHASE1 */

#ifdef PHASE2
#include "app_interaction.h"
#include "tm_interface.h"
#endif /* PHASE2 */

int main(int argc, char *argv[])
{
	int rc;
	struct eu_context_t ebc;
	struct odbc_context_t odbcc;
	union odbc_data_t odbcd;
	int i;
	char sname[32];

#ifdef PHASE1
	char uname[32], auth[32];
#endif /* PHASE1 */

#ifdef PHASE2
	int port;
#endif /* PHASE2 */

#ifdef PHASE1
	if (argc < 5)
	{
		printf("usage: %s <interaction> <servername> <uname> <password>\n", argv[0]);
#endif /* PHASE1 */

#ifdef PHASE2
	if (argc < 4)
	{
		printf("usage: %s <interaction> <servername> <port>\n", argv[0]);
#endif /* PHASE2 */
		printf("  <interaction>:  ac - Admin Confirm\n");
		printf("                  ar - Admin Request\n");
		printf("                  bs - Best Sellers\n");
		printf("                  bc - Buy Confirm\n");
		printf("                  br - Buy Request\n");
		printf("                  ho - Home\n");
		printf("                  np - New Products\n");
		printf("                  od - Order Display\n");
		printf("                  oi - Order Inquiry\n");
		printf("                  pd - Product Display\n");
		printf("                  sr - Search Request\n");
		printf("                  su - Search Results\n");
		printf("                  sc - Shopping Cart\n");
		return 1;
	}

	item_count = 1000;

	strcpy(sname, argv[2]);
#ifdef PHASE1
	strcpy(uname, argv[3]);
	strcpy(auth, argv[4]);
	odbc_init(sname, uname, auth);
	rc = odbc_connect(&odbcc);
	if (rc == W_ERROR)
	{
		printf("odbc_connect() error\n");
		return 2;
	}
#endif /* PHASE 1 */

#ifdef PHASE2 
	port = atoi(argv[3]);
	bzero(&ebc, sizeof(ebc));
	if ((ebc.s = _connect(sname, port)) == -1)
	{
		LOG_ERROR_MESSAGE("connect failed");
		return;
	}
#endif /* PHASE2 */

	if (strcmp(argv[1], "ac") == 0)
	{
		if (argc == 3)
		{
			ebc.admin_confirm_data.i_id = atoi(argv[2]);
		}
		else
		{
			ebc.admin_confirm_data.i_id = 1;
		}
		ebc.admin_confirm_data.i_image = 11;
		ebc.admin_confirm_data.i_thumbnail = 111;
		ebc.admin_confirm_data.i_cost = 12.34;
		printf("\n");
		printf("i_id: %lld\n", ebc.admin_confirm_data.i_id);
		printf("i_thumbnail: %lld\n", ebc.admin_confirm_data.i_thumbnail);
		printf("i_image: %lld\n", ebc.admin_confirm_data.i_image);
		printf("i_cost: %0.2f\n", ebc.admin_confirm_data.i_cost);

		printf("\nexecuting...\n\n");
#ifdef PHASE1
		copy_in_admin_confirm(&ebc, &odbcd);
		rc = execute_admin_confirm(&odbcc, &odbcd);
		if (rc == W_ERROR)
		{
			printf("execute error\n");
			return 3;
		}
		copy_out_admin_confirm(&ebc, &odbcd);
#endif /* PHASE1 */
#ifdef PHASE2
		ebc.interaction=ADMIN_CONFIRM;
		if (send_interaction_packet(ebc.s, &ebc) == W_ERROR)
		{
			LOG_ERROR_MESSAGE("send failed");
			return W_ERROR;
		}
		if (receive_interaction_packet(ebc.s, &ebc) == W_ERROR)
		{
			LOG_ERROR_MESSAGE("receive failed");
			return W_ERROR;
		}
#endif /* PHASE2 */

		printf("i_image: %lld\n", ebc.admin_confirm_data.i_image);
		printf("i_thumbnail: %lld\n", ebc.admin_confirm_data.i_thumbnail);
		printf("i_cost: %0.2f\n", ebc.admin_confirm_data.i_cost);
		printf("i_title: %s\n", ebc.admin_confirm_data.i_title);
		printf("a_fname: %s\n", ebc.admin_confirm_data.a_fname);
		printf("a_lname: %s\n", ebc.admin_confirm_data.a_lname);
		printf("i_subject: %s\n", ebc.admin_confirm_data.i_subject);
		printf("i_desc: %s\n", ebc.admin_confirm_data.i_desc);
		printf("i_srp: %0.2f\n", ebc.admin_confirm_data.i_srp);
		printf("i_backing: %s\n", ebc.admin_confirm_data.i_backing);
		printf("i_page: %d\n", ebc.admin_confirm_data.i_page);
		printf("i_publisher: %s\n", ebc.admin_confirm_data.i_publisher);
		printf("i_pub_date: %s\n", ebc.admin_confirm_data.i_pub_date);
		printf("i_dimensions: %s\n", ebc.admin_confirm_data.i_dimensions);
		printf("i_isbn: %s\n", ebc.admin_confirm_data.i_isbn);
	}
	else if (strcmp(argv[1], "ar") == 0)
	{
		if (argc == 3)
		{
			ebc.admin_request_data.i_id = atoi(argv[2]);
		}
		else
		{
			ebc.admin_request_data.i_id = 1;
		}
		printf("\ni_id: %lld\n", ebc.admin_request_data.i_id);

		printf("executing...\n");
#ifdef PHASE1
		copy_in_admin_request(&ebc, &odbcd);
		rc = execute_admin_request(&odbcc, &odbcd);
		if (rc == W_ERROR)
		{
			printf("execute error\n");
			return 3;
		}
		copy_out_admin_request(&ebc, &odbcd);
#endif /* PHASE1 */
#ifdef PHASE2
		ebc.interaction=ADMIN_REQUEST;
		if (send_interaction_packet(ebc.s, &ebc) == W_ERROR)
		{
			LOG_ERROR_MESSAGE("send failed");
			return W_ERROR;
		}
		if (receive_interaction_packet(ebc.s, &ebc) == W_ERROR)
		{
			LOG_ERROR_MESSAGE("receive failed");
			return W_ERROR;
		}
#endif /* PHASE2 */

		printf("i_title: %s\n", ebc.admin_request_data.i_title);
		printf("a_fname: %s\n", ebc.admin_request_data.a_fname);
		printf("a_lname: %s\n", ebc.admin_request_data.a_lname);
		printf("i_srp: %0.2f\n", ebc.admin_request_data.i_srp);
		printf("i_cost: %0.2f\n", ebc.admin_request_data.i_cost);
		printf("i_image: %lld\n", ebc.admin_request_data.i_image);
		printf("i_thumbnail: %lld\n", ebc.admin_request_data.i_thumbnail);
	}
	else if (strcmp(argv[1], "bs") == 0)
	{
		char i_subject[I_SUBJECT_LEN + 1];

		if (argc == 3)
		{
			strcpy(i_subject, argv[2]);
		}
		else
		{
			strcpy(i_subject, "ARTS");
		}

		strcpy(ebc.best_sellers_data.i_subject, i_subject);
		printf("\ni_subject = %s\n", ebc.best_sellers_data.i_subject);

		printf("executing...\n");
#ifdef PHASE1
		copy_in_best_sellers(&ebc, &odbcd);
		rc = execute_best_sellers(&odbcc, &odbcd);
		if (rc == W_ERROR)
		{
			printf("execute error\n");
			return 3;
		}
		copy_out_best_sellers(&ebc, &odbcd);
#endif /* PHASE1 */
#ifdef PHASE2
		ebc.interaction=BEST_SELLERS;
		if (send_interaction_packet(ebc.s, &ebc) == W_ERROR)
		{
			LOG_ERROR_MESSAGE("send failed");
			return W_ERROR;
		}
		if (receive_interaction_packet(ebc.s, &ebc) == W_ERROR)
		{
			LOG_ERROR_MESSAGE("receive failed");
			return W_ERROR;
		}
#endif /* PHASE2 */

		for (i = 0; i < PROMOTIONAL_ITEMS_MAX; i++)
		{
			printf("i_related%d: %lld\n", i, 
				ebc.best_sellers_data.pp_data.i_related[i]);
			printf("i_thumbnail%d: %lld\n", i, 
				ebc.best_sellers_data.pp_data.i_thumbnail[i]);
		}
		printf("%d item(s) returned.\n", ebc.best_sellers_data.items);
		for (i = 0; i < ebc.best_sellers_data.items; i++)
		{
			printf("i_id%d: %lld\n", i + 1, 
				ebc.best_sellers_data.results_data[i].i_id);
			printf("i_title%d: %s\n", i + 1, 
				ebc.best_sellers_data.results_data[i].i_title);
			printf("a_fname%d: %s\n", i + 1, 
				ebc.best_sellers_data.results_data[i].a_fname);
			printf("a_lname%d: %s\n", i + 1, 
				ebc.best_sellers_data.results_data[i].a_lname);
		}
	}
	else if (strcmp(argv[1], "bc") == 0)
	{
		if (argc != 5)
		{
			printf("<case>(0--no shipping info 1-- new shipping info) <sc_id> <c_id>\n");
			return 10;
		}

		switch(argv[2][0])
		{
		case '0':
			strcpy(ebc.buy_confirm_data.shipping.addr_street1, "");
			strcpy(ebc.buy_confirm_data.shipping.addr_street2, "");
			strcpy(ebc.buy_confirm_data.shipping.addr_city, "");
			strcpy(ebc.buy_confirm_data.shipping.addr_state, "");
			strcpy(ebc.buy_confirm_data.shipping.addr_zip, "");
			strcpy(ebc.buy_confirm_data.shipping.co_name, "");
			break;
		case '1':
			strcpy(ebc.buy_confirm_data.shipping.addr_street1, "st1");
			strcpy(ebc.buy_confirm_data.shipping.addr_street2, "st2");
			strcpy(ebc.buy_confirm_data.shipping.addr_city, "beaverton");
			strcpy(ebc.buy_confirm_data.shipping.addr_state, "OR");
			strcpy(ebc.buy_confirm_data.shipping.addr_zip, "97006");
			strcpy(ebc.buy_confirm_data.shipping.co_name, "United States");
			break;
		default:
			printf("unknown case\n");
			return 11;
		}
		
		ebc.buy_confirm_data.sc_id=atoi(argv[3]);
		ebc.buy_confirm_data.c_id=atoi(argv[4]);
		strcpy(ebc.buy_confirm_data.cx_type, "VISA");
		strcpy(ebc.buy_confirm_data.cx_num, "1234567890123456");
		strcpy(ebc.buy_confirm_data.cx_expiry, "20030202");
		strcpy(ebc.buy_confirm_data.o_ship_type, "AIR");
		strcpy(ebc.buy_confirm_data.cx_name, "first last");

#ifdef PHASE1
		copy_in_buy_confirm(&ebc, &odbcd);
		rc=execute_buy_confirm(&odbcc, &odbcd);
		if (rc == W_ERROR)
		{
			printf("execute error\n");
			return 3;
		}
		copy_out_buy_confirm(&ebc, &odbcd);
#endif /* PHASE1 */
#ifdef PHASE2
		ebc.interaction=BUY_CONFIRM;
		if (send_interaction_packet(ebc.s, &ebc) == W_ERROR)
		{
			LOG_ERROR_MESSAGE("send failed");
			return W_ERROR;
		}
		if (receive_interaction_packet(ebc.s, &ebc) == W_ERROR)
		{
			LOG_ERROR_MESSAGE("receive failed");
			return W_ERROR;
		}
#endif /* PHASE2 */
		printf("c_discount %f\n", ebc.buy_confirm_data.c_discount);
		printf("sc_sub_total %f\n", ebc.buy_confirm_data.sc_sub_total);
		printf("sc_tax %f\n", ebc.buy_confirm_data.sc_tax);
		printf("sc_ship_cost %f\n", ebc.buy_confirm_data.sc_ship_cost);
		printf("sc_total %f\n", ebc.buy_confirm_data.sc_total);
		printf("got %d items in shopping cart\n", 
			ebc.buy_confirm_data.sc_size);
		for (i = 0; i < ebc.buy_confirm_data.sc_size; i++)
		{
			printf("scl_i_id%d: %ld\n", i, 
				ebc.buy_confirm_data.scl_data[i].scl_i_id);
			printf("scl_qty%d: %d\n", i, 
				ebc.buy_confirm_data.scl_data[i].scl_qty);
			printf("scl_cost%d: %f\n", i, 
				ebc.buy_confirm_data.scl_data[i].scl_cost);
			printf("scl_srp%d: %f\n", i, 
				ebc.buy_confirm_data.scl_data[i].scl_srp);
			printf("scl_title%d: %s\n", i, 
				ebc.buy_confirm_data.scl_data[i].i_title);
			printf("scl_backing%d: %s\n", i, 
				ebc.buy_confirm_data.scl_data[i].i_backing);
		}
	}
	else if (strcmp(argv[1], "br") == 0)
	{
		if (argc < 3)
		{
			printf("pick a case: 0--new customer 1-- return customer\n");
			return 10;
		}

		switch(argv[2][0])
		{
			case '0':
				if (argc != 4)
				{
					printf("input shopping_cart id\n");
					return 10;
				}

				ebc.buy_request_data.sc_id=atoi(argv[3]);
				ebc.buy_request_data.returning_flag=0;
				strcpy(ebc.buy_request_data.c_fname, "osdl");
				strcpy(ebc.buy_request_data.c_lname, "losdl");
				strcpy(ebc.buy_request_data.address.addr_street1, "st1");
				strcpy(ebc.buy_request_data.address.addr_street2, "st2");
				strcpy(ebc.buy_request_data.address.addr_city, "beaverton");
				strcpy(ebc.buy_request_data.address.addr_state, "OR");
				strcpy(ebc.buy_request_data.address.addr_zip, "97006");
				strcpy(ebc.buy_request_data.address.co_name, "United States");
				strcpy(ebc.buy_request_data.c_phone, "5034444444");
				strcpy(ebc.buy_request_data.c_email, "mail@osdl.org");
				strcpy(ebc.buy_request_data.c_birthdate, "19701020");
				strcpy(ebc.buy_request_data.c_data, "open source.org");
				break;
			case '1':
				if (argc != 6)
				{
					printf("input username, password and shopping_cart id\n");
					return 10;
				}

				/* c_id=1 returning customer */
				strcpy(ebc.buy_request_data.c_uname, argv[3]);
				strcpy(ebc.buy_request_data.c_passwd, argv[4]);
				ebc.buy_request_data.sc_id=atoi(argv[5]);
				printf("c_uname: %s\n", ebc.buy_request_data.c_uname);
				printf("c_passwd: %s\n", ebc.buy_request_data.c_passwd);
				ebc.buy_request_data.returning_flag=1;
				break;
			default:
				printf("unknown case\n");
				return 11;
		}
#ifdef PHASE1
		copy_in_buy_request(&ebc, &odbcd);
		rc=execute_buy_request(&odbcc, &odbcd);
		if (rc == W_ERROR)
		{
			printf("execute error\n");
			return 3;
		}
		copy_out_buy_request(&ebc, &odbcd);
#endif /* PHASE1 */
#ifdef PHASE2
		ebc.interaction=BUY_REQUEST;
		if (send_interaction_packet(ebc.s, &ebc) == W_ERROR)
		{
			LOG_ERROR_MESSAGE("send failed");
			return W_ERROR;
		}
		if (receive_interaction_packet(ebc.s, &ebc) == W_ERROR)
		{
			LOG_ERROR_MESSAGE("receive failed");
			return W_ERROR;
		}
#endif /* PHASE2 */

		printf("c_fname %s\n", ebc.buy_request_data.c_fname);
		printf("c_lname %s\n", ebc.buy_request_data.c_lname);
		printf("addr_st1 %s\n", ebc.buy_request_data.address.addr_street1);
		printf("addr_st2 %s\n", ebc.buy_request_data.address.addr_street2);
		printf("addr_city %s\n", ebc.buy_request_data.address.addr_city);
		printf("addr_state %s\n", ebc.buy_request_data.address.addr_state);
		printf("addr_zip %s\n", ebc.buy_request_data.address.addr_zip);
		printf("co_name %s\n", ebc.buy_request_data.address.co_name);
		printf("c_phone %s\n", ebc.buy_request_data.c_phone);
		printf("c_email %s\n", ebc.buy_request_data.c_email);
		printf("c_birthdate %s\n", ebc.buy_request_data.c_birthdate);
		printf("c_data %s\n", ebc.buy_request_data.c_data);
		printf("c_id %lld\n", ebc.buy_request_data.c_id);
		printf("c_discount %f\n", ebc.buy_request_data.c_discount);
		printf("sc_sub_total %f\n", ebc.buy_request_data.sc_sub_total);
		printf("sc_tax %f\n", ebc.buy_request_data.sc_tax);
		printf("sc_ship_cost %f\n", ebc.buy_request_data.sc_ship_cost);
		printf("sc_total %f\n", ebc.buy_request_data.sc_total);
		printf("got %d items in shopping cart\n", 
			ebc.buy_request_data.sc_size);
		for (i = 0; i < ebc.buy_request_data.sc_size; i++)
		{
			printf("scl_i_id%d: %lld\n", i, 
				ebc.buy_request_data.scl_data[i].scl_i_id);
			printf("scl_qty%d: %d\n", i, 
				ebc.buy_request_data.scl_data[i].scl_qty);
			printf("scl_cost%d: %f\n", i, 
				ebc.buy_request_data.scl_data[i].scl_cost);
			printf("scl_srp%d: %f\n", i, 
				ebc.buy_request_data.scl_data[i].scl_srp);
			printf("scl_title%d: %s\n", i, 
				ebc.buy_request_data.scl_data[i].i_title);
			printf("scl_backing%d: %s\n", i, 
				ebc.buy_request_data.scl_data[i].i_backing);
		}
	}
	else if (strcmp(argv[1], "ho") == 0)
	{
		if (argc == 3)
		{
			ebc.home_data.c_id = atoi(argv[2]);
		}
		else
		{
			ebc.home_data.c_id = 1;
		}
		printf("\nc_id: %lld\n", ebc.home_data.c_id);

		printf("executing...\n");
#ifdef PHASE1
		copy_in_home(&ebc, &odbcd);
		rc = execute_home(&odbcc, &odbcd);
		if (rc == W_ERROR)
		{
			printf("execute error\n");
			return 3;
		}
		copy_out_home(&ebc, &odbcd);
#endif /* PHASE1 */
#ifdef PHASE2
		ebc.interaction=HOME;
		if (send_interaction_packet(ebc.s, &ebc) == W_ERROR)
		{
			LOG_ERROR_MESSAGE("send failed");
			return W_ERROR;
		}
		if (receive_interaction_packet(ebc.s, &ebc) == W_ERROR)
		{
			LOG_ERROR_MESSAGE("receive failed");
			return W_ERROR;
		}
#endif /* PHASE2 */

		/* Output data. */
		printf("c_fname: %s\n", ebc.home_data.c_fname);
		printf("c_lname: %s\n", ebc.home_data.c_lname);
		for (i = 0; i < PROMOTIONAL_ITEMS_MAX; i++)
		{
			printf("i_related%d: %ld\n", i, 
				ebc.home_data.pp_data.i_related[i]);
			printf("i_thumbnail%d: %ld\n", i, 
				ebc.home_data.pp_data.i_thumbnail[i]);
		}
	}
	else if (strcmp(argv[1], "np") == 0)
	{
		char i_subject[I_SUBJECT_LEN + 1];

		if (argc == 3)
		{
			strcpy(i_subject, argv[2]);
		}
		else
		{
			strcpy(i_subject, "ARTS");
		}

		strcpy(ebc.new_products_data.i_subject, i_subject);
		printf("\ni_subject = %s\n", ebc.new_products_data.i_subject);

		printf("executing...\n");
#ifdef PHASE1
		copy_in_new_products(&ebc, &odbcd);
		rc = execute_new_products(&odbcc, &odbcd);
		if (rc == W_ERROR)
		{
			printf("execute error\n");
			return 3;
		}
		copy_out_new_products(&ebc, &odbcd);
#endif /* PHASE1 */
#ifdef PHASE2
		ebc.interaction=NEW_PRODUCTS;
		if (send_interaction_packet(ebc.s, &ebc) == W_ERROR)
		{
			LOG_ERROR_MESSAGE("send failed");
			return W_ERROR;
		}
		if (receive_interaction_packet(ebc.s, &ebc) == W_ERROR)
		{
			LOG_ERROR_MESSAGE("receive failed");
			return W_ERROR;
		}
#endif /* PHASE2 */

		for (i = 0; i < PROMOTIONAL_ITEMS_MAX; i++)
		{
			printf("i_related%d: %lld\n", i, 
				ebc.new_products_data.pp_data.i_related[i]);
			printf("i_thumbnail%d: %lld\n", i, 
				ebc.new_products_data.pp_data.i_thumbnail[i]);
		}
		printf("%d item(s) returned.\n", ebc.new_products_data.items);
		for (i = 0; i < ebc.new_products_data.items; i++)
		{
			printf("i_id%d: %lld\n", i + 1, 
				ebc.new_products_data.results_data[i].i_id);
			printf("i_title%d: %s\n", i + 1, 
				ebc.new_products_data.results_data[i].i_title);
			printf("a_fname%d: %s\n", i + 1, 
				ebc.new_products_data.results_data[i].a_fname);
			printf("a_lname%d: %s\n", i + 1, 
				ebc.new_products_data.results_data[i].a_lname);
		}
	}
	else if (strcmp(argv[1], "od") == 0)
	{
		if (argc != 4)
		{
			printf("username password\n");
			return 44;
		}
		strcpy(ebc.order_display_data.c_uname, argv[2]);
		strcpy(ebc.order_display_data.c_passwd, argv[3]);
		printf("\n");
		printf("c_uname: %s\n", ebc.order_display_data.c_uname);
		printf("c_passwd: %s\n", ebc.order_display_data.c_passwd);

#ifdef PHASE1
		copy_in_order_display(&ebc, &odbcd);
		printf("\nexecuting...\n\n");
		rc = execute_order_display(&odbcc, &odbcd);
		if (rc == W_ERROR)
		{
			printf("execute error\n");
			return 3;
		}
		copy_out_order_display(&ebc, &odbcd);
#endif /* PHASE1 */
#ifdef PHASE2
		ebc.interaction=ORDER_DISPLAY;
		if (send_interaction_packet(ebc.s, &ebc) == W_ERROR)
		{
			LOG_ERROR_MESSAGE("send failed");
			return W_ERROR;
		}
		if (receive_interaction_packet(ebc.s, &ebc) == W_ERROR)
		{
			LOG_ERROR_MESSAGE("receive failed");
			return W_ERROR;
		}
#endif /* PHASE2 */

		/* Output data. */
		printf("o_id: %lld\n", ebc.order_display_data.o_id);
		printf("c_fname: %s\n", ebc.order_display_data.c_fname);
		printf("c_lname: %s\n", ebc.order_display_data.c_lname);
		printf("c_phone: %s\n", ebc.order_display_data.c_phone);
		printf("c_email: %s\n", ebc.order_display_data.c_email);
		printf("o_date: %s\n", ebc.order_display_data.o_date);
		printf("o_sub_total: %0.2f\n", ebc.order_display_data.o_sub_total);
		printf("o_tax: %0.2f\n", ebc.order_display_data.o_tax);
		printf("o_total: %0.2f\n", ebc.order_display_data.o_total);
		printf("o_ship_type: %s\n", ebc.order_display_data.o_ship_type);
		printf("o_ship_date: %s\n", ebc.order_display_data.o_ship_date);
		printf("o_status: %s\n", ebc.order_display_data.o_status);
		printf("bill_addr_street1: %s\n",
			ebc.order_display_data.billing.addr_street1);
		printf("bill_addr_street2: %s\n",
			ebc.order_display_data.billing.addr_street2);
		printf("bill_addr_city: %s\n",
			ebc.order_display_data.billing.addr_city);
		printf("bill_addr_state: %s\n",
			ebc.order_display_data.billing.addr_state);
		printf("bill_addr_zip: %s\n",
			ebc.order_display_data.billing.addr_zip);
		printf("bill_co_name: %s\n",
			ebc.order_display_data.billing.co_name);
		printf("ship_addr_street1: %s\n",
			ebc.order_display_data.shipping.addr_street1);
		printf("ship_addr_street2: %s\n",
			ebc.order_display_data.shipping.addr_street2);
		printf("ship_addr_city: %s\n",
			ebc.order_display_data.shipping.addr_city);
		printf("ship_addr_state: %s\n",
			ebc.order_display_data.shipping.addr_state);
		printf("ship_addr_zip: %s\n",
			ebc.order_display_data.shipping.addr_zip);
		printf("ship_co_name: %s\n",
			ebc.order_display_data.shipping.co_name);
		printf("cx_type: %s\n",
			ebc.order_display_data.cx_type);
		printf("cx_auth_id: %s\n",
			ebc.order_display_data.cx_auth_id);
		printf("%d item(s) returned.\n", ebc.order_display_data.items);
		for (i = 0; i < ebc.order_display_data.items; i++)
		{
			printf("ol_i_id%d: %lld\n", i,
				ebc.order_display_data.odl_data[i].ol_i_id);
			printf("i_title%d: %s\n", i,
				ebc.order_display_data.odl_data[i].i_title);
			printf("i_publisher%d: %s\n", i,
				ebc.order_display_data.odl_data[i].i_publisher);
			printf("i_cost%d: %0.2f\n", i,
				ebc.order_display_data.odl_data[i].i_cost);
			printf("ol_qty%d: %d\n", i,
				ebc.order_display_data.odl_data[i].ol_qty);
			printf("ol_discount%d: %0.2f\n", i,
				ebc.order_display_data.odl_data[i].ol_discount);
			printf("ol_comment%d: %s\n", i,
				ebc.order_display_data.odl_data[i].ol_comment);
		}
	}
	else if (strcmp(argv[1], "oi") == 0)
	{
		ebc.order_inquiry_data.c_id = 1;
		printf("\nc_id: %lld\n", ebc.order_inquiry_data.c_id);
		
		printf("executing...\n");
#ifdef PHASE1
		copy_in_order_inquiry(&ebc, &odbcd);
		rc = execute_order_inquiry(&odbcc, &odbcd);
		if (rc == W_ERROR)
		{
			printf("execute error\n");
			return 3;
		}
		copy_out_order_inquiry(&ebc, &odbcd);
#endif /* PHASE1 */
#ifdef PHASE2
		ebc.interaction=ORDER_INQUIRY;
		if (send_interaction_packet(ebc.s, &ebc) == W_ERROR)
		{
			LOG_ERROR_MESSAGE("send failed");
			return W_ERROR;
		}
		if (receive_interaction_packet(ebc.s, &ebc) == W_ERROR)
		{
			LOG_ERROR_MESSAGE("receive failed");
			return W_ERROR;
		}
#endif /* PHASE2 */
		
		/* Output data. */
		printf("c_uname: %s\n", ebc.order_inquiry_data.c_uname);	
	}
	else if (strcmp(argv[1], "pd") == 0)
	{
		if (argc == 3)
		{
			ebc.product_detail_data.i_id = atoi(argv[2]);
		}
		else
		{
			ebc.product_detail_data.i_id = 1;
		}
		printf("\ni_id: %lld\n", ebc.product_detail_data.i_id);

		printf("executing...\n");
#ifdef PHASE1
		copy_in_product_detail(&ebc, &odbcd);
		rc = execute_product_detail(&odbcc, &odbcd);
		if (rc == W_ERROR)
		{
			printf("execute error\n");
			return 3;
		}
		copy_out_product_detail(&ebc, &odbcd);
#endif /* PHASE1 */
#ifdef PHASE2
		ebc.interaction=PRODUCT_DETAIL;
		if (send_interaction_packet(ebc.s, &ebc) == W_ERROR)
		{
			LOG_ERROR_MESSAGE("send failed");
			return W_ERROR;
		}
		if (receive_interaction_packet(ebc.s, &ebc) == W_ERROR)
		{
			LOG_ERROR_MESSAGE("receive failed");
			return W_ERROR;
		}
#endif /* PHASE2 */

		printf("i_title: %s\n", ebc.product_detail_data.i_title);
		printf("a_fname: %s\n", ebc.product_detail_data.a_fname);
		printf("a_lname: %s\n", ebc.product_detail_data.a_lname);
		printf("i_pub_date: %s\n", ebc.product_detail_data.i_pub_date);
		printf("i_publisher: %s\n", ebc.product_detail_data.i_publisher);
		printf("i_subject: %s\n", ebc.product_detail_data.i_subject);
		printf("i_desc: %s\n", ebc.product_detail_data.i_desc);
		printf("i_image: %lld\n", ebc.product_detail_data.i_image);
		printf("i_cost: %0.2f\n", ebc.product_detail_data.i_cost);
		printf("i_srp: %0.2f\n", ebc.product_detail_data.i_srp);
		printf("i_avail: %s\n", ebc.product_detail_data.i_avail);
		printf("i_isbn: %s\n", ebc.product_detail_data.i_isbn);
		printf("i_page: %d\n", ebc.product_detail_data.i_page);
		printf("i_backing: %s\n", ebc.product_detail_data.i_backing);
		printf("i_dimensions: %s\n", ebc.product_detail_data.i_dimensions);
	}
	else if (strcmp(argv[1], "sr") == 0)
	{
		printf("\nexecuting...\n\n");
#ifdef PHASE1
		rc = execute_search_request(&odbcc, &odbcd);
		if (rc == W_ERROR)
		{
			printf("execute error\n");
			return 3;
		}
		copy_out_search_request(&ebc, &odbcd);
#endif /* PHASE1 */
#ifdef PHASE2
		ebc.interaction=SEARCH_REQUEST;
		if (send_interaction_packet(ebc.s, &ebc) == W_ERROR)
		{
			LOG_ERROR_MESSAGE("send failed");
			return W_ERROR;
		}
		if (receive_interaction_packet(ebc.s, &ebc) == W_ERROR)
		{
			LOG_ERROR_MESSAGE("receive failed");
			return W_ERROR;
		}
#endif /* PHASE2 */

		/* Output data. */
		for (i = 0; i < PROMOTIONAL_ITEMS_MAX; i++)
		{
			printf("i_related%d: %ld\n", i, 
				ebc.search_request_data.pp_data.i_related[i]);
			printf("i_thumbnail%d: %ld\n", i, 
				ebc.search_request_data.pp_data.i_thumbnail[i]);
		}
	}
	else if (strcmp(argv[1], "su") == 0)
	{
		if (argc < 3)
		{
			printf("select a case 0--author 1--subject 2--title\n");
			return 9;
		}

		switch (argv[2][0])
		{
			case '0':
				ebc.search_results_data.search_type = SEARCH_AUTHOR;
				strcpy(ebc.search_results_data.search_string, "BA");
				break;
			case '1':
				ebc.search_results_data.search_type = SEARCH_SUBJECT;
				strcpy(ebc.search_results_data.search_string, "ARTS");
				break;
			case '2':
				ebc.search_results_data.search_type = SEARCH_TITLE;
				strcpy(ebc.search_results_data.search_string, "BA");
				break;
			default:
				return 10;
				break;
		}
		printf("\nsearch_type: %d\n", ebc.search_results_data.search_type);
		printf("search_string: %s\n", ebc.search_results_data.search_string);

		printf("executing...\n");
#ifdef PHASE1
		copy_in_search_results(&ebc, &odbcd);
		execute_search_results(&odbcc, &odbcd);
		if (rc == W_ERROR)
		{
			printf("execute error\n");
			return 3;
		}
		copy_out_search_results(&ebc, &odbcd);
#endif /* PHASE1 */
#ifdef PHASE2
		ebc.interaction=SEARCH_RESULTS;
		if (send_interaction_packet(ebc.s, &ebc) == W_ERROR)
		{
			LOG_ERROR_MESSAGE("send failed");
			return W_ERROR;
		}
		if (receive_interaction_packet(ebc.s, &ebc) == W_ERROR)
		{
			LOG_ERROR_MESSAGE("receive failed");
			return W_ERROR;
		}
#endif /* PHASE2 */

		for (i = 0; i < PROMOTIONAL_ITEMS_MAX; i++)
		{
			printf("i_related%d: %lld\n", i, 
				ebc.search_results_data.pp_data.i_related[i]);
			printf("i_thumbnail%d: %lld\n", i, 
				ebc.search_results_data.pp_data.i_thumbnail[i]);
		}
		printf("%d item(s) returned.\n", ebc.search_results_data.items);
		for (i = 0; i < ebc.search_results_data.items; i++)
		{
			printf("i_id%d: %lld\n", i + 1, 
				ebc.search_results_data.results_data[i].i_id);
			printf("i_title%d: %s\n", i + 1, 
				ebc.search_results_data.results_data[i].i_title);
			printf("a_fname%d: %s\n", i + 1, 
				ebc.search_results_data.results_data[i].a_fname);
			printf("a_lname%d: %s\n", i + 1, 
				ebc.search_results_data.results_data[i].a_lname);
		}
	}
	else if (strcmp(argv[1], "sc") == 0)
	{
		if (argc != 5)
		{
			printf("input: <case, 0--view shopping cart for the first time 1-- add an item 2--refresh> <sc_id> <c_id>\n");
			return 10;
		}
		
		ebc.shopping_cart_data.sc_id = atoi(argv[3]);
		ebc.shopping_cart_data.c_id = atoi(argv[4]);
		switch(argv[2][0])
		{
		case '0':
			/* add_flag=0, and empty pair, add a random item*/
			printf("viewing shopping cart for the first time\n");
			ebc.shopping_cart_data.add_flag = 0;
			ebc.shopping_cart_data.sc_size = 0;
			break;
		case '1':
			/* add_flag=1, add an item to shopping_cart */
			printf("add an item to shopping_cart\n");
			ebc.shopping_cart_data.add_flag = 1;
			ebc.shopping_cart_data.i_id = 1;
			ebc.shopping_cart_data.sc_size = 1;
			break;
		case '2':
			/* add_flag=0, with pair, refresh shopping cart */
			printf("refresh shopping_cart\n");
			ebc.shopping_cart_data.add_flag = 0;
			ebc.shopping_cart_data.sc_size = 2;
			for (i=0;i<SHOPPING_CART_ITEMS_MAX;i++)
			{
				 ebc.shopping_cart_data.sc_refresh[i].scl_i_id=0;
				 ebc.shopping_cart_data.sc_refresh[i].scl_qty=0;
			}
			ebc.shopping_cart_data.sc_refresh[0].scl_i_id=443;
			ebc.shopping_cart_data.sc_refresh[0].scl_qty=0;
			ebc.shopping_cart_data.sc_refresh[1].scl_i_id=1;
			ebc.shopping_cart_data.sc_refresh[1].scl_qty=4;
			break;
		default:
			printf("unknown case\n");
			return 11;
		}
#ifdef PHASE1
		copy_in_shopping_cart(&ebc, &odbcd);
		rc = execute_shopping_cart(&odbcc, &odbcd);
		if (rc == W_ERROR)
		{
			printf("execute error\n");
			return 3;
		}
		copy_out_shopping_cart(&ebc, &odbcd);
#endif /* PHASE1 */
#ifdef PHASE2
		ebc.interaction=SHOPPING_CART;
		if (send_interaction_packet(ebc.s, &ebc) == W_ERROR)
		{
			LOG_ERROR_MESSAGE("send failed");
			return W_ERROR;
		}
		if (receive_interaction_packet(ebc.s, &ebc) == W_ERROR)
		{
			LOG_ERROR_MESSAGE("receive failed");
			return W_ERROR;
		}
#endif /* PHASE2 */

		printf("sc_id is %lld\n", ebc.shopping_cart_data.sc_id);
		for (i = 0; i < PROMOTIONAL_ITEMS_MAX; i++)
		{
			printf("i_related %d: %lld\n", i,
			ebc.shopping_cart_data.pp_data.i_related[i]);
		}
		printf("got %d items in shopping cart\n", 
			ebc.shopping_cart_data.sc_size);
		for (i = 0; i < ebc.shopping_cart_data.sc_size; i++)
		{
			printf("scl_i_id%d: %ld\n", i, 
				ebc.shopping_cart_data.scl_data[i].scl_i_id);
			printf("scl_qty%d: %d\n", i, 
				ebc.shopping_cart_data.scl_data[i].scl_qty);
			printf("scl_cost%d: %f\n", i, 
				ebc.shopping_cart_data.scl_data[i].scl_cost);
			printf("scl_srp%d: %f\n", i, 
				ebc.shopping_cart_data.scl_data[i].scl_srp);
			printf("scl_title%d: %s\n", i, 
				ebc.shopping_cart_data.scl_data[i].i_title);
			printf("scl_backing%d: %s\n", i, 
				ebc.shopping_cart_data.scl_data[i].i_backing);
		}
	}
	else
	{
		printf("unknown interaction\n");
		return 7;
	}

	printf("\ndone.\n");

	return 0;
}
