/*
 * eu.c
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2002 Mark Wong & Jenny Zhang &
 *                    Open Source Development Lab, Inc.
 *
 * 30 january 2002
 * Based on TPC-W v1.6
 */

#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <math.h>
#include <eu.h>
#include <common.h>
#include <cache.h>

#ifdef PHASE1
#include <odbc_interaction.h>
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
#endif /* PHASE1 */

#include <_socket.h>
#ifdef PHASE2
#include <tm_interface.h>
#endif /* PHASE2 */

/* Defined some log file names. */
#define MIX_LOG_NAME "mix.log"
#define THINK_TIME_LOG_NAME "think_time.log"
#define USMD_LOG_NAME "usmd.log"

/* 15 minutes in milliseconds */
#define USMD_MEAN 900000.0

/* Prototypes */

int do_interaction(struct eu_context_t *euc);

int get_next_interaction(int prev_interaction);
int get_think_time();
double get_usmd();

void init_browsing_mix();
void init_ordering_mix();
void init_shopping_mix();

int dump_interaction_data(struct eu_context_t *euc);
int prepare_admin_confirm(struct eu_context_t *euc);
int prepare_admin_request(struct eu_context_t *euc);
int prepare_best_sellers(struct eu_context_t *euc);
int prepare_buy_confirm(struct eu_context_t *euc);
int prepare_buy_request(struct eu_context_t *euc);
int prepare_home(struct eu_context_t *euc);
int prepare_new_products(struct eu_context_t *euc);
int prepare_order_display(struct eu_context_t *euc);
int prepare_order_inquiry(struct eu_context_t *euc);
int prepare_product_detail(struct eu_context_t *euc);
int prepare_search_results(struct eu_context_t *euc);
int prepare_shopping_cart(struct eu_context_t *euc);

void *start_eu(void *data);

#ifdef DEBUG
int dump_interaction_output(struct eu_context_t *euc);
#endif /* DEBUG */

sem_t running_eu_count;

int customers;
int a;

time_t stop_time;
double think_time_mean;

const char *interaction_short_name[INTERACTION_TOTAL] =
{
	"AC", "AR", "BS", "BC", "BR", "CR", "HO", "NP", "OD", "OI", "PD", "SR",
	"SU", "SC"
};

int mix_matrix[INTERACTION_TOTAL][INTERACTION_TOTAL];

/* Log Files */

FILE *log_mix;
FILE *log_think_time;
FILE *log_usmd;

/* Log Files Mutuexes */

pthread_mutex_t mutex_mix_log = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_think_time_log = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_usmd_log = PTHREAD_MUTEX_INITIALIZER;

#ifdef RUNTIME_STATS
/* Run-time Statistics */

int interaction_count[INTERACTION_TOTAL];
double cumulative_response_time[INTERACTION_TOTAL];

pthread_mutex_t mutex_stats[INTERACTION_TOTAL]; 
#endif /* RUNTIME_STATS */

#ifdef PHASE2
/* IP or hostname of the middle tier system. */
char tm_address[32];
#endif /* PHASE2 */

#ifdef PHASE1
char cache_host[32];
int cache_port;
#endif

/*
 * Generate input data and request an interaction to be executed.
 */
int do_interaction(struct eu_context_t *euc)
{
	int rc = W_OK;

#ifdef PHASE1
	/*
	 * Zero out the memory because of union odbc_data_t to prevent data
	 * overflow from lingering data when the stored procedure is called.
     */
	bzero(&euc->odbcd, sizeof(union odbc_data_t));
#endif /* PHASE1 */

	/* Call the appropriate function to generate the input data. */
	switch (euc->interaction)
	{
		case ADMIN_CONFIRM:
			prepare_admin_confirm(euc);
#ifdef PHASE1
			rc = copy_in_admin_confirm(euc, &euc->odbcd);
			if (rc != W_OK)
			{
				return W_ERROR;
			}
			rc = execute_admin_confirm(&euc->odbcc, &euc->odbcd);
			if (rc != W_OK)
			{
				return W_ERROR;
			}
			copy_out_admin_confirm(euc, &euc->odbcd);
#endif /* PHASE1 */
			break;
		case ADMIN_REQUEST:
			prepare_admin_request(euc);
#ifdef PHASE1
			rc = copy_in_admin_request(euc, &euc->odbcd);
			if (rc != W_OK)
			{
				return W_ERROR;
			}
			rc = execute_admin_request(&euc->odbcc, &euc->odbcd);
			if (rc == W_OK)
			{
				copy_out_admin_request(euc, &euc->odbcd);
			}
#endif /* PHASE1 */
			break;
		case BEST_SELLERS:
			prepare_best_sellers(euc);
#ifdef PHASE1
			copy_in_best_sellers(euc, &euc->odbcd);
			rc = execute_best_sellers(&euc->odbcc, &euc->odbcd);
			switch (rc)
			{
				case W_ZERO_ITEMS:
					LOG_ERROR_MESSAGE("%s returned %d items for %s.\n",
						interaction_short_name[euc->interaction],
						euc->best_sellers_data.items,
						euc->best_sellers_data.i_subject);
				case W_ERROR:
					return W_ERROR;
			}
			copy_out_best_sellers(euc, &euc->odbcd);
#endif /* PHASE1 */
			break;
		case BUY_CONFIRM:
			prepare_buy_confirm(euc);
#ifdef PHASE1
			copy_in_buy_confirm(euc, &euc->odbcd);
			rc = execute_buy_confirm(&euc->odbcc, &euc->odbcd);
			if (rc == W_OK)
			{
				copy_out_buy_confirm(euc, &euc->odbcd);
			}
			euc->sc_id = UNKNOWN_SHOPPING_CART;
#endif /* PHASE1 */
			break;
		case BUY_REQUEST:
			prepare_buy_request(euc);
#ifdef PHASE1
			copy_in_buy_request(euc, &euc->odbcd);
			rc = execute_buy_request(&euc->odbcc, &euc->odbcd);
			if (rc == W_OK)
			{
				copy_out_buy_request(euc, &euc->odbcd);
			}
			euc->c_id = euc->buy_request_data.c_id;
#endif /* PHASE1 */
			break;
		case CUSTOMER_REGISTRATION:
			/*
			 * This isn't a database interaction so we can just return at this
			 * point.
			 */
			return W_OK;
		case HOME:
			rc = prepare_home(euc);
			if (rc != W_OK)
			{
				return W_ERROR;
			}
#ifdef PHASE1
			copy_in_home(euc, &euc->odbcd);
			rc = execute_home(&euc->odbcc, &euc->odbcd);
			if (rc == W_OK)
			{
				copy_out_home(euc, &euc->odbcd);
			}
#endif /* PHASE1 */
			break;
		case NEW_PRODUCTS:
			prepare_new_products(euc);
#ifdef PHASE1
			copy_in_new_products(euc, &euc->odbcd);
			rc = execute_new_products(&euc->odbcc, &euc->odbcd);
			switch (rc)
			{
				case W_ZERO_ITEMS:
					LOG_ERROR_MESSAGE("%s returned %d items for %s.\n",
						interaction_short_name[euc->interaction],
						euc->new_products_data.items,
						euc->new_products_data.i_subject);
				case W_ERROR:
					return W_ERROR;
			}
			copy_out_new_products(euc, &euc->odbcd);
#endif /* PHASE1 */
			break;
		case ORDER_DISPLAY:
			rc = prepare_order_display(euc);
			if (rc != W_OK)
			{
				return W_ERROR;
			}
#ifdef PHASE1
			copy_in_order_display(euc, &euc->odbcd);
			rc = execute_order_display(&euc->odbcc, &euc->odbcd);
			if (rc == W_OK)
			{
				copy_out_order_display(euc, &euc->odbcd);
			}
#endif /* PHASE1 */
			break;
		case ORDER_INQUIRY:
			if (euc->c_id == UNKNOWN_CUSTOMER)
			{
				return W_OK;
			}
			prepare_order_inquiry(euc);
#ifdef PHASE1
			copy_in_order_inquiry(euc, &euc->odbcd);
			rc = execute_order_inquiry(&euc->odbcc, &euc->odbcd);
			if (rc == W_OK)
			{
				copy_out_order_inquiry(euc, &euc->odbcd);
			}
#endif /* PHASE1 */
			break;
		case PRODUCT_DETAIL:
			rc = prepare_product_detail(euc);
/*
#ifdef DEBUG
			DEBUGMSG("product detail id %lld", euc->product_detail_data.i_id);
#endif
*/
			if (rc != W_OK)
			{
				return W_ERROR;
			}
#ifdef PHASE1
			copy_in_product_detail(euc, &euc->odbcd);
			rc = execute_product_detail(&euc->odbcc, &euc->odbcd);
			if (rc == W_OK)
			{
				copy_out_product_detail(euc, &euc->odbcd);
			}
#endif /* PHASE1 */
			break;
		case SEARCH_REQUEST:
#ifdef PHASE1
			rc = execute_search_request(euc, &euc->odbcd);
			if (rc == W_OK)
			{
				copy_out_search_request(euc, &euc->odbcd);
			}
#endif /* PHASE1 */
			break;
		case SEARCH_RESULTS:
			rc = prepare_search_results(euc);
			if (rc != W_OK)
			{
				return W_ERROR;
			}
#ifdef PHASE1
#ifdef SEARCH_RESULTS_CACHE
			if (euc->search_results_data.search_type != SEARCH_SUBJECT)
			{
				rc = send_search_results(euc->cache_s, &euc->search_results_data);
				/* if send fails, reopen a new socket */
				if (rc!=W_OK)
				{
					LOG_ERROR_MESSAGE("send search_results to cache host failed");
					close(euc->cache_s);
					euc->cache_s=_connect(cache_host, cache_port);
					if (euc->cache_s==-1)
					{
						LOG_ERROR_MESSAGE("connect to cache failed\n");
						return W_ERROR;
					}
					return W_ERROR;
				}
				rc = receive_search_results(euc->cache_s, &euc->search_results_data);
				if (rc!=W_OK)
				{
					LOG_ERROR_MESSAGE("receive search_results from cache host failed");
					close(euc->cache_s);
					euc->cache_s=_connect(cache_host, cache_port);
					if (euc->cache_s==-1)
					{
						LOG_ERROR_MESSAGE("connect to cache failed\n");
						return W_ERROR;
					}
					return W_ERROR;
				}
/*
				if (rc==0)
				{
					LOG_ERROR_MESSAGE("cache host closed socket");
					return SOCKET_CLOSE;
				}
*/
			}
			else
			{
				copy_in_search_results(euc, &euc->odbcd);
				rc = execute_search_results(&euc->odbcc, &euc->odbcd);
				if (rc == W_OK)
				{
					copy_out_search_results(euc, &euc->odbcd);
				}
			}
#else
			copy_in_search_results(euc, &euc->odbcd);
			rc = execute_search_results(&euc->odbcc, &euc->odbcd);
			if (rc == W_OK)
			{
				copy_out_search_results(euc, &euc->odbcd);
			}
#endif /*SEARCH_RESULTS_CACHE*/
#endif /* PHASE1 */
			break;
		case SHOPPING_CART:
			prepare_shopping_cart(euc);
#ifdef PHASE1
			copy_in_shopping_cart(euc, &euc->odbcd);
			rc = execute_shopping_cart(&euc->odbcc, &euc->odbcd);
			if (rc == W_OK)
			{
				copy_out_shopping_cart(euc, &euc->odbcd);
			}
			euc->sc_id = euc->shopping_cart_data.sc_id;
#endif /* PHASE1 */
			break;
		default:
			LOG_ERROR_MESSAGE("unknown interaction %d\n", euc->interaction);
			rc = W_ERROR;
			break;
	}
#ifdef PHASE2
	/* Send and receive data to the middle tier program. */
	if (send_interaction_packet(euc->s, euc) == W_ERROR)
	{
		LOG_ERROR_MESSAGE("send failed");
		return W_ERROR;
	}
	if ( (rc=receive_interaction_packet(euc->s, euc)) == W_ERROR)
	{
		LOG_ERROR_MESSAGE("receive failed");
		return W_ERROR;
	}
	if (rc==SOCKET_CLOSE)
	{
		LOG_ERROR_MESSAGE("appServer socket closed");
		return SOCKET_CLOSE;
	}

	if (euc->interaction == SHOPPING_CART) 
	{
		euc->sc_id = euc->shopping_cart_data.sc_id;
	}
	else if (euc->interaction == BUY_REQUEST) 
		euc->c_id = euc->buy_request_data.c_id;
	/* reset sc_id after buy_confirm */
	else if (euc->interaction == BUY_CONFIRM) 
		euc->sc_id = UNKNOWN_SHOPPING_CART;
//#ifdef DEBUG
//	dump_interaction_output(euc);
//#endif /* DEBUG */
#endif /* PHASE2 */

	return rc;
}

