#!/bin/sh

#note: if DATA_CACHE is too big, it should be reduced before backup
#otherwise we get I/O error
#echo "changing data_cache to 10000"
#_o=`cat <<EOF |  /opt/sapdb/depend/bin/dbmcli -d $SID -u dbm,dbm 2>&1
#param_startsession
#param_put DATA_CACHE 10000
#param_checkall
#param_commitsession
#quit
#EOF`
#_test=`echo $_o | grep ERR`
#if ! [ "$_test" = "" ]; then
#        echo "set parameters failed"
#        exit 1
#fi

date
echo "start backup"
_o=`cat <<EOF | /opt/sapdb/depend/bin/dbmcli -d DBT1 -u dbm,dbm 2>&1
db_stop
db_start
util_connect dbm,dbm
backup_start data migration
backup_start incr migration
util_release
db_warm
quit
EOF`
_test=`echo $_o | grep OK`
if [ "$_test" = "" ]; then
        echo "backup failed: $_o"
        exit 1
fi
date

#echo "changing data_cache back to 262144"
#_o=`cat <<EOF |  /opt/sapdb/depend/bin/dbmcli -d $SID -u dbm,dbm 2>&1
#param_startsession
#param_put DATA_CACHE 262144
#param_put _IDXFILE_LIST_SIZE 8192
#param_checkall
#param_commitsession
#db_stop
#db_start
#db_warm
#quit
#EOF`
#_test=`echo $_o | grep ERR`
#if ! [ "$_test" = "" ]; then
#        echo "set parameters failed"
#        exit 1
#fi
