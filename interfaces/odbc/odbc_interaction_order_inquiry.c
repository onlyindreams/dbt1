/*
 * odbc_interaction_order_inquiry.c
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2002 Mark Wong & Jenny Zhang &
 *                    Open Source Development Lab, Inc.
 *
 * 28 february 2002
 */

#include <odbc_interaction_order_inquiry.h>
#include <odbc_interaction.h>
#include <sql.h>
#include <sqlext.h>

#ifdef PHASE1
int copy_in_order_inquiry(struct eu_context_t *euc, union odbc_data_t *odbcd)
{
	odbcd->order_inquiry_odbc_data.eb.c_id = euc->order_inquiry_data.c_id;
	return OK;
}

int copy_out_order_inquiry(struct eu_context_t *euc, union odbc_data_t *odbcd)
{
	strcpy(euc->order_inquiry_data.c_uname, odbcd->order_inquiry_odbc_data.eb.c_uname);
	return OK;
}
#endif /* PHASE1*/

int execute_order_inquiry(struct odbc_context_t *odbcc, union odbc_data_t *odbcd)
{
	SQLRETURN rc;
	int j;

	/* Perpare statement for Order Inquiry interaction. */
	rc = SQLPrepare(odbcc->hstmt, STMT_ORDER_INQUIRY, SQL_NTS);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}

	/* Bind variables for OrderInquiry interaction. */
	j = 1;
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_INPUT, SQL_C_ULONG, SQL_INTEGER,
		0, 0, &odbcd->order_inquiry_odbc_data.eb.c_id, 0, NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR,
		0, 0, odbcd->order_inquiry_odbc_data.eb.c_uname,
		sizeof(odbcd->order_inquiry_odbc_data.eb.c_uname), NULL);
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
#ifndef AUTOCOMMIT_OFF
		return W_ERROR;
#endif
	}

#ifdef AUTOCOMMIT_OFF
	if (rc == SQL_SUCCESS)
	{
		/* Commit. */
		rc = SQLEndTran(SQL_HANDLE_DBC, odbcc->hdbc, SQL_COMMIT);
	}
	else
	{
		/* Rollback. */
		rc = SQLEndTran(SQL_HANDLE_DBC, odbcc->hdbc, SQL_ROLLBACK);
	}
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_DBC, odbcc->hdbc);
		return W_ERROR;
	}
#endif

	return OK;
}