#ifdef DEBUG
/*
 * Dump the interaction output for debugging purposes only.
 */
int dump_interaction_output(struct eu_context_t *euc)
{
	int i;
	DEBUGMSG("dumping %s interaction output, c_id %lld, sc_id %lld",
		interaction_short_name[euc->interaction],
		euc->c_id,
		euc->sc_id);
	switch (euc->interaction)
	{
		case ADMIN_CONFIRM:
			DEBUGMSG("i_title %s, a_fname %s, a_lname %s, i_subject %s, i_desc %s, i_srp %0.2f, i_backing %s, i_page %d, i_publisher %s, i_pub_date %s, i_dimensions %s, i_isbn %s",
				euc->admin_confirm_data.i_title,
				euc->admin_confirm_data.a_fname,
				euc->admin_confirm_data.a_lname,
				euc->admin_confirm_data.i_subject,
				euc->admin_confirm_data.i_desc,
				euc->admin_confirm_data.i_srp,
				euc->admin_confirm_data.i_backing,
				euc->admin_confirm_data.i_page,
				euc->admin_confirm_data.i_publisher,
				euc->admin_confirm_data.i_pub_date,
				euc->admin_confirm_data.i_dimensions,
				euc->admin_confirm_data.i_isbn);
			break;
		case ADMIN_REQUEST:
			DEBUGMSG("i_title %s, a_fname %s, a_lname %s, i_srp %0.2f, i_cost %0.2f, i_image %lld, i_thumbnail %lld",
				euc->admin_request_data.i_title,
				euc->admin_request_data.a_fname,
				euc->admin_request_data.a_lname,
				euc->admin_request_data.i_srp,
				euc->admin_request_data.i_cost,
				euc->admin_request_data.i_image,
				euc->admin_request_data.i_thumbnail);
			break;
		case BEST_SELLERS:
			for (i=0; i < PROMOTIONAL_ITEMS_MAX; i++)
				DEBUGMSG("i_related%d: %lld, i_thumbnail%d: %lld",
					i,euc->best_sellers_data.pp_data.i_related[i],
					i,euc->best_sellers_data.pp_data.i_thumbnail[i]);
			DEBUGMSG("%d item(s) returned", euc->best_sellers_data.items);
			for (i = 0; i < euc->best_sellers_data.items; i++)
			{
				DEBUGMSG("item %d, i_id: %lld, i_title: %s, a_fname: %s, a_lname: %s", i, 
				euc->best_sellers_data.results_data[i].i_id, 
				euc->best_sellers_data.results_data[i].i_title,
				euc->best_sellers_data.results_data[i].a_fname,
				euc->best_sellers_data.results_data[i].a_lname);
			}
			break;
		case BUY_CONFIRM:
			DEBUGMSG("c_discount %0.2f, sc_sub_total %0.2f, sc_tax %0.2f, sc_ship_cost %0.2f, sc_total %0.2f", 
			euc->buy_confirm_data.c_discount,
			euc->buy_confirm_data.sc_sub_total,
			euc->buy_confirm_data.sc_tax,
			euc->buy_confirm_data.sc_ship_cost,
			euc->buy_confirm_data.sc_total);
			DEBUGMSG("got %d items in shopping cart", 
				euc->buy_confirm_data.sc_size);
			for (i = 0; i < euc->buy_confirm_data.sc_size; i++)
			{
				DEBUGMSG("item %d, scl_i_id: %lld, scl_qty: %d, scl_cost: %0.2f, scl_srp: %0.2f, scl_title: %s, scl_backing: %s", i,  
				euc->buy_confirm_data.scl_data[i].scl_i_id,
				euc->buy_confirm_data.scl_data[i].scl_qty,
				euc->buy_confirm_data.scl_data[i].scl_cost,
				euc->buy_confirm_data.scl_data[i].scl_srp,
				euc->buy_confirm_data.scl_data[i].i_title,
				euc->buy_confirm_data.scl_data[i].i_backing);
			}
			break;
		case BUY_REQUEST:
                	DEBUGMSG("c_fname %s, c_lname %s\n"
				"addr_st1 %s\n" 
				"addr_st2 %s\n"
				"addr_city %s, addr_state %s, addr_zip %s, co_name %s\n"
				"c_phone %s, c_email %s, c_birthdate\n"
				"c_data %s\n"
				"c_id %lld, c_discount %0.2f, sc_sub_total %0.2f, sc_tax %0.2f, sc_ship_cost %0.2f, sc_total %0.2f",
				euc->buy_request_data.c_fname, 
				euc->buy_request_data.c_lname,
				euc->buy_request_data.address.addr_street1,
				euc->buy_request_data.address.addr_street2,
				euc->buy_request_data.address.addr_city,
				euc->buy_request_data.address.addr_state,
				euc->buy_request_data.address.addr_zip,
				euc->buy_request_data.address.co_name,
				euc->buy_request_data.c_phone,
				euc->buy_request_data.c_email,
				euc->buy_request_data.c_birthdate,
				euc->buy_request_data.c_data,
				euc->buy_request_data.c_id,
				euc->buy_request_data.c_discount,
				euc->buy_request_data.sc_sub_total,
				euc->buy_request_data.sc_tax,
				euc->buy_request_data.sc_ship_cost,
				euc->buy_request_data.sc_total);
			DEBUGMSG("got %d items in shopping cart",
				euc->buy_request_data.sc_size);
			for (i = 0; i < euc->buy_request_data.sc_size; i++)
                	{
				DEBUGMSG("item %d, scl_i_id: %lld, scl_qty: %d, scl_cost: %0.2f, scl_srp %0.2f, scl_title: %s, scl_backing: %s", i,
				euc->buy_request_data.scl_data[i].scl_i_id,
				euc->buy_request_data.scl_data[i].scl_qty,
				euc->buy_request_data.scl_data[i].scl_cost,
				euc->buy_request_data.scl_data[i].scl_srp,
				euc->buy_request_data.scl_data[i].i_title,
				euc->buy_request_data.scl_data[i].i_backing);
			}
			break;
		case HOME:
			DEBUGMSG("c_fname: %s, c_lname: %s", 
				euc->home_data.c_fname,
				euc->home_data.c_lname);
			for (i=0; i < PROMOTIONAL_ITEMS_MAX; i++)
				DEBUGMSG("i_related%d: %lld, i_thumbnail%d: %lld",
					i,euc->home_data.pp_data.i_related[i],
					i,euc->home_data.pp_data.i_thumbnail[i]);
			break;
		case NEW_PRODUCTS:
			for (i=0; i < PROMOTIONAL_ITEMS_MAX; i++)
				DEBUGMSG("i_related%d: %lld, i_thumbnail%d: %lld",
					i,euc->new_products_data.pp_data.i_related[i],
					i,euc->new_products_data.pp_data.i_thumbnail[i]);
			DEBUGMSG("%d item(s) returned",
				euc->new_products_data.items);
			for (i = 0; i < euc->new_products_data.items; i++)
                	{
				DEBUGMSG("item %d, i_id: %lld, i_titel: %s, a_fname: %s, a_lname %s", i,
				euc->new_products_data.results_data[i].i_id,
				euc->new_products_data.results_data[i].i_title,
				euc->new_products_data.results_data[i].a_fname,
				euc->new_products_data.results_data[i].a_lname);
			}
			break;
		case ORDER_DISPLAY:
			DEBUGMSG("o_id: %lld, c_fname: %s, c_lname: %s, c_phone: %s, c_email: %s\n"
				"o_date: %s, o_sub_total: %0.2f, o_tax: %0.2f, o_total: %0.2f, o_ship_type, o_ship_date: %s, o_status: %s\n"
				"bill_addr_street1: %s\n"
				"bill_addr_street2: %s\n"
				"bill_addr_city: %s, bill_addr_state: %s, bill_addr_zip: %s, bill_co_name: %s\n"
				"ship_addr_street1: %s\n"
				"ship_addr_street2: %s\n"
				"ship_addr_city %s, ship_addr_state: %s, ship_addr_zip: %s, ship_co_name: %s",
				euc->order_display_data.o_id,
				euc->order_display_data.c_fname,
				euc->order_display_data.c_lname,
				euc->order_display_data.c_phone,
				euc->order_display_data.c_email,
				euc->order_display_data.o_date,
				euc->order_display_data.o_sub_total,
				euc->order_display_data.o_tax,
				euc->order_display_data.o_total,
				euc->order_display_data.o_ship_type,
				euc->order_display_data.o_ship_date,
				euc->order_display_data.o_status,
				euc->order_display_data.billing.addr_street1,
				euc->order_display_data.billing.addr_street2,
				euc->order_display_data.billing.addr_city,
				euc->order_display_data.billing.addr_state,
				euc->order_display_data.billing.addr_zip,
				euc->order_display_data.billing.co_name,
				euc->order_display_data.shipping.addr_street1,
				euc->order_display_data.shipping.addr_street2,
				euc->order_display_data.shipping.addr_city,
				euc->order_display_data.shipping.addr_state,
				euc->order_display_data.shipping.addr_zip,
				euc->order_display_data.shipping.co_name);
			DEBUGMSG("%d item(s) returned",
				euc->order_display_data.items);
			for (i = 0; i < euc->order_display_data.items; i++)
                	{
				DEBUGMSG("item %d, ol_i_id: %lld, i_titel: %s, i_publiser: %s, i_cost %0.2f, ol_qty %d, ol_discount %0.2f\n"
				"ol_comment %s", i,
				euc->order_display_data.odl_data[i].ol_i_id,
				euc->order_display_data.odl_data[i].i_title,
				euc->order_display_data.odl_data[i].i_publisher,
				euc->order_display_data.odl_data[i].i_cost,
				euc->order_display_data.odl_data[i].ol_qty,
				euc->order_display_data.odl_data[i].ol_discount,
				euc->order_display_data.odl_data[i].ol_comment);
			}
			break;	
		case ORDER_INQUIRY:
			DEBUGMSG("c_uname: %s", euc->order_inquiry_data.c_uname);
			break;
		case PRODUCT_DETAIL:
			DEBUGMSG("i_title %s, a_fname %s, a_lname %s, i_pub_date
%s, i_publisher %s, i_subject %s, i_desc %s, i_image %lld, i_cost %0.2f, i_srp %0.2f, i_avail %s, i_isbn %s, i_page %d, i_backing %s, i_dimensions %s",
				euc->product_detail_data.i_title,
				euc->product_detail_data.a_fname,
				euc->product_detail_data.a_lname,
				euc->product_detail_data.i_pub_date,
				euc->product_detail_data.i_publisher,
				euc->product_detail_data.i_subject,
				euc->product_detail_data.i_desc,
				euc->product_detail_data.i_image,
				euc->product_detail_data.i_cost,
				euc->product_detail_data.i_srp,
				euc->product_detail_data.i_avail,
				euc->product_detail_data.i_isbn,
				euc->product_detail_data.i_page,
				euc->product_detail_data.i_backing,
				euc->product_detail_data.i_dimensions);
			break;
		case SEARCH_REQUEST:
			for (i=0; i < PROMOTIONAL_ITEMS_MAX; i++)
				DEBUGMSG("i_related%d: %lld, i_thumbnail%d: %lld",
					i,euc->search_request_data.pp_data.i_related[i],
					i,euc->search_request_data.pp_data.i_thumbnail[i]);
			break;
		case SEARCH_RESULTS:
			for (i=0; i < PROMOTIONAL_ITEMS_MAX; i++)
				DEBUGMSG("i_related%d: %lld, i_thumbnail%d: %lld",
					i,euc->search_results_data.pp_data.i_related[i],
					i,euc->search_results_data.pp_data.i_thumbnail[i]);
			DEBUGMSG("%d item(s) returned",
				euc->search_results_data.items);
			for (i = 0; i < euc->search_results_data.items; i++)
                	{
				DEBUGMSG("item %d, i_id: %lld, i_titel: %s, a_fname: %s, a_lname %s", i,
				euc->search_results_data.results_data[i].i_id,
				euc->search_results_data.results_data[i].i_title,
				euc->search_results_data.results_data[i].a_fname,
				euc->search_results_data.results_data[i].a_lname);
			}
			break;
		case SHOPPING_CART:
			for (i=0; i < PROMOTIONAL_ITEMS_MAX; i++)
				DEBUGMSG("i_related%d: %lld, i_thumbnail%d: %lld",
					i,euc->shopping_cart_data.pp_data.i_related[i],
					i,euc->shopping_cart_data.pp_data.i_thumbnail[i]);
			DEBUGMSG("got %d items in shopping cart",
				euc->shopping_cart_data.sc_size);
			for (i = 0; i < euc->shopping_cart_data.sc_size; i++)
                	{
				DEBUGMSG("item %d, scl_i_id: %lld, scl_qty: %d, scl_cost: %0.2f, scl_srp %0.2f, scl_title: %s, scl_backing: %s", i,
				euc->shopping_cart_data.scl_data[i].scl_i_id,
				euc->shopping_cart_data.scl_data[i].scl_qty,
				euc->shopping_cart_data.scl_data[i].scl_cost,
				euc->shopping_cart_data.scl_data[i].scl_srp,
				euc->shopping_cart_data.scl_data[i].i_title,
				euc->shopping_cart_data.scl_data[i].i_backing);
			}
			break;
		default:
			LOG_ERROR_MESSAGE("unknown interaction %d", euc->interaction);
			break;
	}
	return W_OK;
}
#endif /* DEBUG */

