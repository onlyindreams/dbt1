/*
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2002 Mark Wong & Jenny Zhang &
 *                    Open Source Development Lab, Inc.
 *
 */

#include <sys/time.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <ctype.h>
#include <sys/types.h>
#include <signal.h>
#include <cache.h>
#include <cache_interface.h>
#include <common.h>
#include <odbc_interaction.h>
#include <odbc_interaction_search_results.h>
#include <_socket.h>

struct search_results *author_results_table;
struct search_results *title_results_table;
void *warm_up_cache(void *fd);
void *cache_thread(void *fd);
void sighandler(int signum);

pthread_mutex_t mutex_cache_server=PTHREAD_MUTEX_INITIALIZER;
sem_t sem_warm_up;
int sanity_check = 1;

int undo_digsyl(char *search_string);

int main(int argc, char *argv[])
{
	int mastersock, workersock;
	struct sockaddr_in socketaddr;
	char sname[32], uname[32], auth[32];
	pthread_t *warm_up_thread_id;
	pthread_t connect_thread;
	struct table_range *range;
	int port, db_thread, num_items, connectioncount;
	int addrlen;
	int i, j, rec;
	struct sigaction sa;
	int c;
	int warm_up_threads = 1;
	int sem_val;

	setlinebuf(stdout);
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &sighandler;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		printf("can not register signal handler to SIGUSR1\n");
		return -1;
	}
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		printf("can not register signal handler to SIGUSR2\n");
		return -1;
	}
	if (sigaction(SIGSEGV, &sa, NULL) == -1)
	{
		printf("can not register signal handler to SIGSEGV\n");
		return -1;
	}

	if (argc < 13)
	{
		printf("usage: %s -d <dbnodename> -u <username> -p <password> -l <port> -c <db_connection> -i <items>\n", argv[0]);
		return -1;
	}

	opterr = 0;
	while ((c = getopt(argc, argv, "c:d:i:l:p:u:")) != -1)
	{
		switch (c)
		{
			case 'c':
				db_thread=atoi(optarg);
				break;
			case 'd':
				strcpy(sname, optarg);
				break;
			case 'i':
				num_items=atoi(optarg);
				item_count=num_items;
				break;
			case 'l':
				port = atoi(optarg);
				break;
			case 'p':
				strcpy(auth, optarg);
				break;
			case 'u':
				strcpy(uname, optarg);
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
				return -1;
		}
	}
	init_common();
	
	warm_up_thread_id=(pthread_t *)malloc(warm_up_threads*sizeof(pthread_t));
	range=(struct table_range *)malloc(warm_up_threads*sizeof(struct table_range));

	if (init_cache(num_items, sname, uname, auth) != OK)
	{
		printf("init_odbc environment failed\n");
		return -1;
	}
	
	/* create threads to fill out the results tables */
	if (sem_init(&sem_warm_up, 0, 0) != 0)
	{
		perror("sem_init");
		return -1;
	}
	range[0].author_start = 0;
	range[0].author_end = num_items / 10 - 1;
	range[0].title_start = 0;
	range[0].title_end = num_items / 5 - 1;
	for (i=0; i<warm_up_threads; i++)
	{
		sem_post(&sem_warm_up);
		if (pthread_create (&warm_up_thread_id[i], NULL, warm_up_cache, (void *)&range[i]) != 0)
		{
			printf("warm_up thread create failed");
			return -1;
		}

	}

	/* wait for all threads to finish */
	do
	{
		sleep(2);
		sem_getvalue(&sem_warm_up, &sem_val);
	} while (sem_val > 0);

	printf("Cache is warm.\n");

	if (sanity_check == 1)
	{
		printf("Data sanity check.\n");
		printf("Results for a_lname search:\n");
		printf("a_id items i_r1 i_t1 i_r2 i_t2 i_r3 i_t3 i_r4 i_t4 i_r5 i_t5\n");

		/* Check results for an a_lname search. */
		for (i = 0; i < num_items / 10; i++)
		{
			printf("%4d %5d", i + 1, author_results_table[i].record_number);
			for(j = 0; j < 5; j++)
			{
				printf(" %4lld %4lld", author_results_table[i].i_related[j],
					author_results_table[i].i_thumbnail[j]);
			}
			printf("\n");
		}

		/* Check results for an i_title search. */
		printf("Results for i_title search:\n");
		printf("i_id items i_r1 i_t1 i_r2 i_t2 i_r3 i_t3 i_r4 i_t4 i_r5 i_t5\n");
		for (i = 0; i < num_items / 10; i++)
		{
			printf("%4d %5d", i + 1, title_results_table[i].record_number);
			for(j = 0; j < 5; j++)
			{
				printf(" %4lld %4lld", title_results_table[i].i_related[j],
					title_results_table[i].i_thumbnail[j]);
			}
			printf("\n");
		}
		printf("Data sanity check complete.\n");
	}

	mastersock = _server_init_socket(port);
	if (mastersock < 0)
	{
		printf("init cache server master socket failed\n");
		return -1;
	}

	printf("The cache server is active...\n");

	connectioncount=0;
	while (1) {
		addrlen = sizeof(socketaddr);
		pthread_mutex_lock(&mutex_cache_server);
		workersock = accept(mastersock, (struct sockaddr *)&socketaddr, (socklen_t *)&addrlen);
		if (workersock < 0) {
			LOG_ERROR_MESSAGE("accept couldn't open worker socket, errno %d", errno);
		}

		connectioncount++;
		printf("got %d connection\n", connectioncount);
		if ((rec=pthread_create(&connect_thread, NULL, cache_thread, &workersock)) != 0)    
		{
			LOG_ERROR_MESSAGE("pthread_create failed, rec=%d", rec);
			return -1;
		}
	}
	printf("Shutting down.\n");

	close(mastersock);
 
	return 0;
	
}

