--
--
-- This file is released under the terms of the Artistic License.	Please see
-- the file LICENSE, included in this package, for details.
--
-- Copyright (C) 2002 Open Source Development Lab, Inc.
-- History: 
-- July-2003: Created by Satoshi Nagayasu
-- Aug-14-2003:  Reviewed and Tested by Jenny Zhang
--
CREATE OR REPLACE FUNCTION order_display (
	VARCHAR(20),
	VARCHAR(20)
) RETURNS SETOF RECORD AS '
	DECLARE
		v_c_uname ALIAS FOR $1;
		v_c_passwd ALIAS FOR $2;
		v_c_fname VARCHAR(15);
		v_c_lname VARCHAR(15);
		v_c_phone VARCHAR(16);
		v_c_email VARCHAR(50);
		v_o_id NUMERIC(10);
		v_o_date CHAR(26);
		v_o_sub_total NUMERIC(17, 2);
		v_o_tax NUMERIC(17, 2);
		v_o_total NUMERIC(17, 2);
		v_o_ship_type VARCHAR(10);
		v_o_ship_date CHAR(26);
		v_o_status VARCHAR(15);
		v_cx_type VARCHAR(10);
		v_cx_auth_id VARCHAR(15);
		v_bill_addr_street1 VARCHAR(40);
		v_bill_addr_street2 VARCHAR(40);
		v_bill_addr_city VARCHAR(30);
		v_bill_addr_state VARCHAR(20);
		v_bill_addr_zip VARCHAR(10);
		v_bill_co_name VARCHAR(50);
		v_ship_addr_street1 VARCHAR(40);
		v_ship_addr_street2 VARCHAR(40);
		v_ship_addr_city VARCHAR(30);
		v_ship_addr_state VARCHAR(20);
		v_ship_addr_zip VARCHAR(10);
		v_ship_co_name VARCHAR(50);
		v_num_item NUMERIC(3,0);
		v_i_id1 NUMERIC(10);
		v_i_title1 VARCHAR(60);
		v_i_publisher1 VARCHAR(60);
		v_i_cost1 NUMERIC(17, 2);
		v_ol_qty1 NUMERIC(3);
		v_ol_discount1 NUMERIC(17, 2);
		v_ol_comments1 VARCHAR(100);
		v_i_id2 NUMERIC(10);
		v_i_title2 VARCHAR(60);
		v_i_publisher2 VARCHAR(60);
		v_i_cost2 NUMERIC(17, 2);
		v_ol_qty2 NUMERIC(3);
		v_ol_discount2 NUMERIC(17, 2);
		v_ol_comments2 VARCHAR(100);
		v_i_id3 NUMERIC(10);
		v_i_title3 VARCHAR(60);
		v_i_publisher3 VARCHAR(60);
		v_i_cost3 NUMERIC(17, 2);
		v_ol_qty3 NUMERIC(3);
		v_ol_discount3 NUMERIC(17, 2);
		v_ol_comments3 VARCHAR(100);
		v_i_id4 NUMERIC(10);
		v_i_title4 VARCHAR(60);
		v_i_publisher4 VARCHAR(60);
		v_i_cost4 NUMERIC(17, 2);
		v_ol_qty4 NUMERIC(3);
		v_ol_discount4 NUMERIC(17, 2);
		v_ol_comments4 VARCHAR(100);
		v_i_id5 NUMERIC(10);
		v_i_title5 VARCHAR(60);
		v_i_publisher5 VARCHAR(60);
		v_i_cost5 NUMERIC(17, 2);
		v_ol_qty5 NUMERIC(3);
		v_ol_discount5 NUMERIC(17, 2);
		v_ol_comments5 VARCHAR(100);
		v_i_id6 NUMERIC(10);
		v_i_title6 VARCHAR(60);
		v_i_publisher6 VARCHAR(60);
		v_i_cost6 NUMERIC(17, 2);
		v_ol_qty6 NUMERIC(3);
		v_ol_discount6 NUMERIC(17, 2);
		v_ol_comments6 VARCHAR(100);
		v_i_id7 NUMERIC(10);
		v_i_title7 VARCHAR(60);
		v_i_publisher7 VARCHAR(60);
		v_i_cost7 NUMERIC(17, 2);
		v_ol_qty7 NUMERIC(3);
		v_ol_discount7 NUMERIC(17, 2);
		v_ol_comments7 VARCHAR(100);
		v_i_id8 NUMERIC(10);
		v_i_title8 VARCHAR(60);
		v_i_publisher8 VARCHAR(60);
		v_i_cost8 NUMERIC(17, 2);
		v_ol_qty8 NUMERIC(3);
		v_ol_discount8 NUMERIC(17, 2);
		v_ol_comments8 VARCHAR(100);
		v_i_id9 NUMERIC(10);
		v_i_title9 VARCHAR(60);
		v_i_publisher9 VARCHAR(60);
		v_i_cost9 NUMERIC(17, 2);
		v_ol_qty9 NUMERIC(3);
		v_ol_discount9 NUMERIC(17, 2);
		v_ol_comments9 VARCHAR(100);
		v_i_id10 NUMERIC(10);
		v_i_title10 VARCHAR(60);
		v_i_publisher10 VARCHAR(60);
		v_i_cost10 NUMERIC(17, 2);
		v_ol_qty10 NUMERIC(3);
		v_ol_discount10 NUMERIC(17, 2);
		v_ol_comments10 VARCHAR(100);
		v_i_id11 NUMERIC(10);
		v_i_title11 VARCHAR(60);
		v_i_publisher11 VARCHAR(60);
		v_i_cost11 NUMERIC(17, 2);
		v_ol_qty11 NUMERIC(3);
		v_ol_discount11 NUMERIC(17, 2);
		v_ol_comments11 VARCHAR(100);
		v_i_id12 NUMERIC(10);
		v_i_title12 VARCHAR(60);
		v_i_publisher12 VARCHAR(60);
		v_i_cost12 NUMERIC(17, 2);
		v_ol_qty12 NUMERIC(3);
		v_ol_discount12 NUMERIC(17, 2);
		v_ol_comments12 VARCHAR(100);
		v_i_id13 NUMERIC(10);
		v_i_title13 VARCHAR(60);
		v_i_publisher13 VARCHAR(60);
		v_i_cost13 NUMERIC(17, 2);
		v_ol_qty13 NUMERIC(3);
		v_ol_discount13 NUMERIC(17, 2);
		v_ol_comments13 VARCHAR(100);
		v_i_id14 NUMERIC(10);
		v_i_title14 VARCHAR(60);
		v_i_publisher14 VARCHAR(60);
		v_i_cost14 NUMERIC(17, 2);
		v_ol_qty14 NUMERIC(3);
		v_ol_discount14 NUMERIC(17, 2);
		v_ol_comments14 VARCHAR(100);
		v_i_id15 NUMERIC(10);
		v_i_title15 VARCHAR(60);
		v_i_publisher15 VARCHAR(60);
		v_i_cost15 NUMERIC(17, 2);
		v_ol_qty15 NUMERIC(3);
		v_ol_discount15 NUMERIC(17, 2);
		v_ol_comments15 VARCHAR(100);
		v_i_id16 NUMERIC(10);
		v_i_title16 VARCHAR(60);
		v_i_publisher16 VARCHAR(60);
		v_i_cost16 NUMERIC(17, 2);
		v_ol_qty16 NUMERIC(3);
		v_ol_discount16 NUMERIC(17, 2);
		v_ol_comments16 VARCHAR(100);
		v_i_id17 NUMERIC(10);
		v_i_title17 VARCHAR(60);
		v_i_publisher17 VARCHAR(60);
		v_i_cost17 NUMERIC(17, 2);
		v_ol_qty17 NUMERIC(3);
		v_ol_discount17 NUMERIC(17, 2);
		v_ol_comments17 VARCHAR(100);
		v_i_id18 NUMERIC(10);
		v_i_title18 VARCHAR(60);
		v_i_publisher18 VARCHAR(60);
		v_i_cost18 NUMERIC(17, 2);
		v_ol_qty18 NUMERIC(3);
		v_ol_discount18 NUMERIC(17, 2);
		v_ol_comments18 VARCHAR(100);
		v_i_id19 NUMERIC(10);
		v_i_title19 VARCHAR(60);
		v_i_publisher19 VARCHAR(60);
		v_i_cost19 NUMERIC(17, 2);
		v_ol_qty19 NUMERIC(3);
		v_ol_discount19 NUMERIC(17, 2);
		v_ol_comments19 VARCHAR(100);
		v_i_id20 NUMERIC(10);
		v_i_title20 VARCHAR(60);
		v_i_publisher20 VARCHAR(60);
		v_i_cost20 NUMERIC(17, 2);
		v_ol_qty20 NUMERIC(3);
		v_ol_discount20 NUMERIC(17, 2);
		v_ol_comments20 VARCHAR(100);
		-- VARs
		v_o_bill_addr_id NUMERIC(10);
		v_o_ship_addr_id NUMERIC(10);
		refcur REFCURSOR;
		ret RECORD;
	BEGIN

	SELECT c_fname, c_lname, c_phone, c_email,
		o_id, to_char(o_date,''YYYY-MM-DD''), o_sub_total, o_tax, 
		o_total, o_ship_type, to_char(o_ship_date,''YYYY-MM-DD''),
		o_status, o_bill_addr_id, o_ship_addr_id, cx_type, cx_auth_id
	INTO v_c_fname, v_c_lname, v_c_phone, v_c_email,
		v_o_id, v_o_date, v_o_sub_total, v_o_tax,
		v_o_total, v_o_ship_type, v_o_ship_date, v_o_status,
		v_o_bill_addr_id, v_o_ship_addr_id, v_cx_type, v_cx_auth_id 
	FROM customer, orders, cc_xacts
	WHERE c_uname = v_c_uname AND c_passwd = v_c_passwd
		AND o_c_id=c_id AND cx_o_id = o_id ORDER BY o_date DESC;
	
