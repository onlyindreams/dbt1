#!/bin/sh

SRCHOME=/usr/local/src/dbt1

EUS=100
ITEMS=1000
CUSTOMERS=28800

# Users per minute.
RAMPUP=60

# In seconds.
THINKTIME=7.5

# In seconds, 900s = 15min.
DURATION=900

CONNECT_STR=localhost:DBT1
DB_USER=dbt
DB_PASS=dbt
DB_CONN=2
APP_PORT=9997
Q_SIZE=100
T_SIZE=100
APP_HOST=localhost

SAMPLE_LENGTH=30
NUMBER_OF_SAMPLES=40

echo Starting data collection scripts...
cd $SRCHOME/scripts/stats
./cpu.sh $SAMPLE_LENGTH $NUMBER_OF_SAMPLES &
./io.sh $SAMPLE_LENGTH $NUMBER_OF_SAMPLES &
./paging.sh $SAMPLE_LENGTH $NUMBER_OF_SAMPLES &
echo

echo Starting appServer...
cd $SRCHOME/appServer
./appServer $CONNECT_STR $DB_USER $DB_PASS $APP_PORT $DB_CONN $Q_SIZE $T_SIZE &
echo

# Give the appServer some time to start up.
sleep 5

echo Starting driver...
cd $SRCHOME/dbdriver
./dbdriver_p2 $APP_HOST $APP_PORT $ITEMS $CUSTOMERS $EUS $RAMPUP $THINKTIME $DURATION
echo

echo Analyze data...
cd $SRCHOME/tools
./results ../dbdriver/mix.log
