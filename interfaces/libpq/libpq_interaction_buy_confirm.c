/*
 * pgsql_interaction_buy_confirm.c
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) Open Source Development Lab, Inc.
 * History:
 * July-2003 Created by Satoshi Nagayasu & Hideyuki Kawashima &
 *                    Sachi Osawa & Hirokazu Kondo & Satoru Satake
 * Aug-13-2003 Reviewed and tested by Jenny Zhang
 * $Id$
 */

#include <libpq_interaction_buy_confirm.h>

int
execute_buy_confirm(struct db_context_t *dbc,
					struct buy_confirm_t *data)
{
	PGresult *res;
	int i, j;
	short int ship_day;
	char ol_comment[OL_COMMENT_LEN + 1];
	char cx_auth_id[CX_AUTH_ID_LEN + 1];

	/* Generate random day between 1 to 7 for ship_date. */
	ship_day = get_random_int(7) + 1;
	/* generate a_string[20..100] as order_line comment */
	get_a_string(ol_comment, 20, 100);
	/* get authentication id from PGE */
	strcpy(cx_auth_id, "012345678912345");

	res = pgsql_execute(dbc->conn, STMT_BUYCONF,
						data->cx_type,
						atoll(data->cx_num),
						data->cx_name,
						data->cx_expiry,
						data->sc_id,
						data->c_id,
						ship_day,
						ol_comment,
						cx_auth_id,
						data->shipping.addr_street1,
						data->shipping.addr_street2,
						data->shipping.addr_city,
						data->shipping.addr_state,
						data->shipping.addr_zip,
						data->shipping.co_name );

	if ( PQresultStatus(res)!=PGRES_TUPLES_OK )
	{
		pgsql_error(dbc->conn);
		PQclear(res);
		return ERROR;
	}

	if ( PQntuples(res)==0 )
	{
		PQclear(res);
		return ERROR;
	}

	j = 0;
	data->c_discount = atof(PQgetvalue(res, 0, j++));
	data->sc_sub_total = atof(PQgetvalue(res, 0, j++));
	data->sc_tax = atof(PQgetvalue(res, 0, j++));
	data->sc_ship_cost = atof(PQgetvalue(res, 0, j++));
	data->sc_total = atof(PQgetvalue(res, 0, j++));
	data->sc_size = atoi(PQgetvalue(res, 0, j++));

	for (i=0 ; i<data->sc_size; i++)
	{
		data->scl_data[i].scl_i_id = atoll(PQgetvalue(res, 0, j++));
		data->scl_data[i].scl_qty  = atoi(PQgetvalue(res, 0, j++));
		data->scl_data[i].scl_cost = atof(PQgetvalue(res, 0, j++));
		data->scl_data[i].scl_srp  = atof(PQgetvalue(res, 0, j++));
		strcpy(data->scl_data[i].i_title, PQgetvalue(res, 0, j++));
		strcpy(data->scl_data[i].i_backing, PQgetvalue(res, 0, j++));
	}


	PQclear(res);

	return OK;
}
