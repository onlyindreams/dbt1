#!/bin/sh

echo "changing data_cache to 10000"
_o=`cat <<EOF |  /opt/sapdb/depend/bin/dbmcli -d $SID1 -u dbm,dbm 2>&1
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

echo "restore db"
./define_medium.sh
_o=`cat <<EOF | dbmcli -d $SID1 -u dbm,dbm 2>&1
db_stop
db_start
util_connect dbm,dbm
util_execute INIT CONFIG
recover_start data
recover_start incr
util_release
quit
EOF`
_test=`echo $_o | grep OK`
if [ "$_test" = "" ]; then
        echo "db restore failed: $_o"
        exit 1
fi

echo "changing data_cache back to 262144"
./set_param.sh 1
