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
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include "app_threadpool.h"
#include "app_txn_queue.h"
#include "app_txn_array.h"
#include "common.h"
#include "app_interaction.h"
#include <odbc_interaction_admin_confirm.h>
#include <odbc_interaction_admin_request.h>
#include <odbc_interaction_best_sellers.h>
#include <odbc_interaction_buy_confirm.h>
#include <odbc_interaction_buy_request.h>
#include <odbc_interaction_home.h>
#include <odbc_interaction_new_products.h>
#include <odbc_interaction_order_display.h>
#include <odbc_interaction_order_inquiry.h>
#include <odbc_interaction_product_detail.h>
#include <odbc_interaction_shopping_cart.h>
#include <odbc_interaction_search_results.h>
#include <sql.h>
#include <sqlext.h>

/*mutex to control access to the queue*/
extern pthread_mutex_t queue_mutex;

/*semaphore to wait in DoTxn thread, each time a queue item is
  added to the queue, the semaphore must be released once
*/
extern sem_t TxnQSem;

/*the transaction queue*/
extern struct Queue TxnQ;

/*the txn input output array*/
extern struct app_txn_array app_admin_confirm_array;
extern struct app_txn_array app_admin_request_array;
extern struct app_txn_array app_best_sellers_array;
extern struct app_txn_array app_buy_confirm_array;
extern struct app_txn_array app_buy_request_array;
extern struct app_txn_array app_home_array;
extern struct app_txn_array app_new_products_array;
extern struct app_txn_array app_order_display_array;
extern struct app_txn_array app_order_inquiry_array;
extern struct app_txn_array app_product_detail_array;
extern struct app_txn_array app_search_request_array;
extern struct app_txn_array app_search_results_array;
extern struct app_txn_array app_shopping_cart_array;

extern pthread_mutex_t *queue_entry_mutex;
extern struct timeval txn_start_time;
int init_thread_pool(int PoolThreads, int TxnQSize, char *sname, char *uname, char *auth)
{
	int i;
	pthread_t ThreadID;
        struct timeval st, et;
        double time_diff;

	//create semaphore with initial value 0, and local to current process
	if (sem_init(&TxnQSem, 0, 0) == -1) return FALSE;
	//initialize mutex
	pthread_mutex_init(&queue_mutex, NULL);
	queue_entry_mutex=(pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)*TxnQSize);
	for (i=0; i<TxnQSize; i++)
		pthread_mutex_init(&queue_entry_mutex[i], NULL);

#ifndef _SIMDB
	odbc_init(sname, uname, auth);
#endif
	//create pool threads
	for (i=0; i<PoolThreads; i++)
	{
		if (pthread_create (&ThreadID, NULL, DoTxn, NULL) != 0)
		{
			LOG_ERROR_MESSAGE("error creating threadpool thread\n");
			return FALSE;
		}
	}
        if (gettimeofday(&st, NULL)==-1)
                perror("gettimeofday failed");
        sleep(2);
        if (gettimeofday(&et, NULL)==-1)
                perror("gettimeofday failed");
        time_diff=(et.tv_sec-st.tv_sec)+(et.tv_usec-st.tv_usec)/1000000.00;
        printf("elapsed tiem is %f\n", time_diff);
	return TRUE;
}

