#!/bin/sh
#this script can be used to build the database

if [ $# -ne 0 ] # Script invoked with command-line args
then
	getopts "g" Option
	if [ $Option != "g" ]
		then echo "usage: $0 -g <items> <eus>" 
		exit
	else
		if [ $# -ne 3 ]
			then echo "usage: $0 -g <items> <eus>" 
			exit
		else
			ITEMS=$2
			EUS=$3	
		fi
	fi
	echo "Generating data... $ITEMS item and $EUS eu"
	cd ../../datagen
	date
	./datagen $ITEMS $EUS
	echo "data file is generated"
	date
	cd -
else
	echo "build the database without generating the data file"
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
	
	echo "start to create index"
	date
	
	echo "create indexes"
	./create_indexes.sh
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
