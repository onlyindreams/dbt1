/*
 * pgsql_interaction_debug.c -  debug routines for pgsql interface.
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2003 Satoshi Nagayasu & Hideyuki Kawashima &
 *                    Sachi Osawa & Hirokazu Kondo & Satoru Satake
 *
 * $Id$
 */
#include <libpq_interaction.h>

void
print_admin_request_data(struct admin_request_t *data)
{
	fprintf(stderr, "=== admin_request ===\n");
	fprintf(stderr, "INPUT\n");
	fprintf(stderr, "  i_id: %lld\n", data->i_id);
	fprintf(stderr, "OUTPUT\n");
	fprintf(stderr, "  i_srp: %f\n", data->i_srp);
	fprintf(stderr, "  i_cost: %f\n", data->i_cost);
	fprintf(stderr, "  i_title: %s\n", data->i_title);
	fprintf(stderr, "  i_image: %lld\n", data->i_image);
	fprintf(stderr, "  i_thumbnail: %lld\n", data->i_thumbnail);
	fprintf(stderr, "  a_fname: %s\n", data->a_fname);
	fprintf(stderr, "  a_lname: %s\n", data->a_lname);
}

void
print_admin_confirm_data(struct admin_confirm_t *data)
{
	fprintf(stderr, "=== admin_confirm ===\n");
	fprintf(stderr, "INPUT\n");
	fprintf(stderr, "  i_id: %lld\n", data->i_id);
	fprintf(stderr, "  i_image: %lld\n", data->i_image);
	fprintf(stderr, "  i_thumbnail: %lld\n", data->i_thumbnail);
	fprintf(stderr, "  i_cost: %f\n", data->i_cost);
	fprintf(stderr, "OUPUT\n");
	fprintf(stderr, "  i_title: %s\n", data->i_title);
	fprintf(stderr, "  a_fname: %s\n", data->a_fname);
	fprintf(stderr, "  a_lname: %s\n", data->a_lname);
	fprintf(stderr, "  i_subject: %s\n", data->i_subject);
	fprintf(stderr, "  i_desc: %s\n", data->i_desc);
	fprintf(stderr, "  i_srp: %f\n", data->i_srp);
	fprintf(stderr, "  i_backing: %s\n", data->i_backing);
	fprintf(stderr, "  i_page: %d\n", data->i_page);
	fprintf(stderr, "  i_publisher: %s\n", data->i_publisher);
	fprintf(stderr, "  i_pub_date: %s\n", data->i_pub_date);
	fprintf(stderr, "  i_dimensions: %s\n", data->i_dimensions);
	fprintf(stderr, "  i_isbn: %s\n", data->i_isbn);
}

void
print_product_detail_data(struct product_detail_t *data)
{
	fprintf(stderr, "=== product_detail ===\n");
	fprintf(stderr, "INPUT\n");
	fprintf(stderr, "  i_id: %lld\n", data->i_id);
	fprintf(stderr, "OUTPUT\n");
	fprintf(stderr, "  i_title: %s\n", data->i_title);
	fprintf(stderr, "  a_fname: %s\n", data->a_fname);
	fprintf(stderr, "  a_lname: %s\n", data->a_lname);
	fprintf(stderr, "  i_pub_date: %s\n", data->i_pub_date);
	fprintf(stderr, "  i_publisher: %s\n", data->i_publisher);
	fprintf(stderr, "  i_subject: %s\n", data->i_subject);
	fprintf(stderr, "  i_desc: %s\n", data->i_desc);
	fprintf(stderr, "  i_image: %lld\n", data->i_image);
	fprintf(stderr, "  i_cost: %f\n", data->i_cost);
	fprintf(stderr, "  i_srp: %f\n", data->i_srp);
	fprintf(stderr, "  i_avail: %s\n", data->i_avail);
	fprintf(stderr, "  i_isbn: %s\n", data->i_isbn);
	fprintf(stderr, "  i_page: %d\n", data->i_page);
	fprintf(stderr, "  i_backing: %s\n", data->i_backing);
	fprintf(stderr, "  i_dimensions: %s\n", data->i_dimensions);
}

