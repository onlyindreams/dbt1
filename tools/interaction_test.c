/*
 * interaction_test.c
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) Open Source Development Lab, Inc.
 *
 * History:
 * Feb-2002 Created by Mark Wong & Jenny Zhang
 */

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <_socket.h>

#include <eu.h>
#include <db.h>
#include <tm_interface.h>
#include <cache_interface.h>

#define DISPLAY_INPUT_DATA 0
#define DISPLAY_OUTPUT_DATA 1
#define DISPLAY_ALL_DATA 2

#define MODE_APPSERVER 0
#define MODE_DIRECT 1

#define MODE_CACHE_OFF 0
#define MODE_CACHE_ON 1

/* Global Variables */
int c_id = 1;
char c_passwd[C_PASSWD_LEN + 1] = "og";
char c_uname[C_UNAME_LEN + 1] = "OG";
int help = 0;
int i_id = 1;
int cart_mode = 0;
int new_customer = 0;
int sc_id = 1;
int search = SEARCH_SUBJECT;
int ship_to_billing = 0;
char subject[I_SUBJECT_LEN + 1] = "ARTS";

int mode_access = MODE_APPSERVER;
int mode_cache = MODE_CACHE_OFF;

/* Prototypes */
int display_data(int interaction, int inout, void *data);
int display_admin_confirm_data(int inout, struct admin_confirm_t *data);
int display_admin_request_data(int inout, struct admin_request_t *data);
int display_best_sellers_data(int inout, struct best_sellers_t *data);
int display_buy_confirm_data(int inout, struct buy_confirm_t *data);
int display_buy_request_data(int inout, struct buy_request_t *data);
int display_home_data(int inout, struct home_t *data);
int display_new_products_data(int inout, struct new_products_t *data);
int display_order_display_data(int inout, struct order_display_t *data);
int display_order_inquiry_data(int inout, struct order_inquiry_t *data);
int display_product_detail_data(int inout, struct product_detail_t *data);
int display_search_request_data(int inout, struct search_request_t *data);
int display_search_results_data(int inout, struct search_results_t *data);
int display_shopping_cart_data(int inout, struct shopping_cart_t *data);

int generate_input_data(int interaction, void *data);
int generate_admin_confirm_data(struct admin_confirm_t *data);
int generate_admin_request_data(struct admin_request_t *data);
int generate_best_sellers_data(struct best_sellers_t *data);
int generate_buy_confirm_data(struct buy_confirm_t *data);
int generate_buy_request_data(struct buy_request_t *data);
int generate_home_data(struct home_t *data);
int generate_new_products_data(struct new_products_t *data);
int generate_order_display_data(struct order_display_t *data);
int generate_order_inquiry_data(struct order_inquiry_t *data);
int generate_product_detail_data(struct product_detail_t *data);
int generate_search_results_data(struct search_results_t *data);
int generate_shopping_cart_data(struct shopping_cart_t *data);

int usage(char *name);

