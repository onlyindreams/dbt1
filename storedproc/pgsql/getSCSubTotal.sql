--
--
-- This file is released under the terms of the Artistic License.  Please see
-- the file LICENSE, included in this package, for details.
--
-- Copyright (C) 2002 Open Source Development Lab, Inc.
-- History: 
-- July-2003: Created by Satoshi Nagayasu
--
CREATE OR REPLACE FUNCTION getSCSubTotal  ( NUMERIC(10,0) ) RETURNS NUMERIC(17,2) AS '
  DECLARE
    _sc_id ALIAS FOR $1;
    
    sub_total NUMERIC(17,2);
    scl_record RECORD;
  BEGIN
    sub_total := 0;

    FOR scl_record IN SELECT scl_cost, scl_qty FROM shopping_cart_line WHERE scl_sc_id = _sc_id LOOP
	sub_total := sub_total;
    END LOOP;

    RETURN sub_total; 
  END;
' LANGUAGE 'plpgsql';
commit;


-- 
-- Usage:
-- 
-- SELECT getSCSubTotal ( 
--         sc_id NUMERIC(10,0) );

