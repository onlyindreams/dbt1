/* orders.c
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2002 Mark Wong & Jenny Zhang &
 *                    Open Source Development Lab, Inc.
 *
 * 17 january 2001
 * TPCW v1.6
 */

#define _LARGEFILE64_SOURCE

#include <stdio.h>
#include <time.h>
#include <datagen.h>
#include <common.h>


/* Clause 4.7.1 */

void gen_orders(int ebs, int items, char *path)
{
	int i, j;
	FILE *orders_file = stdout;
	FILE *order_line_file = stdout;
	FILE *cc_xacts_file = stdout;
	char a_string[1024];
	int customers, orders;
	double o_sub_total, o_tax, o_total;
	struct tm *tm1, *tm2;
	time_t t1, t2;
	int order_line_count;
	char filename1[256];
	char filename2[256];
	char filename3[256];

	sprintf(filename1, "%s/orders.data", path);
	orders_file = fopen64(filename1, "w");
	if (orders_file == NULL)
	{
		fprintf(stderr, "cannot open orders.data\n");
		return;
	}

	sprintf(filename2, "%s/order_line.data", path);
	order_line_file = fopen64(filename2, "w");
	if (order_line_file == NULL)
	{
		fprintf(stderr, "cannot open order_line.data\n");
		return;
	}

	sprintf(filename3, "%s/cc_xacts.data", path);
	cc_xacts_file = fopen64(filename3, "w");
	if (cc_xacts_file == NULL)
	{
		fprintf(stderr, "cannot open cc_xacts.data\n");
		return;
	}

	customers = ebs * 2880;
	orders = (int) (customers * 0.9);

	for (i = 0; i < orders; i++)
	{

		/* Order Line */

		order_line_count = get_random(5) + 1;
		for (j = 0; j < order_line_count; j++)
		{
			/* ol_id */
			fprintf(order_line_file, "\"%d\"", j + 1);
			fprintf(order_line_file, "%c", DELIMITER);

			/* ol_o_id */
			fprintf(order_line_file, "\"%d\"", i + 1);
			fprintf(order_line_file, "%c", DELIMITER);

			/* ol_i_id */
			fprintf(order_line_file, "\"%d\"", (int) get_random(items) + 1);
			fprintf(order_line_file, "%c", DELIMITER);

			/* ol_qty */
			fprintf(order_line_file, "\"%d\"", (int) get_random(300) + 1);
			fprintf(order_line_file, "%c", DELIMITER);

			/* ol_discount */
			fprintf(order_line_file, "\"%0.2f\"",
				(double) get_random(4) / 100.0);
			fprintf(order_line_file, "%c", DELIMITER);

			/* ol_comments */
			get_a_string(a_string, 20, OL_COMMENT_LEN);
			fprintf(order_line_file, "\"%s\"", a_string);

			fprintf(order_line_file, "\n");
		}

		/* Orders */

		/* o_id */
		fprintf(orders_file, "\"%d\"", i + 1);
		fprintf(orders_file, "%c", DELIMITER);

		/* o_c_id */
		fprintf(orders_file, "\"%d\"", (int) get_random(customers) + 1);
		fprintf(orders_file, "%c", DELIMITER);

		/* o_date */
		/* Note that the milliseconds are not calculated. */
		time(&t2);
		t1 = t2 - (86400 + get_random(5184000));
		tm1 = localtime(&t1);
		fprintf(orders_file, "\"%04d%02d%02d%02d%02d%02d000000\"",
			tm1->tm_year + 1900, tm1->tm_mon + 1, tm1->tm_mday, tm1->tm_hour,
			tm1->tm_min, tm1->tm_sec);
		fprintf(orders_file, "%c", DELIMITER);

		/* o_sub_total */
		o_sub_total = (double) (get_random(999990) + 10) / 100.0;
		fprintf(orders_file, "\"%0.2f\"", o_sub_total);
		fprintf(orders_file, "%c", DELIMITER);

		/* o_tax */
		o_tax = o_sub_total * 0.0825;
		fprintf(orders_file, "\"%0.2f\"", o_tax);
		fprintf(orders_file, "%c", DELIMITER);

		/* o_total */
		o_total = o_sub_total + o_tax + order_line_count;
		fprintf(orders_file, "\"%0.2f\"", o_total);
		fprintf(orders_file, "%c", DELIMITER);

		/* o_ship_type */
		fprintf(orders_file, "\"%s\"",
			o_ship_type[get_random(O_SHIP_TYPE_MAX)]);
		fprintf(orders_file, "%c", DELIMITER);

		/* o_ship_date */
		/* Note that the milliseconds are not calculated. */
		t1 += get_random(691200);
		fprintf(orders_file, "\"%04d%02d%02d%02d%02d%02d000000\"",
			tm1->tm_year + 1900, tm1->tm_mon + 1, tm1->tm_mday, tm1->tm_hour,
			tm1->tm_min, tm1->tm_sec);
		fprintf(orders_file, "%c", DELIMITER);

		/* o_bill_addr_id */
		fprintf(orders_file, "\"%d\"", (int) get_random(2 * customers) + 1);
		fprintf(orders_file, "%c", DELIMITER);

		/* o_ship_addr_id */
		fprintf(orders_file, "\"%d\"", (int) get_random(2 * customers) + 1);
		fprintf(orders_file, "%c", DELIMITER);

		/* o_status */
		fprintf(orders_file, "\"%s\"", o_status[get_random(O_STATUS_MAX)]);

		fprintf(orders_file, "\n");


		/* CC Xacts */

		/* cx_o_id */
		fprintf(cc_xacts_file, "\"%d\"", i + 1);
		fprintf(cc_xacts_file, "%c", DELIMITER);

		/* cx_type */
		fprintf(cc_xacts_file, "\"%s\"", cx_type[get_random(CX_TYPE_MAX)]);
		fprintf(cc_xacts_file, "%c", DELIMITER);

		/* cx_num */
		get_n_string(a_string, 16, 16);
		fprintf(cc_xacts_file, "\"%s\"", a_string);
		fprintf(cc_xacts_file, "%c", DELIMITER);

		/* cx_name */
		/* Clause 4.7.1 says this should be an a_string[14..30] but the
		 * column definition in Clause 1.4.7 says it is at least 31. */
		get_a_string(a_string, 14, 30);
		fprintf(cc_xacts_file, "\"%s\"", a_string);
		fprintf(cc_xacts_file, "%c", DELIMITER);

		/* cx_expiry */
		t2 += 864000 + get_random(62294400);
		tm2 = localtime(&t2);
		fprintf(cc_xacts_file, "\"%04d%02d%02d\"", tm2->tm_year + 1900,
			tm2->tm_mon + 1, tm2->tm_mday);
		fprintf(cc_xacts_file, "%c", DELIMITER);

		/* cx_auth_id */
		get_a_string(a_string, CX_AUTH_ID_LEN, CX_AUTH_ID_LEN);
		fprintf(cc_xacts_file, "\"%s\"", a_string);
		fprintf(cc_xacts_file, "%c", DELIMITER);

		/* cx_xact_amt */
		fprintf(cc_xacts_file, "\"%0.2f\"", o_total);
		fprintf(cc_xacts_file, "%c", DELIMITER);

		/* cx_xact_date */
		/* Note that the milliseconds are not calculated. */
		fprintf(cc_xacts_file, "\"%04d%02d%02d%02d%02d%02d000000\"",
			tm1->tm_year + 1900, tm1->tm_mon + 1, tm1->tm_mday, tm1->tm_hour,
			tm1->tm_min, tm1->tm_sec);
		fprintf(cc_xacts_file, "%c", DELIMITER);

		/* cx_co_id */
		fprintf(cc_xacts_file, "\"%d\"", (int) get_random(92) + 1);

		fprintf(cc_xacts_file, "\n");
	}

	fflush(orders_file);
	fflush(order_line_file);
	fflush(cc_xacts_file);
	fclose(orders_file);
	fclose(order_line_file);
	fclose(cc_xacts_file);
}
