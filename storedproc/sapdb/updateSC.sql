/*
/*
/* This file is released under the terms of the Artistic License.  Please see
/* the file LICENSE, included in this package, for details.
/*
/* Copyright (C) 2002 Mark Wong & Jenny Zhang &
/*                    Open Source Development Lab, Inc.
/*
/*/
CREATE DBPROC updateSC (IN sc_id fixed(10), 
IN discount fixed(5,2), OUT  sc_sub_total fixed(17,2), 
OUT sc_tax fixed(17,2), OUT sc_ship_cost fixed(5,2), 
OUT sc_total fixed(17,2)) AS
VAR i_cost fixed(17,2); i_id fixed(10); sub_total fixed(17,2); 
    scl_qty fixed(3); sc_qty fixed(3);
BEGIN
set sc_qty=0;
set sc_sub_total=0.00;
set sub_total=0.00;
set discount=0.00;
set sc_tax=0.00;
set sc_ship_cost=0.00;
set sc_total=0.00;
SELECT scl_i_id, scl_qty, i_cost FROM dbt.shopping_cart_line, dbt.item
  WHERE i_id=scl_i_id AND scl_sc_id=:sc_id;
WHILE $rc=0 DO BEGIN
  FETCH INTO :i_id, :scl_qty, :i_cost;
  if $rc=0 THEN BEGIN
     UPDATE dbt.shopping_cart_line SET scl_cost=(:i_cost)
        WHERE scl_i_id=:i_id AND scl_sc_id=:sc_id;
     set sub_total=sub_total+i_cost*scl_qty;
     set sc_qty=sc_qty+scl_qty;
  END;
END;
set sc_sub_total=sub_total*(1-discount);
set sc_tax=sc_sub_total*0.0825;
set sc_ship_cost=3.00+(1.00*sc_qty);
set sc_total=sc_sub_total+sc_ship_cost+sc_tax;
UPDATE dbt.shopping_cart set sc_date=(timestamp), sc_sub_total=(:sc_sub_total),
sc_tax=(:sc_tax), sc_ship_cost=(:sc_ship_cost), sc_total=(:sc_total) where sc_id=:sc_id;
END;;
/
/
