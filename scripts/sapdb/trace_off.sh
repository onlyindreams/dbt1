#!/bin/sh

dbmcli -d DBT1 -u dbm,dbm sql_execute vtrace
dbmcli -d DBT1 -u dbm,dbm trace_prot akb
dbmgetf -d DBT1 -u dbm,dbm -k KNLTRCPRT -f $1
dbmcli -d DBT1 -u dbm,dbm util_execute diagnose vtrace default off
