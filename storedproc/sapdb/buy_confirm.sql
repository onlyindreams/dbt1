/*
/*
/* This file is released under the terms of the Artistic License.  Please see
/* the file LICENSE, included in this package, for details.
/*
/* Copyright (C) 2002 Mark Wong & Jenny Zhang &
/*                    Open Source Development Lab, Inc.
/*
/*/
CREATE DBPROC buy_confirm( IN cc_type varchar(10), IN cc_num fixed(16), 
  IN cc_name varchar(31), IN cc_expiry char(8),
  IN ship_type varchar(10), IN sc_id fixed(10),
  IN c_id fixed(10), IN days fixed(1),
  IN comment varchar(100), IN auth_id char(15),
  IN addr_street1 varchar(40), IN addr_Street2 varchar(40),
  IN addr_city varchar(30), IN addr_state varchar(20),
  IN addr_zip varchar(10), IN country varchar(50),
  OUT c_discount fixed(5,2), OUT sc_sub_total fixed(17,2), 
  OUT sc_tax fixed(17,2), OUT sc_shipcost fixed(17,2),
  OUT sc_total fixed(17,2),
  OUT num_item fixed(2),
  OUT scl_i_id1 fixed(10), OUT scl_title1 varchar(60),
  OUT scl_cost1 fixed(17,2), OUT scl_srp1 fixed(17,2),
  OUT scl_backing1 varchar(15), OUT scl_qty1 fixed(3),
  OUT scl_i_id2 fixed(10), OUT scl_title2 varchar(60),
  OUT scl_cost2 fixed(17,2), OUT scl_srp2 fixed(17,2),
  OUT scl_backing2 varchar(15), OUT scl_qty2 fixed(3),
  OUT scl_i_id3 fixed(10), OUT scl_title3 varchar(60),
  OUT scl_cost3 fixed(17,2), OUT scl_srp3 fixed(17,2),
  OUT scl_backing3 varchar(15), OUT scl_qty3 fixed(3),
  OUT scl_i_id4 fixed(10), OUT scl_title4 varchar(60),
  OUT scl_cost4 fixed(17,2), OUT scl_srp4 fixed(17,2),
  OUT scl_backing4 varchar(15), OUT scl_qty4 fixed(3),
  OUT scl_i_id5 fixed(10), OUT scl_title5 varchar(60),
  OUT scl_cost5 fixed(17,2), OUT scl_srp5 fixed(17,2),
  OUT scl_backing5 varchar(15), OUT scl_qty5 fixed(3),
  OUT scl_i_id6 fixed(10), OUT scl_title6 varchar(60),
  OUT scl_cost6 fixed(17,2), OUT scl_srp6 fixed(17,2),
  OUT scl_backing6 varchar(15), OUT scl_qty6 fixed(3),
  OUT scl_i_id7 fixed(10), OUT scl_title7 varchar(60),
  OUT scl_cost7 fixed(17,2), OUT scl_srp7 fixed(17,2),
  OUT scl_backing7 varchar(15), OUT scl_qty7 fixed(3),
  OUT scl_i_id8 fixed(10), OUT scl_title8 varchar(60),
  OUT scl_cost8 fixed(17,2), OUT scl_srp8 fixed(17,2),
  OUT scl_backing8 varchar(15), OUT scl_qty8 fixed(3),
  OUT scl_i_id9 fixed(10), OUT scl_title9 varchar(60),
  OUT scl_cost9 fixed(17,2), OUT scl_srp9 fixed(17,2),
  OUT scl_backing9 varchar(15), OUT scl_qty9 fixed(3),
  OUT scl_i_id10 fixed(10), OUT scl_title10 varchar(60),
  OUT scl_cost10 fixed(17,2), OUT scl_srp10 fixed(17,2),
  OUT scl_backing10 varchar(15), OUT scl_qty10 fixed(3),
  OUT scl_i_id11 fixed(10), OUT scl_title11 varchar(60),
  OUT scl_cost11 fixed(17,2), OUT scl_srp11 fixed(17,2),
  OUT scl_backing11 varchar(15), OUT scl_qty11 fixed(3),
  OUT scl_i_id12 fixed(10), OUT scl_title12 varchar(60),
  OUT scl_cost12 fixed(17,2), OUT scl_srp12 fixed(17,2),
  OUT scl_backing12 varchar(15), OUT scl_qty12 fixed(3),
  OUT scl_i_id13 fixed(10), OUT scl_title13 varchar(60),
  OUT scl_cost13 fixed(17,2), OUT scl_srp13 fixed(17,2),
  OUT scl_backing13 varchar(15), OUT scl_qty13 fixed(3),
  OUT scl_i_id14 fixed(10), OUT scl_title14 varchar(60),
  OUT scl_cost14 fixed(17,2), OUT scl_srp14 fixed(17,2),
  OUT scl_backing14 varchar(15), OUT scl_qty14 fixed(3),
  OUT scl_i_id15 fixed(10), OUT scl_title15 varchar(60),
  OUT scl_cost15 fixed(17,2), OUT scl_srp15 fixed(17,2),
  OUT scl_backing15 varchar(15), OUT scl_qty15 fixed(3),
  OUT scl_i_id16 fixed(10), OUT scl_title16 varchar(60),
  OUT scl_cost16 fixed(17,2), OUT scl_srp16 fixed(17,2),
  OUT scl_backing16 varchar(15), OUT scl_qty16 fixed(3),
  OUT scl_i_id17 fixed(10), OUT scl_title17 varchar(60),
  OUT scl_cost17 fixed(17,2), OUT scl_srp17 fixed(17,2),
  OUT scl_backing17 varchar(15), OUT scl_qty17 fixed(3),
  OUT scl_i_id18 fixed(10), OUT scl_title18 varchar(60),
  OUT scl_cost18 fixed(17,2), OUT scl_srp18 fixed(17,2),
  OUT scl_backing18 varchar(15), OUT scl_qty18 fixed(3),
  OUT scl_i_id19 fixed(10), OUT scl_title19 varchar(60),
  OUT scl_cost19 fixed(17,2), OUT scl_srp19 fixed(17,2),
  OUT scl_backing19 varchar(15), OUT scl_qty19 fixed(3),
  OUT scl_i_id20 fixed(10), OUT scl_title20 varchar(60),
  OUT scl_cost20 fixed(17,2), OUT scl_srp20 fixed(17,2),
  OUT scl_backing20 varchar(15), OUT scl_qty20 fixed(3)) AS
  VAR c_addr_id fixed(10); c_fname char(15); c_lname char(15); 
      co_id smallint;
      ship_addr_id fixed(10);  ol_id fixed(3);
      i_stock fixed(4); scl_i_id fixed(10); scl_qty fixed(3);
      scl_cost fixed(17,2); tmpdate date;