/* 
 * Dump the input data in the euc variable to the error log.  The format of
 * the output could be improved...
 */
int dump_interaction_data(struct eu_context_t *euc)
{
	int i;
	LOG_ERROR_MESSAGE(
		"dumping %s interaction data\n"
		"c_id %lld\n"
		"sc_id %lld",
		interaction_short_name[euc->interaction],
		euc->c_id,
		euc->sc_id);
	switch (euc->interaction)
	{
		case ADMIN_CONFIRM:
			LOG_ERROR_MESSAGE(
				"i_id %lld\n"
				"i_image %lld\n"
				"i_thumbnail %lld\n"
				"i_cost %f", euc->admin_confirm_data.i_id,
				euc->admin_confirm_data.i_image,
				euc->admin_confirm_data.i_thumbnail,
				euc->admin_confirm_data.i_cost);
			break;
		case ADMIN_REQUEST:
			LOG_ERROR_MESSAGE("i_id %lld", euc->admin_request_data.i_id);
			break;
		case BEST_SELLERS:
			LOG_ERROR_MESSAGE(
				"i_subject %s", euc->best_sellers_data.i_subject);
			break;
		case BUY_CONFIRM:
			if (euc->buy_confirm_data.c_id < 1 ||
				euc->buy_confirm_data.c_id > customers)
			{
				LOG_ERROR_MESSAGE("review BR data\n---BR---\n"
					"sc_id %lld", euc->buy_request_data.sc_id);
				if (euc->buy_request_data.returning_flag == TRUE)
				{
					LOG_ERROR_MESSAGE(
						"c_uname %s\n"
						"c_passwd %s\n",
						euc->buy_request_data.c_uname,
						euc->buy_request_data.c_passwd);
				}
				else
				{
					LOG_ERROR_MESSAGE(
						"c_discount %f\n"
						"c_fname %s\n"
						"c_lname %s\n"
						"c_phone %s\n"
						"c_email %s\n"
						"c_birthdate %s\n"
						"c_data %s\n"
						"addr_street1 %s\n"
						"addr_street2 %s\n"
						"addr_city %s\n"
						"addr_state %s\n"
						"addr_zip %s\n"
						"co_name %s\n---BR---",
						euc->buy_request_data.c_discount,
						euc->buy_request_data.c_fname,
						euc->buy_request_data.c_lname,
						euc->buy_request_data.c_phone,
						euc->buy_request_data.c_email,
						euc->buy_request_data.c_birthdate,
						euc->buy_request_data.c_data,
						euc->buy_request_data.address.addr_street1,
						euc->buy_request_data.address.addr_street2,
						euc->buy_request_data.address.addr_city,
						euc->buy_request_data.address.addr_state,
						euc->buy_request_data.address.addr_zip,
						euc->buy_request_data.address.co_name);
				}
			}
			LOG_ERROR_MESSAGE(
				"sc_id %lld\n"
				"c_id %lld\n"
				"cx_type %s\n"
				"cx_num %s\n"
				"cx_name %s\n"
				"cx_expiry %s\n"
				"o_ship_type %s",
				euc->buy_confirm_data.sc_id,
				euc->buy_confirm_data.c_id,
				euc->buy_confirm_data.cx_type,
				euc->buy_confirm_data.cx_num,
				euc->buy_confirm_data.cx_name,
				euc->buy_confirm_data.cx_expiry,
				euc->buy_confirm_data.o_ship_type);
			if (euc->buy_confirm_data.update_address == TRUE)
			{
				LOG_ERROR_MESSAGE(
					"addr_street1 %s\n"
					"addr_street2 %s\n"
					"addr_city %s\n"
					"addr_state %s\n"
					"addr_zip %s\n"
					"co_name %s\n",
					euc->buy_confirm_data.shipping.addr_street1,
					euc->buy_confirm_data.shipping.addr_street2,
					euc->buy_confirm_data.shipping.addr_city,
					euc->buy_confirm_data.shipping.addr_state,
					euc->buy_confirm_data.shipping.addr_zip,
					euc->buy_confirm_data.shipping.co_name);
			}
			break;
		case BUY_REQUEST:
			LOG_ERROR_MESSAGE("sc_id %lld", euc->buy_request_data.sc_id);
			if (euc->buy_request_data.c_id != UNKNOWN_CUSTOMER)
			{
				LOG_ERROR_MESSAGE(
					"c_id %lld\n"
					"c_uname %s\n"
					"c_passwd %s\n",
					euc->buy_request_data.c_id,
					euc->buy_request_data.c_uname,
					euc->buy_request_data.c_passwd);
			}
			else
			{
				LOG_ERROR_MESSAGE(
					"c_discount %f\n"
					"c_fname %s\n"
					"c_lname %s\n"
					"c_phone %s\n"
					"c_email %s\n"
					"c_birthdate %s\n"
					"c_data %s\n"
					"addr_street1 %s\n"
					"addr_street2 %s\n"
					"addr_city %s\n"
					"addr_state %s\n"
					"addr_zip %s\n"
					"co_name %s\n",
					euc->buy_request_data.c_discount,
					euc->buy_request_data.c_fname,
					euc->buy_request_data.c_lname,
					euc->buy_request_data.c_phone,
					euc->buy_request_data.c_email,
					euc->buy_request_data.c_birthdate,
					euc->buy_request_data.c_data,
					euc->buy_request_data.address.addr_street1,
					euc->buy_request_data.address.addr_street2,
					euc->buy_request_data.address.addr_city,
					euc->buy_request_data.address.addr_state,
					euc->buy_request_data.address.addr_zip,
					euc->buy_request_data.address.co_name);
			}
			break;
		case HOME:
			LOG_ERROR_MESSAGE("c_id %lld", euc->home_data.c_id);
			break;
		case NEW_PRODUCTS:
			LOG_ERROR_MESSAGE(
				"i_subject %s", euc->best_sellers_data.i_subject);
			break;
		case ORDER_DISPLAY:
			LOG_ERROR_MESSAGE(
				"c_uname %s\n"
				"c_passwd %s\n",
				euc->order_display_data.c_uname,
				euc->order_display_data.c_passwd);
			break;
		case ORDER_INQUIRY:
			LOG_ERROR_MESSAGE("c_id %lld", euc->order_inquiry_data.c_id);
			break;
		case PRODUCT_DETAIL:
			LOG_ERROR_MESSAGE("i_id %lld", euc->product_detail_data.i_id);
			break;
		case SEARCH_REQUEST:
			break;
		case SEARCH_RESULTS:
			LOG_ERROR_MESSAGE(
				"search_type %d\n"
				"search_string %s",
				euc->search_results_data.search_type,
				euc->search_results_data.search_string);
			break;
		case SHOPPING_CART:
			LOG_ERROR_MESSAGE(
				"add_flag %d\n"
				"sc_size %d",
				euc->shopping_cart_data.add_flag,
				euc->shopping_cart_data.sc_size);
			for (i=0;i<euc->shopping_cart_data.sc_size; i++)
			{
				LOG_ERROR_MESSAGE("i_id %lld\n"
						  "i_qty %d",
						euc->shopping_cart_data.scl_data[i].scl_i_id, euc->shopping_cart_data.scl_data[i].scl_qty);
			}
			break;
		default:
			LOG_ERROR_MESSAGE("unknown interaction %d", euc->interaction);
			break;
	}
	return W_OK;
}

