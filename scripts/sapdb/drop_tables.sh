#!/bin/sh

dbmcli -d DBT1 -u dbm,dbm -uSQL dbt,dbt -i drop_tables.sql
