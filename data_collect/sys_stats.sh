# sys_stat.sh: get system info using sar, iostat and vmstat
#
# This file is released under the terms of the Artistic License.  Please see
# the file LICENSE, included in this package, for details.
#
# Copyright (C) 2003 Open Source Development Lab, Inc.
#
# March 2003

#!/bin/sh
if [ $# -ne 3 ]; then
	echo "Usage: ./$0 <interval> <duration> <result_dir>"
	exit
fi

INTERVAL=$1
RUN_DURATION=$2
RESULTS_PATH=$3

#calculate count
let "COUNT=$RUN_DURATION/$INTERVAL"
if [ $COUNT -eq 0 ]
then
	COUNT=1
fi

#get one more count
let "COUNT=$COUNT+1"

##get database statistics
#echo "start db_stats.sh"
#./db_stats.sh $SID $RESULTS_PATH $COUNT $INTERVAL &
#
if [ -f $RESULTS_PATH/run.sar.data ]; then
	rm $RESULTS_PATH/run.sar.data
fi

#get meminfo
echo "get meminfo0"
cat /proc/meminfo > $RESULTS_PATH/run.meminfo0.out
sleep 2

echo "start sar"
VERSION=`uname -r | awk -F "." '{print $2}'`
export PATH=/usr/local/bin:$PATH

sar -V &> .sar.tmp
sysstat_version=`cat .sar.tmp |grep version | awk '{print $3}'`
rm .sar.tmp
echo "sysstat version $sysstat_version"

if [ $sysstat_version = '4.0.3' ]
then 
#use sysstat 4.1.2
#sar
#/usr/local/bin/sar -u -P ALL -d -B -r -q -W -b -o $RESULTS_PATH/run.sar.data $INTERVAL $COUNT &
sar -u -U ALL -d -B -r -q -W -b -o $RESULTS_PATH/run.sar.data $INTERVAL $COUNT &
#iostat
#/usr/src/ziostat/ziostat -a -d $INTERVAL $COUNT >> $RESULTS_PATH/iostat.txt &
#/usr/src/ziostat/ziostat -a -x $INTERVAL $COUNT >> $RESULTS_PATH/iostat-x.txt &
#/usr/local/bin/iostat -d $INTERVAL $COUNT >> $RESULTS_PATH/iostat.txt &
else
sar -u -P ALL -d -B -r -q -W -b -o $RESULTS_PATH/run.sar.data $INTERVAL $COUNT &
#use sysstat 4.0.3
#sar
#/usr/bin/sar -u -U ALL -d -B -r -q -W -b -o $RESULTS_PATH/run.sar.data $INTERVAL $COUNT &
#iostat
#/usr/bin/iostat -d $INTERVAL $COUNT >> $RESULTS_PATH/iostat.txt &
fi

echo "start iostat";
echo "iostat -d $INTERVAL $COUNT" > $RESULTS_PATH/run.iostat.txt
iostat -d $INTERVAL $COUNT >> $RESULTS_PATH/run.iostat.txt &

if [ -f /usr/local/bin/ziostat ]; then
	echo "start ziostat";
	echo "ziostat -x $INTERVAL $COUNT" > $RESULTS_PATH/run.ziostat.txt
	ziostat -x $INTERVAL $COUNT  >> $RESULTS_PATH/run.ziostat.txt &
fi

# collect vmstat 
echo "start vmstat"
echo "vmstat $INTERVAL $COUNT" > $RESULTS_PATH/run.vmstat.out
vmstat $INTERVAL $COUNT >> $RESULTS_PATH/run.vmstat.out &
#sh ./runtop.sh $1 $2 $RESULTS_PATH &

echo "sleep for $RUN_DURATION seconds..."
sleep $RUN_DURATION

#get meminfo
cat /proc/meminfo > $RESULTS_PATH/run.meminfo1.out

echo "sys_stats.sh done"
