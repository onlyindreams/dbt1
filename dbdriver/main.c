/*
 * main.c
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2002 Mark Wong & Jenny Zhang &
 *                    Open Source Development Lab, Inc.
 *
 * 30 janurary 2002
 */

#include <stdlib.h>
#include <common.h>
#include <eu.h>

/*
 * main() just takes arguments off the command line, starts up the rest of
 * the program and waits for the application to finish.
 */
int main(int argc, char *argv[])
{
	int eus, rampuprate, duration, port;
	double think_time;
	int running_eus;
	char sname[32], uname[32], auth[32];
	time_t stop_time;
#ifdef PHASE1
#ifdef SEARCH_RESULTS_CACHE
	char cache_host[32];
	int cache_port;
#endif
#endif


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
	if (argc != 9)
	{
		printf("usage: %s <servername> <port> <items> <customers> <eus> <eus/min> <think time> <duration>\n",
			argv[0]);
		return -1;
	}
#endif /* PHASE2 */

	strcpy(sname, argv[1]);

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

#ifdef PHASE2
	port = atoi(argv[2]);
	item_count = atoi(argv[3]);
	customers = atoi(argv[4]);
	eus = atoi(argv[5]);
	rampuprate = atoi(argv[6]);
	think_time = atof(argv[7]);
	duration = atoi(argv[8]);
#endif /* PHASE2 */

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
	do
	{
		sem_getvalue(&running_eu_count, &running_eus);
		sleep(1);
	}
	while (time(NULL) <= stop_time);

	return 0;
}
