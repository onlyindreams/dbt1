#!/bin/sh
#this script can be used to build the database

if [ $# -ne 0 ] # Script invoked with command-line args
then
	getopts "g" Option
	if [ $Option != "g" ]
		then echo "usage: $0 -g <items> <eus>" 
		exit
	else
		if [ $# -ne 7 ]
			then echo "usage: $0 -g -i <items> -u <eus> -p <path>" 
			exit
		else
			ITEMS=$3
			EUS=$5	
			PATH=$7
		fi
	fi
	echo "Generating data... $ITEMS item and $EUS eu"
	cd ../../datagen
	date
	./datagen -i $ITEMS -u $EUS -p $PATH
	echo "data file is generated"
	date
	cd -
else
	echo "build the database without generating the data file"
fi
	date
	echo "drop db"
	./drop_db.sh
	echo
	
	date
	echo "create db"
	./create_db.sh
	echo
	
	date
	echo "create tables"
	./create_tables.sh
	echo
	
	date
	echo "load db"
	./load_db.sh
	echo

	echo "backup so that we can add foreign key"
	./backup_db.sh
	echo
	
	date
	echo "create foreign key"
	./create_fk.sh
	echo

	date
	echo "create indexes"
	./create_indexes.sh
	echo
	
	date
	echo "create prejoined tables for large database"
	./add_aux_structure.sh
	echo
	
	date
	echo "update statistics"
	./update_stats.sh
	echo
	
	date
	echo "load dbproc"
	./load_dbproc.sh
	echo
	
	echo "start to backup"
	date
	
	echo "backup"
	./backup_db.sh
	echo
	
	date
