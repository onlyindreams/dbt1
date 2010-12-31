/*
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2002 Open Source Development Lab, Inc.
 *
 * History:
 * Jan-30-2002  Created by Mark Wong & Jenny Zhang 
 * Aug-20-2003  Rewrote parsing command line part
 */

#include <semaphore.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <ctype.h>
#include <time.h>

#include <common.h>
#include <db.h>
#include <eu.h>

static int eus;
static int rampuprate;
static int duration;
static double think_time;
static int help;

struct db_conn_t db_conn;

int usage(char *);

/*
 * main() just takes arguments off the command line, starts up the rest of
 * the program and waits for the application to finish.
 */
int main(int argc, char *argv[])
{
	int running_eus;
	time_t stop_time;
	int c;

	/* setup default value in case the user forgets, but in most
	   cases the user should set it */

	strcpy(db_conn.dbhost, "localhost");
	strcpy(db_conn.dbport, "5432");
	strcpy(db_conn.dbname, "DBT1");
	strcpy(db_conn.dbuser, "dbt");
	strcpy(db_conn.dbpass, "dbt");

	strcpy(cache_host, "localhost");
	cache_port = 9999;
	strcpy(app_host, "localhost");
	app_port = 9992;
	item_count = 1000;
	customers = 28800;
	eus = 10;
	rampuprate = 10;
	think_time = 7.2;
	duration = 300;
	help = 0;
	altered = 0;
	mode_access = MODE_APPSERVER;
	mode_cache = MODE_CACHE_OFF;

	while (1)
	{
		static struct option long_options[] = {
			{ "app_host", required_argument, 0, 0 },
			{ "app_port", required_argument, 0, 0 },
			{ "access_direct", no_argument, &mode_access, MODE_DIRECT },
			{ "dbhost", required_argument, 0, 0 },
			{ "dbport", required_argument, 0, 0 },
			{ "dbname", required_argument, 0, 0 },
			{ "dbuser", required_argument, 0, 0 },
			{ "dbpass", required_argument, 0, 0 },
			{ "access_cache", no_argument, &mode_cache, MODE_CACHE_ON },
			{ "cache_host", required_argument, 0, 0 },
			{ "cache_port", required_argument, 0, 0 },
			{ "items", required_argument, 0, 0 },
			{ "customers", required_argument, 0, 0 },
			{ "eus", required_argument, 0, 0 },
			{ "rampup_rate", required_argument, 0, 0 },
			{ "think_time", required_argument, 0, 0 },
			{ "duration", required_argument, 0, 0 },
			{ "output_path", required_argument, 0, 0 },
			{ "debug", no_argument, 0, 0 },
			{ "help", no_argument, &help, 1 },
			{ "altered", no_argument, &altered, 1 },
			{ 0, 0, 0, 0 }
		};
		int option_index = 0;
                c = getopt_long_only(argc, argv, "", long_options, &option_index);
                if (c == -1)
                {
                         break;
                }
                switch (c)
                {
                case 0:
                        if (long_options[option_index].flag != 0)
                        {
                                break;
                        }
			if (strcmp(long_options[option_index].name, "dbhost") == 0)
                        {
                                strcpy(db_conn.dbhost, optarg);
                        }
			if (strcmp(long_options[option_index].name, "dbport") == 0)
                        {
                                strcpy(db_conn.dbport, optarg);
                        }
			if (strcmp(long_options[option_index].name, "dbname") == 0)
                        {
                                strcpy(db_conn.dbname, optarg);
                        }
			if (strcmp(long_options[option_index].name, "dbuser") == 0)
                        {
                                strcpy(db_conn.dbuser, optarg);
                        }
			if (strcmp(long_options[option_index].name, "dbpass") == 0)
                        {
                                strcpy(db_conn.dbpass, optarg);
                        }
			if (strcmp(long_options[option_index].name, "cache_host") == 0)
                        {
                                strcpy(cache_host, optarg);
                        }
			if (strcmp(long_options[option_index].name, "cache_port") == 0)
                        {
				cache_port = atoi(optarg);
                        }
			if (strcmp(long_options[option_index].name, "app_host") == 0)
                        {
                                strcpy(app_host, optarg);
                        }
			if (strcmp(long_options[option_index].name, "app_port") == 0)
                        {
				app_port = atoi(optarg);
                        }
			if (strcmp(long_options[option_index].name, "items") == 0)
                        {
				item_count = atoi(optarg);
                        }
			if (strcmp(long_options[option_index].name, "customers") == 0)
                        {
				customers = atoi(optarg);
                        }
			if (strcmp(long_options[option_index].name, "eus") == 0)
                        {
				eus = atoi(optarg);
                        }
			if (strcmp(long_options[option_index].name, "output_path") == 0)
                        {
				strcpy(output_path, optarg);
                        }
			if (strcmp(long_options[option_index].name, "rampup_rate") == 0)
                        {
				rampuprate = atoi(optarg);
                        }
			if (strcmp(long_options[option_index].name, "think_time") == 0)
                        {
				think_time = atof(optarg);
                        }
			if (strcmp(long_options[option_index].name, "duration") == 0)
                        {
				duration = atoi(optarg);
                        }
			if (strcmp(long_options[option_index].name, "debug") == 0)
                        {
				LogDebug = 1;
                        }
			break;
		default:
			printf ("?? getopt returned character code 0%o ??\n", c);
			exit(1);
		}
	}

	if ( help == 1)
	{
		return usage(argv[0]);
	}

	/* Initialize global variables. */
	init_common();

	/*
	 * Calculate the stop time before the users are started and factor in
	 * the rampup time.
	 */
	stop_time = time(NULL) + duration + (int) ((eus / rampuprate) * 60);

	/* Start the user threads. */
	if ( init_eus(eus, MIX_SHOPPING, rampuprate, duration, think_time, item_count ) != OK) 
		return 1;

	/*
	 * Sit in an infinite loop until the run duration expires.  This is a good
	 * place to implement some real-time statistics reporting, if someone is so
	 * inclined.
	 */
	mark_logs(RUN_START);
	do
	{
/*
		for (i = 0; i < INTERACTION_TOTAL; i++)
		{
			printf("%s ", interaction_short_name[i]);
		}
		printf("\n");
		for (i = 0; i < INTERACTION_TOTAL; i++)
		{
			sem_getvalue(&running_interactions[i], &sem_val);
			printf("%2d ", sem_val);
		}
		printf("\n");
*/

		sem_getvalue(&running_eu_count, &running_eus);
		sleep(1);
	}
	while (time(NULL) <= stop_time);
/*
	mark_logs(RUN_END);
*/
	/*
	 * Do not change this output. The run script may watch this.
	 * See `run_dbt1.sh' for more details.
	 */
	printf ("Dbdriver ended\n");
	fflush(stdout);

	return 0;
}