-- If there are any result set, the first set is used
	
	IF FOUND THEN 
		SELECT addr_street1, addr_street2, addr_city, addr_state, 
			addr_zip, co_name
		INTO v_bill_addr_street1, v_bill_addr_street2, 
			v_bill_addr_city, v_bill_addr_state, v_bill_addr_zip, 
			v_bill_co_name 
		FROM address, country
		WHERE addr_id = v_o_bill_addr_id AND addr_co_id = co_id;

		SELECT addr_street1, addr_street2, addr_city, addr_state, 
			addr_zip, co_name
		INTO v_ship_addr_street1, v_ship_addr_street2, 
			v_ship_addr_city, v_ship_addr_state, v_ship_addr_zip, 
			v_ship_co_name
		FROM address, country
		WHERE addr_id = v_o_ship_addr_id AND addr_co_id = co_id;

		v_num_item := 0;	
		OPEN refcur FOR SELECT i_id, i_title, i_publisher, i_cost, 
			ol_qty, ol_discount, ol_comments 
		FROM item, order_line 
		WHERE ol_o_id = v_o_id AND ol_i_id = i_id;

--
-- The first fetch
--
		FETCH refcur INTO v_i_id1, v_i_title1, v_i_publisher1, v_i_cost1, v_ol_qty1, v_ol_discount1, v_ol_comments1;

		IF FOUND THEN
			v_num_item := v_num_item + 1;
			FETCH refcur INTO v_i_id2, v_i_title2, v_i_publisher2, v_i_cost2, v_ol_qty2, v_ol_discount2, v_ol_comments2;
		END IF;

		IF FOUND THEN
			v_num_item := v_num_item + 1;
			FETCH refcur INTO v_i_id3, v_i_title3, v_i_publisher3, v_i_cost3, v_ol_qty3, v_ol_discount3, v_ol_comments3;
		END IF;

		IF FOUND THEN
			v_num_item := v_num_item + 1;
			FETCH refcur INTO v_i_id4, v_i_title4, v_i_publisher4, v_i_cost4, v_ol_qty4, v_ol_discount4, v_ol_comments4;
		END IF;

		IF FOUND THEN
			v_num_item := v_num_item + 1;
			FETCH refcur INTO v_i_id5, v_i_title5, v_i_publisher5, v_i_cost5, v_ol_qty5, v_ol_discount5, v_ol_comments5;
		END IF;

		IF FOUND THEN
			v_num_item := v_num_item + 1;
			FETCH refcur INTO v_i_id6, v_i_title6, v_i_publisher6, v_i_cost6, v_ol_qty6, v_ol_discount6, v_ol_comments6;
		END IF;

		IF FOUND THEN
			v_num_item := v_num_item + 1;
			FETCH refcur INTO v_i_id7, v_i_title7, v_i_publisher7, v_i_cost7, v_ol_qty7, v_ol_discount7, v_ol_comments7;
		END IF;

		IF FOUND THEN
			v_num_item := v_num_item + 1;
			FETCH refcur INTO v_i_id8, v_i_title8, v_i_publisher8, v_i_cost8, v_ol_qty8, v_ol_discount8, v_ol_comments8;
		END IF;

		IF FOUND THEN
			v_num_item := v_num_item + 1;
			FETCH refcur INTO v_i_id9, v_i_title9, v_i_publisher9, v_i_cost9, v_ol_qty9, v_ol_discount9, v_ol_comments9;
		END IF;

		IF FOUND THEN
			v_num_item := v_num_item + 1;
			FETCH refcur INTO v_i_id10, v_i_title10, v_i_publisher10, v_i_cost10, v_ol_qty10, v_ol_discount10, v_ol_comments10;
		END IF;

		IF FOUND THEN
			v_num_item := v_num_item + 1;
			FETCH refcur INTO v_i_id11, v_i_title11, v_i_publisher11, v_i_cost11, v_ol_qty11, v_ol_discount11, v_ol_comments11;
		END IF;

		IF FOUND THEN
			v_num_item := v_num_item + 1;
			FETCH refcur INTO v_i_id12, v_i_title12, v_i_publisher12, v_i_cost12, v_ol_qty12, v_ol_discount12, v_ol_comments12;
		END IF;

		IF FOUND THEN			
			v_num_item := v_num_item + 1;
			FETCH refcur INTO v_i_id13, v_i_title13, v_i_publisher13, v_i_cost13, v_ol_qty13, v_ol_discount13, v_ol_comments13;
		END IF;

		IF FOUND THEN			
			v_num_item := v_num_item + 1;
			FETCH refcur INTO v_i_id14, v_i_title14, v_i_publisher14, v_i_cost14, v_ol_qty14, v_ol_discount14, v_ol_comments14;
		END IF;

		IF FOUND THEN						
			v_num_item := v_num_item + 1;
			FETCH refcur INTO v_i_id15, v_i_title15, v_i_publisher15, v_i_cost15, v_ol_qty15, v_ol_discount15, v_ol_comments15;
		END IF;

		IF FOUND THEN			
			v_num_item := v_num_item + 1;
			FETCH refcur INTO v_i_id16, v_i_title16, v_i_publisher16, v_i_cost16, v_ol_qty16, v_ol_discount16, v_ol_comments16;
		END IF;

		IF FOUND THEN			
			v_num_item := v_num_item + 1;
			FETCH refcur INTO v_i_id17, v_i_title17, v_i_publisher17, v_i_cost17, v_ol_qty17, v_ol_discount17, v_ol_comments17;
		END IF;

		IF FOUND THEN						 
			v_num_item := v_num_item + 1;
			FETCH refcur INTO v_i_id18, v_i_title18, v_i_publisher18, v_i_cost18, v_ol_qty18, v_ol_discount18, v_ol_comments18;
		END IF;

		IF FOUND THEN						
			v_num_item := v_num_item + 1;
			FETCH refcur INTO v_i_id19, v_i_title19, v_i_publisher19, v_i_cost19, v_ol_qty19, v_ol_discount19, v_ol_comments19;
		END IF;

		IF FOUND THEN						
			v_num_item := v_num_item + 1;
			FETCH refcur INTO v_i_id20, v_i_title20, v_i_publisher20, v_i_cost20, v_ol_qty20, v_ol_discount20, v_ol_comments20;
		END IF;

		CLOSE refcur;
	END IF;