int main(int argc, char *argv[])
{
	struct db_conn_t db_conn;

	struct eu_context_t euc;
	char interact[4];

	struct db_context_t dbc;

	int cache_sock;
	char cache_host[256] = "";
	int cache_port = 0;

	/* Variables for getopt_long_only(). */
	int c;
	int port;

	strcpy(db_conn.dbhost, "localhost");
	strcpy(db_conn.dbname, "DBT1");
	strcpy(db_conn.dbuser, "pgsql");
	strcpy(db_conn.dbpass, "pgsql");

	if (argc < 3)
	{
		return usage(argv[0]);
	}

	while (1)
	{
		static struct option long_options[] = {
			{ "access_cache", no_argument, &mode_cache, MODE_CACHE_ON },
			{ "access_direct", no_argument, &mode_access, MODE_DIRECT },
			{ "add_item", no_argument, &cart_mode, 1 },
			{ "c_id", required_argument, 0, 0 },
			{ "c_passwd", required_argument, 0, 0 },
			{ "c_uname", required_argument, 0, 0 },
			{ "cache_host", required_argument, 0, 0 },
			{ "cache_port", required_argument, 0, 0 },
			{ "help", no_argument, &help, 1 },
			{ "dbhost", required_argument, 0, 0 },
			{ "i_id", required_argument, 0, 0 },
			{ "interaction", required_argument, 0, 0 },
			{ "new_customer", no_argument, &new_customer, 1 },
			{ "port", required_argument, 0, 0 },
			{ "search_by_author", no_argument, &search, SEARCH_AUTHOR },
			{ "search_by_subject", no_argument, &search, SEARCH_SUBJECT },
			{ "search_by_title", no_argument, &search, SEARCH_TITLE },
			{ "ship_to_billing", no_argument, &ship_to_billing, 1 },
			{ "sc_id", required_argument, 0, 0 },
			{ "subject", required_argument, 0, 0 },
			{ "view_cart", no_argument, &cart_mode, 0 },
			{ "update_cart", no_argument, &cart_mode, 2 },
			{ 0, 0, 0, 0 }
		};
		int option_index = 0;

		c = getopt_long_only(argc, argv, "", long_options, &option_index);
		if (c == -1)
		{
			break;
		}

		switch (c)
		{
			case 0:
				if (long_options[option_index].flag != 0)
				{
					break;
				}

				if (strcmp(long_options[option_index].name, "c_id") == 0)
				{
					c_id = atoi(optarg);
				}
				else if (strcmp(long_options[option_index].name, "help") == 0)
				{
					printf("so you want some help?\n");
					exit(1);
				}
				else if (strcmp(long_options[option_index].name, "dbhost") == 0)
				{
					strcpy(db_conn.dbhost, optarg);
				}
				else if (strcmp(long_options[option_index].name, "i_id") == 0)
				{
					i_id = atoi(optarg);
				}
				else if (strcmp(long_options[option_index].name,
					"interaction") == 0)
				{
					strcpy(interact, optarg);
				}
				else if (strcmp(long_options[option_index].name, "port") == 0)
				{
					port = atoi(optarg);
				}
				else if (strcmp(long_options[option_index].name, "sc_id") == 0)
				{
					sc_id = atoi(optarg);
				}
				else if (strcmp(long_options[option_index].name,
					"subject") == 0)
				{
					strcpy(subject, optarg);
				}
				else if (strcmp(long_options[option_index].name,
					"c_uname") == 0)
				{
					strcpy(c_uname, optarg);
				}
				else if (strcmp(long_options[option_index].name,
					"c_passwd") == 0)
				{
					strcpy(c_passwd, optarg);
				}
				else if (strcmp(long_options[option_index].name,
					"cache_host") == 0)
				{
					strcpy(cache_host, optarg);
				}
				else if (strcmp(long_options[option_index].name,
					"cache_port") == 0)
				{
					cache_port = atoi(optarg);
				}
				break;
			default:
				printf ("?? getopt returned character code 0%o ??\n", c);
				exit(1);
		}
	}

	if (help == 1)
	{
		return usage(argv[0]);
	}

	/* This should be a command line argument. */
	item_count = 1000;

	/* Zero out the context of this user, just in case there is garbage. */
	bzero(&euc, sizeof(euc));
	if (mode_access == MODE_APPSERVER)
	{
		if ((euc.s = _connect(db_conn.dbhost, port)) == -1)
		{
			LOG_ERROR_MESSAGE("connect failed");
			return 2;
		}
	}
	else
	{
		if (db_init(db_conn) != OK)
		{
			printf("sname2 %s, dbname2 %s, dbport2 %s, uname2 %s, auth2 %s\n",
			       db_conn.dbhost, db_conn.dbname, db_conn.dbport, db_conn.dbuser, db_conn.dbpass);
			printf("db environment initialization failed\n");
			return -1;
		}
		if (db_connect(&dbc) != OK)
		{
			printf("could not connect to the database\n");
			return -1;
		}

		if (mode_cache == MODE_CACHE_ON)
		{
			if (cache_host[0] == '\0')
			{
				printf("use --cache_host <hostname>\n");
				return 1;
			}
			if (!cache_port)
			{
				printf("use --cache_post <port>\n");
				return 1;
			}
			cache_sock = _connect(cache_host, cache_port);
		}
	}

	if (strcmp(interact, "ac") == 0)
	{
		euc.interaction = ADMIN_CONFIRM;
		generate_input_data(euc.interaction, &euc.admin_confirm_data);
		display_data(euc.interaction, DISPLAY_INPUT_DATA,
			&euc.admin_confirm_data);
	}
	else if (strcmp(interact, "ar") == 0)
	{
		euc.interaction = ADMIN_REQUEST;
		generate_input_data(euc.interaction, &euc.admin_request_data);
		display_data(euc.interaction, DISPLAY_INPUT_DATA,
			&euc.admin_request_data);
	}
	else if (strcmp(interact, "bs") == 0)
	{
		euc.interaction = BEST_SELLERS;
		generate_input_data(euc.interaction, &euc.best_sellers_data);
		display_data(euc.interaction, DISPLAY_INPUT_DATA,
			&euc.best_sellers_data);
	}
	else if (strcmp(interact, "bc") == 0)
	{
		euc.interaction = BUY_CONFIRM;
		generate_input_data(euc.interaction, &euc.buy_confirm_data);
		display_data(euc.interaction, DISPLAY_INPUT_DATA,
			&euc.buy_confirm_data);
	}
	else if (strcmp(interact, "br") == 0)
	{
		euc.interaction = BUY_REQUEST;
		generate_input_data(euc.interaction, &euc.buy_request_data);
		display_data(euc.interaction, DISPLAY_INPUT_DATA,
			&euc.buy_request_data);
	}
	else if (strcmp(interact, "ho") == 0)
	{
		euc.interaction = HOME;
		generate_input_data(euc.interaction, &euc.home_data);
		display_data(euc.interaction, DISPLAY_INPUT_DATA, &euc.home_data);
	}
	else if (strcmp(interact, "np") == 0)
	{
		euc.interaction = NEW_PRODUCTS;
		generate_input_data(euc.interaction, &euc.new_products_data);
		display_data(euc.interaction, DISPLAY_INPUT_DATA,
			&euc.new_products_data);
	}
	else if (strcmp(interact, "od") == 0)
	{
		euc.interaction = ORDER_DISPLAY;
		generate_input_data(euc.interaction, &euc.order_display_data);
		display_data(euc.interaction, DISPLAY_INPUT_DATA,
			&euc.order_display_data);
	}
	else if (strcmp(interact, "oi") == 0)
	{
		euc.interaction = ORDER_INQUIRY;
		generate_input_data(euc.interaction, &euc.order_inquiry_data);
		display_data(euc.interaction, DISPLAY_INPUT_DATA,
			&euc.order_inquiry_data);
	}
	else if (strcmp(interact, "pd") == 0)
	{
		euc.interaction = PRODUCT_DETAIL;
		generate_input_data(euc.interaction, &euc.product_detail_data);
		display_data(euc.interaction, DISPLAY_INPUT_DATA,
			&euc.product_detail_data);
	}
	else if (strcmp(interact, "sr") == 0)
	{
		euc.interaction = SEARCH_REQUEST;
		generate_input_data(euc.interaction, &euc.search_request_data);
		display_data(euc.interaction, DISPLAY_INPUT_DATA,
			&euc.search_request_data);
	}
	else if (strcmp(interact, "su") == 0)
	{
		euc.interaction = SEARCH_RESULTS;
		generate_input_data(euc.interaction, &euc.search_results_data);
		display_data(euc.interaction, DISPLAY_INPUT_DATA,
			&euc.search_results_data);
	}
	else if (strcmp(interact, "sc") == 0)
	{
		euc.interaction = SHOPPING_CART;
		generate_input_data(euc.interaction, &euc.shopping_cart_data);
		display_data(euc.interaction, DISPLAY_INPUT_DATA,
			&euc.shopping_cart_data);
	}
	else
	{
		printf("unknown interaction\n");
		return 7;
	}

	if (mode_access == MODE_APPSERVER)
	{
		/* Send and retrieve the interaction data to the application server. */
		printf("Sending interaction data...\n");
		if (send_interaction_packet(euc.s, &euc) == ERROR)
		{
			LOG_ERROR_MESSAGE("send failed");
			return ERROR;
		}
		printf("Waiting to receive interaction results...\n");
		if (receive_interaction_packet(euc.s, &euc) == ERROR)
		{
			LOG_ERROR_MESSAGE("receive failed");
			return ERROR;
		}
	}
	else
	{
		void *data = NULL;
		switch (euc.interaction)
		{
			case ADMIN_CONFIRM:
				data = &euc.admin_confirm_data;
				break;
			case ADMIN_REQUEST:
				data = &euc.admin_request_data;
				break;
			case BEST_SELLERS:
				data = &euc.best_sellers_data;
				break;
			case BUY_CONFIRM:
				data = &euc.buy_confirm_data;
				break;
			case BUY_REQUEST:
				data = &euc.buy_request_data;
				break;
			case HOME:
				data = &euc.home_data;
				break;
			case NEW_PRODUCTS:
				data = &euc.new_products_data;
				break;
			case ORDER_DISPLAY:
				data = &euc.order_display_data;
				break;
			case ORDER_INQUIRY:
				data = &euc.order_inquiry_data;
				break;
			case PRODUCT_DETAIL:
				data = &euc.product_detail_data;
				break;
			case SEARCH_REQUEST:
				data = &euc.search_request_data;
				break;
			case SEARCH_RESULTS:
				data = &euc.search_results_data;
				break;
			case SHOPPING_CART:
				data = &euc.shopping_cart_data;
				break;
		}
		if (euc.interaction == SEARCH_RESULTS && mode_cache == MODE_CACHE_ON &&
			euc.search_results_data.search_type != SEARCH_SUBJECT)
		{
			if (send_search_results(cache_sock, &euc.search_results_data) != OK)
			{
				printf("could not send data to cache\n");
				return 1;
			}
			if (receive_search_results(cache_sock, &euc.search_results_data) !=
				OK)
			{
				printf("could not receive data from cache\n");
				return 1;
			}
		}
		else if (process_interaction(euc.interaction, &dbc, data) != OK)
		{
			printf("process_interaction() error\n");
			return 1;
		}
	}

	if (strcmp(interact, "ac") == 0)
	{
		display_data(euc.interaction, DISPLAY_OUTPUT_DATA,
			&euc.admin_confirm_data);
	}
	else if (strcmp(interact, "ar") == 0)
	{
		display_data(euc.interaction, DISPLAY_OUTPUT_DATA,
			&euc.admin_request_data);
	}
	else if (strcmp(interact, "bs") == 0)
	{
		display_data(euc.interaction, DISPLAY_OUTPUT_DATA,
			&euc.best_sellers_data);
	}
	else if (strcmp(interact, "bc") == 0)
	{
		display_data(euc.interaction, DISPLAY_OUTPUT_DATA,
			&euc.buy_confirm_data);
	}
	else if (strcmp(interact, "br") == 0)
	{
		display_data(euc.interaction, DISPLAY_OUTPUT_DATA,
			&euc.buy_request_data);
	}
	else if (strcmp(interact, "ho") == 0)
	{
		display_data(euc.interaction, DISPLAY_OUTPUT_DATA, &euc.home_data);
	}
	else if (strcmp(interact, "np") == 0)
	{
		display_data(euc.interaction, DISPLAY_OUTPUT_DATA,
			&euc.new_products_data);
	}
	else if (strcmp(interact, "od") == 0)
	{
		display_data(euc.interaction, DISPLAY_OUTPUT_DATA,
			&euc.order_display_data);
	}
	else if (strcmp(interact, "oi") == 0)
	{
		display_data(euc.interaction, DISPLAY_OUTPUT_DATA,
			&euc.order_inquiry_data);
	}
	else if (strcmp(interact, "pd") == 0)
	{
		display_data(euc.interaction, DISPLAY_OUTPUT_DATA,
			&euc.product_detail_data);
	}
	else if (strcmp(interact, "sr") == 0)
	{
		display_data(euc.interaction, DISPLAY_OUTPUT_DATA,
			&euc.search_request_data);
	}
	else if (strcmp(interact, "su") == 0)
	{
		display_data(euc.interaction, DISPLAY_OUTPUT_DATA,
			&euc.search_results_data);
	}
	else if (strcmp(interact, "sc") == 0)
	{
		display_data(euc.interaction, DISPLAY_OUTPUT_DATA,
			&euc.shopping_cart_data);
	}

	printf("\ndone.\n");

	db_disconnect(&dbc);
	return 0;
}

