/* main.c
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2002 Mark Wong & Jenny Zhang &
 *                    Open Source Development Lab, Inc.
 *
 * 10 january 2001
 */

#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <tpcw.h>
#include <common.h>

#define DELIMITER ','
#define SEQUENCE_SQL "../scripts/sapdb/create_sequence.sql"

int item_count, author_count;
int set_seeds;

/* Variables for wgen. */
char *dpath;
int verbose;

distribution articles;
distribution nouns;
distribution adjectives;
distribution adverbs;
distribution prepositions;
distribution verbs;
distribution terminators;
distribution auxillaries;
distribution np;
distribution vp;
distribution grammar;

int items, ebs;
/* directory where the datafile will be put */
char path[256];
int flag_cust, flag_item, flag_author, flag_address, flag_order;
int multi = 0; /* multi = 1, allow parallel data generation */

/* Prototypes */
void *gen_addresses(void *data);
void *gen_authors(void *data);
void *gen_customers(void *data);
void *gen_items(void *data);
void *gen_orders(void *data);
int process_options(int count, char **vector);
void usage();
/* Prototype for wgen/text.c since it doesn't provide one for us. */
void load_dists(void);

int main(int argc, char *argv[])
{
	FILE *sequence_sql;
	FILE *p;
	char pwd[256];
	char cmd[256];
	pthread_t t1, t2, t3, t4, t5;

	path[0] = '\0';

	if (process_options(argc, argv) == 0)
	{
		usage();
		return 1;
	}

	if (items != 1000 && items != 10000 && items != 100000 &&
		items != 1000000 && items != 10000000)
	{
		printf("%d is an invalid item scale factor:\n", items);
		printf("\t1000\n");
		printf("\t10000\n");
		printf("\t100000\n");
		printf("\t1000000\n");
		printf("\t10000000\n");
		return 2;
	}

	p = popen("pwd", "r");
	fscanf(p, "%s", pwd);
	printf("%s\n", pwd);
	if (strcmp(path, ".") == 0 || path[0] == '\0' )
	{
		strcpy(path, pwd);
	}

	printf("item scale factor %10d\n", items);
	printf("user scale factor %10d\n", ebs);
	printf("data files are in %10s\n", path);

	printf("generating sequence creation file: %s\n", SEQUENCE_SQL);
	sequence_sql = fopen(SEQUENCE_SQL, "w");
	if (sequence_sql == NULL)
	{
		printf("cannot open %s\n", SEQUENCE_SQL);
		return 3;
	}
	fprintf(sequence_sql, "sql_connect dbt,dbt\n");
	fprintf(sequence_sql,
		"sql_execute CREATE SEQUENCE custid INCREMENT BY 1 START WITH %d\n",
		2880 * ebs + 1);
	fprintf(sequence_sql,
		"sql_execute CREATE SEQUENCE addrid INCREMENT BY 1 START WITH %d\n",
		ebs * 2880 * 2 + 1);
	fprintf(sequence_sql,
		"sql_execute CREATE SEQUENCE scid INCREMENT BY 1 START WITH %d\n",
		(int) ((double) ebs * 2880.0 * 0.9 + 1.0));
	fclose(sequence_sql);

	dpath = (char *) malloc(sizeof(char) * 64);
	strcpy(dpath, "../wgen/grammar.tpcw");

	init_common();
	load_dists();
	printf("generating data files...\n");

	if (flag_item == 1) 
	{
		if (pthread_create(&t1, NULL, gen_items, NULL) != 0)
		{
			perror("pthread_create");
		}
		sprintf(cmd, "ln -fs %s/item.data /tmp/item.data", path);
		popen(cmd, "r");
		if (multi == 0)
		{
			pthread_join(t1, NULL);
		}
	}

	if (flag_cust == 1)
	{
		if (pthread_create(&t2, NULL, gen_customers, NULL) != 0)
		{
			perror("pthread_create");
		}
		sprintf(cmd, "ln -fs %s/customer.data /tmp/customer.data", path);
		popen(cmd, "r");
		if (multi == 0)
		{
			pthread_join(t2, NULL);
		}
	}

	if (flag_author == 1) 
	{
		if (pthread_create(&t3, NULL, gen_authors, NULL) != 0)
		{
			perror("pthread_create");
		}
		sprintf(cmd, "ln -fs %s/author.data /tmp/author.data", path);
		popen(cmd, "r");
		if (multi == 0)
		{
			pthread_join(t3, NULL);
		}
	}

	if (flag_address == 1)
	{
		if (pthread_create(&t4, NULL, gen_addresses, NULL) != 0)
		{
			perror("pthread_create");
		}
		sprintf(cmd, "ln -fs %s/address.data /tmp/address.data", path);
		popen(cmd, "r");
		if (multi == 0)
		{
			pthread_join(t4, NULL);
		}
	}

	if (flag_order == 1)
	{
		if (pthread_create(&t5, NULL, gen_orders, NULL) != 0)
		{
			perror("pthread_create");
		}
		sprintf(cmd, "ln -fs %s/orders.data /tmp/orders.data", path);
		popen(cmd, "r");
		sprintf(cmd, "ln -fs %s/order_line.data /tmp/order_line.data",
			path);
		popen(cmd, "r");
		sprintf(cmd, "ln -fs %s/cc_xacts.data /tmp/cc_xacts.data", path);
		popen(cmd, "r");
		if (multi == 0)
		{
			pthread_join(t5, NULL);
		}
	}

	if (multi == 1)
	{
		pthread_join(t1, NULL);
		pthread_join(t2, NULL);
		pthread_join(t3, NULL);
		pthread_join(t4, NULL);
		pthread_join(t5, NULL);
	}

	sprintf(cmd, "ln -fs %s/country.data /tmp/country.data", pwd);
	popen(cmd, "r");

	free(dpath);
	return 0;
}

