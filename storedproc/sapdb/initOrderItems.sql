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
CREATE DBPROC initOrderItems(
INOUT i_id1 FIXED(10), INOUT i_title1 VARCHAR(60),
INOUT i_publisher1 VARCHAR(60), INOUT i_cost1 FIXED(17, 2),
INOUT ol_qty1 FIXED(3), INOUT ol_discount1 FIXED(17, 2),
INOUT ol_comments1 VARCHAR(100),
INOUT i_id2 FIXED(10), INOUT i_title2 VARCHAR(60),
INOUT i_publisher2 VARCHAR(60), INOUT i_cost2 FIXED(17, 2),
INOUT ol_qty2 FIXED(3), INOUT ol_discount2 FIXED(17, 2),
INOUT ol_comments2 VARCHAR(100),
INOUT i_id3 FIXED(10), INOUT i_title3 VARCHAR(60),
INOUT i_publisher3 VARCHAR(60), INOUT i_cost3 FIXED(17, 2),
INOUT ol_qty3 FIXED(3), INOUT ol_discount3 FIXED(17, 2),
INOUT ol_comments3 VARCHAR(100),
INOUT i_id4 FIXED(10), INOUT i_title4 VARCHAR(60),
INOUT i_publisher4 VARCHAR(60), INOUT i_cost4 FIXED(17, 2),
INOUT ol_qty4 FIXED(3), INOUT ol_discount4 FIXED(17, 2),
INOUT ol_comments4 VARCHAR(100),
INOUT i_id5 FIXED(10), INOUT i_title5 VARCHAR(60),
INOUT i_publisher5 VARCHAR(60), INOUT i_cost5 FIXED(17, 2),
INOUT ol_qty5 FIXED(3), INOUT ol_discount5 FIXED(17, 2),
INOUT ol_comments5 VARCHAR(100),
INOUT i_id6 FIXED(10), INOUT i_title6 VARCHAR(60),
INOUT i_publisher6 VARCHAR(60), INOUT i_cost6 FIXED(17, 2),
INOUT ol_qty6 FIXED(3), INOUT ol_discount6 FIXED(17, 2),
INOUT ol_comments6 VARCHAR(100),
INOUT i_id7 FIXED(10), INOUT i_title7 VARCHAR(60),
INOUT i_publisher7 VARCHAR(60), INOUT i_cost7 FIXED(17, 2),
INOUT ol_qty7 FIXED(3), INOUT ol_discount7 FIXED(17, 2),
INOUT ol_comments7 VARCHAR(100),
INOUT i_id8 FIXED(10), INOUT i_title8 VARCHAR(60),
INOUT i_publisher8 VARCHAR(60), INOUT i_cost8 FIXED(17, 2),
INOUT ol_qty8 FIXED(3), INOUT ol_discount8 FIXED(17, 2),
INOUT ol_comments8 VARCHAR(100),
INOUT i_id9 FIXED(10), INOUT i_title9 VARCHAR(60),
INOUT i_publisher9 VARCHAR(60), INOUT i_cost9 FIXED(17, 2),
INOUT ol_qty9 FIXED(3), INOUT ol_discount9 FIXED(17, 2),
INOUT ol_comments9 VARCHAR(100),
INOUT i_id10 FIXED(10), INOUT i_title10 VARCHAR(60),
INOUT i_publisher10 VARCHAR(60), INOUT i_cost10 FIXED(17, 2),
INOUT ol_qty10 FIXED(3), INOUT ol_discount10 FIXED(17, 2),
INOUT ol_comments10 VARCHAR(100),
INOUT i_id11 FIXED(10), INOUT i_title11 VARCHAR(60),
INOUT i_publisher11 VARCHAR(60), INOUT i_cost11 FIXED(17, 2),
INOUT ol_qty11 FIXED(3), INOUT ol_discount11 FIXED(17, 2),
INOUT ol_comments11 VARCHAR(100),
INOUT i_id12 FIXED(10), INOUT i_title12 VARCHAR(60),
INOUT i_publisher12 VARCHAR(60), INOUT i_cost12 FIXED(17, 2),
INOUT ol_qty12 FIXED(3), INOUT ol_discount12 FIXED(17, 2),
INOUT ol_comments12 VARCHAR(100),
INOUT i_id13 FIXED(10), INOUT i_title13 VARCHAR(60),
INOUT i_publisher13 VARCHAR(60), INOUT i_cost13 FIXED(17, 2),
INOUT ol_qty13 FIXED(3), INOUT ol_discount13 FIXED(17, 2),
INOUT ol_comments13 VARCHAR(100),
INOUT i_id14 FIXED(10), INOUT i_title14 VARCHAR(60),
INOUT i_publisher14 VARCHAR(60), INOUT i_cost14 FIXED(17, 2),
INOUT ol_qty14 FIXED(3), INOUT ol_discount14 FIXED(17, 2),
INOUT ol_comments14 VARCHAR(100),
INOUT i_id15 FIXED(10), INOUT i_title15 VARCHAR(60),
INOUT i_publisher15 VARCHAR(60), INOUT i_cost15 FIXED(17, 2),
INOUT ol_qty15 FIXED(3), INOUT ol_discount15 FIXED(17, 2),
INOUT ol_comments15 VARCHAR(100),
INOUT i_id16 FIXED(10), INOUT i_title16 VARCHAR(60),
INOUT i_publisher16 VARCHAR(60), INOUT i_cost16 FIXED(17, 2),
INOUT ol_qty16 FIXED(3), INOUT ol_discount16 FIXED(17, 2),
INOUT ol_comments16 VARCHAR(100),
INOUT i_id17 FIXED(10), INOUT i_title17 VARCHAR(60),
INOUT i_publisher17 VARCHAR(60), INOUT i_cost17 FIXED(17, 2),
INOUT ol_qty17 FIXED(3), INOUT ol_discount17 FIXED(17, 2),
INOUT ol_comments17 VARCHAR(100),
INOUT i_id18 FIXED(10), INOUT i_title18 VARCHAR(60),
INOUT i_publisher18 VARCHAR(60), INOUT i_cost18 FIXED(17, 2),
INOUT ol_qty18 FIXED(3), INOUT ol_discount18 FIXED(17, 2),
INOUT ol_comments18 VARCHAR(100),
INOUT i_id19 FIXED(10), INOUT i_title19 VARCHAR(60),
INOUT i_publisher19 VARCHAR(60), INOUT i_cost19 FIXED(17, 2),
INOUT ol_qty19 FIXED(3), INOUT ol_discount19 FIXED(17, 2),
INOUT ol_comments19 VARCHAR(100),
INOUT i_id20 FIXED(10), INOUT i_title20 VARCHAR(60),
INOUT i_publisher20 VARCHAR(60), INOUT i_cost20 FIXED(17, 2),
INOUT ol_qty20 FIXED(3), INOUT ol_discount20 FIXED(17, 2),
INOUT ol_comments20 VARCHAR(100)) AS
BEGIN
   i_id1 = 0;
   i_title1 = '';
   i_publisher1 = '';
   i_cost1 = 0;
   ol_qty1 = 0;
   ol_discount1 = 0;
   ol_comments1 = '';
   i_id2 = 0;
   i_title2 = '';
   i_publisher2 = '';
   i_cost2 = 0;
   ol_qty2 = 0;
   ol_discount2 = 0;
   ol_comments2 = '';
   i_id3 = 0;
   i_title3 = '';
   i_publisher3 = '';
   i_cost3 = 0;
   ol_qty3 = 0;
   ol_discount3 = 0;
   ol_comments3 = '';
   i_id4 = 0;
   i_title4 = '';
   i_publisher4 = '';
   i_cost4 = 0;
   ol_qty4 = 0;
   ol_discount4 = 0;
   ol_comments4 = '';
   i_id5 = 0;
   i_title5 = '';
   i_publisher5 = '';
   i_cost5 = 0;
   ol_qty5 = 0;
   ol_discount5 = 0;
   ol_comments5 = '';
   i_id6 = 0;
   i_title6 = '';
   i_publisher6 = '';
   i_cost6 = 0;
   ol_qty6 = 0;
   ol_discount6 = 0;
   ol_comments6 = '';
   i_id7 = 0;
   i_title7 = '';
   i_publisher7 = '';
   i_cost7 = 0;
   ol_qty7 = 0;
   ol_discount7 = 0;
   ol_comments7 = '';
   i_id8 = 0;
   i_title8 = '';
   i_publisher8 = '';
   i_cost8 = 0;
   ol_qty8 = 0;
   ol_discount8 = 0;
   ol_comments8 = '';
   i_id9 = 0;
   i_title9 = '';
   i_publisher9 = '';
   i_cost9 = 0;
   ol_qty9 = 0;
   ol_discount9 = 0;
   ol_comments9 = '';
   i_id10 = 0;
   i_title10 = '';
   i_publisher10 = '';
   i_cost10 = 0;
   ol_qty10 = 0;
   ol_discount10 = 0;
   ol_comments10 = '';
   i_id11 = 0;
   i_title11 = '';
   i_publisher11 = '';
   i_cost11 = 0;
   ol_qty11 = 0;
   ol_discount11 = 0;
   ol_comments11 = '';
   i_id12 = 0;
   i_title12 = '';
   i_publisher12 = '';
   i_cost12 = 0;
   ol_qty12 = 0;
   ol_discount12 = 0;
   ol_comments12 = '';
   i_id13 = 0;
   i_title13 = '';
   i_publisher13 = '';
   i_cost13 = 0;
   ol_qty13 = 0;
   ol_discount13 = 0;
   ol_comments13 = '';
   i_id14 = 0;
   i_title14 = '';
   i_publisher14 = '';
   i_cost14 = 0;
   ol_qty14 = 0;
   ol_discount14 = 0;
   ol_comments14 = '';
   i_id15 = 0;
   i_title15 = '';
   i_publisher15 = '';
   i_cost15 = 0;
   ol_qty15 = 0;
   ol_discount15 = 0;
   ol_comments15 = '';
   i_id16 = 0;
   i_title16 = '';
   i_publisher16 = '';
   i_cost16 = 0;
   ol_qty16 = 0;
   ol_discount16 = 0;
   ol_comments16 = '';
   i_id17 = 0;
   i_title17 = '';
   i_publisher17 = '';
   i_cost17 = 0;
   ol_qty17 = 0;
   ol_discount17 = 0;
   ol_comments17 = '';
   i_id18 = 0;
   i_title18 = '';
   i_publisher18 = '';
   i_cost18 = 0;
   ol_qty18 = 0;
   ol_discount18 = 0;
   ol_comments18 = '';
   i_id19 = 0;
   i_title19 = '';
   i_publisher19 = '';
   i_cost19 = 0;
   ol_qty19 = 0;
   ol_discount19 = 0;
   ol_comments19 = '';
   i_id20 = 0;
   i_title20 = '';
   i_publisher20 = '';
   i_cost20 = 0;
   ol_qty20 = 0;
   ol_discount20 = 0;
   ol_comments20 = '';
END;
;
