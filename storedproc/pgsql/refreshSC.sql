/*
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2002 Open Source Development Lab, Inc.
 * History:
 * Feb 2002: Original version created by Mark Wong & Jenny Zhang 
 * Apr 2003: Rewritten for PostgreSQL by Virginie Megy & Thierry Missimilly
 *		  Bull, Linux Competence Center
 *
 */
CREATE FUNCTION refreshSC (NUMERIC(10), NUMERIC(2),
NUMERIC(10), NUMERIC(3),NUMERIC(10), NUMERIC(3),
NUMERIC(10), NUMERIC(3),NUMERIC(10), NUMERIC(3),
NUMERIC(10), NUMERIC(3), NUMERIC(10), NUMERIC(3),
NUMERIC(10), NUMERIC(3), NUMERIC(10), NUMERIC(3),
NUMERIC(10), NUMERIC(3), NUMERIC(10), NUMERIC(3)) RETURNS INTEGER AS '
DECLARE
	shopcart_id alias for $1;
	itemcount alias for $2;
	i_id1 alias for $3; qty1 alias for $4;
	i_id2 alias for $5; qty2 alias for $6;
	i_id3 alias for $7; qty3 alias for $8;
	i_id4 alias for $9; qty4 alias for $10;
	i_id5 alias for $11; qty5 alias for $12;
	i_id6 alias for $13; qty6 alias for $14;
	i_id7 alias for $15; qty7 alias for $16;
	i_id8 alias for $17; qty8 alias for $18;
	i_id9 alias for $19; qty9 alias for $20;
	i_id10 alias for $21; qty10 alias for $22;
	i integer;

BEGIN
--RAISE NOTICE '' BEGIN REFRESH'';
i:= 0;
if (i<itemcount and i<100) then
  if qty1=0 then
--RAISE NOTICE '' DELETE'';
    delete from shopping_cart_line
      where scl_sc_id=shopcart_id and scl_i_id=i_id1;
  else
--RAISE NOTICE '' UPDATE %.'',qty1;
    update shopping_cart_line set scl_qty=qty1
      where scl_sc_id=shopcart_id and scl_i_id=i_id1;
  end if;
  i:=i+1;
end if;
if (i<itemcount and i<100) then
  if qty2=0 then
    delete from shopping_cart_line
      where scl_sc_id=shopcart_id and scl_i_id=i_id2;
  else
    update shopping_cart_line set scl_qty=qty2
      where scl_sc_id=shopcart_id and scl_i_id=i_id2;
  end if;
  i:=i+1;
end if;
if (i<itemcount and i<100) then
  if qty3=0 then
    delete from shopping_cart_line
      where scl_sc_id=shopcart_id and scl_i_id=i_id3;
  else
    update shopping_cart_line set scl_qty=qty3
      where scl_sc_id=shopcart_id and scl_i_id=i_id3;
  end if;
  i:=i+1;
end if;
if (i<itemcount and i<100) then
  if qty4=0 then
    delete from shopping_cart_line
      where scl_sc_id=shopcart_id and scl_i_id=i_id4;
  else
    update shopping_cart_line set scl_qty=qty4
      where scl_sc_id=shopcart_id and scl_i_id=i_id4;
  end if;
  i:=i+1;
end if;
if (i<itemcount and i<100) then
  if qty5=0 then
    delete from shopping_cart_line
      where scl_sc_id=shopcart_id and scl_i_id=i_id5;
  else
    update shopping_cart_line set scl_qty=qty5
      where scl_sc_id=shopcart_id and scl_i_id=i_id5;
  end if;
  i:=i+1;
end if;
if (i<itemcount and i<100) then
  if qty6=0 then
    delete from shopping_cart_line
      where scl_sc_id=shopcart_id and scl_i_id=i_id6;
  else
    update shopping_cart_line set scl_qty=qty6
      where scl_sc_id=shopcart_id and scl_i_id=i_id6;
  end if;
  i:=i+1;
end if;
if (i<itemcount and i<100) then
  if qty7=0 then
    delete from shopping_cart_line
      where scl_sc_id=shopcart_id and scl_i_id=i_id7;
  else
    update shopping_cart_line set scl_qty=qty7
      where scl_sc_id=shopcart_id and scl_i_id=i_id7;
  end if;
  i:=i+1;
end if;
if (i<itemcount and i<100) then
  if qty8=0 then
    delete from shopping_cart_line
      where scl_sc_id=shopcart_id and scl_i_id=i_id8;
  else
    update shopping_cart_line set scl_qty=qty8
      where scl_sc_id=shopcart_id and scl_i_id=i_id8;
  end if;
  i:=i+1;
end if;
if (i<itemcount and i<100) then
  if qty9=0 then
    delete from shopping_cart_line
      where scl_sc_id=shopcart_id and scl_i_id=i_id9;
  else
    update shopping_cart_line set scl_qty=qty9
      where scl_sc_id=shopcart_id and scl_i_id=i_id9;
  end if;
  i:=i+1;
end if;
if (i<itemcount and i<100) then
  if qty10=0 then
    delete from shopping_cart_line
      where scl_sc_id=shopcart_id and scl_i_id=i_id10;
  else
    update shopping_cart_line set scl_qty=qty10
      where scl_sc_id=shopcart_id and scl_i_id=i_id10;
  end if;
  i:=i+1;
end if;
return 1;
END;
'LANGUAGE 'plpgsql'

