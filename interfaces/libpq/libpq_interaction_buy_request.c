/*
 * pgsql_interaction_buy_request.c
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2002 Mark Wong & Jenny Zhang &
 *                    Open Source Development Lab, Inc.
 * Copyright (C) 2003 Satoshi Nagayasu & Hideyuki Kawashima &
 *                    Sachi Osawa & Hirokazu Kondo & Satoru Satake
 *
 * $Id$
 */

#include <libpq_interaction_buy_request.h>

int
execute_buy_request(struct db_context_t *dbc, struct buy_request_t *data)
{
	int i,j;
	PGresult *res;

	/* discount is random number between 0.00 to 0.50 */
	if (data->returning_flag == FALSE)
	{
		data->c_discount = ((double) get_random_int(51) + 1.0) / 100.0;
	}
	res = pgsql_execute(dbc->conn, STMT_BUYREQ,
						data->returning_flag,
						data->c_uname,
						data->sc_id,
						data->c_discount,
						data->c_fname,
						data->c_lname,
						data->address.addr_street1,
						data->address.addr_street2,
						data->address.addr_city,
						data->address.addr_state,
						data->address.addr_zip,
						data->address.co_name,
						data->c_phone,
						data->c_email,
						data->c_birthdate,
						data->c_data);

	if ( PQresultStatus(res)!=PGRES_TUPLES_OK )
	{
		pgsql_error(dbc->conn);
		PQclear(res);
		return ERROR;
	}

	j = 0;
	data->c_discount = atof(PQgetvalue(res, 0, j++));
	strcpy(data->c_fname, PQgetvalue(res, 0, j++));
	strcpy(data->c_lname, PQgetvalue(res, 0, j++));
	strcpy(data->address.addr_street1, PQgetvalue(res, 0, j++));
	strcpy(data->address.addr_street2, PQgetvalue(res, 0, j++));
	strcpy(data->address.addr_city, PQgetvalue(res, 0, j++));
	strcpy(data->address.addr_state, PQgetvalue(res, 0, j++));
	strcpy(data->address.addr_zip, PQgetvalue(res, 0, j++));
	strcpy(data->address.co_name, PQgetvalue(res, 0, j++));
	strcpy(data->c_phone, PQgetvalue(res, 0, j++));
	strcpy(data->c_email, PQgetvalue(res, 0, j++));
	strcpy(data->c_birthdate, PQgetvalue(res, 0, j++));
	strcpy(data->c_data, PQgetvalue(res, 0, j++));
	strcpy(data->c_passwd, PQgetvalue(res, 0, j++));
	data->c_id         = atoll(PQgetvalue(res, 0, j++));
	data->sc_sub_total = atof(PQgetvalue(res, 0, j++));
	data->sc_tax       = atof(PQgetvalue(res, 0, j++));
	data->sc_ship_cost = atof(PQgetvalue(res, 0, j++));
	data->sc_total     = atof(PQgetvalue(res, 0, j++));
	data->sc_size      = atoi(PQgetvalue(res, 0, j++));

	for (i=0 ; i<SHOPPING_CART_ITEMS_MAX ; i++)
	{
		data->scl_data[i].scl_i_id = atoll(PQgetvalue(res, 0, j++));

		strcpy(data->scl_data[i].i_title, PQgetvalue(res, 0, j++));

		data->scl_data[i].scl_cost = atof(PQgetvalue(res, 0, j++));
		data->scl_data[i].scl_srp  = atof(PQgetvalue(res, 0, j++));

		strcpy(data->scl_data[i].i_backing, PQgetvalue(res, 0, j++));

		data->scl_data[i].scl_qty  = atoi(PQgetvalue(res, 0, j++));
	}

	assert(PQnfields(res)==j);

	PQclear(res);

	return OK;
}
