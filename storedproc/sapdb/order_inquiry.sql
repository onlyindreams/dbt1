/*
/*
/* This file is released under the terms of the Artistic License.  Please see
/* the file LICENSE, included in this package, for details.
/*
/* Copyright (C) 2002 Mark Wong & Jenny Zhang &
/*                    Open Source Development Lab, Inc.
/*
/*/
/* Clause 2.8.3 */
CREATE DBPROC order_inquiry(IN c_id FIXED(10, 0), OUT c_uname VARCHAR(20)) AS
BEGIN
  SELECT c_uname
  INTO :c_uname
  FROM dbt.customer WHERE c_id=:c_id;
END;;
