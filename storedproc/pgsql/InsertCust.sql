--
--
-- This file is released under the terms of the Artistic License.  Please see
-- the file LICENSE, included in this package, for details.
--
-- Copyright (C) 2002 Open Source Development Lab, Inc.
-- History: 
-- July-2003: Created by Satoshi Nagayasu
--
--
--
CREATE OR REPLACE FUNCTION InsertCust ( varchar(50), varchar(40), varchar(40), varchar(30), varchar(20), varchar(10), varchar(15), varchar(15), varchar(16), varchar(50), varchar(500), numeric(10,0), numeric(5,2), char(8) ) RETURNS numeric(10,0) AS '
  DECLARE
    _Co_Name ALIAS FOR $1;
    _Addr_Street1 ALIAS FOR $2;
    _Addr_Street2 ALIAS FOR $3;
    _Addr_City ALIAS FOR $4;
    _Addr_State ALIAS FOR $5;
    _Addr_Zip ALIAS FOR $6;
    _C_FName ALIAS FOR $7;
    _C_LName ALIAS FOR $8;
    _C_Phone ALIAS FOR $9;
    _C_Email ALIAS FOR $10;
    _C_Data ALIAS FOR $11;
    _SC_ID ALIAS FOR $12;
    _C_Discount ALIAS FOR $13;
    _C_BirthDate ALIAS FOR $14;

    _C_Addr_ID numeric(10,0);
    _Co_ID smallint;
    _C_UName varchar(20);
    _C_PassWD char(20);
    _CurrentTime timestamp;
    _C_Expire timestamp;
    _CurrentDate date;
    _tmpdate date;

    _c_id numeric(10,0);
  BEGIN
    SELECT co_id INTO _Co_ID FROM country WHERE co_name=_Co_Name;
    SELECT addr_id INTO _C_Addr_ID FROM address
     WHERE addr_co_id   = _Co_ID
       AND addr_zip     = _Addr_Zip
       AND addr_state   = _Addr_State
       AND addr_city    = _Addr_City
       AND addr_street1 = _Addr_Street1
       AND addr_street2 = _Addr_Street2;

    IF NOT FOUND THEN
      _C_Addr_ID := nextval(''AddrID'');
      INSERT INTO address VALUES (_C_Addr_ID, _Addr_Street1, _Addr_Street2,
                                  _Addr_City, _Addr_State, _Addr_Zip, _Co_ID);
    END IF;

    _C_ID := nextval(''CustID'');

    SELECT DigSyl(_C_ID::integer, 0) INTO _C_UName;
    _C_PassWD := lower(_C_UName);
    _CurrentTime := now();
    _CurrentDate := now();
    _C_Expire := now() + ''02:00'';
    _tmpdate := _C_BirthDate;
--RAISE NOTICE ''c_uname=|%|'', _C_UNAME;

    INSERT INTO customer(c_id,c_uname,c_passwd,c_fname,c_lname,c_addr_id,
                         c_phone,c_email,c_since,c_last_visit,c_login,
                         c_expiration,c_discount, c_balance, c_ytd_pmt,
                         c_birthdate, c_data)
           VALUES (_C_ID, _C_UName, _C_PassWD, _C_FName, _C_LName, _C_Addr_ID,
                   _C_Phone, _C_Email, _CurrentDate,_CurrentDate, _CurrentTime,
                   _C_Expire, _C_Discount, 0.00, 0.00,
                   _tmpdate, _C_Data);

    RETURN _c_id;
  END;
' LANGUAGE 'plpgsql';
commit;

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

