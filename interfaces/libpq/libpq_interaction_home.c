/*
 * pgsql_interaction_home.c
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

#include <libpq_interaction_home.h>

int
execute_home(struct db_context_t *dbc, struct home_t *data)
{
	int i, j;
	PGresult *res;

	data->pp_data.i_id = get_random_int(item_count) + 1;

	res = pgsql_execute(dbc->conn, STMT_HOME,
						data->c_id,
						data->pp_data.i_id);

	if ( PQresultStatus(res)!=PGRES_TUPLES_OK )
	{
		pgsql_error(dbc->conn);
		PQclear(res);
		return ERROR;
	}

	j = 0;
	strcpy(data->c_fname, PQgetvalue(res, 0, j++));
	strcpy(data->c_lname, PQgetvalue(res, 0, j++));

	for (i = 0; i < PROMOTIONAL_ITEMS_MAX; i++)
	{
		data->pp_data.i_related[i]   = atoll(PQgetvalue(res, 0, j++));
		data->pp_data.i_thumbnail[i] = atoll(PQgetvalue(res, 0, j++));
	}

	assert(PQnfields(res)==j);

	PQclear(res);

	return OK;
}
