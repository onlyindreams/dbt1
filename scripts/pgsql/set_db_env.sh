#! /bin/sh

# set_db_env.sh
#
# This file is released under the terms of the Artistic License.  Please see
# the file LICENSE, included in this package, for details.
#
# Copyright (C) 2002 Open Source Development Lab, Inc.
# Author: Jenny Zhang based on the scripts submitted by
#	 Virginie Megy & Thierry Missimilly
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
export PGPORT=5433

# create Postgres DBT1 database
echo "Creating database..."
if [ -d $PGDATA ] ; then
echo "======================================="
echo "PGData directory $PGDATA already exists"
echo "Skipping initdb"
echo "======================================="
else
initdb -D $PGDATA
fi

pg_ctl start -l logfile -D $PGDATA
