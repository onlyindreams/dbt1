#!/bin/sh

dbmcli -d $SID1 -u dbm,dbm -uSQL dbt,dbt -i drop_dbproc.sql
