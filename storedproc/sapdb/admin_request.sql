/*
/*
/* This file is released under the terms of the Artistic License.  Please see
/* the file LICENSE, included in this package, for details.
/*
/* Copyright (C) 2002 Mark Wong & Jenny Zhang &
/*                    Open Source Development Lab, Inc.
/*
/*/
/* Clause 2.15.3 */
CREATE DBPROC admin_request(IN i_id FIXED(10), OUT i_srp FIXED(17, 2),
OUT i_cost FIXED(17, 2), OUT i_title VARCHAR(60), OUT i_image fixed(10),
OUT i_thumbnail fixed(10), OUT a_fname VARCHAR(20),
OUT a_lname VARCHAR(20)) AS
BEGIN
  SELECT i_srp, i_cost, i_title, i_image, i_thumbnail, a_fname, a_lname
  INTO :i_srp, :i_cost, :i_title, :i_image, :i_thumbnail, :a_fname, :a_lname
  FROM dbt.item, dbt.author
  WHERE i_id = :i_id AND i_a_id = a_id;
END;;
