--
--
-- This file is released under the terms of the Artistic License.  Please see
-- the file LICENSE, included in this package, for details.
--
-- Copyright (C) 2002 Open Source Development Lab, Inc.
-- History:
-- July-2003: Created by Satoshi Nagayasu & Hideyuki Kawashima
-- Aug-13-2003: Rewrote and tested by Jenny Zhang
-- Feb-9-2003: Changed the input to arrays for PG 7.4 by Jenny Zhang
\set AUTOCOMMIT off
CREATE OR REPLACE FUNCTION shopping_cart (
  NUMERIC(10),
  NUMERIC(10),
  NUMERIC(2),
  NUMERIC(1),
  NUMERIC(10),
  NUMERIC(10),
  NUMERIC[],
  NUMERIC[]
) RETURNS RECORD AS '
  DECLARE
    C_ID ALIAS FOR $1;
    _sc_id ALIAS FOR $2;
    _itemcount ALIAS FOR $3;
    _add_flag ALIAS FOR $4;
    _i_id ALIAS FOR $5;
    _pp_i_id ALIAS FOR $6;
    _i_id_array ALIAS FOR $7;
    _qty_array ALIAS FOR $8;
-- we can not asign value to _sc_id and _itemcount, since they are CONSTANT
-- declare t_sc_id and itemcount 
    t_sc_id NUMERIC(10);
    itemcount NUMERIC(2);
    scl_i_id1 NUMERIC(10);
    scl_title1 VARCHAR(60);
    scl_cost1 NUMERIC(17,2);
    scl_srp1 NUMERIC(17,2);
    scl_backing1 VARCHAR(15);
    scl_qty1 NUMERIC(3);
    scl_i_id2 NUMERIC(10);
    scl_title2 VARCHAR(60);
    scl_cost2 NUMERIC(17,2);
    scl_srp2 NUMERIC(17,2);
    scl_backing2 VARCHAR(15);
    scl_qty2 NUMERIC(3);
    scl_i_id3 NUMERIC(10);
    scl_title3 VARCHAR(60);
    scl_cost3 NUMERIC(17,2);
    scl_srp3 NUMERIC(17,2);
    scl_backing3 VARCHAR(15);
    scl_qty3 NUMERIC(3);
    scl_i_id4 NUMERIC(10);
    scl_title4 VARCHAR(60);
    scl_cost4 NUMERIC(17,2);
    scl_srp4 NUMERIC(17,2);
    scl_backing4 VARCHAR(15);
    scl_qty4 NUMERIC(3);
    scl_i_id5 NUMERIC(10);
    scl_title5 VARCHAR(60);
    scl_cost5 NUMERIC(17,2);
    scl_srp5 NUMERIC(17,2);
    scl_backing5 VARCHAR(15);
    scl_qty5 NUMERIC(3);
    scl_i_id6 NUMERIC(10);
    scl_title6 VARCHAR(60);
    scl_cost6 NUMERIC(17,2);
    scl_srp6 NUMERIC(17,2);
    scl_backing6 VARCHAR(15);
    scl_qty6 NUMERIC(3);
    scl_i_id7 NUMERIC(10);
    scl_title7 VARCHAR(60);
    scl_cost7 NUMERIC(17,2);
    scl_srp7 NUMERIC(17,2);
    scl_backing7 VARCHAR(15);
    scl_qty7 NUMERIC(3);
    scl_i_id8 NUMERIC(10);
    scl_title8 VARCHAR(60);
    scl_cost8 NUMERIC(17,2);
    scl_srp8 NUMERIC(17,2);
    scl_backing8 VARCHAR(15);
    scl_qty8 NUMERIC(3);
    scl_i_id9 NUMERIC(10);
    scl_title9 VARCHAR(60);
    scl_cost9 NUMERIC(17,2);
    scl_srp9 NUMERIC(17,2);
    scl_backing9 VARCHAR(15);
    scl_qty9 NUMERIC(3);
    scl_i_id10 NUMERIC(10);
    scl_title10 VARCHAR(60);
    scl_cost10 NUMERIC(17,2);
    scl_srp10 NUMERIC(17,2);
    scl_backing10 VARCHAR(15);
    scl_qty10 NUMERIC(3);
    scl_i_id11 NUMERIC(10);
    scl_title11 VARCHAR(60);
    scl_cost11 NUMERIC(17,2);
    scl_srp11 NUMERIC(17,2);
    scl_backing11 VARCHAR(15);
    scl_qty11 NUMERIC(3);
    scl_i_id12 NUMERIC(10);
    scl_title12 VARCHAR(60);
    scl_cost12 NUMERIC(17,2);
    scl_srp12 NUMERIC(17,2);
    scl_backing12 VARCHAR(15);
    scl_qty12 NUMERIC(3);
    scl_i_id13 NUMERIC(10);
    scl_title13 VARCHAR(60);
    scl_cost13 NUMERIC(17,2);
    scl_srp13 NUMERIC(17,2);
    scl_backing13 VARCHAR(15);
    scl_qty13 NUMERIC(3);
    scl_i_id14 NUMERIC(10);
    scl_title14 VARCHAR(60);
    scl_cost14 NUMERIC(17,2);
    scl_srp14 NUMERIC(17,2);
    scl_backing14 VARCHAR(15);
    scl_qty14 NUMERIC(3);
    scl_i_id15 NUMERIC(10);
    scl_title15 VARCHAR(60);
    scl_cost15 NUMERIC(17,2);
    scl_srp15 NUMERIC(17,2);
    scl_backing15 VARCHAR(15);
    scl_qty15 NUMERIC(3);
    scl_i_id16 NUMERIC(10);
    scl_title16 VARCHAR(60);
    scl_cost16 NUMERIC(17,2);
    scl_srp16 NUMERIC(17,2);
    scl_backing16 VARCHAR(15);
    scl_qty16 NUMERIC(3);
    scl_i_id17 NUMERIC(10);
    scl_title17 VARCHAR(60);
    scl_cost17 NUMERIC(17,2);
    scl_srp17 NUMERIC(17,2);
    scl_backing17 VARCHAR(15);
    scl_qty17 NUMERIC(3);
    scl_i_id18 NUMERIC(10);
    scl_title18 VARCHAR(60);
    scl_cost18 NUMERIC(17,2);
    scl_srp18 NUMERIC(17,2);
    scl_backing18 VARCHAR(15);
    scl_qty18 NUMERIC(3);
    scl_i_id19 NUMERIC(10);
    scl_title19 VARCHAR(60);
    scl_cost19 NUMERIC(17,2);
    scl_srp19 NUMERIC(17,2);
    scl_backing19 VARCHAR(15);
    scl_qty19 NUMERIC(3);
    scl_i_id20 NUMERIC(10);
    scl_title20 VARCHAR(60);
    scl_cost20 NUMERIC(17,2);
    scl_srp20 NUMERIC(17,2);
    scl_backing20 VARCHAR(15);
    scl_qty20 NUMERIC(3);
    pp_i_id1 NUMERIC(10);
    pp_i_t1 NUMERIC(10);
    pp_i_id2 NUMERIC(10);
    pp_i_t2 NUMERIC(10);
    pp_i_id3 NUMERIC(10);
    pp_i_t3 NUMERIC(10);
    pp_i_id4 NUMERIC(10);
    pp_i_t4 NUMERIC(10);
    pp_i_id5 NUMERIC(10);
    pp_i_t5 NUMERIC(10);
    -- VARs
    i smallint;
    sc_subtotal NUMERIC(17,2);
    rec RECORD;
  BEGIN

