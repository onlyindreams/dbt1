--
--
-- This file is released under the terms of the Artistic License.  Please see
-- the file LICENSE, included in this package, for details.
--
-- Copyright (C) 2002 Open Source Development Lab, Inc.
-- History: 
-- July-2003: Created by Satoshi Nagayasu
--
CREATE OR REPLACE FUNCTION getOrderItems ( NUMERIC(10,0) ) RETURNS SETOF RECORD AS '
  DECLARE
    o_id ALIAS FOR $1;
    num_item NUMERIC(3,0);
    i_id1 NUMERIC(10);
    i_title1 VARCHAR(60);
    i_publisher1 VARCHAR(60);
    i_cost1 NUMERIC(17, 2);
    ol_qty1 NUMERIC(3);
    ol_discount1 NUMERIC(17, 2);
    ol_comments1 VARCHAR(100);
    i_id2 NUMERIC(10); 
    i_title2 VARCHAR(60);
    i_publisher2 VARCHAR(60);
    i_cost2 NUMERIC(17, 2);
    ol_qty2 NUMERIC(3);
    ol_discount2 NUMERIC(17, 2);
    ol_comments2 VARCHAR(100);
    i_id3 NUMERIC(10); 
    i_title3 VARCHAR(60);
    i_publisher3 VARCHAR(60);
    i_cost3 NUMERIC(17, 2);
    ol_qty3 NUMERIC(3); 
    ol_discount3 NUMERIC(17, 2);
    ol_comments3 VARCHAR(100);
    i_id4 NUMERIC(10); 
    i_title4 VARCHAR(60);
    i_publisher4 VARCHAR(60);
    i_cost4 NUMERIC(17, 2);
    ol_qty4 NUMERIC(3);
    ol_discount4 NUMERIC(17, 2);
    ol_comments4 VARCHAR(100);
    i_id5 NUMERIC(10);
    i_title5 VARCHAR(60);
    i_publisher5 VARCHAR(60);
    i_cost5 NUMERIC(17, 2);
    ol_qty5 NUMERIC(3);
    ol_discount5 NUMERIC(17, 2);
    ol_comments5 VARCHAR(100);
    i_id6 NUMERIC(10);
    i_title6 VARCHAR(60);
    i_publisher6 VARCHAR(60);
    i_cost6 NUMERIC(17, 2);
    ol_qty6 NUMERIC(3);
    ol_discount6 NUMERIC(17, 2);
    ol_comments6 VARCHAR(100);
    i_id7 NUMERIC(10);
    i_title7 VARCHAR(60);
    i_publisher7 VARCHAR(60);
    i_cost7 NUMERIC(17, 2);
    ol_qty7 NUMERIC(3);
    ol_discount7 NUMERIC(17, 2);
    ol_comments7 VARCHAR(100);
    i_id8 NUMERIC(10);
    i_title8 VARCHAR(60);
    i_publisher8 VARCHAR(60);
    i_cost8 NUMERIC(17, 2);
    ol_qty8 NUMERIC(3);
    ol_discount8 NUMERIC(17, 2);
    ol_comments8 VARCHAR(100);
    i_id9 NUMERIC(10);
    i_title9 VARCHAR(60);
    i_publisher9 VARCHAR(60);
    i_cost9 NUMERIC(17, 2);
    ol_qty9 NUMERIC(3);
    ol_discount9 NUMERIC(17, 2);
    ol_comments9 VARCHAR(100);
    i_id10 NUMERIC(10);
    i_title10 VARCHAR(60);
    i_publisher10 VARCHAR(60);
    i_cost10 NUMERIC(17, 2);
    ol_qty10 NUMERIC(3);
    ol_discount10 NUMERIC(17, 2);
    ol_comments10 VARCHAR(100);
    i_id11 NUMERIC(10);
    i_title11 VARCHAR(60);
    i_publisher11 VARCHAR(60);
    i_cost11 NUMERIC(17, 2);
    ol_qty11 NUMERIC(3);
    ol_discount11 NUMERIC(17, 2);
    ol_comments11 VARCHAR(100);
    i_id12 NUMERIC(10);
    i_title12 VARCHAR(60);
    i_publisher12 VARCHAR(60);
    i_cost12 NUMERIC(17, 2);
    ol_qty12 NUMERIC(3);
    ol_discount12 NUMERIC(17, 2);
    ol_comments12 VARCHAR(100);
    i_id13 NUMERIC(10);
    i_title13 VARCHAR(60);
    i_publisher13 VARCHAR(60);
    i_cost13 NUMERIC(17, 2);
    ol_qty13 NUMERIC(3);
    ol_discount13 NUMERIC(17, 2);
    ol_comments13 VARCHAR(100);
    i_id14 NUMERIC(10);
    i_title14 VARCHAR(60);
    i_publisher14 VARCHAR(60);
    i_cost14 NUMERIC(17, 2);
    ol_qty14 NUMERIC(3);
    ol_discount14 NUMERIC(17, 2);
    ol_comments14 VARCHAR(100);
    i_id15 NUMERIC(10);
    i_title15 VARCHAR(60);
    i_publisher15 VARCHAR(60);
    i_cost15 NUMERIC(17, 2);
    ol_qty15 NUMERIC(3);
    ol_discount15 NUMERIC(17, 2);
    ol_comments15 VARCHAR(100);
    i_id16 NUMERIC(10);
    i_title16 VARCHAR(60);
    i_publisher16 VARCHAR(60);
    i_cost16 NUMERIC(17, 2);
    ol_qty16 NUMERIC(3);
    ol_discount16 NUMERIC(17, 2);
    ol_comments16 VARCHAR(100);
    i_id17 NUMERIC(10);
    i_title17 VARCHAR(60);
    i_publisher17 VARCHAR(60);
    i_cost17 NUMERIC(17, 2);
    ol_qty17 NUMERIC(3);
    ol_discount17 NUMERIC(17, 2);
    ol_comments17 VARCHAR(100);
    i_id18 NUMERIC(10);
    i_title18 VARCHAR(60);
    i_publisher18 VARCHAR(60);
    i_cost18 NUMERIC(17, 2);
    ol_qty18 NUMERIC(3);
    ol_discount18 NUMERIC(17, 2);
    ol_comments18 VARCHAR(100);
    i_id19 NUMERIC(10);
    i_title19 VARCHAR(60);
    i_publisher19 VARCHAR(60);
    i_cost19 NUMERIC(17, 2);
    ol_qty19 NUMERIC(3);
    ol_discount19 NUMERIC(17, 2);
    ol_comments19 VARCHAR(100);
    i_id20 NUMERIC(10);
    i_title20 VARCHAR(60);
    i_publisher20 VARCHAR(60);    
    i_cost20 NUMERIC(17, 2);
    ol_qty20 NUMERIC(3);
    ol_discount20 NUMERIC(17, 2);
    ol_comments20 VARCHAR(100);
    refcur REFCURSOR;
    rec RECORD;
  BEGIN
