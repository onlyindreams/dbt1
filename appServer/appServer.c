/*
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2002 Open Source Development Lab, Inc.
 * History: 
 * 2002 Created by Mark Wong & Jenny Zhang
 * Aug-2003: rewrote the command line parsing part by Jenny Zhang
 */

#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <errno.h>
#include <ctype.h>
#include <semaphore.h>
#include <unistd.h>
#include <signal.h>
#include <getopt.h>
#include <_socket.h>
#include <common.h>
#include <db.h>
#include <app_interface.h>
#include <app_txn_array.h>
#include <app_txn_queue.h>
#include <app_threadpool.h>

#ifdef HAVE_CONFIG_H
#include "../config.h"
#endif

void *DoConnection(void *fd);
void sighandler(int signum);

static int connectioncount = 0;
#define MODE_CACHE_OFF 0
#define MODE_CACHE_ON 1

/* globals */

/* mutex to control access to the queue */
pthread_mutex_t queue_mutex;

/* semaphore to wait in DoTxn thread, each time a queue item is
 * added to the queue, the semaphore must be released once
 */
sem_t TxnQSem;

/* the transaction queue */
struct Queue TxnQ;

/* mutex for each each entry in the queue, this is used to 
 * notify the DoConnection thread that the transaction is done
 */
struct condition_bundle_t *queue_entry_condition;

#ifdef GET_TIME
FILE *timefp;
pthread_mutex_t time_log_mutex = PTHREAD_MUTEX_INITIALIZER;
#endif /* GET_TIME */

char search_results_cache_host[32];
int search_results_cache_port;

pthread_mutex_t mutex_app_server = PTHREAD_MUTEX_INITIALIZER;

int help;
int port, PoolThreads, TxnQSize, ArraySize;

struct db_conn_t db_conn;

int altered = 0;
int usage(char *name);

