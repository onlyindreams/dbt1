/*
/*
/* This file is released under the terms of the Artistic License.  Please see
/* the file LICENSE, included in this package, for details.
/*
/* Copyright (C) 2002 Mark Wong & Jenny Zhang &
/*                    Open Source Development Lab, Inc.
/*
/*/
/* Clause 2.9.3 */
CREATE DBPROC getOrderItems(
IN o_id fixed(10,0), OUT num_item fixed(3,0),
OUT i_id1 FIXED(10), OUT i_title1 VARCHAR(60),
OUT i_publisher1 VARCHAR(60), OUT i_cost1 FIXED(17, 2),
OUT ol_qty1 FIXED(3), OUT ol_discount1 FIXED(17, 2),
OUT ol_comments1 VARCHAR(100),
OUT i_id2 FIXED(10), OUT i_title2 VARCHAR(60),
OUT i_publisher2 VARCHAR(60), OUT i_cost2 FIXED(17, 2),
OUT ol_qty2 FIXED(3), OUT ol_discount2 FIXED(17, 2),
OUT ol_comments2 VARCHAR(100),
OUT i_id3 FIXED(10), OUT i_title3 VARCHAR(60),
OUT i_publisher3 VARCHAR(60), OUT i_cost3 FIXED(17, 2),
OUT ol_qty3 FIXED(3), OUT ol_discount3 FIXED(17, 2),
OUT ol_comments3 VARCHAR(100),
OUT i_id4 FIXED(10), OUT i_title4 VARCHAR(60),
OUT i_publisher4 VARCHAR(60), OUT i_cost4 FIXED(17, 2),
OUT ol_qty4 FIXED(3), OUT ol_discount4 FIXED(17, 2),
OUT ol_comments4 VARCHAR(100),
OUT i_id5 FIXED(10), OUT i_title5 VARCHAR(60),
OUT i_publisher5 VARCHAR(60), OUT i_cost5 FIXED(17, 2),
OUT ol_qty5 FIXED(3), OUT ol_discount5 FIXED(17, 2),
OUT ol_comments5 VARCHAR(100),
OUT i_id6 FIXED(10), OUT i_title6 VARCHAR(60),
OUT i_publisher6 VARCHAR(60), OUT i_cost6 FIXED(17, 2),
OUT ol_qty6 FIXED(3), OUT ol_discount6 FIXED(17, 2),
OUT ol_comments6 VARCHAR(100),
OUT i_id7 FIXED(10), OUT i_title7 VARCHAR(60),
OUT i_publisher7 VARCHAR(60), OUT i_cost7 FIXED(17, 2),
OUT ol_qty7 FIXED(3), OUT ol_discount7 FIXED(17, 2),
OUT ol_comments7 VARCHAR(100),
OUT i_id8 FIXED(10), OUT i_title8 VARCHAR(60),
OUT i_publisher8 VARCHAR(60), OUT i_cost8 FIXED(17, 2),
OUT ol_qty8 FIXED(3), OUT ol_discount8 FIXED(17, 2),
OUT ol_comments8 VARCHAR(100),
OUT i_id9 FIXED(10), OUT i_title9 VARCHAR(60),
OUT i_publisher9 VARCHAR(60), OUT i_cost9 FIXED(17, 2),
OUT ol_qty9 FIXED(3), OUT ol_discount9 FIXED(17, 2),
OUT ol_comments9 VARCHAR(100),
OUT i_id10 FIXED(10), OUT i_title10 VARCHAR(60),
OUT i_publisher10 VARCHAR(60), OUT i_cost10 FIXED(17, 2),
OUT ol_qty10 FIXED(3), OUT ol_discount10 FIXED(17, 2),
OUT ol_comments10 VARCHAR(100),
OUT i_id11 FIXED(10), OUT i_title11 VARCHAR(60),
OUT i_publisher11 VARCHAR(60), OUT i_cost11 FIXED(17, 2),
OUT ol_qty11 FIXED(3), OUT ol_discount11 FIXED(17, 2),
OUT ol_comments11 VARCHAR(100),
OUT i_id12 FIXED(10), OUT i_title12 VARCHAR(60),
OUT i_publisher12 VARCHAR(60), OUT i_cost12 FIXED(17, 2),
OUT ol_qty12 FIXED(3), OUT ol_discount12 FIXED(17, 2),
OUT ol_comments12 VARCHAR(100),
OUT i_id13 FIXED(10), OUT i_title13 VARCHAR(60),
OUT i_publisher13 VARCHAR(60), OUT i_cost13 FIXED(17, 2),
OUT ol_qty13 FIXED(3), OUT ol_discount13 FIXED(17, 2),
OUT ol_comments13 VARCHAR(100),
OUT i_id14 FIXED(10), OUT i_title14 VARCHAR(60),
OUT i_publisher14 VARCHAR(60), OUT i_cost14 FIXED(17, 2),
OUT ol_qty14 FIXED(3), OUT ol_discount14 FIXED(17, 2),
OUT ol_comments14 VARCHAR(100),
OUT i_id15 FIXED(10), OUT i_title15 VARCHAR(60),
OUT i_publisher15 VARCHAR(60), OUT i_cost15 FIXED(17, 2),
OUT ol_qty15 FIXED(3), OUT ol_discount15 FIXED(17, 2),
OUT ol_comments15 VARCHAR(100),
OUT i_id16 FIXED(10), OUT i_title16 VARCHAR(60),
OUT i_publisher16 VARCHAR(60), OUT i_cost16 FIXED(17, 2),
OUT ol_qty16 FIXED(3), OUT ol_discount16 FIXED(17, 2),
OUT ol_comments16 VARCHAR(100),
OUT i_id17 FIXED(10), OUT i_title17 VARCHAR(60),
OUT i_publisher17 VARCHAR(60), OUT i_cost17 FIXED(17, 2),
OUT ol_qty17 FIXED(3), OUT ol_discount17 FIXED(17, 2),
OUT ol_comments17 VARCHAR(100),
OUT i_id18 FIXED(10), OUT i_title18 VARCHAR(60),
OUT i_publisher18 VARCHAR(60), OUT i_cost18 FIXED(17, 2),
OUT ol_qty18 FIXED(3), OUT ol_discount18 FIXED(17, 2),
OUT ol_comments18 VARCHAR(100),
OUT i_id19 FIXED(10), OUT i_title19 VARCHAR(60),
OUT i_publisher19 VARCHAR(60), OUT i_cost19 FIXED(17, 2),
OUT ol_qty19 FIXED(3), OUT ol_discount19 FIXED(17, 2),
OUT ol_comments19 VARCHAR(100),
OUT i_id20 FIXED(10), OUT i_title20 VARCHAR(60),
OUT i_publisher20 VARCHAR(60), OUT i_cost20 FIXED(17, 2),
OUT ol_qty20 FIXED(3), OUT ol_discount20 FIXED(17, 2),
OUT ol_comments20 VARCHAR(100)) AS
BEGIN
  set num_item=0;
  CALL initOrderItems( 
      :i_id1, :i_title1, :i_publisher1, :i_cost1, :ol_qty1, :ol_discount1, :ol_comments1,
       :i_id2, :i_title2, :i_publisher2, :i_cost2, :ol_qty2, :ol_discount2, :ol_comments2,
       :i_id3, :i_title3, :i_publisher3, :i_cost3, :ol_qty3, :ol_discount3, :ol_comments3,
       :i_id4, :i_title4, :i_publisher4, :i_cost4, :ol_qty4, :ol_discount4, :ol_comments4,
       :i_id5, :i_title5, :i_publisher5, :i_cost5, :ol_qty5, :ol_discount5, :ol_comments5,
       :i_id6, :i_title6, :i_publisher6, :i_cost6, :ol_qty6, :ol_discount6, :ol_comments6,
       :i_id7, :i_title7, :i_publisher7, :i_cost7, :ol_qty7, :ol_discount7, :ol_comments7,
       :i_id8, :i_title8, :i_publisher8, :i_cost8, :ol_qty8, :ol_discount8, :ol_comments8,
       :i_id9, :i_title9, :i_publisher9, :i_cost9, :ol_qty9, :ol_discount9, :ol_comments9,
       :i_id10, :i_title10, :i_publisher10, :i_cost10, :ol_qty10, :ol_discount10, :ol_comments10,
       :i_id11, :i_title11, :i_publisher11, :i_cost11, :ol_qty11, :ol_discount11, :ol_comments11,
       :i_id12, :i_title12, :i_publisher12, :i_cost12, :ol_qty12, :ol_discount12, :ol_comments12,
       :i_id13, :i_title13, :i_publisher13, :i_cost13, :ol_qty13, :ol_discount13, :ol_comments13,
       :i_id14, :i_title14, :i_publisher14, :i_cost14, :ol_qty14, :ol_discount14, :ol_comments14,
       :i_id15, :i_title15, :i_publisher15, :i_cost15, :ol_qty15, :ol_discount15, :ol_comments15,
       :i_id16, :i_title16, :i_publisher16, :i_cost16, :ol_qty16, :ol_discount16, :ol_comments16,
       :i_id17, :i_title17, :i_publisher17, :i_cost17, :ol_qty17, :ol_discount17, :ol_comments17,
       :i_id18, :i_title18, :i_publisher18, :i_cost18, :ol_qty18, :ol_discount18, :ol_comments18,
       :i_id19, :i_title19, :i_publisher19, :i_cost19, :ol_qty19, :ol_discount19, :ol_comments19,
       :i_id20, :i_title20, :i_publisher20, :i_cost20, :ol_qty20, :ol_discount20, :ol_comments20);
  SELECT ol_i_id, i_title, i_publisher, i_cost, ol_qty, ol_discount,
       ol_comments
  FROM dbt.item, dbt.order_line
  WHERE ol_o_id = :o_id AND ol_i_id = i_id;
  if $rc=0 THEN
    FETCH into :i_id1, :i_title1, :i_publisher1, :i_cost1, :ol_qty1,
                   :ol_discount1, :ol_comments1;
  if $rc=0 THEN begin
    num_item=num_item+1;
    FETCH into :i_id2, :i_title2, :i_publisher2, :i_cost2, :ol_qty2,
                   :ol_discount2, :ol_comments2;
  end;
  if $rc=0 THEN begin
    num_item=num_item+1;
    FETCH into :i_id3, :i_title3, :i_publisher3, :i_cost3, :ol_qty3,
                   :ol_discount3, :ol_comments3;
  end;
  if $rc=0 THEN begin
    num_item=num_item+1;
    FETCH into :i_id4, :i_title4, :i_publisher4, :i_cost4, :ol_qty4,
                   :ol_discount4, :ol_comments4;
  end;
  if $rc=0 THEN begin
    num_item=num_item+1;
    FETCH into :i_id5, :i_title5, :i_publisher5, :i_cost5, :ol_qty5,
                   :ol_discount5, :ol_comments5;
  end;
  if $rc=0 THEN begin
    num_item=num_item+1;
    FETCH into :i_id6, :i_title6, :i_publisher6, :i_cost6, :ol_qty6,
                   :ol_discount6, :ol_comments6;
  end;
  if $rc=0 THEN begin
    num_item=num_item+1;
    FETCH into :i_id7, :i_title7, :i_publisher7, :i_cost7, :ol_qty7,
                   :ol_discount7, :ol_comments7;
  end;
  if $rc=0 THEN begin
    num_item=num_item+1;
    FETCH into :i_id8, :i_title8, :i_publisher8, :i_cost8, :ol_qty8,
                   :ol_discount8, :ol_comments8;
  end;
  if $rc=0 THEN begin
    num_item=num_item+1;
    FETCH into :i_id9, :i_title9, :i_publisher9, :i_cost9, :ol_qty9,
                   :ol_discount9, :ol_comments9;
  end;
  if $rc=0 THEN begin
    num_item=num_item+1;
    FETCH into :i_id10, :i_title10, :i_publisher10, :i_cost10, :ol_qty10,
                   :ol_discount10, :ol_comments10;
  end;
  if $rc=0 THEN begin
    num_item=num_item+1;
    FETCH into :i_id11, :i_title11, :i_publisher11, :i_cost11, :ol_qty11,
                   :ol_discount11, :ol_comments11;
  end;
  if $rc=0 THEN begin
    num_item=num_item+1;
    FETCH into :i_id12, :i_title12, :i_publisher12, :i_cost12, :ol_qty12,
                   :ol_discount12, :ol_comments12;
  end;
  if $rc=0 THEN begin
    num_item=num_item+1;
    FETCH into :i_id13, :i_title13, :i_publisher13, :i_cost13, :ol_qty13,
                   :ol_discount13, :ol_comments13;
  end;
  if $rc=0 THEN begin
    num_item=num_item+1;
    FETCH into :i_id14, :i_title14, :i_publisher14, :i_cost14, :ol_qty14,
                   :ol_discount14, :ol_comments14;
  end;
  if $rc=0 THEN begin
    num_item=num_item+1;
    FETCH into :i_id15, :i_title15, :i_publisher15, :i_cost15, :ol_qty15,
                   :ol_discount15, :ol_comments15;
  end;
  if $rc=0 THEN begin
    num_item=num_item+1;
    FETCH into :i_id16, :i_title16, :i_publisher16, :i_cost16, :ol_qty16,
                   :ol_discount16, :ol_comments16;
  end;
  if $rc=0 THEN begin
    num_item=num_item+1;
    FETCH into :i_id17, :i_title17, :i_publisher17, :i_cost17, :ol_qty17,
                   :ol_discount17, :ol_comments17;
  end;
  if $rc=0 THEN begin
    num_item=num_item+1;
    FETCH into :i_id18, :i_title18, :i_publisher18, :i_cost18, :ol_qty18,
                   :ol_discount18, :ol_comments18;
  end;
  if $rc=0 THEN begin
    num_item=num_item+1;
    FETCH into :i_id19, :i_title19, :i_publisher19, :i_cost19, :ol_qty19,
                   :ol_discount19, :ol_comments19;
  end;
  if $rc=0 THEN begin
    num_item=num_item+1;
    FETCH into :i_id20, :i_title20, :i_publisher20, :i_cost20, :ol_qty20,
                   :ol_discount20, :ol_comments20;
  end;
END;
;