--    RAISE NOTICE ''_sc_id=%, _add_flag=%, _itemcount=%, _i_id=%, _pp_i_id=%, c_id=%'', _sc_id, _add_flag, _itemcount, _i_id, _pp_i_id, c_id;
    --LOCK TABLE shopping_cart_line in EXCLUSIVE MODE;

    -- we have only three situations:
    -- from HO, BS, NP, BR, SRQ, SRS to SC, view cart the first time (_sc_id=0)
    -- or existing shopping cart (_sc_id != 0)
    -- 		_add_flag=0 _itemcount=0, _sc_id=0
    -- from PD to SC, add a single item to the cart
    --		_add_flag=1 _itemcount=1
    -- from SC to SC, refresh the cart
    --		_add_flag=0, _itemcount>0
    IF ( _sc_id=0 ) THEN 
	SELECT createSC(c_id) INTO t_sc_id;
    ELSE
	t_sc_id := _sc_id;
    END IF;
--    RAISE NOTICE ''sc_id=%'', sc_id;
    IF ( _add_flag=1 OR ( _sc_id=0 AND  _add_flag=0 AND _itemcount=0 )) THEN
--    	RAISE NOTICE ''call addToSC'';
	PERFORM addToSC(t_sc_id, _add_flag, _i_id);
    ELSE
	--FOR i in array_lower(_i_id_array,1) .. array_upper(_i_id_array,1) LOOP 
	FOR i in 1..(_itemcount) LOOP 
		PERFORM refreshSC(t_sc_id, _i_id_array[i], _qty_array[i]);
	END LOOP;

    	SELECT getSCSubTotal(t_sc_id) INTO sc_subtotal;

        UPDATE shopping_cart 
           SET sc_sub_total=sc_subtotal, sc_date=now()
           WHERE sc_id=t_sc_id;
    END IF;


    SELECT * 
    INTO itemcount,
    scl_i_id1, scl_title1, scl_cost1, scl_srp1, scl_backing1, scl_qty1,
    scl_i_id2, scl_title2, scl_cost2, scl_srp2, scl_backing2, scl_qty2,
    scl_i_id3, scl_title3, scl_cost3, scl_srp3, scl_backing3, scl_qty3,
    scl_i_id4, scl_title4, scl_cost4, scl_srp4, scl_backing4, scl_qty4,
    scl_i_id5, scl_title5, scl_cost5, scl_srp5, scl_backing5, scl_qty5,
    scl_i_id6, scl_title6, scl_cost6, scl_srp6, scl_backing6, scl_qty6,
    scl_i_id7, scl_title7, scl_cost7, scl_srp7, scl_backing7, scl_qty7,
    scl_i_id8, scl_title8, scl_cost8, scl_srp8, scl_backing8, scl_qty8,
    scl_i_id9, scl_title9, scl_cost9, scl_srp9, scl_backing9, scl_qty9,
    scl_i_id10, scl_title10, scl_cost10, scl_srp10, scl_backing10, scl_qty10,
    scl_i_id11, scl_title11, scl_cost11, scl_srp11, scl_backing11, scl_qty11,
    scl_i_id12, scl_title12, scl_cost12, scl_srp12, scl_backing12, scl_qty12,
    scl_i_id13, scl_title13, scl_cost13, scl_srp13, scl_backing13, scl_qty13,
    scl_i_id14, scl_title14, scl_cost14, scl_srp14, scl_backing14, scl_qty14,
    scl_i_id15, scl_title15, scl_cost15, scl_srp15, scl_backing15, scl_qty15,
    scl_i_id16, scl_title16, scl_cost16, scl_srp16, scl_backing16, scl_qty16,
    scl_i_id17, scl_title17, scl_cost17, scl_srp17, scl_backing17, scl_qty17,
    scl_i_id18, scl_title18, scl_cost18, scl_srp18, scl_backing18, scl_qty18,
    scl_i_id19, scl_title19, scl_cost19, scl_srp19, scl_backing19, scl_qty19,
    scl_i_id20, scl_title20, scl_cost20, scl_srp20, scl_backing20, scl_qty20
    FROM getSCDetail(t_sc_id)
    AS l( N_I NUMERIC(2,0), 
    S_I_ID1 NUMERIC(10,0), S_T1 VARCHAR(60), S_C1 NUMERIC(17,2), 
    S_S1 NUMERIC(17,2), S_B1 VARCHAR(15), S_Q1 NUMERIC(3,0),
    S_I_ID2 NUMERIC(10,0), S_T2 VARCHAR(60), S_C2 NUMERIC(17,2),
    S_S2 NUMERIC(17,2), S_B2 VARCHAR(15), S_Q2 NUMERIC(3,0),
    S_I_ID3 NUMERIC(10,0), S_T3 VARCHAR(60), S_C3 NUMERIC(17,2),
    S_S3 NUMERIC(17,2), S_B3 VARCHAR(15), S_Q3 NUMERIC(3,0),
    S_I_ID4 NUMERIC(10,0), S_T4 VARCHAR(60), S_C4 NUMERIC(17,2),
    S_S4 NUMERIC(17,2), S_B4 VARCHAR(15), S_Q4 NUMERIC(3,0),
    S_I_ID5 NUMERIC(10,0), S_T5 VARCHAR(60), S_C5 NUMERIC(17,2),
    S_S5 NUMERIC(17,2), S_B5 VARCHAR(15), S_Q5 NUMERIC(3,0),
    S_I_ID6 NUMERIC(10,0), S_T6 VARCHAR(60), S_C6 NUMERIC(17,2),
    S_S6 NUMERIC(17,2), S_B6 VARCHAR(15), S_Q6 NUMERIC(3,0),
    S_I_ID7 NUMERIC(10,0), S_T7 VARCHAR(60), S_C7 NUMERIC(17,2),
    S_S7 NUMERIC(17,2), S_B7 VARCHAR(15), S_Q7 NUMERIC(3,0),
    S_I_ID8 NUMERIC(10,0), S_T8 VARCHAR(60), S_C8 NUMERIC(17,2),
    S_S8 NUMERIC(17,2), S_B8 VARCHAR(15), S_Q8 NUMERIC(3,0),
    S_I_ID9 NUMERIC(10,0), S_T9 VARCHAR(60), S_C9 NUMERIC(17,2),
    S_S9 NUMERIC(17,2), S_B9 VARCHAR(15), S_Q9 NUMERIC(3,0),
    S_I_ID10 NUMERIC(10,0), S_T10 VARCHAR(60), S_C10 NUMERIC(17,2),
    S_S10 NUMERIC(17,2), S_B10 VARCHAR(15), S_Q10 NUMERIC(3,0),
    S_I_ID11 NUMERIC(10,0), S_T11 VARCHAR(60), S_C11 NUMERIC(17,2),
    S_S11 NUMERIC(17,2), S_B11 VARCHAR(15), S_Q11 NUMERIC(3,0),
    S_I_ID12 NUMERIC(10,0), S_T12 VARCHAR(60), S_C12 NUMERIC(17,2),
    S_S12 NUMERIC(17,2), S_B12 VARCHAR(15), S_Q12 NUMERIC(3,0),
    S_I_ID13 NUMERIC(10,0), S_T13 VARCHAR(60), S_C13 NUMERIC(17,2),
    S_S13 NUMERIC(17,2), S_B13 VARCHAR(15), S_Q13 NUMERIC(3,0),
    S_I_ID14 NUMERIC(10,0), S_T14 VARCHAR(60), S_C14 NUMERIC(17,2),
    S_S14 NUMERIC(17,2), S_B14 VARCHAR(15), S_Q14 NUMERIC(3,0),
    S_I_ID15 NUMERIC(10,0), S_T15 VARCHAR(60), S_C15 NUMERIC(17,2),
    S_S15 NUMERIC(17,2), S_B15 VARCHAR(15), S_Q15 NUMERIC(3,0),
    S_I_ID16 NUMERIC(10,0), S_T16 VARCHAR(60), S_C16 NUMERIC(17,2),
    S_S16 NUMERIC(17,2), S_B16 VARCHAR(15), S_Q16 NUMERIC(3,0),
    S_I_ID17 NUMERIC(10,0), S_T17 VARCHAR(60), S_C17 NUMERIC(17,2),
    S_S17 NUMERIC(17,2), S_B17 VARCHAR(15), S_Q17 NUMERIC(3,0),
    S_I_ID18 NUMERIC(10,0), S_T18 VARCHAR(60), S_C18 NUMERIC(17,2),
    S_S18 NUMERIC(17,2), S_B18 VARCHAR(15), S_Q18 NUMERIC(3,0),
    S_I_ID19 NUMERIC(10,0), S_T19 VARCHAR(60), S_C19 NUMERIC(17,2),
    S_S19 NUMERIC(17,2), S_B19 VARCHAR(15), S_Q19 NUMERIC(3,0),
    S_I_ID20 NUMERIC(10,0), S_T20 VARCHAR(60), S_C20 NUMERIC(17,2),
    S_S20 NUMERIC(17,2), S_B20 VARCHAR(15), S_Q20 NUMERIC(3,0));

