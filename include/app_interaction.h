/* app_interaction.h
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2002 Mark Wong & Jenny Zhang &
 *                    Open Source Development Lab, Inc.
 *
 */

#ifndef _APP_INTERACTION_H_
#define _APP_INTERACTION_H_

#include <WINDOWS.H>
#include <sqltypes.h>
#include <common.h>
#include <eu.h>

#define LOG_ODBC_ERROR(type, handle) odbc_error(__FILE__, __LINE__, type, handle)

/* Clause 2.16 */
struct admin_confirm_odbc_t
{
	struct admin_confirm_t eb;
};

/* Clause 2.15 */
struct admin_request_odbc_t
{
	struct admin_request_t eb;
};

/* Clause 2.13 */
struct best_sellers_odbc_t
{
	struct best_sellers_t eb;
};

/* Clause 2.7 */
struct buy_confirm_odbc_t
{
	struct buy_confirm_t eb;
	/* temp variables */
	short int ship_day;
	char ol_comment[OL_COMMENT_LEN + 1];
	char cx_auth_id[CX_AUTH_ID_LEN + 1];
	double c_discount;
};

/* Clause 2.6 */
struct buy_request_odbc_t
{
	struct buy_request_t eb;
};

/* Clause 2.3 */
struct home_odbc_t
{
	struct home_t eb;
};

/* Clause 2.12 */
struct new_products_odbc_t
{
	struct new_products_t eb;
};

/* Clause 2.9 */
struct order_display_odbc_t
{
	struct order_display_t eb;
};

/* Clause 2.8 */
struct order_inquiry_odbc_t
{
	struct order_inquiry_t eb;
};

/* Clause 2.14 */
struct product_detail_odbc_t
{
	struct product_detail_t eb;
};

/* Clause 2.10 */
struct search_request_odbc_t
{
	struct search_request_t eb;
};

/* Clause 2.11 */
struct search_results_odbc_t
{
	struct search_results_t eb;
};

/* Clause 2.4 */
struct shopping_cart_odbc_t
{
	struct shopping_cart_t eb;
};

struct odbc_context_t
{
	SQLHDBC hdbc;
	SQLHSTMT hstmt;
};

union odbc_data_t
{
	struct admin_confirm_odbc_t admin_confirm_odbc_data;
	struct admin_request_odbc_t admin_request_odbc_data;
	struct best_sellers_odbc_t best_sellers_odbc_data;
	struct buy_confirm_odbc_t buy_confirm_odbc_data;
	struct buy_request_odbc_t buy_request_odbc_data;
	struct home_odbc_t home_odbc_data;
	struct new_products_odbc_t new_products_odbc_data;
	struct order_display_odbc_t order_display_odbc_data;
	struct order_inquiry_odbc_t order_inquiry_odbc_data;
	struct product_detail_odbc_t product_detail_odbc_data;
	struct search_request_odbc_t search_request_odbc_data;
	struct search_results_odbc_t search_results_odbc_data;
	struct shopping_cart_odbc_t shopping_cart_odbc_data;
};

/* Prototypes */
int odbc_connect(struct odbc_context_t *odbcc);
int odbc_disconnect(struct odbc_context_t *odbcc);
int odbc_error(char *filename, int lin, SQLSMALLINT handle_type,
	SQLHANDLE handle);
int odbc_init(char *sname, char *uname, char *auth);
#endif /* _APP_INTERACTION_H_ */
