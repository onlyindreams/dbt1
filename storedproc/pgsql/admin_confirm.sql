--
--
-- This file is released under the terms of the Artistic License.  Please see
-- the file LICENSE, included in this package, for details.
--
-- Copyright (C) 2002 Open Source Development Lab, Inc.
-- History:
-- Feb 2001: Created by Mark Wong & Jenny Zhang
-- Apr 2003: Rewritten for PostgreSQL by Virginie Megy & Thierry Missimilly
--		  Bull, Linux Competence Center
-- June 2003: Rewritten by NAGAYASU Satoshi to return records
--
CREATE OR REPLACE FUNCTION admin_confirm ( NUMERIC(10), numeric(10), NUMERIC(10), NUMERIC (17,2) ) RETURNS SETOF RECORD AS '
  DECLARE
    _i_id ALIAS FOR $1;
    _i_image ALIAS FOR $2;
    _i_thumbnail ALIAS FOR $3;
    _i_cost ALIAS FOR $4;

    rec RECORD;

  BEGIN
    UPDATE item SET i_image=_i_image, i_thumbnail=_i_thumbnail,
                    i_cost=_i_cost, i_pub_date=now()
     WHERE i_id = _i_id;

    SELECT INTO rec i_image, i_thumbnail, i_cost, i_title, a_fname, a_lname,
                    i_subject, i_desc, i_srp, i_backing, i_page,
                    i_publisher, i_pub_date, i_dimensions, i_isbn
      FROM item, author
     WHERE i_id = _i_id
       AND i_a_id = a_id;

    RETURN NEXT rec;
    RETURN;
  END;
' LANGUAGE 'plpgsql';

-- 
-- Usage:
-- 
-- SELECT * FROM admin_confirm( 
--         i_id NUMERIC(10)
--         i_image numeric(10)
--         i_thumbnail NUMERIC(10)
--         i_cost NUMERIC (17,2) )
--   AS l( i_image numeric(8),
--         i_thumbnail NUMERIC(8),
--         i_cost NUMERIC (17,2),
--         i_title VARCHAR(60),
--         a_fname VARCHAR(20),
--         a_lname VARCHAR(20),
--         i_subject VARCHAR(60),
--         i_desc VARCHAR(500),
--         i_srp NUMERIC(17,2),
--         i_backing VARCHAR(15),
--         i_page NUMERIC(4),
--         i_publisher VARCHAR(60),
--         i_pub_date date,
--         i_dimensions VARCHAR(25),
--         i_isbn CHAR(13) );

