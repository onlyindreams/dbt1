/*
 * pgsql_interaction_order_inquiry.c
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

#include <libpq_interaction_order_inquiry.h>

int
execute_order_inquiry(struct db_context_t *dbc,
					  struct order_inquiry_t *data)
{
	int j;
	PGresult *res;

	res = pgsql_execute(dbc->conn, STMT_ORDER_INQUIRY,
						data->c_id);

	if ( PQresultStatus(res)!=PGRES_TUPLES_OK )
	{
		pgsql_error(dbc->conn);
		PQclear(res);
		return ERROR;
	}

	j = 0;
	strcpy(data->c_uname, PQgetvalue(res, 0, j++));

	assert(PQnfields(res)==j);

	PQclear(res);

//	print_order_inquiry_data(data);

	return OK;
}
