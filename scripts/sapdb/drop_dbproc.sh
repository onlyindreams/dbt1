#!/bin/sh

export PATH=/usr/sapdb/depend/bin:$PATH

set -x

dbmcli -d $SID1 -u dbm,dbm -uSQL dbt,dbt "sql_execute drop dbproc getCustName"
dbmcli -d $SID1 -u dbm,dbm -uSQL dbt,dbt "sql_execute drop dbproc search_results_title"
dbmcli -d $SID1 -u dbm,dbm -uSQL dbt,dbt "sql_execute drop dbproc search_results_subject"
dbmcli -d $SID1 -u dbm,dbm -uSQL dbt,dbt "sql_execute drop dbproc search_results_author"
dbmcli -d $SID1 -u dbm,dbm -uSQL dbt,dbt "sql_execute drop dbproc best_sellers"
dbmcli -d $SID1 -u dbm,dbm -uSQL dbt,dbt "sql_execute drop dbproc new_products"
dbmcli -d $SID1 -u dbm,dbm -uSQL dbt,dbt "sql_execute drop dbproc admin_confirm"
dbmcli -d $SID1 -u dbm,dbm -uSQL dbt,dbt "sql_execute drop dbproc admin_request"
dbmcli -d $SID1 -u dbm,dbm -uSQL dbt,dbt "sql_execute drop dbproc product_detail"
dbmcli -d $SID1 -u dbm,dbm -uSQL dbt,dbt "sql_execute drop dbproc order_display"
dbmcli -d $SID1 -u dbm,dbm -uSQL dbt,dbt "sql_execute drop dbproc order_inquiry"
dbmcli -d $SID1 -u dbm,dbm -uSQL dbt,dbt "sql_execute drop dbproc shopping_cart"
dbmcli -d $SID1 -u dbm,dbm -uSQL dbt,dbt "sql_execute drop dbproc buy_confirm"
dbmcli -d $SID1 -u dbm,dbm -uSQL dbt,dbt "sql_execute drop dbproc buy_request"
dbmcli -d $SID1 -u dbm,dbm -uSQL dbt,dbt "sql_execute drop dbproc home"
dbmcli -d $SID1 -u dbm,dbm -uSQL dbt,dbt "sql_execute drop dbproc getOrderItems"
dbmcli -d $SID1 -u dbm,dbm -uSQL dbt,dbt "sql_execute drop dbproc initOrderItems"
dbmcli -d $SID1 -u dbm,dbm -uSQL dbt,dbt "sql_execute drop dbproc getSCDetail"
dbmcli -d $SID1 -u dbm,dbm -uSQL dbt,dbt "sql_execute drop dbproc initSCItems"
dbmcli -d $SID1 -u dbm,dbm -uSQL dbt,dbt "sql_execute drop dbproc updateSC"
dbmcli -d $SID1 -u dbm,dbm -uSQL dbt,dbt "sql_execute drop dbproc InsertCust"
dbmcli -d $SID1 -u dbm,dbm -uSQL dbt,dbt "sql_execute drop dbproc getCustInfo"
dbmcli -d $SID1 -u dbm,dbm -uSQL dbt,dbt "sql_execute drop dbproc refreshSC"
dbmcli -d $SID1 -u dbm,dbm -uSQL dbt,dbt "sql_execute drop dbproc createSC"
dbmcli -d $SID1 -u dbm,dbm -uSQL dbt,dbt "sql_execute drop dbproc addToSC"
dbmcli -d $SID1 -u dbm,dbm -uSQL dbt,dbt "sql_execute drop dbproc getSCSubTotal"
dbmcli -d $SID1 -u dbm,dbm -uSQL dbt,dbt "sql_execute drop dbproc DigSyl"
dbmcli -d $SID1 -u dbm,dbm -uSQL dbt,dbt "sql_execute drop dbproc GetPromoImages"
