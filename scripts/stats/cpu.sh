#!/bin/sh

# Collect the first 60 minutes of data of CPU data, at 30 second intervals.
iostat -c $1 $2 > cpu.txt

# Reformat the data into a comma delmited format after the run to minimize the
# CPU overhead.
cat cpu.txt | grep "\." | awk '{ print $1","$2","$3","$4 }' > cpu.csv
