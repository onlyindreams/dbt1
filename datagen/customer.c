/* customer.c
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2002 Mark Wong & Jenny Zhang &
 *                    Open Source Development Lab, Inc.
 *
 * 14 january 2001
 * TPCW v1.6
 */

#define _LARGEFILE64_SOURCE

#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include <datagen.h>
#include <common.h>


/* Clause 4.7.1 */

void gen_customers(int ebs, char *path)
{
	int i, j;
	int customers;
	FILE *output = stdout;
	char a_string[1024];
	char c_uname[C_UNAME_LEN + 1];
	int max;
	struct tm *tm1, *tm2, *tm3;
	time_t t1, t2, t3;
	char filename[256];

	sprintf(filename, "%s/customer.data", path);
	output = fopen64(filename, "w");
	if (output == NULL)
	{
		fprintf(stderr, "cannot open customer.data\n");
		return;
	}

	customers = 2880 * ebs;
	for (i = 0; i < customers; i++)
	{

		/* c_id */
		fprintf(output, "\"%d\"", i + 1);
		fprintf(output, "%c", DELIMITER);

		/* c_uname */
		/* Clause 4.6.2.10 */
		digsyl2(c_uname, i + 1, 0);
		fprintf(output, "\"%s\"", c_uname);
		fprintf(output, "%c", DELIMITER);

		/* c_passwd */
		/* Clause 4.6.2.11 */
		max = strlen(c_uname);
		fprintf(output, "\"");
		for (j = 0; j < max; j++)
		{
			fprintf(output, "%c", (char) tolower(c_uname[j]));
		}
		fprintf(output, "\"%c", DELIMITER);

		/* c_lname */
		get_a_string(a_string, 8, C_LNAME_LEN);
		fprintf(output, "\"%s\"", a_string);
		fprintf(output, "%c", DELIMITER);

		/* c_fname */
		get_a_string(a_string, 8, C_FNAME_LEN);
		fprintf(output, "\"%s\"", a_string);
		fprintf(output, "%c", DELIMITER);

		/* c_addr_id */
		fprintf(output, "\"%d\"", (int) get_random(2 * customers) + 1);
		fprintf(output, "%c", DELIMITER);

		/* c_phone */
		get_n_string(a_string, 9, C_PHONE_LEN);
		fprintf(output, "\"%s\"", a_string);
		fprintf(output, "%c", DELIMITER);

		/* c_email */
		/* Clause 6.4.2.14 */
		get_a_string(a_string, 2, 9);
		fprintf(output, "\"%s@%s\"", c_uname, a_string);
		fprintf(output, "%c", DELIMITER);

		/* c_since */
		time(&t2);
		t1 = t2 - (86400 + get_random(63072000));
		tm1 = localtime(&t1);
		fprintf(output, "\"%04d%02d%02d\"", tm1->tm_year + 1900,
			tm1->tm_mon + 1, tm1->tm_mday);
		fprintf(output, "%c", DELIMITER);

		/* c_last_visit */
		t3 = t1 + get_random(5270400);
		if (t3 > t2)
		{
			t3 = t2;
		}
		tm3 = localtime(&t3);
		fprintf(output, "\"%04d%02d%02d\"", tm3->tm_year + 1900,
			tm3->tm_mon + 1, tm3->tm_mday);
		fprintf(output, "%c", DELIMITER);

		/* c_login */
		/* This should be changed to the date and time the table is
		 * populated. Note that the milliseconds are not calculated. */
		tm2 = localtime(&t2);
		fprintf(output, "\"%04d%02d%02d%02d%02d%02d000000\"",
			tm2->tm_year + 1900, tm2->tm_mon + 1, tm2->tm_mday, tm2->tm_hour,
			tm2->tm_min, tm2->tm_sec);
		fprintf(output, "%c", DELIMITER);

		/* c_expiration */
		t2 += 7200;
		tm2 = localtime(&t2);
		fprintf(output, "\"%04d%02d%02d%02d%02d%02d000000\"",
			tm2->tm_year + 1900, tm2->tm_mon + 1, tm2->tm_mday, tm2->tm_hour,
			tm2->tm_min, tm2->tm_sec);
		fprintf(output, "%c", DELIMITER);

		/* c_discount */
		fprintf(output, "\"%0.2f\"", (double) get_random(51) / 100.0);
		fprintf(output, "%c", DELIMITER);

		/* c_balance */
		fprintf(output, "\"0.0\"");
		fprintf(output, "%c", DELIMITER);

		/* c_ytd_pmt */
		fprintf(output, "\"%0.2f\"", (double) get_random(100000) / 100.0);
		fprintf(output, "%c", DELIMITER);

		/* c_birthdate */
		/* The date is being calculated from 1900 instead of 1880. */
		tm1->tm_year = 0;
		tm1->tm_mon = 0;
		tm1->tm_mday = 1;
		tm1->tm_sec = 0;
		tm1->tm_min = 0;
		tm1->tm_hour = 0;
		t1 = mktime(tm1);
		time(&t2);
		tm2 = localtime(&t2);
		t3 = (time_t) (get_percentage() * (double) ((long long) t2 - (long long) t1 + (long long) 86400)) + t1;
		tm3 = localtime(&t3);
		fprintf(output, "\"%04d%02d%02d\"", tm3->tm_year + 1900,
			tm3->tm_mon + 1, tm3->tm_mday);
		fprintf(output, "%c", DELIMITER);

		/* c_data */
		get_a_string(a_string, 100, C_DATA_LEN);
		fprintf(output, "\"%s\"", a_string);

		fprintf(output, "\n");
	}

	fflush(output);
	fclose(output);
}