-- Copy from initOrderItems.sql (See, README.initOrderItems)
-- FROM HERE -----------------------------------------------
    num_item := 0;
    i_id1 := 0;
    i_title1 := '''';
    i_publisher1 := '''';
    i_cost1 := 0;
    ol_qty1 := 0;
    ol_discount1 := 0;
    ol_comments1 := '''';
    i_id2 := 0;
    i_title2 := '''';
    i_publisher2 := '''';
    i_cost2 := 0;
    ol_qty2 := 0;
    ol_discount2 := 0;
    ol_comments2 := '''';
    i_id3 := 0;
    i_title3 := '''';
    i_publisher3 := '''';
    i_cost3 := 0;
    ol_qty3 := 0;
    ol_discount3 := 0;
    ol_comments3 := '''';
    i_id4 := 0;
    i_title4 := '''';
    i_publisher4 := '''';
    i_cost4 := 0;
    ol_qty4 := 0;
    ol_discount4 := 0;
    ol_comments4 := '''';
    i_id5 := 0;
    i_title5 := '''';
    i_publisher5 := '''';
    i_cost5 := 0;
    ol_qty5 := 0;
    ol_discount5 := 0;
    ol_comments5 := '''';
    i_id6 := 0;
    i_title6 := '''';
    i_publisher6 := '''';
    i_cost6 := 0;
    ol_qty6 := 0;
    ol_discount6 := 0;
    ol_comments6 := '''';
    i_id7 := 0;
    i_title7 := '''';
    i_publisher7 := '''';
    i_cost7 := 0;
    ol_qty7 := 0;
    ol_discount7 := 0;
    ol_comments7 := '''';
    i_id8 := 0;
    i_title8 := '''';
    i_publisher8 := '''';
    i_cost8 := 0;
    ol_qty8 := 0;
    ol_discount8 := 0;
    ol_comments8 := '''';
    i_id9 := 0;
    i_title9 := '''';
    i_publisher9 := '''';
    i_cost9 := 0;
    ol_qty9 := 0;
    ol_discount9 := 0;
    ol_comments9 := '''';
    i_id10 := 0;
    i_title10 := '''';
    i_publisher10 := '''';
    i_cost10 := 0;
    ol_qty10 := 0;
    ol_discount10 := 0;
    ol_comments10 := '''';
    i_id11 := 0;
    i_title11 := '''';
    i_publisher11 := '''';
    i_cost11 := 0;
    ol_qty11 := 0;
    ol_discount11 := 0;
    ol_comments11 := '''';
    i_id12 := 0;
    i_title12 := '''';
    i_publisher12 := '''';
    i_cost12 := 0;
    ol_qty12 := 0;
    ol_discount12 := 0;
    ol_comments12 := '''';
    i_id13 := 0;
    i_title13 := '''';
    i_publisher13 := '''';
    i_cost13 := 0;
    ol_qty13 := 0;
    ol_discount13 := 0;
    ol_comments13 := '''';
    i_id14 := 0;
    i_title14 := '''';
    i_publisher14 := '''';
    i_cost14 := 0;
    ol_qty14 := 0;
    ol_discount14 := 0;
    ol_comments14 := '''';
    i_id15 := 0;
    i_title15 := '''';
    i_publisher15 := '''';
    i_cost15 := 0;
    ol_qty15 := 0;
    ol_discount15 := 0;
    ol_comments15 := '''';
    i_id16 := 0;
    i_title16 := '''';
    i_publisher16 := '''';
    i_cost16 := 0;
    ol_qty16 := 0;
    ol_discount16 := 0;
    ol_comments16 := '''';
    i_id17 := 0;
    i_title17 := '''';
    i_publisher17 := '''';
    i_cost17 := 0;
    ol_qty17 := 0;
    ol_discount17 := 0;
    ol_comments17 := '''';
    i_id18 := 0;
    i_title18 := '''';
    i_publisher18 := '''';
    i_cost18 := 0;
    ol_qty18 := 0;
    ol_discount18 := 0;
    ol_comments18 := '''';
    i_id19 := 0;
    i_title19 := '''';
    i_publisher19 := '''';
    i_cost19 := 0;
    ol_qty19 := 0;
    ol_discount19 := 0;
    ol_comments19 := '''';
    i_id20 := 0;
    i_title20 := '''';
    i_publisher20 := '''';
    i_cost20 := 0;
    ol_qty20 := 0;
    ol_discount20 := 0;
    ol_comments20 := '''';

