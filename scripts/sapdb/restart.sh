#!/bin/sh

/opt/sapdb/depend/bin/dbmcli -s -d DBT1 -u dbm,dbm db_cold
/opt/sapdb/depend/bin/dbmcli -s -d DBT1 -u dbm,dbm db_offline
/opt/sapdb/depend/bin/dbmcli -s -d DBT1 -u dbm,dbm db_warm