--    RAISE NOTICE ''itemcount=%'', itemcount;

    SELECT * 
    INTO pp_i_id1, pp_i_t1, 
         pp_i_id2, pp_i_t2, 
         pp_i_id3, pp_i_t3, 
         pp_i_id4, pp_i_t4, 
         pp_i_id5, pp_i_t5
    FROM getPromoImages(_pp_i_id)
    AS l(P_I_ID1 NUMERIC(10), 
         P_I_T1 NUMERIC(10),
         P_I_ID2 NUMERIC(10), 
         P_I_T2 NUMERIC(10),
         P_I_ID3 NUMERIC(10), 
         P_I_T3 NUMERIC(10),
         P_I_ID4 NUMERIC(10), 
         P_I_T4 NUMERIC(10),
         P_I_ID5 NUMERIC(10), 
         P_I_T5 NUMERIC(10));

    SELECT
    t_sc_id::NUMERIC(10),
    itemcount::NUMERIC(2),
    pp_i_id1::NUMERIC(10),
    pp_i_t1::NUMERIC(10),
    pp_i_id2::NUMERIC(10),
    pp_i_t2::NUMERIC(10),
    pp_i_id3::NUMERIC(10),
    pp_i_t3::NUMERIC(10),
    pp_i_id4::NUMERIC(10),
    pp_i_t4::NUMERIC(10),
    pp_i_id5::NUMERIC(10),
    pp_i_t5::NUMERIC(10),
    scl_i_id1::NUMERIC(10),
    scl_title1::VARCHAR(60),
    scl_cost1::NUMERIC(17,2),
    scl_srp1::NUMERIC(17,2),
    scl_backing1::VARCHAR(15),
    scl_qty1::NUMERIC(3),
    scl_i_id2::NUMERIC(10),
    scl_title2::VARCHAR(60),
    scl_cost2::NUMERIC(17,2),
    scl_srp2::NUMERIC(17,2),
    scl_backing2::VARCHAR(15),
    scl_qty2::NUMERIC(3),
    scl_i_id3::NUMERIC(10),
    scl_title3::VARCHAR(60),
    scl_cost3::NUMERIC(17,2),
    scl_srp3::NUMERIC(17,2),
    scl_backing3::VARCHAR(15),
    scl_qty3::NUMERIC(3),
    scl_i_id4::NUMERIC(10),
    scl_title4::VARCHAR(60),
    scl_cost4::NUMERIC(17,2),
    scl_srp4::NUMERIC(17,2),
    scl_backing4::VARCHAR(15),
    scl_qty4::NUMERIC(3),
    scl_i_id5::NUMERIC(10),
    scl_title5::VARCHAR(60),
    scl_cost5::NUMERIC(17,2),
    scl_srp5::NUMERIC(17,2),
    scl_backing5::VARCHAR(15),
    scl_qty5::NUMERIC(3),
    scl_i_id6::NUMERIC(10),
    scl_title6::VARCHAR(60),
    scl_cost6::NUMERIC(17,2),
    scl_srp6::NUMERIC(17,2),
    scl_backing6::VARCHAR(15),
    scl_qty6::NUMERIC(3),
    scl_i_id7::NUMERIC(10),
    scl_title7::VARCHAR(60),
    scl_cost7::NUMERIC(17,2),
    scl_srp7::NUMERIC(17,2),
    scl_backing7::VARCHAR(15),
    scl_qty7::NUMERIC(3),
    scl_i_id8::NUMERIC(10),
    scl_title8::VARCHAR(60),
    scl_cost8::NUMERIC(17,2),
    scl_srp8::NUMERIC(17,2),
    scl_backing8::VARCHAR(15),
    scl_qty8::NUMERIC(3),
    scl_i_id9::NUMERIC(10),
    scl_title9::VARCHAR(60),
    scl_cost9::NUMERIC(17,2),
    scl_srp9::NUMERIC(17,2),
    scl_backing9::VARCHAR(15),
    scl_qty9::NUMERIC(3),
    scl_i_id10::NUMERIC(10),
    scl_title10::VARCHAR(60),
    scl_cost10::NUMERIC(17,2),
    scl_srp10::NUMERIC(17,2),
    scl_backing10::VARCHAR(15),
    scl_qty10::NUMERIC(3),
    scl_i_id11::NUMERIC(10),
    scl_title11::VARCHAR(60),
    scl_cost11::NUMERIC(17,2),
    scl_srp11::NUMERIC(17,2),
    scl_backing11::VARCHAR(15),
    scl_qty11::NUMERIC(3),
    scl_i_id12::NUMERIC(10),
    scl_title12::VARCHAR(60),
    scl_cost12::NUMERIC(17,2),
    scl_srp12::NUMERIC(17,2),
    scl_backing12::VARCHAR(15),
    scl_qty12::NUMERIC(3),
    scl_i_id13::NUMERIC(10),
    scl_title13::VARCHAR(60),
    scl_cost13::NUMERIC(17,2),
    scl_srp13::NUMERIC(17,2),
    scl_backing13::VARCHAR(15),
    scl_qty13::NUMERIC(3),
    scl_i_id14::NUMERIC(10),
    scl_title14::VARCHAR(60),
    scl_cost14::NUMERIC(17,2),
    scl_srp14::NUMERIC(17,2),
    scl_backing14::VARCHAR(15),
    scl_qty14::NUMERIC(3),
    scl_i_id15::NUMERIC(10),
    scl_title15::VARCHAR(60),
    scl_cost15::NUMERIC(17,2),
    scl_srp15::NUMERIC(17,2),
    scl_backing15::VARCHAR(15),
    scl_qty15::NUMERIC(3),
    scl_i_id16::NUMERIC(10),
    scl_title16::VARCHAR(60),
    scl_cost16::NUMERIC(17,2),
    scl_srp16::NUMERIC(17,2),
    scl_backing16::VARCHAR(15),
    scl_qty16::NUMERIC(3),
    scl_i_id17::NUMERIC(10),
    scl_title17::VARCHAR(60),
    scl_cost17::NUMERIC(17,2),
    scl_srp17::NUMERIC(17,2),
    scl_backing17::VARCHAR(15),
    scl_qty17::NUMERIC(3),
    scl_i_id18::NUMERIC(10),
    scl_title18::VARCHAR(60),
    scl_cost18::NUMERIC(17,2),
    scl_srp18::NUMERIC(17,2),
    scl_backing18::VARCHAR(15),
    scl_qty18::NUMERIC(3),
    scl_i_id19::NUMERIC(10),
    scl_title19::VARCHAR(60),
    scl_cost19::NUMERIC(17,2),
    scl_srp19::NUMERIC(17,2),
    scl_backing19::VARCHAR(15),
    scl_qty19::NUMERIC(3),
    scl_i_id20::NUMERIC(10),
    scl_title20::VARCHAR(60),
    scl_cost20::NUMERIC(17,2),
    scl_srp20::NUMERIC(17,2),
    scl_backing20::VARCHAR(15),
    scl_qty20::NUMERIC(3)
    INTO rec;

    RETURN rec;

  END;
