/*
 * pgsql_interaction_product_detail.c
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

#include <libpq_interaction_product_detail.h>

int
execute_product_detail(struct db_context_t *dbc,
					   struct product_detail_t *data)
{
	int j;
	PGresult *res;

	res = pgsql_execute(dbc->conn, STMT_PRODUCT_DETAIL, data->i_id);

	if ( PQresultStatus(res)!=PGRES_TUPLES_OK )
	{
		pgsql_error(dbc->conn);
		PQclear(res);
		return ERROR;
	}

	j = 0;
	strcpy(data->i_title, PQgetvalue(res, 0, j++));
	strcpy(data->a_fname, PQgetvalue(res, 0, j++));
	strcpy(data->a_lname, PQgetvalue(res, 0, j++));
	strcpy(data->i_pub_date, PQgetvalue(res, 0, j++));
	strcpy(data->i_publisher, PQgetvalue(res, 0, j++));
	strcpy(data->i_subject, PQgetvalue(res, 0, j++));
	strcpy(data->i_desc, PQgetvalue(res, 0, j++));
	data->i_image     = atol( PQgetvalue(res, 0, j++) );
	data->i_cost      = atof( PQgetvalue(res, 0, j++) );
	data->i_srp = atof( PQgetvalue(res, 0, j++) );
	strcpy(data->i_avail, PQgetvalue(res, 0, j++));
	strcpy(data->i_isbn, PQgetvalue(res, 0, j++));
	data->i_page = atoi( PQgetvalue(res, 0, j++) );
	strcpy(data->i_backing, PQgetvalue(res, 0, j++));
	strcpy(data->i_dimensions, PQgetvalue(res, 0, j++));

	assert(PQnfields(res)==j);

	PQclear(res);

	return OK;
}
