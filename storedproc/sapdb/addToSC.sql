/*
/*
/* This file is released under the terms of the Artistic License.  Please see
/* the file LICENSE, included in this package, for details.
/*
/* Copyright (C) 2002 Mark Wong & Jenny Zhang &
/*                    Open Source Development Lab, Inc.
/*
/*/
CREATE DBPROC addToSC (IN sc_id fixed(10,0), IN add_flag fixed(1,0),
IN i_id fixed(10,0)) AS
  VAR itemcount fixed(3, 0); scl_qty fixed(3,0); i_cost fixed(17,2);
      i_srp fixed(17,2); i_title char(60); i_backing char(15); 
      i_related1 fixed(10,0);
BEGIN
IF add_flag=1 THEN BEGIN
  SELECT sum(scl_qty) INTO :itemcount FROM dbt.shopping_cart_line 
  WHERE scl_sc_id=:SC_ID;
  IF itemcount<100 THEN BEGIN
    SELECT scl_qty INTO :scl_qty FROM dbt.shopping_cart_line
    WHERE scl_sc_id=:SC_ID AND scl_i_id=:I_ID;
    IF $rc<>100 THEN
       UPDATE dbt.shopping_cart_line SET scl_qty=:scl_qty+1
       WHERE scl_sc_id=:SC_ID AND scl_i_id=:I_ID
    ELSE BEGIN
       SELECT i_cost, i_srp, i_title, i_backing 
       INTO :i_cost, :i_srp, :i_title, :i_backing
       FROM dbt.item WHERE i_id=:I_ID;
       INSERT INTO dbt.shopping_cart_line VALUES(:sc_id, :i_id, 1, :i_cost,
       :i_srp, :i_title, :i_backing);
    END;
  END
  ELSE BEGIN
    return;
  END;
END
ELSE BEGIN
SELECT * FROM dbt.shopping_cart_line WHERE scl_sc_id=:SC_ID;
IF $rc=100 THEN BEGIN
  SELECT i_related1 INTO :i_related1 FROM dbt.item WHERE i_id=:I_ID;
  SELECT i_cost, i_srp, i_title, i_backing
    INTO :i_cost, :i_srp, :i_title, :i_backing
    FROM dbt.item where i_id=:i_related1;
  INSERT INTO dbt.shopping_cart_line values(:sc_id, :i_related1, 1,
    :i_cost, :i_srp, :i_title, :i_backing);
END;
END;
END;
;
/
/
