# get_config.sh: get dbt3 run configuration
#
# This file is released under the terms of the Artistic License.  Please see
# the file LICENSE, included in this package, for details.
#
# Copyright (C) 2003 Open Source Development Lab, Inc.
#
# Author: Jenny Zhang
# Dec 2003

#!/bin/sh

if [ $# -lt 3 ]; then
        echo "usage: $0.sh <redirect_tmp> <redirect_xlog> <output_dir>"
        exit
fi

redirect_tmp=$1
redirect_xlog=$2
output_dir=$3

kernel=`uname -r`
pgsql=`psql --version | grep PostgreSQL | awk '{print $3}'`
procps=`vmstat -V|grep version| awk '{print $3}'`
sar -V &> .sar.tmp
sysstat=`cat .sar.tmp |grep version | awk '{print $3}'`
rm .sar.tmp

#CPUS=`grep -c '^processor' /proc/cpuinfo`
CPUS=1
MHz=`grep 'cpu MHz' /proc/cpuinfo|head -1|awk -F: '{print $2}'`
model=`grep 'model name' /proc/cpuinfo|head -1|awk -F: '{print $2}'`

memory=`grep 'MemTotal' /proc/meminfo | awk -F: '{print $2 $3}'`

shmmax_value=`/sbin/sysctl -e -a |grep shmmax|awk '{print $3}'`

dbitems=`grep 'items' dbt1.${CPUS}way.conf | awk -F= '{print $2}'`
dbcustomers=`grep 'gcustomers' dbt1.${CPUS}way.conf | awk -F= '{print $2}'`
let "dbcustomers=$dbcustomers/2880"
cachedbconnection=`grep 'mconnection' dbt1.${CPUS}way.conf | awk -F= '{print $2}'`
numcache=1
numserver=`grep '^server_host' dbt1.${CPUS}way.conf | wc -l`
serverdbconnection=`grep 'rconnection' dbt1.${CPUS}way.conf | awk -F= '{print $2}'`
numdriver=`grep '^ydriver_host' dbt1.${CPUS}way.conf | wc -l`
rampuprate=`grep 'vrate' dbt1.${CPUS}way.conf | awk -F= '{print $2}'`
eus=`grep 'eus' dbt1.${CPUS}way.conf | awk -F= '{print $2}'`
duration=`grep 'zduration' dbt1.${CPUS}way.conf | awk -F= '{print $2}'`
thinktime=`grep 'think_time' dbt1.${CPUS}way.conf | awk -F= '{print $2}'`

echo "kernel: $kernel" > $output_dir/config.txt
echo "pgsql: $pgsql">> $output_dir/config.txt
echo "procps: $procps">> $output_dir/config.txt
echo "sysstat: $sysstat">> $output_dir/config.txt
echo "CPUS: $CPUS">> $output_dir/config.txt
echo "MHz: $MHz">> $output_dir/config.txt
echo "model: $model">> $output_dir/config.txt
echo "memory: $memory">> $output_dir/config.txt
echo "redirect_tmp: $redirect_tmp">> $output_dir/config.txt
echo "redirect_xlog: $redirect_xlog">> $output_dir/config.txt
echo "shmmax: $shmmax_value" >> $output_dir/config.txt
echo "dbitems: $dbitems" >> $output_dir/config.txt
echo "dbcustomers: $dbcustomers" >> $output_dir/config.txt
echo "numcache: $numcache" >> $output_dir/config.txt
echo "cachedbconnection: $cachedbconnection" >> $output_dir/config.txt
echo "numserver: $numserver" >> $output_dir/config.txt
echo "serverdbconnection: $serverdbconnection" >> $output_dir/config.txt
echo "numdriver: $numdriver" >> $output_dir/config.txt
echo "eus: $eus" >> $output_dir/config.txt
echo "rampuprate: $rampuprate" >> $output_dir/config.txt
echo "duration: $duration" >> $output_dir/config.txt
echo "thinktime: $thinktime" >> $output_dir/config.txt
