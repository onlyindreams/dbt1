#!/bin/sh

echo "start backup"
./define_medium.sh

_test=`pg_dump $SID1 --file=/tmp/$SID1.db | grep OK`
if [ "$_test" != "" ]; then
        echo "backup failed: $_o"
        exit 1
fi