/* 
 * Determine the next interaction based on a predefined decision matrix.
 * Clause 5.2.2.4
 */
int get_next_interaction(int prev_interaction)
{
	int threshold;
	int i;

	threshold = (int) get_random(10000);
	for (i = 0; i < INTERACTION_TOTAL; i++)
	{
		if (mix_matrix[prev_interaction][i] != 0 &&
			threshold <= mix_matrix[prev_interaction][i])
		{
			return i;
		}
	}
	
	LOG_ERROR_MESSAGE(
		"cannot get next interaction from %s where threshold is %d\n",
		interaction_short_name[prev_interaction], threshold);
	return -1;
}

/* 
 * Calculate and return a think time using a negative exponential function
 * while limiting the maximum value.
 * tt = -ln(r) * m
 * tt: think time, in milliseconds
 * r: random number with at least 31 bit precision, where 0 < r <= 1
 * m = mean think time, in milliseconds
 * Clause 5.3.1.1
 */
int get_think_time()
{
	int tt;
	time_t t;

	tt = -1.0 * log(get_percentage() + 0.000001) * think_time_mean;
	if (tt > 10 * think_time_mean)
	{
		tt = 10 * think_time_mean;
	}

	/* Log the calculate think time. */
	pthread_mutex_lock(&mutex_think_time_log);
	time(&t);
	fprintf(log_think_time, "%d,%d,%d\n", t, tt, pthread_self());
	fflush(log_think_time);
	pthread_mutex_unlock(&mutex_think_time_log);

	return tt;
}

/* 
 * Calculate and return the user session minimum duration time using a
 * negative exponential function while limiting the maximum value.
 * usmd = -ln(r) * m
 * usmd: User Session Minimum Duration, in milliseconds
 * r: random number uniformly distributed between 0 and 1.0
 * m: mean usmd in milliseconds
 * Clause 6.2.1.2
 */
double get_usmd()
{
	double usmd;
	time_t t;

	usmd = -1.0 * log(get_percentage() + 0.000001) * USMD_MEAN;
	if (usmd > 4.0 * USMD_MEAN)
	{
		usmd = 4.0 * USMD_MEAN;
	}

	/* Log the calculated USMD. */
	pthread_mutex_lock(&mutex_usmd_log);
	time(&t);
	fprintf(log_usmd, "%d,%f,%d\n", t, usmd, pthread_self());
	fflush(log_usmd);
	pthread_mutex_unlock(&mutex_usmd_log);

	return usmd;
}

/* 
 * Preset the numbers in the matrix for a browsing mix.
 * Clause 5.2.2.4
 */