int display_data(int interaction, int inout, void *data)
{
	if (inout == DISPLAY_INPUT_DATA)
	{
		printf("--%s Input Data--\n", interaction_name[interaction]);
	}
	else if (inout == DISPLAY_OUTPUT_DATA)
	{
		printf("--%s Output Data--\n", interaction_name[interaction]);
	}
	else
	{
		printf("what do you want me to display?\n");
		return 1;
	}

	switch (interaction)
	{
		case ADMIN_CONFIRM:
			display_admin_confirm_data(inout, (struct admin_confirm_t *) data);
			break;
		case ADMIN_REQUEST:
			display_admin_request_data(inout, (struct admin_request_t *) data);
			break;
		case BEST_SELLERS:
			display_best_sellers_data(inout, (struct best_sellers_t *) data);
			break;
		case BUY_CONFIRM:
			display_buy_confirm_data(inout, (struct buy_confirm_t *) data);
			break;
		case BUY_REQUEST:
			display_buy_request_data(inout, (struct buy_request_t *) data);
			break;
		case HOME:
			display_home_data(inout, (struct home_t *) data);
			break;
		case NEW_PRODUCTS:
			display_new_products_data(inout, (struct new_products_t *) data);
			break;
		case ORDER_DISPLAY:
			display_order_display_data(inout, (struct order_display_t *) data);
			break;
		case ORDER_INQUIRY:
			display_order_inquiry_data(inout, (struct order_inquiry_t *) data);
			break;
		case PRODUCT_DETAIL:
			display_product_detail_data(inout,
				(struct product_detail_t *) data);
			break;
		case SEARCH_REQUEST:
			display_search_request_data(inout,
				(struct search_request_t *) data);
			break;
		case SEARCH_RESULTS:
			display_search_results_data(inout,
				(struct search_results_t *) data);
			break;
		case SHOPPING_CART:
			display_shopping_cart_data(inout, (struct shopping_cart_t *) data);
			break;
		default:
			printf("unknown interaction %d\n", interaction);
			exit(1);
	}
	return 1;
}

