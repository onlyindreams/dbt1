#!/bin/sh

if [ $# -ne 1 ]; then
        echo "Usage: ./run_dbt1.sh <result_dir>"
        exit
fi

CPUS=`grep -c processor /proc/cpuinfo`
RESULTS_PATH=$1

#rm /tmp/*.log
#
# Use $IFS (Internal File Separator variable) to split a line of input to
# "read", if you do not want the default to be whitespace.

OIFS=$IFS; IFS=:       # dbt1.config uses ":" for field separator.

declare -a appServer_host
declare -a appServer_port
declare -a appServer_dbconnection
declare -a appServer_txn_q_size
declare -a appServer_txn_a_size
declare -a appServer_items
declare -a appServer_dir

declare -a dbdriver_host
declare -a dbdriver_items
declare -a dbdriver_customers
declare -a dbdriver_eus
declare -a dbdriver_eus_per_min
declare -a dbdriver_think_time
declare -a dbdriver_run_duraion
declare -a dbdriver_dir

echo reading from dbt1.config
while read var1
do
	if [ "$var1" == [database] ]
	then
		read #skip the comment
		read db_host db_instance db_user db_password
		echo "db: $db_host $db_instance $db_user $db_password"
	fi
	if [ "$var1" == [cache] ]
	then
		read #skip the comment
		read cache_host cache_port cache_dbconnection cache_items cache_dir
		echo "cache: $cache_host $cache_port $cache_dbconnection $cache_items $cache_dir"
	fi
	if [ "$var1" == [appServer] ]
	then
		read #skip the comment
		read -a appServer_host
		read #skip the comment
		read -a appServer_port
		read #skip the comment
		read -a appServer_dbconnection
		read #skip the comment
		read -a appServer_txn_q_size
		read #skip the comment
		read -a appServer_txn_a_size
		read #skip the comment
		read -a appServer_items
		read #skip the comment
		read -a appServer_dir
		element_count=${#appServer_host[@]}
		index=0
		while [ "$index" -lt "$element_count" ]
		do  # List all the elements in the array.
		   echo appServer "$index"
		   echo ${appServer_host[$index]} ${appServer_port[$index]} ${appServer_dbconnection[$index]} ${appServer_txn_q_size[$index]} ${appServer_txn_a_size[$index]} ${appServer_items[$index]} ${appServer_dir[$index]}
		   let "index = $index + 1"
		done 
	fi
	if [ "$var1" == [dbdriver] ]
	then
		read #skip the comment
		read -a dbdriver_host
		read #skip the comment
		read -a dbdriver_items
		read #skip the comment
		read -a dbdriver_customers
		read #skip the comment
		read -a dbdriver_eus
		read #skip the comment
		read -a dbdriver_eus_per_min
		read #skip the comment
		read -a dbdriver_think_time
		read #skip the comment
		read -a dbdriver_run_duration
		read #skip the comment
		read -a dbdriver_dir
		element_count=${#appServer_host[@]}
		index=0
		while [ "$index" -lt "$element_count" ]
		do  # List all the elements in the array.
			echo dbdriver "$index"
			echo ${dbdriver_host[$index]} ${dbdriver_items[$index]} ${dbdriver_customers[$index]} ${dbdriver_eus[$index]} ${dbdriver_eus_per_min[$index]} ${dbdriver_think_time[$index]} ${dbdriver_run_duration[$index]} ${dbdriver_dir[$index]}
			let "index = $index + 1"
		done 
	fi
done <./dbt1.config   # I/O redirection.

IFS=$OIFS              # Restore originial $IFS.


#see if appCache is running
cache_running=0
ssh  sapdb@$cache_host "ps -ef |grep appCache" > /tmp/cache_pid.log
while read v1 v2 v3 v4 v5 v6 v7 v8 v9
do
	if [ "$v1" = "" ]
	then 
		sleep 2
		continue
	fi

	if [ "$v8" = "./appCache" ]
	then 
		cache_running=1
		break;
	fi
done < /tmp/cache_pid.log

#if appCache is running...
if [ $cache_running -eq 1 ]
then 
	echo appCache is running
else # start appCache
	echo 
	echo Starting appCache
	
	ssh -n -f sapdb@$cache_host "cd $cache_dir; ./appCache $db_host:$db_instance $db_user $db_password $cache_port $cache_dbconnection $cache_items" > /tmp/cache.log
	sleep 2
	while [ 1 ]
	do
		read cache_output
		echo "$cache_output"
		if [ "$cache_output" = "" ] 
		then 
			sleep 10  #if no output, wait
			continue
		fi
	
		if [ "$cache_output" = "The cache server is active..." ]
		then break
		else
			#echo "stipping cache_output"
			#strip cache_output from the last longest 'failed'
			v1=${cache_output%%*failed*}
			echo "v1 is $v1"
			#if failed is in cache_output
			if [ "$v1" = "" ]
			then
				echo "appCache failed"
				exit
			fi
		fi
	done < /tmp/cache.log
fi

echo appCache is active
echo 

index=0
element_count=${#appServer_host[@]}
while [ "$index" -lt "$element_count" ]
do
	echo Starting appServer "$index"
	ssh -n -f sapdb@${appServer_host[$index]} "cd ${appServer_dir[$index]}; ./appServer $db_host:$db_instance $db_user $db_password ${appServer_port[$index]} ${appServer_dbconnection[$index]} ${appServer_txn_q_size[$index]} ${appServer_txn_a_size[$index]} ${dbdriver_items[$index]} $cache_host $cache_port" > /tmp/appServer$index.log
	sleep 2
	while [ 1 ]
	do
		read appServer_output
		echo "$appServer_output"
		if [ "$appServer_output" = "" ] 
		then 
			sleep 10  #if no output, wait
			continue
		fi
	
		if [ "$appServer_output" = "The server is active..." ]
		then 
			echo "appServer $index started"
			break
		else
			#echo "stipping appServer_output"
			#strip appServer_output from the last longest 'failed'
			v1=${appServer_output%%*failed*}
			#echo "v1 is $v1"
			#if failed is in appServer_output
			if [ "$v1" = "" ]
			then
				echo "appServer failed"
				exit
			fi
		fi
	done < /tmp/appServer$index.log
	let "index = $index + 1"
done 

echo 
index=0
element_count=${#appServer_host[@]}
while [ "$index" -lt "$element_count" ]
do
	echo Starting dbdriver "$index"
	ssh -n -f sapdb@${dbdriver_host[$index]} "cd ${dbdriver_dir[$index]}; ./dbdriver_p2 ${appServer_host[$index]} ${appServer_port[$index]} ${dbdriver_items[$index]} ${dbdriver_customers[$index]} ${dbdriver_eus[$index]} ${dbdriver_eus_per_min[$index]} ${dbdriver_think_time[$index]} ${dbdriver_run_duration[$index]}" > /tmp/driver$index.log
let "index = $index + 1"
done 

#estimate how long it takes for all users logging in
#using parameters from one dbdriver
let "rampup_time = ${dbdriver_eus[0]}/${dbdriver_eus_per_min[0]}"
#convert it to seconds
let "rampup_time = rampup_time*60"
echo "sleep for ramp up time $rampup_time"
#sleep $rampup_time

#read from the appServer.log and see if all users logged in
eus=${dbdriver_eus[0]}
echo "wait for $eus users login"
while [ 1 ]
do
	read v1 v2
	echo "first var is $v1"
	#skip the first line
	if [ "$v1" = "The" ]
		then continue
	else
		if [ "$v1" = "" ] 
		then 
			sleep 10
			continue
		else
			if [ "$v1" = "$eus" ] 
			then 
				break
			fi
		fi
	fi
done < /tmp/appServer0.log

echo all users started, start collecting data
#calculate the time window we need to collect system statistics
run_duration=${dbdriver_run_duration[0]}
echo "run duration is $run_duration"
#leave 20 minutes for rampdown
if [ $run_duration -gt 1200 ]
then 
	let "collect_count = (run_duration-20*60)/10"
else
	let "collect_count = (run_duration)/10"
fi

if [ -d ${RESULTS_PATH} ]
then
	echo "$RESULTS_PATH exists"
else
	mkdir "$RESULTS_PATH"
fi
echo "./collect_data 10 $collect_count $CPUS $RESULTS_PATH"
./collect_data.sh 10 $collect_count $CPUS $RESULTS_PATH

#wait for run to stop
let sleep_sec=$run_duration-$collect_count*10
echo "waiting for the run to finish, sleep for $sleep_sec..."
sleep $sleep_sec

#copy mix files
cd $RESULTS_PATH
index=0
element_count=${#dbdriver_host[@]}
while [ "$index" -lt "$element_count" ]
do
	echo "copying mix.log from ${dbdriver_host[$index]}"
	scp sapdb@${dbdriver_host[$index]}:"${dbdriver_dir[$index]}/mix.log" ./mix.log.${dbdriver_host[$index]}
	let "index = $index + 1"
done

#get the latest start time
start_time=`eval grep -h START mix.log.* | sort -n -r|head -n1| awk -F, '{print $1}'`
echo "got latest start time $start_time"

#chop the mix.logs so that only the transactions after start_time is logged
index=0
element_count=${#dbdriver_host[@]}
while [ "$index" -lt "$element_count" ]
do
echo "chopping file mix.log.${dbdriver_host[$index]}"
cat mix.log.${dbdriver_host[$index]} | awk -F, '{if ($1 > "'$start_time'") print $0}' > result_mix.log.${dbdriver_host[$index]}
let "index = $index + 1"
done

#merge mix.log
echo "merging the logs..."
cat result_mix.log.*|sort -n>mix.log
#run results
echo "analyzing the logs..."
../../../tools/results ./mix.log > BT
