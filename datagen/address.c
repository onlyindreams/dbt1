/* address.c
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

#define _LARGEFILES64_SOURCE

#include <stdio.h>
#include <time.h>
#include <datagen.h>
#include <common.h>


/* Clause 4.7.1 */

void gen_addresses(int ebs)
{
	int i;
	FILE *output = stdout;
	char a_string[1024];
	int addresses;

	output = fopen64("address.data", "w");
	if (output == NULL)
	{
		fprintf(stderr, "cannot open address.data\n");
		return;
	}

	addresses = ebs * 2880 * 2;

	for (i = 0; i < addresses; i++)
	{
		/* addr_id */
		fprintf(output, "\"%d\"", i + 1);
		fprintf(output, "%c", DELIMITER);

		/* addr_street1 */
		get_a_string(a_string, 15, ADDR_STREET1_LEN);
		fprintf(output, "\"%s\"", a_string);
		fprintf(output, "%c", DELIMITER);

		/* addr_street2 */
		get_a_string(a_string, 15, ADDR_STREET1_LEN);
		fprintf(output, "\"%s\"", a_string);
		fprintf(output, "%c", DELIMITER);

		/* addr_city */
		get_a_string(a_string, 4, ADDR_CITY_LEN);
		fprintf(output, "\"%s\"", a_string);
		fprintf(output, "%c", DELIMITER);

		/* addr_state */
		get_a_string(a_string, 2, ADDR_STATE_LEN);
		fprintf(output, "\"%s\"", a_string);
		fprintf(output, "%c", DELIMITER);

		/* addr_zip */
		get_a_string(a_string, 5, ADDR_ZIP_LEN);
		fprintf(output, "\"%s\"", a_string);
		fprintf(output, "%c", DELIMITER);

		/* addr_co_id */
		fprintf(output, "\"%d\"", (int) get_random(CO_ID_MAX) + 1);

		fprintf(output, "\n");
	}

	fflush(output);
	fclose(output);
}
