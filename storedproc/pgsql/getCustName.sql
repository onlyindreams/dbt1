--
--
-- This file is released under the terms of the Artistic License.  Please see
-- the file LICENSE, included in this package, for details.
--
-- Copyright (C) 2002 Mark Wong & Jenny Zhang &
--                    Open Source Development Lab, Inc.
-- Copyright (C) 2003 Satoshi Nagayasu
--
-- Usage:
-- select * from getCustName(11) as p(c_fname varchar(15), c_lname varchar(15));
-- 
CREATE OR REPLACE FUNCTION getCustName(NUMERIC(10,0)) RETURNS SETOF RECORD AS '
  SELECT c_fname,c_lname FROM customer WHERE c_id = $1;
' LANGUAGE 'SQL';
