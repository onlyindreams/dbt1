#!/bin/sh
#this script can be used to build the database

date

echo "drop db"
./drop_db.sh
echo

echo "create db"
./create_db.sh
echo

echo "create tables"
./create_tables.sh
echo

echo "start to load db"
date

echo "load db"
./load_db.sh
echo

echo "start to create index"
date

echo "create indexes"
./create_indexes.sh
echo

echo "start to create keys"
date

echo "create keys"
./create_keys.sh
echo

echo "create sequences"
./create_sequences.sh
echo

echo "load dbproc"
./load_dbproc.sh
echo

echo "start to backup"
date

echo "backup"
./backup_db.sh
echo

date