-- TO HERE -------------------------------------------------
-- Copy from initOrderItems.sql (See, README.initOrderItems)

    PERFORM ol_i_id, i_title, i_publisher, i_cost, 
            ol_qty, ol_discount, ol_comments 
    FROM item, order_line WHERE ol_o_id = o_id AND ol_i_id = i_id;

    IF NOT FOUND THEN
      RETURN;
    END IF;

--
-- Open
--
    OPEN refcur FOR SELECT i_id, i_title, i_publisher, i_cost, ol_qty, ol_discount, ol_comments FROM item, order_line WHERE ol_o_id = o_id AND ol_i_id = i_id;

--
-- The first fetch
--
    FETCH refcur INTO i_id1, i_title1, i_publisher1, i_cost1, ol_qty1, ol_discount1, ol_comments1;

    IF FOUND THEN
      num_item := num_item + 1;
      FETCH refcur INTO i_id2, i_title2, i_publisher2, i_cost2, ol_qty2, ol_discount2, ol_comments2;
    END IF;

    IF FOUND THEN
      num_item := num_item + 1;
      FETCH refcur INTO i_id3, i_title3, i_publisher3, i_cost3, ol_qty3, ol_discount3, ol_comments3;
    END IF;

    IF FOUND THEN
      num_item := num_item + 1;
      FETCH refcur INTO i_id4, i_title4, i_publisher4, i_cost4, ol_qty4, ol_discount4, ol_comments4;
    END IF;

    IF FOUND THEN
      num_item := num_item + 1;
      FETCH refcur INTO i_id5, i_title5, i_publisher5, i_cost5, ol_qty5, ol_discount5, ol_comments5;
    END IF;

    IF FOUND THEN
      num_item := num_item + 1;
      FETCH refcur INTO i_id6, i_title6, i_publisher6, i_cost6, ol_qty6, ol_discount6, ol_comments6;
    END IF;

    IF FOUND THEN
      num_item := num_item + 1;
      FETCH refcur INTO i_id7, i_title7, i_publisher7, i_cost7, ol_qty7, ol_discount7, ol_comments7;
    END IF;

    IF FOUND THEN
      num_item := num_item + 1;
      FETCH refcur INTO i_id8, i_title8, i_publisher8, i_cost8, ol_qty8, ol_discount8, ol_comments8;
    END IF;

    IF FOUND THEN
      num_item := num_item + 1;
      FETCH refcur INTO i_id9, i_title9, i_publisher9, i_cost9, ol_qty9, ol_discount9, ol_comments9;
    END IF;

    IF FOUND THEN
      num_item := num_item + 1;
      FETCH refcur INTO i_id10, i_title10, i_publisher10, i_cost10, ol_qty10, ol_discount10, ol_comments10;
    END IF;

    IF FOUND THEN
      num_item := num_item + 1;
      FETCH refcur INTO i_id11, i_title11, i_publisher11, i_cost11, ol_qty11, ol_discount11, ol_comments11;
    END IF;

    IF FOUND THEN
      num_item := num_item + 1;
      FETCH refcur INTO i_id12, i_title12, i_publisher12, i_cost12, ol_qty12, ol_discount12, ol_comments12;
    END IF;

    IF FOUND THEN      
      num_item := num_item + 1;
      FETCH refcur INTO i_id13, i_title13, i_publisher13, i_cost13, ol_qty13, ol_discount13, ol_comments13;
    END IF;

    IF FOUND THEN      
      num_item := num_item + 1;
      FETCH refcur INTO i_id14, i_title14, i_publisher14, i_cost14, ol_qty14, ol_discount14, ol_comments14;
    END IF;

    IF FOUND THEN            
      num_item := num_item + 1;
      FETCH refcur INTO i_id15, i_title15, i_publisher15, i_cost15, ol_qty15, ol_discount15, ol_comments15;
    END IF;

    IF FOUND THEN      
      num_item := num_item + 1;
      FETCH refcur INTO i_id16, i_title16, i_publisher16, i_cost16, ol_qty16, ol_discount16, ol_comments16;
    END IF;

    IF FOUND THEN      
      num_item := num_item + 1;
      FETCH refcur INTO i_id17, i_title17, i_publisher17, i_cost17, ol_qty17, ol_discount17, ol_comments17;
    END IF;

    IF FOUND THEN             
      num_item := num_item + 1;
      FETCH refcur INTO i_id18, i_title18, i_publisher18, i_cost18, ol_qty18, ol_discount18, ol_comments18;
    END IF;

    IF FOUND THEN            
      num_item := num_item + 1;
      FETCH refcur INTO i_id19, i_title19, i_publisher19, i_cost19, ol_qty19, ol_discount19, ol_comments19;
    END IF;

    IF FOUND THEN            
      num_item := num_item + 1;
      FETCH refcur INTO i_id20, i_title20, i_publisher20, i_cost20, ol_qty20, ol_discount20, ol_comments20;
    END IF;

    CLOSE refcur;	

