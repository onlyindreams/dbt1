/*
 * odbc_interaction_shopping_cart.c
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2002 Mark Wong & Jenny Zhang &
 *                    Open Source Development Lab, Inc.
 *
 */

#include <odbc_interaction_shopping_cart.h>
#include <odbc_interaction.h>
#include <sql.h>
#include <sqlext.h>

#ifdef PHASE1
int copy_in_shopping_cart(struct eu_context_t *euc, union odbc_data_t *odbcd)
{
	int i;

#ifdef DEBUG
	printf("addflag is %d, itemcount %d, sc_id %ld\n", 
		euc->shopping_cart_data.add_flag, 
		euc->shopping_cart_data.sc_size,  
		euc->shopping_cart_data.sc_id);
#endif /* DEBUG */

	/* Copy data in. */
	odbcd->shopping_cart_odbc_data.eb.c_id=euc->shopping_cart_data.c_id;
	odbcd->shopping_cart_odbc_data.eb.sc_id=euc->shopping_cart_data.sc_id;
	odbcd->shopping_cart_odbc_data.eb.sc_size=euc->shopping_cart_data.sc_size;
	odbcd->shopping_cart_odbc_data.eb.add_flag=euc->shopping_cart_data.add_flag;
	/* if (i_id,qty) pair is empty, and add_flag=FALSE, add a random 
		i_id to shopping cart, move to execute_shopping_cart part*/
	/* add item to shopping_cart */
	if ( euc->shopping_cart_data.add_flag==TRUE)
	{
		odbcd->shopping_cart_odbc_data.eb.i_id
			=euc->shopping_cart_data.i_id;
	}
	/*refresh shopping_cart*/
	else if (euc->shopping_cart_data.add_flag==FALSE &&
			euc->shopping_cart_data.sc_size != 0)
	{
		for (i=0; i<euc->shopping_cart_data.sc_size;i++)
		{
		 odbcd->shopping_cart_odbc_data.eb.sc_refresh[i].scl_i_id =
			euc->shopping_cart_data.sc_refresh[i].scl_i_id;
		 odbcd->shopping_cart_odbc_data.eb.sc_refresh[i].scl_qty =
			euc->shopping_cart_data.sc_refresh[i].scl_qty;
		}
	}
	return OK;
}

int copy_out_shopping_cart(struct eu_context_t *euc, union odbc_data_t *odbcd)
{
	int i;

 	euc->shopping_cart_data.sc_id=odbcd->shopping_cart_odbc_data.eb.sc_id;
	for (i=0; i< PROMOTIONAL_ITEMS_MAX; i++)
	{
		euc->shopping_cart_data.pp_data.i_related[i] =
		odbcd->shopping_cart_odbc_data.eb.pp_data.i_related[i];
		euc->shopping_cart_data.pp_data.i_thumbnail[i] =
			odbcd->shopping_cart_odbc_data.eb.pp_data.i_thumbnail[i];
	}
	euc->shopping_cart_data.sc_size=odbcd->shopping_cart_odbc_data.eb.sc_size;

	for (i=0; i<odbcd->shopping_cart_odbc_data.eb.sc_size; i++)
	{
		euc->shopping_cart_data.scl_data[i].scl_i_id =
			odbcd->shopping_cart_odbc_data.eb.scl_data[i].scl_i_id; 
		euc->shopping_cart_data.scl_data[i].scl_qty =
			odbcd->shopping_cart_odbc_data.eb.scl_data[i].scl_qty; 
		euc->shopping_cart_data.scl_data[i].scl_cost =
			odbcd->shopping_cart_odbc_data.eb.scl_data[i].scl_cost; 
		euc->shopping_cart_data.scl_data[i].scl_srp =
			odbcd->shopping_cart_odbc_data.eb.scl_data[i].scl_srp; 
		strcpy( euc->shopping_cart_data.scl_data[i].i_title, 
			odbcd->shopping_cart_odbc_data.eb.scl_data[i].i_title);
		strcpy( euc->shopping_cart_data.scl_data[i].i_backing, 
			odbcd->shopping_cart_odbc_data.eb.scl_data[i].i_backing);
	}
	return OK;
}
#endif /* PHASE1 */

