/* item.c
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2002 Mark Wong & Jenny Zhang &
 *                    Open Source Development Lab, Inc.
 *
 * 11 january 2001
 * TPCW v1.6
 */

#define _LARGEFILE64_SOURCE

#include <stdio.h>
#include <time.h>
#include <datagen.h>
#include <tpcw.h>
#include <common.h>


/* Clause 4.7.1 */

void gen_items(int items, char *path)
{
	int i;
	FILE *output = stdout;
	char a_string[1024];
	int i1, i2, i3, i4, i5;
	double srp;
	struct tm tm1, *tm2, *tm3;
	time_t t1, t2, t3;
	char filename[256];

	sprintf(filename, "%s/item.data", path);
	output = fopen64(filename, "w");
	if (output == NULL)
	{
		fprintf(stderr, "cannot open item.txt");
		return;
	}

	item_count = items;

	for (i = 0; i < items; i++)
	{

		/* i_id */
		fprintf(output, "\"%d\"", i + 1);
		fprintf(output, "%c", DELIMITER);

		/* i_title */
		fprintf(output, "\"%s\"", mk_title(i+1));
		fprintf(output, "%c", DELIMITER);

		/* i_a_id */
		if (i < items / 4)
		{
			fprintf(output, "\"%d\"", i + 1);
		}
		else
		{
			fprintf(output, "\"%d\"", (int) get_random(items / 4) + 1);
		}
		fprintf(output, "%c", DELIMITER);

		/* i_pub_date */
		tm1.tm_year = 30;
		tm1.tm_mon = 0;
		tm1.tm_mday = 1;
		tm1.tm_sec = 0;
		tm1.tm_min = 0;
		tm1.tm_hour = 0;
		t1 = mktime(&tm1);
		time(&t2);
		tm2 = localtime(&t2);
		t3 = (time_t) (get_percentage() * (double) ((long long) t2 - (long long) t1 + (long long) 86400)) + t1;
		tm3 = localtime(&t3);
		fprintf(output, "\"%04d%02d%02d\"", tm3->tm_year + 1900,
			tm3->tm_mon + 1, tm3->tm_mday);
		fprintf(output, "%c", DELIMITER);

		/* i_publisher */
		get_a_string(a_string, 14, I_PUBLISHER_LEN);
		fprintf(output, "\"%s\"", a_string);
		fprintf(output, "%c", DELIMITER);

		/* i_subject */
		fprintf(output, "\"%s\"", i_subject[(int) get_random(I_SUBJECT_MAX)]);
		fprintf(output, "%c", DELIMITER);

		/* i_desc */
		get_a_string(a_string, 100, I_DESC_LEN);
		fprintf(output, "\"%s\"", a_string);
		fprintf(output, "%c", DELIMITER);

		/* i_related1 */
		i1 = get_random(items) + 1;
		fprintf(output, "\"%d\"", i1);
		fprintf(output, "%c", DELIMITER);

		/* i_related2 */
		do
		{
			i2 = get_random(items) + 1;
		}
		while (i2 == i1);
		fprintf(output, "\"%d\"", i2);
		fprintf(output, "%c", DELIMITER);

		/* i_related3 */
		do
		{
			i3 = get_random(items) + 1;
		}
		while (i3 == i1 || i3 == i2);
		fprintf(output, "\"%d\"", i3);
		fprintf(output, "%c", DELIMITER);

		/* i_related4 */
		do
		{
			i4 = get_random(items) + 1;
		}
		while (i4 == i1 || i4 == i2 || i4 == i3);
		fprintf(output, "\"%d\"", i4);
		fprintf(output, "%c", DELIMITER);

		/* i_related5 */
		do
		{
			i5 = get_random(items) + 1;
		}
		while (i5 == i1 || i5 == i2 || i5 == i3 || i5 == i4);
		fprintf(output, "\"%d\"", i5);
		fprintf(output, "%c", DELIMITER);

		/* i_thumbnail */
		fprintf(output, "\"%d\"", i + 1);
		fprintf(output, "%c", DELIMITER);

		/* i_image */
		fprintf(output, "\"%d\"", i + 1);
		fprintf(output, "%c", DELIMITER);

		/* i_srp */
		srp = (get_random(999900) + 100.0) / 100;
		fprintf(output, "\"%0.2f\"", srp);
		fprintf(output, "%c", DELIMITER);

		/* i_cost */
		fprintf(output, "\"%0.2f\"",
			(1.0 - ((double) get_random(6) / 10.0)) * srp);
		fprintf(output, "%c", DELIMITER);

		/* i_avail */
		/* 86400 is the number of seconds in a day, and 2505600 is the number of
		 * seconds in 29 days. */
		t3 += 86400 + (time_t) get_random(2505601);
		tm3 = localtime(&t3);
		fprintf(output, "\"%04d%02d%02d\"", tm3->tm_year + 1900,
			tm3->tm_mon + 1, tm3->tm_mday);
		fprintf(output, "%c", DELIMITER);

		/* i_stock */
		fprintf(output, "\"%d\"", (int) get_random(21) + 10);
		fprintf(output, "%c", DELIMITER);

		/* i_isbn */
		get_a_string(a_string, 13, I_ISBN_LEN);
		fprintf(output, "\"%s\"", a_string);
		fprintf(output, "%c", DELIMITER);

		/* i_page */
		fprintf(output, "\"%d\"", (int) get_random(9980) + 20);
		fprintf(output, "%c", DELIMITER);

		/* i_backing */
		fprintf(output, "\"%s\"", i_backing[get_random(I_BACKING_MAX)]);
		fprintf(output, "%c", DELIMITER);

		/* i_dimensions */
		/* Clause 4.6.2.17 */
		fprintf(output, "\"%0.2fx%0.2fx%0.2f\"",
			(double) (get_random(9999) + 1) / 100.0, (double) (get_random(9999) + 1) / 100.0, (double) (get_random(9999) + 1) / 100.0);

		fprintf(output, "\n");
	}

	fflush(output);
	fclose(output);
}
