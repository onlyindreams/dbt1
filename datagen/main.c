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

#include <stdlib.h>
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


int main(int argc, char *argv[])
{
	int items, ebs;
	FILE *sequence_sql;
	FILE *p;
	char pwd[256];
	char cmd[256];

	if (argc != 3)
	{
		printf("Usage: %s <items> <ebs>\n", argv[0]);
		return 1;
	}

	items = atoi(argv[1]);
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

	ebs = atoi(argv[2]);

	printf("item scale factor	%d\n", items);
	printf("EB scale factor		%d\n", ebs);

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
	gen_items(items);
	gen_customers(ebs);
	gen_authors(items);
	gen_addresses(ebs);
	gen_orders(ebs, items);

	/*
	 * In my environment, I don't have enough /tmp space to put the data files
	 * in /tmp.
	 */
	p = popen("pwd", "r");
	fscanf(p, "%s", pwd);
	printf("%s\n", pwd);
	printf("creating links in /tmp to data files...\n");
	sprintf(cmd, "ln -fs %s/address.data /tmp/address.data", pwd);
	popen(cmd, "r");
	sprintf(cmd, "ln -fs %s/address.data /tmp/address.data", pwd);
	popen(cmd, "r");
	sprintf(cmd, "ln -fs %s/author.data /tmp/author.data", pwd);
	popen(cmd, "r");
	sprintf(cmd, "ln -fs %s/customer.data /tmp/customer.data", pwd);
	popen(cmd, "r");
	sprintf(cmd, "ln -fs %s/item.data /tmp/item.data", pwd);
	popen(cmd, "r");
	sprintf(cmd, "ln -fs %s/orders.data /tmp/orders.data", pwd);
	popen(cmd, "r");
	sprintf(cmd, "ln -fs %s/order_line.data /tmp/order_line.data", pwd);
	popen(cmd, "r");
	sprintf(cmd, "ln -fs %s/cc_xacts.data /tmp/cc_xacts.data", pwd);
	popen(cmd, "r");
	sprintf(cmd, "ln -fs %s/country.data /tmp/country.data", pwd);
	popen(cmd, "r");

	free(dpath);
	return 0;
}
