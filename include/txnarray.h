/*
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2002 Mark Wong & Jenny Zhang &
 *                    Open Source Development Lab, Inc.
 *
 */
#ifndef __TXNARRAY_H
#define __TXNARRAY_H

#include <pthread.h>
#define ArrayDim 50
#include "txnstruct.h"

//an array of *Info is created for each transaction,
//Here we declare a template first
/*
template <class TYPE>
class TxnInfoArray
{
 private:
   //flag to indicate if this slot is used, 0 -- free 1 -- usede
   int pin[ArrayDim];
   pthread_mutex_t TxnArrayMutex;
 public:
   TxnInfoArray();
   TYPE TxnInfo[ArrayDim];
   //find a free slot and pin it, return -1 if can not pin it
   int PinSlot();
   //release this slot
   void FreeSlot(int SlotID);
};*/

class AdminConfTxnArray
{
 private:
   //flag to indicate if this slot is used, 0 -- free 1 -- usede
   int pin[ArrayDim];
   pthread_mutex_t TxnArrayMutex;
 public:
   AdminConfTxnArray();
   struct AdminConfInfo TxnInfo[ArrayDim];
   //find a free slot and pin it, return -1 if can not pin it
   int PinSlot();
   //release this slot
   void FreeSlot(int SlotID);
};

class AdminReqTxnArray
{
 private:
   //flag to indicate if this slot is used, 0 -- free 1 -- usede
   int pin[ArrayDim];
   pthread_mutex_t TxnArrayMutex;
 public:
   AdminReqTxnArray();
   struct AdminReqInfo TxnInfo[ArrayDim];
   //find a free slot and pin it, return -1 if can not pin it
   int PinSlot();
   //release this slot
   void FreeSlot(int SlotID);
};

class SearchSubTxnArray
{
 private:
   //flag to indicate if this slot is used, 0 -- free 1 -- usede
   int pin[ArrayDim];
   pthread_mutex_t TxnArrayMutex;
 public:
   SearchSubTxnArray();
   struct SearchSubInfo TxnInfo[ArrayDim];
   //find a free slot and pin it, return -1 if can not pin it
   int PinSlot();
   //release this slot
   void FreeSlot(int SlotID);
};

class BuyConfTxnArray
{
 private:
   //flag to indicate if this slot is used, 0 -- free 1 -- usede
   int pin[ArrayDim];
   pthread_mutex_t TxnArrayMutex;
 public:
   BuyConfTxnArray();
   struct BuyConfInfo TxnInfo[ArrayDim];
   //find a free slot and pin it, return -1 if can not pin it
   int PinSlot();
   //release this slot
   void FreeSlot(int SlotID);
};

class BuyReqTxnArray
{
 private:
   //flag to indicate if this slot is used, 0 -- free 1 -- usede
   int pin[ArrayDim];
   pthread_mutex_t TxnArrayMutex;
 public:
   BuyReqTxnArray();
   struct BuyReqInfo TxnInfo[ArrayDim];
   //find a free slot and pin it, return -1 if can not pin it
   int PinSlot();
   //release this slot
   void FreeSlot(int SlotID);
};

class HomeTxnArray
{
 private:
   //flag to indicate if this slot is used, 0 -- free 1 -- usede
   int pin[ArrayDim];
   pthread_mutex_t TxnArrayMutex;
 public:
   HomeTxnArray();
   struct HomeInfo TxnInfo[ArrayDim];
   //find a free slot and pin it, return -1 if can not pin it
   int PinSlot();
   //release this slot
   void FreeSlot(int SlotID);
};

class OrderDispTxnArray
{
 private:
   //flag to indicate if this slot is used, 0 -- free 1 -- usede
   int pin[ArrayDim];
   pthread_mutex_t TxnArrayMutex;
 public:
   OrderDispTxnArray();
   struct OrderDispInfo TxnInfo[ArrayDim];
   //find a free slot and pin it, return -1 if can not pin it
   int PinSlot();
   //release this slot
   void FreeSlot(int SlotID);
};

class OrderInqTxnArray
{
 private:
   //flag to indicate if this slot is used, 0 -- free 1 -- usede
   int pin[ArrayDim];
   pthread_mutex_t TxnArrayMutex;
 public:
   OrderInqTxnArray();
   struct OrderInqInfo TxnInfo[ArrayDim];
   //find a free slot and pin it, return -1 if can not pin it
   int PinSlot();
   //release this slot
   void FreeSlot(int SlotID);
};

class ProdDetailTxnArray
{
 private:
   //flag to indicate if this slot is used, 0 -- free 1 -- usede
   int pin[ArrayDim];
   pthread_mutex_t TxnArrayMutex;
 public:
   ProdDetailTxnArray();
   struct ProdDetailInfo TxnInfo[ArrayDim];
   //find a free slot and pin it, return -1 if can not pin it
   int PinSlot();
   //release this slot
   void FreeSlot(int SlotID);
};

class ShopCartTxnArray
{
 private:
   //flag to indicate if this slot is used, 0 -- free 1 -- usede
   int pin[ArrayDim];
   pthread_mutex_t TxnArrayMutex;
 public:
   ShopCartTxnArray();
   struct ShopCartInfo TxnInfo[ArrayDim];
   //find a free slot and pin it, return -1 if can not pin it
   int PinSlot();
   //release this slot
   void FreeSlot(int SlotID);
};

#endif
