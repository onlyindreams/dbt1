--
--
-- This file is released under the terms of the Artistic License.  Please see
-- the file LICENSE, included in this package, for details.
--
-- Copyright (C) 2002 Open Source Development Lab, Inc.
-- History: 
-- July-2003: Created by Satoshi Nagayasu
--
-- -
CREATE OR REPLACE FUNCTION order_inquiry (
  NUMERIC(10, 0)
) RETURNS VARCHAR(20) AS '
  DECLARE
	i_c_id ALIAS FOR $1;
	o_c_uname VARCHAR(20);
  BEGIN
	SELECT c_uname INTO o_c_uname
	FROM customer WHERE c_id=i_c_id;

	RETURN o_c_uname;
  END;
' LANGUAGE 'plpgsql';
commit;
-- Usage:
-- 
-- SELECT * FROM (
--    c_id numeric(10, 0),
-- )
-- AS l(
--    c_uname VARCHAR(20),
--);

