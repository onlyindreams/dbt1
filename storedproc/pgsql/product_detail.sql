--
--
-- This file is released under the terms of the Artistic License.  Please see
-- the file LICENSE, included in this package, for details.
--
-- Copyright (C) 2002 Open Source Development Lab, Inc.
-- History:
-- July-2003: Created by Satoshi Nagayasu & Hideyuki Kawashima
--
--
\set AUTOCOMMIT off
CREATE OR REPLACE FUNCTION product_detail ( numeric(10) ) RETURNS RECORD AS '
  DECLARE
    _i_id ALIAS FOR $1;
  
    _i_title varchar(60);
    _a_fname varchar(20);
    _a_lname varchar(20);
    _i_pub_date varchar(10);
    _i_publisher varchar(60);
    _i_subject varchar(60);
    _i_desc varchar(500);
    _i_image numeric(10);
    _i_cost numeric(17, 2);
    _i_srp numeric(17, 2);
    _i_avail varchar(10);
    _i_isbn varchar(13);
    _i_page numeric(4);
    _i_backing varchar(15);
    _i_dimensions varchar(25);

    rec record;
 
  BEGIN
        SELECT i_title, a_fname, a_lname, 
               Cast(i_pub_date as char), i_publisher, i_subject,
               i_desc, i_image, i_cost,
               i_srp, Cast(i_avail as char), i_isbn,
               i_page, i_backing, i_dimensions 
        INTO _i_title, _a_fname, _a_lname, 
             _i_pub_date, _i_publisher, _i_subject,
             _i_desc, _i_image, _i_cost,
             _i_srp, _i_avail, _i_isbn,
             _i_page, _i_backing, _i_dimensions
	FROM item, author
	WHERE i_id = _i_id
	AND i_a_id = a_id;

	SELECT  _i_title::varchar(60), 
	  	_a_fname::varchar(20),
		_a_lname::varchar(20),
		_i_pub_date::varchar(10),
		_i_publisher::varchar(60),
		_i_subject::varchar(60),
		_i_desc::varchar(500),
		_i_image::numeric(10),
		_i_cost::numeric(17, 2),
		_i_srp::numeric(17, 2),
		_i_avail::varchar(10),
		_i_isbn::varchar(13),
		_i_page::numeric(4),
		_i_backing::varchar(15),
		_i_dimensions::varchar(25)

	INTO rec;

	RETURN rec;
 


  END;
' LANGUAGE 'plpgsql';
commit;


-- 
-- Usage:
-- 
-- SELECT * FROM product_detail( 
--         i_id FIXED(10) )
--   AS l( i_title VARCHAR(60),
--         a_fname VARCHAR(20),
--         a_lname VARCHAR(20),
--         i_pub_date VARCHAR(10),
--         i_publisher VARCHAR(60),
--         i_subject VARCHAR(60),
--         i_desc VARCHAR(500),
--         i_image FIXED(10),
--         i_cost FIXED(17,2),
--         i_srp FIXED(17,2),
--         i_avail VARCHAR(10),
--         i_isbn VARCHAR(13),
--         i_page FIXED(4),
--         i_backing VARCHAR(15),
--         i_dimensions VARCHAR(25) );

