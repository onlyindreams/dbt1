/*
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2002 Mark Wong & Jenny Zhang &
 *                    Open Source Development Lab, Inc.
 *
 */

#ifndef __QUEUE_H__
#define __QUEUE_H__
#include <sys/types.h>

#define TxnQSize 50
struct QItem
{
   int TxnType;
   int SlotID;
//--   pid_t pid;
};

//this simulates a Queue, we use an array since we do not want to
//alloc/dealloc memory frequently
class Queue
{
 private:
   QItem TxnQ[TxnQSize];
   int front;
   int rear;
   int items;
 public:
   Queue();
   ~Queue();
   bool isempty();
   bool isfull();
   int queuecount();
   int enqueue(const QItem &Item);
   int dequeue(QItem *Item);
};
#endif