/* Clause 4.7.1 */
void *gen_addresses(void *data)
{
	int i;
	FILE *output = stdout;
	char a_string[1024];
	int addresses;
	char filename[256];

	sprintf(filename, "%s/address.data", path);
	output = fopen(filename, "w");
	if (output == NULL)
	{
		fprintf(stderr, "cannot open address.data\n");
		return NULL;
	}

	srand(0);
	printf("Generating address table data...\n");

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
	printf("Finished address table data.\n");
	return NULL;
}

/* Clause 4.7.1 */
void *gen_authors(void *data)
{
	int i;
	FILE *output = stdout;
	char a_string[1024];
	struct tm tm1, *tm2, *tm3;
	time_t t1, t2, t3;
	char filename[256];

	sprintf(filename, "%s/author.data", path);
	output = fopen(filename, "w");
	if (output == NULL)
	{
		fprintf(stderr, "cannot open author.data\n");
		return NULL;
	}

	srand(0);
	printf("Generating author table data...\n");

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
		fprintf(output, "\"%04d%02d%02d\"", tm3->tm_year + 1900,
			tm3->tm_mon + 1, tm3->tm_mday);
		fprintf(output, "%c", DELIMITER);

		/* a_bio */
		get_a_string(a_string, 125, A_BIO_LEN);
		fprintf(output, "\"%s\"", a_string);

		fprintf(output, "\n");
	}

	fflush(output);
	fclose(output);
	printf("Finished author table data.\n");
	return NULL;
}

/* Clause 4.7.1 */
void *gen_customers(void *data)
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
	output = fopen(filename, "w");
	if (output == NULL)
	{
		fprintf(stderr, "cannot open customer.data\n");
		return NULL;
	}

	srand(0);
	printf("Generating customer table data...\n");

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
	printf("Finished customer table data.\n");
	return NULL;
}

/* Clause 4.7.1 */
void *gen_items(void *data)
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
	output = fopen(filename, "w");
	if (output == NULL)
	{
		fprintf(stderr, "cannot open item.txt");
		return NULL;
	}

	srand(0);
	printf("Generating item table data...\n");

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
	printf("Finished item table data.\n");
	return NULL;
}

/* Clause 4.7.1 */
void *gen_orders(void *data)
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
	orders_file = fopen(filename1, "w");
	if (orders_file == NULL)
	{
		fprintf(stderr, "cannot open orders.data\n");
		return NULL;
	}

	sprintf(filename2, "%s/order_line.data", path);
	order_line_file = fopen(filename2, "w");
	if (order_line_file == NULL)
	{
		fprintf(stderr, "cannot open order_line.data\n");
		return NULL;
	}

	sprintf(filename3, "%s/cc_xacts.data", path);
	cc_xacts_file = fopen(filename3, "w");
	if (cc_xacts_file == NULL)
	{
		fprintf(stderr, "cannot open cc_xacts.data\n");
		return NULL;
	}

	srand(0);
	printf("Generating order, order_line, and cc_xacts table data...\n");

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
	printf("Finished order, order_line, and cc_xacts table data.\n");
	return NULL;
}

int process_options(int count, char **vector)
{
	int option;
	int set_items;
	int set_eus;
	int flag_all = 1;

	set_items = 0;
	set_eus = 0;

	flag_cust = 0;
	flag_item = 0;
	flag_author = 0;
	flag_address = 0;
	flag_order = 0;
	while ((option = getopt (count, vector, "i:u:p:T:h:m")) != -1)
	{
		switch (option)
		{
			case 'i':
				items = atoi(optarg);
				set_items = 1;
				break;
			case 'u':
				ebs = atoi(optarg);
				set_eus = 1;
				break;
			case 'p':
				strcpy(path, optarg);
				break;
			case 'T':
				flag_all = 0;
				switch (*optarg)
				{
					case 'i':
						flag_item = 1 ; /* generate item ONLY */
						break;
					case 'c':
						flag_cust = 1 ; /* generate customer ONLY */
						break;
					case 'o':
						flag_order = 1; /* generate order ONLY */
						break;
					case 'a':
						flag_author = 1; /* generate author ONLY */
						break;
					case 'd':
						flag_address = 1; /* generate address ONLY */
						break;
					default:
						return 0;
				}
				break;
			case 'h':
				return 0;
			case 'm':
				multi = 1;
				break;
			default:
				return 0;
		}
	}
	if (flag_all == 1)
	{
		flag_cust = 1;
		flag_item = 1;
		flag_author = 1;
		flag_address = 1;
		flag_order = 1;
	}
	if (set_items == 0 || set_eus == 0)
	{
		printf("item and eu numbers are required\n");
		return 0;
	}
	return 1;
}

void usage()
{
	printf("usage: ./datagen -i <item> -u <eu> -p <path> -T <table_name>\n");
	printf("table name is:\n");
	printf(" i -- item\n");
	printf(" c -- customer\n");
	printf(" a -- author\n");
	printf(" d -- address\n");
	printf(" o -- order\n");
	printf("example: ./datagen -i 10000 -u 1000 -p /tmp -T i -T c\n");
	printf("generates table ITEM and CUSTOMER for 10k item 1k eu in directory /tmp\n");
}
