#!/bin/sh
###
# 		dont start script as root!
#		--------------------------
#
# create example database TST with (only for seperated packages - sapdb-ind, sapdb-srv, sapdb-testdb):
#   - 20 MB data devspace and 8 MB log devspace
#   - demo database user test (with password test)
###


id=`id | sed s/\(.*// | sed s/uid=//`

if [ "$id" = "0" ]; then
	echo "dont start script as root"
	exit 1
fi 

export PATH=/opt/sapdb/indep_prog/bin:$PATH
#set -x

# start remote communication server
echo "start communication server..."
x_server start >/dev/null 2>&1

# dir where the database system files are
SYS_DIR="$HOME/dbt1"

# stop and drop probably existing demo database
echo "stop and drop existing $SID1..."
dbmcli -d $SID1 -u dbm,dbm db_offline >/dev/null 2>&1
dbmcli -d $SID1 -u dbm,dbm db_drop >/dev/null 2>&1

# create new demo database
echo "create database $SID1..."
_o=`/opt/sapdb/depend/bin/dbmcli -s -R /opt/sapdb/depend db_create $SID1 dbm,dbm 2>&1`
_test=`echo $_o | grep OK`
if [ "$_test" = "" ]; then
	echo "create $SID1 failed: $_o"
	exit 1
fi

# create directory where to put the database files
mkdir -p $SYS_DIR/$SID1

# setup database parameters
echo "set parameters for $SID1..."
./set_param.sh
#devspace definition
_o=`cat <<EOF | dbmcli -d $SID1 -u dbm,dbm 2>&1
param_adddevspace 1 SYS  $SYS_DIR/$SID1/DBT1_SYS_001   F
param_adddevspace 1 LOG  /dev/raw/raw8  R 120000
param_adddevspace 1 DATA /dev/raw/raw1  R 150000
param_adddevspace 2 DATA /dev/raw/raw2  R 150000
param_adddevspace 3 DATA /dev/raw/raw3  R 150000
param_adddevspace 4 DATA /dev/raw/raw4  R 150000
param_adddevspace 5 DATA /dev/raw/raw5  R 150000
param_adddevspace 6 DATA /dev/raw/raw6  R 150000
param_adddevspace 7 DATA /dev/raw/raw7  R 150000
quit
EOF`
_test=`echo $_o | grep OK`
if [ "$_test" = "" ]; then
        echo "set parameters failed: $_o"
        exit 1
fi


# startup database
echo "start $SID1..."
_o=`dbmcli -d $SID1 -u dbm,dbm db_start 2>&1`
_test=`echo $_o | grep OK`
if [ "$_test" = "" ]; then
        echo "start $SID1 failed: $_o"
        exit 1
fi

# initialize database files
echo "initializing $SID1..."
_o=`cat <<EOF | dbmcli -d $SID1 -u dbm,dbm 2>&1
util_connect dbm,dbm
util_execute init config
util_activate dba,dba
quit
EOF`
_test=`echo $_o | grep OK`
if [ "$_test" = "" ]; then
        echo "initialize $SID1 failed: $_o"
        exit 1
fi

# load database system tables
echo "load system tables..."
_o=`dbmcli -d $SID1 -u dbm,dbm load_systab -u dba,dba -ud domain 2>&1`
_test=`echo $_o | grep OK`
if [ "$_test" = "" ]; then
        echo "load system tables failed: $_o"
        exit 1
fi

# create database demo user
echo "create database demo user..."
_o=`cat <<EOF | dbmcli -d $SID1 -u dba,dba 2>&1
sql_connect dba,dba
sql_execute CREATE USER dbt PASSWORD dbt DBA NOT EXCLUSIVE
EOF`
_test=`echo $_o | grep OK`
if [ "$_test" = "" ]; then
        echo "create db user failed: $_o"
        exit 1
fi

exit 0
