/*
/*
/* This file is released under the terms of the Artistic License.  Please see
/* the file LICENSE, included in this package, for details.
/*
/* Copyright (C) 2002 Mark Wong & Jenny Zhang &
/*                    Open Source Development Lab, Inc.
/*
/*/
CREATE DBPROC createSC (IN C_ID fixed(10,0), OUT sc_id fixed(10,0)) AS
  VAR C_FName char(15); C_LName char(15); C_Discount fixed(5,2);
BEGIN
SELECT SCID.NEXTVAL into :sc_id from sysdba.dual;
IF C_ID <> 0 THEN BEGIN
  SELECT c_fname, c_lname, c_discount INTO :C_FName, :C_LName, :C_Discount
  FROM dbt.customer WHERE c_id=:C_ID;
  INSERT INTO dbt.shopping_cart(sc_id, sc_c_id, sc_date, sc_c_fname, 
    sc_c_lname, sc_c_discount) VALUES (:sc_id, :c_id, timestamp, :C_FName, 
    :C_LName, :C_Discount);
  END
ELSE
INSERT INTO dbt.shopping_cart(sc_id, sc_date) VALUES (:sc_id, timestamp);
END;;
/
/
