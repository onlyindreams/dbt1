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
CREATE FUNCTION buyconfirm( varchar(10),  numeric(16,0), varchar(31),
varchar(8), varchar(10), numeric(10,0), numeric(10,0), numeric(1,0), varchar(10),
varchar(15), varchar(10), varchar(40), varchar(30), varchar(20), 
varchar(10), varchar(50)) RETURNS NUMERIC(5,2) AS'


DECLARE

	cart_type alias for $1;
	cart_num alias for $2;
	cart_name alias for $3;
	cart_expiry alias for $4;
	shipord_type alias for $5;
	shopcart_id alias for $6;
	cust_id alias for $7;
	days alias for $8;
	comment alias for $9;
	auth_id alias for $10;
	address_street1 alias for $11;
	address_Street2 alias for $12;
	address_city alias for $13;
	address_state alias for $14;
	address_zip alias for $15;
	country_name alias for $16;

  	cust_discount numeric(5,2);
  	cust_addr_id numeric(10);
	cust_fname char(15);
	cust_lname char(15);
	country_id smallint;
	shipord_addr_id numeric(10);
	orderl_id numeric(3);
	item_stock numeric(4);
	shopcart_sub_total numeric(17,2);
	shopcart_tax numeric(17,2);
	shopcart_shipcost numeric(17,2);
	shopcart_total numeric(17,2);
	shopcartl_i_id numeric(10);
	shopcartl_qty numeric(3);
	shopcartl_cost numeric(17,2);
	tmpdate date;
	rescurs refcursor;

BEGIN
tmpdate:=cart_expiry;

SELECT sc_sub_total, sc_tax, sc_ship_cost, sc_total INTO
  shopcart_sub_total, shopcart_tax, shopcart_shipcost, shopcart_total
  FROM shopping_cart WHERE sc_id=shopcart_id;

SELECT c_fname, c_lname, c_discount, c_addr_id INTO
  cust_fname, cust_lname, cust_discount, cust_addr_id
  FROM customer WHERE c_id=cust_id;

IF address_street1 <> '''' THEN
	SELECT co_id INTO country_id FROM country WHERE co_name=country_name;

	SELECT addr_id INTO shipord_addr_id FROM address
 		WHERE addr_co_id=country_id AND addr_zip=address_zip AND
       			addr_state=address_state AND addr_city=address_city AND
       			addr_street1=address_street1 AND addr_street2=address_street2;

	IF FOUND THEN
  	shipord_addr_id := nextval(''addrid'');
  	INSERT INTO address VALUES (shipord_addr_id, address_street1, address_street2, address_city, address_state, address_zip, country_id);
	END IF;

ELSE
  shipord_addr_id:=cust_addr_id;
  SELECT addr_co_id INTO country_id FROM address WHERE addr_id=shipord_addr_id;
END IF;

--Change current_date+days with the addTime() function!!!!

INSERT INTO orders VALUES(shopcart_id, cust_id, current_date , shopcart_sub_total, shopcart_tax, shopcart_total, ''SHIP'', current_date , cust_addr_id, shipord_addr_id, ''PENDING'');

orderl_id:=0;
OPEN rescurs FOR SELECT scl_i_id, scl_cost, scl_qty FROM shopping_cart_line WHERE scl_sc_id=shopcart_id;
FETCH rescurs INTO shopcartl_i_id, shopcartl_cost, shopcartl_qty;
WHILE FOUND LOOP
     orderl_id:=orderl_id+1;
     INSERT INTO order_line VALUES (orderl_id, shopcart_id, shopcartl_i_id, shopcartl_qty, cust_discount, comment);
     SELECT i_stock INTO item_stock FROM item WHERE i_id=shopcartl_i_id;
     IF (item_stock-10>shopcartl_qty) THEN
       item_stock :=item_stock-shopcartl_qty;
     ELSE
       item_stock :=item_stock-shopcartl_qty+21;
     END IF;
     UPDATE item set i_stock=item_stock where i_id=shopcartl_i_id;
     FETCH rescurs INTO shopcartl_i_id, shopcartl_cost, shopcartl_qty;
  END LOOP;

INSERT INTO cc_xacts VALUES (shopcart_id, cart_type, cart_num, cart_name, tmpdate, auth_id, shopcart_total, ''now'', country_id);

RETURN cust_discount;

END;
' LANGUAGE 'plpgsql';
