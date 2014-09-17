#!/bin/sh

if [ $# -ne 1 ]; then
        echo "Usage: ./run_dbt1.sh <result_dir>"
        exit
fi

CPUS=`grep -c processor /proc/cpuinfo`
RESULTS_PATH=$1

runtime_env="LD_LIBRARY_PATH=$PGHOME/lib"

rm /tmp/*.log
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


# --------------------------------------------------------------
# Start appCache in background
# --------------------------------------------------------------
#see if appCache is running
cache_running=0
if [ "$cache_host" = "localhost" ]; then
    ps -ef |grep appCache > /tmp/cache_pid.log
else
    ssh  $cache_host "ps -ef |grep appCache" > /tmp/cache_pid.log
fi

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
	
	CMD="./appCache --dbhost $db_host --dbport ${PORT} --dbname $db_instance --dbuser $db_user --dbpass $db_password \
	              --port $cache_port --dbconn $cache_dbconnection --item_count $cache_items"
	echo $CMD

	if [ "$cache_host" = "localhost" ]; then
	    SHELL_EXEC="bash -c";
	else
	    SHELL_EXEC="ssh -n -f $cache_host";
	fi

	$SHELL_EXEC "cd $cache_dir; $runtime_env $CMD" > /tmp/cache.log &

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

# --------------------------------------------------------------
# Start appServer in background
# --------------------------------------------------------------
index=0
element_count=${#appServer_host[@]}
while [ "$index" -lt "$element_count" ]
do
	echo Starting appServer "$index"

	CMD="./appServer --dbhost $db_host --dbport ${PORT} --dbname $db_instance --dbuser $db_user --dbpass $db_password \
	               --server_port ${appServer_port[$index]} \
	               --dbconn ${appServer_dbconnection[$index]} \
	               --txn_q_size ${appServer_txn_q_size[$index]} \
	               --txn_a_size ${appServer_txn_a_size[$index]} \
	               --item_count ${dbdriver_items[$index]} \
	               --cache_host $cache_host --cache_port $cache_port \
	               --debug"
	echo $CMD

	if [ "${appServer_host[$index]}" = "localhost" ]; then
	    SHELL_EXEC="bash -c";
	else
	    SHELL_EXEC="ssh -n -f ${appServer_host[$index]}";
	fi

	$SHELL_EXEC "cd ${appServer_dir[$index]}; $runtime_env $CMD" > /tmp/appServer$index.log &

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
	
		if [ "$appServer_output" = "The app server is active..." ]
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

# --------------------------------------------------------------
# Start dbdriver in background
# --------------------------------------------------------------
echo 
index=0
element_count=${#appServer_host[@]}
while [ "$index" -lt "$element_count" ]
do
	echo Starting dbdriver "$index"

	if [ "${dbdriver_host[$index]}" = "localhost" ]; then
	    SHELL_EXEC="bash -c";
	else
	    SHELL_EXEC="ssh -n -f ${dbdriver_host[$index]}";
	fi

	CMD="./dbdriver --app_host ${appServer_host[$index]} \
	              --app_port ${appServer_port[$index]} \
	              --items ${dbdriver_items[$index]} \
	              --customers ${dbdriver_customers[$index]} \
	              --eus ${dbdriver_eus[$index]} \
	              --rampup_rate ${dbdriver_eus_per_min[$index]} \
	              --think_time ${dbdriver_think_time[$index]} \
	              --duration ${dbdriver_run_duration[$index]} \
	              --debug"

	$SHELL_EXEC "cd ${dbdriver_dir[$index]}; $runtime_env $CMD " \
	> /tmp/driver$index.log

let "index = $index + 1"
done 

# --------------------------------------------------------------
# Wait for all EUS to get connected to appServer.
# --------------------------------------------------------------
#read from the appServer.log and see if all users logged in
eus=${dbdriver_eus[0]}
while [ 1 ]
do
	read v1
	if [ "$v1" = "$eus client connections have been established." ]
		then break
	elif [ "$v1" = "" ]
	then
		# next line not arrived yet.
		sleep 2
		continue
	fi
done < /tmp/appServer0.log

echo "all EUS got connected."

# --------------------------------------------------------------
# Starts collecting data.
# --------------------------------------------------------------
echo all users started, start collecting data
#calculate the time window we need to collect system statistics
run_duration=${dbdriver_run_duration[0]}
interval=10
echo "run duration is $run_duration"
#leave 20 minutes for rampdown
if [ $run_duration -gt 1200 ]
then 
	let "collect_count = (run_duration-20*60)/interval"
else
	let "collect_count = (run_duration)/interval"
fi

if [ -d ${RESULTS_PATH} ]
then
	echo "$RESULTS_PATH exists"
else
	mkdir "$RESULTS_PATH"
fi
echo "./collect_data $interval $collect_count $CPUS $RESULTS_PATH"
# FIXME: collect_data.sh is still broken.
# ./collect_data.sh $interval $collect_count $CPUS $RESULTS_PATH

# --------------------------------------------------------------
# Wait for dbdriver completion.
# --------------------------------------------------------------
while [ 1 ]
do
	read v1

	if [ "$v1" = "Dbdriver ended" ]
		then break
	elif [ "$v1" = "" ]
	then
		# next line not arrived yet.
		sleep 2
		continue
	fi
done < /tmp/driver0.log

echo "dbdriver finished."

# --------------------------------------------------------------
# Collect and summarize stats data.
#
# At first, collects mix.log(s) generated by dbdriver from
# each server, and merge them into one log file.
#
# And then, run the `results' command to summarize it into
# `BT' and `ips.csv' files.
# --------------------------------------------------------------
#copy mix files
index=0
element_count=${#dbdriver_host[@]}
while [ "$index" -lt "$element_count" ]
do
	echo "copying mix.log from ${dbdriver_host[$index]}"

	if [ "${dbdriver_host[$index]}" = "localhost" ]; then
	    CP="cp ${dbdriver_dir[$index]}/mix.log $RESULTS_PATH/mix.log.${dbdriver_host[$index]}"
	else
	    CP="scp ${dbdriver_host[$index]}:${dbdriver_dir[$index]}/mix.log $RESULTS_PATH/mix.log.${dbdriver_host[$index]}"
	fi

	echo $CP
	bash -c "$CP"

	let "index = $index + 1"
done

#get the latest start time
start_time=`eval grep -h START $RESULTS_PATH/mix.log.* | sort -n -r|head -n1| awk -F, '{print $1}'`
echo "got latest start time $start_time"

#chop the mix.logs so that only the transactions after start_time is logged
index=0
element_count=${#dbdriver_host[@]}
while [ "$index" -lt "$element_count" ]
do
echo "chopping file mix.log.${dbdriver_host[$index]}"
cat $RESULTS_PATH/mix.log.${dbdriver_host[$index]} | awk -F, '{if ($1 > "'$start_time'") print $0}' > $RESULTS_PATH/result_mix.log.${dbdriver_host[$index]}
let "index = $index + 1"
done

#merge mix.log
echo "merging the logs..."
cat $RESULTS_PATH/result_mix.log.* | sort -n > $RESULTS_PATH/mix.log
#run results
echo "analyzing the logs..."
../../tools/results --mixfile $RESULTS_PATH/mix.log --outputdir $RESULTS_PATH

ls -l $RESULTS_PATH
