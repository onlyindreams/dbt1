/*
 * odbc_interaction_order_display.c
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2002 Mark Wong & Jenny Zhang &
 *		    Open Source Development Lab, Inc.
 *
 * 1 march 2002
 */

#include <odbc_interaction_order_display.h>
#include <odbc_interaction.h>
#include <sql.h>
#include <sqlext.h>

#ifdef PHASE1
int copy_in_order_display(struct eu_context_t *euc, union odbc_data_t *odbcd)
{
	strcpy(odbcd->order_display_odbc_data.eb.c_uname,
		euc->order_display_data.c_uname);
	strcpy(odbcd->order_display_odbc_data.eb.c_passwd,
		euc->order_display_data.c_passwd);

	return W_OK;
}

int copy_out_order_display(struct eu_context_t *euc, union odbc_data_t *odbcd)
{
	int i;

	euc->order_display_data.o_id = odbcd->order_display_odbc_data.eb.o_id;
	strcpy(euc->order_display_data.c_fname,
		odbcd->order_display_odbc_data.eb.c_fname);
	strcpy(euc->order_display_data.c_lname,
		odbcd->order_display_odbc_data.eb.c_lname);
	strcpy(euc->order_display_data.c_phone,
		odbcd->order_display_odbc_data.eb.c_phone);
	strcpy(euc->order_display_data.c_email,
		odbcd->order_display_odbc_data.eb.c_email);
	strcpy(euc->order_display_data.o_date,
		odbcd->order_display_odbc_data.eb.o_date);
	euc->order_display_data.o_sub_total =
		odbcd->order_display_odbc_data.eb.o_sub_total;
	euc->order_display_data.o_tax = odbcd->order_display_odbc_data.eb.o_tax;
	euc->order_display_data.o_total = odbcd->order_display_odbc_data.eb.o_total;
	strcpy(euc->order_display_data.o_ship_type,
		odbcd->order_display_odbc_data.eb.o_ship_type);
	strcpy(euc->order_display_data.o_ship_date,
		odbcd->order_display_odbc_data.eb.o_ship_date);
	strcpy(euc->order_display_data.o_status,
		odbcd->order_display_odbc_data.eb.o_status);
	strcpy(euc->order_display_data.billing.addr_street1,
		odbcd->order_display_odbc_data.eb.billing.addr_street1);
	strcpy(euc->order_display_data.billing.addr_street2,
		odbcd->order_display_odbc_data.eb.billing.addr_street2);
	strcpy(euc->order_display_data.billing.addr_city,
		odbcd->order_display_odbc_data.eb.billing.addr_city);
	strcpy(euc->order_display_data.billing.addr_state,
		odbcd->order_display_odbc_data.eb.billing.addr_state);
	strcpy(euc->order_display_data.billing.addr_zip,
		odbcd->order_display_odbc_data.eb.billing.addr_zip);
	strcpy(euc->order_display_data.billing.co_name,
		odbcd->order_display_odbc_data.eb.billing.co_name);
	strcpy(euc->order_display_data.shipping.addr_street1,
		odbcd->order_display_odbc_data.eb.shipping.addr_street1);
	strcpy(euc->order_display_data.shipping.addr_street2,
		odbcd->order_display_odbc_data.eb.shipping.addr_street2);
	strcpy(euc->order_display_data.shipping.addr_city,
		odbcd->order_display_odbc_data.eb.shipping.addr_city);
	strcpy(euc->order_display_data.shipping.addr_state,
		odbcd->order_display_odbc_data.eb.shipping.addr_state);
	strcpy(euc->order_display_data.shipping.addr_zip,
		odbcd->order_display_odbc_data.eb.shipping.addr_zip);
	strcpy(euc->order_display_data.shipping.co_name,
		odbcd->order_display_odbc_data.eb.shipping.co_name);
	euc->order_display_data.items = odbcd->order_display_odbc_data.eb.items;
	for (i = 0; i < odbcd->order_display_odbc_data.eb.items; i++)
	{
		euc->order_display_data.odl_data[i].ol_i_id =
			odbcd->order_display_odbc_data.eb.odl_data[i].ol_i_id;
		strcpy(euc->order_display_data.odl_data[i].i_title,
			odbcd->order_display_odbc_data.eb.odl_data[i].i_title);
		strcpy(euc->order_display_data.odl_data[i].i_publisher,
			odbcd->order_display_odbc_data.eb.odl_data[i].i_publisher);
		euc->order_display_data.odl_data[i].i_cost =
			odbcd->order_display_odbc_data.eb.odl_data[i].i_cost;
		euc->order_display_data.odl_data[i].ol_qty =
			odbcd->order_display_odbc_data.eb.odl_data[i].ol_qty;
		euc->order_display_data.odl_data[i].ol_discount =
			odbcd->order_display_odbc_data.eb.odl_data[i].ol_discount;
		strcpy(euc->order_display_data.odl_data[i].ol_comment,
			odbcd->order_display_odbc_data.eb.odl_data[i].ol_comment);
	}
	strcpy(euc->order_display_data.cx_type,
		odbcd->order_display_odbc_data.eb.cx_type);
	strcpy(euc->order_display_data.cx_auth_id,
		odbcd->order_display_odbc_data.eb.cx_auth_id);
	return W_OK;
}
#endif /* PHASE1 */

