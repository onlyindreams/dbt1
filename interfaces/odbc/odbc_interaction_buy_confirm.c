/*
 * odbc_interaction_buy_confirm.c
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2002 Mark Wong & Jenny Zhang &
 *		    Open Source Development Lab, Inc.
 *
 * 26 february 2002
 */

#include <odbc_interaction_buy_confirm.h>
#include <sql.h>
#include <sqlext.h>
#include <common.h>

#ifdef PHASE1
#include <odbc_interaction.h>
#define BUY_CONFIRM_ODBC_DATA buy_confirm_odbc_data
#endif /* PHASE1 */

#ifdef PHASE2
#include <app_interaction.h>
#define BUY_CONFIRM_ODBC_DATA buy_confirm_odbc_data.eb
#endif /* PHASE2 */

#ifdef PHASE1
int copy_in_buy_confirm(struct eu_context_t *euc, union odbc_data_t *odbcd)
{
	odbcd->buy_confirm_odbc_data.sc_id=euc->buy_confirm_data.sc_id;
	odbcd->buy_confirm_odbc_data.c_id=euc->buy_confirm_data.c_id;
	strcpy(odbcd->buy_confirm_odbc_data.cx_type, euc->buy_confirm_data.cx_type);
	strcpy(odbcd->buy_confirm_odbc_data.cx_num, euc->buy_confirm_data.cx_num);
	strcpy(odbcd->buy_confirm_odbc_data.cx_name, euc->buy_confirm_data.cx_name);
	strcpy(odbcd->buy_confirm_odbc_data.cx_expiry,
		euc->buy_confirm_data.cx_expiry);
	strcpy(odbcd->buy_confirm_odbc_data.o_ship_type,
		euc->buy_confirm_data.o_ship_type);
	strcpy(odbcd->buy_confirm_odbc_data.shipping.addr_street1,
		euc->buy_confirm_data.shipping.addr_street1);
	strcpy(odbcd->buy_confirm_odbc_data.shipping.addr_street2,
		euc->buy_confirm_data.shipping.addr_street2);
	strcpy(odbcd->buy_confirm_odbc_data.shipping.addr_city,
		euc->buy_confirm_data.shipping.addr_city);
	strcpy(odbcd->buy_confirm_odbc_data.shipping.addr_state,
		euc->buy_confirm_data.shipping.addr_state);
	strcpy(odbcd->buy_confirm_odbc_data.shipping.addr_zip,
		euc->buy_confirm_data.shipping.addr_zip);
	strcpy(odbcd->buy_confirm_odbc_data.shipping.co_name,
		euc->buy_confirm_data.shipping.co_name);
	return W_OK;
}

int copy_out_buy_confirm(struct eu_context_t *euc, union odbc_data_t *odbcd)
{
	int i;
	euc->buy_confirm_data.c_discount = odbcd->buy_confirm_odbc_data.c_discount;
	euc->buy_confirm_data.sc_sub_total =
		odbcd->buy_confirm_odbc_data.sc_sub_total;
	euc->buy_confirm_data.sc_tax = odbcd->buy_confirm_odbc_data.sc_tax;
	euc->buy_confirm_data.sc_ship_cost =
		odbcd->buy_confirm_odbc_data.sc_ship_cost;
	euc->buy_confirm_data.sc_total = odbcd->buy_confirm_odbc_data.sc_total;
	euc->buy_confirm_data.sc_size = odbcd->buy_confirm_odbc_data.sc_size;

	for (i=0; i<odbcd->buy_confirm_odbc_data.sc_size; i++)
	{
		euc->buy_confirm_data.scl_data[i].scl_i_id =
			odbcd->buy_confirm_odbc_data.scl_data[i].scl_i_id; 
		euc->buy_confirm_data.scl_data[i].scl_qty =
			odbcd->buy_confirm_odbc_data.scl_data[i].scl_qty; 
		euc->buy_confirm_data.scl_data[i].scl_cost =
			odbcd->buy_confirm_odbc_data.scl_data[i].scl_cost; 
		euc->buy_confirm_data.scl_data[i].scl_srp =
			odbcd->buy_confirm_odbc_data.scl_data[i].scl_srp; 
		strcpy( euc->buy_confirm_data.scl_data[i].i_title, 
			odbcd->buy_confirm_odbc_data.scl_data[i].i_title);
		strcpy( euc->buy_confirm_data.scl_data[i].i_backing, 
			odbcd->buy_confirm_odbc_data.scl_data[i].i_backing);
	}
	return W_OK;

}
#endif /* PHASE1*/

