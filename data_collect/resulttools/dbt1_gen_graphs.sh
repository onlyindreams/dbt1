#!/bin/sh

# dbt3_gen_graphs.sh: parse the statistic output and generate graphs for dbt-3 runs
# This file is released under the terms of the Artistic License.  Please see
# the file LICENSE, included in this package, for details.
#
# Copyright (C) 2003 Open Source Development Lab, Inc.
#
# Author: Jenny Zhang
# Feb 2003

if [ $# -lt 2 ]; then
        echo "usage: $0 <input_dir> <output_dir>"
        exit
fi

input_dir=$1
output_dir=$2
CPUS=`grep -c ^processor /proc/cpuinfo`

VERSION=`uname -r | awk -F "." '{print $2}'`
sar -V &> .sar.tmp
sysstat_version=`cat .sar.tmp |grep version | awk '{print $3}'`
rm .sar.tmp

echo "making output dir  $output_dir"
mkdir -p $output_dir

if [ -f $input_dir/build.vmstat.out ]; then
	echo "parse build vmstat";
	#parse vmstat
	./parse_vmstat.pl -i $input_dir/build.vmstat.out -o $output_dir/build.vmstat -c "vmstat taken every 60 seconds"

	#generate graphs based on build.vmstat.dat file
	./gr_single_dir.pl -i $output_dir/build.vmstat.dat -o $output_dir/build.vmstat_cpu -t "build vmstat CPU" -b "build.vmstat." -e ".dat" -c 12,13,14,15 -v "percetage" -hl "samples every 60 sec"

	./gr_single_dir.pl -i $output_dir/build.vmstat.dat -o $output_dir/build.vmstat_io -t "build vmstat IO" -b "build.vmstat." -e ".dat" -c 8,9 -v "Block/Sec" -hl "samples every 60 sec"

	./gr_single_dir.pl -i $output_dir/build.vmstat.dat -o $output_dir/build.vmstat_memory -t "build vmstat memory" -b "build.vmstat." -e ".dat" -c 2,3,4,5, -v "kblock" -hl "samples every 60 sec"

	./gr_single_dir.pl -i $output_dir/build.vmstat.dat -o $output_dir/build.vmstat_swap -t "build vmstat swap" -b "build.vmstat." -e ".dat" -c 6,7 -v "kblock/sec" -hl "samples every 60 sec"

	./gr_single_dir.pl -i $output_dir/build.vmstat.dat -o $output_dir/build.vmstat_system -t "build vmstat system" -b "build.vmstat." -e ".dat" -c 10,11 -v "per sec" -hl "samples every 60 sec"

	./gr_single_dir.pl -i $output_dir/build.vmstat.dat -o $output_dir/build.vmstat_procs -t "build vmstat process" -b "build.vmstat." -e ".dat" -c 0,1 -hl "samples every 60 sec"
fi
	
if [ -f $input_dir/run.vmstat.out ]; then
	echo "parse run vmstat";
	#parse vmstat
	./parse_vmstat.pl -i $input_dir/run.vmstat.out -o $output_dir/run.vmstat -c "vmstat taken every 60 seconds"
	#generate graphs based on run.vmstat.dat file
	./gr_single_dir.pl -i $output_dir/run.vmstat.dat -o $output_dir/run.vmstat_cpu -t "run vmstat CPU" -b "run.vmstat." -e ".dat" -c 12,13,14,15 -v "percetage" -hl "samples every 60 sec"

	./gr_single_dir.pl -i $output_dir/run.vmstat.dat -o $output_dir/run.vmstat_io -t "run vmstat IO" -b "run.vmstat." -e ".dat" -c 8,9 -v "Block/Sec" -hl "samples every 60 sec"

	./gr_single_dir.pl -i $output_dir/run.vmstat.dat -o $output_dir/run.vmstat_memory -t "run vmstat memory" -b "run.vmstat." -e ".dat" -c 2,3,4,5, -v "kblock" -hl "samples every 60 sec"

	./gr_single_dir.pl -i $output_dir/run.vmstat.dat -o $output_dir/run.vmstat_swap -t "run vmstat swap" -b "run.vmstat." -e ".dat" -c 6,7 -v "kblock/sec" -hl "samples every 60 sec"

	./gr_single_dir.pl -i $output_dir/run.vmstat.dat -o $output_dir/run.vmstat_system -t "run vmstat system" -b "run.vmstat." -e ".dat" -c 10,11 -v "per sec" -hl "samples every 60 sec"

	./gr_single_dir.pl -i $output_dir/run.vmstat.dat -o $output_dir/run.vmstat_procs -t "run vmstat process" -b "run.vmstat." -e ".dat" -c 0,1 -hl "samples every 60 sec"
fi
	
if [ -f $input_dir/build.iostat.txt ]; then
	echo "parse build iostat";
	./parse_iostat.pl -i $input_dir/build.iostat.txt -d $output_dir/build.iostat -co "iostat -d taken every 60 seconds" -o '-d'
	#generate graphs based on build iostat .dat file
	./gr_single_dir.pl -i "$output_dir/build.iostat.*.dat" -o $output_dir/build.iostat_read_sec -t "build iostat read per second" -b "build.iostat." -e ".dat" -c 1 -hl "samples every 60 sec"
	./gr_single_dir.pl -i "$output_dir/build.iostat.*.dat" -o $output_dir/build.iostat_write_sec -t "build iostat write per second" -b "build.iostat." -e ".dat" -c 2 -hl "samples every 60 sec"
	./gr_single_dir.pl -i "$output_dir/build.iostat.*.dat" -o $output_dir/build.iostat_tps -t "build iostat tps" -b "build.iostat." -e ".dat" -c 0 -hl "samples every 60 sec"
fi

if [ -f $input_dir/run.iostat.txt ]; then
	echo "parse run iostat";
	./parse_iostat.pl -i $input_dir/run.iostat.txt -d $output_dir/run.iostat -co "iostat -d taken every 60 seconds" -o '-d'
	#generate graphs based on run iostat .dat file
	./gr_single_dir.pl -i "$output_dir/run.iostat.*.dat" -o $output_dir/run.iostat_read_sec -t "run iostat read per second" -b "run.iostat." -e ".dat" -c 1 -hl "samples every 60 sec"
	./gr_single_dir.pl -i "$output_dir/run.iostat.*.dat" -o $output_dir/run.iostat_write_sec -t "run iostat write per second" -b "run.iostat." -e ".dat" -c 2 -hl "samples every 60 sec"
	./gr_single_dir.pl -i "$output_dir/run.iostat.*.dat" -o $output_dir/run.iostat_tps -t "run iostat tps" -b "run.iostat." -e ".dat" -c 0 -hl "samples every 60 sec"
fi

if [ -f $input_dir/build.ziostat.txt ]; then
	echo "parse build ziostat";
	./parse_ziostat.pl -i $input_dir/build.ziostat.txt -d $output_dir/build.ziostat -co "ziostat -d taken every 60 seconds" -o '-x'
	#generate graphs based on build iostat .dat file
	./gr_single_dir.pl -i "$output_dir/build.ziostat.*.dat" -o $output_dir/build.ziostat_read_merge -t "build ziostat read request merged per second" -b "build.ziostat." -e ".dat" -c 0 -hl "samples every 60 sec"
	./gr_single_dir.pl -i "$output_dir/build.ziostat.*.dat" -o $output_dir/build.ziostat_write_merge -t "build ziostat write request merged per second" -b "build.ziostat." -e ".dat" -c 1 -hl "samples every 60 sec"
	./gr_single_dir.pl -i "$output_dir/build.ziostat.*.dat" -o $output_dir/build.ziostat_read_request -t "build ziostat read request per second" -b "build.ziostat." -e ".dat" -c 2 -hl "samples every 60 sec"
	./gr_single_dir.pl -i "$output_dir/build.ziostat.*.dat" -o $output_dir/build.ziostat_write_request -t "build ziostat write request per second" -b "build.ziostat." -e ".dat" -c 3 -hl "samples every 60 sec"
	./gr_single_dir.pl -i "$output_dir/build.ziostat.*.dat" -o $output_dir/build.ziostat_kbyte_read -t "build ziostat kbyte read per second" -b "build.ziostat." -e ".dat" -c 4 -hl "samples every 60 sec"
	./gr_single_dir.pl -i "$output_dir/build.ziostat.*.dat" -o $output_dir/build.ziostat_kbyte_write -t "build ziostat kbyte write per second" -b "build.ziostat." -e ".dat" -c 5 -hl "samples every 60 sec"
	./gr_single_dir.pl -i "$output_dir/build.ziostat.*.dat" -o $output_dir/build.ziostat_avg_request_size -t "build ziostat average request size in kbyte" -b "build.ziostat." -e ".dat" -c 6 -hl "samples every 60 sec"
	./gr_single_dir.pl -i "$output_dir/build.ziostat.*.dat" -o $output_dir/build.ziostat_avg_queue_size -t "build ziostat average queued requests" -b "build.ziostat." -e ".dat" -c 7 -hl "samples every 60 sec"
	./gr_single_dir.pl -i "$output_dir/build.ziostat.*.dat" -o $output_dir/build.ziostat_wait_time -t "build ziostat average io wait time" -b "build.ziostat." -e ".dat" -c 8 -hl "samples every 60 sec"
	./gr_single_dir.pl -i "$output_dir/build.ziostat.*.dat" -o $output_dir/build.ziostat_svc_time -t "build ziostat average service time" -b "build.ziostat." -e ".dat" -c 9 -hl "samples every 60 sec"
	./gr_single_dir.pl -i "$output_dir/build.ziostat.*.dat" -o $output_dir/build.ziostat_util -t "build ziostat disk utility" -b "build.ziostat." -e ".dat" -c 10 -hl "samples every 60 sec"
fi

if [ -f $input_dir/run.ziostat.txt ]; then
	echo "parse run ziostat";
	./parse_ziostat.pl -i $input_dir/run.ziostat.txt -d $output_dir/run.ziostat -co "ziostat -d taken every 60 seconds" -o '-x'
	#generate graphs based on run iostat .dat file
	./gr_single_dir.pl -i "$output_dir/run.ziostat.*.dat" -o $output_dir/run.ziostat_read_merge -t "run ziostat read request merged per second" -b "run.ziostat." -e ".dat" -c 0 -hl "samples every 60 sec"
	./gr_single_dir.pl -i "$output_dir/run.ziostat.*.dat" -o $output_dir/run.ziostat_write_merge -t "run ziostat write request merged per second" -b "run.ziostat." -e ".dat" -c 1 -hl "samples every 60 sec"
	./gr_single_dir.pl -i "$output_dir/run.ziostat.*.dat" -o $output_dir/run.ziostat_read_request -t "run ziostat read request per second" -b "run.ziostat." -e ".dat" -c 2 -hl "samples every 60 sec"
	./gr_single_dir.pl -i "$output_dir/run.ziostat.*.dat" -o $output_dir/run.ziostat_write_request -t "run ziostat write request per second" -b "run.ziostat." -e ".dat" -c 3 -hl "samples every 60 sec"
	./gr_single_dir.pl -i "$output_dir/run.ziostat.*.dat" -o $output_dir/run.ziostat_kbyte_read -t "run ziostat kbyte read per second" -b "run.ziostat." -e ".dat" -c 4 -hl "samples every 60 sec"
	./gr_single_dir.pl -i "$output_dir/run.ziostat.*.dat" -o $output_dir/run.ziostat_kbyte_write -t "run ziostat kbyte write per second" -b "run.ziostat." -e ".dat" -c 5 -hl "samples every 60 sec"
	./gr_single_dir.pl -i "$output_dir/run.ziostat.*.dat" -o $output_dir/run.ziostat_avg_request_size -t "run ziostat average request size in kbyte" -b "run.ziostat." -e ".dat" -c 6 -hl "samples every 60 sec"
	./gr_single_dir.pl -i "$output_dir/run.ziostat.*.dat" -o $output_dir/run.ziostat_avg_queue_size -t "run ziostat average queued requests" -b "run.ziostat." -e ".dat" -c 7 -hl "samples every 60 sec"
	./gr_single_dir.pl -i "$output_dir/run.ziostat.*.dat" -o $output_dir/run.ziostat_wait_time -t "run ziostat average io wait time" -b "run.ziostat." -e ".dat" -c 8 -hl "samples every 60 sec"
	./gr_single_dir.pl -i "$output_dir/run.ziostat.*.dat" -o $output_dir/run.ziostat_svc_time -t "run ziostat average service time" -b "run.ziostat." -e ".dat" -c 9 -hl "samples every 60 sec"
	./gr_single_dir.pl -i "$output_dir/run.ziostat.*.dat" -o $output_dir/run.ziostat_util -t "run ziostat disk utility" -b "run.ziostat." -e ".dat" -c 10 -hl "samples every 60 sec"
fi

if [ -f $input_dir/run.iostat.txt ]; then
	echo "parse run iostat";
	./parse_iostat.pl -i $input_dir/run.iostat.txt -d $output_dir/run.iostat -co "iostat -d taken every 60 seconds" -o '-d'
	#generate graphs based on run iostat .dat file
	./gr_single_dir.pl -i "$output_dir/run.iostat.*.dat" -o $output_dir/run.iostat_read_sec -t "run iostat read per second" -b "run.iostat." -e ".dat" -c 1 -hl "samples every 60 sec"
	./gr_single_dir.pl -i "$output_dir/run.iostat.*.dat" -o $output_dir/run.iostat_write_sec -t "run iostat write per second" -b "run.iostat." -e ".dat" -c 2 -hl "samples every 60 sec"
	./gr_single_dir.pl -i "$output_dir/run.iostat.*.dat" -o $output_dir/run.iostat_tps -t "run iostat tps" -b "run.iostat." -e ".dat" -c 0 -hl "samples every 60 sec"
fi

if [ -f $input_dir/build.sar.data ]; then
	echo "parse build sar -b";
	#parse sar io
	./parse_sar.pl -i $input_dir/build.sar.data -out $output_dir/build.sar_io -c "sar -b taken every 60 seconds" -op '-b'

	echo "parse build sar -r";
	#parse sar memory
	./parse_sar.pl -i $input_dir/build.sar.data -out $output_dir/build.sar_memory -c "sar -r taken every 60 seconds" -op '-r'

	echo "parse build sar -u";
	#parse sar total cpu
	./parse_sar.pl -i $input_dir/build.sar.data -out $output_dir/build.sar_cpu_all -c "sar -u taken every 60 seconds" -op '-u'

	if [ $sysstat_version = '4.1.2' ]; then
		echo "parse build sar -P";
		#parse sar individual cpu
		./parse_sar.pl -i $input_dir/build.sar.data -out $output_dir/build.sar -c "sar -P taken every 60 seconds" -op '-P' -n $CPUS
	else
		echo "parse build sar -U";
		#parse sar individual cpu
		./parse_sar.pl -i $input_dir/build.sar.data -out $output_dir/build.sar -c "sar -U taken every 60 seconds" -op '-U' -n $CPUS
	fi

	echo "parse build sar -W";
	#parse sar swapping
	./parse_sar.pl -i $input_dir/build.sar.data -out $output_dir/build.sar_swap -c "sar -W taken every 60 seconds" -op '-W'
	#generate data based on build sar .dat files
	./gr_single_dir.pl -i "$output_dir/build.sar.cpu*.dat" -o $output_dir/build.sar_cpu_user -t "build sar individual CPU pct_user" -b "build.sar." -e ".dat" -c 0 -hl "samples every 60 sec"
	
	./gr_single_dir.pl -i "$output_dir/build.sar.cpu*.dat" -o $output_dir/build.sar_cpu_system -t "build sar individual CPU pct_system" -b "build.sar." -e ".dat" -c 2 -hl "samples every 60 sec"
	
	if [ $VERSION -eq 5 ]
	then
		./gr_single_dir.pl -i "$output_dir/build.sar.cpu*.dat" -o $output_dir/build.sar_cpu_iowait -t "build sar individual CPU pct_iowait" -b "build.sar." -e ".dat" -c 3 -hl "samples every 60 sec"
	
		./gr_single_dir.pl -i "$output_dir/build.sar.cpu*.dat" -o $output_dir/build.sar_cpu_idle -t "build sar individual CPU pct_idle" -b "build.sar." -e ".dat" -c 4 -hl "samples every 60 sec"
		./gr_single_dir.pl -i "$output_dir/build.sar_cpu_all.dat" -o $output_dir/build.sar_cpu_all -t "build sar CPU" -b "build.sar_cpu_all" -e ".dat" -c 0,1,2,3,4 -hl "samples every 60 sec"
	else
		./gr_single_dir.pl -i "$output_dir/build.sar.cpu*.dat" -o $output_dir/build.sar_cpu_idle -t "build sar individual CPU pct_idle" -b "build.sar." -e ".dat" -c 3 -hl "samples every 60 sec"
		./gr_single_dir.pl -i "$output_dir/build.sar_cpu_all.dat" -o $output_dir/build.sar_cpu_all -t "build sar CPU" -b "build.sar_cpu_all" -e ".dat" -c 0,1,2,3 -hl "samples every 60 sec"
	fi
	
	./gr_single_dir.pl -i "$output_dir/build.sar_io.dat" -o $output_dir/build.sar_io -t "sar IO" -b "build.sar_io" -e ".dat" -c 0,1,2,3,4 -hl "samples every 60 sec"
	
	./gr_single_dir.pl -i "$output_dir/build.sar_memory.dat" -o $output_dir/build.sar_memory -t "build sar memory" -b "build.sar_memory" -e ".dat" -c 0,1,3,4,5,6,7 -hl "samples every 60 sec"
	
	./gr_single_dir.pl -i "$output_dir/build.sar_memory.dat" -o $output_dir/build.sar_memory_pct -t "build sar memory percentage" -b "build.sar_memory" -e ".dat" -c 2,8 -hl "samples every 60 sec"
fi


if [ -f $input_dir/run.sar.data ]; then
	echo "parse run sar -b";
	#parse sar io
	./parse_sar.pl -i $input_dir/run.sar.data -out $output_dir/run.sar_io -c "sar -b taken every 60 seconds" -op '-b'

	echo "parse run sar -r";
	#parse sar memory
	./parse_sar.pl -i $input_dir/run.sar.data -out $output_dir/run.sar_memory -c "sar -r taken every 60 seconds" -op '-r'

	echo "parse run sar -u";
	#parse sar total cpu
	./parse_sar.pl -i $input_dir/run.sar.data -out $output_dir/run.sar_cpu_all -c "sar -u taken every 60 seconds" -op '-u'

	if [ $sysstat_version = '4.1.2' ]
	then
		echo "parse run sar -P";
		#parse sar individual cpu
		./parse_sar.pl -i $input_dir/run.sar.data -out $output_dir/run.sar -c "sar -P taken every 60 seconds" -op '-P' -n $CPUS
	else
		echo "parse run sar -U";
		#parse sar individual cpu
		./parse_sar.pl -i $input_dir/run.sar.data -out $output_dir/run.sar -c "sar -U taken every 60 seconds" -op '-U' -n $CPUS
	fi

	echo "parse run sar -W";
	#parse sar swapping
	./parse_sar.pl -i $input_dir/run.sar.data -out $output_dir/run.sar_swap -c "sar -W taken every 60 seconds" -op '-W'

	#generate data based on run sar .dat files
	./gr_single_dir.pl -i "$output_dir/run.sar.cpu*.dat" -o $output_dir/run.sar_cpu_user -t "run sar individual CPU pct_user" -b "run.sar." -e ".dat" -c 0 -hl "samples every 60 sec"
	
	./gr_single_dir.pl -i "$output_dir/run.sar.cpu*.dat" -o $output_dir/run.sar_cpu_system -t "run sar individual CPU pct_system" -b "run.sar." -e ".dat" -c 2 -hl "samples every 60 sec"
	
	if [ $VERSION -eq 5 ]
	then
		./gr_single_dir.pl -i "$output_dir/run.sar.cpu*.dat" -o $output_dir/run.sar_cpu_iowait -t "run sar individual CPU pct_iowait" -b "run.sar." -e ".dat" -c 3 -hl "samples every 60 sec"
	
		./gr_single_dir.pl -i "$output_dir/run.sar.cpu*.dat" -o $output_dir/run.sar_cpu_idle -t "run sar individual CPU pct_idle" -b "run.sar." -e ".dat" -c 4 -hl "samples every 60 sec"
		./gr_single_dir.pl -i "$output_dir/run.sar_cpu_all.dat" -o $output_dir/run.sar_cpu_all -t "run sar CPU" -b "run.sar_cpu_all" -e ".dat" -c 0,1,2,3,4 -hl "samples every 60 sec"
	else
		./gr_single_dir.pl -i "$output_dir/run.sar.cpu*.dat" -o $output_dir/run.sar_cpu_idle -t "run sar individual CPU pct_idle" -b "run.sar." -e ".dat" -c 3 -hl "samples every 60 sec"
		./gr_single_dir.pl -i "$output_dir/run.sar_cpu_all.dat" -o $output_dir/run.sar_cpu_all -t "run sar CPU" -b "run.sar_cpu_all" -e ".dat" -c 0,1,2,3 -hl "samples every 60 sec"
	fi
	
	./gr_single_dir.pl -i "$output_dir/run.sar_io.dat" -o $output_dir/run.sar_io -t "sar IO" -b "run.sar_io" -e ".dat" -c 0,1,2,3,4 -hl "samples every 60 sec"
	
	./gr_single_dir.pl -i "$output_dir/run.sar_memory.dat" -o $output_dir/run.sar_memory -t "run.sar_memory" -b "sar_memory" -e ".dat" -c 0,1,3,4,5,6,7 -hl "samples every 60 sec"
	
	./gr_single_dir.pl -i "$output_dir/run.sar_memory.dat" -o $output_dir/run.sar_memory_pct -t "run sar memory percentage" -b "run.sar_memory" -e ".dat" -c 2,8 -hl "samples every 60 sec"
fi

#parse ips.csv output
if [ -f $input_dir/ips.csv ]; then
	echo "parse ips.csv";
	#parse vips.csv
	./parse_ips.pl -i $input_dir/ips.csv -o $output_dir/ips.dat -c "Transaction Per Second"

	#generate graphs based on build.vmstat.dat file
	./gr_single_dir.pl -i $output_dir/ips.dat -o $output_dir/ips -t "Transaction Per Second" -b "" -e "dat" -c 0,1
fi
