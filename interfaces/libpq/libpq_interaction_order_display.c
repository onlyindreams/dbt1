/*
 * pgsql_interaction_order_display.c
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2002 Mark Wong & Jenny Zhang &
 *		    Open Source Development Lab, Inc.
 * Copyright (C) 2003 Satoshi Nagayasu & Hideyuki Kawashima &
 *                    Sachi Osawa & Hirokazu Kondo & Satoru Satake
 *
 * $Id$
 */

#include <libpq_interaction_order_display.h>

int
execute_order_display(struct db_context_t *dbc,
					  struct order_display_t *data)
{
	PGresult *res;
	int i, j;

	res = pgsql_execute(dbc->conn, STMT_ORDER_DISPLAY,
						data->c_uname,
						data->c_passwd);

	if ( PQresultStatus(res)!=PGRES_TUPLES_OK )
	{
		pgsql_error(dbc->conn);
		PQclear(res);
		return ERROR;
	}

	assert( PQntuples(res)==1 );

	j = 0;
	strcpy(data->c_fname, PQgetvalue(res, 0, j++));
	strcpy(data->c_lname, PQgetvalue(res, 0, j++));
	strcpy(data->c_phone, PQgetvalue(res, 0, j++));
	strcpy(data->c_email, PQgetvalue(res, 0, j++));
	data->o_id = atoll(PQgetvalue(res, 0, j++));
	strcpy(data->o_date, PQgetvalue(res, 0, j++));
	data->o_sub_total = atof(PQgetvalue(res, 0, j++));
	data->o_tax       = atof(PQgetvalue(res, 0, j++));
	data->o_total     = atof(PQgetvalue(res, 0, j++));
	strcpy(data->o_ship_type, PQgetvalue(res, 0, j++));
	strcpy(data->o_ship_date, PQgetvalue(res, 0, j++));
	strcpy(data->o_status,    PQgetvalue(res, 0, j++));
	strcpy(data->cx_type,     PQgetvalue(res, 0, j++));
	strcpy(data->cx_auth_id,  PQgetvalue(res, 0, j++));

	strcpy(data->billing.addr_street1, PQgetvalue(res, 0, j++));
	strcpy(data->billing.addr_street2, PQgetvalue(res, 0, j++));
	strcpy(data->billing.addr_city,    PQgetvalue(res, 0, j++));
	strcpy(data->billing.addr_state,   PQgetvalue(res, 0, j++));
	strcpy(data->billing.addr_zip,     PQgetvalue(res, 0, j++));
	strcpy(data->billing.co_name,      PQgetvalue(res, 0, j++));

	strcpy(data->shipping.addr_street1, PQgetvalue(res, 0, j++));
	strcpy(data->shipping.addr_street2, PQgetvalue(res, 0, j++));
	strcpy(data->shipping.addr_city,    PQgetvalue(res, 0, j++));
	strcpy(data->shipping.addr_state,   PQgetvalue(res, 0, j++));
	strcpy(data->shipping.addr_zip,     PQgetvalue(res, 0, j++));
	strcpy(data->shipping.co_name,      PQgetvalue(res, 0, j++));

	data->items = atoi(PQgetvalue(res, 0, j++));

	for (i=0 ; i<SHOPPING_CART_ITEMS_MAX ; i++)
	{
		data->odl_data[i].ol_i_id     = atoll(PQgetvalue(res, 0, j++));
		strcpy(data->odl_data[i].i_title,     PQgetvalue(res, 0, j++));
		strcpy(data->odl_data[i].i_publisher, PQgetvalue(res, 0, j++));
		data->odl_data[i].i_cost      = atof(PQgetvalue(res, 0, j++));
		data->odl_data[i].ol_qty      = atoi(PQgetvalue(res, 0, j++));
		data->odl_data[i].ol_discount = atof(PQgetvalue(res, 0, j++));
		strcpy(data->odl_data[i].ol_comment,  PQgetvalue(res, 0, j++));
	}

	assert(PQnfields(res)==j);

	PQclear(res);

//	print_order_display_data(data);

	return OK;
}