BEGIN
set tmpdate=cc_expiry;
SELECT sc_sub_total, sc_tax, sc_ship_cost, sc_total INTO
  :sc_sub_total, :sc_tax, :sc_shipcost, :sc_total
  FROM dbt.shopping_cart WHERE sc_id=:sc_id;
SELECT c_fname, c_lname, c_discount, c_addr_id INTO
  :c_fname, :c_lname, :c_discount, :c_addr_id
  FROM dbt.customer WHERE c_id=:c_id;
IF addr_street1 <> '' THEN BEGIN
SELECT addr_id, co_id INTO :ship_addr_id, :co_id FROM dbt.address, dbt.country
 WHERE co_name=:country AND addr_co_id=co_id AND addr_zip=:addr_zip AND
       addr_state=:addr_state AND addr_city=:addr_city AND
       addr_street1=:addr_street1 AND addr_street2=:addr_street2;
IF $rc=100 THEN BEGIN
  set Ship_Addr_ID = AddrID.NEXTVAL;
  INSERT INTO dbt.address VALUES(:ship_addr_id, :addr_street1, :addr_street2,
  :addr_city, :addr_state, :addr_zip, :co_id);
END;
END
ELSE BEGIN
  set ship_addr_id=c_addr_id;
  SELECT addr_co_id INTO :co_id FROM dbt.address WHERE addr_id=:ship_addr_id;
