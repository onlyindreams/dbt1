/* app_txn_queue.h 
 * transaction queue data structure, it is actually a big array
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2002 Mark Wong & Jenny Zhang &
 *                    Open Source Development Lab, Inc.
 *
 */
#ifndef _APP_TXN_QUEUE_H
#define _APP_TXN_QUEUE_H
#include <pthread.h>

struct QItem
{
	int TxnType;
	int SlotID;
};

struct Queue
{
	int front;
	int rear;
	int items;
	int size;
	struct QItem *TxnQ;
};

void init_queue(struct Queue *txn_queue, int TxnQSize);
int isempty(struct Queue txn_queue);
int isfull(struct Queue txn_queue);
int queuecount(struct Queue txn_queue);
int enqueue(struct QItem Item, struct Queue *txn_queue);
int dequeue(struct QItem *Item, struct Queue *txn_queue);

#endif