int execute_order_display(struct odbc_context_t *odbcc, union odbc_data_t *odbcd)
{
	SQLRETURN rc;
	int i, j;

	/* Perpare statement for order display interaction. */
	rc = SQLPrepare(odbcc->hstmt, STMT_ORDER_DISPLAY, SQL_NTS);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			return W_ERROR;
	}

	/* Bind variables for New Products interaction. */
	i = 1;
	rc = SQLBindParameter(odbcc->hstmt,
		i++, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		odbcd->order_display_odbc_data.eb.c_uname,
		sizeof(odbcd->order_display_odbc_data.eb.c_uname), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		i++, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		odbcd->order_display_odbc_data.eb.c_passwd,
		sizeof(odbcd->order_display_odbc_data.eb.c_passwd), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		i++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		odbcd->order_display_odbc_data.eb.c_fname,
		sizeof(odbcd->order_display_odbc_data.eb.c_fname), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		i++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		odbcd->order_display_odbc_data.eb.c_lname,
		sizeof(odbcd->order_display_odbc_data.eb.c_lname), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		i++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		odbcd->order_display_odbc_data.eb.c_phone,
		sizeof(odbcd->order_display_odbc_data.eb.c_phone), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		i++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		odbcd->order_display_odbc_data.eb.c_email,
		sizeof(odbcd->order_display_odbc_data.eb.c_email), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		i++, SQL_PARAM_OUTPUT, SQL_C_ULONG, SQL_INTEGER, 0, 0,
		&odbcd->order_display_odbc_data.eb.o_id, 0, NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		i++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		&odbcd->order_display_odbc_data.eb.o_date,
		sizeof(odbcd->order_display_odbc_data.eb.o_date), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		i++, SQL_PARAM_OUTPUT, SQL_C_DOUBLE, SQL_DOUBLE, 0, 0,
		&odbcd->order_display_odbc_data.eb.o_sub_total, 0, NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		i++, SQL_PARAM_OUTPUT, SQL_C_DOUBLE, SQL_DOUBLE, 0, 0,
		&odbcd->order_display_odbc_data.eb.o_tax, 0, NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		i++, SQL_PARAM_OUTPUT, SQL_C_DOUBLE, SQL_DOUBLE, 0, 0,
		&odbcd->order_display_odbc_data.eb.o_total, 0, NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		i++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		odbcd->order_display_odbc_data.eb.o_ship_type,
		sizeof(odbcd->order_display_odbc_data.eb.o_ship_type), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		i++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		&odbcd->order_display_odbc_data.eb.o_ship_date,
		sizeof(odbcd->order_display_odbc_data.eb.o_ship_date), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		i++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		odbcd->order_display_odbc_data.eb.o_status,
		sizeof(odbcd->order_display_odbc_data.eb.o_status), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		i++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		odbcd->order_display_odbc_data.eb.cx_type,
		sizeof(odbcd->order_display_odbc_data.eb.cx_type), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		i++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		odbcd->order_display_odbc_data.eb.cx_auth_id,
		sizeof(odbcd->order_display_odbc_data.eb.cx_auth_id), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		i++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		odbcd->order_display_odbc_data.eb.billing.addr_street1,
		sizeof(odbcd->order_display_odbc_data.eb.billing.addr_street1), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		i++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		odbcd->order_display_odbc_data.eb.billing.addr_street2,
		sizeof(odbcd->order_display_odbc_data.eb.billing.addr_street2), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		i++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		odbcd->order_display_odbc_data.eb.billing.addr_city,
		sizeof(odbcd->order_display_odbc_data.eb.billing.addr_city), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		i++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		odbcd->order_display_odbc_data.eb.billing.addr_state,
		sizeof(odbcd->order_display_odbc_data.eb.billing.addr_state), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		i++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		odbcd->order_display_odbc_data.eb.billing.addr_zip,
		sizeof(odbcd->order_display_odbc_data.eb.billing.addr_zip), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		i++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		odbcd->order_display_odbc_data.eb.billing.co_name,
		sizeof(odbcd->order_display_odbc_data.eb.billing.co_name), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		i++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		odbcd->order_display_odbc_data.eb.shipping.addr_street1,
		sizeof(odbcd->order_display_odbc_data.eb.shipping.addr_street1), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		i++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		odbcd->order_display_odbc_data.eb.shipping.addr_street2,
		sizeof(odbcd->order_display_odbc_data.eb.shipping.addr_street2), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		i++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		odbcd->order_display_odbc_data.eb.shipping.addr_city,
		sizeof(odbcd->order_display_odbc_data.eb.shipping.addr_city), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		i++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		odbcd->order_display_odbc_data.eb.shipping.addr_state,
		sizeof(odbcd->order_display_odbc_data.eb.shipping.addr_state), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		i++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		odbcd->order_display_odbc_data.eb.shipping.addr_zip,
		sizeof(odbcd->order_display_odbc_data.eb.shipping.addr_zip), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		i++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		odbcd->order_display_odbc_data.eb.shipping.co_name,
		sizeof(odbcd->order_display_odbc_data.eb.shipping.co_name), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		i++, SQL_PARAM_OUTPUT, SQL_C_SSHORT, SQL_SMALLINT, 0, 0,
		&odbcd->order_display_odbc_data.eb.items, 0, NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			return W_ERROR;
	}
	for (j = 0; j < SHOPPING_CART_ITEMS_MAX; j++)
	{
		rc = SQLBindParameter(odbcc->hstmt,
			i++, SQL_PARAM_OUTPUT, SQL_C_ULONG, SQL_INTEGER, 0, 0,
			&odbcd->order_display_odbc_data.eb.odl_data[j].ol_i_id, 0, NULL);
		if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
		{
			LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
				return W_ERROR;
		}
		rc = SQLBindParameter(odbcc->hstmt,
			i++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
			odbcd->order_display_odbc_data.eb.odl_data[j].i_title,
			sizeof(odbcd->order_display_odbc_data.eb.odl_data[j].i_title), NULL);
		if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
		{
			LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
				return W_ERROR;
		}
		rc = SQLBindParameter(odbcc->hstmt,
			i++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
			odbcd->order_display_odbc_data.eb.odl_data[j].i_publisher,
			sizeof(odbcd->order_display_odbc_data.eb.odl_data[j].i_publisher),
			NULL);
		if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
		{
			LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
				return W_ERROR;
		}
		rc = SQLBindParameter(odbcc->hstmt,
			i++, SQL_PARAM_OUTPUT, SQL_C_DOUBLE, SQL_DOUBLE, 0, 0,
			&odbcd->order_display_odbc_data.eb.odl_data[j].i_cost, 0, NULL);
		if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
		{
			LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
				return W_ERROR;
		}
		rc = SQLBindParameter(odbcc->hstmt,
			i++, SQL_PARAM_OUTPUT, SQL_C_SSHORT, SQL_SMALLINT, 0, 0,
			&odbcd->order_display_odbc_data.eb.odl_data[j].ol_qty, 0, NULL);
		if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
		{
			LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
				return W_ERROR;
		}
		rc = SQLBindParameter(odbcc->hstmt,
			i++, SQL_PARAM_OUTPUT, SQL_C_DOUBLE, SQL_DOUBLE, 0, 0,
			&odbcd->order_display_odbc_data.eb.odl_data[j].ol_discount, 0, NULL);
		if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
		{
			LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
				return W_ERROR;
		}
		rc = SQLBindParameter(odbcc->hstmt,
			i++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
			odbcd->order_display_odbc_data.eb.odl_data[j].ol_comment,
			sizeof(odbcd->order_display_odbc_data.eb.odl_data[j].ol_comment),
			NULL);
		if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
		{
			LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
				return W_ERROR;
		}
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