void init_browsing_mix()
{
	mix_matrix[ADMIN_CONFIRM][HOME] = 9877;
	mix_matrix[ADMIN_CONFIRM][SEARCH_REQUEST] = 9999;

	mix_matrix[ADMIN_REQUEST][ADMIN_CONFIRM] = 8999;
	mix_matrix[ADMIN_REQUEST][HOME] = 9999;

	mix_matrix[BEST_SELLERS][HOME] = 4607;
	mix_matrix[BEST_SELLERS][PRODUCT_DETAIL] = 5259;
	mix_matrix[BEST_SELLERS][SEARCH_REQUEST] = 9942;
	mix_matrix[BEST_SELLERS][SHOPPING_CART] = 9999;

	mix_matrix[BUY_CONFIRM][HOME] = 342;
	mix_matrix[BUY_CONFIRM][SEARCH_REQUEST] = 9999;

	mix_matrix[BUY_REQUEST][BUY_CONFIRM] = 9199;
	mix_matrix[BUY_REQUEST][HOME] = 9595;
	mix_matrix[BUY_REQUEST][SHOPPING_CART] = 9999;

	mix_matrix[CUSTOMER_REGISTRATION][BUY_REQUEST] = 9145;
	mix_matrix[CUSTOMER_REGISTRATION][HOME] = 9619;
	mix_matrix[CUSTOMER_REGISTRATION][SEARCH_REQUEST] = 9999;

	mix_matrix[HOME][BEST_SELLERS] = 3792;
	mix_matrix[HOME][NEW_PRODUCTS] = 7585;
	mix_matrix[HOME][ORDER_INQUIRY] = 7688;
	mix_matrix[HOME][SEARCH_REQUEST] = 9559;
	mix_matrix[HOME][SHOPPING_CART] = 9999;

	mix_matrix[NEW_PRODUCTS][HOME] = 299;
	mix_matrix[NEW_PRODUCTS][PRODUCT_DETAIL] = 9867;
	mix_matrix[NEW_PRODUCTS][SEARCH_REQUEST] = 9941;
	mix_matrix[NEW_PRODUCTS][SHOPPING_CART] = 9999;

	mix_matrix[ORDER_DISPLAY][HOME] = 69;
	mix_matrix[ORDER_DISPLAY][SEARCH_REQUEST] = 9999;

	mix_matrix[ORDER_INQUIRY][HOME] = 523;
	mix_matrix[ORDER_INQUIRY][ORDER_DISPLAY] = 8856;
	mix_matrix[ORDER_INQUIRY][SEARCH_REQUEST] = 9999;

	mix_matrix[PRODUCT_DETAIL][ADMIN_REQUEST] = 47;
	mix_matrix[PRODUCT_DETAIL][HOME] = 8346;
	mix_matrix[PRODUCT_DETAIL][PRODUCT_DETAIL] = 9749;
	mix_matrix[PRODUCT_DETAIL][SEARCH_REQUEST] = 9890;
	mix_matrix[PRODUCT_DETAIL][SHOPPING_CART] = 9999;

	mix_matrix[SEARCH_REQUEST][HOME] = 788;
	mix_matrix[SEARCH_REQUEST][SEARCH_RESULTS] = 9955;
	mix_matrix[SEARCH_REQUEST][SHOPPING_CART] = 9999;

	mix_matrix[SEARCH_RESULTS][HOME] = 3674;
	mix_matrix[SEARCH_RESULTS][PRODUCT_DETAIL] = 9868;
	mix_matrix[SEARCH_RESULTS][SEARCH_REQUEST] = 9942;
	mix_matrix[SEARCH_RESULTS][SHOPPING_CART] = 9999;

	mix_matrix[SHOPPING_CART][CUSTOMER_REGISTRATION] = 4099;
	mix_matrix[SHOPPING_CART][HOME] = 8883;
	mix_matrix[SHOPPING_CART][SHOPPING_CART] = 9999;
}

/* 
 * Preset the numbers in the matrix for an ordering mix.
 * Clause 5.2.2.4
 */
void init_ordering_mix()
{
	mix_matrix[ADMIN_CONFIRM][HOME] = 8348;
	mix_matrix[ADMIN_CONFIRM][SEARCH_REQUEST] = 9999;

	mix_matrix[ADMIN_REQUEST][ADMIN_CONFIRM] = 8999;
	mix_matrix[ADMIN_REQUEST][HOME] = 9999;

	mix_matrix[BEST_SELLERS][HOME] = 1;
	mix_matrix[BEST_SELLERS][PRODUCT_DETAIL] = 333;
	mix_matrix[BEST_SELLERS][SEARCH_REQUEST] = 9998;
	mix_matrix[BEST_SELLERS][SHOPPING_CART] = 9999;

	mix_matrix[BUY_CONFIRM][HOME] = 2;
	mix_matrix[BUY_CONFIRM][SEARCH_REQUEST] = 9999;

	mix_matrix[BUY_REQUEST][BUY_CONFIRM] = 7999;
	mix_matrix[BUY_REQUEST][HOME] = 9452;
	mix_matrix[BUY_REQUEST][SHOPPING_CART] = 9999;

	mix_matrix[CUSTOMER_REGISTRATION][BUY_REQUEST] = 9899;
	mix_matrix[CUSTOMER_REGISTRATION][HOME] = 9901;
	mix_matrix[CUSTOMER_REGISTRATION][SEARCH_REQUEST] = 9999;

	mix_matrix[HOME][BEST_SELLERS] = 499;
	mix_matrix[HOME][NEW_PRODUCTS] = 999;
	mix_matrix[HOME][ORDER_INQUIRY] = 1269;
	mix_matrix[HOME][SEARCH_REQUEST] = 1295;
	mix_matrix[HOME][SHOPPING_CART] = 9999;

	mix_matrix[NEW_PRODUCTS][HOME] = 504;
	mix_matrix[NEW_PRODUCTS][PRODUCT_DETAIL] = 9942;
	mix_matrix[NEW_PRODUCTS][SEARCH_REQUEST] = 9976;
	mix_matrix[NEW_PRODUCTS][SHOPPING_CART] = 9999;

	mix_matrix[ORDER_DISPLAY][HOME] = 9939;
	mix_matrix[ORDER_DISPLAY][SEARCH_REQUEST] = 9999;

	mix_matrix[ORDER_INQUIRY][HOME] = 1168;
	mix_matrix[ORDER_INQUIRY][ORDER_DISPLAY] = 9968;
	mix_matrix[ORDER_INQUIRY][SEARCH_REQUEST] = 9999;

	mix_matrix[PRODUCT_DETAIL][ADMIN_REQUEST] = 99;
	mix_matrix[PRODUCT_DETAIL][HOME] = 3750;
	mix_matrix[PRODUCT_DETAIL][PRODUCT_DETAIL] = 5621;
	mix_matrix[PRODUCT_DETAIL][SEARCH_REQUEST] = 8341;
	mix_matrix[PRODUCT_DETAIL][SHOPPING_CART] = 9999;

	mix_matrix[SEARCH_REQUEST][HOME] = 815;
	mix_matrix[SEARCH_REQUEST][SEARCH_RESULTS] = 9815;
	mix_matrix[SEARCH_REQUEST][SHOPPING_CART] = 9999;

	mix_matrix[SEARCH_RESULTS][HOME] = 486;
	mix_matrix[SEARCH_RESULTS][PRODUCT_DETAIL] = 7817;
	mix_matrix[SEARCH_RESULTS][SEARCH_REQUEST] = 9998;
	mix_matrix[SEARCH_RESULTS][SHOPPING_CART] = 9999;

	mix_matrix[SHOPPING_CART][CUSTOMER_REGISTRATION] = 9499;
	mix_matrix[SHOPPING_CART][HOME] = 9918;
	mix_matrix[SHOPPING_CART][SHOPPING_CART] = 9999;
}

/*
 * Preset the numbers in the matrix for a shopping mix.
 * Clause 5.2.2.4
 */
void init_shopping_mix()
{
	mix_matrix[ADMIN_CONFIRM][HOME] = 9952;
	mix_matrix[ADMIN_CONFIRM][SEARCH_REQUEST] = 9999;

	mix_matrix[ADMIN_REQUEST][ADMIN_CONFIRM] = 8999;
	mix_matrix[ADMIN_REQUEST][HOME] = 9999;

	mix_matrix[BEST_SELLERS][HOME] = 167;
	mix_matrix[BEST_SELLERS][PRODUCT_DETAIL] = 472;
	mix_matrix[BEST_SELLERS][SEARCH_REQUEST] = 9927;
	mix_matrix[BEST_SELLERS][SHOPPING_CART] = 9999;

	mix_matrix[BUY_CONFIRM][HOME] = 84;
	mix_matrix[BUY_CONFIRM][SEARCH_REQUEST] = 9999;

	mix_matrix[BUY_REQUEST][BUY_CONFIRM] = 4614;
	mix_matrix[BUY_REQUEST][HOME] = 6545;
	mix_matrix[BUY_REQUEST][SHOPPING_CART] = 9999;

	mix_matrix[CUSTOMER_REGISTRATION][BUY_REQUEST] = 8666;
	mix_matrix[CUSTOMER_REGISTRATION][HOME] = 8760;
	mix_matrix[CUSTOMER_REGISTRATION][SEARCH_REQUEST] = 9999;

	mix_matrix[HOME][BEST_SELLERS] = 3124;
	mix_matrix[HOME][NEW_PRODUCTS] = 6249;
	mix_matrix[HOME][ORDER_INQUIRY] = 6718;
	mix_matrix[HOME][SEARCH_REQUEST] = 7026;
	mix_matrix[HOME][SHOPPING_CART] = 9999;

	mix_matrix[NEW_PRODUCTS][HOME] = 156;
	mix_matrix[NEW_PRODUCTS][PRODUCT_DETAIL] = 9735;
	mix_matrix[NEW_PRODUCTS][SEARCH_REQUEST] = 9784;
	mix_matrix[NEW_PRODUCTS][SHOPPING_CART] = 9999;

	mix_matrix[ORDER_DISPLAY][HOME] = 69;
	mix_matrix[ORDER_DISPLAY][SEARCH_REQUEST] = 9999;

	mix_matrix[ORDER_INQUIRY][HOME] = 72;
	mix_matrix[ORDER_INQUIRY][ORDER_DISPLAY] = 8872;
	mix_matrix[ORDER_INQUIRY][SEARCH_REQUEST] = 9999;

	mix_matrix[PRODUCT_DETAIL][ADMIN_REQUEST] = 58;
	mix_matrix[PRODUCT_DETAIL][HOME] = 832;
	mix_matrix[PRODUCT_DETAIL][PRODUCT_DETAIL] = 1288;
	mix_matrix[PRODUCT_DETAIL][SEARCH_REQUEST] = 8603;
	mix_matrix[PRODUCT_DETAIL][SHOPPING_CART] = 9999;

	mix_matrix[SEARCH_REQUEST][HOME] = 635;
	mix_matrix[SEARCH_REQUEST][SEARCH_RESULTS] = 9135;
	mix_matrix[SEARCH_REQUEST][SHOPPING_CART] = 9999;

	mix_matrix[SEARCH_RESULTS][HOME] = 2657;
	mix_matrix[SEARCH_RESULTS][PRODUCT_DETAIL] = 9294;
	mix_matrix[SEARCH_RESULTS][SEARCH_REQUEST] = 9304;
	mix_matrix[SEARCH_RESULTS][SHOPPING_CART] = 9999;

	mix_matrix[SHOPPING_CART][CUSTOMER_REGISTRATION] = 2585;
	mix_matrix[SHOPPING_CART][HOME] = 9552;
	mix_matrix[SHOPPING_CART][SHOPPING_CART] = 9999;
}

