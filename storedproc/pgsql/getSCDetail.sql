--
--
-- This file is released under the terms of the Artistic License.  Please see
-- the file LICENSE, included in this package, for details.
--
-- Copyright (C) 2002 Open Source Development Lab, Inc.
-- History: 
-- July-2003: Created by Satoshi Nagayasu
-- Aug-12-2003: Removed initSC part and added init _num_item by Jenny Zhang
--
CREATE OR REPLACE FUNCTION getSCDetail (
  NUMERIC(10)
) RETURNS SETOF RECORD AS '
  DECLARE
    _sc_id ALIAS FOR $1;
    _num_item NUMERIC(2,0);
    scl_i_id1 NUMERIC(10,0);
    scl_title1 VARCHAR(60);
    scl_cost1 NUMERIC(17,2);
    scl_srp1 NUMERIC(17,2);
    scl_backing1 VARCHAR(15);
    scl_qty1 NUMERIC(3,0);
    scl_i_id2 NUMERIC(10,0);
    scl_title2 VARCHAR(60);
    scl_cost2 NUMERIC(17,2);
    scl_srp2 NUMERIC(17,2);
    scl_backing2 VARCHAR(15);
    scl_qty2 NUMERIC(3,0);
    scl_i_id3 NUMERIC(10,0);
    scl_title3 VARCHAR(60);
    scl_cost3 NUMERIC(17,2);
    scl_srp3 NUMERIC(17,2);
    scl_backing3 VARCHAR(15);
    scl_qty3 NUMERIC(3,0);
    scl_i_id4 NUMERIC(10,0);
    scl_title4 VARCHAR(60);
    scl_cost4 NUMERIC(17,2);
    scl_srp4 NUMERIC(17,2);
    scl_backing4 VARCHAR(15);
    scl_qty4 NUMERIC(3,0);
    scl_i_id5 NUMERIC(10,0);
    scl_title5 VARCHAR(60);
    scl_cost5 NUMERIC(17,2);
    scl_srp5 NUMERIC(17,2);
    scl_backing5 VARCHAR(15);
    scl_qty5 NUMERIC(3,0);
    scl_i_id6 NUMERIC(10,0);
    scl_title6 VARCHAR(60);
    scl_cost6 NUMERIC(17,2);
    scl_srp6 NUMERIC(17,2);
    scl_backing6 VARCHAR(15);
    scl_qty6 NUMERIC(3,0);
    scl_i_id7 NUMERIC(10,0);
    scl_title7 VARCHAR(60);
    scl_cost7 NUMERIC(17,2);
    scl_srp7 NUMERIC(17,2);
    scl_backing7 VARCHAR(15);
    scl_qty7 NUMERIC(3,0);
    scl_i_id8 NUMERIC(10,0);
    scl_title8 VARCHAR(60);
    scl_cost8 NUMERIC(17,2);
    scl_srp8 NUMERIC(17,2);
    scl_backing8 VARCHAR(15);
    scl_qty8 NUMERIC(3,0);
    scl_i_id9 NUMERIC(10,0);
    scl_title9 VARCHAR(60);
    scl_cost9 NUMERIC(17,2);
    scl_srp9 NUMERIC(17,2);
    scl_backing9 VARCHAR(15);
    scl_qty9 NUMERIC(3,0);
    scl_i_id10 NUMERIC(10,0);
    scl_title10 VARCHAR(60);
    scl_cost10 NUMERIC(17,2);
    scl_srp10 NUMERIC(17,2);
    scl_backing10 VARCHAR(15);
    scl_qty10 NUMERIC(3,0);
    scl_i_id11 NUMERIC(10,0);
    scl_title11 VARCHAR(60);
    scl_cost11 NUMERIC(17,2);
    scl_srp11 NUMERIC(17,2);
    scl_backing11 VARCHAR(15);
    scl_qty11 NUMERIC(3,0);
    scl_i_id12 NUMERIC(10,0);
    scl_title12 VARCHAR(60);
    scl_cost12 NUMERIC(17,2);
    scl_srp12 NUMERIC(17,2);
    scl_backing12 VARCHAR(15);
    scl_qty12 NUMERIC(3,0);
    scl_i_id13 NUMERIC(10,0);
    scl_title13 VARCHAR(60);
    scl_cost13 NUMERIC(17,2);
    scl_srp13 NUMERIC(17,2);
    scl_backing13 VARCHAR(15);
    scl_qty13 NUMERIC(3,0);
    scl_i_id14 NUMERIC(10,0);
    scl_title14 VARCHAR(60);
    scl_cost14 NUMERIC(17,2);
    scl_srp14 NUMERIC(17,2);
    scl_backing14 VARCHAR(15);
    scl_qty14 NUMERIC(3,0);
    scl_i_id15 NUMERIC(10,0);
    scl_title15 VARCHAR(60);
    scl_cost15 NUMERIC(17,2);
    scl_srp15 NUMERIC(17,2);
    scl_backing15 VARCHAR(15);
    scl_qty15 NUMERIC(3,0);
    scl_i_id16 NUMERIC(10,0);
    scl_title16 VARCHAR(60);
    scl_cost16 NUMERIC(17,2);
    scl_srp16 NUMERIC(17,2);
    scl_backing16 VARCHAR(15);
    scl_qty16 NUMERIC(3,0);
    scl_i_id17 NUMERIC(10,0);
    scl_title17 VARCHAR(60);
    scl_cost17 NUMERIC(17,2);
    scl_srp17 NUMERIC(17,2);
    scl_backing17 VARCHAR(15);
    scl_qty17 NUMERIC(3,0);
    scl_i_id18 NUMERIC(10,0);
    scl_title18 VARCHAR(60);
    scl_cost18 NUMERIC(17,2);
    scl_srp18 NUMERIC(17,2);
    scl_backing18 VARCHAR(15);
    scl_qty18 NUMERIC(3,0);
    scl_i_id19 NUMERIC(10,0);
    scl_title19 VARCHAR(60);
    scl_cost19 NUMERIC(17,2);
    scl_srp19 NUMERIC(17,2);
    scl_backing19 VARCHAR(15);
    scl_qty19 NUMERIC(3,0);
    scl_i_id20 NUMERIC(10,0);
    scl_title20 VARCHAR(60);
    scl_cost20 NUMERIC(17,2);
    scl_srp20 NUMERIC(17,2);
    scl_backing20 VARCHAR(15);
    scl_qty20 NUMERIC(3,0);
    refcur REFCURSOR;
    rec RECORD;
  BEGIN
    _num_item := 0;
    OPEN refcur FOR 
      SELECT scl_i_id, scl_title, scl_cost, scl_srp, scl_backing, scl_qty
      FROM shopping_cart_line
      WHERE scl_sc_id = _sc_id;

    FETCH refcur INTO scl_i_id1, scl_title1, scl_cost1,
               scl_srp1, scl_backing1, scl_qty1;
    IF FOUND THEN
    	_num_item := _num_item+1;
 	FETCH refcur INTO scl_i_id2, scl_title2, scl_cost2,
               scl_srp2, scl_backing2, scl_qty2;
    END IF;
    IF FOUND THEN
    	_num_item := _num_item+1;
    	FETCH refcur INTO scl_i_id3, scl_title3, scl_cost3,
               scl_srp3, scl_backing3, scl_qty3;
    END IF;
    IF FOUND THEN
    	_num_item := _num_item+1;
    	FETCH refcur INTO scl_i_id4, scl_title4, scl_cost4,
               scl_srp4, scl_backing4, scl_qty4;
    END IF;
    IF FOUND THEN
    	_num_item := _num_item+1;
    	FETCH refcur INTO scl_i_id5, scl_title5, scl_cost5,
               scl_srp5, scl_backing5, scl_qty5;
    END IF;
    IF FOUND THEN
    	_num_item := _num_item+1;
    	FETCH refcur INTO scl_i_id6, scl_title6, scl_cost6,
               scl_srp6, scl_backing6, scl_qty6;
    END IF;
    IF FOUND THEN
    	_num_item := _num_item+1;
    	FETCH refcur INTO scl_i_id7, scl_title7, scl_cost7,
               scl_srp7, scl_backing7, scl_qty7;
    END IF;
    IF FOUND THEN
    	_num_item := _num_item+1;
    	FETCH refcur INTO scl_i_id8, scl_title8, scl_cost8,
               scl_srp8, scl_backing8, scl_qty8;
    END IF;
    IF FOUND THEN
    	_num_item := _num_item+1;
    	FETCH refcur INTO scl_i_id9, scl_title9, scl_cost9,
               scl_srp9, scl_backing9, scl_qty9;
    END IF;
    IF FOUND THEN
    	_num_item := _num_item+1;
    	FETCH refcur INTO scl_i_id10, scl_title10, scl_cost10,
               scl_srp10, scl_backing10, scl_qty10;
    END IF;
    IF FOUND THEN
    	_num_item := _num_item+1;
    	FETCH refcur INTO scl_i_id11, scl_title11, scl_cost11,
               scl_srp11, scl_backing11, scl_qty11;
    END IF;
    IF FOUND THEN
    	_num_item := _num_item+1;
    	FETCH refcur INTO scl_i_id12, scl_title12, scl_cost12,
               scl_srp12, scl_backing12, scl_qty12;
    END IF;
    IF FOUND THEN
    	_num_item := _num_item+1;
    	FETCH refcur INTO scl_i_id13, scl_title13, scl_cost13,
               scl_srp13, scl_backing13, scl_qty13;
    END IF;
    IF FOUND THEN
    	_num_item := _num_item+1;
    	FETCH refcur INTO scl_i_id14, scl_title14, scl_cost14,
               scl_srp14, scl_backing14, scl_qty14;
    END IF;
    IF FOUND THEN
    	_num_item := _num_item+1;
    	FETCH refcur INTO scl_i_id15, scl_title15, scl_cost15,
               scl_srp15, scl_backing15, scl_qty15;
    END IF;
    IF FOUND THEN
    	_num_item := _num_item+1;
    	FETCH refcur INTO scl_i_id16, scl_title16, scl_cost16,
               scl_srp16, scl_backing16, scl_qty16;
    END IF;
    IF FOUND THEN
    	_num_item := _num_item+1;
    	FETCH refcur INTO scl_i_id17, scl_title17, scl_cost17,
               scl_srp17, scl_backing17, scl_qty17;
    END IF;
    IF FOUND THEN
    	_num_item := _num_item+1;
    	FETCH refcur INTO scl_i_id18, scl_title18, scl_cost18,
               scl_srp18, scl_backing18, scl_qty18;
    END IF;
    IF FOUND THEN
    	_num_item := _num_item+1;
    	FETCH refcur INTO scl_i_id19, scl_title19, scl_cost19,
               scl_srp19, scl_backing19, scl_qty19;
    END IF;
    IF FOUND THEN
    	_num_item := _num_item+1;
    	FETCH refcur INTO scl_i_id20, scl_title20, scl_cost20,
               scl_srp20, scl_backing20, scl_qty20;
    END IF;
    CLOSE refcur;

