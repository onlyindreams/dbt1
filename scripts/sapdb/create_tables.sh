#!/bin/sh

/opt/sapdb/depend/bin/dbmcli -d $SID1 -u dbm,dbm -uSQL dbt,dbt -i create_tables.sql
