/*
 * pgsql_interaction_search_results.c
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

#include <libpq_interaction_search_results.h>

int
execute_search_results(struct db_context_t *dbc,
					   struct search_results_t *data)
{
	int i, j;
	PGresult *res;

	/* Generate random number for Promotional Processing. */
	data->pp_data.i_id = get_random_int(item_count) + 1;

	/* Perpare statement for Search Results interaction. */
	switch (data->search_type)
	{
		case SEARCH_AUTHOR:
			res = pgsql_execute(dbc->conn, STMT_SEARCH_RESULTS_AUTHOR,
								data->search_string,
								data->pp_data.i_id);
			break;
		case SEARCH_SUBJECT:
			res = pgsql_execute(dbc->conn, STMT_SEARCH_RESULTS_SUBJECT,
								data->search_string,
								data->pp_data.i_id);
			break;
		case SEARCH_TITLE:
			res = pgsql_execute(dbc->conn, STMT_SEARCH_RESULTS_TITLE,
								data->search_string,
								data->pp_data.i_id);
			break;
		default:
			return ERROR;
			break;
	}

	if ( PQresultStatus(res)!=PGRES_TUPLES_OK )
        {
		pgsql_error(dbc->conn);
		PQclear(res);
		return ERROR;
        }

	j = 0;
	for (i=0 ; i<PROMOTIONAL_ITEMS_MAX ; i++)
		data->pp_data.i_related[i] = atoll(PQgetvalue(res, 0, j++));

	for (i=0 ; i<PROMOTIONAL_ITEMS_MAX ; i++)
		data->pp_data.i_thumbnail[i] = atoll(PQgetvalue(res, 0, j++));

	data->items = atoi(PQgetvalue(res, 0, j++));

	for (i=0 ; i<data->items ; i++)
	{
		data->results_data[i].i_id = atoll(PQgetvalue(res, 0, j++));

		strcpy(data->results_data[i].i_title, PQgetvalue(res, 0, j++));
		strcpy(data->results_data[i].a_fname, PQgetvalue(res, 0, j++));
		strcpy(data->results_data[i].a_lname, PQgetvalue(res, 0, j++));
	}

	/* assert(PQnfields(res)==j); */

	PQclear(res);

	return OK;
}
