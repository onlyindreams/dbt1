#!/bin/sh
# load_db.sh
#
# This file is released under the terms of the Artistic License.  Please see
# the file LICENSE, included in this package, for details.
#
# Copyright (C) 2002 Open Source Development Lab, Inc.
# History:
# Feb 2001: Original version created by Mark Wong & Jenny Zhang for SAPDB
# Apr 2003: Rewritten for PostgreSQL by
#           Virginie Megy & Thierry Missimilly
#                Bull, Linux Competence Center

psql -d $SID1 -f country.sql &
psql -d $SID1 -f author.sql & 
psql -d $SID1 -f orders.sql &
psql -d $SID1 -f order_line.sql & 
psql -d $SID1 -f cc_xacts.sql &
psql -d $SID1 -f address.sql &
psql -d $SID1 -f item.sql &
psql -d $SID1 -f customer.sql &
psql -d $SID1 -f create_sequence.sql &
wait
