/*
 * odbc_interaction_best_sellers.c
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2002 Mark Wong & Jenny Zhang &
 *                    Open Source Development Lab, Inc.
 *
 * 21 february 2002
 */

#include <odbc_interaction_best_sellers.h>
#include <odbc_interaction.h>
#include <sql.h>
#include <sqlext.h>

#ifdef PHASE1
int copy_in_best_sellers(struct eu_context_t *euc, union odbc_data_t *odbcd)
{
	strcpy(odbcd->best_sellers_odbc_data.eb.i_subject,
		euc->best_sellers_data.i_subject);

	return W_OK;
}

int copy_out_best_sellers(struct eu_context_t *euc, union odbc_data_t *odbcd)
{
	int i;

	for (i = 0; i < PROMOTIONAL_ITEMS_MAX; i++)
	{
		euc->best_sellers_data.pp_data.i_related[i] =
			odbcd->best_sellers_odbc_data.eb.pp_data.i_related[i];
		euc->best_sellers_data.pp_data.i_thumbnail[i] =
			odbcd->best_sellers_odbc_data.eb.pp_data.i_thumbnail[i];
	}
	euc->best_sellers_data.items =
		odbcd->best_sellers_odbc_data.eb.items;
	for (i = 0; i < odbcd->best_sellers_odbc_data.eb.items; i++)
	{
		euc->best_sellers_data.results_data[i].i_id =
			odbcd->best_sellers_odbc_data.eb.results_data[i].i_id;
		strcpy(euc->best_sellers_data.results_data[i].i_title,
			odbcd->best_sellers_odbc_data.eb.results_data[i].i_title);
		strcpy(euc->best_sellers_data.results_data[i].a_fname,
			odbcd->best_sellers_odbc_data.eb.results_data[i].a_fname);
		strcpy(euc->best_sellers_data.results_data[i].a_lname,
			odbcd->best_sellers_odbc_data.eb.results_data[i].a_lname);
	}
	return W_OK;
}
#endif /* PHASE1 */

int execute_best_sellers(struct odbc_context_t *odbcc, union odbc_data_t *odbcd)
{
	SQLRETURN rc;
	int i, j;

	/* Perpare statement for Best Sellers interaction. */
	rc = SQLPrepare(odbcc->hstmt, STMT_BEST_SELLERS, SQL_NTS);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}

	/* Bind variables for Best Sellers interaction. */
	i = 1;
	rc = SQLBindParameter(odbcc->hstmt,
		i++, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		odbcd->best_sellers_odbc_data.eb.i_subject,
		sizeof(odbcd->best_sellers_odbc_data.eb.i_subject), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}

	rc = SQLBindParameter(odbcc->hstmt,
		i++, SQL_PARAM_INPUT, SQL_C_ULONG, SQL_INTEGER, 0, 0,
		&odbcd->best_sellers_odbc_data.eb.pp_data.i_id, 0, NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}
	for (j = 0; j < PROMOTIONAL_ITEMS_MAX; j++)
	{
		rc = SQLBindParameter(odbcc->hstmt,
			i++, SQL_PARAM_OUTPUT, SQL_C_ULONG, SQL_INTEGER, 0, 0,
			&odbcd->best_sellers_odbc_data.eb.pp_data.i_related[j], 0,
			NULL);
		if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
		{
			LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			return W_ERROR;
		}
		rc = SQLBindParameter(odbcc->hstmt,
			i++, SQL_PARAM_OUTPUT, SQL_C_ULONG, SQL_INTEGER, 0, 0,
			&odbcd->best_sellers_odbc_data.eb.pp_data.i_thumbnail[j], 0,
			NULL);
		if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
		{
			LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			return W_ERROR;
		}
	}

	rc = SQLBindParameter(odbcc->hstmt,
		i++, SQL_PARAM_OUTPUT, SQL_C_SSHORT, SQL_SMALLINT, 0, 0,
		&odbcd->best_sellers_odbc_data.eb.items, 0, NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}
	for (j = 0; j < SEARCH_RESULT_ITEMS_MAX; j++)
	{
		rc = SQLBindParameter(odbcc->hstmt,
			i++, SQL_PARAM_OUTPUT, SQL_C_ULONG, SQL_INTEGER, 0, 0,
			&odbcd->best_sellers_odbc_data.eb.results_data[j].i_id, 0, NULL);
		if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
		{
			LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			return W_ERROR;
		}
		rc = SQLBindParameter(odbcc->hstmt,
			i++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
			odbcd->best_sellers_odbc_data.eb.results_data[j].i_title,
			sizeof(odbcd->best_sellers_odbc_data.eb.results_data[j].i_title),
			NULL);
		if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
		{
			LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			return W_ERROR;
		}
		rc = SQLBindParameter(odbcc->hstmt,
			i++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
			odbcd->best_sellers_odbc_data.eb.results_data[j].a_fname,
			sizeof(odbcd->best_sellers_odbc_data.eb.results_data[j].a_fname),
			NULL);
		if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
		{
			LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			return W_ERROR;
		}
		rc = SQLBindParameter(odbcc->hstmt,
			i++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
			odbcd->best_sellers_odbc_data.eb.results_data[j].a_lname,
			sizeof(odbcd->best_sellers_odbc_data.eb.results_data[j].a_lname),
			NULL);
		if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
		{
			LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			return W_ERROR;
		}
	}

	/* Generate random number for Promotional Processing. */
	odbcd->best_sellers_odbc_data.eb.pp_data.i_id =
		(UDWORD) get_random((long long) item_count) + 1;

	/* Execute stored procedure. */
	rc = SQLExecute(odbcc->hstmt);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}

	if (odbcd->best_sellers_odbc_data.eb.items < 1)
	{
		return W_ZERO_ITEMS;
	}
	return W_OK;
}
