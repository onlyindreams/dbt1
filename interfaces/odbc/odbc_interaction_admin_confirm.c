/*
 * odbc_interaction_admin_confirm.c
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2002 Mark Wong & Jenny Zhang &
 *                    Open Source Development Lab, Inc.
 *
 * 1 march 2002
 */

#include <odbc_interaction_admin_confirm.h>
#include <odbc_interaction.h>
#include <sql.h>
#include <sqlext.h>

#ifdef PHASE1
int copy_in_admin_confirm(struct eu_context_t *euc, union odbc_data_t *odbcd)
{
	if (euc->admin_confirm_data.i_id < 1 ||
		euc->admin_confirm_data.i_id > item_count)
	{
		LOG_ERROR_MESSAGE("i_id %lld is out of range",
			euc->admin_confirm_data.i_id);
		return W_ERROR;
	}
	odbcd->admin_confirm_odbc_data.eb.i_id =
		(UDWORD) euc->admin_confirm_data.i_id;
	odbcd->admin_confirm_odbc_data.eb.i_image =
		(UDWORD) euc->admin_confirm_data.i_image;
	odbcd->admin_confirm_odbc_data.eb.i_thumbnail =
		(UDWORD) euc->admin_confirm_data.i_thumbnail;
	odbcd->admin_confirm_odbc_data.eb.i_cost = euc->admin_confirm_data.i_cost;
	return W_OK;
}

int copy_out_admin_confirm(struct eu_context_t *euc, union odbc_data_t *odbcd)
{
	euc->admin_confirm_data.i_image = odbcd->admin_confirm_odbc_data.eb.i_image;
	euc->admin_confirm_data.i_thumbnail =
		odbcd->admin_confirm_odbc_data.eb.i_thumbnail;
	euc->admin_confirm_data.i_cost = odbcd->admin_confirm_odbc_data.eb.i_cost;
	strcpy(euc->admin_confirm_data.i_title,
		odbcd->admin_confirm_odbc_data.eb.i_title);
	strcpy(euc->admin_confirm_data.a_fname,
		odbcd->admin_confirm_odbc_data.eb.a_fname);
	strcpy(euc->admin_confirm_data.a_lname,
		odbcd->admin_confirm_odbc_data.eb.a_lname);
	strcpy(euc->admin_confirm_data.i_subject,
		odbcd->admin_confirm_odbc_data.eb.i_subject);
	strcpy(euc->admin_confirm_data.i_desc,
		odbcd->admin_confirm_odbc_data.eb.i_desc);
	euc->admin_confirm_data.i_srp = odbcd->admin_confirm_odbc_data.eb.i_srp;
	strcpy(euc->admin_confirm_data.i_backing,
		odbcd->admin_confirm_odbc_data.eb.i_backing);
	euc->admin_confirm_data.i_page = odbcd->admin_confirm_odbc_data.eb.i_page;
	strcpy(euc->admin_confirm_data.i_publisher,
		odbcd->admin_confirm_odbc_data.eb.i_publisher);
	strcpy(euc->admin_confirm_data.i_pub_date,
		odbcd->admin_confirm_odbc_data.eb.i_pub_date);
	strcpy(euc->admin_confirm_data.i_dimensions,
		odbcd->admin_confirm_odbc_data.eb.i_dimensions);
	strcpy(euc->admin_confirm_data.i_isbn,
		odbcd->admin_confirm_odbc_data.eb.i_isbn);

	return W_OK;
}
#endif /* PHASE1*/

int execute_admin_confirm(struct odbc_context_t *odbcc, union odbc_data_t *odbcd)
{
	SQLRETURN rc;
	int i, j;

	/* Perpare statement for Admin Confirm interaction. */
	rc = SQLPrepare(odbcc->hstmt, STMT_ADMIN_CONFIRM, SQL_NTS);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}

	/* Bind variables for Admin Confirm interaction. */
	j = 1;
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_INPUT, SQL_C_ULONG, SQL_INTEGER, 0, 0,
		&odbcd->admin_confirm_odbc_data.eb.i_id, 0, NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}

	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_INPUT_OUTPUT, SQL_C_ULONG, SQL_INTEGER, 0, 0,
		&odbcd->admin_confirm_odbc_data.eb.i_image, 0, NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_INPUT_OUTPUT, SQL_C_ULONG, SQL_INTEGER, 0, 0,
		&odbcd->admin_confirm_odbc_data.eb.i_thumbnail, 0, NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_INPUT_OUTPUT, SQL_C_DOUBLE, SQL_DOUBLE, 0, 0,
		&odbcd->admin_confirm_odbc_data.eb.i_cost, 0, NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}

	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR,
		0, 0, odbcd->admin_confirm_odbc_data.eb.i_title,
		sizeof(odbcd->admin_confirm_odbc_data.eb.i_title), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		odbcd->admin_confirm_odbc_data.eb.a_fname,
		sizeof(odbcd->admin_confirm_odbc_data.eb.a_fname), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		odbcd->admin_confirm_odbc_data.eb.a_lname,
		sizeof(odbcd->admin_confirm_odbc_data.eb.a_lname), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		odbcd->admin_confirm_odbc_data.eb.i_subject,
		sizeof(odbcd->admin_confirm_odbc_data.eb.i_subject), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		odbcd->admin_confirm_odbc_data.eb.i_desc,
		sizeof(odbcd->admin_confirm_odbc_data.eb.i_desc), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_OUTPUT, SQL_C_DOUBLE, SQL_DOUBLE, 0, 0,
		&odbcd->admin_confirm_odbc_data.eb.i_srp, 0, NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		odbcd->admin_confirm_odbc_data.eb.i_backing,
		sizeof(odbcd->admin_confirm_odbc_data.eb.i_backing), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_OUTPUT, SQL_C_SSHORT, SQL_SMALLINT, 0, 0,
		&odbcd->admin_confirm_odbc_data.eb.i_page, 0, NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		odbcd->admin_confirm_odbc_data.eb.i_publisher,
		sizeof(odbcd->admin_confirm_odbc_data.eb.i_publisher), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		odbcd->admin_confirm_odbc_data.eb.i_pub_date,
		sizeof(odbcd->admin_confirm_odbc_data.eb.i_pub_date), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		odbcd->admin_confirm_odbc_data.eb.i_dimensions,
		sizeof(odbcd->admin_confirm_odbc_data.eb.i_dimensions), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		odbcd->admin_confirm_odbc_data.eb.i_isbn,
		sizeof(odbcd->admin_confirm_odbc_data.eb.i_isbn), NULL);
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
		rc = SQLPrepare(odbcc->hstmt, COMMIT, SQL_NTS);
	}
	else
	{
		/* Rollback. */
		rc = SQLPrepare(odbcc->hstmt, ROLLBACK, SQL_NTS);
	}
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}
	rc = SQLExecute(odbcc->hstmt);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}
#endif

	return W_OK;
}
