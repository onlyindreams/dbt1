/*
 * odbc_interaction_admin_request.c
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2002 Mark Wong & Jenny Zhang &
 *                    Open Source Development Lab, Inc.
 *
 * 28 february 2002
 */

#include <stdio.h>
#include <odbc_interaction_admin_request.h>
#include <odbc_interaction.h>
#include <sql.h>
#include <sqlext.h>

#ifdef PHASE1
int copy_in_admin_request(struct eu_context_t *euc, union odbc_data_t *odbcd)
{
	if (euc->admin_request_data.i_id < (long long) 1 ||
		euc->admin_request_data.i_id > (long long) item_count)
	{
		LOG_ERROR_MESSAGE("i_id %lld is out of range\n",
			euc->admin_request_data.i_id);
		return W_ERROR;
	}
	odbcd->admin_request_odbc_data.eb.i_id =
		(UDWORD) euc->admin_request_data.i_id;
	return W_OK;
}

int copy_out_admin_request(struct eu_context_t *euc, union odbc_data_t *odbcd)
{
	strcpy(euc->admin_request_data.a_fname,
		odbcd->admin_request_odbc_data.eb.a_fname);
	strcpy(euc->admin_request_data.a_lname,
		odbcd->admin_request_odbc_data.eb.a_lname);
	strcpy(euc->admin_request_data.i_title,
		odbcd->admin_request_odbc_data.eb.i_title);
	euc->admin_request_data.i_srp = odbcd->admin_request_odbc_data.eb.i_srp;
	euc->admin_request_data.i_cost = odbcd->admin_request_odbc_data.eb.i_cost;
	euc->admin_request_data.i_image = odbcd->admin_request_odbc_data.eb.i_image;
	euc->admin_request_data.i_thumbnail =
		odbcd->admin_request_odbc_data.eb.i_thumbnail;
	return W_OK;
}
#endif /* PHASE1*/

int execute_admin_request(struct odbc_context_t *odbcc, union odbc_data_t *odbcd)
{
	SQLRETURN rc;
	int j;

	/* Perpare statement for Admin Request interaction. */
	rc = SQLPrepare(odbcc->hstmt, STMT_ADMIN_REQUEST, SQL_NTS);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}

	/* Bind variables for Admin Request interaction. */
	j = 1;
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_INPUT, SQL_C_ULONG, SQL_INTEGER, 0, 0,
		&odbcd->admin_request_odbc_data.eb.i_id, 0, NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}

	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_OUTPUT, SQL_C_DOUBLE, SQL_DOUBLE, 0, 0,
		&odbcd->admin_request_odbc_data.eb.i_srp, 0, NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_OUTPUT, SQL_C_DOUBLE, SQL_DOUBLE, 0, 0,
		&odbcd->admin_request_odbc_data.eb.i_cost, 0, NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR,
		0, 0, odbcd->admin_request_odbc_data.eb.i_title,
		sizeof(odbcd->admin_request_odbc_data.eb.i_title), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_OUTPUT, SQL_C_ULONG, SQL_INTEGER, 0, 0,
		&odbcd->admin_request_odbc_data.eb.i_image, 0, NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_OUTPUT, SQL_C_ULONG, SQL_INTEGER, 0, 0,
		&odbcd->admin_request_odbc_data.eb.i_thumbnail, 0, NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		odbcd->admin_request_odbc_data.eb.a_fname,
		sizeof(odbcd->admin_request_odbc_data.eb.a_fname), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		odbcd->admin_request_odbc_data.eb.a_lname,
		sizeof(odbcd->admin_request_odbc_data.eb.a_lname), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}

	/* Execute stored procedure. */
	rc = SQLExecute(odbcc->hstmt);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}

	return W_OK;
}