int usage(char *name)
{
	printf("\nUsage: %s [option]...\n", name);
	printf("\n");

	printf("Options for accessing through the middle tier (appServ):\n");
	printf("    --app_host <host>     Hostname for appServ connection. (default:%s)\n", app_host);
	printf("    --app_port <port>     Port number for appServ connection. (default:%d)\n", app_port);
	printf("\n");

	printf("Options for accessing database directly:\n");
	printf("    --access_direct       Enable to connect database server directly. (default:disabled)\n");

	printf("    --dbhost <hostname>   Hostname for database connection. (default:%s)\n", db_conn.dbhost);
	printf("                          Use a datasource name when using ODBC interfaces.\n");
	printf("    --dbport <port>       Port number for database connection. (default:%s)\n", db_conn.dbport);
	printf("    --dbname <dbname>     Database name for database connection. (default:%s)\n", db_conn.dbname);
	printf("    --dbuser <username>   Username for database connection. (default:%s)\n", db_conn.dbuser);
	printf("    --dbpass <password>   Password for database connection. (default:%s)\n", db_conn.dbpass);
	printf("\n");

	printf("Options for using the search result cache (appCache):\n");
	printf("    --access_cache        Enable the search results cache. (default:disabled)\n");
	printf("    --cache_host <host>   Hostname for cache connection. (default:%s)\n", cache_host);
	printf("    --cache_port <port>   Port number for cache connection. (default:%d)\n", cache_port);
	printf("\n");

	printf("Common options:\n");
	printf("    --items <num>         Number of item table records. (default:%d)\n", item_count);
	printf("    --customers <num>     Number of customer table records. (default:%d)\n", customers);
	printf("    --eus <num>           Number of emulated users. (default:%d)\n", eus);
	printf("    --rampup_rate <num>   Rampup rate in \"EUs/minute\". (default:%d)\n", rampuprate);
	printf("    --think_time <sec>    A mean think time in seconds. (default:%.1f)\n", think_time);
	printf("    --duration <sec>      Run duration time in seconds. (default:%d)\n", duration);
	printf("    --output_path <path>  Log output directory.\n");
	printf("    --altered\n");
	printf("    --debug\n");
	printf("    --help\n");
	printf("\n");

	return 1;
}