void
print_shopping_cart_data(struct shopping_cart_t *data)
{
	int i;

	fprintf(stderr, "=== shopping_cart ===\n");
	fprintf(stderr, "INPUT\n");
	fprintf(stderr, "  c_id: %lld\n", data->c_id);
	fprintf(stderr, "  sc_id: %lld\n", data->sc_id);
	fprintf(stderr, "  sc_size: %d\n", data->sc_size);
	fprintf(stderr, "  add_flag: %d\n", data->add_flag);
	fprintf(stderr, "  i_id: %lld\n", data->i_id);
	fprintf(stderr, "  pp_data.i_id: %lld\n", data->pp_data.i_id);
	for (i=0 ; i<SHOPPING_CART_ITEMS_MAX ; i++)
	{
		fprintf(stderr, "  sc_refresh[%d].scl_i_id: %lld\n", i, data->sc_refresh[i].scl_i_id);
		fprintf(stderr, "  sc_refresh[%d].scl_qty: %d\n", i, data->sc_refresh[i].scl_qty);
	}

	fprintf(stderr, "OUTPUT\n");
	fprintf(stderr, "  sc_id: %lld\n", data->sc_id);
	fprintf(stderr, "  sc_size: %d\n", data->sc_size);

	for (i=0 ; i<data->sc_size ; i++)
	{
		fprintf(stderr, "  scl_data[%d].scl_i_id: %lld\n", i, data->scl_data[i].scl_i_id);
		fprintf(stderr, "  scl_data[%d].i_title: %s\n", i, data->scl_data[i].i_title);
		fprintf(stderr, "  scl_data[%d].scl_cost: %f\n", i, data->scl_data[i].scl_cost);
		fprintf(stderr, "  scl_data[%d].scl_srp: %f\n", i, data->scl_data[i].scl_srp);
		fprintf(stderr, "  scl_data[%d].i_backing: %s\n", i, data->scl_data[i].i_backing);
	}

	for (i=0 ; i<PROMOTIONAL_ITEMS_MAX ; i++)
	{
		fprintf(stderr, "  pp_data.i_related[%d]: %lld\n", i, data->pp_data.i_related[i]);
		fprintf(stderr, "  pp_data.i_thumbnail[%d]: %lld\n", i, data->pp_data.i_thumbnail[i]);
	}
}

void
print_home_data(struct home_t *data)
{
	int i;

	fprintf(stderr, "=== home ===\n");
	fprintf(stderr, "INPUT\n");
	fprintf(stderr, "  c_id: %lld\n", data->c_id);
	fprintf(stderr, "  pp_data.i_id: %lld\n", data->pp_data.i_id);

	fprintf(stderr, "OUTPUT\n");
	fprintf(stderr, "  c_fname: %s\n", data->c_fname);
	fprintf(stderr, "  c_lname: %s\n", data->c_lname);

	for (i = 0; i < PROMOTIONAL_ITEMS_MAX; i++)
	{
		fprintf(stderr, "  i_related[%d]: %lld\n", i, data->pp_data.i_related[i]);
		fprintf(stderr, "  i_thumbnail[%d]: %lld\n", i, data->pp_data.i_thumbnail[i]);
	}
}

void
print_best_sellers_data(struct best_sellers_t *data)
{
	int i;

	fprintf(stderr, "=== best_sellers ===\n");
	fprintf(stderr, "INPUT\n");
	fprintf(stderr, "  c_subject: %s\n", data->i_subject);
	fprintf(stderr, "  pp_data.i_id: %lld\n", data->pp_data.i_id);

	fprintf(stderr, "OUTPUT\n");
	fprintf(stderr, "  items: %d\n", data->items);

	for (i = 0; i < PROMOTIONAL_ITEMS_MAX; i++)
	{
		fprintf(stderr, "  data->pp_data.i_related[%d]: %lld\n", i, data->pp_data.i_related[i]);
		fprintf(stderr, "  data->pp_data.i_thumbnail[%d]: %lld\n", i, data->pp_data.i_thumbnail[i]);
	}

	for (i = 0; i < SEARCH_RESULT_ITEMS_MAX; i++)
	{
		fprintf(stderr, "  data->results_data[%d].i_id: %lld\n", i, data->results_data[i].i_id);
		fprintf(stderr, "  data->results_data[%d].i_title: %s\n", i, data->results_data[i].i_title);
		fprintf(stderr, "  data->results_data[%d].a_fname: %s\n", i, data->results_data[i].a_fname);
		fprintf(stderr, "  data->results_data[%d].a_lname: %s\n", i, data->results_data[i].a_lname);
	}
}

void
print_buy_request_data(struct buy_request_t *data)
{
	int i;

	fprintf(stderr, "=== buy_request ===\n");

	fprintf(stderr, "INPUT\n");

	fprintf(stderr, "OUTPUT\n");
	fprintf(stderr, "  c_discount: %f\n", data->c_discount);
#ifdef NOT_USED
	j++; /* c_fname */
	j++; /* c_lname */
	j++; /* addr_street1 */
	j++; /* addr_street2 */
	j++; /* addr_city */
	j++; /* addr_state */
	j++; /* addr_zip */
	j++; /* co_name */
	j++; /* c_phone */
	j++; /* c_email */
	j++; /* c_birthday */
	j++; /* c_data */
	j++; /* c_passwd */
#endif
	fprintf(stderr, "  c_id: %lld\n", data->c_id);
	fprintf(stderr, "  sc_sub_total: %f\n", data->sc_sub_total);
	fprintf(stderr, "  sc_tax: %f\n", data->sc_tax);
	fprintf(stderr, "  sc_ship_cost: %f\n", data->sc_ship_cost);
	fprintf(stderr, "  sc_total: %f\n", data->sc_total);
	fprintf(stderr, "  sc_size: %d\n", data->sc_size);

	for (i=0 ; i<SHOPPING_CART_ITEMS_MAX ; i++)
	{
		fprintf(stderr, "  scl_data[%d].scl_i_id: %lld\n", i, data->scl_data[i].scl_i_id);

		fprintf(stderr, "  scl_data[%d].i_title: %s\n", i, data->scl_data[i].i_title);

		fprintf(stderr, "  scl_data[%d].scl_cost: %f\n", i, data->scl_data[i].scl_cost);
		fprintf(stderr, "  scl_data[%d].scl_srp: %f\n", i, data->scl_data[i].scl_srp);

		fprintf(stderr, "  scl_data[%d].i_backing: %s\n", i, data->scl_data[i].i_backing);

		fprintf(stderr, "  scl_data[%d].scl_qty: %d\n", i, data->scl_data[i].scl_qty);
	}
}

