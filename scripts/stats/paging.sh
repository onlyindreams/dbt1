#!/bin/sh

# Collect the first 60 minutes of data, at 30 second intervals, of 
# memory paging data.
sar -B $1 $2 > paging.txt

# Reformat the data into a comma delmited format after the run to minimize the
# CPU overhead.
cat paging.txt | grep "\." | grep -v "^Average" | awk '{ print $3","$4","$5","$6","$7","$8 }' > paging.csv
