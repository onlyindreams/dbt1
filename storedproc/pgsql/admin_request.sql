--
--
-- This file is released under the terms of the Artistic License.  Please see
-- the file LICENSE, included in this package, for details.
--
-- Copyright (C) Open Source Development Lab, Inc.
-- History:
-- July 2003 Created by 2003 Satoshi Nagayasu
--
--
CREATE OR REPLACE FUNCTION admin_request ( NUMERIC(10) ) RETURNS SETOF RECORD AS '
  DECLARE
    _i_id ALIAS FOR $1;
    rec RECORD;

  BEGIN
    SELECT i_srp, i_cost, i_title, i_image, i_thumbnail, a_fname, a_lname
      INTO rec
      FROM item, author
     WHERE i_id = _i_id AND i_a_id = a_id;
    RETURN NEXT rec;
    RETURN;
  END;
' LANGUAGE 'plpgsql';
commit;

-- 
-- Usage:
-- 
-- SELECT * FROM admin_request( 
--         NUMERIC(10) )
--   AS l( i_srp NUMERIC(17,2),
--         i_cost NUMERIC(17,2),
--         i_title VARCHAR(60),
--         i_image numeric(10),
--         i_thumbnail numeric(10),
--         a_fname VARCHAR(20),
--         a_lname VARCHAR(20) );

