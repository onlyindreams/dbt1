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
CREATE FUNCTION updateSC (NUMERIC(10,0), NUMERIC(5,2)) RETURNS INTEGER AS '

DECLARE

	shopcart_id alias for $1;
	shopcart_discount alias for $2;

	item_cost numeric(17,2);
	item_id numeric(10,0);
--	discount numeric(5,2);
	shopcart_sub_total numeric(17,2);
	shopcart_total numeric(17,2);
	shopcartline_qty numeric(3, 0);
	shopcart_tax numeric(17,2);
	shopcart_ship_cost numeric(17,2);
	curs_scl_i_id refcursor;

BEGIN
shopcart_sub_total:=0.00;
-- discount:=0.00;
shopcart_tax:=0.00;
shopcart_ship_cost:=0.00;
shopcart_total:=0.00;
OPEN curs_scl_i_id FOR SELECT scl_i_id FROM shopping_cart_line WHERE scl_sc_id=shopcart_id;
FETCH curs_scl_i_id INTO item_id;
WHILE FOUND LOOP
     SELECT i_cost INTO item_cost FROM item WHERE i_id=item_id;
     UPDATE shopping_cart_line SET scl_cost=item_cost
        WHERE scl_i_id=item_id AND scl_sc_id=shopcart_id;
     FETCH curs_scl_i_id INTO item_id;
  END LOOP;
CLOSE curs_scl_i_id;
shopcart_sub_total:= getSCSubTotal(shopcart_id);
SELECT sum(scl_qty) INTO shopcartline_qty
  FROM shopping_cart_line WHERE scl_sc_id=shopcart_id;
shopcart_sub_total:=shopcart_sub_total*(1-shopcart_discount);
shopcart_tax:=shopcart_sub_total*0.0825;
shopcart_ship_cost:=3.00+(1.00*shopcartline_qty);
shopcart_total:=shopcart_sub_total+shopcart_ship_cost+shopcart_tax;
UPDATE shopping_cart set sc_date=''now'', sc_sub_total=shopcart_sub_total,
sc_tax=shopcart_tax, sc_ship_cost=shopcart_ship_cost, sc_total=shopcart_total where sc_id=shopcart_id;
RETURN 1;
END;
' LANGUAGE 'plpgsql';

