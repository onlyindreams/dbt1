#!/bin/sh

if [ $# -ne 1 ]; then
        echo "Usage: ./get_log_info.sh <result_dir>"
        exit
fi

i=1
echo "">$1/info_log
while [ $i -le 20 ] 
do
echo "======= log info $i ==========" >> $1/info_log
dbmcli -d $SID1 -u dbm,dbm -uSQL dbt,dbt "info log" >> $1/info_log
sleep 60
let "i=$i+1"
done