/* 
 * Initialize a semaphore and create a thread per user to run.
 */
#ifdef PHASE1
#ifdef SEARCH_RESULTS_CACHE
int init_eus(char *sname, char *uname, char *auth, int eus,
	int interaction_mix, int rampuprate, int duration, double tt_mean,
	int item_scale, char *host, int port)
#else
int init_eus(char *sname, char *uname, char *auth, int eus,
	int interaction_mix, int rampuprate, int duration, double tt_mean,
	int item_scale)

#endif /*SEARCH_RESULTS_CACHE */
#endif /*PHASE1*/
#ifdef PHASE2
int init_eus(char *sname, int port, int eus,
	int interaction_mix, int rampuprate, int duration, double tt_mean,
	int item_scale)
#endif
{
	int i, rc;
	struct timespec ts;

#ifdef PHASE1
#ifdef SEARCH_RESULTS_CACHE
	strcpy(cache_host, host);
	cache_port = port;
#endif
#endif

	/*
	 * Initialize the semaphore that keeps count of the number of threads
	 * currently running.
	 */
	if (sem_init(&running_eu_count, 0, 0) != 0)
	{
		LOG_ERROR_MESSAGE("cannot init running_eu_count\n");
		return W_ERROR;
	}

	/*
	 * Open log files to record the actual mix of interactions, the think time
	 * calculated, and the USMD calculated.
	 */
	log_mix = fopen(MIX_LOG_NAME, "w");
	if (log_mix == NULL)
	{
		fprintf(stderr, "cannot open %s\n", MIX_LOG_NAME);
		return W_ERROR;
	}

	log_think_time = fopen(THINK_TIME_LOG_NAME, "w");
	if (log_think_time == NULL)
	{
		fprintf(stderr, "cannot open %s\n", THINK_TIME_LOG_NAME);
		return W_ERROR;
	}

	log_usmd = fopen(USMD_LOG_NAME, "w");
	if (log_usmd == NULL)
	{
		fprintf(stderr, "cannot open %s\n", USMD_LOG_NAME);
		return W_ERROR;
	}

#ifdef RUNTIME_STATS
	/* Initialize the statistics counters. */
	for (i = 0; i < INTERACTION_TOTAL; i++)
	{
		 interaction_count[i] = 0;
		 cumulative_response_time[i] = 0;

		 pthread_mutex_init(&mutex_stats[i], NULL); 
	}
#endif /* RUNTIME_STATS */

	/* Initialized the matrix for the correct interaction mix. */
	for (i = 0; i < INTERACTION_TOTAL; i++)
	{
		for (rc = 0; rc < INTERACTION_TOTAL; rc++)
		{
			mix_matrix[i][rc] = 0;
		}
	}
	switch (interaction_mix)
	{
		case MIX_SHOPPING:
			init_shopping_mix();
			break;
		case MIX_BROWSING:
			init_browsing_mix();
			break;
		case MIX_ORDERING:
			init_ordering_mix();
			break;
	}

	/* Initialize global constants. */
	item_count = item_scale;
	if (customers >= 0 && customers < 10000)
	{
		a = 1023;
	}
	else if (customers < 40000)
	{
		a = 4095;
	}
	else if (customers < 160000)
	{
		a = 16383;
	}
	else if (customers < 640000)
	{
		a = 65535;
	}
	else if (customers < 2560000)
	{
		a = 262143;
	}
	else if (customers < 10240000)
	{
		a = 1048575;
	}
	else if (customers < 40960000)
	{
		a = 4194303;
	}
	else if (customers < 163840000)
	{
		a = 16777215;
	}
	else if (customers >= 163840000 && customers < 655359999)
	{
		a = 67108863;
	}
	else
	{
		LOG_ERROR_MESSAGE("customer cardinality error %d\n", customers);
		return W_ERROR;
	}
	think_time_mean = tt_mean * 1000.0;

#ifdef PHASE1
	/* Set the ODBC connect string, username and password. */
	odbc_init(sname, uname, auth);
#endif /* PHASE1 */

#ifdef PHASE2
	strcpy(tm_address, sname);
#endif /* PHASE2 */

	/*
	 * Calculate the stop time from this point, right before the EB threads
	 * are started.  Do not factor in the rampup time as part of the run
	 * duration.
	 */
	stop_time = time(NULL) + duration + (int) ((eus / rampuprate) * 60);

	printf("starting %d users\n", eus);
	for (i = 0; i < eus; i++)
	{
		pthread_t tid;

		/* Increment the semaphore to signal that an user has started. */
		sem_post(&running_eu_count);

		/* Start a thread. */
#ifdef PHASE1
		if (pthread_create(&tid, NULL, &start_eu,NULL) != 0)
#endif /* PHASE1 */
#ifdef PHASE2
		if (pthread_create(&tid, NULL, &start_eu, &port) != 0)
#endif /* PHASE2 */
		{
			/* Just bail if a thread cannot start. */
			LOG_ERROR_MESSAGE("error creating thread\n");
			return W_ERROR;
		}
		ts.tv_sec = (time_t) (60 / rampuprate);
		ts.tv_nsec =
			(long) ((60000.0 / (double) ((rampuprate * 1000) % 1000)) * 1000000.0);
		nanosleep(&ts, NULL);
	}

	return W_OK;
}

int mark_logs(char *mark)
{
	pthread_mutex_lock(&mutex_mix_log);
	fprintf(log_mix, "%d,%s\n", time(NULL), mark);
	fflush(log_mix);
	pthread_mutex_unlock(&mutex_mix_log);

	pthread_mutex_lock(&mutex_think_time_log);
	fprintf(log_think_time, "%s\n", mark);
	fflush(log_think_time);
	pthread_mutex_unlock(&mutex_think_time_log);

	pthread_mutex_lock(&mutex_usmd_log);
	fprintf(log_usmd, "%s\n", mark);
	fflush(log_usmd);
	pthread_mutex_unlock(&mutex_usmd_log);

	return W_OK;
}

/*
 * Clause 2.16
 */
int prepare_admin_confirm(struct eu_context_t *euc)
{
	euc->admin_confirm_data.i_id = euc->admin_request_data.i_id;
	euc->admin_confirm_data.i_cost =
		(1.0 - (double) get_random(6) / 10.0) * euc->admin_request_data.i_srp;
	euc->admin_confirm_data.i_image = (int) get_random(item_count);
	euc->admin_confirm_data.i_thumbnail = (int) get_random(item_count);

	return W_OK;
}

/* 
 * Clause 2.15
 */
int prepare_admin_request(struct eu_context_t *euc)
{
	euc->admin_request_data.i_id = euc->product_detail_data.i_id;

	return W_OK;
}

/* 
 * Clause 2.13
 */
int prepare_best_sellers(struct eu_context_t *euc)
{
	euc->previous_search_interaction = BEST_SELLERS;

	strcpy(euc->best_sellers_data.i_subject,
		i_subject[(int) get_random(I_SUBJECT_MAX)]);

	return W_OK;
}

/* 
 * Clause 2.7
 */
int prepare_buy_confirm(struct eu_context_t *euc)
{
	time_t t1;
	struct tm *tm1;

	euc->buy_confirm_data.c_id = euc->c_id;
	euc->buy_confirm_data.sc_id = euc->sc_id;

	strcpy(euc->buy_confirm_data.cx_type,
		cx_type[(int) get_random(CX_TYPE_MAX)]);

	get_n_string(euc->buy_confirm_data.cx_num, 16, 16);

	sprintf(euc->buy_confirm_data.cx_name, "%s %s",
		euc->buy_request_data.c_fname, euc->buy_request_data.c_lname);

	time(&t1);
	t1 += 86400 + (int) get_random(63158400);
	tm1 = localtime(&t1);
	sprintf(euc->buy_confirm_data.cx_expiry, "%04d%02d%02d",
		tm1->tm_year + 1900, tm1->tm_mon + 1, tm1->tm_mday);
	
	if (get_percentage() > 0.05)
	{
		euc->buy_confirm_data.update_address = FALSE;
	}
	else
	{
		euc->buy_confirm_data.update_address = TRUE;

		get_a_string(euc->buy_confirm_data.shipping.addr_street1,
			15, ADDR_STREET1_LEN);

		get_a_string(euc->buy_confirm_data.shipping.addr_street2,
			15, ADDR_STREET1_LEN);

		get_a_string(euc->buy_confirm_data.shipping.addr_city,
			4, ADDR_CITY_LEN);

		get_a_string(euc->buy_confirm_data.shipping.addr_state,
			2, ADDR_STATE_LEN);

		get_a_string(euc->buy_confirm_data.shipping.addr_zip,
			5, ADDR_ZIP_LEN);

		strcpy(euc->buy_confirm_data.shipping.co_name,
			co_name[(int) get_random(CO_ID_MAX)]);
	}

	return W_OK;
}

/* 
 * Clause 2.6
 */