void sighandler(int signum)
{
	if (signum==SIGUSR1)
		printf("connect to database failed\n");
	else if (signum==SIGUSR2)
		printf("warm up threads failed\n");
	else if (signum==SIGSEGV)
		printf("memory violation\n");
	printf("please check error.log\n");
	_exit(-1);
}

/* allocate results tables and initialize odbc environment */
int init_cache(int item, char *sname, char *uname, char *auth)
{
	int rc;
	author_results_table=malloc(item/10*sizeof(struct search_results));	
	title_results_table=malloc(item/5*sizeof(struct search_results));	

	if ((rc=odbc_init(sname, uname, auth))!=OK)
	{
		return W_ERROR;
	}
	return OK;
}

/* thread filling out results tables */
void *warm_up_cache(void *fd)
{
	struct table_range *range;
	int rc, i, j, k;
	struct odbc_context_t odbcc;
	union odbc_data_t odbc_data;

	range = (struct table_range *)(fd);

	srand(time(NULL) + pthread_self());
	rc = odbc_connect(&odbcc);
	if (rc == W_ERROR)
	{
		LOG_ERROR_MESSAGE("odbc_connect error\n");
		kill(0, SIGUSR1);
		pthread_exit(NULL);
	}

	/* do search_by_author*/
	odbc_data.search_results_odbc_data.eb.search_type=SEARCH_AUTHOR;
	for (i=range->author_start; i<=range->author_end;i++)
	{
		digsyl2(odbc_data.search_results_odbc_data.eb.search_string, (long long)i+1, (long long)7);
		rc = execute_search_results(&odbcc, &odbc_data);
		if (rc == W_ERROR)
		{
			LOG_ERROR_MESSAGE("execute_search_results returned error");
			kill(0, SIGUSR2);
			pthread_exit(NULL);
		}

		/* copy the results out */
		author_results_table[i].record_number=odbc_data.search_results_odbc_data.eb.items;

		for (j=0; j<odbc_data.search_results_odbc_data.eb.items; j++)
		{
			author_results_table[i].search_results[j].i_id=odbc_data.search_results_odbc_data.eb.results_data[j].i_id;
			strcpy(author_results_table[i].search_results[j].i_title, odbc_data.search_results_odbc_data.eb.results_data[j].i_title);
			strcpy(author_results_table[i].search_results[j].a_fname, odbc_data.search_results_odbc_data.eb.results_data[j].a_fname);
			strcpy(author_results_table[i].search_results[j].a_lname, odbc_data.search_results_odbc_data.eb.results_data[j].a_lname);
		}
		for (k=0; k<PROMOTIONAL_ITEMS_MAX; k++)
		{
			author_results_table[i].i_related[k]= odbc_data.search_results_odbc_data.eb.pp_data.i_related[k];
			author_results_table[i].i_thumbnail[k]= odbc_data.search_results_odbc_data.eb.pp_data.i_thumbnail[k];
		}
	}

	/* do search_by_title*/
	odbc_data.search_results_odbc_data.eb.search_type=SEARCH_TITLE;
	for (i=range->title_start; i<=range->title_end;i++)
	{
		digsyl2(odbc_data.search_results_odbc_data.eb.search_string, (long long)i+1, (long long)7);
		rc = execute_search_results(&odbcc, &odbc_data);
		if (rc == W_ERROR)
		{
			LOG_ERROR_MESSAGE("execute_search_results returned error");
			kill(0, SIGUSR2);
			pthread_exit(NULL);
		}

		/* copy the results out */
		title_results_table[i].record_number=odbc_data.search_results_odbc_data.eb.items;

		for (j=0; j<odbc_data.search_results_odbc_data.eb.items; j++)
		{
			title_results_table[i].search_results[j].i_id=odbc_data.search_results_odbc_data.eb.results_data[j].i_id;
			strcpy(title_results_table[i].search_results[j].i_title, odbc_data.search_results_odbc_data.eb.results_data[j].i_title);
			strcpy(title_results_table[i].search_results[j].a_fname, odbc_data.search_results_odbc_data.eb.results_data[j].a_fname);
			strcpy(title_results_table[i].search_results[j].a_lname, odbc_data.search_results_odbc_data.eb.results_data[j].a_lname);
		}
		for (k=0; k<PROMOTIONAL_ITEMS_MAX; k++)
		{
			title_results_table[i].i_related[k]= odbc_data.search_results_odbc_data.eb.pp_data.i_related[k];
			title_results_table[i].i_thumbnail[k]= odbc_data.search_results_odbc_data.eb.pp_data.i_thumbnail[k];
		}
	}
	odbc_disconnect(&odbcc);
	sem_wait(&sem_warm_up);
	return NULL;
}

