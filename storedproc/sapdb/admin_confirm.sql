/*
/*
/* This file is released under the terms of the Artistic License.  Please see
/* the file LICENSE, included in this package, for details.
/*
/* Copyright (C) 2002 Mark Wong & Jenny Zhang &
/*                    Open Source Development Lab, Inc.
/*
/*/
/* Clause 2.16.3 */
/* Not complient. */
CREATE DBPROC admin_confirm(IN i_id FIXED(10),
INOUT i_image fixed(10), INOUT i_thumbnail FIXED(10),
INOUT i_cost FIXED (17, 2), OUT i_title VARCHAR(60), OUT a_fname VARCHAR(20),
OUT a_lname VARCHAR(20), OUT i_subject VARCHAR(60), OUT i_desc VARCHAR(500),
OUT i_srp FIXED(17, 2), OUT i_backing VARCHAR(15), OUT i_page FIXED(4),
OUT i_publisher VARCHAR(60), OUT i_pub_date VARCHAR(10),
OUT i_dimensions VARCHAR(25), OUT i_isbn VARCHAR(13)) AS
BEGIN
  UPDATE dbt.item (i_image, i_thumbnail, i_cost, i_pub_date)
  VALUES (:i_image, :i_thumbnail, :i_cost, DATE)
  WHERE i_id = :i_id;
  SELECT i_image, i_thumbnail, i_cost, i_title, a_fname, a_lname,
         i_subject, i_desc, i_srp, i_cost, i_backing, i_page,
         i_publisher, CHAR(i_pub_date, ISO), i_dimensions, i_isbn
  INTO :i_image, :i_thumbnail, :i_cost, :i_title, :a_fname, :a_lname,
       :i_subject, :i_desc, :i_srp, :i_cost, :i_backing, :i_page,
       :i_publisher, :i_pub_date, :i_dimensions, :i_isbn
  FROM dbt.item, dbt.author
  WHERE i_id = :i_id
    AND i_a_id = a_id;
END;;
