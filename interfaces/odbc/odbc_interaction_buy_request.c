/*
 * odbc_interaction_buy_request.c
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2002 Mark Wong & Jenny Zhang &
 *                    Open Source Development Lab, Inc.
 *
 * 25 february 2002
 */

#include <odbc_interaction_buy_request.h>
#include <odbc_interaction.h>
#include <sql.h>
#include <sqlext.h>

#ifdef PHASE1
int copy_in_buy_request(struct eu_context_t *euc, union odbc_data_t *odbcd)
{
	odbcd->buy_request_odbc_data.eb.returning_flag =
		euc->buy_request_data.returning_flag;
	odbcd->buy_request_odbc_data.eb.sc_id = euc->buy_request_data.sc_id;
#ifdef DEBUG
	printf("returning_flag %d\n", odbcd->buy_request_odbc_data.eb.returning_flag);
	printf("sc_id %ld\n", odbcd->buy_request_odbc_data.eb.sc_id);
#endif /* DEBUG */
	if (odbcd->buy_request_odbc_data.eb.returning_flag == TRUE)
	{
#ifdef DEBUG
		printf("c_uname %s\n",  euc->buy_request_data.c_uname);
#endif /* DEBUG */
		strcpy(odbcd->buy_request_odbc_data.eb.c_uname,
			euc->buy_request_data.c_uname);
		odbcd->buy_request_odbc_data.eb.c_discount = 0.00;
	}
	else
	{
#ifdef DEBUG
		printf("c_fname %s\n", euc->buy_request_data.c_fname);
		printf("c_phone %s\n", euc->buy_request_data.c_phone);
#endif /* DEBUG */
		strcpy(odbcd->buy_request_odbc_data.eb.c_fname,
			euc->buy_request_data.c_fname);
		strcpy(odbcd->buy_request_odbc_data.eb.c_lname,
			euc->buy_request_data.c_lname);
		strcpy(odbcd->buy_request_odbc_data.eb.address.addr_street1,
			euc->buy_request_data.address.addr_street1);
		strcpy(odbcd->buy_request_odbc_data.eb.address.addr_street2,
			euc->buy_request_data.address.addr_street2);
		strcpy(odbcd->buy_request_odbc_data.eb.address.addr_city,
			euc->buy_request_data.address.addr_city);
		strcpy(odbcd->buy_request_odbc_data.eb.address.addr_state,
			euc->buy_request_data.address.addr_state);
		strcpy(odbcd->buy_request_odbc_data.eb.address.addr_zip,
			euc->buy_request_data.address.addr_zip);
		strcpy(odbcd->buy_request_odbc_data.eb.address.co_name,
			euc->buy_request_data.address.co_name);
		strcpy(odbcd->buy_request_odbc_data.eb.c_phone,
			euc->buy_request_data.c_phone);
		strcpy(odbcd->buy_request_odbc_data.eb.c_email,
			euc->buy_request_data.c_email);
		strcpy(odbcd->buy_request_odbc_data.eb.c_birthdate,
			euc->buy_request_data.c_birthdate);
		strcpy(odbcd->buy_request_odbc_data.eb.c_data,
			euc->buy_request_data.c_data);
	}
	return W_OK;
}