--
-- return
--
    SELECT 
    _num_item::NUMERIC(2,0),
    scl_i_id1::NUMERIC(10),
    scl_title1::VARCHAR(60),
    scl_cost1::NUMERIC(17,2),
    scl_srp1::NUMERIC(17,2),
    scl_backing1::VARCHAR(15),
    scl_qty1::NUMERIC(3,0),
    scl_i_id2::NUMERIC(10),
    scl_title2::VARCHAR(60),
    scl_cost2::NUMERIC(17,2),
    scl_srp2::NUMERIC(17,2),
    scl_backing2::VARCHAR(15),
    scl_qty2::NUMERIC(3,0),
    scl_i_id3::NUMERIC(10),
    scl_title3::VARCHAR(60),
    scl_cost3::NUMERIC(17,2),
    scl_srp3::NUMERIC(17,2),
    scl_backing3::VARCHAR(15),
    scl_qty3::NUMERIC(3,0),
    scl_i_id4::NUMERIC(10),
    scl_title4::VARCHAR(60),
    scl_cost4::NUMERIC(17,2),
    scl_srp4::NUMERIC(17,2),
    scl_backing4::VARCHAR(15),
    scl_qty4::NUMERIC(3,0),
    scl_i_id5::NUMERIC(10),
    scl_title5::VARCHAR(60),
    scl_cost5::NUMERIC(17,2),
    scl_srp5::NUMERIC(17,2),
    scl_backing5::VARCHAR(15),
    scl_qty5::NUMERIC(3,0),
    scl_i_id6::NUMERIC(10),
    scl_title6::VARCHAR(60),
    scl_cost6::NUMERIC(17,2),
    scl_srp6::NUMERIC(17,2),
    scl_backing6::VARCHAR(15),
    scl_qty6::NUMERIC(3,0),
    scl_i_id7::NUMERIC(10),
    scl_title7::VARCHAR(60),
    scl_cost7::NUMERIC(17,2),
    scl_srp7::NUMERIC(17,2),
    scl_backing7::VARCHAR(15),
    scl_qty7::NUMERIC(3,0),
    scl_i_id8::NUMERIC(10),
    scl_title8::VARCHAR(60),
    scl_cost8::NUMERIC(17,2),
    scl_srp8::NUMERIC(17,2),
    scl_backing8::VARCHAR(15),
    scl_qty8::NUMERIC(3,0),
    scl_i_id9::NUMERIC(10),
    scl_title9::VARCHAR(60),
    scl_cost9::NUMERIC(17,2),
    scl_srp9::NUMERIC(17,2),
    scl_backing9::VARCHAR(15),
    scl_qty9::NUMERIC(3,0),
    scl_i_id10::NUMERIC(10),
    scl_title10::VARCHAR(60),
    scl_cost10::NUMERIC(17,2),
    scl_srp10::NUMERIC(17,2),
    scl_backing10::VARCHAR(15),
    scl_qty10::NUMERIC(3,0),
    scl_i_id11::NUMERIC(10),
    scl_title11::VARCHAR(60),
    scl_cost11::NUMERIC(17,2),
    scl_srp11::NUMERIC(17,2),
    scl_backing11::VARCHAR(15),
    scl_qty11::NUMERIC(3,0),
    scl_i_id12::NUMERIC(10),
    scl_title12::VARCHAR(60),
    scl_cost12::NUMERIC(17,2),
    scl_srp12::NUMERIC(17,2),
    scl_backing12::VARCHAR(15),
    scl_qty12::NUMERIC(3,0),
    scl_i_id13::NUMERIC(10),
    scl_title13::VARCHAR(60),
    scl_cost13::NUMERIC(17,2),
    scl_srp13::NUMERIC(17,2),
    scl_backing13::VARCHAR(15),
    scl_qty13::NUMERIC(3,0),
    scl_i_id14::NUMERIC(10),
    scl_title14::VARCHAR(60),
    scl_cost14::NUMERIC(17,2),
    scl_srp14::NUMERIC(17,2),
    scl_backing14::VARCHAR(15),
    scl_qty14::NUMERIC(3,0),
    scl_i_id15::NUMERIC(10),
    scl_title15::VARCHAR(60),
    scl_cost15::NUMERIC(17,2),
    scl_srp15::NUMERIC(17,2),
    scl_backing15::VARCHAR(15),
    scl_qty15::NUMERIC(3,0),
    scl_i_id16::NUMERIC(10),
    scl_title16::VARCHAR(60),
    scl_cost16::NUMERIC(17,2),
    scl_srp16::NUMERIC(17,2),
    scl_backing16::VARCHAR(15),
    scl_qty16::NUMERIC(3,0),
    scl_i_id17::NUMERIC(10),
    scl_title17::VARCHAR(60),
    scl_cost17::NUMERIC(17,2),
    scl_srp17::NUMERIC(17,2),
    scl_backing17::VARCHAR(15),
    scl_qty17::NUMERIC(3,0),
    scl_i_id18::NUMERIC(10),
    scl_title18::VARCHAR(60),
    scl_cost18::NUMERIC(17,2),
    scl_srp18::NUMERIC(17,2),
    scl_backing18::VARCHAR(15),
    scl_qty18::NUMERIC(3,0),
    scl_i_id19::NUMERIC(10),
    scl_title19::VARCHAR(60),
    scl_cost19::NUMERIC(17,2),
    scl_srp19::NUMERIC(17,2),
    scl_backing19::VARCHAR(15),
    scl_qty19::NUMERIC(3,0),
    scl_i_id20::NUMERIC(10),
    scl_title20::VARCHAR(60),
    scl_cost20::NUMERIC(17,2),
    scl_srp20::NUMERIC(17,2),
    scl_backing20::VARCHAR(15),
    scl_qty20::NUMERIC(3,0)
    INTO rec;
    RETURN NEXT rec;
