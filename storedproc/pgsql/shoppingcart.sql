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
CREATE FUNCTION shoppingcart(
			NUMERIC(10), NUMERIC(10),
			NUMERIC(2), NUMERIC(1), NUMERIC(10),
			NUMERIC(10), NUMERIC(3),NUMERIC(10), NUMERIC(3),
			NUMERIC(10), NUMERIC(3),NUMERIC(10), NUMERIC(3),
			NUMERIC(10), NUMERIC(3),NUMERIC(10), NUMERIC(3),
			NUMERIC(10), NUMERIC(3),NUMERIC(10), NUMERIC(3),
			NUMERIC(10), NUMERIC(3),NUMERIC(10), NUMERIC(3))
		RETURNS NUMERIC(10) AS'
DECLARE
	C_ID alias for $1;
	shop_cart_id alias for $2;
	itemcount alias for $3;
	add_flag alias for $4;
	i_id alias for $5;

	i_id1 alias for $6 ;  qty1 alias for $7 ;
	i_id2 alias for $8 ;  qty2 alias for $9 ;
 	i_id3 alias for $10;  qty3 alias for $11 ;
	i_id4 alias for $12 ;  qty4 alias for $13 ;
	i_id5 alias for $14 ;  qty5 alias for $15 ;
	i_id6 alias for $16 ;  qty6 alias for $17 ;
	i_id7 alias for $18 ;  qty7 alias for $19 ;
	i_id8 alias for $20 ;  qty8 alias for $21 ;
	i_id9 alias for $22 ;  qty9 alias for $23 ;
	i_id10 alias for $24 ;  qty10 alias for $25 ;

	shopcart_id NUMERIC(10);
	sc_subtotal NUMERIC(17,2);
	tampon integer;
	tampon1 integer;

BEGIN
--RAISE NOTICE ''BEGIN'' ;

  IF (add_flag=1 or (shop_cart_id=0 and add_flag=0 and itemcount=0) or (add_flag=0 and itemcount <> 0)) THEN
    IF shop_cart_id=0 THEN
    	shopcart_id := createSC(c_id);
    ELSE
    	shopcart_id := shop_cart_id;
    END IF;
    IF (add_flag=1 or (add_flag=0 and itemcount=0)) THEN
      tampon:= addToSC(shopcart_id, add_flag, i_id);
    ELSE

--RAISE NOTICE ''Case REFRESH: %.'', itemcount;

      tampon1 :=refreshSC(shopcart_id, itemcount,
      i_id1, qty1, i_id2, qty2,
      i_id3,  qty3, i_id4, qty4,
      i_id5, qty5, i_id6, qty6,
      i_id7, qty7, i_id8, qty8,
      i_id9, qty9, i_id10, qty10);
    END IF;
    sc_subtotal:= getSCSubTotal(shopcart_id);
    UPDATE shopping_cart SET sc_sub_total=sc_subtotal, sc_date=''now''
      WHERE sc_id=shopcart_id;
  END IF;
  RETURN shopcart_id;
END;
'LANGUAGE 'plpgsql'
