#!/bin/sh

ITEMS=1000
EUS=1

echo This is a sample script to create a database with $ITEMS items and $EUS emulated users.
echo

echo Generating data...
cd ../../datagen
./datagen $ITEMS $EUS
cd -
echo

echo Creating the database dev spaces...
./create_db.sh
echo

echo Creating the tables...
./create_tables.sh
echo

echo Loading the database...
./load_db.sh
echo

echo Creating indexes...
./create_indexes.sh
echo

echo Loading stored procedures...
./load_dbproc.sh
echo

echo Backing up database...
./backup_db.sh