int execute_buy_confirm(struct odbc_context_t *odbcc, union odbc_data_t *odbcd)
{
	SQLRETURN rc;
	int i, j;

	/* Perpare statement for Buy Confirm interaction. */
	rc = SQLPrepare(odbcc->hstmt, STMT_BUYCONF, SQL_NTS);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		if (LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt) != W_OK)
			return W_ERROR;
	}

	/* Bind variables for buyconfirm interaction. */
	j = 1;
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,
		0, 0, &odbcd->BUY_CONFIRM_ODBC_DATA.cx_type,
		sizeof(odbcd->BUY_CONFIRM_ODBC_DATA.cx_type), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		if (LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt) != W_OK)
			return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,
		0, 0, &odbcd->BUY_CONFIRM_ODBC_DATA.cx_num,
		sizeof(odbcd->BUY_CONFIRM_ODBC_DATA.cx_num), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		if (LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt) != W_OK)
			return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,
		0, 0, &odbcd->BUY_CONFIRM_ODBC_DATA.cx_name, 
		sizeof(odbcd->BUY_CONFIRM_ODBC_DATA.cx_name), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		if (LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt) != W_OK)
			return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,
		0, 0, &odbcd->BUY_CONFIRM_ODBC_DATA.cx_expiry, 
		sizeof(odbcd->BUY_CONFIRM_ODBC_DATA.cx_expiry), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		if (LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt) != W_OK)
			return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,
		0, 0, &odbcd->BUY_CONFIRM_ODBC_DATA.o_ship_type, 
		sizeof(odbcd->BUY_CONFIRM_ODBC_DATA.o_ship_type), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		if (LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt) != W_OK)
			return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
			j++, SQL_PARAM_INPUT, SQL_C_ULONG, SQL_INTEGER,
			0, 0, &odbcd->BUY_CONFIRM_ODBC_DATA.sc_id,
			0, NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		if (LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt) != W_OK)
			return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
			j++, SQL_PARAM_INPUT, SQL_C_ULONG, SQL_INTEGER,
			0, 0, &odbcd->BUY_CONFIRM_ODBC_DATA.c_id,
			0, NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		if (LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt) != W_OK)
			return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
			j++, SQL_PARAM_INPUT, SQL_C_SSHORT, SQL_INTEGER,
			0, 0, &odbcd->buy_confirm_odbc_data.ship_day, 0, NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		if (LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt) != W_OK)
			return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,
		0, 0, odbcd->buy_confirm_odbc_data.ol_comment, 
		sizeof(odbcd->buy_confirm_odbc_data.ol_comment), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		if (LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt) != W_OK)
			return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,
		0, 0, odbcd->buy_confirm_odbc_data.cx_auth_id,
		sizeof(odbcd->buy_confirm_odbc_data.cx_auth_id), NULL);

	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		if (LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt) != W_OK)
			return W_ERROR;
	}
	rc=SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,
		0, 0, odbcd->BUY_CONFIRM_ODBC_DATA.shipping.addr_street1,
		sizeof(odbcd->BUY_CONFIRM_ODBC_DATA.shipping.addr_street1), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		if (LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt) != W_OK)
			return W_ERROR;
	}
	rc=SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,
		0, 0, odbcd->BUY_CONFIRM_ODBC_DATA.shipping.addr_street2,
		sizeof(odbcd->BUY_CONFIRM_ODBC_DATA.shipping.addr_street2), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		if (LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt) != W_OK)
			return W_ERROR;
	}
	rc=SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,
		0, 0, odbcd->BUY_CONFIRM_ODBC_DATA.shipping.addr_city,
		sizeof(odbcd->BUY_CONFIRM_ODBC_DATA.shipping.addr_city), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		if (LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt) != W_OK)
			return W_ERROR;
	}
	rc=SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,
		0, 0, odbcd->BUY_CONFIRM_ODBC_DATA.shipping.addr_state,
		sizeof(odbcd->BUY_CONFIRM_ODBC_DATA.shipping.addr_state), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		if (LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt) != W_OK)
			return W_ERROR;
	}
	rc=SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,
		0, 0, odbcd->BUY_CONFIRM_ODBC_DATA.shipping.addr_zip,
		sizeof(odbcd->BUY_CONFIRM_ODBC_DATA.shipping.addr_zip), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		if (LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt) != W_OK)
			return W_ERROR;
	}
	rc=SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,
		0, 0, odbcd->BUY_CONFIRM_ODBC_DATA.shipping.co_name,
		sizeof(odbcd->BUY_CONFIRM_ODBC_DATA.shipping.co_name), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		if (LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt) != W_OK)
			return W_ERROR;
	}
	rc=SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_OUTPUT, SQL_C_DOUBLE, SQL_DOUBLE,
		0, 0, &odbcd->buy_confirm_odbc_data.c_discount, 0, NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		if (LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt) != W_OK)
			return W_ERROR;
	}
	rc=SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_OUTPUT, SQL_C_DOUBLE, SQL_DOUBLE,
		0, 0, &odbcd->BUY_CONFIRM_ODBC_DATA.sc_sub_total, 0, NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		if (LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt) != W_OK)
			return W_ERROR;
	}
	rc=SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_OUTPUT, SQL_C_DOUBLE, SQL_DOUBLE,
		0, 0, &odbcd->BUY_CONFIRM_ODBC_DATA.sc_tax, 0, NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		if (LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt) != W_OK)
			return W_ERROR;
	}
	rc=SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_OUTPUT, SQL_C_DOUBLE, SQL_DOUBLE,
		0, 0, &odbcd->BUY_CONFIRM_ODBC_DATA.sc_ship_cost, 0, NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		if (LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt) != W_OK)
			return W_ERROR;
	}
	rc=SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_OUTPUT, SQL_C_DOUBLE, SQL_DOUBLE,
		0, 0, &odbcd->BUY_CONFIRM_ODBC_DATA.sc_total, 0, NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		if (LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt) != W_OK)
			return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_OUTPUT, SQL_C_SLONG, SQL_INTEGER,
		0, 0, &odbcd->BUY_CONFIRM_ODBC_DATA.sc_size, 0, NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		if (LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt) != W_OK)
			return W_ERROR;
	}
	for (i=0; i<SHOPPING_CART_ITEMS_MAX; i++)
	{
		rc = SQLBindParameter(odbcc->hstmt,
			j++, SQL_PARAM_OUTPUT, SQL_C_ULONG, SQL_INTEGER,
			0, 0, 
			&odbcd->BUY_CONFIRM_ODBC_DATA.scl_data[i].scl_i_id,
			0, NULL);
		if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
		{
			if (LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt) != W_OK)
				return W_ERROR;
		}
		rc = SQLBindParameter(odbcc->hstmt,
			j++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
			odbcd->BUY_CONFIRM_ODBC_DATA.scl_data[i].i_title,
			sizeof(odbcd->BUY_CONFIRM_ODBC_DATA.scl_data[i].i_title), NULL);
		if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
		{
			if (LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt) != W_OK)
				return W_ERROR;
		}
		rc = SQLBindParameter(odbcc->hstmt,
			j++, SQL_PARAM_OUTPUT, SQL_C_DOUBLE, SQL_DOUBLE, 0, 0,
			&odbcd->BUY_CONFIRM_ODBC_DATA.scl_data[i].scl_cost, 
			0, NULL);
		if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
		{
			if (LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt) != W_OK)
				return W_ERROR;
		}
		rc = SQLBindParameter(odbcc->hstmt,
			j++, SQL_PARAM_OUTPUT, SQL_C_DOUBLE, SQL_DOUBLE, 0, 0,
			&odbcd->BUY_CONFIRM_ODBC_DATA.scl_data[i].scl_srp, 
			0, NULL);
		if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
		{
			if (LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt) != W_OK)
				return W_ERROR;
		}
		rc = SQLBindParameter(odbcc->hstmt,
			j++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
			odbcd->BUY_CONFIRM_ODBC_DATA.scl_data[i].i_backing,
			sizeof(odbcd->BUY_CONFIRM_ODBC_DATA.scl_data[i].i_backing), NULL);
		if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
		{
			if (LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt) != W_OK)
				return W_ERROR;
		}
		rc = SQLBindParameter(odbcc->hstmt, j++,
			SQL_PARAM_OUTPUT, SQL_C_SSHORT, SQL_SMALLINT, 0,0,
			&odbcd->BUY_CONFIRM_ODBC_DATA.scl_data[i].scl_qty, 0,
			NULL);
		if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
		{
			if (LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt) != W_OK)
				return W_ERROR;
		}
	}

	/* Generate random day between 1 to 7 for ship_date. */
	odbcd->buy_confirm_odbc_data.ship_day = get_random(7) + 1;
	/* get authentication id from PGE*/
	strcpy(odbcd->buy_confirm_odbc_data.cx_auth_id, "012345678912345");
	/* generate a_string[20..100] as order_line comment*/
	get_a_string(odbcd->buy_confirm_odbc_data.ol_comment, 20, 100);

	/* Execute stored procedure. */
	rc = SQLExecute(odbcc->hstmt);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
#ifdef DEBUG
		printf("SQLExecute error %d\n", rc);
#endif /* DEBUG */
		if (LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt) != W_OK)
			return W_ERROR;
	}

	return W_OK;
}
