/*
 * odbc_interaction_new_products.c
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2002 Mark Wong & Jenny Zhang &
 *                    Open Source Development Lab, Inc.
 *
 * 21 february 2002
 */

#include <odbc_interaction_new_products.h>
#include <odbc_interaction.h>
#include <sql.h>
#include <sqlext.h>

#ifdef PHASE1
int copy_in_new_products(struct eu_context_t *euc, union odbc_data_t *odbcd)
{
	strcpy(odbcd->new_products_odbc_data.eb.i_subject,
		euc->new_products_data.i_subject);

	return W_OK;
}

int copy_out_new_products(struct eu_context_t *euc, union odbc_data_t *odbcd)
{
	int i;

	for (i = 0; i < PROMOTIONAL_ITEMS_MAX; i++)
	{
		euc->new_products_data.pp_data.i_related[i] =
			odbcd->new_products_odbc_data.eb.pp_data.i_related[i];
		euc->new_products_data.pp_data.i_thumbnail[i] =
			odbcd->new_products_odbc_data.eb.pp_data.i_thumbnail[i];
	}
	euc->new_products_data.items =
		odbcd->new_products_odbc_data.eb.items;
	for (i = 0; i < odbcd->new_products_odbc_data.eb.items; i++)
	{
		euc->new_products_data.results_data[i].i_id =
			odbcd->new_products_odbc_data.eb.results_data[i].i_id;
		strcpy(euc->new_products_data.results_data[i].i_title,
			odbcd->new_products_odbc_data.eb.results_data[i].i_title);
		strcpy(euc->new_products_data.results_data[i].a_fname,
			odbcd->new_products_odbc_data.eb.results_data[i].a_fname);
		strcpy(euc->new_products_data.results_data[i].a_lname,
			odbcd->new_products_odbc_data.eb.results_data[i].a_lname);
	}
	return W_OK;
}
#endif /* PHASE1 */

int execute_new_products(struct odbc_context_t *odbcc, union odbc_data_t *odbcd)
{
	SQLRETURN rc;
	int i, j;

	/* Perpare statement for New Products interaction. */
	rc = SQLPrepare(odbcc->hstmt, STMT_NEW_PRODUCTS, SQL_NTS);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}

	/* Bind variables for New Products interaction. */
	i = 1;
	rc = SQLBindParameter(odbcc->hstmt,
		i++, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		odbcd->new_products_odbc_data.eb.i_subject,
		sizeof(odbcd->new_products_odbc_data.eb.i_subject), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}

	rc = SQLBindParameter(odbcc->hstmt,
		i++, SQL_PARAM_INPUT, SQL_C_ULONG, SQL_INTEGER, 0, 0,
		&odbcd->new_products_odbc_data.eb.pp_data.i_id, 0, NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}
	for (j = 0; j < PROMOTIONAL_ITEMS_MAX; j++)
	{
		rc = SQLBindParameter(odbcc->hstmt,
			i++, SQL_PARAM_OUTPUT, SQL_C_ULONG, SQL_INTEGER, 0, 0,
			&odbcd->new_products_odbc_data.eb.pp_data.i_related[j], 0,
			NULL);
		if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
		{
			LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			return W_ERROR;
		}
		rc = SQLBindParameter(odbcc->hstmt,
			i++, SQL_PARAM_OUTPUT, SQL_C_ULONG, SQL_INTEGER, 0, 0,
			&odbcd->new_products_odbc_data.eb.pp_data.i_thumbnail[j], 0,
			NULL);
		if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
		{
			LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			return W_ERROR;
		}
	}

	rc = SQLBindParameter(odbcc->hstmt,
		i++, SQL_PARAM_OUTPUT, SQL_C_SSHORT, SQL_SMALLINT, 0, 0,
		&odbcd->new_products_odbc_data.eb.items, 0, NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}
	for (j = 0; j < SEARCH_RESULT_ITEMS_MAX; j++)
	{
		rc = SQLBindParameter(odbcc->hstmt,
			i++, SQL_PARAM_OUTPUT, SQL_C_ULONG, SQL_INTEGER, 0, 0,
			&odbcd->new_products_odbc_data.eb.results_data[j].i_id, 0, NULL);
		if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
		{
			LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			return W_ERROR;
		}
		rc = SQLBindParameter(odbcc->hstmt,
			i++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
			odbcd->new_products_odbc_data.eb.results_data[j].i_title,
			sizeof(odbcd->new_products_odbc_data.eb.results_data[j].i_title),
			NULL);
		if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
		{
			LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			return W_ERROR;
		}
		rc = SQLBindParameter(odbcc->hstmt,
			i++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
			odbcd->new_products_odbc_data.eb.results_data[j].a_fname,
			sizeof(odbcd->new_products_odbc_data.eb.results_data[j].a_fname),
			NULL);
		if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
		{
			LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			return W_ERROR;
		}
		rc = SQLBindParameter(odbcc->hstmt,
			i++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
			odbcd->new_products_odbc_data.eb.results_data[j].a_lname,
			sizeof(odbcd->new_products_odbc_data.eb.results_data[j].a_lname),
			NULL);
		if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
		{
			LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			return W_ERROR;
		}
	}

	/* Generate random number for Promotional Processing. */
	odbcd->new_products_odbc_data.eb.pp_data.i_id =
		(UDWORD) get_random((long long) item_count) + 1;

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

	if (odbcd->new_products_odbc_data.eb.items < 1)
	{
		return W_ZERO_ITEMS;
	}
	return W_OK;
}
