/*
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2002 Mark Wong & Jenny Zhang &
 *                    Open Source Development Lab, Inc.
 *
 */
#include "app_txn_array.h"
#include <string.h>

void init_app_txn_array(struct app_txn_array *txn_array, int ArraySize)
{
	int i;
	pthread_mutex_init(&txn_array->odbc_txn_array_mutex, NULL);
	txn_array->size=ArraySize;
	txn_array->pin=(int *)malloc(sizeof(int)*ArraySize);
	txn_array->odbc_data_array=(union odbc_data_t *)malloc(sizeof(union odbc_data_t)*ArraySize);

#ifdef GET_TIME
	txn_array->db_response_time=(double *)malloc(sizeof(double)*ArraySize);
#endif
	/* all the slots are initially free */
	for (i=0; i<txn_array->size; i++) 
	{
		txn_array->pin[i]=0;
		bzero(&txn_array->odbc_data_array[i], sizeof(union odbc_data_t));
#ifdef GET_TIME
		txn_array->db_response_time[i]=0.0;
#endif
	}
}

int PinSlot(struct app_txn_array *txn_array)
{
	int i;
	pthread_mutex_lock(&txn_array->odbc_txn_array_mutex);
	for (i=0; i<txn_array->size; i++)
	{
		if (txn_array->pin[i] == 0) 
		{ 
			txn_array->pin[i] = 1;
			pthread_mutex_unlock(&txn_array->odbc_txn_array_mutex);
			return i;
		}
	} 
	/* all are used */
	pthread_mutex_unlock(&txn_array->odbc_txn_array_mutex);
	return -1;
}

int FreeSlot(struct app_txn_array *txn_array, int SlotID)
{
	pthread_mutex_lock(&txn_array->odbc_txn_array_mutex);
	txn_array->pin[SlotID]=0;
	bzero(&txn_array->odbc_data_array[SlotID], sizeof(union odbc_data_t));
	pthread_mutex_unlock(&txn_array->odbc_txn_array_mutex);
}

