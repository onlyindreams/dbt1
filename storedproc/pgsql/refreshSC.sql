--
--
-- This file is released under the terms of the Artistic License.  Please see
-- the file LICENSE, included in this package, for details.
--
-- Copyright (C) 2002 Open Source Development Lab, Inc.
-- History:
-- July-2003: Created by Satoshi Nagayasu & Hideyuki Kawashima
-- Aug-12-2003: Reviewed by Jenny Zhang
-- refreshSC.sql
\set AUTOCOMMIT off
CREATE OR REPLACE FUNCTION refreshSC (
  NUMERIC(10),
  NUMERIC(10),
  NUMERIC(3)
) RETURNS INT AS'
  DECLARE
    sc_id ALIAS FOR $1;
    i_id ALIAS FOR $2;
    qty ALIAS FOR $3;
    -- VARs
    i smallint;
  BEGIN

--  RAISE NOTICE ''sc_id=% i_id=% qty=%'', sc_id, i_id, qty;
  IF (qty=0) THEN
      DELETE FROM shopping_cart_line 
      WHERE scl_sc_id=sc_id AND scl_i_id=i_id;
  ELSE
      UPDATE shopping_cart_line SET scl_qty=qty
      WHERE scl_sc_id=sc_id AND scl_i_id=i_id;
  END IF;
  RETURN 0;
  END;
' LANGUAGE 'plpgsql';
commit;

-- Usage:
-- 
-- SELECT (
--    sc_id NUMERIC(10,0),
--    itemcount NUMERIC(2,0),
--    i_id NUMERIC(10,0),
--    qty NUMERIC(3,0),
-- );

