/*
 * odbc_interaction_search_results.c
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2002 Mark Wong & Jenny Zhang &
 *                    Open Source Development Lab, Inc.
 *
 * 26 february 2002
 */

#include <odbc_interaction_search_results.h>
#include <odbc_interaction.h>
#include <sql.h>
#include <sqlext.h>

#ifdef PHASE1
int copy_in_search_results(struct eu_context_t *euc, union odbc_data_t *odbcd)
{
	odbcd->search_results_odbc_data.eb.search_type = 
		euc->search_results_data.search_type;
	strcpy(odbcd->search_results_odbc_data.eb.search_string,
		euc->search_results_data.search_string);
	return W_OK;
}

int copy_out_search_results(struct eu_context_t *euc, union odbc_data_t *odbcd)
{
	int i;

	for (i = 0; i < PROMOTIONAL_ITEMS_MAX; i++)
	{
		euc->search_results_data.pp_data.i_related[i] =
			odbcd->search_results_odbc_data.eb.pp_data.i_related[i];
		euc->search_results_data.pp_data.i_thumbnail[i] =
			odbcd->search_results_odbc_data.eb.pp_data.i_thumbnail[i];
	}
	euc->search_results_data.items =
		odbcd->search_results_odbc_data.eb.items;
	for (i = 0; i < odbcd->search_results_odbc_data.eb.items; i++)
	{
		euc->search_results_data.results_data[i].i_id =
			odbcd->search_results_odbc_data.eb.results_data[i].i_id;
		strcpy(euc->search_results_data.results_data[i].i_title,
			odbcd->search_results_odbc_data.eb.results_data[i].i_title);
		strcpy(euc->search_results_data.results_data[i].a_fname,
			odbcd->search_results_odbc_data.eb.results_data[i].a_fname);
		strcpy(euc->search_results_data.results_data[i].a_lname,
			odbcd->search_results_odbc_data.eb.results_data[i].a_lname);
	}
	return W_OK;
}
#endif /* PHASE1 */

int execute_search_results(struct odbc_context_t *odbcc,
	union odbc_data_t *odbcd)
{
	SQLRETURN rc;
	int i, j;

	/* Perpare statement for Search Results interaction. */
	switch (odbcd->search_results_odbc_data.eb.search_type)
	{
		case SEARCH_AUTHOR:
			rc = SQLPrepare(odbcc->hstmt, STMT_SEARCH_RESULTS_AUTHOR, SQL_NTS);
			break;
		case SEARCH_SUBJECT:
			rc = SQLPrepare(odbcc->hstmt, STMT_SEARCH_RESULTS_SUBJECT, SQL_NTS);
			break;
		case SEARCH_TITLE:
			rc = SQLPrepare(odbcc->hstmt, STMT_SEARCH_RESULTS_TITLE, SQL_NTS);
			break;
		default:
			return W_ERROR;
			break;
	}
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}

	/* Bind variables for Search Results interaction. */
	i = 1;
	rc = SQLBindParameter(odbcc->hstmt,
		i++, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		odbcd->search_results_odbc_data.eb.search_string,
		sizeof(odbcd->search_results_odbc_data.eb.search_string), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}

	rc = SQLBindParameter(odbcc->hstmt,
		i++, SQL_PARAM_INPUT, SQL_C_ULONG, SQL_INTEGER, 0, 0,
		&odbcd->search_results_odbc_data.eb.pp_data.i_id, 0, NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}
	for (j = 0; j < PROMOTIONAL_ITEMS_MAX; j++)
	{
		rc = SQLBindParameter(odbcc->hstmt,
			i++, SQL_PARAM_OUTPUT, SQL_C_ULONG, SQL_INTEGER, 0, 0,
			&odbcd->search_results_odbc_data.eb.pp_data.i_related[j], 0,
			NULL);
		if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
		{
			LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			return W_ERROR;
		}
		rc = SQLBindParameter(odbcc->hstmt,
			i++, SQL_PARAM_OUTPUT, SQL_C_ULONG, SQL_INTEGER, 0, 0,
			&odbcd->search_results_odbc_data.eb.pp_data.i_thumbnail[j], 0,
			NULL);
		if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
		{
			LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			return W_ERROR;
		}
	}

	rc = SQLBindParameter(odbcc->hstmt,
		i++, SQL_PARAM_OUTPUT, SQL_C_SSHORT, SQL_SMALLINT, 0, 0,
		&odbcd->search_results_odbc_data.eb.items, 0, NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}
	for (j = 0; j < SEARCH_RESULT_ITEMS_MAX; j++)
	{
		rc = SQLBindParameter(odbcc->hstmt,
			i++, SQL_PARAM_OUTPUT, SQL_C_ULONG, SQL_INTEGER, 0, 0,
			&odbcd->search_results_odbc_data.eb.results_data[j].i_id, 0, NULL);
		if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
		{
			LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			return W_ERROR;
		}
		rc = SQLBindParameter(odbcc->hstmt,
			i++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
			odbcd->search_results_odbc_data.eb.results_data[j].i_title,
			sizeof(odbcd->search_results_odbc_data.eb.results_data[j].i_title),
			NULL);
		if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
		{
			LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			return W_ERROR;
		}
		rc = SQLBindParameter(odbcc->hstmt,
			i++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
			odbcd->search_results_odbc_data.eb.results_data[j].a_fname,
			sizeof(odbcd->search_results_odbc_data.eb.results_data[j].a_fname),
			NULL);
		if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
		{
			LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			return W_ERROR;
		}
		rc = SQLBindParameter(odbcc->hstmt,
			i++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
			odbcd->search_results_odbc_data.eb.results_data[j].a_lname,
			sizeof(odbcd->search_results_odbc_data.eb.results_data[j].a_lname),
			NULL);
		if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
		{
			LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			return W_ERROR;
		}
	}

	/* Generate random number for Promotional Processing. */
	odbcd->search_results_odbc_data.eb.pp_data.i_id =
		(UDWORD) get_random((long long) item_count) + 1;

	/* Execute stored procedure. */
	rc = SQLExecute(odbcc->hstmt);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}

	return W_OK;
}
