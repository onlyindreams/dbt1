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

int db_connect(struct db_context_t *dbc)
{
	if (odbc_connect(dbc) != OK)
	{
		return W_ERROR;
	}
	return OK;
}

int db_init(char *sname, char *uname, char *auth)
{
	if (odbc_init(sname, uname, auth) != OK)
	{
		return W_ERROR;
	}
	return OK;
}

int process_interaction(int interaction, struct db_context_t *dbc,
	union interaction_data_t *data)
{
	int i;
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
			return W_ERROR;
	}

	if (rc == OK)
	{
		/* Commit. */
		i = SQLEndTran(SQL_HANDLE_DBC, dbc->hdbc, SQL_COMMIT);
		status = OK;
	}
	else
	{
		/* Rollback. */
		i = SQLEndTran(SQL_HANDLE_DBC, dbc->hdbc, SQL_ROLLBACK);
		status = STATUS_ROLLBACK;
	}
	if (i != SQL_SUCCESS && i != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, dbc->hstmt);
		status = W_ERROR;
	}

	return status;
}