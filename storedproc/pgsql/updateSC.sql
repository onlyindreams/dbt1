--
--
-- This file is released under the terms of the Artistic License.  Please see
-- the file LICENSE, included in this package, for details.
--
-- Copyright (C) 2002 Open Source Development Lab, Inc.
-- History:
-- July-2003: Created by Satoshi Nagayasu & Hideyuki Kawashima
--
\set AUTOCOMMIT off
CREATE OR REPLACE FUNCTION updateSC ( numeric(10), numeric(5,2) ) RETURNS RECORD AS '
  DECLARE
    _sc_id ALIAS FOR $1;
    discount ALIAS FOR $2;

    _sc_sub_total numeric(17,2);
    _sc_tax numeric(17,2);
    _sc_ship_cost numeric(5,2);
    _sc_total numeric(17,2);

    _i_cost numeric(17,2);
    _i_id numeric(10);
    _sub_total numeric(17,2);
    _scl_qty numeric(3);
    sc_qty numeric(3);

    rec RECORD;
    refcur REFCURSOR;
  BEGIN
    sc_qty := 0;
    _sc_sub_total := 0.00;
    _sub_total := 0.00;
-- discount is specified by the caller.
--    discount := 0.00;
    _sc_tax := 0.00;
    _sc_ship_cost := 0.00;
    _sc_total := 0.00;

    OPEN refcur FOR SELECT scl_i_id, scl_qty, i_cost
                      FROM shopping_cart_line, item
                     WHERE i_id=scl_i_id
                       AND scl_sc_id=_sc_id;

    FETCH refcur INTO _i_id, _scl_qty, _i_cost;

    WHILE FOUND LOOP
--      RAISE NOTICE ''i_id=%,scl_qty=%,i_cost=%'', _i_id, _scl_qty, _i_cost;

      UPDATE shopping_cart_line SET scl_cost=_i_cost
       WHERE scl_i_id=_i_id
         AND scl_sc_id=_sc_id;

      _sub_total := _sub_total + _i_cost * _scl_qty;
      sc_qty := sc_qty + _scl_qty;

      FETCH refcur INTO _i_id, _scl_qty, _i_cost;
    END LOOP;

    _sc_sub_total := _sub_total * (1-discount);
    _sc_tax       := _sc_sub_total * 0.0825;
    _sc_ship_cost := 3.00 + (1.00*sc_qty);
    _sc_total     := _sc_sub_total + _sc_ship_cost + _sc_tax;

    UPDATE shopping_cart
       SET sc_date=now(), sc_sub_total=_sc_sub_total,
           sc_tax=_sc_tax, sc_ship_cost=_sc_ship_cost,
           sc_total=_sc_total
     WHERE sc_id=_sc_id;

    SELECT _sc_sub_total::numeric(17,2), _sc_tax::numeric(17,2),
           _sc_ship_cost::numeric(5,2), _sc_total::numeric(17,2)
      INTO rec;

    RETURN rec;
  END;
' LANGUAGE 'plpgsql';
commit;


-- 
-- Usage:
-- 
-- SELECT * FROM updateSC ( 
--         sc_id numeric(10)
--         discount numeric(5,2) )
--   AS l( sc_sub_total numeric(17,2),
--         sc_tax numeric(17,2),
--         sc_ship_cost numeric(5,2),
--         sc_total numeric(17,2) );

