/*
 * pgsql_interaction_admin_confirm.c
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

#include <libpq_interaction_admin_confirm.h>

int
execute_admin_confirm(struct db_context_t *dbc,
					  struct admin_confirm_t *data)
{
	PGresult *res;
	int j;

	res = pgsql_execute(dbc->conn, STMT_ADMIN_CONFIRM, data->i_id,
					data->i_image, data->i_thumbnail, 
					data->i_cost);

	if ( PQresultStatus(res)!=PGRES_TUPLES_OK )
	{
		pgsql_error(dbc->conn);
		PQclear(res);
		return ERROR;
	}

	j = 0;
	data->i_image     = atoll( PQgetvalue(res, 0, j++) );
	data->i_thumbnail = atoll( PQgetvalue(res, 0, j++) );
	data->i_cost      = atof( PQgetvalue(res, 0, j++) );
	strcpy(data->i_title, PQgetvalue(res, 0, j++));
	strcpy(data->a_fname, PQgetvalue(res, 0, j++));
	strcpy(data->a_lname, PQgetvalue(res, 0, j++));
	strcpy(data->i_subject, PQgetvalue(res, 0, j++));
	strcpy(data->i_desc, PQgetvalue(res, 0, j++));
	data->i_srp = atof( PQgetvalue(res, 0, j++) );
	strcpy(data->i_backing, PQgetvalue(res, 0, j++));
	data->i_page = atoi( PQgetvalue(res, 0, j++) );
	strcpy(data->i_publisher, PQgetvalue(res, 0, j++));
	strcpy(data->i_pub_date, PQgetvalue(res, 0, j++));
	strcpy(data->i_dimensions, PQgetvalue(res, 0, j++));
	strcpy(data->i_isbn, PQgetvalue(res, 0, j++));

	assert(PQnfields(res)==j);

	PQclear(res);

	return OK;
}
