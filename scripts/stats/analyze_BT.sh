#!/bin/sh

declare -a dbdriver_host
declare -a dbdriver_dir

OIFS=$IFS; IFS=:       # dbt1.config uses ":" for field separator.

echo reading from dbdriver.config
while read var1
do
	if [ "$var1" == [dbdriver] ]
	then
		read #skip the comment
		read -a dbdriver_host
		read #skip the comment
		read -a dbdriver_dir
		element_count=${#appServer_host[@]}
		index=0
		while [ "$index" -lt "$element_count" ]
		do  # List all the elements in the array.
			echo dbdriver "$index"
			echo ${dbdriver_host[$index]} ${dbdriver_dir[$index]}
			let "index = $index + 1"
		done 
	fi
done <./dbdriver.config   # I/O redirection.

IFS=$OIFS              # Restore originial $IFS.

#copy mix files
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
../../tools/results ./mix.log > BT