int main(int argc, char *argv[]) 
{
	int mastersock, workersock;
	struct sockaddr_in socketaddr;
	int addrlen;
	pthread_t ConnThread;
	int rec;
	struct sigaction sa;
	int c;
#ifdef GET_TIME
	char filename[512];
#endif /* GET_TIME */


	strcpy(db_conn.dbhost, "localhost");
	strcpy(db_conn.dbport, "5432");
	strcpy(db_conn.dbname, "DBT1");
	strcpy(db_conn.dbuser, "dbt");
	strcpy(db_conn.dbpass, "dbt");

	help = 0;
	ArraySize = 100;
	PoolThreads = 20;
	port = 9992;
	mode_cache = MODE_CACHE_OFF;
	TxnQSize = 100;
	strcpy(search_results_cache_host, "localhost");
	search_results_cache_port = 9999;
	item_count = 1000;

	setlinebuf(stdout);
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &sighandler;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		printf("can not register signal handler to SIGUSR1\n");
		return -1;
	}
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		printf("can not register signal handler to SIGINT\n");
		return -1;
	}

	if (argc < 1)
	{
		return usage(argv[0]);
	}

	while (1)
	{
		static struct option long_options[] = {
			{ "dbhost", required_argument, 0, 0 },
			{ "dbport", required_argument, 0, 0 },
			{ "dbname", required_argument, 0, 0 },
			{ "dbuser", required_argument, 0, 0 },
			{ "dbpass", required_argument, 0, 0 },
			{ "dbconn", required_argument, 0, 0 },
			{ "server_port", required_argument, 0, 0 },
			{ "txn_q_size", required_argument, 0, 0 },
			{ "txn_a_size", required_argument, 0, 0 },
			{ "item_count", required_argument, 0, 0 },
			{ "access_cache", no_argument, &mode_cache, MODE_CACHE_ON },
			{ "cache_host", required_argument, 0, 0 },
			{ "cache_port", required_argument, 0, 0 },
			{ "output_path", required_argument, 0, 0 },
			{ "debug", no_argument, 0, 0 },
			{ "altered", no_argument, &altered, 1 },
			{ "help", no_argument, &help, 1},
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
				if (strcmp(long_options[option_index].name, "help") == 0)
				{
					break;
				}
				else if (strcmp(long_options[option_index].name, "dbhost") == 0)
				{
					strcpy(db_conn.dbhost, optarg);
				}
				else if (strcmp(long_options[option_index].name, "dbname") == 0)
				{
					strcpy(db_conn.dbname, optarg);
				}
				else if (strcmp(long_options[option_index].name, "dbport") == 0)
				{
					strcpy(db_conn.dbport, optarg);
				}
				else if (strcmp(long_options[option_index].name, "dbuser") == 0)
				{
					strcpy(db_conn.dbuser, optarg);
				}
				else if (strcmp(long_options[option_index].name, "dbpass") == 0)
				{
					strcpy(db_conn.dbpass, optarg);
				}
				else if (strcmp(long_options[option_index].name, "dbconn") == 0)
				{
					PoolThreads = atoi(optarg);
				}
				else if (strcmp(long_options[option_index].name, "server_port") == 0)
				{
					port = atoi(optarg);
				}
				else if (strcmp(long_options[option_index].name, "txn_q_size") == 0)
				{
					TxnQSize = atoi(optarg);
				}
				else if (strcmp(long_options[option_index].name, "txn_a_size") == 0)
				{
					ArraySize = atoi(optarg);
				}
				else if (strcmp(long_options[option_index].name, "item_count") == 0)
				{
					item_count = atoi(optarg);
				}
				else if (strcmp(long_options[option_index].name, "cache_host") == 0)
				{
					strcpy(search_results_cache_host, optarg);
				}
				else if (strcmp(long_options[option_index].name, "cache_port") == 0)
				{
					search_results_cache_port = atoi(optarg);
				}
				else if (strcmp(long_options[option_index].name, "output_path") == 0)
				{
					strcpy(output_path, optarg);
				}
				else if (strcmp(long_options[option_index].name, "debug") == 0)
				{
					LogDebug = 1;
				}
				break;
			default:
				printf ("?? getopt returned character code 0%o ??\n", c);
				exit(1);
		}
	}

	if ( help )
	{
		return usage(argv[0]);
	}
	
	init_common();

	mastersock = _server_init_socket(port);

	if (mastersock < 0)
	{
		LOG_ERROR_MESSAGE("init server master socket failed\n");
		printf("init server master socket failed\n");
		return -1;
	}

	/* create the threadpool. */
	if (!init_thread_pool(PoolThreads, TxnQSize, db_conn))
	{
		LOG_ERROR_MESSAGE("InitThreadPool() failed with %d connection",
			PoolThreads);
		return -1;
  	}

	/* Initialize app_txn_array */
	init_app_txn_array(&app_admin_confirm_array, ArraySize);
	init_app_txn_array(&app_admin_request_array, ArraySize);
	init_app_txn_array(&app_best_sellers_array, ArraySize);
	init_app_txn_array(&app_buy_confirm_array, ArraySize);
	init_app_txn_array(&app_buy_request_array, ArraySize);
	init_app_txn_array(&app_home_array, ArraySize);
	init_app_txn_array(&app_new_products_array, ArraySize);
	init_app_txn_array(&app_order_display_array, ArraySize);
	init_app_txn_array(&app_order_inquiry_array, ArraySize);
	init_app_txn_array(&app_product_detail_array, ArraySize);
	init_app_txn_array(&app_search_request_array, ArraySize);
	init_app_txn_array(&app_search_results_array, ArraySize);
	init_app_txn_array(&app_shopping_cart_array, ArraySize);
	/* initialize TxnQ */
	init_queue(&TxnQ, TxnQSize);
#ifdef GET_TIME
	if (output_path[0] != '\0')
	{
		sprintf(filename, "%stime.log", output_path);
	}
	else
	{
		strcpy(filename, "time.log");
	}
	timefp = fopen(filename, "w");
	if (timefp == NULL)
	{
		LOG_ERROR_MESSAGE("cannot open file time.log\n");
		return -1;
	}
