/*
/*
/* This file is released under the terms of the Artistic License.  Please see
/* the file LICENSE, included in this package, for details.
/*
/* Copyright (C) 2002 Mark Wong & Jenny Zhang &
/*                    Open Source Development Lab, Inc.
/*
/*/
CREATE DBPROC getCustName (IN C_ID fixed(10,0), OUT C_FName char(15), OUT C_LName char(15)) AS
BEGIN
SELECT c_fname, c_lname INTO :C_FName, :C_LName from dbt.customer where c_id=:C_ID;
END;;
/
/