/******************************************************************
 *
 *                       Return result sets
 *
 ******************************************************************/
    SELECT 
    num_item::NUMERIC(3,0),
    i_id1::NUMERIC(10),
    i_title1::VARCHAR(60),
    i_publisher1::VARCHAR(60),
    i_cost1::NUMERIC(17,2),
    ol_qty1::NUMERIC(3),
    ol_discount1::NUMERIC(17,2),
    ol_comments1::VARCHAR(100),
    i_id2::NUMERIC(10),
    i_title2::VARCHAR(60),
    i_publisher2::VARCHAR(60),
    i_cost2::NUMERIC(17,2),
    ol_qty2::NUMERIC(3),
    ol_discount2::NUMERIC(17,2),
    ol_comments2::VARCHAR(100),
    i_id3::NUMERIC(10),
    i_title3::VARCHAR(60),
    i_publisher3::VARCHAR(60),
    i_cost3::NUMERIC(17,2),
    ol_qty3::NUMERIC(3),
    ol_discount3::NUMERIC(17,2),
    ol_comments3::VARCHAR(100),
    i_id4::NUMERIC(10),
    i_title4::VARCHAR(60),
    i_publisher4::VARCHAR(60),
    i_cost4::NUMERIC(17,2),
    ol_qty4::NUMERIC(3),
    ol_discount4::NUMERIC(17,2),
    ol_comments4::VARCHAR(100),
    i_id5::NUMERIC(10),
    i_title5::VARCHAR(60),
    i_publisher5::VARCHAR(60),
    i_cost5::NUMERIC(17,2),
    ol_qty5::NUMERIC(3),
    ol_discount5::NUMERIC(17,2),
    ol_comments5::VARCHAR(100),
    i_id6::NUMERIC(10),
    i_title6::VARCHAR(60),
    i_publisher6::VARCHAR(60),
    i_cost6::NUMERIC(17,2),
    ol_qty6::NUMERIC(3),
    ol_discount6::NUMERIC(17,2),
    ol_comments6::VARCHAR(100),
    i_id7::NUMERIC(10),
    i_title7::VARCHAR(60),
    i_publisher7::VARCHAR(60),
    i_cost7::NUMERIC(17,2),
    ol_qty7::NUMERIC(3),
    ol_discount7::NUMERIC(17,2),
    ol_comments7::VARCHAR(100),
    i_id8::NUMERIC(10),
    i_title8::VARCHAR(60),
    i_publisher8::VARCHAR(60),
    i_cost8::NUMERIC(17,2),
    ol_qty8::NUMERIC(3),
    ol_discount8::NUMERIC(17,2),
    ol_comments8::VARCHAR(100),
    i_id9::NUMERIC(10),
    i_title9::VARCHAR(60),
    i_publisher9::VARCHAR(60),
    i_cost9::NUMERIC(17,2),
    ol_qty9::NUMERIC(3),
    ol_discount9::NUMERIC(17,2),
    ol_comments9::VARCHAR(100),
    i_id10::NUMERIC(10),
    i_title10::VARCHAR(60),
    i_publisher10::VARCHAR(60),
    i_cost10::NUMERIC(17,2),
    ol_qty10::NUMERIC(3),
    ol_discount10::NUMERIC(17,2),
    ol_comments10::VARCHAR(100),
    i_id11::NUMERIC(10),
    i_title11::VARCHAR(60),
    i_publisher11::VARCHAR(60),
    i_cost11::NUMERIC(17,2),
    ol_qty11::NUMERIC(3),
    ol_discount11::NUMERIC(17,2),
    ol_comments11::VARCHAR(100),
    i_id12::NUMERIC(10),
    i_title12::VARCHAR(60),
    i_publisher12::VARCHAR(60),
    i_cost12::NUMERIC(17,2),
    ol_qty12::NUMERIC(3),
    ol_discount12::NUMERIC(17,2),
    ol_comments12::VARCHAR(100),
    i_id13::NUMERIC(10),
    i_title13::VARCHAR(60),
    i_publisher13::VARCHAR(60),
    i_cost13::NUMERIC(17,2),
    ol_qty13::NUMERIC(3),
    ol_discount13::NUMERIC(17,2),
    ol_comments13::VARCHAR(100),
    i_id14::NUMERIC(10),
    i_title14::VARCHAR(60),
    i_publisher14::VARCHAR(60),
    i_cost14::NUMERIC(17,2),
    ol_qty14::NUMERIC(3),
    ol_discount14::NUMERIC(17,2),
    ol_comments14::VARCHAR(100),
    i_id15::NUMERIC(10),
    i_title15::VARCHAR(60),
    i_publisher15::VARCHAR(60),
    i_cost15::NUMERIC(17,2),
    ol_qty15::NUMERIC(3),
    ol_discount15::NUMERIC(17,2),
    ol_comments15::VARCHAR(100),
    i_id16::NUMERIC(10),
    i_title16::VARCHAR(60),
    i_publisher16::VARCHAR(60),
    i_cost16::NUMERIC(17,2),
    ol_qty16::NUMERIC(3),
    ol_discount16::NUMERIC(17,2),
    ol_comments16::VARCHAR(100),
    i_id17::NUMERIC(10),
    i_title17::VARCHAR(60),
    i_publisher17::VARCHAR(60),
    i_cost17::NUMERIC(17,2),
    ol_qty17::NUMERIC(3),
    ol_discount17::NUMERIC(17,2),
    ol_comments17::VARCHAR(100),
    i_id18::NUMERIC(10),
    i_title18::VARCHAR(60),
    i_publisher18::VARCHAR(60),
    i_cost18::NUMERIC(17,2),
    ol_qty18::NUMERIC(3),
    ol_discount18::NUMERIC(17,2),
    ol_comments18::VARCHAR(100),
    i_id19::NUMERIC(10),
    i_title19::VARCHAR(60),
    i_publisher19::VARCHAR(60),
    i_cost19::NUMERIC(17,2),
    ol_qty19::NUMERIC(3),
    ol_discount19::NUMERIC(17,2),
    ol_comments19::VARCHAR(100),
    i_id20::NUMERIC(10),
    i_title20::VARCHAR(60),
    i_publisher20::VARCHAR(60),
    i_cost20::NUMERIC(17,2),
    ol_qty20::NUMERIC(3),
    ol_discount20::NUMERIC(17,2),
    ol_comments20::VARCHAR(100)
    INTO rec;

    RETURN NEXT rec;
    RETURN;
  END;  
