/* author.c
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


#include <stdio.h>
#include <time.h>
#include <datagen.h>
#include <tpcw.h>
#include <common.h>


/* Clause 4.7.1 */

void gen_authors(int items)
{
	int i;
	FILE *output = stdout;
	char a_string[1024];
	struct tm tm1, *tm2, *tm3;
	time_t t1, t2, t3;

	output = fopen("author.data", "w");
	if (output == NULL)
	{
		fprintf(stderr, "cannot open author.data\n");
		return;
	}

	author_count = items / 4;

	for (i = 0; i < author_count; i++)
	{
		/* a_id */
		fprintf(output, "\"%d\"", i + 1);
		fprintf(output, "%c", DELIMITER);

		/* a_fname */
		get_a_string(a_string, 3, A_FNAME_LEN);
		fprintf(output, "\"%s\"", a_string);
		fprintf(output, "%c", DELIMITER);

		/* a_lname */
		fprintf(output, "\"%s\"", mk_author(i + 1));
		fprintf(output, "%c", DELIMITER);

		/* a_mname */
		get_a_string(a_string, 1, A_MNAME_LEN);
		fprintf(output, "\"%s\"", a_string);
		fprintf(output, "%c", DELIMITER);

		/* a_dob */
		/* The date is being calculated from 1900 instead of 1800. */
		tm1.tm_year = 0;
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
		fprintf(output, "\"%04d%02d%02d\"", tm3->tm_year + 1900, tm3->tm_mon + 1,
			tm3->tm_mday);
		fprintf(output, "%c", DELIMITER);

		/* a_bio */
		get_a_string(a_string, 125, A_BIO_LEN);
		fprintf(output, "\"%s\"", a_string);

		fprintf(output, "\n");
	}

	fflush(output);
	fclose(output);
}
