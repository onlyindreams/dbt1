Makefile:The makefile to build the files in this directory.
app_txn_array.c: txn_array.
app_txn_queue.c: txn_queue.
app_interface.c: communication interface between RBE and appServer
appServer.c: main function and threads handling request from the RBE
app_threadpool.c: implement the threads accessing database.
design: data structure and implementation detail

For implementation detail, please refer to the file 'design'.
