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
-- SELECT * FROM getCustInfo('OG') l(c_id numeric(10), c_passwd varchar(20), c_fname varchar(15), c_lname varchar(15), addr_street1 varchar(40), addr_street2 varchar(40), addr_city varchar(30), addr_state varchar(20), addr_zip varchar(10), co_name varchar(50), c_phone varchar(16), c_email varchar(50), c_data varchar(500), c_birthdate date, c_discount numeric(5,2));
--

CREATE OR REPLACE FUNCTION getCustInfo (VARCHAR(20)) RETURNS SETOF RECORD AS '
  DECLARE
    rs RECORD;
  BEGIN
    SELECT INTO rs c_id, c_passwd, c_fname, c_lname, 
      addr_street1, addr_street2,
      addr_city, addr_state,
      addr_zip, co_name, c_phone,
      c_email, c_data, c_birthdate, c_discount
    FROM CUSTOMER, address, country
    WHERE c_uname = $1 and addr_id = c_addr_id and addr_co_id=co_id;

    IF NOT FOUND THEN
	RAISE EXCEPTION ''can not find record c_id=%, c_uname=%'', rs.c_id, $1;
    END IF;
    UPDATE customer set c_login=now(), c_expiration = now()+''02:00''  WHERE c_id = rs.c_id;
    RETURN NEXT rs;
    RETURN;
  END;
' LANGUAGE 'plpgsql';
commit;