END;
INSERT INTO dbt.orders VALUES(:sc_id, :c_id, timestamp, :sc_sub_total,
  :sc_tax, :sc_total, 'SHIP', adddate(timestamp,:days), :c_addr_id,
  :ship_addr_id, 'PENDING');
set ol_id=0;
SELECT scl_i_id, scl_cost, scl_qty FROM dbt.shopping_cart_line
  WHERE scl_sc_id=:sc_id;
WHILE $rc=0 DO BEGIN
  FETCH INTO :scl_i_id, :scl_cost, :scl_qty;
  IF $rc=0 THEN BEGIN
     set ol_id=ol_id+1;
     INSERT INTO dbt.order_line VALUES(:ol_id, :sc_id, :scl_i_id, :scl_qty,
            :c_discount, :comment);
     SELECT i_stock INTO :i_stock FROM dbt.item WHERE i_id=:scl_i_id;
     IF (i_stock-10>scl_qty) THEN
       set i_stock =i_stock-scl_qty
     ELSE
       set i_stock =i_stock-scl_qty+21;
     UPDATE dbt.item set i_stock=:i_stock where i_id=:scl_i_id;
  END;
END;
INSERT INTO dbt.cc_xacts VALUES(:sc_id, :cc_type, :cc_num, :cc_name,
  :tmpdate, :auth_id, :sc_total, timestamp, :co_id);
call getSCDetail(:sc_id, :num_item,
    :scl_i_id1, :scl_title1, :scl_cost1, :scl_srp1, :scl_backing1, :scl_qty1,
    :scl_i_id2, :scl_title2, :scl_cost2, :scl_srp2, :scl_backing2, :scl_qty2,
    :scl_i_id3, :scl_title3, :scl_cost3, :scl_srp3, :scl_backing3, :scl_qty3,
    :scl_i_id4, :scl_title4, :scl_cost4, :scl_srp4, :scl_backing4, :scl_qty4,
    :scl_i_id5, :scl_title5, :scl_cost5, :scl_srp5, :scl_backing5, :scl_qty5,
    :scl_i_id6, :scl_title6, :scl_cost6, :scl_srp6, :scl_backing6, :scl_qty6,
    :scl_i_id7, :scl_title7, :scl_cost7, :scl_srp7, :scl_backing7, :scl_qty7,
    :scl_i_id8, :scl_title8, :scl_cost8, :scl_srp8, :scl_backing8, :scl_qty8,
    :scl_i_id9, :scl_title9, :scl_cost9, :scl_srp9, :scl_backing9, :scl_qty9,
    :scl_i_id10, :scl_title10, :scl_cost10, :scl_srp10, :scl_backing10, :scl_qty10,
    :scl_i_id11, :scl_title11, :scl_cost11, :scl_srp11, :scl_backing11, :scl_qty11,
    :scl_i_id12, :scl_title12, :scl_cost12, :scl_srp12, :scl_backing12, :scl_qty12,
    :scl_i_id13, :scl_title13, :scl_cost13, :scl_srp13, :scl_backing13, :scl_qty13,
    :scl_i_id14, :scl_title14, :scl_cost14, :scl_srp14, :scl_backing14, :scl_qty14,
    :scl_i_id15, :scl_title15, :scl_cost15, :scl_srp15, :scl_backing15, :scl_qty15,
    :scl_i_id16, :scl_title16, :scl_cost16, :scl_srp16, :scl_backing16, :scl_qty16,
    :scl_i_id17, :scl_title17, :scl_cost17, :scl_srp17, :scl_backing17, :scl_qty17,
    :scl_i_id18, :scl_title18, :scl_cost18, :scl_srp18, :scl_backing18, :scl_qty18,
    :scl_i_id19, :scl_title19, :scl_cost19, :scl_srp19, :scl_backing19, :scl_qty19,
    :scl_i_id20, :scl_title20, :scl_cost20, :scl_srp20, :scl_backing20, :scl_qty20);
END;
;
/
/