int display_admin_confirm_data(int inout, struct admin_confirm_t *data)
{
	if (inout == DISPLAY_INPUT_DATA)
	{
		printf("i_id: %lld\n", data->i_id);
		printf("i_thumbnail: %lld\n", data->i_thumbnail);
		printf("i_image: %lld\n", data->i_image);
		printf("i_cost: %0.2f\n", data->i_cost);
	}
	else if (inout == DISPLAY_OUTPUT_DATA)
	{
		printf("i_image: %lld\n", data->i_image);
		printf("i_thumbnail: %lld\n", data->i_thumbnail);
		printf("i_cost: %0.2f\n", data->i_cost);
		printf("i_title: %s\n", data->i_title);
		printf("a_fname: %s\n", data->a_fname);
		printf("a_lname: %s\n", data->a_lname);
		printf("i_subject: %s\n", data->i_subject);
		printf("i_desc: %s\n", data->i_desc);
		printf("i_srp: %0.2f\n", data->i_srp);
		printf("i_backing: %s\n", data->i_backing);
		printf("i_page: %d\n", data->i_page);
		printf("i_publisher: %s\n", data->i_publisher);
		printf("i_pub_date: %s\n", data->i_pub_date);
		printf("i_dimensions: %s\n", data->i_dimensions);
		printf("i_isbn: %s\n", data->i_isbn);
	}
	return 1;
}

int display_admin_request_data(int inout, struct admin_request_t *data)
{
	if (inout == DISPLAY_INPUT_DATA)
	{
		printf("i_id: %lld\n", data->i_id);
	}
	else if (inout == DISPLAY_OUTPUT_DATA)
	{
		printf("i_title: %s\n", data->i_title);
		printf("a_fname: %s\n", data->a_fname);
		printf("a_lname: %s\n", data->a_lname);
		printf("i_srp: %0.2f\n", data->i_srp);
		printf("i_cost: %0.2f\n", data->i_cost);
		printf("i_image: %lld\n", data->i_image);
		printf("i_thumbnail: %lld\n", data->i_thumbnail);
	}
	return 1;
}

int display_best_sellers_data(int inout, struct best_sellers_t *data)
{
	int i;

	if (inout == DISPLAY_INPUT_DATA)
	{
		printf("i_subject = %s\n", data->i_subject);
	}
	else if (inout == DISPLAY_OUTPUT_DATA)
	{
		printf("\n");
		printf(" #  i_related i_thumbnail\n");
		printf("-- ---------- -----------\n");
		for (i = 0; i < PROMOTIONAL_ITEMS_MAX; i++)
		{
			printf("%2i %10lld %11lld\n", i, data->pp_data.i_related[i],
				data->pp_data.i_thumbnail[i]);
		}
		printf("\n");
		printf("%d item(s) returned:\n", data->items);
		printf("\n");
		printf("%2s %-10s %-60s %-20s %-20s\n", "#", "i_id", "i_title",
			"a_fname", "a_lname");
		printf("%2s %-10s %-60s %-20s %-20s\n", "--", "-----", "-----",
			"-----", "-----");
		for (i = 0; i < data->items; i++)
		{
			printf("%2d %10lld %-60s %-20s %-20s\n", i,
				data->results_data[i].i_id, data->results_data[i].i_title,
				data->results_data[i].a_fname, data->results_data[i].a_lname);
		}
	}
	return 1;
}

int display_buy_confirm_data(int inout, struct buy_confirm_t *data)
{
	int i;

	if (inout == DISPLAY_INPUT_DATA)
	{
		printf("cx_type: %s\n", data->cx_type);
		printf("cx_num: %s\n", data->cx_num);
		printf("cx_expiry: %s\n", data->cx_expiry);
		printf("cx_name: %s\n", data->cx_name);
		printf("o_ship_type: %s\n", data->o_ship_type);
		printf("shipping.addr_street1: %s\n", data->shipping.addr_street1);
		printf("shipping.addr_street2: %s\n", data->shipping.addr_street2);
		printf("shipping.addr_city: %s\n", data->shipping.addr_city);
		printf("shipping.addr_state: %s\n", data->shipping.addr_state);
		printf("shipping.addr_zip: %s\n", data->shipping.addr_zip);
		printf("shipping.co_name: %s\n", data->shipping.co_name);
	}
	else if (inout == DISPLAY_OUTPUT_DATA)
	{
		printf("c_discount %f\n", data->c_discount);
		printf("sc_sub_total %f\n", data->sc_sub_total);
		printf("sc_tax %f\n", data->sc_tax);
		printf("sc_ship_cost %f\n", data->sc_ship_cost);
		printf("sc_total %f\n", data->sc_total);
		printf("got %d items in shopping cart\n", data->sc_size);
		for (i = 0; i < data->sc_size; i++)
		{
			printf("scl_i_id%d: %lld\n", i, data->scl_data[i].scl_i_id);
			printf("scl_qty%d: %d\n", i, data->scl_data[i].scl_qty);
			printf("scl_cost%d: %f\n", i, data->scl_data[i].scl_cost);
			printf("scl_srp%d: %f\n", i, data->scl_data[i].scl_srp);
			printf("scl_title%d: %s\n", i, data->scl_data[i].i_title);
			printf("scl_backing%d: %s\n", i, data->scl_data[i].i_backing);
		}
	}
	return 1;
}

