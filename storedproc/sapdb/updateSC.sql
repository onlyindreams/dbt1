/*
/*
/* This file is released under the terms of the Artistic License.  Please see
/* the file LICENSE, included in this package, for details.
/*
/* Copyright (C) 2002 Mark Wong & Jenny Zhang &
/*                    Open Source Development Lab, Inc.
/*
/*/
CREATE DBPROC updateSC (IN sc_id fixed(10,0), 
OUT  sc_sub_total fixed(17,2), OUT discount fixed(5,2), 
OUT sc_tax fixed(17,2), OUT sc_ship_cost fixed(5,2), 
OUT sc_total fixed(17,2)) AS
VAR i_cost fixed(17,2); i_id fixed(10,0); sub_total fixed(17,2); 
    scl_qty fixed(3, 0); 
SUBTRANS BEGIN;
set sc_sub_total=0.00;
set sc_tax=0.00;
set sc_ship_cost=0.00;
set sc_total=0.00;
SELECT scl_i_id FROM dbt.shopping_cart_line WHERE scl_sc_id=:sc_id;
WHILE $rc=0 DO BEGIN
  FETCH INTO :i_id;
  IF $rc = 0 THEN BEGIN
     SELECT i_cost INTO :i_cost FROM dbt.item WHERE i_id=:i_id;
     UPDATE dbt.shopping_cart_line SET scl_cost=(:i_cost) 
        WHERE scl_i_id=:i_id AND scl_sc_id=:sc_id;
  END;
END;
CALL getSCSubTotal(:sc_id, :sub_total);
SELECT sc_c_discount INTO :discount FROM dbt.shopping_cart WHERE sc_id=:sc_id;
SELECT sum(scl_qty) INTO :scl_qty 
  FROM dbt.shopping_cart_line WHERE scl_sc_id=:sc_id;
set sc_sub_total=sub_total*(1-discount);
set sc_tax=sc_sub_total*0.0825; 
set sc_ship_cost=3.00+(1.00*scl_qty);
set sc_total=sc_sub_total+sc_ship_cost+sc_tax;
UPDATE dbt.shopping_cart set sc_date=(timestamp), sc_sub_total=(:sc_sub_total),
sc_tax=(:sc_tax), sc_ship_cost=(:sc_ship_cost), sc_total=(:sc_total) where sc_id=:sc_id;
SUBTRANS END;;
/
/
