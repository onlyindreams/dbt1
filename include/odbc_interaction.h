/*
 * odbc_interaction.h
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2002 Mark Wong & Jenny Zhang &
 *                    Open Source Development Lab, Inc.
 *
 * 18 february 2002
 *
 * Note that ODBC doesn't appear to have a type definition to support 64 bit
 * integeters.  This makes the application non-complient.
 */

#ifndef _ODBC_INTERACTION_H_
#define _ODBC_INTERACTION_H_

#include <WINDOWS.H>
#include <sqltypes.h>
#include <common.h>

#define LOG_ODBC_ERROR(type, handle) odbc_error(__FILE__, __LINE__, type, handle)

struct promotional_processing_odbc_t
{
	UDWORD i_id;
	UDWORD i_related[PROMOTIONAL_ITEMS_MAX];
	UDWORD i_thumbnail[PROMOTIONAL_ITEMS_MAX];
};

struct shopping_cart_refresh_odbc_t
{
	UDWORD scl_i_id;
	SWORD scl_qty;
};

struct shopping_cart_line_odbc_t
{
	UDWORD scl_i_id;
	SWORD scl_qty;
	SDOUBLE scl_cost;
	SDOUBLE scl_srp;
	UCHAR i_title[I_TITLE_LEN + 1];
	UCHAR i_backing[I_BACKING_LEN + 1];
};

struct address_odbc_t
{
	UCHAR addr_street1[ADDR_STREET1_LEN + 1];
	UCHAR addr_street2[ADDR_STREET2_LEN + 1];
	UCHAR addr_city[ADDR_CITY_LEN + 1];
	UCHAR addr_state[ADDR_STATE_LEN + 1];
	UCHAR addr_zip[ADDR_ZIP_LEN + 1];
	UCHAR co_name[CO_NAME_LEN + 1];
};

struct search_results_line_odbc_t
{
	UDWORD i_id;
	UCHAR i_title[I_TITLE_LEN + 1];
	UCHAR a_fname[A_FNAME_LEN + 1];
	UCHAR a_lname[A_LNAME_LEN + 1];
};

/* Clause 2.16 */
struct admin_confirm_odbc_t
{
	/* Input data. */
	UDWORD i_id;

	/* Input and output data. */
	UDWORD i_image;
	UDWORD i_thumbnail;
	SDOUBLE i_cost;

	/* Output data. */
	UCHAR i_title[I_TITLE_LEN + 1];
	UCHAR a_fname[A_FNAME_LEN + 1];
	UCHAR a_lname[A_LNAME_LEN + 1];
	UCHAR i_subject[I_SUBJECT_LEN + 1];
	UCHAR i_desc[I_DESC_LEN + 1];
	SDOUBLE i_srp;
	UCHAR i_backing[I_BACKING_LEN + 1];
	SWORD i_page;
	UCHAR i_publisher[I_PUBLISHER_LEN + 1];
	UCHAR i_pub_date[I_PUB_DATE_LEN + 1];
	UCHAR i_dimensions[I_DIMENSIONS_LEN + 1];
	UCHAR i_isbn[I_ISBN_LEN + 1];
};

/* Clause 2.15 */
struct admin_request_odbc_t
{
	/* Input data. */
	UDWORD i_id;

	/* Output data. */
	SDOUBLE i_srp;
	SDOUBLE i_cost;
	UCHAR i_title[I_TITLE_LEN + 1];
	UDWORD i_image;
	UDWORD i_thumbnail;
	UCHAR a_fname[A_FNAME_LEN + 1];
	UCHAR a_lname[A_LNAME_LEN + 1];
};

/* Clause 2.13 */
struct best_sellers_odbc_t
{
	/* Input data. */
	UCHAR i_subject[I_SUBJECT_LEN + 1];

	/* Output data. */
	SWORD items;
	struct search_results_line_odbc_t results_data[SEARCH_RESULT_ITEMS_MAX];
	struct promotional_processing_odbc_t pp_data;
};

/* Clause 2.7 */
struct buy_confirm_odbc_t
{
	/* Input data. */
	UDWORD sc_id;
	UDWORD c_id;
	UCHAR cx_type[CX_TYPE_LEN + 1];
	UCHAR cx_num[CX_NUM_LEN + 1];
	UCHAR cx_name[CX_NAME_LEN + 1];
	UCHAR cx_expiry[CX_EXPIRY_LEN + 1];
	UCHAR o_ship_type[O_SHIP_TYPE_LEN + 1];
	SWORD update_address;
	struct address_odbc_t shipping;
	/* temp variables */
	SWORD ship_day;
	UCHAR ol_comment[OL_COMMENT_LEN + 1];
	UCHAR cx_auth_id[CX_AUTH_ID_LEN + 1];

	/* Output data. */
	UDWORD o_id;
	SDWORD sc_size;
	struct shopping_cart_line_odbc_t scl_data[SHOPPING_CART_ITEMS_MAX];
	SDOUBLE sc_sub_total;
	SDOUBLE sc_tax;
	SDOUBLE sc_ship_cost;
	SDOUBLE sc_total;
	SDOUBLE c_discount;
};

/* Clause 2.6 */
struct buy_request_odbc_t
{
	/* Input data. */
	SWORD returning_flag;
	UCHAR c_uname[C_UNAME_LEN + 1];
	UCHAR c_passwd[C_PASSWD_LEN + 1];
	SDOUBLE c_discount;
	UDWORD sc_id;
	/* if returning_flag=1 output else input */
	UCHAR c_fname[C_FNAME_LEN + 1];
	UCHAR c_lname[C_LNAME_LEN + 1];
	struct address_odbc_t address;
	UCHAR c_phone[C_PHONE_LEN + 1];
	UCHAR c_email[C_EMAIL_LEN + 1];
	UCHAR c_birthdate[C_BIRTHDATE_LEN + 1];
	UCHAR c_data[C_DATA_LEN + 1];

