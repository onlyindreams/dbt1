/*
/*
/* This file is released under the terms of the Artistic License.  Please see
/* the file LICENSE, included in this package, for details.
/*
/* Copyright (C) 2002 Mark Wong & Jenny Zhang &
/*                    Open Source Development Lab, Inc.
/*
/*/
CREATE DBPROC getCustInfo (IN C_UName char(20),
OUT C_ID fixed(10,0),
OUT C_PassWD varchar(20), OUT C_FName char(15), OUT C_LName char(15),
OUT Addr_Street1 varchar(40), OUT Addr_Street2 varchar(40),
OUT Addr_City varchar(30), OUT Addr_State varchar(20),
OUT Addr_Zip varchar(10), OUT Co_Name varchar(50), OUT C_Phone varchar(16),
OUT C_Email varchar(50), OUT C_Data varchar(500), OUT C_BirthDate char(10), 
OUT c_discount fixed(5,2)) AS
  VAR C_Addr_ID fixed(10,0); 
BEGIN
SELECT c_id, c_passwd, c_fname, c_lname, c_phone, c_email, 
  c_addr_id, c_data, CHAR(c_birthdate, ISO), c_discount 
INTO :C_ID, :C_PassWD, :C_FName, :C_LName, 
  :C_Phone, :C_Email, :C_Addr_ID, :C_Data, :C_BirthDate, :c_discount
FROM dbt.CUSTOMER
WHERE c_uname = :C_UName;
UPDATE dbt.customer set c_login=(timestamp), c_expiration=(addtime(timestamp,
'00020000')) WHERE c_id = :C_ID;
SELECT addr_street1, addr_street2, addr_city, addr_state, addr_zip, co_name
INTO :Addr_Street1, :Addr_Street2, :Addr_City, :Addr_State, :Addr_Zip,
     :Co_Name
FROM dbt.address, dbt.country
WHERE addr_id = :C_Addr_ID and addr_co_id=co_id;
END;;
/
/
