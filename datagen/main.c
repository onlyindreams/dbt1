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

#define _LARGEFILE64_SOURCE

#include <stdlib.h>
#include <unistd.h>
#include <tpcw.h>
#include <datagen.h>


#define SEQUENCE_SQL "../scripts/sapdb/create_sequence.sql"

int item_count, author_count;
int set_seeds;

char *dpath;
int  verbose;

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

int main(int argc, char *argv[])
{
	FILE *sequence_sql;
	FILE *p;
	char pwd[256];
	char cmd[256];

	flag_cust=0;
	flag_item=0;
	flag_author=0;
	flag_address=0;
	flag_order=0;
	path[0]='\0';

	process_options(argc, argv);

	if (items != 1000 && items != 10000 && items != 100000 && items != 1000000
		&& items != 10000000)
	{
		printf("%d is an invalid item scale factor:\n", items);
		printf("\t1000\n", items);
		printf("\t10000\n", items);
		printf("\t100000\n", items);
		printf("\t1000000\n", items);
		printf("\t10000000\n", items);
		return 2;
	}

	p = popen("pwd", "r");
	fscanf(p, "%s", pwd);
	printf("%s\n", pwd);
	if (strcmp(path, ".")==0 || path[0]=='\0' ) strcpy(path, pwd);

	printf("item scale factor	%d\n", items);
	printf("EB scale factor		%d\n", ebs);
	printf("data file is in	%s\n", path);

	printf("generating sequence creation file: %s\n", SEQUENCE_SQL);
	sequence_sql = fopen64(SEQUENCE_SQL, "w");
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
	/*if -T is not specified, then generate all the files */
	if (flag_item==0 && flag_cust==0 && flag_author==0 && flag_address==0 &&
		flag_order==0)
	{
		gen_items(items, path);
		gen_customers(ebs, path);
		gen_authors(items, path);
		gen_addresses(ebs, path);
		gen_orders(ebs, items, path);
		/*
		 * In my environment, I don't have enough /tmp space to put the data files
		 * in /tmp.
		 */

		printf("creating links in /tmp to data files...\n");
		sprintf(cmd, "ln -fs %s/address.data /tmp/address.data", path);
		popen(cmd, "r");
		sprintf(cmd, "ln -fs %s/author.data /tmp/author.data", path);
		popen(cmd, "r");
		sprintf(cmd, "ln -fs %s/customer.data /tmp/customer.data", path);
		popen(cmd, "r");
		sprintf(cmd, "ln -fs %s/item.data /tmp/item.data", path);
		popen(cmd, "r");
		sprintf(cmd, "ln -fs %s/orders.data /tmp/orders.data", path);
		popen(cmd, "r");
		sprintf(cmd, "ln -fs %s/order_line.data /tmp/order_line.data", path);
		popen(cmd, "r");
		sprintf(cmd, "ln -fs %s/cc_xacts.data /tmp/cc_xacts.data", path);
		popen(cmd, "r");
	}
	else
	{
		if (flag_item == 1) 
		{
			gen_items(items, path);
			sprintf(cmd, "ln -fs %s/item.data /tmp/item.data", path);
			popen(cmd, "r");
		}
		if (flag_cust == 1)
		{
			gen_customers(ebs, path);
			sprintf(cmd, "ln -fs %s/customer.data /tmp/customer.data", path);
			popen(cmd, "r");
		}
		if (flag_author == 1) 
		{
			gen_authors(items, path);
			sprintf(cmd, "ln -fs %s/author.data /tmp/author.data", path);
			popen(cmd, "r");
		}
		if (flag_address == 1)
		{
			gen_addresses(ebs, path);
			sprintf(cmd, "ln -fs %s/address.data /tmp/address.data", path);
			popen(cmd, "r");
		}
		if (flag_order == 1)
		{
			gen_orders(ebs, items, path);
			sprintf(cmd, "ln -fs %s/orders.data /tmp/orders.data", path);
			popen(cmd, "r");
			sprintf(cmd, "ln -fs %s/order_line.data /tmp/order_line.data", path);
			popen(cmd, "r");
			sprintf(cmd, "ln -fs %s/cc_xacts.data /tmp/cc_xacts.data", path);
			popen(cmd, "r");
		}
	}

	sprintf(cmd, "ln -fs %s/country.data /tmp/country.data", pwd);
	popen(cmd, "r");

	free(dpath);
	return 0;
}

void process_options(int count, char **vector)
{
	int option;
	int set_items;
	int set_eus;

	set_items=0;
	set_eus=0;

	while ((option = getopt (count, vector, "i:u:p:T:h")) != -1)
	{
		switch (option)
		{
			case 'i':
				items = atoi(optarg);
				set_items=1;
				break;
			case 'u':
				ebs = atoi(optarg);
				set_eus=1;
				break;
			case 'p':
				strcpy(path, optarg);
				break;
			case 'T':
				switch (*optarg)
				{
					case 'i':
						flag_item = 1 ; /*generate item ONLY */
						break;
					case 'c':
						flag_cust = 1 ; /*generate customer ONLY */
						break;
					case 'o':
						flag_order = 1; /*generate order ONLY */
						break;
					case 'a':
						flag_author = 1; /*generate author ONLY */
						break;
					case 'd':
						flag_address = 1; /*generate address ONLY */
						break;
				}
				break;
			case 'h':
				usage();
				exit(1);
				break;
			default:
				usage();
				exit(1);
		}
	}
	if (set_items==0 || set_eus==0)
	{
		printf("item and eu numbers are required\n");
		usage();
		exit(1);
	}
}

void usage()
{
	printf("usage: ./datagen -i <item> -u <eu> -p <path> -T <table_name>\n");
	printf("table name is:\n");
	printf(" i -- item\n c -- customer\n a -- author\n d -- address\n o -- order\n");
	printf("example: ./datagen -i 10000 -u 1000 -p /tmp -T i -T c\n");
	printf("generates table ITEM and CUSTOMER for 10k item 1k eu in directory /tmp\n");
}