int prepare_buy_request(struct eu_context_t *euc)
{
	euc->buy_request_data.sc_id = euc->sc_id;
	euc->buy_request_data.c_id = euc->c_id;
	if (euc->buy_request_data.c_id != UNKNOWN_CUSTOMER)
	{
		int i, max;

		euc->buy_request_data.returning_flag = TRUE;
		digsyl2(euc->buy_request_data.c_uname, euc->buy_request_data.c_id, 0);
		max = strlen(euc->buy_request_data.c_uname);
		for (i = 0; i < max; i++)
		{
			euc->buy_request_data.c_passwd[i] =
				(char) tolower(euc->buy_request_data.c_uname[i]);
		}
	}
	else
	{
		time_t t1, t2, t3;
		struct tm tm1, *tm2, *tm3;

#ifdef DEBUG
		DEBUGMSG("creating new customer...");
#endif
		euc->buy_request_data.returning_flag = FALSE;

		get_a_string(euc->buy_request_data.c_fname, 8, C_FNAME_LEN);

		get_a_string(euc->buy_request_data.c_lname, 8, C_LNAME_LEN);

		sprintf(euc->buy_request_data.c_email, "%s@%s.com",
			euc->buy_request_data.c_fname,
			euc->buy_request_data.c_lname);

		get_n_string(euc->buy_request_data.c_phone, 9, C_PHONE_LEN);

		get_a_string(euc->buy_request_data.c_data, 100, C_DATA_LEN);

		/* The date is being calculated from 1900 instead of 1880. */
		tm1.tm_year = 0;
		tm1.tm_mon = 0;
		tm1.tm_mday = 1;
		tm1.tm_sec = 0;
		tm1.tm_min = 0;
		tm1.tm_hour = 0;
		t1 = mktime(&tm1);
		time(&t2);
		tm2 = localtime(&t2);
		t3 = (time_t) (get_percentage() * (double) ((long long) t2 - (long long) t1 + (long long) 86400)) + t1;
		tm3 = localtime(&t3);
		sprintf(euc->buy_request_data.c_birthdate, "%04d%02d%02d",
			tm3->tm_year + 1900, tm3->tm_mon + 1, tm3->tm_mday);

		get_a_string(euc->buy_request_data.address.addr_street1,
			15, ADDR_STREET1_LEN);

		get_a_string(euc->buy_request_data.address.addr_street2,
			15, ADDR_STREET2_LEN);

		get_a_string(euc->buy_request_data.address.addr_city,
			4, ADDR_CITY_LEN);

		get_a_string(euc->buy_request_data.address.addr_state,
			2, ADDR_STATE_LEN);

		get_a_string(euc->buy_request_data.address.addr_zip,
			5, ADDR_ZIP_LEN);

		strcpy(euc->buy_request_data.address.co_name,
			co_name[(int) get_random(CO_ID_MAX)]);
	}

	return W_OK;
}

/*
 * Clause 2.3
 */
int prepare_home(struct eu_context_t *euc)
{
	/* if it is the first interaction, then generate c_id */
	if (euc->first_interaction == TRUE )
	{
		if (get_percentage() <= 0.80)
		{
			euc->c_id = euc->home_data.c_id = get_nu_rand(a, 1, customers);
			if (euc->c_id < 1 || euc->c_id > customers)
			{
				LOG_ERROR_MESSAGE("invalid c_id generated %lld", euc->c_id);
				return W_ERROR;
			}
		}
		else
		{
			euc->home_data.c_id = UNKNOWN_CUSTOMER;
		}
	}

	return W_OK;
}

/*
 * Clause 2.12
 */
int prepare_new_products(struct eu_context_t *euc)
{
	euc->previous_search_interaction = NEW_PRODUCTS;

	strcpy(euc->new_products_data.i_subject,
		i_subject[(int) get_random(I_SUBJECT_MAX)]);

	return W_OK;
}

/*
 * Clause 2.9
 */
int prepare_order_display(struct eu_context_t *euc)
{
	int i, max;
	long long temp_c_id;

	temp_c_id = euc->c_id;

	/* Remember that 0 == UNKNOWN CUSTOMER. */
	if (temp_c_id < 0)
	{
		LOG_ERROR_MESSAGE("invalid c_id %lld", euc->c_id);
		return W_ERROR;
	}

	/*
	 * We use temp_c_id instead of registering this as a known customer, by
	 * setting euc->c_id, because the specification says this interaction
	 * does not signify that the customer will be known.
	 */
	if (temp_c_id == UNKNOWN_CUSTOMER)
	{
		temp_c_id = get_nu_rand(a, 1, customers);
	}

	digsyl2(euc->order_display_data.c_uname, temp_c_id, 0);
	max = strlen(euc->order_display_data.c_uname);
	for (i = 0; i < max; i++)
	{
		euc->order_display_data.c_passwd[i] =
			(char) tolower(euc->order_display_data.c_uname[i]);
	}

	return W_OK;
}

/*
 * Clause 2.8
 */
int prepare_order_inquiry(struct eu_context_t *euc)
{
	euc->order_inquiry_data.c_id = euc->c_id;

	return W_OK;
}

/*
 * Clause 2.14
 */
int prepare_product_detail(struct eu_context_t *euc)
{
	if (euc->previous_search_interaction == BEST_SELLERS)
	{
		euc->product_detail_data.i_id =
			euc->best_sellers_data.results_data[(int) get_random(euc->best_sellers_data.items)].i_id;
	}
	else if (euc->previous_search_interaction == NEW_PRODUCTS)
	{
		euc->product_detail_data.i_id =
			euc->new_products_data.results_data[(int) get_random(euc->new_products_data.items)].i_id;
	}
	else if (euc->previous_search_interaction == SEARCH_RESULTS)
	{
		euc->product_detail_data.i_id =
			euc->search_results_data.results_data[(int) get_random(euc->search_results_data.items)].i_id;
	}
	else
	{
		LOG_ERROR_MESSAGE(
			"unknown transition from interaction %d to product details\n",
			euc->previous_search_interaction);
		return W_ERROR;
	}
	if (euc->product_detail_data.i_id==0)
        {
		LOG_ERROR_MESSAGE("PD i_id is 0, previous_interaction %s, previous_search_interaction %s", interaction_short_name[euc->previous_interaction], interaction_short_name[euc->previous_search_interaction]);
		return W_ERROR;
        }

	return W_OK;
}

/*
 * Clause 2.11
 */
int prepare_search_results(struct eu_context_t *euc)
{
	char msg[64];

	euc->previous_search_interaction = SEARCH_RESULTS;

	euc->search_results_data.search_type = (int) get_random(SEARCH_TYPE_MAX);
	switch(euc->search_results_data.search_type)
	{
		case SEARCH_AUTHOR:
			digsyl2(euc->search_results_data.search_string,
				get_nu_rand(a, 1, item_count / 10), 7);
			break;
		case SEARCH_TITLE:
			digsyl2(euc->search_results_data.search_string,
				get_nu_rand(a, 1, item_count / 5), 7);
			break;
		case SEARCH_SUBJECT:
			strcpy(euc->search_results_data.search_string,
				i_subject[(int) get_random(I_SUBJECT_MAX)]);
			break;
		default:
			LOG_ERROR_MESSAGE("invalid search type %d\n",
				euc->search_results_data.search_type);
			return W_ERROR;
	}

	return W_OK;
}

/*
 * Clause 2.4
 */
int prepare_shopping_cart(struct eu_context_t *euc)
{
	int random_pairs;
	int *update_flag;
	int update_index;
	int update_done;

	euc->shopping_cart_data.sc_id = euc->sc_id;
	euc->shopping_cart_data.c_id = euc->c_id;

	/*
	 * Determine the course of action depending on what the previous
	 * interaction was.
	 */
	if (euc->previous_interaction != PRODUCT_DETAIL)
	{
		/* Generally, a user goes to the shopping cart to view it. */
		euc->shopping_cart_data.add_flag = FALSE;
		euc->shopping_cart_data.sc_size = 0;
	}
	else if (euc->previous_interaction == SHOPPING_CART)
	{
		int i;

		/*
		 * If the previous interaction was Shopping Cart then the user must
		 * be updating the quantity of items in the shopping cart.  Update
		 * the quantity for each item to update the shopping cart.
		 */
		euc->shopping_cart_data.add_flag = FALSE;

		/* clause 2.4.5.1 if there is only one (i_id, qty) pair, qty is 
		   a random number between 1 and 10 */
		if (euc->shopping_cart_data.sc_size==1)
			euc->shopping_cart_data.scl_data[0].scl_qty=get_random(10)+1;
		/* else select a random number between 1 and one less than the 
		   number of pairs.
		   for each selected pair, the qty is set to a random number 
		   between 0 and 10 */
		else 
		{
			update_flag = (int *)malloc(sizeof(int)*euc->shopping_cart_data.sc_size);
			for (i=0;i<euc->shopping_cart_data.sc_size; i++)
				update_flag[i]=0;
			update_done=0;

			random_pairs=get_random(euc->shopping_cart_data.sc_size-1)+1;
			for (i=0; i<random_pairs; i++)
			{
				while (update_done == 0)
				{
					update_index=get_random(euc->shopping_cart_data.sc_size);
					if (update_flag[update_index] == 0)
					{
						euc->shopping_cart_data.scl_data[update_index].scl_qty=get_random(11);
						update_flag[update_index]=1;
						update_done=1;
					}
				}
				update_done=0;
			}
			free(update_flag);
		}	
	}
	else
	{
		/*
		 * If the previous interaction was Product Detail, then the user must
		 * be adding an item into the shopping cart.
		 */
		euc->shopping_cart_data.add_flag = TRUE;
		euc->shopping_cart_data.i_id = euc->product_detail_data.i_id;
	}

	return W_OK;
}

