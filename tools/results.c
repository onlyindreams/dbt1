/*
 * results.c
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2002 Mark Wong & Jenny Zhang &
 *                    Open Source Development Lab, Inc.
 *
 * 9 april 2002
 */

#include <stdio.h>
#include <time.h>
#include <common.h>

/* Previously defined in eb.c, maybe it should go in common.c? */
const char *interaction_short_name[INTERACTION_TOTAL] =
{
    "AC", "AR", "BS", "BC", "BR", "CR", "HO", "NP", "OD", "OI", "PD", "SR",
    "SU", "SC"
};

/* Stuff to do I/O analysis, bah! */
struct io_dev_node_t
{
	char name[32];
	int count;
	float rrqms, wrqms, rs, ws, rsecs, wsecs, avgrqsz, avgqusz, await, svctm,
		util;
	struct io_dev_node_t *next;
};
struct io_dev_node_t *io_dev_head;
struct io_dev_node_t *io_dev_cur;

int main(int argc, char *argv[])
{
	int i;
	FILE *log_mix;
	FILE *plot_ips;
	time_t current_time;
	char interaction[3];
	float response_time;
	int tid;
	time_t start_time = -1;
	float total_response_time;
	float ips;
	long long total_interaction_count = 0;
	long long interaction_count[INTERACTION_TOTAL];
	float interaction_response_time[INTERACTION_TOTAL];

	FILE *log_cpu;
	FILE *log_io;
	FILE *log_paging;
	int count;
	float user, nice, sys, idle;
	float total_user = 0, total_nice = 0, total_sys = 0, total_idle = 0;
	float pgpgin, pgpgout, activepg, inadtypg, inaclnpg, inatarpg;
	float total_pgpgin = 0, total_pgpgout = 0, total_activepg = 0,
		total_inadtypg = 0, total_inaclnpg = 0, total_inatarpg = 0;
	char iostat_line[128];

	time_t previous_time;
	int elapsed_time = 0;
	int current_interation_count = 0;

	if (argc != 2)
	{
		printf("usage: %s <filename>\n", argv[0]);
		return 1;
	}

	log_mix = fopen(argv[1], "r");
	if (log_mix == NULL)
	{
		printf("cannot open %s for reading\n", argv[1]);
		return 2;
	}

	plot_ips = fopen("ips.csv", "w");
	if (plot_ips == NULL)
	{
		printf("cannot open mix.csv for writing\n");
		return 3;
	}

	/*
	 * Initialize the counters for the number of each interaction to 0
	 * as well as the total response time.
	 */
	for (i = 0; i < INTERACTION_TOTAL; i++)
	{
		interaction_count[i] = 0;
		interaction_response_time[i] = 0;
	}

	/*
	 * Set the last character to null, in case we ever want to print out
	 * the data captured in interaction[].
	 */
	interaction[2] = '\0';

	/* Read the first line individually to capture the start time. */
	fscanf(log_mix, "%d,%c%c,%f,%d", &start_time, &interaction[0],
		&interaction[1], &total_response_time, &tid);

	/*
	 * The first line is always the Home interaction, so update the
	 * appropriate counters.
	 */
	++interaction_count[HOME];
	interaction_response_time[HOME] += response_time;
	++total_interaction_count;

	previous_time = start_time;

	/* Keep reading the file until we hit the end. */
	while (fscanf(log_mix, "%d,%c%c,%f,%d", &current_time, &interaction[0],
		&interaction[1], &response_time, &tid) != EOF)
	{
		/*
		 * Note that we're factoring in Customer Registration even though
		 * it isn't a database interaction.
		 */
		total_response_time += response_time;
		++total_interaction_count;
		if (strcmp(interaction, interaction_short_name[ADMIN_CONFIRM]) == 0)
		{
			++interaction_count[ADMIN_CONFIRM];
			interaction_response_time[ADMIN_CONFIRM] += response_time;
		}
		else if (strcmp(interaction,
			interaction_short_name[ADMIN_REQUEST]) == 0)
		{
			++interaction_count[ADMIN_REQUEST];
			interaction_response_time[ADMIN_REQUEST] += response_time;
		}
		else if (strcmp(interaction,
			interaction_short_name[BEST_SELLERS]) == 0)
		{
			++interaction_count[BEST_SELLERS];
			interaction_response_time[BEST_SELLERS] += response_time;
		}
		else if (strcmp(interaction,
			interaction_short_name[BUY_CONFIRM]) == 0)
		{
			++interaction_count[BUY_CONFIRM];
			interaction_response_time[BUY_CONFIRM] += response_time;
		}
		else if (strcmp(interaction, interaction_short_name[BUY_REQUEST]) == 0)
		{
			++interaction_count[BUY_REQUEST];
			interaction_response_time[BUY_REQUEST] += response_time;
		}
		else if (strcmp(interaction,
			interaction_short_name[CUSTOMER_REGISTRATION]) == 0)
		{
			++interaction_count[CUSTOMER_REGISTRATION];
			interaction_response_time[CUSTOMER_REGISTRATION] += response_time;
		}
		else if (strcmp(interaction, interaction_short_name[HOME]) == 0)
		{
			++interaction_count[HOME];
			interaction_response_time[HOME] += response_time;
		}
		else if (strcmp(interaction, interaction_short_name[NEW_PRODUCTS]) == 0)
		{
			++interaction_count[NEW_PRODUCTS];
			interaction_response_time[NEW_PRODUCTS] += response_time;
		}
		else if (strcmp(interaction,
			interaction_short_name[ORDER_DISPLAY]) == 0)
		{
			++interaction_count[ORDER_DISPLAY];
			interaction_response_time[ORDER_DISPLAY] += response_time;
		}
		else if (strcmp(interaction,
			interaction_short_name[ORDER_INQUIRY]) == 0)
		{
			++interaction_count[ORDER_INQUIRY];
			interaction_response_time[ORDER_INQUIRY] += response_time;
		}
		else if (strcmp(interaction,
			interaction_short_name[PRODUCT_DETAIL]) == 0)
		{
			++interaction_count[PRODUCT_DETAIL];
			interaction_response_time[PRODUCT_DETAIL] += response_time;
		}
		else if (strcmp(interaction,
			interaction_short_name[SEARCH_REQUEST]) == 0)
		{
			++interaction_count[SEARCH_REQUEST];
			interaction_response_time[SEARCH_REQUEST] += response_time;
		}
		else if (strcmp(interaction,
			interaction_short_name[SEARCH_RESULTS]) == 0)
		{
			++interaction_count[SEARCH_RESULTS];
			interaction_response_time[SEARCH_RESULTS] += response_time;
		}
		else if (strcmp(interaction,
			interaction_short_name[SHOPPING_CART]) == 0)
		{
			++interaction_count[SHOPPING_CART];
			interaction_response_time[SHOPPING_CART] += response_time;
		}

		/* Output data to graph for interactions per second. */
		if (current_time <= previous_time + 30)
		{
			++current_interation_count;
		}
		else
		{
			fprintf(plot_ips, "%d,%f\n", elapsed_time,
				(double) current_interation_count / 30.0);
			++elapsed_time;

			previous_time = current_time;
			current_interation_count = 1;
		}
	}
	fclose(log_mix);
	fclose(plot_ips);

	/* Calculate the actualy mix of interactions. */
	printf("interaction\t%\tavg response time (s)\n");
	for (i = 0; i < INTERACTION_TOTAL; i++)
	{
		printf("%s\t\t%2.2f\t%0.3f\n", interaction_short_name[i],
			(double) interaction_count[i] / (double) total_interaction_count * 100.0,
			interaction_response_time[i] / (double) total_interaction_count);
	}
	
	/* Calculated the number of interactions per second. */
	ips = (double) total_interaction_count / difftime(current_time, start_time);
	printf("\n%0.1f interactions per second\n", ips);

	printf("%0.1f minute duration\n",
		difftime(current_time, start_time) / 60.0);
	printf("\n");

	/* Open the files in ../scripts/stats to crunch numbers. */
	log_cpu = fopen("../scripts/stats/cpu.csv", "r");
	if (log_cpu == NULL)
	{
		printf("cannot open ../scripts/stats/cpu.csv for reading\n");
		return 4;
	}

	/* Skip the first 2 lines, system info and 1 line of data. */
	fscanf(log_cpu, "%*s");
	fscanf(log_cpu, "%*s");
	count = 0;
	while (fscanf(log_cpu, "%f,%f,%f,%f", &user, &nice, &sys, &idle) != EOF)
	{
		total_user += user;
		total_nice += nice;
		total_sys += sys;
		total_idle += idle;
		++count;
	}
	fclose(log_cpu);
	printf("CPU:\n");
	printf("Average %%user %0.2f\n", total_user / (double) count);
	printf("Average %%nice %0.2f\n", total_nice / (double) count);
	printf("Average %%sys %0.2f\n", total_sys / (double) count);
	printf("Average %%idle %0.2f\n", total_idle / (double) count);
	printf("\n");

	log_io = fopen("../scripts/stats/io.csv", "r");
	if (log_io == NULL)
	{
		printf("cannot open ../scripts/stats/io.csv for reading\n");
		return 5;
	}

	/* Skip the first 2 lines, system info and 1 line of data. */
	fscanf(log_io, "%*s");
	fscanf(log_io, "%*s");
	io_dev_head = NULL;
	while (fscanf(log_io, "%s", iostat_line) != EOF)
	{
		char dev_name[32];
		int dev_name_len;
		struct io_dev_node_t *tmp;
		float rrqms, wrqms, rs, ws, rsecs, wsecs, avgrqsz, avgqusz, await,
			svctm, util;

		/* I know there's a better way to do this, but I can't think... */
		dev_name_len =
			strlen(iostat_line) - strlen((char *) strstr(iostat_line, ","));
		strncpy(dev_name, iostat_line, dev_name_len);
		dev_name[dev_name_len] = '\0';

		tmp = io_dev_head;
		if (tmp == NULL)
		{
			/* List is empty, insert this at the head. */
			tmp =
				(struct io_dev_node_t *) malloc(sizeof(struct io_dev_node_t));
			strcpy(tmp->name, dev_name);
			tmp->count = 0;
			tmp->next = NULL;
			tmp->rrqms = tmp->wrqms = tmp->rs = tmp->ws = tmp->rsecs =
				tmp->wsecs = tmp->avgrqsz = tmp->avgqusz = tmp->await =
				tmp->svctm = tmp->util = 0.0;
			io_dev_head = tmp;
		}
		else
		{
			/* Locate the device in the list by name. */
			while (tmp != NULL && strcmp(dev_name, tmp->name) != 0)
			{
				tmp = tmp->next;
			}
		}
		if (tmp == NULL)
		{
			struct io_dev_node_t *tmp2;

			/* Dev is not in the list, so stick it on the top. */
			tmp = io_dev_head;
			while (tmp->next != NULL)
			{
				tmp = tmp->next;
			}

			tmp2 = tmp;
			tmp =
			(struct io_dev_node_t *) malloc(sizeof(struct io_dev_node_t));
			strcpy(tmp->name, dev_name);
			tmp->count = 0;
			tmp->next = NULL;
			tmp->rrqms = tmp->wrqms = tmp->rs = tmp->ws = tmp->rsecs =
				tmp->wsecs = tmp->avgrqsz = tmp->avgqusz = tmp->await =
				tmp->svctm = tmp->util = 0.0;
			tmp2->next = tmp;
		}

		/* Read the input. */
		sscanf((char *) strstr(iostat_line, ","),
			",%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
			&rrqms, &wrqms, &rs, &ws, &rsecs, &wsecs, &avgrqsz, &avgqusz,
			&await, &svctm, &util);
		tmp->rrqms += rrqms;
		tmp->wrqms += wrqms;
		tmp->rs += rs;
		tmp->ws += ws;
		tmp->rsecs += rsecs;
		tmp->wsecs += wsecs;
		tmp->avgrqsz += avgrqsz;
		tmp->avgqusz += avgqusz;
		tmp->await += await;
		tmp->svctm += svctm;
		tmp->util += util;
		++tmp->count;

	}
	fclose(log_io);
	io_dev_cur = io_dev_head;
	printf("I/O:\n");
	printf("The following numbers are presented as averages for each column.\n");
	printf("Note that stats are reported for every device attached to the system.\n");
	printf("device\trrqm/s\twrqm/s\tr/s\tw/s\trsec/s\twsec/s\tavgrq-sz\tavgqu-sz\tawait\tsvctm\t%%util\n");
	while (io_dev_cur != NULL)
	{
		printf("%s\t%0.2f\t%0.2f\t%0.2f\t%0.2f\t%0.2f\t%0.2f\t%0.2f\t\t%0.2f\t\t%0.2f\t%0.2f\t%0.2f\n",
			io_dev_cur->name,
			io_dev_cur->rrqms / io_dev_cur->count,
			io_dev_cur->wrqms / io_dev_cur->count,
			io_dev_cur->rs / io_dev_cur->count,
			io_dev_cur->ws / io_dev_cur->count,
			io_dev_cur->rsecs / io_dev_cur->count,
			io_dev_cur->wsecs / io_dev_cur->count,
			io_dev_cur->avgrqsz / io_dev_cur->count,
			io_dev_cur->avgqusz / io_dev_cur->count,
			io_dev_cur->await / io_dev_cur->count,
			io_dev_cur->svctm / io_dev_cur->count,
			io_dev_cur->util / io_dev_cur->count);
		io_dev_cur = io_dev_cur->next;
	}
	printf("\n");

	log_paging = fopen("../scripts/stats/paging.csv", "r");
	if (log_paging == NULL)
	{
		printf("cannot open ../scripts/stats/paging.csv for reading\n");
		return 6;
	}

	/* Skip the first 2 lines, system info and 1 line of data. */
	fscanf(log_paging, "%*s");
	fscanf(log_paging, "%*s");
	count = 0;
	while (fscanf(log_paging, "%f,%f,%f,%f,%f,%f", &pgpgin, &pgpgout,
		&activepg, &inadtypg, &inaclnpg, &inatarpg) != EOF)
	{
		total_pgpgin += pgpgin;
		total_pgpgout += pgpgout;
		total_activepg += activepg;
		total_inadtypg += inadtypg;
		total_inaclnpg += inaclnpg;
		total_inatarpg += inatarpg;
		++count;
	}
	fclose(log_paging);
	printf("Paging:\n");
	printf("Average pgpgin/s %0.2f\n", total_pgpgin / (double) count);
	printf("Average pgpgout/s %0.2f\n", total_pgpgout / (double) count);
	printf("Average activepg %0.2f\n", total_activepg / (double) count);
	printf("Average inadtypg %0.2f\n", total_inadtypg / (double) count);
	printf("Average inaclnpg %0.2f\n", total_inaclnpg / (double) count);
	printf("Average inatarpg %0.2f\n", total_inatarpg / (double) count);
	printf("\n");

	return 0;
}
