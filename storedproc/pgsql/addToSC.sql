/*
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2002 Open Source Development Lab, Inc.
 * History:
 * Feb 2001: Created by Mark Wong & Jenny Zhang
 * Apr 2003: Rewritten for PostgreSQL by Virginie Megy & Thierry Missimilly
 *		  Bull, Linux Competence Center
 *
 */
CREATE FUNCTION addToSC (NUMERIC(10), NUMERIC(1), NUMERIC(10)) RETURNS INTEGER AS'
DECLARE
	shop_cart_id	alias for $1;
	flag		alias for $2;
	item_id		alias for $3;

	itemcount numeric(3, 0);
	shop_cart_line_qty numeric(3,0);
	item_cost numeric(17,2);
	item_srp numeric(17,2);
	item_title varchar(60);
	item_backing varchar(15);
	item_related1 numeric(10,0);
	counter integer;
BEGIN
IF flag=1 THEN
  SELECT sum(scl_qty) INTO itemcount FROM shopping_cart_line
  WHERE scl_sc_id= shop_cart_id;
  IF itemcount<100 THEN
    SELECT scl_qty INTO shop_cart_line_qty FROM shopping_cart_line
    WHERE scl_sc_id = shop_cart_id AND scl_i_id= item_id;
    IF FOUND THEN
       UPDATE shopping_cart_line SET scl_qty=shop_cart_line_qty+1
       WHERE scl_sc_id=shop_cart_id AND scl_i_id=item_id;
    ELSE
       SELECT i_cost, i_srp, i_title, i_backing
       INTO item_cost, item_srp, item_title, item_backing
       FROM item WHERE i_id=item_id;
       INSERT INTO shopping_cart_line VALUES(shop_cart_id, item_id, 1, item_cost,
       item_srp, item_title, item_backing);
    END IF;
    return 1;
  ELSE
    return 0;
  END IF;
ELSE
--RAISE NOTICE ''flag=0'';
   SELECT count(*) INTO counter FROM shopping_cart_line WHERE scl_sc_id=shop_cart_id;
   IF counter=0 THEN
--RAISE NOTICE ''shopping_cart_line vide'';
  	SELECT i_related1 INTO item_related1 FROM item WHERE i_id=item_id;
	SELECT i_cost, i_srp, i_title, i_backing
	INTO item_cost, item_srp, item_title, item_backing
 	FROM item where i_id=item_related1;
 	INSERT INTO shopping_cart_line values(shop_cart_id, item_related1, 1,
  	item_cost, item_srp, item_title, item_backing);
   END IF;
END IF;
return 1;
END;
'LANGUAGE 'plpgsql'

