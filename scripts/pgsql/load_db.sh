#!/bin/sh
# load_db.sh
#
# This file is released under the terms of the Artistic License.  Please see
# the file LICENSE, included in this package, for details.
#
# Copyright (C) 2002 Open Source Development Lab, Inc.
# Author: Jenny Zhang based on the scripts submitted by
#        Virginie Megy & Thierry Missimilly
#               Bull, Liux Competence Center
#
# 28 May 2003

psql -d $SID1 -f country.sql &
psql -d $SID1 -f author.sql & 
psql -d $SID1 -f orders.sql &
psql -d $SID1 -f order_line.sql & 
psql -d $SID1 -f cc_xacts.sql &
psql -d $SID1 -f address.sql &
psql -d $SID1 -f item.sql &
psql -d $SID1 -f customer.sql &
wait
