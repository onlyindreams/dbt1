/*
 * pgsql_interaction_best_sellers.c
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

#include <libpq_interaction_best_sellers.h>

int
execute_best_sellers(struct db_context_t *dbc,
					 struct best_sellers_t *data)
{
	int i, j;
	PGresult *res;

	data->pp_data.i_id = get_random_int(item_count) + 1;

	res = pgsql_execute(dbc->conn, STMT_BEST_SELLERS,
						data->i_subject, 
						data->pp_data.i_id);

	if ( PQresultStatus(res)!=PGRES_TUPLES_OK )
	{
		pgsql_error(dbc->conn);
		PQclear(res);
		return ERROR;
	}

	j = 0;
	for (i = 0; i < PROMOTIONAL_ITEMS_MAX; i++)
		data->pp_data.i_related[i]   = atoll(PQgetvalue(res, 0, j++));

	for (i = 0; i < PROMOTIONAL_ITEMS_MAX; i++)
		data->pp_data.i_thumbnail[i] = atoll(PQgetvalue(res, 0, j++));

	data->items = atoi(PQgetvalue(res, 0, j++));
		
	/* use data->items so that we do not need to get all the returned values */
	for (i = 0; i < data->items; i++)
	{
		data->results_data[i].i_id = atoll(PQgetvalue(res, 0, j++));
		strcpy(data->results_data[i].i_title, PQgetvalue(res, 0, j++));
		strcpy(data->results_data[i].a_fname, PQgetvalue(res, 0, j++));
		strcpy(data->results_data[i].a_lname, PQgetvalue(res, 0, j++));
	}

	// assert(PQnfields(res)==j);

	PQclear(res);

	if (data->items < 1)
	{
		return W_ZERO_ITEMS;
	}

	return OK;
}