/*
 * The main loop of the EB.
 */
void *start_eu(void *data)
{
	double usmd;
	time_t user_start;
	struct timeval rt0, rt1;
	double response_time;
	int i;
	struct eu_context_t euc;
	int rc;
	struct timespec think_time, rem;
	int retry;
	extern int errno;
#ifdef PHASE2
	int *port;
	port = (int *) data;
#endif /* PHASE2 */

	/* Random number generator must be seeded per thread in Linux. */
	srand(time(NULL) + pthread_self());

	/*
	 * Just zero out the entire structure since it's all contiguous and I use
	 * 0 as unknown values (defined in common.h) and so I don't have to
	 * remember which variables to initialize individually.
	 */
	bzero(&euc, sizeof(euc));

#ifdef PHASE1
	/* Connect to the database. */
	while (odbc_connect(&euc.odbcc) != W_OK)
	{
		/*
		 * Attempt to connect to the database every 10 seconds, if there
		 * is a failure.
		 */
		sleep(10);
		LOG_ERROR_MESSAGE("cannot connect to database");
	}
#ifdef SEARCH_RESULTS_CACHE
	if ((euc.cache_s = _connect(cache_host, cache_port)) == -1)
	{
		printf("connect to cache failed\n");
		LOG_ERROR_MESSAGE("connect to cache failed");
		return;
	}
#endif
#endif /* PHASE1 */

#ifdef PHASE2
	if ((euc.s = _connect(tm_address, *port)) == -1)
	{
		printf("connect to appServer failed\n");
		LOG_ERROR_MESSAGE("connect failed");
		return;
	}
#endif /* PHASE2 */

	/* Main loop for the user logic. */
	retry = 0;
	do
	{
		/* Determine this users minimum duration and note the start time. */
		usmd = get_usmd();
		time(&user_start);

		/* The Home interaction is always first. */
		euc.interaction = HOME;
		euc.previous_interaction = HOME;
		euc.sc_id = UNKNOWN_SHOPPING_CART;
		euc.first_interaction=TRUE;
		/* do Home interaction, retry RETRY time if error happens */
		do
		{
			/* Get the time before the interaction is executed. */
			if (gettimeofday(&rt0, NULL) == -1)
			{
				perror("gettimeofday");
			}
			rc = do_interaction(&euc);
			
			/* Get the time after the interaction has executed. */
			if (gettimeofday(&rt1, NULL) == -1)
			{
				perror("gettimeofday");
			}
			if (rc == W_ERROR)
			{
				LOG_ERROR_MESSAGE("error executing %s",
					interaction_short_name[euc.interaction]);
				dump_interaction_data(&euc);

				/* Log the error */
				pthread_mutex_lock(&mutex_mix_log);
				fprintf(log_mix, "%d,ER,%f,%d\n",
					time(NULL), (double)retry, pthread_self());
				fflush(log_mix);
				pthread_mutex_unlock(&mutex_mix_log);

#ifdef PHASE1
				/*
				 * If an error occurs, reconnect since it could be a dropped
				 * connection causing the error.
				 */
				odbc_disconnect(&euc.odbcc);
				odbc_connect(&euc.odbcc);
#endif /* PHASE1 */
				/* an error can be caused by db transaction 
				 * failure, or socket error 
				 */
				/* If an error occurs, sleep for 10 seconds and try again. */
				sleep(10);
			}
			retry++;
		} while (rc == W_ERROR && retry<RETRY);
#ifdef PHASE2
		/* if retry fails, start from the beginning */
		if (rc == W_ERROR && retry==RETRY) 
		{
			LOG_ERROR_MESSAGE("retry Home interaction failed");
			continue;
		}

		/* if appServer close this socket, reconnect */
		if (rc == SOCKET_CLOSE)
		{
			close(euc.s);

			if ((euc.s = _connect(tm_address, *port)) == -1)
			{
				LOG_ERROR_MESSAGE("re-connect failed");
				return;
			}
			LOG_ERROR_MESSAGE("re-connect");
			continue;
		}
#endif
		response_time = time_diff(rt0, rt1);

		/* Log the response time and the interaction that was just executed. */
		/* log only successful interactions */
		pthread_mutex_lock(&mutex_mix_log);
		fprintf(log_mix, "%d,%s,%f,%d\n",
			time(NULL), interaction_short_name[euc.interaction],
			response_time, pthread_self());
		fflush(log_mix);
		pthread_mutex_unlock(&mutex_mix_log);

#ifdef RUNTIME_STATS
		pthread_mutex_lock(&mutex_stats[euc.interaction]);
		++interaction_count[euc.interaction];
		cumulative_response_time[euc.interaction] += response_time;
		pthread_mutex_unlock(&mutex_stats[euc.interaction]);
#endif /* RUNTIME_STATS */

		/* Simulate the user thinking before executing the next interaction. */
		think_time.tv_nsec = (long) get_think_time();
		think_time.tv_sec = (time_t) (think_time.tv_nsec / 1000);
		think_time.tv_nsec = (think_time.tv_nsec % 1000) * 1000000;
		while (nanosleep(&think_time, &rem) == -1)
		{
			if (errno == EINTR)
			{
				memcpy(&think_time, &rem, sizeof (struct timespec));
			}
			else
			{
				LOG_ERROR_MESSAGE("sleep time invalid %d s %ls ns",
					think_time.tv_sec, think_time.tv_nsec);
				break;
			}
		}

		euc.first_interaction=FALSE;
		/*
		 * Continue through the interaction mix until this user's duration
		 * has expired and this user has completed the Home interaction.
		 */
		while (usmd > (difftime(time(NULL), user_start) * 1000.0) ||
			euc.interaction != HOME)
		{ 
			euc.previous_interaction = euc.interaction;
			euc.interaction = get_next_interaction(euc.interaction);
			retry=0;
			do
			{
				/* Get the time before the interaction is executed. */
				if (gettimeofday(&rt0, NULL) == -1)
				{
					perror("gettimeofday");
				}
				rc = do_interaction(&euc);
				/* Get the time after the interaction has executed. */
				if (gettimeofday(&rt1, NULL) == -1)
				{
					perror("gettimeofday");
				}
				if (rc == W_ERROR)
				{
					LOG_ERROR_MESSAGE("error executing %s",
						interaction_short_name[euc.interaction]);
					/* Log the error */
					pthread_mutex_lock(&mutex_mix_log);
					fprintf(log_mix, "%d,ER,%f,%d\n",
						time(NULL), response_time, (double)retry, pthread_self());
					fflush(log_mix);
					pthread_mutex_unlock(&mutex_mix_log);

					dump_interaction_data(&euc);
#ifdef PHASE1
					/*
					 * If an error occurs, reconnect since it could be a
					 * dropped connection causing the error.
				 	 */
					odbc_disconnect(&euc.odbcc);
					odbc_connect(&euc.odbcc);
#endif /* PHASE1 */
					/*
					 * If an error occurs, sleep for 10 seconds and try again.
					 */
					sleep(10);
				}
				retry++;
			} while (rc == W_ERROR && retry < RETRY);
#ifdef PHASE2
			/* if retry fails, try other interaction or the same 
                         * interaction with different data */
			if (rc == W_ERROR && retry == RETRY) continue;

	                /* if appServer close this socket, reconnect */
        	        if (rc == SOCKET_CLOSE)
			{
                        	close(euc.s);
                        	if ((euc.s = _connect(tm_address, *port)) == -1)
                        	{
                               		LOG_ERROR_MESSAGE("re-connect failed");
                                	return;
                        	}
                        	LOG_ERROR_MESSAGE("re-connect");
                        	continue;
                	}
#endif

			response_time =
				(double) (rt1.tv_sec - rt0.tv_sec) + (double) (rt1.tv_usec - rt0.tv_usec) / 1000000.0;

			/*
			 * Log the response time and the interaction that was just
			 * executed.
			 */
			pthread_mutex_lock(&mutex_mix_log);
			fprintf(log_mix, "%d,%s,%f,%d\n",
				time(NULL), interaction_short_name[euc.interaction],
				response_time, pthread_self());
			fflush(log_mix);
			pthread_mutex_unlock(&mutex_mix_log);

#ifdef RUNTIME_STATS
			pthread_mutex_lock(&mutex_stats[euc.interaction]);
			++interaction_count[euc.interaction];
			cumulative_response_time[euc.interaction] += response_time;
			pthread_mutex_unlock(&mutex_stats[euc.interaction]);
#endif /* RUNTIME_STATS */

			think_time.tv_nsec = (long) get_think_time();
			think_time.tv_sec = (time_t) (think_time.tv_nsec / 1000);
			think_time.tv_nsec = (think_time.tv_nsec % 1000) * 1000000;
			while (nanosleep(&think_time, &rem) == -1)
			{
				if (errno == EINTR)
				{
					memcpy(&think_time, &rem, sizeof (struct timespec));
				}
				else
				{
					LOG_ERROR_MESSAGE("sleep time invalid %d s %ls ns",
						think_time.tv_sec, think_time.tv_nsec);
					break;
				}
			}
		}
		/* user session ends*/
#ifdef DEBUG
		DEBUGMSG("user c_id %lld, sc_id %lld, usmd %f, user_session ended", euc.c_id, euc.sc_id, usmd);
#endif

	}
	while (time(NULL) < stop_time);

	sem_wait(&running_eu_count);
}