void *DoTxn(void *fd)
{
	int rc;
	struct QItem TxnQItem;
	int QIndex;
	int i;
#ifdef GET_TIME
        struct timeval txn_start_time, txn_end_time;
#endif

#ifndef _SIMDB
	struct odbc_context_t odbcc;
	/*connect to database */
	rc = odbc_connect(&odbcc);
	if (rc == W_ERROR)
	{
		LOG_ERROR_MESSAGE("odbc_connect error\n");
		pthread_exit(NULL);
	}
#endif
	//wait on the TxnQSem. Its value is positive when the queue is not
	//empty, sem_wait returns. If the queue is empty, block until a job is
	//enqueued.
#ifdef DEBUG
	DEBUGMSG("thread_id%ld: ThreadPool thread started, connect to database", pthread_self());
#endif

	while (1)
	{
		sem_wait(&TxnQSem);
#ifdef DEBUG
		DEBUGMSG("thread_id%ld: semaphore raised", pthread_self());
#endif
		/*lock the mutex of the TxnQ*/
		pthread_mutex_lock(&queue_mutex);
		if ((QIndex=dequeue(&TxnQItem, &TxnQ))==-1)
		{
			LOG_ERROR_MESSAGE("TxnQ dequeue error");
			pthread_exit(NULL);
		}
		pthread_mutex_unlock(&queue_mutex);
	
#ifdef DEBUG
		DEBUGMSG("thread_id%ld: QItem type %d, slot %d", pthread_self(), TxnQItem.TxnType, TxnQItem.SlotID);
#endif
		switch (TxnQItem.TxnType)
		{
		case ADMIN_CONFIRM:
#ifdef DEBUG
			DEBUGMSG("thread_id%ld: Txn AdminConfirm, i_id %lld, i_newimage %lld, i_newthumbnail %lld, i_newcost %f", pthread_self(),
				app_admin_confirm_array.odbc_data_array[TxnQItem.SlotID].admin_confirm_odbc_data.eb.i_id,
				app_admin_confirm_array.odbc_data_array[TxnQItem.SlotID].admin_confirm_odbc_data.eb.i_image,
				app_admin_confirm_array.odbc_data_array[TxnQItem.SlotID].admin_confirm_odbc_data.eb.i_thumbnail,
				app_admin_confirm_array.odbc_data_array[TxnQItem.SlotID].admin_confirm_odbc_data.eb.i_cost);
#endif
#ifdef _SIMDB
			sprintf(app_admin_confirm_array.odbc_data_array[TxnQItem.SlotID].admin_confirm_odbc_data.eb.i_title, "%s", "I_Title");
			sprintf(app_admin_confirm_array.odbc_data_array[TxnQItem.SlotID].admin_confirm_odbc_data.eb.a_fname, "%s", "A_FNAME");
			sprintf(app_admin_confirm_array.odbc_data_array[TxnQItem.SlotID].admin_confirm_odbc_data.eb.a_lname, "%s", "A_LNAME");
			sprintf(app_admin_confirm_array.odbc_data_array[TxnQItem.SlotID].admin_confirm_odbc_data.eb.i_subject, "%s", "I_SUBJECET");
			sprintf(app_admin_confirm_array.odbc_data_array[TxnQItem.SlotID].admin_confirm_odbc_data.eb.i_desc, "%s", "I_DESCRIBTION");
			app_admin_confirm_array.odbc_data_array[TxnQItem.SlotID].admin_confirm_odbc_data.eb.i_srp=99.99;
			sprintf(app_admin_confirm_array.odbc_data_array[TxnQItem.SlotID].admin_confirm_odbc_data.eb.i_backing, "%s", "PAPER");
			app_admin_confirm_array.odbc_data_array[TxnQItem.SlotID].admin_confirm_odbc_data.eb.i_page = 200;
			sprintf(app_admin_confirm_array.odbc_data_array[TxnQItem.SlotID].admin_confirm_odbc_data.eb.i_publisher, "%s", "Addison");
			sprintf(app_admin_confirm_array.odbc_data_array[TxnQItem.SlotID].admin_confirm_odbc_data.eb.i_pub_date, "%s", "01/24/2002");
			sprintf(app_admin_confirm_array.odbc_data_array[TxnQItem.SlotID].admin_confirm_odbc_data.eb.i_dimensions, "%s", "2x3x4");
			sprintf(app_admin_confirm_array.odbc_data_array[TxnQItem.SlotID].admin_confirm_odbc_data.eb.i_isbn, "%s", "0-201-30821-5");
#else
#ifdef GET_TIME
        		if (gettimeofday(&txn_start_time, NULL)==-1)
				LOG_ERROR_MESSAGE("gettimeofday failed");
#endif
			rc = execute_admin_confirm(&odbcc, &app_admin_confirm_array.odbc_data_array[TxnQItem.SlotID]);
			if (rc == W_ERROR)
			{
				LOG_ERROR_MESSAGE("execute_admin_confirm returned error");
			}
#ifdef GET_TIME
        		if (gettimeofday(&txn_end_time, NULL)==-1)
				LOG_ERROR_MESSAGE("gettimeofday failed");
			app_home_array.db_response_time[TxnQItem.SlotID]=time_diff(txn_start_time, txn_end_time);
#endif
#endif
			pthread_mutex_unlock(&queue_entry_mutex[QIndex]);
			//-- kill(TxnQItem.pid, SIGUSR1);
			break;
		case ADMIN_REQUEST:
#ifdef DEBUG
			DEBUGMSG("thread_id%ld: Txn AdminRequest, i_id %lld", pthread_self(),
				app_admin_request_array.odbc_data_array[TxnQItem.SlotID].admin_request_odbc_data.eb.i_id);
#endif
#ifdef _SIMDB
			app_admin_request_array.odbc_data_array[TxnQItem.SlotID].admin_request_odbc_data.eb.i_srp=199.99;
			app_admin_request_array.odbc_data_array[TxnQItem.SlotID].admin_request_odbc_data.eb.i_cost=99.99;
			sprintf(app_admin_request_array.odbc_data_array[TxnQItem.SlotID].admin_request_odbc_data.eb.i_title, "%s", "I_Title");
			app_admin_request_array.odbc_data_array[TxnQItem.SlotID].admin_request_odbc_data.eb.i_image=11;
			app_admin_request_array.odbc_data_array[TxnQItem.SlotID].admin_request_odbc_data.eb.i_thumbnail=11;
			sprintf(app_admin_request_array.odbc_data_array[TxnQItem.SlotID].admin_request_odbc_data.eb.a_fname, "%s", "A_FNAME");
			sprintf(app_admin_request_array.odbc_data_array[TxnQItem.SlotID].admin_request_odbc_data.eb.a_lname, "%s", "A_LNAME");
#else
#ifdef GET_TIME
        		if (gettimeofday(&txn_start_time, NULL)==-1)
				LOG_ERROR_MESSAGE("gettimeofday failed");
#endif
			rc = execute_admin_request(&odbcc, &app_admin_request_array.odbc_data_array[TxnQItem.SlotID]);
			if (rc == W_ERROR)
			{
				LOG_ERROR_MESSAGE("execute_admin_request returned error");
			}
#ifdef GET_TIME
        		if (gettimeofday(&txn_end_time, NULL)==-1)
				LOG_ERROR_MESSAGE("gettimeofday failed");
			app_admin_request_array.db_response_time[TxnQItem.SlotID]=time_diff(txn_start_time, txn_end_time);
#endif
#endif
			pthread_mutex_unlock(&queue_entry_mutex[QIndex]);
			//-- kill(TxnQItem.pid, SIGUSR1);
			break;
		case SEARCH_REQUEST:
#ifdef DEBUG
			DEBUGMSG("thread_id%ld: Txn SearchRequest", pthread_self()); 
#endif
#ifdef _SIMDB
			fill_promo_data(&app_search_request_array.odbc_data_array[TxnQItem.SlotID].search_request_odbc_data.eb.pp_data);
#else
#ifdef GET_TIME
        		if (gettimeofday(&txn_start_time, NULL)==-1)
				LOG_ERROR_MESSAGE("gettimeofday failed");
#endif
			rc = execute_search_request(&odbcc, &app_search_request_array.odbc_data_array[TxnQItem.SlotID]);
			if (rc == W_ERROR)
			{
				LOG_ERROR_MESSAGE("execute_search_results returned error");
			}
#ifdef GET_TIME
        		if (gettimeofday(&txn_end_time, NULL)==-1)
				LOG_ERROR_MESSAGE("gettimeofday failed");
			app_search_request_array.db_response_time[TxnQItem.SlotID]=time_diff(txn_start_time, txn_end_time);
#endif
#endif
			pthread_mutex_unlock(&queue_entry_mutex[QIndex]);
			//--kill(TxnQItem.pid, SIGUSR1);
			break;
		case SEARCH_RESULTS:
#ifdef DEBUG
			DEBUGMSG("thread_id%ld: Txn SearchResults, search_type %d, subject %s", pthread_self(),
				app_search_results_array.odbc_data_array[TxnQItem.SlotID].search_results_odbc_data.eb.search_type, 
				app_search_results_array.odbc_data_array[TxnQItem.SlotID].search_results_odbc_data.eb.search_string);
#endif
#ifdef _SIMDB
			app_search_results_array.odbc_data_array[TxnQItem.SlotID].search_results_odbc_data.eb.items=3;
			for (i=0; i<3; i++)
			{
				app_search_results_array.odbc_data_array[TxnQItem.SlotID].search_results_odbc_data.eb.results_data[i].i_id=1;
				sprintf(app_search_results_array.odbc_data_array[TxnQItem.SlotID].search_results_odbc_data.eb.results_data[i].a_fname, "%s", "A_FNAME");
				sprintf(app_search_results_array.odbc_data_array[TxnQItem.SlotID].search_results_odbc_data.eb.results_data[i].a_lname, "%s", "A_LNAME");
				sprintf(app_search_results_array.odbc_data_array[TxnQItem.SlotID].search_results_odbc_data.eb.results_data[i].i_title, "%s", "TITLE");
			}
			fill_promo_data(&app_search_results_array.odbc_data_array[TxnQItem.SlotID].search_results_odbc_data.eb.pp_data);
#else
#ifdef GET_TIME
        		if (gettimeofday(&txn_start_time, NULL)==-1)
				LOG_ERROR_MESSAGE("gettimeofday failed");
#endif
			rc = execute_search_results(&odbcc, &app_search_results_array.odbc_data_array[TxnQItem.SlotID]);
			if (rc == W_ERROR)
			{
				LOG_ERROR_MESSAGE("execute_search_results returned error");
			}
#ifdef GET_TIME
        		if (gettimeofday(&txn_end_time, NULL)==-1)
				LOG_ERROR_MESSAGE("gettimeofday failed");
			app_search_results_array.db_response_time[TxnQItem.SlotID]=time_diff(txn_start_time, txn_end_time);
#endif
#endif
			pthread_mutex_unlock(&queue_entry_mutex[QIndex]);
			//--kill(TxnQItem.pid, SIGUSR1);
			break;
		case BEST_SELLERS:
#ifdef DEBUG
			DEBUGMSG("thread_id%ld: Txn BestSeller, subject %s", pthread_self(),
				app_best_sellers_array.odbc_data_array[TxnQItem.SlotID].best_sellers_odbc_data.eb.i_subject);
#endif
#ifdef _SIMDB
			app_best_sellers_array.odbc_data_array[TxnQItem.SlotID].best_sellers_odbc_data.eb.items=3;
			for (i=0; i<3; i++)
			{
				app_best_sellers_array.odbc_data_array[TxnQItem.SlotID].best_sellers_odbc_data.eb.results_data[i].i_id=1;
				sprintf(app_best_sellers_array.odbc_data_array[TxnQItem.SlotID].best_sellers_odbc_data.eb.results_data[i].a_fname, "%s", "A_FNAME");
				sprintf(app_best_sellers_array.odbc_data_array[TxnQItem.SlotID].best_sellers_odbc_data.eb.results_data[i].a_lname, "%s", "A_LNAME");
				sprintf(app_best_sellers_array.odbc_data_array[TxnQItem.SlotID].best_sellers_odbc_data.eb.results_data[i].i_title, "%s", "TITLE");
			}
			fill_promo_data(&app_best_sellers_array.odbc_data_array[TxnQItem.SlotID].best_sellers_odbc_data.eb.pp_data);
#else
#ifdef GET_TIME
        		if (gettimeofday(&txn_start_time, NULL)==-1)
				LOG_ERROR_MESSAGE("gettimeofday failed");
#endif
			rc = execute_best_sellers(&odbcc, &app_best_sellers_array.odbc_data_array[TxnQItem.SlotID]);
			if (rc == W_ERROR)
			{
				LOG_ERROR_MESSAGE("execute_best_sellers returned error");
			}
#ifdef GET_TIME
        		if (gettimeofday(&txn_end_time, NULL)==-1)
				LOG_ERROR_MESSAGE("gettimeofday failed");
			app_best_sellers_array.db_response_time[TxnQItem.SlotID]=time_diff(txn_start_time, txn_end_time);
#endif
#endif
			pthread_mutex_unlock(&queue_entry_mutex[QIndex]);
			//--kill(TxnQItem.pid, SIGUSR1);
			break;
		case NEW_PRODUCTS:
#ifdef DEBUG
			DEBUGMSG("thread_id%ld: Txn NewProducts, subject %s", pthread_self(),
				app_new_products_array.odbc_data_array[TxnQItem.SlotID].new_products_odbc_data.eb.i_subject);
#endif
#ifdef _SIMDB
			app_new_products_array.odbc_data_array[TxnQItem.SlotID].new_products_odbc_data.eb.items=3;
			for (i=0; i<3; i++)
			{
				app_new_products_array.odbc_data_array[TxnQItem.SlotID].new_products_odbc_data.eb.results_data[i].i_id=1;
				sprintf(app_new_products_array.odbc_data_array[TxnQItem.SlotID].new_products_odbc_data.eb.results_data[i].a_fname, "%s", "A_FNAME");
				sprintf(app_new_products_array.odbc_data_array[TxnQItem.SlotID].new_products_odbc_data.eb.results_data[i].a_lname, "%s", "A_LNAME");
				sprintf(app_new_products_array.odbc_data_array[TxnQItem.SlotID].new_products_odbc_data.eb.results_data[i].i_title, "%s", "TITLE");
			}
			fill_promo_data(&app_new_products_array.odbc_data_array[TxnQItem.SlotID].new_products_odbc_data.eb.pp_data);
#else
#ifdef GET_TIME
        		if (gettimeofday(&txn_start_time, NULL)==-1)
				LOG_ERROR_MESSAGE("gettimeofday failed");
#endif
			rc = execute_new_products(&odbcc, &app_new_products_array.odbc_data_array[TxnQItem.SlotID]);
			if (rc == W_ERROR)
			{
				LOG_ERROR_MESSAGE("execute_new_products returned error");
			}
#ifdef GET_TIME
        		if (gettimeofday(&txn_end_time, NULL)==-1)
				LOG_ERROR_MESSAGE("gettimeofday failed");
			app_new_products_array.db_response_time[TxnQItem.SlotID]=time_diff(txn_start_time, txn_end_time);
#endif
#endif
			pthread_mutex_unlock(&queue_entry_mutex[QIndex]);
			//--kill(TxnQItem.pid, SIGUSR1);
			break;
		case BUY_CONFIRM:
#ifdef DEBUG
			DEBUGMSG("thread_id%ld: Txn BuyConfirm, sc_id %lld, c_id %lld, cx_type %s, cx_num %s, cx_name %s, cx_exp %s, street1 %s, street2 %s, city %s, state %s, zip %s, country %s", pthread_self(),
					app_buy_confirm_array.odbc_data_array[TxnQItem.SlotID].buy_confirm_odbc_data.eb.sc_id,
					app_buy_confirm_array.odbc_data_array[TxnQItem.SlotID].buy_confirm_odbc_data.eb.c_id,
					app_buy_confirm_array.odbc_data_array[TxnQItem.SlotID].buy_confirm_odbc_data.eb.cx_type,
					app_buy_confirm_array.odbc_data_array[TxnQItem.SlotID].buy_confirm_odbc_data.eb.cx_num,
					app_buy_confirm_array.odbc_data_array[TxnQItem.SlotID].buy_confirm_odbc_data.eb.cx_name,
					app_buy_confirm_array.odbc_data_array[TxnQItem.SlotID].buy_confirm_odbc_data.eb.cx_expiry,
					app_buy_confirm_array.odbc_data_array[TxnQItem.SlotID].buy_confirm_odbc_data.eb.shipping.addr_street1,
					app_buy_confirm_array.odbc_data_array[TxnQItem.SlotID].buy_confirm_odbc_data.eb.shipping.addr_street2,
					app_buy_confirm_array.odbc_data_array[TxnQItem.SlotID].buy_confirm_odbc_data.eb.shipping.addr_city,
					app_buy_confirm_array.odbc_data_array[TxnQItem.SlotID].buy_confirm_odbc_data.eb.shipping.addr_state,
					app_buy_confirm_array.odbc_data_array[TxnQItem.SlotID].buy_confirm_odbc_data.eb.shipping.addr_zip,
					app_buy_confirm_array.odbc_data_array[TxnQItem.SlotID].buy_confirm_odbc_data.eb.shipping.co_name);
#endif
#ifdef _SIMDB
			app_buy_confirm_array.odbc_data_array[TxnQItem.SlotID].buy_confirm_odbc_data.eb.o_id=1;
			app_buy_confirm_array.odbc_data_array[TxnQItem.SlotID].buy_confirm_odbc_data.eb.sc_size=3;
			//write 3 items
			for (i=0; i<app_buy_confirm_array.odbc_data_array[TxnQItem.SlotID].buy_confirm_odbc_data.eb.sc_size; i++)
			{
				app_buy_confirm_array.odbc_data_array[TxnQItem.SlotID].buy_confirm_odbc_data.eb.scl_data[i].scl_i_id=i+1;
				app_buy_confirm_array.odbc_data_array[TxnQItem.SlotID].buy_confirm_odbc_data.eb.scl_data[i].scl_qty=i+2;
				app_buy_confirm_array.odbc_data_array[TxnQItem.SlotID].buy_confirm_odbc_data.eb.scl_data[i].scl_cost=99.99;
				app_buy_confirm_array.odbc_data_array[TxnQItem.SlotID].buy_confirm_odbc_data.eb.scl_data[i].scl_srp=199.99;
				sprintf(app_buy_confirm_array.odbc_data_array[TxnQItem.SlotID].buy_confirm_odbc_data.eb.scl_data[i].i_title, "%s", "TITLE");
				sprintf(app_buy_confirm_array.odbc_data_array[TxnQItem.SlotID].buy_confirm_odbc_data.eb.scl_data[i].i_backing, "%s", "PAPER");
			}
			app_buy_confirm_array.odbc_data_array[TxnQItem.SlotID].buy_confirm_odbc_data.eb.c_discount=0.4;
			app_buy_confirm_array.odbc_data_array[TxnQItem.SlotID].buy_confirm_odbc_data.eb.sc_sub_total=20.50;
			app_buy_confirm_array.odbc_data_array[TxnQItem.SlotID].buy_confirm_odbc_data.eb.sc_tax=8.50;
			app_buy_confirm_array.odbc_data_array[TxnQItem.SlotID].buy_confirm_odbc_data.eb.sc_ship_cost=8.0;
			app_buy_confirm_array.odbc_data_array[TxnQItem.SlotID].buy_confirm_odbc_data.eb.sc_total=40.20;
#else
#ifdef GET_TIME
        		if (gettimeofday(&txn_start_time, NULL)==-1)
				LOG_ERROR_MESSAGE("gettimeofday failed");
#endif
			rc = execute_buy_confirm(&odbcc, &app_buy_confirm_array.odbc_data_array[TxnQItem.SlotID]);
			if (rc == W_ERROR)
			{
				LOG_ERROR_MESSAGE("execute_buy_confirm returned error");
			}
#ifdef GET_TIME
        		if (gettimeofday(&txn_end_time, NULL)==-1)
				LOG_ERROR_MESSAGE("gettimeofday failed");
			app_buy_confirm_array.db_response_time[TxnQItem.SlotID]=time_diff(txn_start_time, txn_end_time);
#endif
#endif
			pthread_mutex_unlock(&queue_entry_mutex[QIndex]);
			break;
		case BUY_REQUEST:
#ifdef DEBUG
			DEBUGMSG("thread_id%ld: Txn BuyRequest,return flag %d, uname %s, passwd %s, sc_id %lld", pthread_self(),
					app_buy_request_array.odbc_data_array[TxnQItem.SlotID].buy_request_odbc_data.eb.returning_flag,
					app_buy_request_array.odbc_data_array[TxnQItem.SlotID].buy_request_odbc_data.eb.c_uname, 
					app_buy_request_array.odbc_data_array[TxnQItem.SlotID].buy_request_odbc_data.eb.c_passwd,
					app_buy_request_array.odbc_data_array[TxnQItem.SlotID].buy_request_odbc_data.eb.sc_id);
			if (app_buy_request_array.odbc_data_array[TxnQItem.SlotID].buy_request_odbc_data.eb.returning_flag==FALSE)
				DEBUGMSG("thread_id%ld: c_fname %s, c_lname %s, c_phone %s, c_email %s, c_birthday %s, c_data %s, addr_street1 %s, addr_street2 %s, addr_city %s, addr_state %s, addr_zip %s, addr_country %s", pthread_self(),
						app_buy_request_array.odbc_data_array[TxnQItem.SlotID].buy_request_odbc_data.eb.c_fname,
						app_buy_request_array.odbc_data_array[TxnQItem.SlotID].buy_request_odbc_data.eb.c_lname,
						app_buy_request_array.odbc_data_array[TxnQItem.SlotID].buy_request_odbc_data.eb.c_phone,
						app_buy_request_array.odbc_data_array[TxnQItem.SlotID].buy_request_odbc_data.eb.c_email,
						app_buy_request_array.odbc_data_array[TxnQItem.SlotID].buy_request_odbc_data.eb.c_birthdate,
						app_buy_request_array.odbc_data_array[TxnQItem.SlotID].buy_request_odbc_data.eb.c_data,
						app_buy_request_array.odbc_data_array[TxnQItem.SlotID].buy_request_odbc_data.eb.address.addr_street1,
						app_buy_request_array.odbc_data_array[TxnQItem.SlotID].buy_request_odbc_data.eb.address.addr_street2,
						app_buy_request_array.odbc_data_array[TxnQItem.SlotID].buy_request_odbc_data.eb.address.addr_city,
						app_buy_request_array.odbc_data_array[TxnQItem.SlotID].buy_request_odbc_data.eb.address.addr_state,
						app_buy_request_array.odbc_data_array[TxnQItem.SlotID].buy_request_odbc_data.eb.address.addr_zip,
						app_buy_request_array.odbc_data_array[TxnQItem.SlotID].buy_request_odbc_data.eb.address.co_name);
#endif
#ifdef _SIMDB
			if (app_buy_request_array.odbc_data_array[TxnQItem.SlotID].buy_request_odbc_data.eb.returning_flag==TRUE)
			{
				sprintf(app_buy_request_array.odbc_data_array[TxnQItem.SlotID].buy_request_odbc_data.eb.c_fname, "%s", "CFNAME");
				sprintf(app_buy_request_array.odbc_data_array[TxnQItem.SlotID].buy_request_odbc_data.eb.c_lname, "%s", "CLNAME");
				sprintf(app_buy_request_array.odbc_data_array[TxnQItem.SlotID].buy_request_odbc_data.eb.c_phone, "%s", "phone");
				sprintf(app_buy_request_array.odbc_data_array[TxnQItem.SlotID].buy_request_odbc_data.eb.c_email, "%s", "email");
				sprintf(app_buy_request_array.odbc_data_array[TxnQItem.SlotID].buy_request_odbc_data.eb.c_birthdate, "%s", "01/01/2002");
				sprintf(app_buy_request_array.odbc_data_array[TxnQItem.SlotID].buy_request_odbc_data.eb.c_data, "%s", "data");
				sprintf(app_buy_request_array.odbc_data_array[TxnQItem.SlotID].buy_request_odbc_data.eb.address.addr_street1, "%s", "Street1");
				sprintf(app_buy_request_array.odbc_data_array[TxnQItem.SlotID].buy_request_odbc_data.eb.address.addr_street2, "%s", "Street2");
				sprintf(app_buy_request_array.odbc_data_array[TxnQItem.SlotID].buy_request_odbc_data.eb.address.addr_city, "%s", "City");
				sprintf(app_buy_request_array.odbc_data_array[TxnQItem.SlotID].buy_request_odbc_data.eb.address.addr_state, "%s", "State");
				sprintf(app_buy_request_array.odbc_data_array[TxnQItem.SlotID].buy_request_odbc_data.eb.address.addr_zip, "%s", "zip");
				sprintf(app_buy_request_array.odbc_data_array[TxnQItem.SlotID].buy_request_odbc_data.eb.address.co_name, "%s", "country");
			} 
			app_buy_request_array.odbc_data_array[TxnQItem.SlotID].buy_request_odbc_data.eb.c_id=1;
			app_buy_request_array.odbc_data_array[TxnQItem.SlotID].buy_request_odbc_data.eb.sc_size=3;
			//write 3 items
			for (i=0; i<app_buy_request_array.odbc_data_array[TxnQItem.SlotID].buy_request_odbc_data.eb.sc_size; i++)
			{
				app_buy_request_array.odbc_data_array[TxnQItem.SlotID].buy_request_odbc_data.eb.scl_data[i].scl_i_id=i+1;
				app_buy_request_array.odbc_data_array[TxnQItem.SlotID].buy_request_odbc_data.eb.scl_data[i].scl_qty=i+2;
				app_buy_request_array.odbc_data_array[TxnQItem.SlotID].buy_request_odbc_data.eb.scl_data[i].scl_cost=99.99;
				app_buy_request_array.odbc_data_array[TxnQItem.SlotID].buy_request_odbc_data.eb.scl_data[i].scl_srp=199.99;
				sprintf(app_buy_request_array.odbc_data_array[TxnQItem.SlotID].buy_request_odbc_data.eb.scl_data[i].i_title, "%s", "TITLE");
				sprintf(app_buy_request_array.odbc_data_array[TxnQItem.SlotID].buy_request_odbc_data.eb.scl_data[i].i_backing, "%s", "PAPER");
			}
			app_buy_request_array.odbc_data_array[TxnQItem.SlotID].buy_request_odbc_data.eb.c_discount=0.4;
			app_buy_request_array.odbc_data_array[TxnQItem.SlotID].buy_request_odbc_data.eb.sc_sub_total=20.50;
			app_buy_request_array.odbc_data_array[TxnQItem.SlotID].buy_request_odbc_data.eb.sc_tax=8.50;
			app_buy_request_array.odbc_data_array[TxnQItem.SlotID].buy_request_odbc_data.eb.sc_ship_cost=8.0;
			app_buy_request_array.odbc_data_array[TxnQItem.SlotID].buy_request_odbc_data.eb.sc_total=40.20;
#else
#ifdef GET_TIME
        		if (gettimeofday(&txn_start_time, NULL)==-1)
				LOG_ERROR_MESSAGE("gettimeofday failed");
#endif
			rc = execute_buy_request(&odbcc, &app_buy_request_array.odbc_data_array[TxnQItem.SlotID]);
			if (rc == W_ERROR)
			{
				LOG_ERROR_MESSAGE("execute_buy_request returned error");
			}
#ifdef GET_TIME
        		if (gettimeofday(&txn_end_time, NULL)==-1)
				LOG_ERROR_MESSAGE("gettimeofday failed");
			app_buy_request_array.db_response_time[TxnQItem.SlotID]=time_diff(txn_start_time, txn_end_time);
#endif
#endif
			pthread_mutex_unlock(&queue_entry_mutex[QIndex]);
			break;
		case HOME:
			//do transaction
#ifdef DEBUG
			DEBUGMSG("thread_id%ld: Txn Home, c_id %lld", pthread_self(),
				app_home_array.odbc_data_array[TxnQItem.SlotID].home_odbc_data.eb.c_id);
#endif
#ifdef _SIMDB
			strcpy(app_home_array.odbc_data_array[TxnQItem.SlotID].home_odbc_data.eb.c_fname, "FNAME");
			strcpy(app_home_array.odbc_data_array[TxnQItem.SlotID].home_odbc_data.eb.c_lname, "LNAME");
			fill_promo_data(&app_home_array.odbc_data_array[TxnQItem.SlotID].home_odbc_data.eb.pp_data);
#else
#ifdef GET_TIME
        		if (gettimeofday(&txn_start_time, NULL)==-1)
				LOG_ERROR_MESSAGE("gettimeofday failed");
#endif
			rc = execute_home(&odbcc, &app_home_array.odbc_data_array[TxnQItem.SlotID]);
			if (rc == W_ERROR)
			{
				LOG_ERROR_MESSAGE("execute_home returned error");
			}
#ifdef GET_TIME
        		if (gettimeofday(&txn_end_time, NULL)==-1)
				LOG_ERROR_MESSAGE("gettimeofday failed");
			app_home_array.db_response_time[TxnQItem.SlotID]=time_diff(txn_start_time, txn_end_time);
#endif
#endif
			pthread_mutex_unlock(&queue_entry_mutex[QIndex]);
			//--kill(TxnQItem.pid, SIGUSR1);
			break;
		case ORDER_DISPLAY:
#ifdef DEBUG
			DEBUGMSG("thread_id%ld: Txn OrderDisplay, c_uname %s, c_passwd %s", pthread_self(),
				app_order_display_array.odbc_data_array[TxnQItem.SlotID].order_display_odbc_data.eb.c_uname, 
				app_order_display_array.odbc_data_array[TxnQItem.SlotID].order_display_odbc_data.eb.c_passwd);
#endif
#ifdef _SIMDB
			app_order_display_array.odbc_data_array[TxnQItem.SlotID].order_display_odbc_data.eb.o_id=1;
			sprintf(app_order_display_array.odbc_data_array[TxnQItem.SlotID].order_display_odbc_data.eb.c_fname, "%s", "CFNAME");
			sprintf(app_order_display_array.odbc_data_array[TxnQItem.SlotID].order_display_odbc_data.eb.c_lname, "%s", "CLNAME");
			sprintf(app_order_display_array.odbc_data_array[TxnQItem.SlotID].order_display_odbc_data.eb.c_phone, "%s", "phone");
	 sprintf(app_order_display_array.odbc_data_array[TxnQItem.SlotID].order_display_odbc_data.eb.c_email, "%s", "email");
			sprintf(app_order_display_array.odbc_data_array[TxnQItem.SlotID].order_display_odbc_data.eb.o_date, "%s", "01-01-2002");
			app_order_display_array.odbc_data_array[TxnQItem.SlotID].order_display_odbc_data.eb.o_sub_total=100.20;
			app_order_display_array.odbc_data_array[TxnQItem.SlotID].order_display_odbc_data.eb.o_tax=20.20;
			app_order_display_array.odbc_data_array[TxnQItem.SlotID].order_display_odbc_data.eb.o_total=1200.20;
			sprintf(app_order_display_array.odbc_data_array[TxnQItem.SlotID].order_display_odbc_data.eb.o_ship_type, "%s", "Regular");
			sprintf(app_order_display_array.odbc_data_array[TxnQItem.SlotID].order_display_odbc_data.eb.o_ship_date, "%s", "01-02-2002");
			sprintf(app_order_display_array.odbc_data_array[TxnQItem.SlotID].order_display_odbc_data.eb.o_status, "%s", "shipped");
			sprintf(app_order_display_array.odbc_data_array[TxnQItem.SlotID].order_display_odbc_data.eb.billing.addr_street1, "%s", "Street1");
			sprintf(app_order_display_array.odbc_data_array[TxnQItem.SlotID].order_display_odbc_data.eb.billing.addr_street2, "%s", "Street2");
			sprintf(app_order_display_array.odbc_data_array[TxnQItem.SlotID].order_display_odbc_data.eb.billing.addr_city, "%s", "City");
			sprintf(app_order_display_array.odbc_data_array[TxnQItem.SlotID].order_display_odbc_data.eb.billing.addr_state, "%s", "State");
			sprintf(app_order_display_array.odbc_data_array[TxnQItem.SlotID].order_display_odbc_data.eb.billing.addr_zip, "%s", "zip");
			sprintf(app_order_display_array.odbc_data_array[TxnQItem.SlotID].order_display_odbc_data.eb.billing.co_name, "%s", "country");
			sprintf(app_order_display_array.odbc_data_array[TxnQItem.SlotID].order_display_odbc_data.eb.shipping.addr_street1, "%s", "Street1");
			sprintf(app_order_display_array.odbc_data_array[TxnQItem.SlotID].order_display_odbc_data.eb.shipping.addr_street2, "%s", "Street2");
			sprintf(app_order_display_array.odbc_data_array[TxnQItem.SlotID].order_display_odbc_data.eb.shipping.addr_city, "%s", "City");
			sprintf(app_order_display_array.odbc_data_array[TxnQItem.SlotID].order_display_odbc_data.eb.shipping.addr_state, "%s", "State");
			sprintf(app_order_display_array.odbc_data_array[TxnQItem.SlotID].order_display_odbc_data.eb.shipping.addr_zip, "%s", "zip");
			sprintf(app_order_display_array.odbc_data_array[TxnQItem.SlotID].order_display_odbc_data.eb.shipping.co_name, "%s", "country");
			app_order_display_array.odbc_data_array[TxnQItem.SlotID].order_display_odbc_data.eb.items=2;
			for (i=0; i< app_order_display_array.odbc_data_array[TxnQItem.SlotID].order_display_odbc_data.eb.items; i++)
			{
				 app_order_display_array.odbc_data_array[TxnQItem.SlotID].order_display_odbc_data.eb.odl_data[i].ol_i_id=i+1;
				 sprintf(app_order_display_array.odbc_data_array[TxnQItem.SlotID].order_display_odbc_data.eb.odl_data[i].i_title, "%s", "Title");
				 sprintf(app_order_display_array.odbc_data_array[TxnQItem.SlotID].order_display_odbc_data.eb.odl_data[i].i_publisher, "%s", "Publisher");
				 app_order_display_array.odbc_data_array[TxnQItem.SlotID].order_display_odbc_data.eb.odl_data[i].i_cost=99.99;
				 app_order_display_array.odbc_data_array[TxnQItem.SlotID].order_display_odbc_data.eb.odl_data[i].ol_qty=1;
				 app_order_display_array.odbc_data_array[TxnQItem.SlotID].order_display_odbc_data.eb.odl_data[i].ol_discount=0.12;
				 sprintf(app_order_display_array.odbc_data_array[TxnQItem.SlotID].order_display_odbc_data.eb.odl_data[i].ol_comment, "%s", "comment");
			 }
			 sprintf(app_order_display_array.odbc_data_array[TxnQItem.SlotID].order_display_odbc_data.eb.cx_type, "%s", "visa");
			 sprintf(app_order_display_array.odbc_data_array[TxnQItem.SlotID].order_display_odbc_data.eb.cx_auth_id, "%s", "idof923");
#else
#ifdef GET_TIME
        		if (gettimeofday(&txn_start_time, NULL)==-1)
				LOG_ERROR_MESSAGE("gettimeofday failed");
#endif
			rc = execute_order_display(&odbcc, &app_order_display_array.odbc_data_array[TxnQItem.SlotID]);
			if (rc == W_ERROR)
			{
				LOG_ERROR_MESSAGE("execute_order_display returned error");
			}
#ifdef GET_TIME
        		if (gettimeofday(&txn_end_time, NULL)==-1)
				LOG_ERROR_MESSAGE("gettimeofday failed");
			app_order_display_array.db_response_time[TxnQItem.SlotID]=time_diff(txn_start_time, txn_end_time);
#endif
#endif
			pthread_mutex_unlock(&queue_entry_mutex[QIndex]);
			break;
		case ORDER_INQUIRY:
#ifdef DEBUG
			DEBUGMSG("thread_id%ld: Txn OrderInquiry, C_ID %d", pthread_self(),
				app_order_inquiry_array.odbc_data_array[TxnQItem.SlotID].order_inquiry_odbc_data.eb.c_id);
#endif
#ifdef _SIMDB
			sprintf(app_order_inquiry_array.odbc_data_array[TxnQItem.SlotID].order_inquiry_odbc_data.eb.c_uname, "%s", "UNAME");
#else
#ifdef GET_TIME
        		if (gettimeofday(&txn_start_time, NULL)==-1)
				LOG_ERROR_MESSAGE("gettimeofday failed");
#endif
			rc = execute_order_inquiry(&odbcc, &app_order_inquiry_array.odbc_data_array[TxnQItem.SlotID]);
			if (rc == W_ERROR)
			{
				LOG_ERROR_MESSAGE("execute_order_inquiry returned error");
			}
#ifdef GET_TIME
        		if (gettimeofday(&txn_end_time, NULL)==-1)
				LOG_ERROR_MESSAGE("gettimeofday failed");
			app_order_inquiry_array.db_response_time[TxnQItem.SlotID]=time_diff(txn_start_time, txn_end_time);
#endif
#endif
			pthread_mutex_unlock(&queue_entry_mutex[QIndex]);
			break;
		case PRODUCT_DETAIL:
#ifdef DEBUG
			DEBUGMSG("thread_id%ld: Txn ProdDetail, i_id %lld", pthread_self(),
				app_product_detail_array.odbc_data_array[TxnQItem.SlotID].product_detail_odbc_data.eb.i_id);
#endif
#ifdef _SIMDB
			sprintf(app_product_detail_array.odbc_data_array[TxnQItem.SlotID].product_detail_odbc_data.eb.i_title, "%s", "I_Title");
			sprintf(app_product_detail_array.odbc_data_array[TxnQItem.SlotID].product_detail_odbc_data.eb.a_fname, "%s", "A_FNAME");
			sprintf(app_product_detail_array.odbc_data_array[TxnQItem.SlotID].product_detail_odbc_data.eb.a_lname, "%s", "A_LNAME");
			sprintf(app_product_detail_array.odbc_data_array[TxnQItem.SlotID].product_detail_odbc_data.eb.i_pub_date, "%s", "01/24/2002");
			sprintf(app_product_detail_array.odbc_data_array[TxnQItem.SlotID].product_detail_odbc_data.eb.i_publisher, "%s", "Addison");
			sprintf(app_product_detail_array.odbc_data_array[TxnQItem.SlotID].product_detail_odbc_data.eb.i_subject, "%s", "I_SUBJECET");
			sprintf(app_product_detail_array.odbc_data_array[TxnQItem.SlotID].product_detail_odbc_data.eb.i_desc, "%s", "I_DESCRIBTION");
			app_product_detail_array.odbc_data_array[TxnQItem.SlotID].product_detail_odbc_data.eb.i_image=1;
			app_product_detail_array.odbc_data_array[TxnQItem.SlotID].product_detail_odbc_data.eb.i_cost=99.99;
			app_product_detail_array.odbc_data_array[TxnQItem.SlotID].product_detail_odbc_data.eb.i_srp=99.99;
			sprintf(app_product_detail_array.odbc_data_array[TxnQItem.SlotID].product_detail_odbc_data.eb.i_avail, "%s", "Ava");
			sprintf(app_product_detail_array.odbc_data_array[TxnQItem.SlotID].product_detail_odbc_data.eb.i_isbn, "%s", "0-201-30821-5");
			app_product_detail_array.odbc_data_array[TxnQItem.SlotID].product_detail_odbc_data.eb.i_page = 200;
			sprintf(app_product_detail_array.odbc_data_array[TxnQItem.SlotID].product_detail_odbc_data.eb.i_backing, "%s", "PAPER");
			sprintf(app_product_detail_array.odbc_data_array[TxnQItem.SlotID].product_detail_odbc_data.eb.i_dimensions, "%s", "2x3x4");
#else
#ifdef GET_TIME
        		if (gettimeofday(&txn_start_time, NULL)==-1)
				LOG_ERROR_MESSAGE("gettimeofday failed");
#endif
			rc = execute_product_detail(&odbcc, &app_product_detail_array.odbc_data_array[TxnQItem.SlotID]);
			if (rc == W_ERROR)
			{
				LOG_ERROR_MESSAGE("execute_product_detail returned error");
			}
#ifdef GET_TIME
        		if (gettimeofday(&txn_end_time, NULL)==-1)
				LOG_ERROR_MESSAGE("gettimeofday failed");
			app_product_detail_array.db_response_time[TxnQItem.SlotID]=time_diff(txn_start_time, txn_end_time);
#endif
#endif
			pthread_mutex_unlock(&queue_entry_mutex[QIndex]);
			break;
		case SHOPPING_CART:
#ifdef DEBUG
			DEBUGMSG("thread_id%ld: Txn ShoppingCart: add_flag %d, c_id %lld", pthread_self(),
				app_shopping_cart_array.odbc_data_array[TxnQItem.SlotID].shopping_cart_odbc_data.eb.add_flag,
				app_shopping_cart_array.odbc_data_array[TxnQItem.SlotID].shopping_cart_odbc_data.eb.c_id);

/* if adding an item */
			if (app_shopping_cart_array.odbc_data_array[TxnQItem.SlotID].shopping_cart_odbc_data.eb.add_flag==TRUE)
				DEBUGMSG("thread_id%ld: sc_id %lld, i_id %lld", pthread_self(),
					app_shopping_cart_array.odbc_data_array[TxnQItem.SlotID].shopping_cart_odbc_data.eb.sc_id,
					app_shopping_cart_array.odbc_data_array[TxnQItem.SlotID].shopping_cart_odbc_data.eb.i_id);

/* if refreshing shopping cart*/
			if (app_shopping_cart_array.odbc_data_array[TxnQItem.SlotID].shopping_cart_odbc_data.eb.add_flag==FALSE && app_shopping_cart_array.odbc_data_array[TxnQItem.SlotID].shopping_cart_odbc_data.eb.sc_size > 0)
			{
				DEBUGMSG("thread_id%ld: sc_id %lld, sc_size %d", pthread_self(),
					app_shopping_cart_array.odbc_data_array[TxnQItem.SlotID].shopping_cart_odbc_data.eb.sc_id,
					app_shopping_cart_array.odbc_data_array[TxnQItem.SlotID].shopping_cart_odbc_data.eb.sc_size);
				for (i=0; i< app_shopping_cart_array.odbc_data_array[TxnQItem.SlotID].shopping_cart_odbc_data.eb.sc_size; i++)
				{
					DEBUGMSG("thread_id%ld: scl_i_id %lld, scl_qty %d", 
						pthread_self(),
						app_shopping_cart_array.odbc_data_array[TxnQItem.SlotID].shopping_cart_odbc_data.eb.sc_refresh[i].scl_i_id,
						app_shopping_cart_array.odbc_data_array[TxnQItem.SlotID].shopping_cart_odbc_data.eb.sc_refresh[i].scl_qty);
				}
					
			}
#endif
#ifdef _SIMDB
			app_shopping_cart_array.odbc_data_array[TxnQItem.SlotID].shopping_cart_odbc_data.eb.sc_id=1;
			app_shopping_cart_array.odbc_data_array[TxnQItem.SlotID].shopping_cart_odbc_data.eb.sc_size=3;
			for (i=0; i< app_shopping_cart_array.odbc_data_array[TxnQItem.SlotID].shopping_cart_odbc_data.eb.sc_size; i++)
			{
				app_shopping_cart_array.odbc_data_array[TxnQItem.SlotID].shopping_cart_odbc_data.eb.scl_data[i].scl_i_id=i+1;
				app_shopping_cart_array.odbc_data_array[TxnQItem.SlotID].shopping_cart_odbc_data.eb.scl_data[i].scl_qty=i+2;
				app_shopping_cart_array.odbc_data_array[TxnQItem.SlotID].shopping_cart_odbc_data.eb.scl_data[i].scl_cost=99.99;
				app_shopping_cart_array.odbc_data_array[TxnQItem.SlotID].shopping_cart_odbc_data.eb.scl_data[i].scl_srp=199.99;
				sprintf(app_shopping_cart_array.odbc_data_array[TxnQItem.SlotID].shopping_cart_odbc_data.eb.scl_data[i].i_title, "%s", "TITLE");
				sprintf(app_shopping_cart_array.odbc_data_array[TxnQItem.SlotID].shopping_cart_odbc_data.eb.scl_data[i].i_backing, "%s", "PAPER");
			}
			fill_promo_data(&app_shopping_cart_array.odbc_data_array[TxnQItem.SlotID].shopping_cart_odbc_data.eb.pp_data);
#else
#ifdef GET_TIME
        		if (gettimeofday(&txn_start_time, NULL)==-1)
				LOG_ERROR_MESSAGE("gettimeofday failed");
#endif
			rc = execute_shopping_cart(&odbcc, &app_shopping_cart_array.odbc_data_array[TxnQItem.SlotID]);
			if (rc == W_ERROR)
			{
				LOG_ERROR_MESSAGE("execute_shopping_cart returned error");
			}
#ifdef GET_TIME
        		if (gettimeofday(&txn_end_time, NULL)==-1)
				LOG_ERROR_MESSAGE("gettimeofday failed");
			app_shopping_cart_array.db_response_time[TxnQItem.SlotID]=time_diff(txn_start_time, txn_end_time);
#endif
#endif
#ifdef DEBUG
			DEBUGMSG("thread_id%ld: sc_id %lld", pthread_self(),
				app_shopping_cart_array.odbc_data_array[TxnQItem.SlotID].shopping_cart_odbc_data.eb.sc_id);
			
#endif
			pthread_mutex_unlock(&queue_entry_mutex[QIndex]);
			break;
		}
	}
#ifdef DEBUG
	DEBUGMSG("thread_id%ld: Terminated", pthread_self());
#endif
}

#ifdef _SIMDB
void fill_promo_data(struct promotional_processing_t *pp_data)
{
	int i;
	pp_data->i_id=1;
	for (i=0; i<PROMOTIONAL_ITEMS_MAX; i++)
	{
		pp_data->i_related[i]=(long long)i+1;
		pp_data->i_thumbnail[i]=(long long)i+6;
	}
}
#endif
