#!/bin/sh

/opt/sapdb/depend/bin/dbmcli -s -d DBT1 -u dba,dba -uSQL dbt,dbt "sql_execute select * from monitor_caches" > mcache.out
/opt/sapdb/depend/bin/dbmcli -s -d DBT1 -u dba,dba -uSQL dbt,dbt "sql_execute select * from monitor_load" > mload.out
/opt/sapdb/depend/bin/dbmcli -s -d DBT1 -u dba,dba -uSQL dbt,dbt "sql_execute select * from monitor_lock" > mlock.out
/opt/sapdb/depend/bin/dbmcli -s -d DBT1 -u dba,dba -uSQL dbt,dbt "sql_execute select * from monitor_log" > mlog.out
/opt/sapdb/depend/bin/dbmcli -s -d DBT1 -u dba,dba -uSQL dbt,dbt "sql_execute select * from monitor_pages" > mpages.out
/opt/sapdb/depend/bin/dbmcli -s -d DBT1 -u dba,dba -uSQL dbt,dbt "sql_execute select * from monitor_row" > mrow.out
/opt/sapdb/depend/bin/dbmcli -s -d DBT1 -u dba,dba -uSQL dbt,dbt "sql_execute select * from monitor_trans" > mtrans.out