--
-- Create Result Data
--
	SELECT  
		v_c_fname::VARCHAR(15),
		v_c_lname::VARCHAR(15),
		v_c_phone::VARCHAR(16),
		v_c_email::VARCHAR(50),
		v_o_id::NUMERIC(10),
		v_o_date::CHAR(26),
		v_o_sub_total::NUMERIC(17, 2),
		v_o_tax::NUMERIC(17, 2),
		v_o_total::NUMERIC(17, 2),
		v_o_ship_type::VARCHAR(10),
		v_o_ship_date::CHAR(26),
		v_o_status::VARCHAR(15),
		v_cx_type::VARCHAR(10),
		v_cx_auth_id::VARCHAR(15),
		v_bill_addr_street1::VARCHAR(40),
		v_bill_addr_street2::VARCHAR(40),
		v_bill_addr_city::VARCHAR(30),
		v_bill_addr_state::VARCHAR(20),
		v_bill_addr_zip::VARCHAR(10),
		v_bill_co_name::VARCHAR(50),
		v_ship_addr_street1::VARCHAR(40),
		v_ship_addr_street2::VARCHAR(40),
		v_ship_addr_city::VARCHAR(30),
		v_ship_addr_state::VARCHAR(20),
		v_ship_addr_zip::VARCHAR(10),
		v_ship_co_name::VARCHAR(50),
		v_num_item::NUMERIC(3,0),
		v_i_id1::NUMERIC(10),
		v_i_title1::VARCHAR(60),
		v_i_publisher1::VARCHAR(60),
		v_i_cost1::NUMERIC(17, 2),
		v_ol_qty1::NUMERIC(3),
		v_ol_discount1::NUMERIC(17, 2),
		v_ol_comments1::VARCHAR(100),
		v_i_id2::NUMERIC(10),
		v_i_title2::VARCHAR(60),
		v_i_publisher2::VARCHAR(60),
		v_i_cost2::NUMERIC(17, 2),
		v_ol_qty2::NUMERIC(3),
		v_ol_discount2::NUMERIC(17, 2),
		v_ol_comments2::VARCHAR(100),
		v_i_id3::NUMERIC(10),
		v_i_title3::VARCHAR(60),
		v_i_publisher3::VARCHAR(60),
		v_i_cost3::NUMERIC(17, 2),
		v_ol_qty3::NUMERIC(3),
		v_ol_discount3::NUMERIC(17, 2),
		v_ol_comments3::VARCHAR(100),
		v_i_id4::NUMERIC(10),
		v_i_title4::VARCHAR(60),
		v_i_publisher4::VARCHAR(60),
		v_i_cost4::NUMERIC(17, 2),
		v_ol_qty4::NUMERIC(3),
		v_ol_discount4::NUMERIC(17, 2),
		v_ol_comments4::VARCHAR(100),
		v_i_id5::NUMERIC(10),
		v_i_title5::VARCHAR(60),
		v_i_publisher5::VARCHAR(60),
		v_i_cost5::NUMERIC(17, 2),
		v_ol_qty5::NUMERIC(3),
		v_ol_discount5::NUMERIC(17, 2),
		v_ol_comments5::VARCHAR(100),
		v_i_id6::NUMERIC(10),
		v_i_title6::VARCHAR(60),
		v_i_publisher6::VARCHAR(60),
		v_i_cost6::NUMERIC(17, 2),
		v_ol_qty6::NUMERIC(3),
		v_ol_discount6::NUMERIC(17, 2),
		v_ol_comments6::VARCHAR(100),
		v_i_id7::NUMERIC(10),
		v_i_title7::VARCHAR(60),
		v_i_publisher7::VARCHAR(60),
		v_i_cost7::NUMERIC(17, 2),
		v_ol_qty7::NUMERIC(3),
		v_ol_discount7::NUMERIC(17, 2),
		v_ol_comments7::VARCHAR(100),
		v_i_id8::NUMERIC(10),
		v_i_title8::VARCHAR(60),
		v_i_publisher8::VARCHAR(60),
		v_i_cost8::NUMERIC(17, 2),
		v_ol_qty8::NUMERIC(3),
		v_ol_discount8::NUMERIC(17, 2),
		v_ol_comments8::VARCHAR(100),
		v_i_id9::NUMERIC(10),
		v_i_title9::VARCHAR(60),
		v_i_publisher9::VARCHAR(60),
		v_i_cost9::NUMERIC(17, 2),
		v_ol_qty9::NUMERIC(3),
		v_ol_discount9::NUMERIC(17, 2),
		v_ol_comments9::VARCHAR(100),
		v_i_id10::NUMERIC(10),
		v_i_title10::VARCHAR(60),
		v_i_publisher10::VARCHAR(60),
		v_i_cost10::NUMERIC(17, 2),
		v_ol_qty10::NUMERIC(3),
		v_ol_discount10::NUMERIC(17, 2),
		v_ol_comments10::VARCHAR(100),
		v_i_id11::NUMERIC(10),
		v_i_title11::VARCHAR(60),
		v_i_publisher11::VARCHAR(60),
		v_i_cost11::NUMERIC(17, 2),
		v_ol_qty11::NUMERIC(3),
		v_ol_discount11::NUMERIC(17, 2),
		v_ol_comments11::VARCHAR(100),
		v_i_id12::NUMERIC(10),
		v_i_title12::VARCHAR(60),
		v_i_publisher12::VARCHAR(60),
		v_i_cost12::NUMERIC(17, 2),
		v_ol_qty12::NUMERIC(3),
		v_ol_discount12::NUMERIC(17, 2),
		v_ol_comments12::VARCHAR(100),
		v_i_id13::NUMERIC(10),
		v_i_title13::VARCHAR(60),
		v_i_publisher13::VARCHAR(60),
		v_i_cost13::NUMERIC(17, 2),
		v_ol_qty13::NUMERIC(3),
		v_ol_discount13::NUMERIC(17, 2),
		v_ol_comments13::VARCHAR(100),
		v_i_id14::NUMERIC(10),
		v_i_title14::VARCHAR(60),
		v_i_publisher14::VARCHAR(60),
		v_i_cost14::NUMERIC(17, 2),
		v_ol_qty14::NUMERIC(3),
		v_ol_discount14::NUMERIC(17, 2),
		v_ol_comments14::VARCHAR(100),
		v_i_id15::NUMERIC(10),
		v_i_title15::VARCHAR(60),
		v_i_publisher15::VARCHAR(60),
		v_i_cost15::NUMERIC(17, 2),
		v_ol_qty15::NUMERIC(3),
		v_ol_discount15::NUMERIC(17, 2),
		v_ol_comments15::VARCHAR(100),
		v_i_id16::NUMERIC(10),
		v_i_title16::VARCHAR(60),
		v_i_publisher16::VARCHAR(60),
		v_i_cost16::NUMERIC(17, 2),
		v_ol_qty16::NUMERIC(3),
		v_ol_discount16::NUMERIC(17, 2),
		v_ol_comments16::VARCHAR(100),
		v_i_id17::NUMERIC(10),
		v_i_title17::VARCHAR(60),
		v_i_publisher17::VARCHAR(60),
		v_i_cost17::NUMERIC(17, 2),
		v_ol_qty17::NUMERIC(3),
		v_ol_discount17::NUMERIC(17, 2),
		v_ol_comments17::VARCHAR(100),
		v_i_id18::NUMERIC(10),
		v_i_title18::VARCHAR(60),
		v_i_publisher18::VARCHAR(60),
		v_i_cost18::NUMERIC(17, 2),
		v_ol_qty18::NUMERIC(3),
		v_ol_discount18::NUMERIC(17, 2),
		v_ol_comments18::VARCHAR(100),
		v_i_id19::NUMERIC(10),
		v_i_title19::VARCHAR(60),
		v_i_publisher19::VARCHAR(60),
		v_i_cost19::NUMERIC(17, 2),
		v_ol_qty19::NUMERIC(3),
		v_ol_discount19::NUMERIC(17, 2),
		v_ol_comments19::VARCHAR(100),
		v_i_id20::NUMERIC(10),
		v_i_title20::VARCHAR(60),
		v_i_publisher20::VARCHAR(60),
		v_i_cost20::NUMERIC(17, 2),
		v_ol_qty20::NUMERIC(3),
		v_ol_discount20::NUMERIC(17, 2),
		v_ol_comments20::VARCHAR(100)
		INTO ret;

		RETURN NEXT ret;
	RETURN;

	END;