' LANGUAGE 'plpgsql';
commit;

-- 
-- Usage
-- 
-- SELECT * FROM getOrderItems(  o_id NUMERIC(10,0) ) 
-- AS l(  num_item NUMERIC(3,0),
--  i_id1 NUMERIC(10),
--  i_title1 VARCHAR(60),
--  i_publisher1 VARCHAR(60),
--  i_cost1 NUMERIC(17,2),
--  ol_qty1 NUMERIC(3),
--  ol_discount1 NUMERIC(17,2),
--  ol_comments1 VARCHAR(100),
--  i_id2 NUMERIC(10),
--  i_title2 VARCHAR(60),
--  i_publisher2 VARCHAR(60),
--  i_cost2 NUMERIC(17,2),
--  ol_qty2 NUMERIC(3),
--  ol_discount2 NUMERIC(17,2),
--  ol_comments2 VARCHAR(100),
--  i_id3 NUMERIC(10),
--  i_title3 VARCHAR(60),
--  i_publisher3 VARCHAR(60),
--  i_cost3 NUMERIC(17,2),
--  ol_qty3 NUMERIC(3),
--  ol_discount3 NUMERIC(17,2),
--  ol_comments3 VARCHAR(100),
--  i_id4 NUMERIC(10),
--  i_title4 VARCHAR(60),
--  i_publisher4 VARCHAR(60),
--  i_cost4 NUMERIC(17,2),
--  ol_qty4 NUMERIC(3),
--  ol_discount4 NUMERIC(17,2),
--  ol_comments4 VARCHAR(100),
--  i_id5 NUMERIC(10),
--  i_title5 VARCHAR(60),
--  i_publisher5 VARCHAR(60),
--  i_cost5 NUMERIC(17,2),
--  ol_qty5 NUMERIC(3),
--  ol_discount5 NUMERIC(17,2),
--  ol_comments5 VARCHAR(100),
--  i_id6 NUMERIC(10),
--  i_title6 VARCHAR(60),
--  i_publisher6 VARCHAR(60),
--  i_cost6 NUMERIC(17,2),
--  ol_qty6 NUMERIC(3),
--  ol_discount6 NUMERIC(17,2),
--  ol_comments6 VARCHAR(100),
--  i_id7 NUMERIC(10),
--  i_title7 VARCHAR(60),
--  i_publisher7 VARCHAR(60),
--  i_cost7 NUMERIC(17,2),
--  ol_qty7 NUMERIC(3),
--  ol_discount7 NUMERIC(17,2),
--  ol_comments7 VARCHAR(100),
--  i_id8 NUMERIC(10),
--  i_title8 VARCHAR(60),
--  i_publisher8 VARCHAR(60),
--  i_cost8 NUMERIC(17,2),
--  ol_qty8 NUMERIC(3),
--  ol_discount8 NUMERIC(17,2),
--  ol_comments8 VARCHAR(100),
--  i_id9 NUMERIC(10),
--  i_title9 VARCHAR(60),
--  i_publisher9 VARCHAR(60),
--  i_cost9 NUMERIC(17,2),
--  ol_qty9 NUMERIC(3),
--  ol_discount9 NUMERIC(17,2),
--  ol_comments9 VARCHAR(100),
--  i_id10 NUMERIC(10),
--  i_title10 VARCHAR(60),
--  i_publisher10 VARCHAR(60),
--  i_cost10 NUMERIC(17,2),
--  ol_qty10 NUMERIC(3),
--  ol_discount10 NUMERIC(17,2),
--  ol_comments10 VARCHAR(100),
--  i_id11 NUMERIC(10),
--  i_title11 VARCHAR(60),
--  i_publisher11 VARCHAR(60),
--  i_cost11 NUMERIC(17,2),
--  ol_qty11 NUMERIC(3),
--  ol_discount11 NUMERIC(17,2),
--  ol_comments11 VARCHAR(100),
--  i_id12 NUMERIC(10),
--  i_title12 VARCHAR(60),
--  i_publisher12 VARCHAR(60),
--  i_cost12 NUMERIC(17,2),
--  ol_qty12 NUMERIC(3),
--  ol_discount12 NUMERIC(17,2),
--  ol_comments12 VARCHAR(100),
--  i_id13 NUMERIC(10),
--  i_title13 VARCHAR(60),
--  i_publisher13 VARCHAR(60),
--  i_cost13 NUMERIC(17,2),
--  ol_qty13 NUMERIC(3),
--  ol_discount13 NUMERIC(17,2),
--  ol_comments13 VARCHAR(100),
--  i_id14 NUMERIC(10),
--  i_title14 VARCHAR(60),
--  i_publisher14 VARCHAR(60),
--  i_cost14 NUMERIC(17,2),
--  ol_qty14 NUMERIC(3),
--  ol_discount14 NUMERIC(17,2),
--  ol_comments14 VARCHAR(100),
--  i_id15 NUMERIC(10),
--  i_title15 VARCHAR(60),
--  i_publisher15 VARCHAR(60),
--  i_cost15 NUMERIC(17,2),
--  ol_qty15 NUMERIC(3),
--  ol_discount15 NUMERIC(17,2),
--  ol_comments15 VARCHAR(100),
--  i_id16 NUMERIC(10),
--  i_title16 VARCHAR(60),
--  i_publisher16 VARCHAR(60),
--  i_cost16 NUMERIC(17,2),
--  ol_qty16 NUMERIC(3),
--  ol_discount16 NUMERIC(17,2),
--  ol_comments16 VARCHAR(100),
--  i_id17 NUMERIC(10),
--  i_title17 VARCHAR(60),
--  i_publisher17 VARCHAR(60),
--  i_cost17 NUMERIC(17,2),
--  ol_qty17 NUMERIC(3),
--  ol_discount17 NUMERIC(17,2),
--  ol_comments17 VARCHAR(100),
--  i_id18 NUMERIC(10),
--  i_title18 VARCHAR(60),
--  i_publisher18 VARCHAR(60),
--  i_cost18 NUMERIC(17,2),
--  ol_qty18 NUMERIC(3),
--  ol_discount18 NUMERIC(17,2),
--  ol_comments18 VARCHAR(100),
--  i_id19 NUMERIC(10),
--  i_title19 VARCHAR(60),
--  i_publisher19 VARCHAR(60),
--  i_cost19 NUMERIC(17,2),
--  ol_qty19 NUMERIC(3),
--  ol_discount19 NUMERIC(17,2),
--  ol_comments19 VARCHAR(100),
--  i_id20 NUMERIC(10),
--  i_title20 VARCHAR(60),
--  i_publisher20 VARCHAR(60),
--  i_cost20 NUMERIC(17,2),
--  ol_qty20 NUMERIC(3),
--  ol_discount20 NUMERIC(17,2),
--  ol_comments20 VARCHAR(100) );