int display_buy_request_data(int inout, struct buy_request_t *data)
{
	int i;

	if (inout == DISPLAY_INPUT_DATA)
	{
		printf("returning_flag: %d\n", data->returning_flag);
		/* if it is old customer */
		if (data->returning_flag)
		{
			printf("c_uname: %s\n", data->c_uname);
			printf("c_passwd: %s\n", data->c_passwd);
			printf("sc_id: %lld\n", data->sc_id);
		}
		/* new user */
		else
		{
			printf("sc_id: %lld\n", data->sc_id);
			printf("c_fname: %s\n", data->c_fname);
			printf("c_lname: %s\n", data->c_lname);
			printf("address.street1: %s\n", data->address.addr_street1);
			printf("address.street2: %s\n", data->address.addr_street2);
			printf("address.city: %s\n", data->address.addr_city);
			printf("address.state: %s\n", data->address.addr_state);
			printf("address.zip: %s\n", data->address.addr_zip);
			printf("address.co_name: %s\n", data->address.co_name);
			printf("c_phone %s\n", data->c_phone);
			printf("c_email %s\n", data->c_email);
			printf("c_birthdate %s\n", data->c_birthdate);
			printf("c_data %s\n", data->c_data);
		}
	}
	else if (inout == DISPLAY_OUTPUT_DATA)
	{
		printf("c_fname: %s\n", data->c_fname);
		printf("c_lname: %s\n", data->c_lname);
		printf("addr_street1: %s\n", data->address.addr_street1);
		printf("addr_street2: %s\n", data->address.addr_street2);
		printf("addr_city: %s\n", data->address.addr_city);
		printf("addr_state: %s\n", data->address.addr_state);
		printf("addr_zip: %s\n", data->address.addr_zip);
		printf("co_name: %s\n", data->address.co_name);
		printf("c_phone: %s\n", data->c_phone);
		printf("c_email: %s\n", data->c_email);
		printf("c_birthdate: %s\n", data->c_birthdate);
		printf("c_data: %s\n", data->c_data);
		printf("c_id: %lld\n", data->c_id);
		printf("c_discount: %f\n", data->c_discount);
		printf("sc_sub_total: %f\n", data->sc_sub_total);
		printf("sc_tax: %0.2f\n", data->sc_tax);
		printf("sc_ship_cost: %0.2f\n", data->sc_ship_cost);
		printf("sc_total: %0.2f\n", data->sc_total);
		printf("\n");
		printf("%d items in the shopping cart:\n", data->sc_size);
		printf("\n");
		printf("%2s %-10s %-7s %-8s %-7s %-60s %-15s\n", "#",
			"scl_i_id", "scl_qty", "scl_cost", "scl_srp", "i_title",
			"i_backing");
		printf("%2s %-10s %-7s %-8s %-7s %-60s %-15s\n", "--",
			"-----", "-----", "-----", "-----", "-----", "-----");
		for (i = 0; i < data->sc_size; i++)
		{
			printf("%2d %10lld %7d %8.2f %7.2f %-60s %-15s\n", i,
				data->scl_data[i].scl_i_id, data->scl_data[i].scl_qty,
				data->scl_data[i].scl_cost, data->scl_data[i].scl_srp,
				data->scl_data[i].i_title, data->scl_data[i].i_backing);
		}
	}
	return 1;
}

int display_home_data(int inout, struct home_t *data)
{
	int i;

	if (inout == DISPLAY_INPUT_DATA)
	{
		printf("c_id: %lld\n", data->c_id);
	}
	else if (inout == DISPLAY_OUTPUT_DATA)
	{
		printf("c_fname: %s\n", data->c_fname);
		printf("c_lname: %s\n", data->c_lname);
		printf("\n");
		printf(" #  i_related i_thumbnail\n");
		printf("-- ---------- -----------\n");
		for (i = 0; i < PROMOTIONAL_ITEMS_MAX; i++)
		{
			printf("%2i %10lld %11lld\n", i, data->pp_data.i_related[i],
				data->pp_data.i_thumbnail[i]);
		}
	}
	return 1;
}

int display_new_products_data(int inout, struct new_products_t *data)
{
	int i;

	if (inout == DISPLAY_INPUT_DATA)
	{
		printf("i_subject = %s\n", data->i_subject);
	}
	else if (inout == DISPLAY_OUTPUT_DATA)
	{
		printf("\n");
		printf(" #  i_related i_thumbnail\n");
		printf("-- ---------- -----------\n");
		for (i = 0; i < PROMOTIONAL_ITEMS_MAX; i++)
		{
			printf("%2i %10lld %11lld\n", i, data->pp_data.i_related[i],
				data->pp_data.i_thumbnail[i]);
		}
		printf("\n");
		printf("%d item(s) returned:\n", data->items);
		printf("\n");
		printf("%2s %-10s %-60s %-20s %-20s\n", "#", "i_id", "i_title",
			"a_fname", "a_lname");
		printf("%2s %-10s %-60s %-20s %-20s\n", "--", "-----", "-----",
			"-----", "-----");
		for (i = 0; i < data->items; i++)
		{
			printf("%2d %10lld %-60s %-20s %-20s\n", i,
				data->results_data[i].i_id, data->results_data[i].i_title,
				data->results_data[i].a_fname, data->results_data[i].a_lname);
		}
	}
	return 1;
}

