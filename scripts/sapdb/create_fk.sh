#!/bin/sh

date
dbmcli -d $SID1 -u dbm,dbm -uSQL dbt,dbt -i create_fk.sql
date
