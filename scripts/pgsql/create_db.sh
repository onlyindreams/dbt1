#! /bin/sh

# create_db.sh
#
# This file is released under the terms of the Artistic License.  Please see
# the file LICENSE, included in this package, for details.
#
# Copyright (C) 2002 Open Source Development Lab, Inc.
# Author: Jenny Zhang
#
# 28 May 2003

# pgsql does not create db successfully if createdb is moved to set_db_env.sh
./set_db_env.sh
createdb $SID1