int display_order_display_data(int inout, struct order_display_t *data)
{
	int i;

	if (inout == DISPLAY_INPUT_DATA)
	{
		printf("c_uname: %s\n", data->c_uname);
		printf("c_passwd: %s\n", data->c_passwd);
	}
	else if (inout == DISPLAY_OUTPUT_DATA)
	{
		printf("o_id: %lld\n", data->o_id);
		printf("c_fname: %s\n", data->c_fname);
		printf("c_lname: %s\n", data->c_lname);
		printf("c_phone: %s\n", data->c_phone);
		printf("c_email: %s\n", data->c_email);
		printf("o_date: %s\n", data->o_date);
		printf("o_sub_total: %0.2f\n", data->o_sub_total);
		printf("o_tax: %0.2f\n", data->o_tax);
		printf("o_total: %0.2f\n", data->o_total);
		printf("o_ship_type: %s\n", data->o_ship_type);
		printf("o_ship_date: %s\n", data->o_ship_date);
		printf("o_status: %s\n", data->o_status);
		printf("\n");
		printf("bill_addr_street1: %s\n", data->billing.addr_street1);
		printf("bill_addr_street2: %s\n", data->billing.addr_street2);
		printf("bill_addr_city: %s\n", data->billing.addr_city);
		printf("bill_addr_state: %s\n", data->billing.addr_state);
		printf("bill_addr_zip: %s\n", data->billing.addr_zip);
		printf("bill_co_name: %s\n", data->billing.co_name);
		printf("\n");
		printf("ship_addr_street1: %s\n", data->shipping.addr_street1);
		printf("ship_addr_street2: %s\n", data->shipping.addr_street2);
		printf("ship_addr_city: %s\n", data->shipping.addr_city);
		printf("ship_addr_state: %s\n", data->shipping.addr_state);
		printf("ship_addr_zip: %s\n", data->shipping.addr_zip);
		printf("ship_co_name: %s\n", data->shipping.co_name);
		printf("\n");
		printf("cx_type: %s\n", data->cx_type);
		printf("cx_auth_id: %s\n", data->cx_auth_id);
		printf("\n");
		printf("%d items in the order:\n", data->items);
		printf("%2s %-10s %-60s %-60s %-7s %-6s %-11s %-100s\n", "#", "ol_i_id",
			"i_title", "i_publisher", "i_cost", "ol_qty", "ol_discount",
			"ol_comment");
		printf("%2s %-10s %-60s %-60s %-7s %-6s %-11s %-100s\n", "--", "-----",
			"-----", "-----", "-----", "-----", "-----", "-----");
		for (i = 0; i < data->items; i++)
		{
			printf("%2d %10lld %-60s %-60s %7.2f %6d %11.2f %-100s\n", i,
				data->odl_data[i].ol_i_id, data->odl_data[i].i_title,
				data->odl_data[i].i_publisher, data->odl_data[i].i_cost,
				data->odl_data[i].ol_qty, data->odl_data[i].ol_discount,
				data->odl_data[i].ol_comment);
		}
	}
	return 1;
}

int display_order_inquiry_data(int inout, struct order_inquiry_t *data)
{
	if (inout == DISPLAY_INPUT_DATA)
	{
		printf("c_id: %lld\n", data->c_id);
	}
	else if (inout == DISPLAY_OUTPUT_DATA)
	{
		printf("c_uname: %s\n", data->c_uname);	
	}
	return 1;
}

int display_product_detail_data(int inout, struct product_detail_t *data)
{
	if (inout == DISPLAY_INPUT_DATA)
	{
		printf("i_id: %lld\n", data->i_id);
	}
	else if (inout == DISPLAY_OUTPUT_DATA)
	{
		printf("i_title: %s\n", data->i_title);
		printf("a_fname: %s\n", data->a_fname);
		printf("a_lname: %s\n", data->a_lname);
		printf("i_pub_date: %s\n", data->i_pub_date);
		printf("i_publisher: %s\n", data->i_publisher);
		printf("i_subject: %s\n", data->i_subject);
		printf("i_desc: %s\n", data->i_desc);
		printf("i_image: %lld\n", data->i_image);
		printf("i_cost: %0.2f\n", data->i_cost);
		printf("i_srp: %0.2f\n", data->i_srp);
		printf("i_avail: %s\n", data->i_avail);
		printf("i_isbn: %s\n", data->i_isbn);
		printf("i_page: %d\n", data->i_page);
		printf("i_backing: %s\n", data->i_backing);
		printf("i_dimensions: %s\n", data->i_dimensions);
	}
	return 1;
}

int display_search_request_data(int inout, struct search_request_t *data)
{
	int i;

	if (inout == DISPLAY_INPUT_DATA)
	{
	}
	else if (inout == DISPLAY_OUTPUT_DATA)
	{
		printf("\n");
		printf(" #  i_related i_thumbnail\n");
		printf("-- ---------- -----------\n");
		for (i = 0; i < PROMOTIONAL_ITEMS_MAX; i++)
		{
			printf("%2i %10lld %11lld\n", i, data->pp_data.i_related[i],
				data->pp_data.i_thumbnail[i]);
		}
	}
	return 1;
}

