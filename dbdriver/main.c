/*
 * main.c
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2002 Mark Wong & Jenny Zhang &
 *                    Open Source Development Lab, Inc.
 *
 * 30 January 2002
 */

#include <semaphore.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>

#include <common.h>
#include <eu.h>

/*
 * main() just takes arguments off the command line, starts up the rest of
 * the program and waits for the application to finish.
 */
int main(int argc, char *argv[])
{
	int eus, rampuprate, duration;
	double think_time;
	int running_eus;
	char sname[32];
	time_t stop_time;
#ifdef PHASE1
	char uname[32], auth[32];
#ifdef SEARCH_RESULTS_CACHE
	char cache_host[32];
	int cache_port;
#endif /* SEARCH_RESULTS_CACHE */
#endif /* PHASE1 */
#ifdef PHASE2
	int port;
	int c;
#endif /* PHASE2 */
/*
	int i;
	int sem_val;
*/


#ifdef PHASE1
#ifdef SEARCH_RESULTS_CACHE
	if (argc != 12)
	{
		printf("usage: %s <servername> <user> <pass> <items> <customers> <eus> <eus/min> <think time> <duration> <cache_host> <cache_port>\n",
			argv[0]);
		return -1;
	}
#else
	if (argc != 10)
	{
		printf("usage: %s <servername> <user> <pass> <items> <customers> <eus> <eus/min> <think time> <duration>\n",
			argv[0]);
		return -1;
	}
#endif
#endif /* PHASE1 */

#ifdef PHASE2
	if (argc < 17)
	{
		printf("usage: %s -d <servername> -p <port> -i <items> -c <customers> -u <eus> -r <eus/min> -t <think time> -l <duration>\n",
			argv[0]);
		return -1;
	}
#endif /* PHASE2 */


#ifdef PHASE1
	strcpy(uname, argv[2]);
	strcpy(auth, argv[3]);
	item_count = atoi(argv[4]);
	customers = atoi(argv[5]);
	eus = atoi(argv[6]);
	rampuprate = atoi(argv[7]);
	think_time = atof(argv[8]);
	duration = atoi(argv[9]);
#ifdef SEARCH_RESULTS_CACHE
	strcpy(cache_host, argv[10]);
	cache_port = atoi(argv[11]);
#endif
#endif /* PHASE1 */

	opterr = 0;
	while ((c = getopt(argc, argv, "a:c:d:i:l:o:p:r:t:u:")) != -1)
	{
		switch (c)
		{
			case 'a':
				altered = 1;
			case 'c':
				customers = atoi(optarg);
				break;
			case 'd':
				strcpy(sname, optarg);
				break;
			case 'i':
				item_count = atoi(optarg);
				break;
			case 'l':
				duration = atoi(optarg);
				break;
			case 'o':
				strcpy(output_path, optarg);
				break;
			case 'p':
				port = atoi(optarg);
				break;
			case 'r':
				rampuprate = atoi(optarg);
				break;
			case 't':
				think_time = atof(optarg);
				break;
			case 'u':
				eus = atoi(optarg);
				break;
			case '?':
				if (isprint(optopt))
				{
					fprintf(stderr, "Unknown option `-%c'.\n", optopt);
				}
				else
				{
					fprintf (stderr, "Unknown option character `\\x%x'.\n",
						optopt);
				}
				return 1;
			default:
				printf("usage: %s <filename>\n", argv[0]);
				return 1;
		}
	}

	/* Initialize global variables. */
	init_common();

	/*
	 * Calculate the stop time before the users are started and factor in
	 * the rampup time.
	 */
	stop_time = time(NULL) + duration + (int) ((eus / rampuprate) * 60);

	/* Start the user threads. */
#ifdef PHASE1
#ifdef SEARCH_RESULTS_CACHE
	init_eus(sname, uname, auth, eus, MIX_SHOPPING, rampuprate, duration,
		think_time, item_count, cache_host, cache_port);
#else
	init_eus(sname, uname, auth, eus, MIX_SHOPPING, rampuprate, duration,
		think_time, item_count);
#endif
#endif /* PHASE1 */

#ifdef PHASE2
	init_eus(sname, port, eus, MIX_SHOPPING, rampuprate, duration,
		think_time, item_count);
#endif /* PHASE2 */

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

	return 0;
}
