/*
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2002 Mark Wong & Jenny Zhang &
 *                    Open Source Development Lab, Inc.
 *
 */

#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <signal.h>
#include "_socket.h"
#include "common.h"
#include "app_txn_array.h"
#include "app_txn_queue.h"
#include "app_threadpool.h"

void *DoConnection(void *fd);
void sighandler(int signum);

static int connectioncount = 0;

/*globals*/
/*array to hold odbc input/output data
  though the data structure is the same for all the transaction,
  create an array for each transaction so that there is less contention
  trying to pin the slot
*/
struct app_txn_array app_admin_confirm_array;
struct app_txn_array app_admin_request_array;
struct app_txn_array app_best_sellers_array;
struct app_txn_array app_buy_confirm_array;
struct app_txn_array app_buy_request_array;
struct app_txn_array app_home_array;
struct app_txn_array app_new_products_array;
struct app_txn_array app_order_display_array;
struct app_txn_array app_order_inquiry_array;
struct app_txn_array app_product_detail_array;
struct app_txn_array app_search_request_array;
struct app_txn_array app_search_results_array;
struct app_txn_array app_shopping_cart_array;

/*mutex to control access to the queue*/
pthread_mutex_t queue_mutex;

/*semaphore to wait in DoTxn thread, each time a queue item is
  added to the queue, the semaphore must be released once
*/
sem_t TxnQSem;

/*the transaction queue*/
struct Queue TxnQ;

/*mutex for each each entry in the queue, this is used to 
  notify the DoConnection thread that the transaction is done
*/
struct condition_bundle_t *queue_entry_condition;

#ifdef GET_TIME
FILE *timefp;
pthread_mutex_t time_log_mutex=PTHREAD_MUTEX_INITIALIZER;
const char *interaction_short_name[INTERACTION_TOTAL] =
{
	"AC", "AR", "BS", "BC", "BR", "CR", "HO", "NP", "OD", "OI", "PD", "SR",
	"SU", "SC"
};
#endif

#ifdef SEARCH_RESULTS_CACHE
char search_results_cache_host[32];
int search_results_cache_port;
#endif

pthread_mutex_t mutex_app_server=PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char *argv[]) 
{
	int mastersock, workersock;
	struct sockaddr_in socketaddr;
	int addrlen;
	char buffer[1024];
	char size[100];
	char sname[32], uname[32], auth[32];
	pthread_t ConnThread;
	int rec;
	int port, PoolThreads, TxnQSize, ArraySize;
	struct sigaction sa;

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
#ifdef SEARCH_RESULTS_CACHE
		printf("usage: appServer <dbnodename> <username> <password> <port> <db_connection> <transaction queue size> <transaction array size> <items> <search_results_cache_host> <search_results_cache_port>\n");
#else
		printf("usage: appServer <dbnodename> <username> <password> <port> <db_connection> <transaction queue size> <transaction array size> <items>\n");
#endif
		return -1;
	}
	
	strcpy(sname, argv[1]);
	strcpy(uname, argv[2]);
	strcpy(auth, argv[3]);
	port = atoi(argv[4]);
	PoolThreads=atoi(argv[5]);
	TxnQSize=atoi(argv[6]);
	ArraySize=atoi(argv[7]);
	item_count=atoi(argv[8]);
#ifdef SEARCH_RESULTS_CACHE
	strcpy(search_results_cache_host, argv[9]);
	search_results_cache_port=atoi(argv[10]);
