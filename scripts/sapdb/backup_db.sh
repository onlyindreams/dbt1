#!/bin/sh

echo "changing data_cache to 10000"
_o=`cat <<EOF |  /opt/sapdb/depend/bin/dbmcli -d $SID1 -u dbm,dbm 2>&1
db_cold
param_startsession
param_put DATA_CACHE 10000
param_checkall
param_commitsession
quit
EOF`
_test=`echo $_o | grep ERR`
if ! [ "$_test" = "" ]; then
        echo "set parameters failed"
        exit 1
fi

date
echo "start backup"
./define_medium.sh

_o=`cat <<EOF | /opt/sapdb/depend/bin/dbmcli -d $SID1 -u dbm,dbm 2>&1
db_stop
db_start
util_connect dbm,dbm
backup_start data migration
backup_start incr migration
util_release
quit
EOF`
_test=`echo $_o | grep OK`
if [ "$_test" = "" ]; then
        echo "backup failed: $_o"
        exit 1
fi
date

echo "changing data_cache back to 262144"
./set_param.sh 1