int display_search_results_data(int inout, struct search_results_t *data)
{
	int i;

	if (inout == DISPLAY_INPUT_DATA)
	{
		printf("search_type: %d\n", data->search_type);
		printf("search_string: %s\n", data->search_string);
	}
	else if (inout == DISPLAY_OUTPUT_DATA)
	{
		printf("\n");
		printf(" #  i_related i_thumbnail\n");
		printf("-- ---------- -----------\n");
		for (i = 0; i < PROMOTIONAL_ITEMS_MAX; i++)
		{
			printf("%2i %10lld %11lld\n", i, data->pp_data.i_related[i],
				data->pp_data.i_thumbnail[i]);
		}
		printf("\n");
		printf("%d item(s) returned:\n", data->items);
		printf("\n");
		printf("%2s %-10s %-60s %-20s %-20s\n", "#", "i_id", "i_title",
			"a_fname", "a_lname");
		printf("%2s %-10s %-60s %-20s %-20s\n", "--", "-----", "-----",
			"-----", "-----");
		for (i = 0; i < data->items; i++)
		{
			printf("%2d %10lld %-60s %-20s %-20s\n", i,
				data->results_data[i].i_id, data->results_data[i].i_title,
				data->results_data[i].a_fname, data->results_data[i].a_lname);
		}
	}
	return 1;
}

int display_shopping_cart_data(int inout, struct shopping_cart_t *data)
{
	int i;

	if (inout == DISPLAY_INPUT_DATA)
	{
		printf("sc_id is %lld\n", data->sc_id);
		printf("c_id is %lld\n", data->c_id);
	}
	else if (inout == DISPLAY_OUTPUT_DATA)
	{
		printf("sc_id is %lld\n", data->sc_id);
		printf("\n");
		printf(" #  i_related i_thumbnail\n");
		printf("-- ---------- -----------\n");
		for (i = 0; i < PROMOTIONAL_ITEMS_MAX; i++)
		{
			printf("%2i %10lld %11lld\n", i, data->pp_data.i_related[i],
				data->pp_data.i_thumbnail[i]);
		}
		printf("\n");
		printf("%d items in the shopping cart:\n", data->sc_size);
		printf("\n");
		printf("%2s %-10s %-7s %-8s %-7s %-60s %-15s\n", "#",
			"scl_i_id", "scl_qty", "scl_cost", "scl_srp", "i_title",
			"i_backing");
		printf("%2s %-10s %-7s %-8s %-7s %-60s %-15s\n", "--",
			"-----", "-----", "-----", "-----", "-----", "-----");
		for (i = 0; i < data->sc_size; i++)
		{
			printf("%2d %10lld %7d %8.2f %7.2f %-60s %-15s\n", i,
				data->scl_data[i].scl_i_id, data->scl_data[i].scl_qty,
				data->scl_data[i].scl_cost, data->scl_data[i].scl_srp,
				data->scl_data[i].i_title, data->scl_data[i].i_backing);
		}
	}
	return 1;
}

int generate_input_data(int interaction, void *data)
{
	printf("Generating input data for %s...\n", interaction_name[interaction]);
	switch (interaction)
	{
		case ADMIN_CONFIRM:
			generate_admin_confirm_data((struct admin_confirm_t *) data);
			break;
		case ADMIN_REQUEST:
			generate_admin_request_data((struct admin_request_t *) data);
			break;
		case BEST_SELLERS:
			generate_best_sellers_data((struct best_sellers_t *) data);
			break;
		case BUY_CONFIRM:
			generate_buy_confirm_data((struct buy_confirm_t *) data);
			break;
		case BUY_REQUEST:
			generate_buy_request_data((struct buy_request_t *) data);
			break;
		case HOME:
			generate_home_data((struct home_t *) data);
			break;
		case NEW_PRODUCTS:
			generate_new_products_data((struct new_products_t *) data);
			break;
		case ORDER_DISPLAY:
			generate_order_display_data((struct order_display_t *) data);
			break;
		case ORDER_INQUIRY:
			generate_order_inquiry_data((struct order_inquiry_t *) data);
			break;
		case PRODUCT_DETAIL:
			generate_product_detail_data((struct product_detail_t *) data);
			break;
		case SEARCH_REQUEST:
			break;
		case SEARCH_RESULTS:
			generate_search_results_data((struct search_results_t *) data);
			break;
		case SHOPPING_CART:
			generate_shopping_cart_data((struct shopping_cart_t *) data);
			break;
		default:
			printf("unknown interaction %d\n", interaction);
			exit(1);
	}
	return 1;
}

int generate_admin_confirm_data(struct admin_confirm_t *data)
{
	data->i_id = i_id;
	data->i_image = 11;
	data->i_thumbnail = 111;
	data->i_cost = 12.34;
	return 1;
}

int generate_admin_request_data(struct admin_request_t *data)
{
	data->i_id = i_id;
	return 1;
}

int generate_best_sellers_data(struct best_sellers_t *data)
{
	strcpy(data->i_subject, subject);
	return 1;
}

int generate_buy_confirm_data(struct buy_confirm_t *data)
{
	data->sc_id = sc_id;
	data->c_id = c_id;
	if (ship_to_billing)
	{
		strcpy(data->shipping.addr_street1, "");
		strcpy(data->shipping.addr_street2, "");
		strcpy(data->shipping.addr_city, "");
		strcpy(data->shipping.addr_state, "");
		strcpy(data->shipping.addr_zip, "");
		strcpy(data->shipping.co_name, "");
	}
	else
	{
		strcpy(data->shipping.addr_street1, "st1");
		strcpy(data->shipping.addr_street2, "st2");
		strcpy(data->shipping.addr_city, "beaverton");
		strcpy(data->shipping.addr_state, "OR");
		strcpy(data->shipping.addr_zip, "97006");
		strcpy(data->shipping.co_name, "United States");
	}
	strcpy(data->cx_type, "VISA");
	strcpy(data->cx_num, "1234567890123456");
	strcpy(data->cx_expiry, "20030202");
	strcpy(data->o_ship_type, "AIR");
	strcpy(data->cx_name, "first last");

	return 1;
}

