/*
 * pgsql_interaction_admin_request.c
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

#include <stdlib.h>
#include <string.h>

#include <libpq_interaction_admin_request.h>

int
execute_admin_request(struct db_context_t *dbc, struct admin_request_t *data)
{
	PGresult *res;
	int j;

	res = pgsql_execute(dbc->conn, STMT_ADMIN_REQUEST, data->i_id);

	if ( PQresultStatus(res)!=PGRES_TUPLES_OK )
	{
		pgsql_error(dbc->conn);
		PQclear(res);
		return ERROR;
	}

	j = 0;
	data->i_srp       = atof( PQgetvalue(res, 0, j++) );
	data->i_cost      = atof( PQgetvalue(res, 0, j++) );
	strcpy(data->i_title, PQgetvalue(res, 0, j++));
	data->i_image     = atol( PQgetvalue(res, 0, j++) );
	data->i_thumbnail = atol( PQgetvalue(res, 0, j++) );
	strcpy(data->a_fname, PQgetvalue(res, 0, j++));
	strcpy(data->a_lname, PQgetvalue(res, 0, j++));

	assert(PQnfields(res)==j);

	PQclear(res);

	return OK;
}
