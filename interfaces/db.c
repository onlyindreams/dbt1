/*
 * db.c
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2002 Mark Wong & Open Source Development Lab, Inc.
 *
 * 06 March 2003
 */

#include <db.h>

#ifdef odbc
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
#include <odbc_interaction_search_request.h>
#include <odbc_interaction_search_results.h>
#endif

#ifdef libpq
#include <libpq_interaction_admin_confirm.h>
#include <libpq_interaction_admin_request.h>
#include <libpq_interaction_best_sellers.h>
#include <libpq_interaction_buy_confirm.h>
#include <libpq_interaction_buy_request.h>
#include <libpq_interaction_home.h>
#include <libpq_interaction_new_products.h>
#include <libpq_interaction_order_display.h>
#include <libpq_interaction_order_inquiry.h>
#include <libpq_interaction_product_detail.h>
#include <libpq_interaction_shopping_cart.h>
#include <libpq_interaction_search_request.h>
#include <libpq_interaction_search_results.h>
#endif

int db_connect(struct db_context_t *dbc)
{
	if (_db_connect(dbc) != OK)
	{
		return ERROR;
	}
	return OK;
}

#ifdef odbc
int db_init(char *sname, char *uname, char *auth)
#endif
#ifdef libpq
int db_init(char *shost, char *dbname, char *uname, char *auth)
#endif
{
#ifdef odbc	
	_db_init(sname, uname, auth);
#endif
#ifdef libpq
	_db_init(shost, dbname, uname, auth);
#endif
	return OK;
}

int db_disconnect(struct db_context_t *dbc)
{
	if (_db_disconnect(dbc) != OK)
	{
		return ERROR;
	}
	return OK;
}

int process_interaction(int interaction, struct db_context_t *dbc,
	union interaction_data_t *data)
{
	int rc;
	int status;

	switch (interaction)
	{
		case ADMIN_CONFIRM:
			rc = execute_admin_confirm(dbc, &data->admin_confirm_data);
			break;
		case ADMIN_REQUEST:
			rc = execute_admin_request(dbc, &data->admin_request_data);
			break;
		case BEST_SELLERS:
			rc = execute_best_sellers(dbc, &data->best_sellers_data);
			break;
		case BUY_CONFIRM:
			rc = execute_buy_confirm(dbc, &data->buy_confirm_data);
			break;
		case BUY_REQUEST:
			rc = execute_buy_request(dbc, &data->buy_request_data);
			break;
		case HOME:
			rc = execute_home(dbc, &data->home_data);
			break;
		case NEW_PRODUCTS:
			rc = execute_new_products(dbc, &data->new_products_data);
			break;
		case ORDER_DISPLAY:
			rc = execute_order_display(dbc, &data->order_display_data);
			break;
		case ORDER_INQUIRY:
			rc = execute_order_inquiry(dbc, &data->order_inquiry_data);
			break;
		case PRODUCT_DETAIL:
			rc = execute_product_detail(dbc, &data->product_detail_data);
			break;
		case SEARCH_REQUEST:
			rc = execute_search_request(dbc, &data->search_request_data);
			break;
		case SEARCH_RESULTS:
			rc = execute_search_results(dbc, &data->search_results_data);
			break;
		case SHOPPING_CART:
			rc = execute_shopping_cart(dbc, &data->shopping_cart_data);
			break;
		default:
			LOG_ERROR_MESSAGE("unknown interaction type %d", interaction);
			return ERROR;
	}
#ifdef odbc
	if (rc == OK)
	{
		/* Commit. */
		i = commit_transaction(dbc);
		status = OK;
	}
	else
	{
		/* Rollback. */
		i = rollback_transaction(dbc);
		status = STATUS_ROLLBACK;
	}
	if (i != OK )
	{
		status = ERROR;
	}
#endif
/* libpq does not have autocommit implemented yet, it is controlled by BEGIN/END
*/
#ifdef libpq
	if (rc == OK)
	{
		status = OK;
	}
	else
	{
		status = ERROR;
	}
#endif

	return status;
}
