--
--
-- This file is released under the terms of the Artistic License.	Please see
-- the file LICENSE, included in this package, for details.
--
-- Copyright (C) 2002 Open Source Development Lab, Inc.
-- History: 
-- July-2003: Created by Satoshi Nagayasu & Hideyuki Kawashima
--
\set AUTOCOMMIT off
CREATE OR REPLACE FUNCTION buy_request (
	NUMERIC(1),
	VARCHAR(20),
	NUMERIC(10),
	NUMERIC(5,2),
	VARCHAR(15),
	VARCHAR(15),
	VARCHAR(40),
	VARCHAR(40),
	VARCHAR(30),
	VARCHAR(20),
	VARCHAR(10),
	VARCHAR(50),
	VARCHAR(16),
	VARCHAR(50),
	CHAR(10),
	VARCHAR(500)
) RETURNS RECORD AS '
	DECLARE
		_flag ALIAS FOR $1;
		_c_uname ALIAS FOR $2;
		_sc_id ALIAS FOR $3;
		_c_discount ALIAS FOR $4;
		_c_fname ALIAS FOR $5;
		_c_lname ALIAS FOR $6;
		_addr_street1 ALIAS FOR $7;
		_addr_street2 ALIAS FOR $8;
		_addr_city ALIAS FOR $9;
		_addr_state ALIAS FOR $10;
		_addr_zip ALIAS FOR $11;
		_co_name ALIAS FOR $12;
		_c_phone ALIAS FOR $13;
		_c_email ALIAS FOR $14;
		_c_birthdate ALIAS FOR $15;
		_c_data ALIAS FOR $16;
		local_c_discount NUMERIC(5,2);
		local_c_fname VARCHAR(15);
		local_c_lname VARCHAR(15);
		local_addr_street1 VARCHAR(40);
		local_addr_street2 VARCHAR(40);
		local_addr_city VARCHAR(30);
		local_addr_state VARCHAR(20);
		local_addr_zip VARCHAR(10);
		local_co_name VARCHAR(50);
		local_c_phone VARCHAR(16);
		local_c_email VARCHAR(50);
		local_c_birthdate CHAR(10);
		local_c_data VARCHAR(500);
		_c_passwd VARCHAR(20);
		_c_id NUMERIC(10);
		_sc_sub_total NUMERIC(17,2);
		_sc_tax NUMERIC(17,2);
		_sc_ship_cost NUMERIC(5,2);
		_sc_total NUMERIC(17,2);
		_num_item NUMERIC(2);
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
		refcur REFCURSOR;
		rec RECORD;
	BEGIN
		IF (_flag = 1) THEN
			SELECT * 
			INTO _c_id, _c_passwd, local_c_fname, local_c_lname, 
					 local_addr_street1, local_addr_street2, 
					 local_addr_city, local_addr_state, local_addr_zip, 
					 local_co_name, local_c_phone, local_c_email, 
					 local_c_data, local_c_birthdate, local_c_discount
			FROM getCustInfo(_c_uname) 
			AS l(c_id NUMERIC(10), 
					 c_passwd VARCHAR(20), 
					 c_fname VARCHAR(15), 
					 c_lname VARCHAR(15), 
					 addr_street1 VARCHAR(40), 
					 addr_street2 VARCHAR(40), 
					 addr_city VARCHAR(30), 
					 addr_state VARCHAR(20), 
					 addr_zip VARCHAR(10), 
					 co_name VARCHAR(50), 
					 c_phone VARCHAR(16), 
					 c_email VARCHAR(50), 
					 c_data VARCHAR(500), 
					 c_birthdate DATE, 
					 c_discount NUMERIC(5,2));
