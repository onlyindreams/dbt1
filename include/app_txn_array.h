/* app_txn_array.h 
 * array of odbc_data_t to hold input/output for each transaction
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2002 Mark Wong & Jenny Zhang &
 *                    Open Source Development Lab, Inc.
 *
 */
#ifndef _APP_TXN_ARRAY_H
#define _APP_TXN_ARRAY_H
#include <pthread.h>
#include "odbc_interaction.h"


struct app_txn_array
{
	int size;
	int *pin;
	pthread_mutex_t odbc_txn_array_mutex;
	union odbc_data_t *odbc_data_array;
#ifdef GET_TIME
	double *db_response_time;
#endif
};

void init_app_txn_array(struct app_txn_array *txn_array, int ArraySize);
int PinSlot(struct app_txn_array *txn_array);
int FreeSlot(struct app_txn_array *txn_array, int SlotID);
#endif
