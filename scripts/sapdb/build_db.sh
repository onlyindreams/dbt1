#!/bin/sh
#this script is used to build the database
# ./build_db.sh -g <items> <eus> will generate data and build the database
# ./build_db.sh will load the database from previously generated data files

if [ $# -ne 0 ] # Script invoked with command-line args
then
	getopts "g" Option
	if [ $Option != "g" ]
		then echo "usage: $0 -g <items> <eus>" 
	else
		if [ $# -ne 3 ]
			then echo "usage: $0 -g <items> <eus>" 
		else
			ITEMS=$2
			EUS=$3	
		fi
	fi
	echo "Generating data... $ITEMS item and $EUS eu"
	cd ../../datagen
	date
	./datagen $ITEMS $EUS
	echo "data files are generated"
	date
else
	echo "build the database without generating the data files"
fi
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
	
	echo "starting to create indexes"
	date
	
	echo "creating indexes"
	./create_indexes.sh
	echo
	
	echo "starting to create keys"
	date
	
	echo "creating keys"
	./create_keys.sh
	echo
	
	echo "loading stored procedures"
	./load_dbproc.sh
	echo
	
	echo "starting to backup database"
	date
	
	echo "backup"
	./backup_db.sh
	echo
	
	date
