#!/bin/sh

/opt/sapdb/depend/bin/dbmcli -s -d DBT1 -u dba,dba -uSQL dbt,dbt "sql_execute select * from monitor_caches" > mcache.out
/opt/sapdb/depend/bin/dbmcli -s -d DBT1 -u dba,dba -uSQL dbt,dbt "sql_execute select * from monitor_load" > mcache.out
/opt/sapdb/depend/bin/dbmcli -s -d DBT1 -u dba,dba -uSQL dbt,dbt "sql_execute select * from monitor_lock" > mcache.out
/opt/sapdb/depend/bin/dbmcli -s -d DBT1 -u dba,dba -uSQL dbt,dbt "sql_execute select * from monitor_log" > mcache.out
/opt/sapdb/depend/bin/dbmcli -s -d DBT1 -u dba,dba -uSQL dbt,dbt "sql_execute select * from monitor_pages" > mcache.out
/opt/sapdb/depend/bin/dbmcli -s -d DBT1 -u dba,dba -uSQL dbt,dbt "sql_execute select * from monitor_row" > mcache.out
/opt/sapdb/depend/bin/dbmcli -s -d DBT1 -u dba,dba -uSQL dbt,dbt "sql_execute select * from monitor_trans" > mcache.out
