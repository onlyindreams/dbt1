#!/bin/sh

echo "define backup medium"
_o=`cat <<EOF | /opt/sapdb/depend/bin/dbmcli -d $SID -u dbm,dbm 2>&1
medium_put data /dbt1_backup/data FILE DATA 0 8 YES
medium_put incr /dbt1_backup/incremental FILE PAGES 0 8 YES
quit
EOF`
_test=`echo $_o | grep OK`
if [ "$_test" = "" ]; then
        echo "backup failed: $_o"
        exit 1
fi