void
print_buy_confirm_data(struct buy_confirm_t *data)
{
	fprintf(stderr, "=== buy_confirm ===\n");
	fprintf(stderr, "=== NOT IMPLEMENTED YET ===\n");
}

void
print_new_products_data(struct new_products_t *data)
{
	int i;
	fprintf(stderr, "=== new_products ===\n");
	fprintf(stderr, "INPUT\n");
	fprintf(stderr, "  i_subject: %s\n", data->i_subject);
	fprintf(stderr, "  pp_data.i_id: %lld\n", data->pp_data.i_id);
	fprintf(stderr, "OUTPUT\n");

	for (i=0 ; i<PROMOTIONAL_ITEMS_MAX ; i++)
		fprintf(stderr, "  pp_data.i_related[%d]: %lld\n", i, data->pp_data.i_related[i]);

	for (i=0 ; i<PROMOTIONAL_ITEMS_MAX ; i++)
		fprintf(stderr, "  pp_data.i_thumbnail[%d]: %lld\n", i, data->pp_data.i_thumbnail[i]);

	fprintf(stderr, "  items: %d\n", data->items);

	for (i=0 ; i<SEARCH_RESULT_ITEMS_MAX ; i++)
	{
		fprintf(stderr, "  results_data[%d].i_id: %lld\n", i, data->results_data[i].i_id);
		fprintf(stderr, "  results_data[%d].i_title: %s\n", i, data->results_data[i].i_title);
		fprintf(stderr, "  results_data[%d].a_fname: %s\n", i, data->results_data[i].a_fname);
		fprintf(stderr, "  results_data[%d].a_lname: %s\n", i, data->results_data[i].a_lname);
	}

}

void
print_order_display_data(struct order_display_t *data)
{
	fprintf(stderr, "=== order_display ===\n");
	fprintf(stderr, "=== NOT IMPLEMENTED YET ===\n");
}

void
print_order_inquiry_data(struct order_inquiry_t *data)
{
	fprintf(stderr, "=== order_inquiry ===\n");
	fprintf(stderr, "INPUT\n");
	fprintf(stderr, "  c_id: %lld\n", data->c_id);

	fprintf(stderr, "OUTPUT\n");
	fprintf(stderr, "  c_uname: %s\n", data->c_uname);
}

void
print_search_request_data(struct search_request_t *data)
{
	int i;

	fprintf(stderr, "=== search_request ===\n");
	fprintf(stderr, "INPUT\n");
	fprintf(stderr, "  pp_data.i_id: %lld\n", data->pp_data.i_id);

	fprintf(stderr, "OUTPUT\n");

	for (i=0 ; i<PROMOTIONAL_ITEMS_MAX ; i++)
	{
		fprintf(stderr, "  pp_data.i_related[%d]: %lld\n", i, data->pp_data.i_related[i]);
		fprintf(stderr, "  pp_data.i_thumbnail[%d]: %lld\n", i, data->pp_data.i_thumbnail[i]);
	}

}

void
print_search_results_data(struct search_results_t *data)
{
	int i;

	fprintf(stderr, "=== search_request ===\n");
	fprintf(stderr, "INPUT\n");
	fprintf(stderr, "  (search type): %d\n", data->search_type);
	fprintf(stderr, "  search_string: %s\n", data->search_string);
	fprintf(stderr, "  pp_data.i_id: %lld\n", data->pp_data.i_id);

	fprintf(stderr, "OUTPUT\n");

	for (i = 0; i < PROMOTIONAL_ITEMS_MAX; i++)
		fprintf(stderr, "  pp_data.i_related[%d]: %lld\n", i, data->pp_data.i_related[i]);

	for (i = 0; i < PROMOTIONAL_ITEMS_MAX; i++)
		fprintf(stderr, "  pp_data.i_thumbnail[%d]: %lld\n", i, data->pp_data.i_thumbnail[i]);

	fprintf(stderr, "  items: %d\n", data->items);

	for (i=0 ; i<SEARCH_RESULT_ITEMS_MAX ; i++)
	{
		fprintf(stderr, "  results_data[%d].i_id: %lld\n", i, data->results_data[i].i_id);

		fprintf(stderr, "  results_data[%d].i_title: %s\n", i, data->results_data[i].i_title);
		fprintf(stderr, "  results_data[%d].a_fname: %s\n", i, data->results_data[i].a_fname);
		fprintf(stderr, "  results_data[%d].a_lname: %s\n", i, data->results_data[i].a_lname);
	}
}
