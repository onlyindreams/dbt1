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
CREATE OR REPLACE FUNCTION createSC  ( numeric(10,0) ) RETURNS numeric(10,0) AS '
  DECLARE
    _C_ID ALIAS FOR $1;

    _C_FName char(15);
    _C_LName char(15);
    _C_Discount numeric(5,2);

    _sc_id numeric(10,0);
  BEGIN
    _sc_id := nextval(''scid'');
    IF _C_ID <> 0 THEN
      SELECT c_fname,c_lname,c_discount
        INTO _C_FName,_C_LName,_C_Discount
        FROM customer WHERE c_id=_C_ID;

      INSERT INTO shopping_cart(sc_id, sc_c_id, sc_date, sc_c_fname, 
                                sc_c_lname, sc_c_discount)
      VALUES (_sc_id, _c_id, now(), _C_FName, _C_LName, _C_Discount);
    ELSE
      INSERT INTO shopping_cart(sc_id, sc_date) VALUES (_sc_id, now());
    END IF;
    RETURN _sc_id;
  END;
' LANGUAGE 'plpgsql';
commit;


-- 
-- Usage:
-- 
-- SELECT createSC ( 
--         C_ID numeric(10,0) );

