--
--
-- This file is released under the terms of the Artistic License.  Please see
-- the file LICENSE, included in this package, for details.
--
-- Copyright (C) 2002 Open Source Development Lab, Inc.
-- History: 
-- July-2003: Created by Satoshi Nagayasu
--
\set AUTOCOMMIT off
CREATE OR REPLACE FUNCTION GetPromoImages ( numeric(10) ) RETURNS RECORD AS '
  DECLARE
    _I_ID ALIAS FOR $1;

    r1 numeric(10);
    r2 numeric(10);
    r3 numeric(10);
    r4 numeric(10);
    r5 numeric(10);

    I_ID1 numeric(10);
    I_T1  numeric(10); 
    I_ID2 numeric(10);
    I_T2  numeric(10); 
    I_ID3 numeric(10);
    I_T3  numeric(10); 
    I_ID4 numeric(10);
    I_T4  numeric(10); 
    I_ID5 numeric(10);
    I_T5  numeric(10);

    rec record;
  BEGIN
    SELECT i_related1, i_related2, i_related3, i_related4, i_related5
      INTO r1, r2, r3, r4, r5
      FROM item
     WHERE i_id = _I_ID;

--    RAISE NOTICE ''%,%,%,%,%'', r1,r2,r3,r4,r5;

    SELECT i_id, i_thumbnail
      INTO I_ID1, I_T1
      FROM item
     WHERE i_id = r1;

--    RAISE NOTICE ''%,%'', i_id1, i_t1;

    SELECT i_id, i_thumbnail
      INTO I_ID2, I_T2
      FROM item
     WHERE i_id = r2;

    SELECT i_id, i_thumbnail
      INTO I_ID3, I_T3
      FROM item
     WHERE i_id = r3;

    SELECT i_id, i_thumbnail
      INTO I_ID4, I_T4
      FROM item
     WHERE i_id = r4;

    SELECT i_id, i_thumbnail
      INTO I_ID5, I_T5
      FROM item
     WHERE i_id = r5;

    SELECT I_ID1::numeric(10), I_T1::numeric(10),
           I_ID2::numeric(10), I_T2::numeric(10),
           I_ID3::numeric(10), I_T3::numeric(10),
           I_ID4::numeric(10), I_T4::numeric(10),
           I_ID5::numeric(10), I_T5::numeric(10)
      INTO rec;

    RETURN rec;
  END;
' LANGUAGE 'plpgsql';
commit;


-- 
-- Usage:
-- 
-- SELECT * FROM GetPromoImages( 
--         I_ID numeric(10) )
--   AS l( I_ID1 numeric(10),
--         I_T1 numeric(10),
--         I_ID2 numeric(10),
--         I_T2 numeric(10),
--         I_ID3 numeric(10),
--         I_T3 numeric(10),
--         I_ID4 numeric(10),
--         I_T4 numeric(10),
--         I_ID5 numeric(10),
--         I_T5 numeric(10) );

