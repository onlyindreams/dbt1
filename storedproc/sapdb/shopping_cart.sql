/*
/*
/* This file is released under the terms of the Artistic License.  Please see
/* the file LICENSE, included in this package, for details.
/*
/* Copyright (C) 2002 Mark Wong & Jenny Zhang &
/*                    Open Source Development Lab, Inc.
/*
/*/
CREATE DBPROC shopping_cart(IN C_ID fixed(10), INOUT sc_id fixed(10),
  INOUT itemcount fixed(2), IN add_flag fixed(1), 
  IN i_id fixed(10), IN pp_i_id fixed(10),
  IN i_id1 fixed(10), IN qty1 fixed(3),
  IN i_id2 fixed(10), IN qty2 fixed(3),
  IN i_id3 fixed(10), IN qty3 fixed(3),
  IN i_id4 fixed(10), IN qty4 fixed(3),
  IN i_id5 fixed(10), IN qty5 fixed(3),
  IN i_id6 fixed(10), IN qty6 fixed(3),
  IN i_id7 fixed(10), IN qty7 fixed(3),
  IN i_id8 fixed(10), IN qty8 fixed(3),
  IN i_id9 fixed(10), IN qty9 fixed(3),
  IN i_id10 fixed(10), IN qty10 fixed(3),
  IN i_id11 fixed(10), IN qty11 fixed(3),
  IN i_id12 fixed(10), IN qty12 fixed(3),
  IN i_id13 fixed(10), IN qty13 fixed(3),
  IN i_id14 fixed(10), IN qty14 fixed(3),
  IN i_id15 fixed(10), IN qty15 fixed(3),
  IN i_id16 fixed(10), IN qty16 fixed(3),
  IN i_id17 fixed(10), IN qty17 fixed(3),
  IN i_id18 fixed(10), IN qty18 fixed(3),
  IN i_id19 fixed(10), IN qty19 fixed(3),
  IN i_id20 fixed(10), IN qty20 fixed(3),
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
  OUT scl_backing20 varchar(15), OUT scl_qty20 fixed(3),
  OUT pp_i_id1 fixed(10), OUT pp_i_t1 fixed(10),
  OUT pp_i_id2 fixed(10), OUT pp_i_t2 fixed(10),
  OUT pp_i_id3 fixed(10), OUT pp_i_t3 fixed(10),
  OUT pp_i_id4 fixed(10), OUT pp_i_t4 fixed(10),
  OUT pp_i_id5 fixed(10), OUT pp_i_t5 fixed(10)) AS
VAR sc_subtotal fixed(17,2);
BEGIN
  IF (add_flag=1 or (sc_id=0 and add_flag=0 and itemcount=0) or (add_flag=0 and itemcount <> 0)) THEN
    BEGIN
    IF sc_id=0 THEN CALL createSC(:c_id, :sc_id);
    IF (add_flag=1 or (add_flag=0 and itemcount=0)) THEN  begin
      CALL addToSC(:sc_id, :add_flag, :i_id);
    end
    ELSE 
      CALL refreshSC(:sc_id, :itemcount, 
      :i_id1, :qty1, :i_id2, :qty2,
      :i_id3,  :qty3, :i_id4, :qty4, 
      :i_id5, :qty5, :i_id6, :qty6, 
      :i_id7, :qty7, :i_id8, :qty8, 
      :i_id9, :qty9, :i_id10, :qty10, 
      :i_id11, :qty11, :i_id12, :qty12, 
      :i_id13, :qty13, :i_id14, :qty14, 
      :i_id15, :qty15, :i_id16, :qty16,
      :i_id17, :qty17, :i_id18, :qty18, 
      :i_id19, :qty19, :i_id20, :qty20);
    CALL getSCSubTotal(:sc_id, :sc_subtotal);
    UPDATE dbt.shopping_cart SET sc_sub_total=:sc_subtotal, sc_date=timestamp
      WHERE sc_id=:sc_id;
  END;
  call getSCDetail(:sc_id, :itemcount,
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
  CALL getPromoImages(:pp_i_id, :pp_i_id1, :pp_i_t1, :pp_i_id2, :pp_i_t2, 
    :pp_i_id3, :pp_i_t3, :pp_i_id4, :pp_i_t4, :pp_i_id5, :pp_i_t5);
END;;
/
/