#endif /* GET_TIME */

	/*
	 * Do not change this output. The run script may watch this.
	 * See `run_dbt1.sh' for more details.
	 */
	printf("The app server is active...\n");

	while (1) {
		addrlen = sizeof(socketaddr);
		pthread_mutex_lock(&mutex_app_server);
		workersock = accept(mastersock, (struct sockaddr *) &socketaddr,
			(socklen_t *)&addrlen);
		if (workersock < 0) {
			printf("accept failed: %d\n", errno);
			if (altered == 0)
			{
				LOG_ERROR_MESSAGE(
					"accept couldn't open worker socket, errno %d", errno);
				return -1;
			}
			break;
		}

		connectioncount++;
		if ((rec = pthread_create(&ConnThread, NULL, DoConnection,
			&workersock)) != 0)
		{
			if (altered == 0)
			{
				LOG_ERROR_MESSAGE("pthread_create failed: %s", strerror(rec));
				return -1;
			}
			--connectioncount;
			printf("Connection attempt made, but we cannot start a new pthread.  Stop listening...");
			break;
		}

		/*
		 * Do not change this output. The run script may watch this.
		 * See `run_dbt1.sh' for more details.
		 */
		printf("%d client connections have been established.\n", connectioncount);
		fflush(stdout);
	}
	close(mastersock);
	printf("%d client connections have been established.\n", connectioncount);
	while (1)
	{
		sleep(60);
	}
	printf("Shutting down.\n");

 
	return 0;
}

void sighandler(int signum)
{
	if (signum == SIGUSR1)
		printf("db connect thread failed, please check error.log\n");
	else if (signum == SIGINT)
	{
		printf("program ended by user\n");
		popen("ps -ef | grep appServer|grep -v 'grep' | awk '{print $2}' | xargs -t -i kill -9 {}", "r");
		exit(1);
	}
	_exit(-1);
}

/* Handle connection requests from a user. */
void *DoConnection(void *fd)
{
	int *sf;
	int workersock;
	int QIndex;
	struct QItem TxnQItem;
	int rec;
#ifdef GET_TIME
	struct timeval receive_request_time,  send_response_time, t1;
	double server_response_time, db_response_time = 0, server_db_time;
#endif /* GET_TIME */
	
	sf = (int *)(fd);
	workersock = *sf;
	pthread_mutex_unlock(&mutex_app_server);
	while (1)
	{
		if ((rec = receive_transaction_packet(workersock, &TxnQItem)) ==
			ERROR) 
		{
			LOG_ERROR_MESSAGE("receive_transaction_packet failed");
			close(workersock);
			pthread_exit(NULL);
		}
		if (rec == SOCKET_CLOSE)
		{
			LOG_ERROR_MESSAGE("driver socket closed");
			close(workersock);
			pthread_exit(NULL);
		}
#ifdef GET_TIME
		if (gettimeofday(&receive_request_time, NULL)== -1)
		{
			LOG_ERROR_MESSAGE("gettimeofday failed");
		}
#endif /* GET_TIME */
		/* add interaction to txnQ */
		pthread_mutex_lock(&queue_mutex);
		QIndex = enqueue(TxnQItem, &TxnQ);
		if (QIndex == -1)
		{
			pthread_mutex_unlock(&queue_mutex);
			close(workersock);
			LOG_ERROR_MESSAGE("enquue failed");
			pthread_exit(NULL);
		}
		pthread_mutex_unlock(&queue_mutex);

		sem_post(&TxnQSem);
#ifdef GET_TIME
		if (gettimeofday(&t1, NULL) == -1)
		{
			LOG_ERROR_MESSAGE("gettimeofday failed");
		}
#endif /* GET_TIME */
		/* wait for transation done */
		pthread_mutex_lock(&queue_entry_condition[QIndex].condition_mutex);
		while (!queue_entry_condition[QIndex].done_flag)
			pthread_cond_wait(&queue_entry_condition[QIndex].done_cv,
				&queue_entry_condition[QIndex].condition_mutex);
		queue_entry_condition[QIndex].done_flag = 0;
		pthread_mutex_unlock(&queue_entry_condition[QIndex].condition_mutex);
			
#ifdef GET_TIME
		if (gettimeofday(&send_response_time, NULL) == -1)
		{
			LOG_ERROR_MESSAGE("gettimeofday failed");
		}
		server_response_time =
			time_diff(receive_request_time, send_response_time);
		server_db_time = time_diff(t1,send_response_time);
		switch (TxnQItem.TxnType)
		{
			case ADMIN_CONFIRM:
				db_response_time =
					app_admin_confirm_array.db_response_time[TxnQItem.SlotID];
				break;
			case ADMIN_REQUEST:
				db_response_time =
					app_admin_request_array.db_response_time[TxnQItem.SlotID];
				break;
			case BEST_SELLERS:
				db_response_time =
					app_best_sellers_array.db_response_time[TxnQItem.SlotID];
				break;
			case BUY_CONFIRM:
				db_response_time =
					app_buy_confirm_array.db_response_time[TxnQItem.SlotID];
				break;
			case BUY_REQUEST:
				db_response_time =
					app_buy_request_array.db_response_time[TxnQItem.SlotID];
				break;
			case HOME:
				db_response_time =
					app_home_array.db_response_time[TxnQItem.SlotID];
				break;
			case NEW_PRODUCTS:
				db_response_time =
					app_new_products_array.db_response_time[TxnQItem.SlotID];
				break;
			case ORDER_DISPLAY:
				db_response_time =
					app_order_display_array.db_response_time[TxnQItem.SlotID];
				break;
			case ORDER_INQUIRY:
				db_response_time =
					app_order_inquiry_array.db_response_time[TxnQItem.SlotID];
				break;
			case PRODUCT_DETAIL:
				db_response_time =
					app_product_detail_array.db_response_time[TxnQItem.SlotID];
				break;
			case SEARCH_REQUEST:
				db_response_time =
					app_search_request_array.db_response_time[TxnQItem.SlotID];
				break;
			case SEARCH_RESULTS:
				db_response_time =
					app_search_results_array.db_response_time[TxnQItem.SlotID];
				break;
			case SHOPPING_CART:
				db_response_time =
					app_shopping_cart_array.db_response_time[TxnQItem.SlotID];
				break;
		}
		pthread_mutex_lock(&time_log_mutex);
		fprintf(timefp, "%s, total %f, db %f, server_db_time %f\n",
			interaction_short_name[TxnQItem.TxnType], 
			server_response_time, db_response_time, server_db_time);
		fflush(timefp);
		pthread_mutex_unlock(&time_log_mutex);
#endif /* GET_TIME */
		if(send_transaction_packet(workersock, TxnQItem) != OK) 
		{
			LOG_ERROR_MESSAGE("send_transaction_packet failed");
			close(workersock);
			pthread_exit(NULL);
		}
	}
	close(workersock);
	return NULL;
}

