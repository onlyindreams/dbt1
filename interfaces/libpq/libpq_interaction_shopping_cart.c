/*
 * pgsql_interaction_shopping_cart.c
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2002 Open Source Development Lab, Inc.
 * History:
 * Feb-2002: Created by Mark Wong & Jenny Zhang &
 * July-2003: Ported to PostgreSQL by
 *            Satoshi Nagayasu & Hideyuki Kawashima &
 *                    Sachi Osawa & Hirokazu Kondo & Satoru Satake
 * Aug-2003: tested and fixed, removed using temporary table, instead
 *		changed pg_config.h.in #define INDEX_MAX_KEYS 64 by Jenny Zhang
 * $Id$
 */

#include <libpq_interaction_shopping_cart.h>

int
execute_shopping_cart(struct db_context_t *dbc, struct shopping_cart_t *data)
{
	int i, j;
	PGresult *res;

	/* generate random item if add_flag == FALSE and empty (i_id, qty) pair */
        if (data->sc_size == 0 && data->add_flag == FALSE)
        {
                data->i_id = get_random_int(item_count) + 1;
        }
        /* Generate random number for Promotional Processing. */
        data->pp_data.i_id = get_random_int(item_count) + 1;

	/*
	 * call shopping_cart()
	 */
	res = pgsql_execute(dbc->conn, STMT_SC, data->c_id, data->sc_id,
					data->sc_size, data->add_flag, data->i_id,
					data->pp_data.i_id,
					data->sc_refresh[0].scl_i_id, data->sc_refresh[0].scl_qty,
					data->sc_refresh[1].scl_i_id, data->sc_refresh[1].scl_qty,
					data->sc_refresh[2].scl_i_id, data->sc_refresh[2].scl_qty,
					data->sc_refresh[3].scl_i_id, data->sc_refresh[3].scl_qty,
					data->sc_refresh[4].scl_i_id, data->sc_refresh[4].scl_qty,
					data->sc_refresh[5].scl_i_id, data->sc_refresh[5].scl_qty,
					data->sc_refresh[6].scl_i_id, data->sc_refresh[6].scl_qty,
					data->sc_refresh[7].scl_i_id, data->sc_refresh[7].scl_qty,
					data->sc_refresh[8].scl_i_id, data->sc_refresh[8].scl_qty,
					data->sc_refresh[9].scl_i_id, data->sc_refresh[9].scl_qty,
					data->sc_refresh[10].scl_i_id, data->sc_refresh[10].scl_qty,
					data->sc_refresh[11].scl_i_id, data->sc_refresh[11].scl_qty,
					data->sc_refresh[12].scl_i_id, data->sc_refresh[12].scl_qty,
					data->sc_refresh[13].scl_i_id, data->sc_refresh[13].scl_qty,
					data->sc_refresh[14].scl_i_id, data->sc_refresh[14].scl_qty,
					data->sc_refresh[15].scl_i_id, data->sc_refresh[15].scl_qty,
					data->sc_refresh[16].scl_i_id, data->sc_refresh[16].scl_qty,
					data->sc_refresh[17].scl_i_id, data->sc_refresh[17].scl_qty,
					data->sc_refresh[18].scl_i_id, data->sc_refresh[18].scl_qty,
					data->sc_refresh[19].scl_i_id, data->sc_refresh[19].scl_qty
);

	if ( PQresultStatus(res)!=PGRES_TUPLES_OK )
	{
		pgsql_error(dbc->conn);
		PQclear(res);
		return ERROR;
	}
	/* We don't have ARGshopping_cart here. */

	j = 0;
	data->sc_id   = atoll(PQgetvalue(res, 0, j++));
	data->sc_size = atoi(PQgetvalue(res, 0, j++));

	for (i=0 ; i<PROMOTIONAL_ITEMS_MAX ; i++)
	{
		data->pp_data.i_related[i]   = atoll(PQgetvalue(res, 0, j++));
		data->pp_data.i_thumbnail[i] = atoll(PQgetvalue(res, 0, j++));
	}

	for (i=0 ; i<data->sc_size; i++)
	{
		data->scl_data[i].scl_i_id = atoll(PQgetvalue(res, 0, j++));
		strcpy(data->scl_data[i].i_title, PQgetvalue(res, 0, j++));
		data->scl_data[i].scl_cost = atof(PQgetvalue(res, 0, j++));
		data->scl_data[i].scl_srp  = atof(PQgetvalue(res, 0, j++));
		strcpy(data->scl_data[i].i_backing, PQgetvalue(res, 0, j++));
		data->scl_data[i].scl_qty  = atoi(PQgetvalue(res, 0, j++));
	}

	/* assert(PQnfields(res)==j); */

	PQclear(res);

	return OK;
}
