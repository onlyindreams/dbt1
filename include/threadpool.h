/*
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2002 Mark Wong & Jenny Zhang &
 *                    Open Source Development Lab, Inc.
 *
 */
#ifndef __THREADPOOL_H
#define __THREADPOOL_H
#include <pthread.h>

//number of threads in pool
#define PoolThreads 2
 
bool InitThreadPool();

void *DoTxn(void *fd);
#endif
