/*
 * odbc_interaction_search_request.c
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2002 Mark Wong & Jenny Zhang &
 *                    Open Source Development Lab, Inc.
 *
 * 28 february 2002
 */

#include <odbc_interaction_search_request.h>
#include <sql.h>
#include <sqlext.h>

#ifdef PHASE1
#include <odbc_interaction.h>
#define SEARCH_REQUEST_ODBC_DATA search_request_odbc_data
#endif /* PHASE1 */

#ifdef PHASE2
#include <app_interaction.h>
#define SEARCH_REQUEST_ODBC_DATA search_request_odbc_data.eb
#endif /* PHASE2 */

#ifdef PHASE1
int copy_out_search_request(struct eu_context_t *euc, union odbc_data_t *odbcd)
{
	int i;

	for (i = 0; i < PROMOTIONAL_ITEMS_MAX; i++)
	{
		euc->search_request_data.pp_data.i_related[i] =
			(long long) odbcd->search_request_odbc_data.pp_data.i_related[i];
		euc->search_request_data.pp_data.i_thumbnail[i] =
			(long long) odbcd->search_request_odbc_data.pp_data.i_thumbnail[i];
	}
	return W_OK;
}
#endif /* PHASE1*/

int execute_search_request(struct odbc_context_t *odbcc, union odbc_data_t *odbcd)
{
	SQLRETURN rc;
	int i, j;

	/* Perpare statement for Search Request interaction. */
	rc = SQLPrepare(odbcc->hstmt, STMT_SEARCH_REQUEST, SQL_NTS);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}

	/* Bind variables for Search Request interaction. */
	j = 1;
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_INPUT, SQL_C_ULONG, SQL_INTEGER, 0, 0,
		&odbcd->SEARCH_REQUEST_ODBC_DATA.pp_data.i_id, 0, NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}

	for (i = 0; i < PROMOTIONAL_ITEMS_MAX; i++)
	{
		rc = SQLBindParameter(odbcc->hstmt,
			j++, SQL_PARAM_OUTPUT, SQL_C_ULONG, SQL_INTEGER, 0, 0,
			&odbcd->SEARCH_REQUEST_ODBC_DATA.pp_data.i_related[i], 0, NULL);
		if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
		{
			LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			return W_ERROR;
		}
		rc = SQLBindParameter(odbcc->hstmt,
			j++, SQL_PARAM_OUTPUT, SQL_C_ULONG, SQL_INTEGER, 0, 0,
			&odbcd->SEARCH_REQUEST_ODBC_DATA.pp_data.i_thumbnail[i], 0, NULL);
		if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
		{
			LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			return W_ERROR;
		}
	}

	/* Generate random number for Promotional Processing. */
	odbcd->SEARCH_REQUEST_ODBC_DATA.pp_data.i_id =
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
