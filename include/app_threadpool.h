/* app_interface.h 
 * appServer interface for sending/receiving packet to/from eb
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2002 Mark Wong & Jenny Zhang &
 *                    Open Source Development Lab, Inc.
 *
 */
#ifndef _APP_THREADPOOL_H
#define _APP_THREADPOOL_H_
#include "odbc_interaction.h"
#include "app_txn_queue.h"

struct condition_bundle_t {
	int txn_done_flag;
	pthread_mutex_t condition_mutex;
	pthread_cond_t txn_done_cv;
};

int init_thread_pool(int PoolThreads, int TxnQSize, char *sname, char *uname, char *auth);
void *DoTxn(void *fd);
void set_txn_done_flag(struct Queue *txn_queue, int QIndex);
#ifdef _SIMDB
void fill_promo_data(struct promotional_processing_t *pp_data);
#endif
#endif