' LANGUAGE 'plpgsql';
commit;
-- Usage:
-- 
-- SELECT * FROM (
--		c_uname VARCHAR(20),
--		c_passwd VARCHAR(20),
-- )
-- AS l(
--		c_fname VARCHAR(15),
--		c_lname VARCHAR(15),
--		c_phone VARCHAR(16),
--		c_email VARCHAR(50),
--		o_id NUMERIC(10),
--		o_date CHAR(26),
--		o_sub_total NUMERIC(17, 2),
--		o_tax NUMERIC(17, 2),
--		o_total NUMERIC(17, 2),
--		o_ship_type VARCHAR(10),
--		o_ship_date CHAR(26),
--		o_status VARCHAR(15),
--		cx_type VARCHAR(10),
--		cx_auth_id VARCHAR(15),
--		bill_addr_street1 VARCHAR(40),
--		bill_addr_street2 VARCHAR(40),
--		bill_addr_city VARCHAR(30),
--		bill_addr_state VARCHAR(20),
--		bill_addr_zip VARCHAR(10),
--		bill_co_name VARCHAR(50),
--		ship_addr_street1 VARCHAR(40),
--		ship_addr_street2 VARCHAR(40),
--		ship_addr_city VARCHAR(30),
--		ship_addr_state VARCHAR(20),
--		ship_addr_zip VARCHAR(10),
--		ship_co_name VARCHAR(50),
--		num_item NUMERIC(3,0),
--		i_id1 NUMERIC(10),
--		i_title1 VARCHAR(60),
--		i_publisher1 VARCHAR(60),
--		i_cost1 NUMERIC(17, 2),
--		ol_qty1 NUMERIC(3),
--		ol_discount1 NUMERIC(17, 2),
--		ol_comments1 VARCHAR(100),
--		i_id2 NUMERIC(10),
--		i_title2 VARCHAR(60),
--		i_publisher2 VARCHAR(60),
--		i_cost2 NUMERIC(17, 2),
--		ol_qty2 NUMERIC(3),
--		ol_discount2 NUMERIC(17, 2),
--		ol_comments2 VARCHAR(100),
--		i_id3 NUMERIC(10),
--		i_title3 VARCHAR(60),
--		i_publisher3 VARCHAR(60),
--		i_cost3 NUMERIC(17, 2),
--		ol_qty3 NUMERIC(3),
--		ol_discount3 NUMERIC(17, 2),
--		ol_comments3 VARCHAR(100),
--		i_id4 NUMERIC(10),
--		i_title4 VARCHAR(60),
--		i_publisher4 VARCHAR(60),
--		i_cost4 NUMERIC(17, 2),
--		ol_qty4 NUMERIC(3),
--		ol_discount4 NUMERIC(17, 2),
--		ol_comments4 VARCHAR(100),
--		i_id5 NUMERIC(10),
--		i_title5 VARCHAR(60),
--		i_publisher5 VARCHAR(60),
--		i_cost5 NUMERIC(17, 2),
--		ol_qty5 NUMERIC(3),
--		ol_discount5 NUMERIC(17, 2),
--		ol_comments5 VARCHAR(100),
--		i_id6 numeric(10),
--		i_title6 VARCHAR(60),
--		i_publisher6 VARCHAR(60),
--		i_cost6 numeric(17, 2),
--		ol_qty6 numeric(3),
--		ol_discount6 numeric(17, 2),
--		ol_comments6 VARCHAR(100),
--		i_id7 numeric(10),
--		i_title7 VARCHAR(60),
--		i_publisher7 VARCHAR(60),
--		i_cost7 numeric(17, 2),
--		ol_qty7 numeric(3),
--		ol_discount7 numeric(17, 2),
--		ol_comments7 VARCHAR(100),
--		i_id8 numeric(10),
--		i_title8 VARCHAR(60),
--		i_publisher8 VARCHAR(60),
--		i_cost8 numeric(17, 2),
--		ol_qty8 numeric(3),
--		ol_discount8 numeric(17, 2),
--		ol_comments8 VARCHAR(100),
--		i_id9 numeric(10),
--		i_title9 VARCHAR(60),
--		i_publisher9 VARCHAR(60),
--		i_cost9 numeric(17, 2),
--		ol_qty9 numeric(3),
--		ol_discount9 numeric(17, 2),
--		ol_comments9 VARCHAR(100),
--		i_id10 numeric(10),
--		i_title10 VARCHAR(60),
--		i_publisher10 VARCHAR(60),
--		i_cost10 numeric(17, 2),
--		ol_qty10 numeric(3),
--		ol_discount10 numeric(17, 2),
--		ol_comments10 VARCHAR(100),
--		i_id11 numeric(10),
--		i_title11 VARCHAR(60),
--		i_publisher11 VARCHAR(60),
--		i_cost11 numeric(17, 2),
--		ol_qty11 numeric(3),
--		ol_discount11 numeric(17, 2),
--		ol_comments11 VARCHAR(100),
--		i_id12 numeric(10),
--		i_title12 VARCHAR(60),
--		i_publisher12 VARCHAR(60),
--		i_cost12 numeric(17, 2),
--		ol_qty12 numeric(3),
--		ol_discount12 numeric(17, 2),
--		ol_comments12 VARCHAR(100),
--		i_id13 numeric(10),
--		i_title13 VARCHAR(60),
--		i_publisher13 VARCHAR(60),
--		i_cost13 numeric(17, 2),
--		ol_qty13 numeric(3),
--		ol_discount13 numeric(17, 2),
--		ol_comments13 VARCHAR(100),
--		i_id14 numeric(10),
--		i_title14 VARCHAR(60),
--		i_publisher14 VARCHAR(60),
--		i_cost14 numeric(17, 2),
--		ol_qty14 numeric(3),
--		ol_discount14 numeric(17, 2),
--		ol_comments14 VARCHAR(100),
--		i_id15 numeric(10),
--		i_title15 VARCHAR(60),
--		i_publisher15 VARCHAR(60),
--		i_cost15 numeric(17, 2),
--		ol_qty15 numeric(3),
--		ol_discount15 numeric(17, 2),
--		ol_comments15 VARCHAR(100),
--		i_id16 numeric(10),
--		i_title16 VARCHAR(60),
--		i_publisher16 VARCHAR(60),
--		i_cost16 numeric(17, 2),
--		ol_qty16 numeric(3),
--		ol_discount16 numeric(17, 2),
--		ol_comments16 VARCHAR(100),
--		i_id17 numeric(10),
--		i_title17 VARCHAR(60),
--		i_publisher17 VARCHAR(60),
--		i_cost17 numeric(17, 2),
--		ol_qty17 numeric(3),
--		ol_discount17 numeric(17, 2),
--		ol_comments17 VARCHAR(100),
--		i_id18 numeric(10),
--		i_title18 VARCHAR(60),
--		i_publisher18 VARCHAR(60),
--		i_cost18 numeric(17, 2),
--		ol_qty18 numeric(3),
--		ol_discount18 numeric(17, 2),
--		ol_comments18 VARCHAR(100),
--		i_id19 numeric(10),
--		i_title19 VARCHAR(60),
--		i_publisher19 VARCHAR(60),
--		i_cost19 numeric(17, 2),
--		ol_qty19 numeric(3),
--		ol_discount19 numeric(17, 2),
--		ol_comments19 VARCHAR(100),
--		i_id20 numeric(10),
--		i_title20 VARCHAR(60),
--		i_publisher20 VARCHAR(60),
--		i_cost20 numeric(17, 2),
--		ol_qty20 numeric(3),
--		ol_discount20 numeric(17, 2),
--		ol_comments20 VARCHAR(100),
--);

