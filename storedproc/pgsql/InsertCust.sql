/*
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2002 Mark Wong & Jenny Zhang &
 *                    Open Source Development Lab, Inc.
 * Contributors : Virginie Megy & Thierry Missimilly
 *		  Bull, Linux Competence Center
 *
 */
CREATE FUNCTION InsertCust(varchar(50), varchar(40), varchar(40),
			varchar(30), varchar(20), varchar(10),
			varchar(15), varchar(15), varchar(16),
			varchar(50), varchar(500),numeric(10,0), numeric(5,2),
			char(8)) RETURNS NUMERIC(10,0) AS '

DECLARE

	Country_Name alias for $1;
	Addresse_Street1 alias for $2;
	Addresse_Street2 alias for $3;
	Addresse_City alias for $4;
	Addresse_State alias for $5;
	Addresse_Zip alias for $6;
	Cust_FName alias for $7;
	Cust_LName alias for $8;
	Cust_Phone alias for $9;
	Cust_Email alias for $10;
	Cust_Data alias for $11;
	Shopcart_ID alias for $12;
	Cust_Discount alias for $13;
	Cust_BirthDate alias for $14;
	Cust_ID numeric(10,0);

	Cust_Addr_ID numeric(10,0);
	Country_ID smallint;
	Cust_UName char(20);
	Cust_PassWD char(20);
      	CurrentTime timestamp;
	Cust_Expire timestamp;
	CurrentDate date;
	tmpdate date;

BEGIN
SELECT co_id INTO Country_ID FROM country WHERE co_name=Country_Name;
SELECT addr_id INTO Cust_Addr_ID FROM address
 WHERE addr_co_id=Country_ID AND addr_zip=Addresse_Zip AND
       addr_state=Addresse_State AND addr_city=Addresse_City AND
       addr_street1=Addresse_Street1 AND addr_street2=Addresse_Street2;
IF FOUND THEN
  Cust_Addr_ID := nextval(''addrid'');
  INSERT INTO address VALUES (Cust_Addr_ID, Addresse_Street1, Addresse_Street2, Addresse_City, Addresse_State, Addresse_Zip, Country_ID);
END If;
Cust_id := nextval(''custid'');
Cust_UName := DigSyl(Cust_id,0);
Cust_PassWD:=lower(Cust_UName);
CurrentTime := ''now'';
CurrentDate := current_date;
-- Change Cust_Expire := CurrentTime + ''00020000'' by using addTime() function;
Cust_Expire := ''tomorrow'';
tmpdate:= Cust_BirthDate;
INSERT INTO customer(c_id, c_uname,c_passwd,c_fname,c_lname,c_addr_id,
  c_phone,c_email,c_since,c_last_visit,c_login,c_expiration,c_discount,
  c_balance, c_ytd_pmt, c_birthdate, c_data) values(Cust_ID, Cust_UName, Cust_PassWD,
  Cust_FName, Cust_LName, Cust_Addr_ID, Cust_Phone, Cust_Email, CurrentDate,
  CurrentDate, CurrentTime, Cust_Expire, Cust_Discount, 0.00, 0.00,
  tmpdate, Cust_Data);
RETURN Cust_id;
END;
'LANGUAGE 'plpgsql'