int execute_shopping_cart(struct odbc_context_t *odbcc,  union odbc_data_t *odbcd)
{
	SQLRETURN rc;
	int i,j;

	/* Perpare statement for shoppingcart interaction. */
	rc = SQLPrepare(odbcc->hstmt, STMT_SC, SQL_NTS);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			return W_ERROR;
	}

	j=1;
	/* Bind variables for shopping_cart interaction. */
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_INPUT, SQL_C_ULONG, SQL_INTEGER,
		0, 0, &odbcd->shopping_cart_odbc_data.eb.c_id, 0, NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_INPUT_OUTPUT, SQL_C_ULONG, SQL_INTEGER,
		0, 0, &odbcd->shopping_cart_odbc_data.eb.sc_id, 0, NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_INPUT_OUTPUT, SQL_C_SSHORT, SQL_SMALLINT,
		0, 0, &odbcd->shopping_cart_odbc_data.eb.sc_size, 0, NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_INPUT, SQL_C_SSHORT, SQL_SMALLINT,
		0, 0, &odbcd->shopping_cart_odbc_data.eb.add_flag, 0, NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_INPUT, SQL_C_ULONG, SQL_INTEGER,
		0, 0, &odbcd->shopping_cart_odbc_data.eb.i_id,
		0, NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			return W_ERROR;
	}
	rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_INPUT, SQL_C_ULONG, SQL_INTEGER,
		0, 0, &odbcd->shopping_cart_odbc_data.eb.pp_data.i_id,
		0, NULL);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
	{
		LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
			return W_ERROR;
	}
	/*bind i_id,qty pairs*/
	for (i=0; i<SHOPPING_CART_ITEMS_MAX; i++)
	{
		rc = SQLBindParameter(odbcc->hstmt, j++,
		SQL_PARAM_INPUT, SQL_C_ULONG, SQL_INTEGER, 0,0,
		&odbcd->shopping_cart_odbc_data.eb.sc_refresh[i].scl_i_id, 0,
		NULL);
		if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
		{
			LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
				return W_ERROR;
		}
		rc = SQLBindParameter(odbcc->hstmt, j++,
		SQL_PARAM_INPUT, SQL_C_SSHORT, SQL_SMALLINT, 0,0,
		&odbcd->shopping_cart_odbc_data.eb.sc_refresh[i].scl_qty, 0,
		NULL);
		if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
		{
			LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
				return W_ERROR;
		}
	}
	/* bind shopping cart line info*/
	for (i=0; i<SHOPPING_CART_ITEMS_MAX; i++)
	{
		rc = SQLBindParameter(odbcc->hstmt,
			j++, SQL_PARAM_OUTPUT, SQL_C_ULONG, SQL_INTEGER,
			0, 0, 
			&odbcd->shopping_cart_odbc_data.eb.scl_data[i].scl_i_id,
			0, NULL);
		if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
		{
			LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
				return W_ERROR;
		}
		rc = SQLBindParameter(odbcc->hstmt,
			j++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
			odbcd->shopping_cart_odbc_data.eb.scl_data[i].i_title,
			sizeof(odbcd->shopping_cart_odbc_data.eb.scl_data[i].i_title), NULL);
		if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
		{
			LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
				return W_ERROR;
		}
		rc = SQLBindParameter(odbcc->hstmt,
			j++, SQL_PARAM_OUTPUT, SQL_C_DOUBLE, SQL_DOUBLE, 0, 0,
			&odbcd->shopping_cart_odbc_data.eb.scl_data[i].scl_cost, 
			0, NULL);
		if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
		{
			LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
				return W_ERROR;
		}
		rc = SQLBindParameter(odbcc->hstmt,
			j++, SQL_PARAM_OUTPUT, SQL_C_DOUBLE, SQL_DOUBLE, 0, 0,
			&odbcd->shopping_cart_odbc_data.eb.scl_data[i].scl_srp, 
			0, NULL);
		if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
		{
			LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
				return W_ERROR;
		}
		rc = SQLBindParameter(odbcc->hstmt,
			j++, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0,
			odbcd->shopping_cart_odbc_data.eb.scl_data[i].i_backing,
			sizeof(odbcd->shopping_cart_odbc_data.eb.scl_data[i].i_backing), NULL);
		if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
		{
			LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
				return W_ERROR;
		}
		rc = SQLBindParameter(odbcc->hstmt, j++,
			SQL_PARAM_OUTPUT, SQL_C_SSHORT, SQL_SMALLINT, 0,0,
			&odbcd->shopping_cart_odbc_data.eb.scl_data[i].scl_qty, 0,
			NULL);
		if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
		{
			LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
				return W_ERROR;
		}
	}
	/* bind promo proc data*/
	for (i=0; i< PROMOTIONAL_ITEMS_MAX; i++)
	{
		rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_OUTPUT, SQL_C_ULONG, SQL_INTEGER,
		0, 0, &odbcd->shopping_cart_odbc_data.eb.pp_data.i_related[i],
		0, NULL);
		if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
		{
			LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
				return W_ERROR;
		}
		rc = SQLBindParameter(odbcc->hstmt,
		j++, SQL_PARAM_OUTPUT, SQL_C_ULONG, SQL_INTEGER,
		0, 0, &odbcd->shopping_cart_odbc_data.eb.pp_data.i_thumbnail[i],
		0, NULL);
		if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
		{
			LOG_ODBC_ERROR(SQL_HANDLE_STMT, odbcc->hstmt);
				return W_ERROR;
		}
	}

	/* generate random item if add_flag==FALSE and empty (i_id, qty) pair*/
	if (odbcd->shopping_cart_odbc_data.eb.sc_size == 0 &&
		odbcd->shopping_cart_odbc_data.eb.add_flag == FALSE)
	{
		odbcd->shopping_cart_odbc_data.eb.i_id =
			(UDWORD) get_random((long long)item_count) + 1;
#ifdef DEBUG
	DEBUGMSG("visiting sc the first time, random i_id %d", odbcd->shopping_cart_odbc_data.eb.i_id);
	DEBUGMSG("visiting sc the first time, random i_id %d", odbcd->shopping_cart_odbc_data.eb.sc_refresh[i].scl_i_id);
#endif /* DEBUG */
	}
	/* Generate random number for Promotional Processing. */
	odbcd->shopping_cart_odbc_data.eb.pp_data.i_id= get_random(item_count)+1;
#ifdef DEBUG
	DEBUGMSG("pp i_id %ld\n",  odbcd->shopping_cart_odbc_data.eb.pp_data.i_id);
#endif

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