--  END IF;
  RETURN;
  END;
' LANGUAGE 'plpgsql';
commit;
-- Usage:
-- 
-- SELECT * FROM (
--    _sc_id NUMERIC(10),
-- )
-- AS l(
--    _num_item NUMERIC(2,0),
--    scl_i_id1 NUMERIC(10,0),
--    scl_title1 VARCHAR(60),
--    scl_cost1 NUMERIC(17,2),
--    scl_srp1 NUMERIC(17,2),
--    scl_backing1 VARCHAR(15),
--    scl_qty1 NUMERIC(3,0),
--    scl_i_id2 NUMERIC(10,0),
--    scl_title2 VARCHAR(60),
--    scl_cost2 NUMERIC(17,2),
--    scl_srp2 NUMERIC(17,2),
--    scl_backing2 VARCHAR(15),
--    scl_qty2 NUMERIC(3,0),
--    scl_i_id3 NUMERIC(10,0),
--    scl_title3 VARCHAR(60),
--    scl_cost3 NUMERIC(17,2),
--    scl_srp3 NUMERIC(17,2),
--    scl_backing3 VARCHAR(15),
--    scl_qty3 NUMERIC(3,0),
--    scl_i_id4 NUMERIC(10,0),
--    scl_title4 VARCHAR(60),
--    scl_cost4 NUMERIC(17,2),
--    scl_srp4 NUMERIC(17,2),
--    scl_backing4 VARCHAR(15),
--    scl_qty4 NUMERIC(3,0),
--    scl_i_id5 NUMERIC(10,0),
--    scl_title5 VARCHAR(60),
--    scl_cost5 NUMERIC(17,2),
--    scl_srp5 NUMERIC(17,2),
--    scl_backing5 VARCHAR(15),
--    scl_qty5 NUMERIC(3,0),
--    scl_i_id6 NUMERIC(10,0),
--    scl_title6 VARCHAR(60),
--    scl_cost6 NUMERIC(17,2),
--    scl_srp6 NUMERIC(17,2),
--    scl_backing6 VARCHAR(15),
--    scl_qty6 NUMERIC(3,0),
--    scl_i_id7 NUMERIC(10,0),
--    scl_title7 VARCHAR(60),
--    scl_cost7 NUMERIC(17,2),
--    scl_srp7 NUMERIC(17,2),
--    scl_backing7 VARCHAR(15),
--    scl_qty7 NUMERIC(3,0),
--    scl_i_id8 NUMERIC(10,0),
--    scl_title8 VARCHAR(60),
--    scl_cost8 NUMERIC(17,2),
--    scl_srp8 NUMERIC(17,2),
--    scl_backing8 VARCHAR(15),
--    scl_qty8 NUMERIC(3,0),
--    scl_i_id9 NUMERIC(10,0),
--    scl_title9 VARCHAR(60),
--    scl_cost9 NUMERIC(17,2),
--    scl_srp9 NUMERIC(17,2),
--    scl_backing9 VARCHAR(15),
--    scl_qty9 NUMERIC(3,0),
--    scl_i_id10 NUMERIC(10,0),
--    scl_title10 VARCHAR(60),
--    scl_cost10 NUMERIC(17,2),
--    scl_srp10 NUMERIC(17,2),
--    scl_backing10 VARCHAR(15),
--    scl_qty10 NUMERIC(3,0),
--    scl_i_id11 NUMERIC(10,0),
--    scl_title11 VARCHAR(60),
--    scl_cost11 NUMERIC(17,2),
--    scl_srp11 NUMERIC(17,2),
--    scl_backing11 VARCHAR(15),
--    scl_qty11 NUMERIC(3,0),
--    scl_i_id12 NUMERIC(10,0),
--    scl_title12 VARCHAR(60),
--    scl_cost12 NUMERIC(17,2),
--    scl_srp12 NUMERIC(17,2),
--    scl_backing12 VARCHAR(15),
--    scl_qty12 NUMERIC(3,0),
--    scl_i_id13 NUMERIC(10,0),
--    scl_title13 VARCHAR(60),
--    scl_cost13 NUMERIC(17,2),
--    scl_srp13 NUMERIC(17,2),
--    scl_backing13 VARCHAR(15),
--    scl_qty13 NUMERIC(3,0),
--    scl_i_id14 NUMERIC(10,0),
--    scl_title14 VARCHAR(60),
--    scl_cost14 NUMERIC(17,2),
--    scl_srp14 NUMERIC(17,2),
--    scl_backing14 VARCHAR(15),
--    scl_qty14 NUMERIC(3,0),
--    scl_i_id15 NUMERIC(10,0),
--    scl_title15 VARCHAR(60),
--    scl_cost15 NUMERIC(17,2),
--    scl_srp15 NUMERIC(17,2),
--    scl_backing15 VARCHAR(15),
--    scl_qty15 NUMERIC(3,0),
--    scl_i_id16 NUMERIC(10,0),
--    scl_title16 VARCHAR(60),
--    scl_cost16 NUMERIC(17,2),
--    scl_srp16 NUMERIC(17,2),
--    scl_backing16 VARCHAR(15),
--    scl_qty16 NUMERIC(3,0),
--    scl_i_id17 NUMERIC(10,0),
--    scl_title17 VARCHAR(60),
--    scl_cost17 NUMERIC(17,2),
--    scl_srp17 NUMERIC(17,2),
--    scl_backing17 VARCHAR(15),
--    scl_qty17 NUMERIC(3,0),
--    scl_i_id18 NUMERIC(10,0),
--    scl_title18 VARCHAR(60),
--    scl_cost18 NUMERIC(17,2),
--    scl_srp18 NUMERIC(17,2),
--    scl_backing18 VARCHAR(15),
--    scl_qty18 NUMERIC(3,0),
--    scl_i_id19 NUMERIC(10,0),
--    scl_title19 VARCHAR(60),
--    scl_cost19 NUMERIC(17,2),
--    scl_srp19 NUMERIC(17,2),
--    scl_backing19 VARCHAR(15),
--    scl_qty19 NUMERIC(3,0),
--    scl_i_id20 NUMERIC(10,0),
--    scl_title20 VARCHAR(60),
--    scl_cost20 NUMERIC(17,2),
--    scl_srp20 NUMERIC(17,2),
--    scl_backing20 VARCHAR(15),
--    scl_qty20 NUMERIC(3,0)
--);

