/*
/*
/* This file is released under the terms of the Artistic License.  Please see <  * the file LICENSE, included in this package, for details.
/*
/* Copyright (C) 2002 Mark Wong & Jenny Zhang &
/*                    Open Source Development Lab, Inc.
/*
/*/
/
/*DROP DBPROC InsertCust;*/
/
CREATE DBPROC InsertCust(IN Co_Name varchar(50),
IN Addr_Street1 varchar(40), IN Addr_Street2 varchar(40),
IN Addr_City varchar(30), IN Addr_State varchar(20),
IN Addr_Zip varchar(10), IN C_FName varchar(15),
IN C_LName varchar(15), IN C_Phone varchar(16),
IN C_Email varchar(50), IN C_Data varchar(500), 
IN SC_ID fixed(10,0), IN C_Discount fixed(5,2), 
IN C_BirthDate char(8), OUT C_ID fixed(10,0)) AS
  VAR C_Addr_ID fixed(10,0); Co_ID smallint;
      C_UName char(20); C_PassWD char(20);
      CurrentTime timestamp; C_Expire timestamp; CurrentDate date;
      tmpdate date;
BEGIN
SELECT co_id INTO :Co_ID FROM dbt.country WHERE co_name=:Co_Name;
SELECT addr_id INTO :C_Addr_ID FROM dbt.address
 WHERE addr_co_id=:Co_ID AND addr_zip=:Addr_Zip AND
       addr_state=:Addr_State AND addr_city=:Addr_City AND
       addr_street1=:Addr_Street1 AND addr_street2=:Addr_Street2;
IF $rc=100 THEN BEGIN
  set C_Addr_ID = AddrID.NEXTVAL;
  INSERT INTO dbt.address VALUES (:C_Addr_ID, :Addr_Street1, :Addr_Street2,  :Addr_City, :Addr_State, :Addr_Zip, :Co_ID);
END;
SELECT CustID.NEXTVAL into :c_id from sysdba.dual;
CALL DigSyl(:C_ID, 0, :C_UName);
set C_PassWD=lower(C_UName);
set CurrentTime = timestamp;
set CurrentDate = date;
set C_Expire = addtime(CurrentTime, '00020000');
set tmpdate=C_BirthDate;
INSERT INTO dbt.customer(c_id, c_uname,c_passwd,c_fname,c_lname,c_addr_id,
  c_phone,c_email,c_since,c_last_visit,c_login,c_expiration,c_discount,
  c_balance, c_ytd_pmt, c_birthdate, c_data) values(:C_ID, :C_UName, :C_PassWD,
  :C_FName, :C_LName, :C_Addr_ID, :C_Phone, :C_Email, :CurrentDate,
  :CurrentDate, :CurrentTime, :C_Expire, :C_Discount, 0.00, 0.00,
  :tmpdate, :C_Data);
END;
;
/
/