--			RAISE NOTICE ''_c_id=% c_fname=% c_lname=% _c_discount=%'', _c_id, local_c_fname, local_c_lname, _c_discount;
			RAISE NOTICE ''flag=1 _c_id=% c_fname=% c_lname=% _c_discount=%'', _c_id, local_c_fname, local_c_lname, _c_discount;
		ELSE
			SELECT InsertCust(_co_name, _addr_street1, _addr_street2, _addr_city,
				_addr_state, _addr_zip, _c_fname, _c_lname, _c_phone, _c_email,
				_c_data, _sc_id, _c_discount, _c_birthdate)
			INTO _c_id;

			UPDATE shopping_cart 
			SET sc_c_fname = _c_fname, sc_c_lname = _c_lname,
					sc_c_discount = _c_discount, sc_c_id = _c_id 
			WHERE sc_id = _sc_id;

			/***************************************************
			 *
			 * These lines are appended to absorb differences
			 * between local_X and X
			 *
			 **************************************************/
			local_co_name := _co_name;
			local_addr_street1 := _addr_street1; 
			local_addr_street2 := _addr_street2;
			local_addr_city := _addr_city;
			local_addr_state := _addr_state;
			local_addr_zip := _addr_zip;
			local_c_fname := _c_fname;
			local_c_lname := _c_lname; 
			local_c_phone := _c_phone; 
			local_c_email := _c_email;
			local_c_data := _c_data;
			local_c_discount := _c_discount;
			local_c_birthdate := _c_birthdate;
		END IF;

		SELECT * 
		INTO _sc_sub_total, _sc_tax, _sc_ship_cost, _sc_total
		FROM updateSC(_sc_id, local_c_discount)
		AS l(ss_total NUMERIC(17,2), s_tax NUMERIC(17,2),
				 ss_cost NUMERIC(5,2), s_total NUMERIC(17,2));


		SELECT *
		INTO _num_item,
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
		FROM getSCDetail(_sc_id)
		AS l( 
			n_i NUMERIC(2,0),
			s_i_id1 NUMERIC(10,0),
			s_title1 VARCHAR(60),
			s_cost1 NUMERIC(17,2),
			s_srp1 NUMERIC(17,2),
			s_backing1 VARCHAR(15),
			s_qty1 NUMERIC(3,0),
			s_i_id2 NUMERIC(10,0),
			s_title2 VARCHAR(60),
			s_cost2 NUMERIC(17,2),
			s_srp2 NUMERIC(17,2),
			s_backing2 VARCHAR(15),
			s_qty2 NUMERIC(3,0),
			s_i_id3 NUMERIC(10,0),
			s_title3 VARCHAR(60),
			s_cost3 NUMERIC(17,2),
			s_srp3 NUMERIC(17,2),
			s_backing3 VARCHAR(15),
			s_qty3 NUMERIC(3,0),
			s_i_id4 NUMERIC(10,0),
			s_title4 VARCHAR(60),
			s_cost4 NUMERIC(17,2),
			s_srp4 NUMERIC(17,2),
			s_backing4 VARCHAR(15),
			s_qty4 NUMERIC(3,0),
			s_i_id5 NUMERIC(10,0),
			s_title5 VARCHAR(60),
			s_cost5 NUMERIC(17,2),
			s_srp5 NUMERIC(17,2),
			s_backing5 VARCHAR(15),
			s_qty5 NUMERIC(3,0),
			s_i_id6 NUMERIC(10,0),
			s_title6 VARCHAR(60),
			s_cost6 NUMERIC(17,2),
			s_srp6 NUMERIC(17,2),
			s_backing6 VARCHAR(15),
			s_qty6 NUMERIC(3,0),
			s_i_id7 NUMERIC(10,0),
			s_title7 VARCHAR(60),
			s_cost7 NUMERIC(17,2),
			s_srp7 NUMERIC(17,2),
			s_backing7 VARCHAR(15),
			s_qty7 NUMERIC(3,0),
			s_i_id8 NUMERIC(10,0),
			s_title8 VARCHAR(60),
			s_cost8 NUMERIC(17,2),
			s_srp8 NUMERIC(17,2),
			s_backing8 VARCHAR(15),
			s_qty8 NUMERIC(3,0),
			s_i_id9 NUMERIC(10,0),
			s_title9 VARCHAR(60),
			s_cost9 NUMERIC(17,2),
			s_srp9 NUMERIC(17,2),
			s_backing9 VARCHAR(15),
			s_qty9 NUMERIC(3,0),
			s_i_id10 NUMERIC(10,0),
			s_title10 VARCHAR(60),
			s_cost10 NUMERIC(17,2),
			s_srp10 NUMERIC(17,2),
			s_backing10 VARCHAR(15),
			s_qty10 NUMERIC(3,0),
			s_i_id11 NUMERIC(10,0),
			s_title11 VARCHAR(60),
			s_cost11 NUMERIC(17,2),
			s_srp11 NUMERIC(17,2),
			s_backing11 VARCHAR(15),
			s_qty11 NUMERIC(3,0),
			s_i_id12 NUMERIC(10,0),
			s_title12 VARCHAR(60),
			s_cost12 NUMERIC(17,2),
			s_srp12 NUMERIC(17,2),
			s_backing12 VARCHAR(15),
			s_qty12 NUMERIC(3,0),
			s_i_id13 NUMERIC(10,0),
			s_title13 VARCHAR(60),
			s_cost13 NUMERIC(17,2),
			s_srp13 NUMERIC(17,2),
			s_backing13 VARCHAR(15),
			s_qty13 NUMERIC(3,0),
			s_i_id14 NUMERIC(10,0),
			s_title14 VARCHAR(60),
			s_cost14 NUMERIC(17,2),
			s_srp14 NUMERIC(17,2),
			s_backing14 VARCHAR(15),
			s_qty14 NUMERIC(3,0),
			s_i_id15 NUMERIC(10,0),
			s_title15 VARCHAR(60),
			s_cost15 NUMERIC(17,2),
			s_srp15 NUMERIC(17,2),
			s_backing15 VARCHAR(15),
			s_qty15 NUMERIC(3,0),
			s_i_id16 NUMERIC(10,0),
			s_title16 VARCHAR(60),
			s_cost16 NUMERIC(17,2),
			s_srp16 NUMERIC(17,2),
			s_backing16 VARCHAR(15),
			s_qty16 NUMERIC(3,0),
			s_i_id17 NUMERIC(10,0),
			s_title17 VARCHAR(60),
			s_cost17 NUMERIC(17,2),
			s_srp17 NUMERIC(17,2),
			s_backing17 VARCHAR(15),
			s_qty17 NUMERIC(3,0),
			s_i_id18 NUMERIC(10,0),
			s_title18 VARCHAR(60),
			s_cost18 NUMERIC(17,2),
			s_srp18 NUMERIC(17,2),
			s_backing18 VARCHAR(15),
			s_qty18 NUMERIC(3,0),
			s_i_id19 NUMERIC(10,0),
			s_title19 VARCHAR(60),
			s_cost19 NUMERIC(17,2),
			s_srp19 NUMERIC(17,2),
			s_backing19 VARCHAR(15),
			s_qty19 NUMERIC(3,0),
			s_i_id20 NUMERIC(10,0),
			s_title20 VARCHAR(60),
			s_cost20 NUMERIC(17,2),
			s_srp20 NUMERIC(17,2),
			s_backing20 VARCHAR(15),
			s_qty20 NUMERIC(3,0));

		SELECT 
		local_c_discount::NUMERIC(5,2),
		local_c_fname::VARCHAR(15),
		local_c_lname::VARCHAR(15),
		local_addr_street1::VARCHAR(40),
		local_addr_street2::VARCHAR(40),
		local_addr_city::VARCHAR(30),
		local_addr_state::VARCHAR(20),
		local_addr_zip::VARCHAR(10),
		local_co_name::VARCHAR(50),
		local_c_phone::VARCHAR(16),
		local_c_email::VARCHAR(50),
		local_c_birthdate::CHAR(10),
		local_c_data::VARCHAR(500),
		_c_passwd::VARCHAR(20),
		_c_id::NUMERIC(10),
		_sc_sub_total::NUMERIC(17,2),
		_sc_tax::NUMERIC(17,2),
		_sc_ship_cost::NUMERIC(5,2),
		_sc_total::NUMERIC(17,2),
		_num_item::NUMERIC(2),
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
-- Usage:
-- 
-- SELECT * FROM (
--		flag NUMERIC(1),
--		c_uname VARCHAR(20),
--		sc_id NUMERIC(10),
--		c_discount NUMERIC(5,2),
--		c_fname VARCHAR(15),
--		c_lname VARCHAR(15),
--		addr_street1 VARCHAR(40),
--		addr_street2 VARCHAR(40),
--		addr_city VARCHAR(30),
--		addr_state VARCHAR(20),
--		addr_zip VARCHAR(10),
--		co_name VARCHAR(50),
--		c_phone VARCHAR(16),
--		c_email VARCHAR(50),
--		c_birthday CHAR(10),
--		c_data VARCHAR(500),
-- )
-- AS l(
--		local_c_discount NUMERIC(5,2),
--		c_fname VARCHAR(15),
--		c_lname VARCHAR(15),
--		addr_street1 VARCHAR(40),
--		addr_street2 VARCHAR(40),
--		addr_city VARCHAR(30),
--		addr_state VARCHAR(20),
--		addr_zip VARCHAR(10),
--		co_name VARCHAR(50),
--		c_phone VARCHAR(16),
--		c_email VARCHAR(50),
--		c_birthday CHAR(10),
--		c_data VARCHAR(500),
--		c_passwd VARCHAR(20),
--		c_id NUMERIC(10),
--		sc_sub_total NUMERIC(17,2),
--		sc_tax NUMERIC(17,2),
--		sc_ship_cost NUMERIC(5,2),
--		sc_total NUMERIC(17,2),
--		num_item NUMERIC(2),
--		scl_i_id1 NUMERIC(10),
--		scl_title1 VARCHAR(60),
--		scl_cost1 NUMERIC(17,2),
--		scl_srp1 NUMERIC(17,2),
--		scl_backing1 VARCHAR(15),
--		scl_qty1 NUMERIC(3),
--		scl_i_id2 NUMERIC(10),
--		scl_title2 VARCHAR(60),
--		scl_cost2 NUMERIC(17,2),
--		scl_srp2 NUMERIC(17,2),
--		scl_backing2 VARCHAR(15),
--		scl_qty2 NUMERIC(3),
--		scl_i_id3 NUMERIC(10),
--		scl_title3 VARCHAR(60),
--		scl_cost3 NUMERIC(17,2),
--		scl_srp3 NUMERIC(17,2),
--		scl_backing3 VARCHAR(15),
--		scl_qty3 NUMERIC(3),
--		scl_i_id4 NUMERIC(10),
--		scl_title4 VARCHAR(60),
--		scl_cost4 NUMERIC(17,2),
--		scl_srp4 NUMERIC(17,2),
--		scl_backing4 VARCHAR(15),
--		scl_qty4 NUMERIC(3),
--		scl_i_id5 NUMERIC(10),
--		scl_title5 VARCHAR(60),
--		scl_cost5 NUMERIC(17,2),
--		scl_srp5 NUMERIC(17,2),
--		scl_backing5 VARCHAR(15),
--		scl_qty5 NUMERIC(3),
--		scl_i_id6 NUMERIC(10),
--		scl_title6 VARCHAR(60),
--		scl_cost6 NUMERIC(17,2),
--		scl_srp6 NUMERIC(17,2),
--		scl_backing6 VARCHAR(15),
--		scl_qty6 NUMERIC(3),
--		scl_i_id7 NUMERIC(10),
--		scl_title7 VARCHAR(60),
--		scl_cost7 NUMERIC(17,2),
--		scl_srp7 NUMERIC(17,2),
--		scl_backing7 VARCHAR(15),
--		scl_qty7 NUMERIC(3),
--		scl_i_id8 NUMERIC(10),
--		scl_title8 VARCHAR(60),
--		scl_cost8 NUMERIC(17,2),
--		scl_srp8 NUMERIC(17,2),
--		scl_backing8 VARCHAR(15),
--		scl_qty8 NUMERIC(3),
--		scl_i_id9 NUMERIC(10),
--		scl_title9 VARCHAR(60),
--		scl_cost9 NUMERIC(17,2),
--		scl_srp9 NUMERIC(17,2),
--		scl_backing9 VARCHAR(15),
--		scl_qty9 NUMERIC(3),
--		scl_i_id10 NUMERIC(10),
--		scl_title10 VARCHAR(60),
--		scl_cost10 NUMERIC(17,2),
--		scl_srp10 NUMERIC(17,2),
--		scl_backing10 VARCHAR(15),
--		scl_qty10 NUMERIC(3),
--		scl_i_id11 NUMERIC(10),
--		scl_title11 VARCHAR(60),
--		scl_cost11 NUMERIC(17,2),
--		scl_srp11 NUMERIC(17,2),
--		scl_backing11 VARCHAR(15),
--		scl_qty11 NUMERIC(3),
--		scl_i_id12 NUMERIC(10),
--		scl_title12 VARCHAR(60),
--		scl_cost12 NUMERIC(17,2),
--		scl_srp12 NUMERIC(17,2),
--		scl_backing12 VARCHAR(15),
--		scl_qty12 NUMERIC(3),
--		scl_i_id13 NUMERIC(10),
--		scl_title13 VARCHAR(60),
--		scl_cost13 NUMERIC(17,2),
--		scl_srp13 NUMERIC(17,2),
--		scl_backing13 VARCHAR(15),
--		scl_qty13 NUMERIC(3),
--		scl_i_id14 NUMERIC(10),
--		scl_title14 VARCHAR(60),
--		scl_cost14 NUMERIC(17,2),
--		scl_srp14 NUMERIC(17,2),
--		scl_backing14 VARCHAR(15),
--		scl_qty14 NUMERIC(3),
--		scl_i_id15 NUMERIC(10),
--		scl_title15 VARCHAR(60),
--		scl_cost15 NUMERIC(17,2),
--		scl_srp15 NUMERIC(17,2),
--		scl_backing15 VARCHAR(15),
--		scl_qty15 NUMERIC(3),
--		scl_i_id16 NUMERIC(10),
--		scl_title16 VARCHAR(60),
--		scl_cost16 NUMERIC(17,2),
--		scl_srp16 NUMERIC(17,2),
--		scl_backing16 VARCHAR(15),
--		scl_qty16 NUMERIC(3),
--		scl_i_id17 NUMERIC(10),
--		scl_title17 VARCHAR(60),
--		scl_cost17 NUMERIC(17,2),
--		scl_srp17 NUMERIC(17,2),
--		scl_backing17 VARCHAR(15),
--		scl_qty17 NUMERIC(3),
--		scl_i_id18 NUMERIC(10),
--		scl_title18 VARCHAR(60),
--		scl_cost18 NUMERIC(17,2),
--		scl_srp18 NUMERIC(17,2),
--		scl_backing18 VARCHAR(15),
--		scl_qty18 NUMERIC(3),
--		scl_i_id19 NUMERIC(10),
--		scl_title19 VARCHAR(60),
--		scl_cost19 NUMERIC(17,2),
--		scl_srp19 NUMERIC(17,2),
--		scl_backing19 VARCHAR(15),
--		scl_qty19 NUMERIC(3),
--		scl_i_id20 NUMERIC(10),
--		scl_title20 VARCHAR(60),
--		scl_cost20 NUMERIC(17,2),
--		scl_srp20 NUMERIC(17,2),
--		scl_backing20 VARCHAR(15),
--		scl_qty20 NUMERIC(3),
--);

