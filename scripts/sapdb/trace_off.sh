#!/bin/sh

/opt/sapdb/depend/bin/dbmcli -d DBT1 -u dbm,dbm sql_execute vtrace
/opt/sapdb/depend/bin/dbmcli -d DBT1 -u dbm,dbm trace_prot akb
/opt/sapdb/depend/bin/dbmgetf -d DBT1 -u dbm,dbm -k KNLTRCPRT -f $1
/opt/sapdb/depend/bin/dbmcli -d DBT1 -u dbm,dbm util_execute diagnose vtrace default off
