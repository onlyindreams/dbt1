/*
/*
/* This file is released under the terms of the Artistic License.  Please see
/* the file LICENSE, included in this package, for details.
/*
/* Copyright (C) 2002 Mark Wong & Jenny Zhang &
/*                    Open Source Development Lab, Inc.
/*
/*/
/* Clause 2.14.3 */
CREATE DBPROC product_detail(IN i_id FIXED(10), OUT i_title VARCHAR(60),
OUT a_fname VARCHAR(20), OUT a_lname VARCHAR(20), OUT i_pub_date VARCHAR(10),
OUT i_publisher VARCHAR(60), OUT i_subject VARCHAR(60),
OUT i_desc VARCHAR(500), OUT i_image FIXED(10), OUT i_cost FIXED(17, 2),
OUT i_srp FIXED(17, 2), OUT i_avail VARCHAR(10), OUT i_isbn VARCHAR(13),
OUT i_page FIXED(4), OUT i_backing VARCHAR(15),
OUT i_dimensions VARCHAR(25)) AS
BEGIN
  SELECT i_title, a_fname, a_lname, CHAR(i_pub_date, ISO), i_publisher,
         i_subject, i_desc, i_image, i_cost, i_srp, CHAR(i_avail, ISO),
         i_isbn, i_page, i_backing, i_dimensions 
  INTO :i_title, :a_fname, :a_lname, :i_pub_date, :i_publisher, :i_subject,
       :i_desc, :i_image, :i_cost, :i_srp, :i_avail, :i_isbn, :i_page,
       :i_backing, :i_dimensions 
  FROM dbt.item, dbt.author
  WHERE i_id = :i_id
    AND i_a_id = a_id;
END;;