int copy_out_buy_request(struct eu_context_t *euc, union odbc_data_t *odbcd)
{
	int i;
	if (odbcd->buy_request_odbc_data.eb.returning_flag == TRUE)
	{
		strcpy(euc->buy_request_data.c_fname,
			odbcd->buy_request_odbc_data.eb.c_fname);
		strcpy(euc->buy_request_data.c_lname,
			odbcd->buy_request_odbc_data.eb.c_lname);
		strcpy(euc->buy_request_data.address.addr_street1,
			odbcd->buy_request_odbc_data.eb.address.addr_street1);
		strcpy(euc->buy_request_data.address.addr_street2,
			odbcd->buy_request_odbc_data.eb.address.addr_street2);
		strcpy(euc->buy_request_data.address.addr_city,
			odbcd->buy_request_odbc_data.eb.address.addr_city);
		strcpy(euc->buy_request_data.address.addr_state,
			odbcd->buy_request_odbc_data.eb.address.addr_state);
		strcpy(euc->buy_request_data.address.addr_zip,
			odbcd->buy_request_odbc_data.eb.address.addr_zip);
		strcpy(euc->buy_request_data.address.co_name,
			odbcd->buy_request_odbc_data.eb.address.co_name);
		strcpy(euc->buy_request_data.c_phone,
			odbcd->buy_request_odbc_data.eb.c_phone);
		strcpy(euc->buy_request_data.c_email,
			odbcd->buy_request_odbc_data.eb.c_email);
		strcpy(euc->buy_request_data.c_birthdate,
			odbcd->buy_request_odbc_data.eb.c_birthdate);
		strcpy(euc->buy_request_data.c_data,
			odbcd->buy_request_odbc_data.eb.c_data);
		strcpy(euc->buy_request_data.c_passwd,
			odbcd->buy_request_odbc_data.eb.c_passwd);
	}

	euc->buy_request_data.c_id = odbcd->buy_request_odbc_data.eb.c_id;
	euc->buy_request_data.c_discount = odbcd->buy_request_odbc_data.eb.c_discount;
	euc->buy_request_data.sc_sub_total =
		odbcd->buy_request_odbc_data.eb.sc_sub_total;
	euc->buy_request_data.sc_tax = odbcd->buy_request_odbc_data.eb.sc_tax;
	euc->buy_request_data.sc_ship_cost =
		odbcd->buy_request_odbc_data.eb.sc_ship_cost;
	euc->buy_request_data.sc_total = odbcd->buy_request_odbc_data.eb.sc_total;

	euc->buy_request_data.sc_size=odbcd->buy_request_odbc_data.eb.sc_size;

	for (i=0; i<odbcd->buy_request_odbc_data.eb.sc_size; i++)
	{
		euc->buy_request_data.scl_data[i].scl_i_id =
			odbcd->buy_request_odbc_data.eb.scl_data[i].scl_i_id; 
		euc->buy_request_data.scl_data[i].scl_qty =
			odbcd->buy_request_odbc_data.eb.scl_data[i].scl_qty; 
		euc->buy_request_data.scl_data[i].scl_cost =
			odbcd->buy_request_odbc_data.eb.scl_data[i].scl_cost; 
		euc->buy_request_data.scl_data[i].scl_srp =
			odbcd->buy_request_odbc_data.eb.scl_data[i].scl_srp; 
		strcpy(euc->buy_request_data.scl_data[i].i_title, 
			odbcd->buy_request_odbc_data.eb.scl_data[i].i_title);
		strcpy(euc->buy_request_data.scl_data[i].i_backing, 
			odbcd->buy_request_odbc_data.eb.scl_data[i].i_backing);
	}
	return W_OK;
}
#endif /* PHASE1 */

