#!/bin/sh

if [ $# -ne 1 ]; then
        echo "Usage: ./get_xcons.sh <result_dir>"
        exit
fi

i=1
while [ $i -le 20 ] 
do
x_cons $SID1 show all > $1/x_cons$i.out
sleep 60
let "i=$i+1"
done