#endif
	init_common();
	/* create the threadpool. */
	if (!init_thread_pool(PoolThreads, TxnQSize, sname, uname, auth))
	{
		LOG_ERROR_MESSAGE("InitThreadPool() failed with %d connection", PoolThreads);
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
	timefp = fopen("time.log", "w");
        if (timefp == NULL)
        {
                LOG_ERROR_MESSAGE("cannot open file time.log\n");
                return -1;
        }
#endif
	mastersock = _server_init_socket(port);

	if (mastersock < 0)
	{
		LOG_ERROR_MESSAGE("init server master socket failed\n");
		perror("init server master socket failed");
		return -1;
	}

	printf("The server is active.	You may terminate it with Ctrl-C.\n");

	while (1) {
		addrlen = sizeof(socketaddr);
		pthread_mutex_lock(&mutex_app_server);
		workersock = accept(mastersock, (struct sockaddr *)&socketaddr, (socklen_t *)&addrlen);
		if (workersock < 0) {
			LOG_ERROR_MESSAGE("accept couldn't open worker socket, errno %d", errno);
			perror("accept failed");
			return -1;
		}

		connectioncount++;
		printf("%d users logged in\n", connectioncount);
		if ((rec=pthread_create(&ConnThread, NULL, DoConnection, &workersock)) != 0)    
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
		printf("db connect thread failed, please check error.log\n");
        else if (signum==SIGINT)
	{
                printf("program ended by user\n");
		popen("ps -ef|grep appServer|grep -v 'grep' |awk '{print $2}'| xargs -t -i kill -9 {}", "r");
		exit(1);
	}
        _exit(-1);
}

void *DoConnection(void *fd)
{
	int *sf;
	int workersock;
	char buffer[1024];
	char size[100];
	int QIndex;
	struct QItem TxnQItem;
	int rec;
#ifdef GET_TIME
	struct timeval receive_request_time,  send_response_time, t1;
	double server_response_time, db_response_time, server_db_time;
#endif
	
	sf = (int *)(fd);
	workersock = *sf;
	pthread_mutex_unlock(&mutex_app_server);
#ifdef DEBUG
	DEBUGMSG("pthread_id%ld: DoConnection: got connection", pthread_self());
#endif
	while (1)
	{
		if((rec=receive_transaction_packet(workersock, &TxnQItem)) == W_ERROR) 
		{
			LOG_ERROR_MESSAGE("receive_transaction_packet failed");
			close(workersock);
			pthread_exit(NULL);
		}
		if (rec==SOCKET_CLOSE)
		{
			LOG_ERROR_MESSAGE("driver socket closed");
			close(workersock);
			pthread_exit(NULL);
		}
#ifdef DEBUG
		DEBUGMSG("pthread_id%ld: TxnQItem txn_id %d, slot %d", pthread_self(), TxnQItem.TxnType, TxnQItem.SlotID);
#endif
#ifdef GET_TIME
		if (gettimeofday(&receive_request_time, NULL)== -1)
		{
			LOG_ERROR_MESSAGE("gettimeofday failed");
		}
#endif
		/*add interaction to txnQ */
		pthread_mutex_lock(&queue_mutex);
		QIndex=enqueue(TxnQItem, &TxnQ);
		if (QIndex==-1)
		{
			pthread_mutex_unlock(&queue_mutex);
			close(workersock);
			LOG_ERROR_MESSAGE("enquue failed");
			pthread_exit(NULL);
		}
		pthread_mutex_unlock(&queue_mutex);

		sem_post(&TxnQSem);
#ifdef GET_TIME
		if (gettimeofday(&t1, NULL)== -1)
		{
			LOG_ERROR_MESSAGE("gettimeofday failed");
		}
#endif
		/* wait for transation done */
#ifdef DEBUG
		DEBUGMSG("pthread_id%ld: wait for txn done...", pthread_self());
#endif
		pthread_mutex_lock(&queue_entry_condition[QIndex].condition_mutex);
		while (!queue_entry_condition[QIndex].done_flag)
			pthread_cond_wait(&queue_entry_condition[QIndex].done_cv, &queue_entry_condition[QIndex].condition_mutex);
		queue_entry_condition[QIndex].done_flag=0;
		pthread_mutex_unlock(&queue_entry_condition[QIndex].condition_mutex);
			
#ifdef DEBUG
		DEBUGMSG("pthread_id%ld: got it, txn done", pthread_self());
#endif
#ifdef GET_TIME
		if (gettimeofday(&send_response_time, NULL)== -1)
		{
			LOG_ERROR_MESSAGE("gettimeofday failed");
		}
		server_response_time=time_diff(receive_request_time, send_response_time);
		server_db_time=time_diff(t1,send_response_time);
		switch (TxnQItem.TxnType)
		{
			case ADMIN_CONFIRM:
				db_response_time = app_admin_confirm_array.db_response_time[TxnQItem.SlotID];
				break;
			case ADMIN_REQUEST:
				db_response_time = app_admin_request_array.db_response_time[TxnQItem.SlotID];
				break;
			case BEST_SELLERS:
				db_response_time = app_best_sellers_array.db_response_time[TxnQItem.SlotID];
				break;
			case BUY_CONFIRM:
				db_response_time = app_buy_confirm_array.db_response_time[TxnQItem.SlotID];
				break;
			case BUY_REQUEST:
				db_response_time = app_buy_request_array.db_response_time[TxnQItem.SlotID];
				break;
			case HOME:
				db_response_time = app_home_array.db_response_time[TxnQItem.SlotID];
				break;
			case NEW_PRODUCTS:
				db_response_time = app_new_products_array.db_response_time[TxnQItem.SlotID];
				break;
			case ORDER_DISPLAY:
				db_response_time = app_order_display_array.db_response_time[TxnQItem.SlotID];
				break;
			case ORDER_INQUIRY:
				db_response_time = app_order_inquiry_array.db_response_time[TxnQItem.SlotID];
				break;
			case PRODUCT_DETAIL:
				db_response_time = app_product_detail_array.db_response_time[TxnQItem.SlotID];
				break;
			case SEARCH_REQUEST:
				db_response_time = app_search_request_array.db_response_time[TxnQItem.SlotID];
				break;
			case SEARCH_RESULTS:
				db_response_time = app_search_results_array.db_response_time[TxnQItem.SlotID];
				break;
			case SHOPPING_CART:
				db_response_time = app_shopping_cart_array.db_response_time[TxnQItem.SlotID];
				break;
		}
		pthread_mutex_lock(&time_log_mutex);
		fprintf(timefp, "%s, total %f, db %f, server_db_time %f\n",
			interaction_short_name[TxnQItem.TxnType], 
			server_response_time, db_response_time, server_db_time);
		fflush(timefp);
		pthread_mutex_unlock(&time_log_mutex);
#endif
		if(send_transaction_packet(workersock, TxnQItem) != W_OK) 
		{
			LOG_ERROR_MESSAGE("send_transaction_packet failed");
			close(workersock);
			pthread_exit(NULL);
		}
	}
	close(workersock);
	return NULL;
}
