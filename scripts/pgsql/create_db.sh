#! /bin/sh

# create_db.sh
#
# This file is released under the terms of the Artistic License.  Please see
# the file LICENSE, included in this package, for details.
#
# Copyright (C) 2002 Open Source Development Lab, Inc.
#
# History:
# Feb 2001: Original version created by Mark Wong & Jenny Zhang for SAPDB
# Apr 2003: Rewritten for PostgreSQL by
#           Virginie Megy & Thierry Missimilly
#                Bull, Linux Competence Center
# May 2003: Jenny Zhang created set_db_env
# June 2003: Merged NAGAYASU Satoshi's checking error code 

# pgsql does not create db successfully if createdb is moved to set_db_env.sh
./set_db_env.sh

# create database
echo "create database $SID1..."
_o=`createdb -U $USER $SID1 2>&1`
_test=`echo $_o | grep CREATE`
if [ "$_test" = "" ]; then
	echo "create $SID1 failed: $_o $_test"
	exit 1
fi

echo "create plpgsql on $SID1..."
_o=`createlang -U $USER -d $SID1 plpgsql 2>&1`
_test=`echo $_o`
if [ "$_test" != "" ]; then
	echo "create plpgsql on $SID1 failed: $_o $_test"
	exit 1
fi

# create database demo user
echo "create database demo user..."
_o=`psql -c "create user dbt" $SID1 2>&1`
_test=`echo $_o | grep CREATE`
if [ "$_test" = "" ]; then
	echo "create db user failed: $_o"
	exit 1
fi

exit 0
