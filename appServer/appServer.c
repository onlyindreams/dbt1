/*
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2002 Mark Wong & Jenny Zhang &
 *                    Open Source Development Lab, Inc.
 *
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
#include <_socket.h>
#include <common.h>
#include <app_interface.h>
#include <app_txn_array.h>
#include <app_txn_queue.h>
#include <app_threadpool.h>

void *DoConnection(void *fd);
void sighandler(int signum);

static int connectioncount = 0;

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

int altered = 0;

int main(int argc, char *argv[]) 
{
	int mastersock, workersock;
	struct sockaddr_in socketaddr;
	int addrlen;
	char sname[32], uname[32], auth[32];
	pthread_t ConnThread;
	int rec;
	int port, PoolThreads, TxnQSize, ArraySize;
	struct sigaction sa;
	int c;
#ifdef GET_TIME
	char filename[512];
#endif /* GET_TIME */

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

	if (argc < 9)
	{
		printf("usage: appServer -d <dbnodename> -u <username> -p <password> -l <port>\n");
		printf("                 -c <db_connection> -q <transaction queue size>\n");
		printf("                 -a <transaction array size> -i <items>\n");
		printf("                 -x <search_results_cache_host> -y <search_results_cache_port>\n");
		printf("                 -m <0|1>\n");
		printf("\n");
		printf("-m 1 accesses the cache and requires -x and -y, default\n");
		printf("-m 0 does not access the cache\n");
		return -1;
	}

	opterr = 0;
	while ((c = getopt(argc, argv, "a:c:d:i:l:m:o:p:q:u:x:y:z")) != -1)
	{
		switch (c)
		{
			case 'a':
				ArraySize = atoi(optarg);
				break;
			case 'c':
				PoolThreads = atoi(optarg);
				break;
			case 'd':
				strcpy(sname, optarg);
				break;
			case 'i':
				item_count = atoi(optarg);
				break;
			case 'l':
				port = atoi(optarg);
				break;
			case 'm':
				mode_cache = atoi(optarg);
				break;
			case 'o':
				strcpy(output_path, optarg);
				break;
			case 'p':
				strcpy(auth, optarg);
				break;
			case 'q':
				TxnQSize = atoi(optarg);
				break;
			case 'u':
				strcpy(uname, optarg);
				break;
			case 'x':
				strcpy(search_results_cache_host, optarg);
				break;
			case 'y':
				search_results_cache_port = atoi(optarg);
				break;
			case 'z':
				altered = 1;
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

	mastersock = _server_init_socket(port);

	if (mastersock < 0)
	{
		LOG_ERROR_MESSAGE("init server master socket failed\n");
		printf("init server master socket failed\n");
		return -1;
	}

	/* create the threadpool. */
	if (!init_thread_pool(PoolThreads, TxnQSize, sname, uname, auth))
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
				LOG_ERROR_MESSAGE("pthread_create failed, rec=%d", rec);
				return -1;
			}
			--connectioncount;
			printf("Connection attempt made, but we cannot start a new pthread.  Stop listening...");
			break;
		}
		printf("%d client connections have been established.\n", connectioncount);
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
			W_ERROR) 
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
