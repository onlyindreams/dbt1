/*
 * odbc_interaction_product_detail.c
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
#include <odbc_interaction_product_detail.h>
#include <sql.h>
#include <sqlext.h>

#ifdef PHASE1
#include <odbc_interaction.h>
#define PRODUCT_DETAIL_ODBC_DATA product_detail_odbc_data
#endif /* PHASE1 */

#ifdef PHASE2
#include <app_interaction.h>
#define PRODUCT_DETAIL_ODBC_DATA product_detail_odbc_data.eb
#endif /* PHASE2 */

#ifdef PHASE1
int copy_in_product_detail(struct eu_context_t *euc, union odbc_data_t *odbcd)
{
	if (euc->product_detail_data.i_id < 1 ||
		euc->product_detail_data.i_id > item_count)
	{
		LOG_ERROR_MESSAGE( "i_id %lld is out of range\n",
			euc->product_detail_data.i_id);
		return W_ERROR;
	}
	odbcd->product_detail_odbc_data.i_id = euc->product_detail_data.i_id;
	return W_OK;
}

int copy_out_product_detail(struct eu_context_t *euc, union odbc_data_t *odbcd)
{
	strcpy(euc->product_detail_data.a_fname,
		odbcd->product_detail_odbc_data.a_fname);
	strcpy(euc->product_detail_data.a_lname,
		odbcd->product_detail_odbc_data.a_lname);
	strcpy(euc->product_detail_data.i_title,
		odbcd->product_detail_odbc_data.i_title);
	strcpy(euc->product_detail_data.i_pub_date,
		odbcd->product_detail_odbc_data.i_pub_date);
	strcpy(euc->product_detail_data.i_avail,
		odbcd->product_detail_odbc_data.i_avail);
	strcpy(euc->product_detail_data.i_publisher,
		odbcd->product_detail_odbc_data.i_publisher);
	strcpy(euc->product_detail_data.i_subject,
		odbcd->product_detail_odbc_data.i_subject);
	strcpy(euc->product_detail_data.i_desc,
		odbcd->product_detail_odbc_data.i_desc);
	strcpy(euc->product_detail_data.i_isbn,
		odbcd->product_detail_odbc_data.i_isbn);
	strcpy(euc->product_detail_data.i_backing,
		odbcd->product_detail_odbc_data.i_backing);
	strcpy(euc->product_detail_data.i_dimensions,
		odbcd->product_detail_odbc_data.i_dimensions);
	euc->product_detail_data.i_page = odbcd->product_detail_odbc_data.i_page;
	euc->product_detail_data.i_cost = odbcd->product_detail_odbc_data.i_cost;
	euc->product_detail_data.i_srp = odbcd->product_detail_odbc_data.i_srp;
	euc->product_detail_data.i_cost = odbcd->product_detail_odbc_data.i_cost;
	euc->product_detail_data.i_image = odbcd->product_detail_odbc_data.i_image;

	return W_OK;
}
#endif /* PHASE1*/

int execute_product_detail(struct odbc_context_t *odbcc, union odbc_data_t *odbcd)
{
	SQLRETURN rc;
	int i, j;

	/* Perpare statement for Product Detail interaction. */
	rc = SQLPrepare(odbcc->hstmt, STMT_PRODUCT_DETAIL, SQL_NTS);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}

	/* Bind variables for Product Detail interaction. */
	j = 1;
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_INPUT, SQL_C_ULONG, SQL_INTEGER, 0, 0,
		&odbcd->PRODUCT_DETAIL_ODBC_DATA.i_id, 0, NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}

	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR,
		0, 0, odbcd->PRODUCT_DETAIL_ODBC_DATA.i_title,
		sizeof(odbcd->PRODUCT_DETAIL_ODBC_DATA.i_title), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		odbcd->PRODUCT_DETAIL_ODBC_DATA.a_fname,
		sizeof(odbcd->PRODUCT_DETAIL_ODBC_DATA.a_fname), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		odbcd->PRODUCT_DETAIL_ODBC_DATA.a_lname,
		sizeof(odbcd->PRODUCT_DETAIL_ODBC_DATA.a_lname), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		odbcd->PRODUCT_DETAIL_ODBC_DATA.i_pub_date,
		sizeof(odbcd->PRODUCT_DETAIL_ODBC_DATA.i_pub_date), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		odbcd->PRODUCT_DETAIL_ODBC_DATA.i_publisher,
		sizeof(odbcd->PRODUCT_DETAIL_ODBC_DATA.i_publisher), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		odbcd->PRODUCT_DETAIL_ODBC_DATA.i_subject,
		sizeof(odbcd->PRODUCT_DETAIL_ODBC_DATA.i_subject), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		odbcd->PRODUCT_DETAIL_ODBC_DATA.i_desc,
		sizeof(odbcd->PRODUCT_DETAIL_ODBC_DATA.i_desc), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_OUTPUT, SQL_C_ULONG, SQL_INTEGER, 0, 0,
		&odbcd->PRODUCT_DETAIL_ODBC_DATA.i_image, 0, NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_OUTPUT, SQL_C_DOUBLE, SQL_DOUBLE, 0, 0,
		&odbcd->PRODUCT_DETAIL_ODBC_DATA.i_cost, 0, NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_OUTPUT, SQL_C_DOUBLE, SQL_DOUBLE, 0, 0,
		&odbcd->PRODUCT_DETAIL_ODBC_DATA.i_srp, 0, NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		odbcd->PRODUCT_DETAIL_ODBC_DATA.i_avail,
		sizeof(odbcd->PRODUCT_DETAIL_ODBC_DATA.i_avail), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		odbcd->PRODUCT_DETAIL_ODBC_DATA.i_isbn,
		sizeof(odbcd->PRODUCT_DETAIL_ODBC_DATA.i_isbn), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_OUTPUT, SQL_C_SSHORT, SQL_SMALLINT, 0, 0,
		&odbcd->PRODUCT_DETAIL_ODBC_DATA.i_page, 0, NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		odbcd->PRODUCT_DETAIL_ODBC_DATA.i_backing,
		sizeof(odbcd->PRODUCT_DETAIL_ODBC_DATA.i_backing), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		odbcd->PRODUCT_DETAIL_ODBC_DATA.i_dimensions,
		sizeof(odbcd->PRODUCT_DETAIL_ODBC_DATA.i_dimensions), NULL);
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