int execute_buy_request(struct odbc_context_t *odbcc, union odbc_data_t *odbcd)
{
	SQLRETURN rc;
	int i,j;

	/* Perpare statement for Buy Request interaction. */
	rc = SQLPrepare(odbcc->hstmt, STMT_BUYREQ, SQL_NTS);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}

	j = 1;
	/* Bind variables for Home interaction. */
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_INPUT, SQL_C_SSHORT, SQL_SMALLINT, 0, 0,
		&odbcd->buy_request_odbc_data.eb.returning_flag, 0, NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		LOG_ERROR_MESSAGE("j is %d", j);
		return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		odbcd->buy_request_odbc_data.eb.c_uname,
		sizeof(odbcd->buy_request_odbc_data.eb.c_uname), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		LOG_ERROR_MESSAGE("j is %d", j);
		return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_INPUT, SQL_C_ULONG, SQL_INTEGER, 0, 0,
		&odbcd->buy_request_odbc_data.eb.sc_id, 0, NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		LOG_ERROR_MESSAGE("j is %d", j);
		return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_INPUT_OUTPUT, SQL_C_DOUBLE, SQL_DOUBLE, 0, 0,
		&odbcd->buy_request_odbc_data.eb.c_discount, 0, NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		LOG_ERROR_MESSAGE("j is %d", j);
		return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_INPUT_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		odbcd->buy_request_odbc_data.eb.c_fname,
		sizeof(odbcd->buy_request_odbc_data.eb.c_fname), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		LOG_ERROR_MESSAGE("j is %d", j);
		return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_INPUT_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		odbcd->buy_request_odbc_data.eb.c_lname,
		sizeof(odbcd->buy_request_odbc_data.eb.c_lname), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		LOG_ERROR_MESSAGE("j is %d", j);
		return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_INPUT_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		odbcd->buy_request_odbc_data.eb.address.addr_street1,
		sizeof(odbcd->buy_request_odbc_data.eb.address.addr_street1), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		LOG_ERROR_MESSAGE("j is %d", j);
		return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_INPUT_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		odbcd->buy_request_odbc_data.eb.address.addr_street2,
		sizeof(odbcd->buy_request_odbc_data.eb.address.addr_street2), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		LOG_ERROR_MESSAGE("j is %d", j);
		return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_INPUT_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		odbcd->buy_request_odbc_data.eb.address.addr_city,
		sizeof(odbcd->buy_request_odbc_data.eb.address.addr_city), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		LOG_ERROR_MESSAGE("j is %d", j);
			 return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_INPUT_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		odbcd->buy_request_odbc_data.eb.address.addr_state,
		sizeof(odbcd->buy_request_odbc_data.eb.address.addr_state), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		LOG_ERROR_MESSAGE("j is %d", j);
			 return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_INPUT_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		odbcd->buy_request_odbc_data.eb.address.addr_zip,
		sizeof(odbcd->buy_request_odbc_data.eb.address.addr_zip), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		LOG_ERROR_MESSAGE("j is %d", j);
			 return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_INPUT_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		odbcd->buy_request_odbc_data.eb.address.co_name,
		sizeof(odbcd->buy_request_odbc_data.eb.address.co_name), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		LOG_ERROR_MESSAGE("j is %d", j);
			 return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_INPUT_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		odbcd->buy_request_odbc_data.eb.c_phone,
		sizeof(odbcd->buy_request_odbc_data.eb.c_phone), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		LOG_ERROR_MESSAGE("j is %d", j);
			 return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_INPUT_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		odbcd->buy_request_odbc_data.eb.c_email,
		sizeof(odbcd->buy_request_odbc_data.eb.c_email), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		LOG_ERROR_MESSAGE("j is %d", j);
			 return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_INPUT_OUTPUT, SQL_C_CHAR, SQL_CHAR, 0, 0,
		odbcd->buy_request_odbc_data.eb.c_birthdate,
		sizeof(odbcd->buy_request_odbc_data.eb.c_birthdate), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		LOG_ERROR_MESSAGE("j is %d", j);
			 return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_INPUT_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		odbcd->buy_request_odbc_data.eb.c_data,
		sizeof(odbcd->buy_request_odbc_data.eb.c_data), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		LOG_ERROR_MESSAGE("j is %d", j);
			 return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
		odbcd->buy_request_odbc_data.eb.c_passwd,
		sizeof(odbcd->buy_request_odbc_data.eb.c_passwd), NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		LOG_ERROR_MESSAGE("j is %d", j);
			 return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_OUTPUT, SQL_C_ULONG, SQL_NUMERIC, 0, 0,
		&odbcd->buy_request_odbc_data.eb.c_id, 0, NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		LOG_ERROR_MESSAGE("j is %d", j);
			 return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_OUTPUT, SQL_C_DOUBLE, SQL_DOUBLE, 0, 0,
		&odbcd->buy_request_odbc_data.eb.sc_sub_total, 0, NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		LOG_ERROR_MESSAGE("j is %d", j);
			 return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_OUTPUT, SQL_C_DOUBLE, SQL_DOUBLE, 0, 0,
		&odbcd->buy_request_odbc_data.eb.sc_tax, 0, NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		LOG_ERROR_MESSAGE("j is %d", j);
			 return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_OUTPUT, SQL_C_DOUBLE, SQL_DOUBLE, 0, 0,
		&odbcd->buy_request_odbc_data.eb.sc_ship_cost, 0, NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		LOG_ERROR_MESSAGE("j is %d", j);
			 return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_OUTPUT, SQL_C_DOUBLE, SQL_DOUBLE, 0, 0,
		&odbcd->buy_request_odbc_data.eb.sc_total, 0, NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		LOG_ERROR_MESSAGE("j is %d", j);
			 return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_OUTPUT, SQL_C_SSHORT, SQL_SMALLINT,
		0, 0, &odbcd->buy_request_odbc_data.eb.sc_size, 0, NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		LOG_ERROR_MESSAGE("j is %d", j);
			 return W_ERROR;
	}
	for (i=0; i<SHOPPING_CART_ITEMS_MAX; i++)
	{
		rc = SQLBindParameter(odbcc->hstmt,
			j++, SQL_PARAM_OUTPUT, SQL_C_ULONG, SQL_INTEGER,
			0, 0, 
			&odbcd->buy_request_odbc_data.eb.scl_data[i].scl_i_id,
			0, NULL);
		if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
		{
			LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			LOG_ERROR_MESSAGE("j is %d", j);
				 return W_ERROR;
		}
		rc = SQLBindParameter(odbcc->hstmt,
			j++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
			odbcd->buy_request_odbc_data.eb.scl_data[i].i_title,
			sizeof(odbcd->buy_request_odbc_data.eb.scl_data[i].i_title), NULL);
		if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
		{
			LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			LOG_ERROR_MESSAGE("j is %d", j);
				 return W_ERROR;
		}
		rc = SQLBindParameter(odbcc->hstmt,
			j++, SQL_PARAM_OUTPUT, SQL_C_DOUBLE, SQL_DOUBLE, 0, 0,
			&odbcd->buy_request_odbc_data.eb.scl_data[i].scl_cost, 
			0, NULL);
		if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
		{
			LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			LOG_ERROR_MESSAGE("j is %d", j);
				 return W_ERROR;
		}
		rc = SQLBindParameter(odbcc->hstmt,
			j++, SQL_PARAM_OUTPUT, SQL_C_DOUBLE, SQL_DOUBLE, 0, 0,
			&odbcd->buy_request_odbc_data.eb.scl_data[i].scl_srp, 
			0, NULL);
		if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
		{
			LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			LOG_ERROR_MESSAGE("j is %d", j);
				 return W_ERROR;
		}
		rc = SQLBindParameter(odbcc->hstmt,
			j++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
			odbcd->buy_request_odbc_data.eb.scl_data[i].i_backing,
			sizeof(odbcd->buy_request_odbc_data.eb.scl_data[i].i_backing), NULL);
		if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
		{
			LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			LOG_ERROR_MESSAGE("j is %d", j);
				 return W_ERROR;
		}
		rc = SQLBindParameter(odbcc->hstmt, j++,
			SQL_PARAM_OUTPUT, SQL_C_SSHORT, SQL_SMALLINT, 0,0,
			&odbcd->buy_request_odbc_data.eb.scl_data[i].scl_qty, 0,
			NULL);
		if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
		{
			LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			LOG_ERROR_MESSAGE("j is %d", j);
				 return W_ERROR;
		}
	}

	/* if not return customer, copy data */
	/* discount is random number between 0.00 to 0.50*/
	if (odbcd->buy_request_odbc_data.eb.returning_flag == FALSE)
	{
		odbcd->buy_request_odbc_data.eb.c_discount=((double)get_random(50)+1.0)/100.0;
#ifdef DEBUG
		DEBUGMSG("c_discount %0.2f\n",odbcd->buy_request_odbc_data.eb.c_discount);
#endif /* DEBUG */
	}

	/* Execute stored procedure. */
	rc = SQLExecute(odbcc->hstmt);
#ifdef DEBUG
	printf("rc %d\n", rc);
#endif /* DEBUG */
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
#ifdef DEBUG
		printf("error rc %d\n", rc);
		LOG_ERROR_MESSAGE("execute error rc %d", rc);
		LOG_ERROR_MESSAGE("returning_flag %d", odbcd->buy_request_odbc_data.eb.returning_flag);
#endif /* DEBUG */
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
		return W_ERROR;
	}
#ifdef DEBUG
	printf("after exec c_fname %s\n", odbcd->buy_request_odbc_data.eb.c_fname);
	printf("after exec c_id %d\n", odbcd->buy_request_odbc_data.eb.c_id);
#endif /* DEBUG */

	return W_OK;
}
