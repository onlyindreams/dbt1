#! /bin/sh

# set_db_env.sh
#
# This file is released under the terms of the Artistic License.  Please see
# the file LICENSE, included in this package, for details.
#
# Copyright (C) 2002 Open Source Development Lab, Inc.
# Author: Jenny Zhang, NAGAYASU Satoshi
#
# Contributer: Virginie Megy & Thierry Missimilly
#               Bull, Liux Competence Center
#
# 28 May 2003

# dont start script as root!
id=`id | sed s/\(.*// | sed s/uid=//`

if [ "$id" = "0" ]; then
	echo "dont start script as root"
	exit 1
fi

export PATH=/usr/local/pgsql/bin:$PATH

# Postgres env for the database (directory where to put the database files)
export PGDATA=/dbt1/pgsql

echo "shutting down postgresql server..."
pg_ctl stop > /dev/null 2>&1

# remove and create directory where to put the database files
echo "removing existing database cluster..."
rm -rf $PGDATA
mkdir -p $PGDATA

# initialize database cluster
echo "initializing database cluster..."
initdb -D $PGDATA > /dev/null 2>&1

# start remote communication server
echo "start postgresql server..."
pg_ctl start -o -i -l logfile > /dev/null 2>&1