void *cache_thread(void *fd)
{
	int *sf;
	int workersock;
	int rec;
	struct search_results_t search_results;
	int index, i;

	sf = (int *)(fd);
	workersock = *sf;
	pthread_mutex_unlock(&mutex_cache_server);

	while (1)
	{
		/* receive search results request */
		if ((rec=receive_search_results(workersock, &search_results)) == W_ERROR)
		{
			LOG_ERROR_MESSAGE("receive_search_results_request failed");
			close(workersock);
			pthread_exit(NULL);
		}		
		if (rec == 0)
		{
			LOG_ERROR_MESSAGE("driver socket closed");
			close(workersock);
			pthread_exit(NULL);
                }
		
		/* look up the results*/
		index=undo_digsyl(search_results.search_string);
		if (index==-1)
		{
			LOG_ERROR_MESSAGE("undo_digsyl failed");
			close(workersock);
			pthread_exit(NULL);
		}
		if (search_results.search_type==SEARCH_AUTHOR)
		{
			/* copy out data */
			search_results.items=author_results_table[index].record_number;
			for(i=0; i<author_results_table[index].record_number; i++)
			{
				search_results.results_data[i].i_id=author_results_table[index].search_results[i].i_id;
				strcpy(search_results.results_data[i].i_title, author_results_table[index].search_results[i].i_title);
				strcpy(search_results.results_data[i].a_fname, author_results_table[index].search_results[i].a_fname);
				strcpy(search_results.results_data[i].a_lname, author_results_table[index].search_results[i].a_lname);
			}
			/* copy out promotion data */
			for (i=0; i<PROMOTIONAL_ITEMS_MAX; i++)
			{
				search_results.pp_data.i_related[i]=author_results_table[index].i_related[i];
				search_results.pp_data.i_thumbnail[i]=author_results_table[index].i_thumbnail[i];
			}
		}
		else if (search_results.search_type==SEARCH_TITLE)
		{
			search_results.items=title_results_table[index].record_number;
			/* copy out data */
			for(i=0; i<title_results_table[index].record_number; i++)
			{
				search_results.results_data[i].i_id=title_results_table[index].search_results[i].i_id;
				strcpy(search_results.results_data[i].i_title, title_results_table[index].search_results[i].i_title);
				strcpy(search_results.results_data[i].a_fname, title_results_table[index].search_results[i].a_fname);
				strcpy(search_results.results_data[i].a_lname, title_results_table[index].search_results[i].a_lname);
			}
			/* copy out promotion data */
			for (i=0; i<PROMOTIONAL_ITEMS_MAX; i++)
			{
				search_results.pp_data.i_related[i]=title_results_table[index].i_related[i];
				search_results.pp_data.i_thumbnail[i]=title_results_table[index].i_thumbnail[i];
			}
		}
		else
		{
			LOG_ERROR_MESSAGE("wrong search type");
			close(workersock);
			pthread_exit(NULL);
		}		
		
		
		/* send results back */
		if ((rec=send_search_results(workersock, &search_results)) == W_ERROR)
		{
			LOG_ERROR_MESSAGE("send_search_results_response failed");
			close(workersock);
			pthread_exit(NULL);
		}		
	}
	close(workersock);
}

int undo_digsyl(char *search_string)
{
	int i, j, k;
	int rec, digit, base;

	j=0;
	rec=0;
	for(i=13; i>=0; i=i-2)
	{
		if (search_string[i]=='A') digit=0;
		else if (search_string[i]=='I') digit=3;
		else if (search_string[i]=='T') digit=6;
		else if (search_string[i]=='N') digit=8;
		else if (search_string[i]=='G')
		{
			if (search_string[i-1]=='O') digit=1;
			else if (search_string[i-1]=='N') digit=9;
			else 
			{
				LOG_ERROR_MESSAGE("no digit for syllable %cG", search_string[i-1]);
				return -1;
			}
		}
		else if (search_string[i]=='L')
		{
			if (search_string[i-1]=='A') digit=2;
			else if (search_string[i-1]=='U') digit=7;
			else 
			{
				LOG_ERROR_MESSAGE("no digit for syllable %cL", search_string[i-1]);
				return -1;
			}
		}
		else if (search_string[i]=='E')
		{
			if (search_string[i-1]=='R') digit=4;
			else if (search_string[i-1]=='S') digit=5;
			else 
			{
				LOG_ERROR_MESSAGE("no digit for syllable %cE", search_string[i-1]);
				return -1;
			}
		}
		else 
		{
			LOG_ERROR_MESSAGE("no digit for syllable %c%c", search_string[i-1], search_string[i]);
			return -1;
		}
		base=1;
		for(k=0; k<j; k++)
			base=base*10;
		rec+=base*digit;
		j++;
	}
	return rec;
}
