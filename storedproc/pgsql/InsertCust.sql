--
--
-- This file is released under the terms of the Artistic License.  Please see
-- the file LICENSE, included in this package, for details.
--
-- Copyright (C) 2002 Open Source Development Lab, Inc.
-- History:
-- Feb 2001: Created by Mark Wong & Jenny Zhang
-- Apr 2003: Rewritten for PostgreSQL by Virginie Megy & Thierry Missimilly
--                Bull, Linux Competence Center
-- June 2003: Rewritten by NAGAYASU Satoshi to return records
--
CREATE OR REPLACE FUNCTION InsertCust ( varchar(50), varchar(40), varchar(40), varchar(30), varchar(20), varchar(10), varchar(15), varchar(15), varchar(16), varchar(50), varchar(500), numeric(10,0), numeric(5,2), char(8) ) RETURNS numeric(10,0) AS '
  DECLARE
    Co_Name ALIAS FOR $1;
    Addr_Street1 ALIAS FOR $2;
    Addr_Street2 ALIAS FOR $3;
    Addr_City ALIAS FOR $4;
    Addr_State ALIAS FOR $5;
    Addr_Zip ALIAS FOR $6;
    C_FName ALIAS FOR $7;
    C_LName ALIAS FOR $8;
    C_Phone ALIAS FOR $9;
    C_Email ALIAS FOR $10;
    C_Data ALIAS FOR $11;
    SC_ID ALIAS FOR $12;
    C_Discount ALIAS FOR $13;
    C_BirthDate ALIAS FOR $14;

    C_Addr_ID numeric(10,0);
    Co_ID smallint;
    C_UName char(20);
    C_PassWD char(20);
    CurrentTime timestamp;
    C_Expire timestamp;
    CurrentDate date;
    tmpdate date;
  BEGIN
	SELECT INTO Co_ID co_id FROM country WHERE co_name=Co_Name;
    SELECT INTO C_Addr_ID addr_id  FROM address
     WHERE addr_co_id=Co_ID AND addr_zip=Addr_Zip AND
           addr_state=Addr_State AND addr_city=Addr_City AND
           addr_street1=Addr_Street1 AND addr_street2=Addr_Street2;
    IF NOT FOUND THEN
      C_Addr_ID = nextval(''AddrID'');
      INSERT INTO address VALUES (C_Addr_ID, Addr_Street1, Addr_Street2, Addr_City, Addr_State, Addr_Zip, Co_ID);
    END IF;
  END;
' LANGUAGE 'plpgsql';

-- SELECT CustID.NEXTVAL into :c_id from sysdba.dual;
-- CALL DigSyl(:C_ID, 0, :C_UName);
-- set C_PassWD=lower(C_UName);
-- set CurrentTime = timestamp;
-- set CurrentDate = date;
-- set C_Expire = addtime(CurrentTime, '00020000');
-- set tmpdate=C_BirthDate;
-- INSERT INTO dbt.customer(c_id, c_uname,c_passwd,c_fname,c_lname,c_addr_id,
--   c_phone,c_email,c_since,c_last_visit,c_login,c_expiration,c_discount,
--   c_balance, c_ytd_pmt, c_birthdate, c_data) values(:C_ID, :C_UName, :C_PassWD,
--   :C_FName, :C_LName, :C_Addr_ID, :C_Phone, :C_Email, :CurrentDate,
--   :CurrentDate, :CurrentTime, :C_Expire, :C_Discount, 0.00, 0.00,
--   :tmpdate, :C_Data);


-- 
-- Usage:
-- 
-- SELECT InsertCust(  Co_Name varchar(50),
--  Addr_Street1 varchar(40),
--  Addr_Street2 varchar(40),
--  Addr_City varchar(30),
--  Addr_State varchar(20),
--  Addr_Zip varchar(10),
--  C_FName varchar(15),
--  C_LName varchar(15),
--  C_Phone varchar(16),
--  C_Email varchar(50),
--  C_Data varchar(500),
--  SC_ID numeric(10,0),
--  C_Discount fixed(5,2),
--  C_BirthDate char(8) );