' LANGUAGE 'plpgsql';
commit;
---- Usage:
---- 
---- SELECT * FROM (
----    C_ID NUMERIC(10),
----    sc_id NUMERIC(10),
----    itemcount NUMERIC(2),
----    add_flag NUMERIC(1),
----    i_id NUMERIC(10),
----    pp_i_id NUMERIC(10),
----    tbl argumentTableFORshopping_cartORrefrSC
---- )
---- AS l(
----    sc_id NUMERIC(10),
----    itemcount NUMERIC(2),
----    pp_i_id1 NUMERIC(10),
----    pp_i_t1 NUMERIC(10),
----    pp_i_id2 NUMERIC(10),
----    pp_i_t2 NUMERIC(10),
----    pp_i_id3 NUMERIC(10),
----    pp_i_t3 NUMERIC(10),
----    pp_i_id4 NUMERIC(10),
----    pp_i_t4 NUMERIC(10),
----    pp_i_id5 NUMERIC(10),
----    pp_i_t5 NUMERIC(10),
----    scl_i_id1 NUMERIC(10),
----    scl_title1 VARCHAR(60),
----    scl_cost1 NUMERIC(17,2),
----    scl_srp1 NUMERIC(17,2),
----    scl_backing1 VARCHAR(15),
----    scl_qty1 NUMERIC(3),
----    scl_i_id2 NUMERIC(10),
----    scl_title2 VARCHAR(60),
----    scl_cost2 NUMERIC(17,2),
----    scl_srp2 NUMERIC(17,2),
----    scl_backing2 VARCHAR(15),
----    scl_qty2 NUMERIC(3),
----    scl_i_id3 NUMERIC(10),
----    scl_title3 VARCHAR(60),
----    scl_cost3 NUMERIC(17,2),
----    scl_srp3 NUMERIC(17,2),
----    scl_backing3 VARCHAR(15),
----    scl_qty3 NUMERIC(3),
----    scl_i_id4 NUMERIC(10),
----    scl_title4 VARCHAR(60),
----    scl_cost4 NUMERIC(17,2),
----    scl_srp4 NUMERIC(17,2),
----    scl_backing4 VARCHAR(15),
----    scl_qty4 NUMERIC(3),
----    scl_i_id5 NUMERIC(10),
----    scl_title5 VARCHAR(60),
----    scl_cost5 NUMERIC(17,2),
----    scl_srp5 NUMERIC(17,2),
----    scl_backing5 VARCHAR(15),
----    scl_qty5 NUMERIC(3),
----    scl_i_id6 NUMERIC(10),
----    scl_title6 VARCHAR(60),
----    scl_cost6 NUMERIC(17,2),
----    scl_srp6 NUMERIC(17,2),
----    scl_backing6 VARCHAR(15),
----    scl_qty6 NUMERIC(3),
----    scl_i_id7 NUMERIC(10),
----    scl_title7 VARCHAR(60),
----    scl_cost7 NUMERIC(17,2),
----    scl_srp7 NUMERIC(17,2),
----    scl_backing7 VARCHAR(15),
----    scl_qty7 NUMERIC(3),
----    scl_i_id8 NUMERIC(10),
----    scl_title8 VARCHAR(60),
----    scl_cost8 NUMERIC(17,2),
----    scl_srp8 NUMERIC(17,2),
----    scl_backing8 VARCHAR(15),
----    scl_qty8 NUMERIC(3),
----    scl_i_id9 NUMERIC(10),
----    scl_title9 VARCHAR(60),
----    scl_cost9 NUMERIC(17,2),
----    scl_srp9 NUMERIC(17,2),
----    scl_backing9 VARCHAR(15),
----    scl_qty9 NUMERIC(3),
----    scl_i_id10 NUMERIC(10),
----    scl_title10 VARCHAR(60),
----    scl_cost10 NUMERIC(17,2),
----    scl_srp10 NUMERIC(17,2),
----    scl_backing10 VARCHAR(15),
----    scl_qty10 NUMERIC(3),
----    scl_i_id11 NUMERIC(10),
----    scl_title11 VARCHAR(60),
----    scl_cost11 NUMERIC(17,2),
----    scl_srp11 NUMERIC(17,2),
----    scl_backing11 VARCHAR(15),
----    scl_qty11 NUMERIC(3),
----    scl_i_id12 NUMERIC(10),
----    scl_title12 VARCHAR(60),
----    scl_cost12 NUMERIC(17,2),
----    scl_srp12 NUMERIC(17,2),
----    scl_backing12 VARCHAR(15),
----    scl_qty12 NUMERIC(3),
----    scl_i_id13 NUMERIC(10),
----    scl_title13 VARCHAR(60),
----    scl_cost13 NUMERIC(17,2),
----    scl_srp13 NUMERIC(17,2),
----    scl_backing13 VARCHAR(15),
----    scl_qty13 NUMERIC(3),
----    scl_i_id14 NUMERIC(10),
----    scl_title14 VARCHAR(60),
----    scl_cost14 NUMERIC(17,2),
----    scl_srp14 NUMERIC(17,2),
----    scl_backing14 VARCHAR(15),
----    scl_qty14 NUMERIC(3),
----    scl_i_id15 NUMERIC(10),
----    scl_title15 VARCHAR(60),
----    scl_cost15 NUMERIC(17,2),
----    scl_srp15 NUMERIC(17,2),
----    scl_backing15 VARCHAR(15),
----    scl_qty15 NUMERIC(3),
----    scl_i_id16 NUMERIC(10),
----    scl_title16 VARCHAR(60),
----    scl_cost16 NUMERIC(17,2),
----    scl_srp16 NUMERIC(17,2),
----    scl_backing16 VARCHAR(15),
----    scl_qty16 NUMERIC(3),
----    scl_i_id17 NUMERIC(10),
----    scl_title17 VARCHAR(60),
----    scl_cost17 NUMERIC(17,2),
----    scl_srp17 NUMERIC(17,2),
----    scl_backing17 VARCHAR(15),
----    scl_qty17 NUMERIC(3),
----    scl_i_id18 NUMERIC(10),
----    scl_title18 VARCHAR(60),
----    scl_cost18 NUMERIC(17,2),
----    scl_srp18 NUMERIC(17,2),
----    scl_backing18 VARCHAR(15),
----    scl_qty18 NUMERIC(3),
----    scl_i_id19 NUMERIC(10),
----    scl_title19 VARCHAR(60),
----    scl_cost19 NUMERIC(17,2),
----    scl_srp19 NUMERIC(17,2),
----    scl_backing19 VARCHAR(15),
----    scl_qty19 NUMERIC(3),
----    scl_i_id20 NUMERIC(10),
----    scl_title20 VARCHAR(60),
----    scl_cost20 NUMERIC(17,2),
----    scl_srp20 NUMERIC(17,2),
----    scl_backing20 VARCHAR(15),
----    scl_qty20 NUMERIC(3),
----);