	/* Output data. */
	SWORD sc_size;
	struct shopping_cart_line_odbc_t scl_data[SHOPPING_CART_ITEMS_MAX];
	SDOUBLE sc_sub_total;
	SDOUBLE sc_tax;
	SDOUBLE sc_ship_cost;
	SDOUBLE sc_total;
	UDWORD c_id;
};

/* Clause 2.3 */
struct home_odbc_t
{
	/* Input data. */
	UDWORD c_id;

	/* Output data. */
	UCHAR c_fname[C_FNAME_LEN + 1];
	UCHAR c_lname[C_LNAME_LEN + 1];
	struct promotional_processing_odbc_t pp_data;
};

/* Clause 2.12 */
struct new_products_odbc_t
{
	/* Input data. */
	UCHAR i_subject[I_SUBJECT_LEN + 1];

	/* Output data. */
	SWORD items;
	struct promotional_processing_odbc_t pp_data;
	struct search_results_line_odbc_t results_data[SEARCH_RESULT_ITEMS_MAX];
};

struct order_display_line_odbc_t
{
	UDWORD ol_i_id;
	UCHAR i_title[I_TITLE_LEN + 1];
	UCHAR i_publisher[I_PUBLISHER_LEN + 1];
	SDOUBLE i_cost;
	SWORD ol_qty;
	SDOUBLE ol_discount;
	UCHAR ol_comment[OL_COMMENT_LEN + 1];
};

/* Clause 2.9 */
struct order_display_odbc_t
{
	/* Input data. */
	UCHAR c_uname[C_UNAME_LEN + 1];
	UCHAR c_passwd[C_UNAME_LEN + 1];

	/* Output data. */
	SWORD items;
	UDWORD o_id;
	UCHAR c_fname[C_FNAME_LEN + 1];
	UCHAR c_lname[C_LNAME_LEN + 1];
	UCHAR c_phone[C_PHONE_LEN + 1];
	UCHAR c_email[C_EMAIL_LEN + 1];
	UCHAR o_date[O_DATE_LEN + 1];
	SDOUBLE o_sub_total;
	SDOUBLE o_tax;
	SDOUBLE o_total;
	UCHAR o_ship_type[O_SHIP_TYPE_LEN + 1];
	UCHAR o_ship_date[O_SHIP_DATE_LEN + 1];
	UCHAR o_status[O_STATUS_LEN + 1];
	struct address_odbc_t billing;
	struct address_odbc_t shipping;
	struct order_display_line_odbc_t odl_data[SHOPPING_CART_ITEMS_MAX];
	UCHAR cx_type[CX_TYPE_LEN + 1];
	UCHAR cx_auth_id[CX_AUTH_ID_LEN + 1];
};

/* Clause 2.8 */
struct order_inquiry_odbc_t
{
	/* Input data. */
	UDWORD c_id;

	/* Output data. */
	UCHAR c_uname[C_UNAME_LEN + 1];
};

/* Clause 2.14 */
struct product_detail_odbc_t
{
	/* Input data. */
	UDWORD i_id;

	/* Output data. */
	UCHAR i_title[I_TITLE_LEN + 1];
	UCHAR a_fname[A_FNAME_LEN + 1];
	UCHAR a_lname[A_LNAME_LEN + 1];
	UCHAR i_pub_date[I_PUB_DATE_LEN + 1];
	UCHAR i_publisher[I_PUBLISHER_LEN + 1];
	UCHAR i_subject[I_SUBJECT_LEN + 1];
	UCHAR i_desc[I_DESC_LEN + 1];
	UDWORD i_image;
	SDOUBLE i_cost;
	SDOUBLE i_srp;
	UCHAR i_avail[I_AVAIL_LEN + 1];
	UCHAR i_isbn[I_ISBN_LEN + 1];
	SWORD i_page;
	UCHAR i_backing[I_BACKING_LEN + 1];
	UCHAR i_dimensions[I_DIMENSIONS_LEN + 1];
};

/* Clause 2.10 */
struct search_request_odbc_t
{
	/* Output data. */
	struct promotional_processing_odbc_t pp_data;
};

/* Clause 2.11 */
struct search_results_odbc_t
{
	/* Input data. */
	SWORD search_type;
	UCHAR search_string[SEARCH_STRING_LEN + 1];

	/* Output data. */
	SWORD items;
	struct promotional_processing_odbc_t pp_data;
	struct search_results_line_odbc_t results_data[SEARCH_RESULT_ITEMS_MAX];
};

/* Clause 2.4 */
struct shopping_cart_odbc_t
{
	/* Input data. */
	SWORD add_flag;
	UDWORD c_id;
	struct shopping_cart_refresh_odbc_t sc_refresh[SHOPPING_CART_ITEMS_MAX];
	/* used for first visiting(as temp variable holding random i_id) 
	 * or adding item to shopping_cart(as input data)*/
	UDWORD i_id;
	/* Input and output data. */
	UDWORD sc_id;
	SWORD sc_size;
	/* output data */
	struct promotional_processing_odbc_t pp_data;
	struct shopping_cart_line_odbc_t scl_data[SHOPPING_CART_ITEMS_MAX];
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
#endif /* _ODBC_INTERACTION_H_ */