int generate_buy_request_data(struct buy_request_t *data)
{
	data->sc_id = sc_id;
	if (new_customer)
	{
		data->returning_flag = 0;

		strcpy(data->c_fname, "osdl");
		strcpy(data->c_lname, "losdl");
		strcpy(data->address.addr_street1, "st1");
		strcpy(data->address.addr_street2, "st2");
		strcpy(data->address.addr_city, "beaverton");
		strcpy(data->address.addr_state, "OR");
		strcpy(data->address.addr_zip, "97006");
		strcpy(data->address.co_name, "United States");
		strcpy(data->c_phone, "5034444444");
		strcpy(data->c_email, "mail@osdl.org");
		strcpy(data->c_birthdate, "19701020");
		strcpy(data->c_data, "open source.org");
	}
	else
	{
		data->returning_flag = 1;

		strcpy(data->c_uname, c_uname);
		strcpy(data->c_passwd, c_passwd);
	}
	return 1;
}

int generate_home_data(struct home_t *data)
{
	data->c_id = c_id;
	return 1;
}

int generate_new_products_data(struct new_products_t *data)
{
	strcpy(data->i_subject, subject);
	return 1;
}

int generate_order_display_data(struct order_display_t *data)
{
	strcpy(data->c_uname, c_uname);
	strcpy(data->c_passwd, c_passwd);
	return 1;
}

int generate_order_inquiry_data(struct order_inquiry_t *data)
{
	data->c_id = c_id;
	return 1;
}

int generate_product_detail_data(struct product_detail_t *data)
{
	data->i_id = i_id;
	return 1;
}

int generate_search_results_data(struct search_results_t *data)
{
	data->search_type = search;
	strcpy(data->search_string, subject);
	return 1;
}

int generate_shopping_cart_data(struct shopping_cart_t *data)
{
	int i;
	data->sc_id = sc_id;
	data->c_id = c_id;
	switch(cart_mode)
	{
		case 0:
			/* add_flag=0, and empty pair, add a random item */
			printf("viewing shopping cart for the first time\n");
			data->add_flag = 0;
			data->sc_size = 0;
			/* sc_id must not be > 0 else this case will fail. */
			data->sc_id = sc_id;
			break;
		case 1:
			/* add_flag=1, add an item to shopping_cart */
			printf("add an item to shopping_cart\n");
			data->add_flag = 1;
			data->i_id = 1;
			data->sc_size = 1;
			break;
		case 2:
			/* add_flag=0, with pair, refresh shopping cart */
			printf("refresh shopping_cart\n");
			data->add_flag = 0;
			data->sc_size = 2;
			for (i = 0; i < SHOPPING_CART_ITEMS_MAX; i++)
			{
			 	data->sc_refresh[i].scl_i_id = 0;
			 	data->sc_refresh[i].scl_qty = 0;
			}
			data->sc_refresh[0].scl_i_id = 443;
			data->sc_refresh[0].scl_qty = 0;
			data->sc_refresh[1].scl_i_id = 1;
			data->sc_refresh[1].scl_qty = 4;
			break;
		default:
			printf("unknown case\n");
			return 11;
	}
	return 1;
}

int usage(char *name)
{
	int i;

	printf(
		"to use the application server:\n"
		"usage: %s --dbhost <servername> --port <port>\n"
		"	--interaction <interaction>\n\n", name);
	printf(
		"to connect to the database directly without using cache:\n"
		"usage: %s --access_direct --dbhost <dbhost>\n"
		"	--interaction <interaction>\n\n", name);
	printf(
		"to connect to the database directly with using cache:\n"
		"usage: %s --access_direct --dbhost <dbhost> --access_cache\n"
		"	--cache_host <cachehost> --cache_port <cache_port>\n"
		"	--interaction <interaction>\n\n", name);
	printf("  <interaction>:  ac  - Admin Confirm\n");
	printf("                        [--i_id <#>], default 1\n");
	printf("                  ar  - Admin Request\n");
	printf("                        [--i_id <#>], default 1\n");
	printf("                  bs  - Best Sellers\n");
	printf("                        [--subject <i_subject>], default ARTS\n");
	printf("                  bc  - Buy Confirm\n");
	printf("                        [--ship_to_billing]\n");
	printf("                        [--c_id <#>], default 1\n");
	printf("                        [--sc_id <#>], default 1\n");
	printf("                  br  - Buy Request\n");
	printf("                        [--new_customer [--sc_id <#>], default 1]\n");
	printf("                        or\n");
	printf("                        [[--c_uname] <c_uname>], default OG\n");
	printf("                         [--c_passwd] <c_passwd>], default og [--sc_id <#>]]\n");
	printf("                  ho  - Home\n");
	printf("                        [--c_id <#>], default 1\n");
	printf("                  np  - New Products\n");
	printf("                        [--subject <i_subject>], default ARTS\n");
	printf("                  od  - Order Display\n");
	printf("                        [--c_uname] <c_uname>, default OG\n");
	printf("                        [--c_passwd] <c_passwd>, default og\n");
	printf("                  oi  - Order Inquiry\n");
	printf("                        [--c_id <#>], default 1\n");
	printf("                  pd  - Product Display\n");
	printf("                        [--i_id <#>], default 1\n");
	printf("                  sr  - Search Request\n");
	printf("                  su  - Search Results\n");
	printf("                        [--search_by_author or --search_by_subject\n");
	printf("                         or --search_by_title]\n");
	printf("                        [--subject <search_string>], default ARTS\n");
	printf("                  sc  - Shopping Cart\n");
	printf("                        [--view_cart or --add_item or --update_cart],\n");
	printf("                         default --view_cart\n");
	printf("                        [--c_id <#>], default 1\n");
	printf("                        [--sc_id <#>], default 1\n");
	printf("\n");
	printf("  <i_subject>:\n");
	for (i = 0; i < I_SUBJECT_MAX; i++)
	{
		printf("                  %s\n", i_subject[i]);
	}
	return 1;
}
