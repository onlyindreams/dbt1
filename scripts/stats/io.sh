#!/bin/sh

# Collect the first 60 minutes of data, at 30 second intervals, of extended
# I/O data.
iostat -d -x $1 $2 > io.txt

# Reformat the data into a comma delmited format after the run to minimize the
# CPU overhead.
cat io.txt | grep "\." | awk '{ print $1","$2","$3","$4","$5","$6","$7","$8","$9","$10","$11","$12 }' > io.csv