int usage(char *name)
{
	printf("\nUsage: %s [option]...\n\n", name);

	printf("Options:\n");
	printf("    --dbhost <hostname>          Hostname for database connection. (default:%s)\n", db_conn.dbhost);
	printf("                                 Use a datasource name when using ODBC interfaces.\n");
	printf("    --dbport <port>              Port number for database connection. (default:%s)\n", db_conn.dbport);
	printf("    --dbname <dbname>            Database name for database connection. (default:%s)\n", db_conn.dbname);
	printf("    --dbuser <username>          Username for database connection. (default:%s)\n", db_conn.dbuser);
	printf("    --dbpass <password>          Password for database connection. (default:%s)\n", db_conn.dbpass);
	printf("    --dbconn <connection>        Number of database connections. (default:%d)\n", PoolThreads);
	printf("    --server_port <port>         Listening port for waiting dbdriver. (default:%d)\n", port);
	printf("    --txn_q_size <queue size>    Transaction queue size. (default:%d)\n", TxnQSize);
	printf("    --txn_a_size <array size>    Transaction array size. (default:%d)\n", ArraySize);
	printf("    --item_count <items>         Number of item table records. (default:%d)\n", item_count);
	printf("    --output_path <output_path>  Log output directory. (default:%s)\n", output_path);
	printf("    --debug\n");
	printf("    --altered\n");
	printf("    --help\n");
	printf("\n");

	printf("Options for the search results cache:\n");
	printf("    --access_cache               Enable the search results cache. (default:disabled)\n");
	printf("    --cache_host <hostname>      Hostname for cache connection. (default:%s)\n", search_results_cache_host);
	printf("    --cache_port <port>          Port number for cache connection. (default:%d)\n", search_results_cache_port);
	printf("    \n");

	return 1;
}
