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
CREATE OR REPLACE FUNCTION buy_confirm (
	VARCHAR(10),
	NUMERIC(16),
	VARCHAR(31),
	CHAR(8), 
	NUMERIC(10),
	NUMERIC(10),
	NUMERIC(1),
	VARCHAR(100),
	CHAR(15),
	VARCHAR(40),
	VARCHAR(40),
	VARCHAR(30),
	VARCHAR(20),
	VARCHAR(10),
	VARCHAR(50)
) RETURNS RECORD AS '
	DECLARE
		_cc_type ALIAS FOR $1;
		_cc_num ALIAS FOR $2;
		_cc_name ALIAS FOR $3;
		_cc_expiry ALIAS FOR $4;
		_sc_id ALIAS FOR $5;
		_c_id ALIAS FOR $6;
		_days ALIAS FOR $7;
		_comment ALIAS FOR $8;
		_auth_id ALIAS FOR $9;
		_addr_street1 ALIAS FOR $10;
		_addr_street2 ALIAS FOR $11;
		_addr_city ALIAS FOR $12;
		_addr_state ALIAS FOR $13;
		_addr_zip ALIAS FOR $14;
		_country ALIAS FOR $15;
		_c_discount NUMERIC(5,2);
		_sc_sub_total NUMERIC(17,2);
		_sc_tax NUMERIC(17,2);
		_sc_ship_cost NUMERIC(17,2);
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
		-- VARs
		_c_addr_id NUMERIC(10); 
		_c_fname CHAR(15); 
		_c_lname CHAR(15); 
		_co_id NUMERIC(4,0);
		_ship_addr_id NUMERIC(10);	
		_ol_id NUMERIC(3);
		_i_stock NUMERIC(4); 
		_scl_i_id NUMERIC(10); 
		_scl_qty NUMERIC(3);
		_scl_cost NUMERIC(17,2); 
		cur_timestamp DATE;
		add_timestamp DATE;
		refcur REFCURSOR;
		rec RECORD;
		localdays NUMERIC(1);
		tmpdate DATE;
	BEGIN
		tmpdate := _cc_expiry;

		SELECT sc_sub_total, sc_tax, sc_ship_cost, sc_total 
		INTO _sc_sub_total, _sc_tax, _sc_ship_cost, _sc_total
		FROM shopping_cart 
		WHERE sc_id = _sc_id;

		SELECT c_fname, c_lname, c_discount, c_addr_id 
		INTO _c_fname, _c_lname, _c_discount, _c_addr_id
		FROM customer 
		WHERE c_id = _c_id;

		--RAISE NOTICE ''_addr_street1=%'', _addr_street1;
		IF _addr_street1 <> '''' THEN 

			SELECT addr_id, co_id 
			INTO _ship_addr_id, _co_id 
			FROM address, country
			WHERE co_name = _country 
				AND addr_co_id = co_id 
				AND addr_zip = _addr_zip 
				AND addr_state = _addr_state 
				AND addr_city = _addr_city 
				AND addr_street1 = _addr_street1 
				AND addr_street2 = _addr_street2;

			IF NOT FOUND THEN
				_ship_addr_id := nextval(''AddrID'');
				INSERT INTO address 
				VALUES(_ship_addr_id, _addr_street1, _addr_street2, 
							 _addr_city, _addr_state, _addr_zip, _co_id);
			END IF;

		ELSE 
			_ship_addr_id := _c_addr_id;
			SELECT addr_co_id 
			INTO _co_id 
			FROM address 
			WHERE addr_id = _ship_addr_id;
		END IF;

		/**********************************************************
		 *
		 *									Porting "adddate"
		 *
		 *********************************************************/
		cur_timestamp := CURRENT_TIMESTAMP;		
		add_timestamp := cur_timestamp;
		localdays := _days;
		WHILE (localdays <> 0) LOOP
			add_timestamp := add_timestamp + 1;
			localdays := localdays - 1;
		END LOOP;
		--RAISE NOTICE ''_days=% add_timestamp=%'', _days, add_timestamp;

		INSERT INTO orders 
		VALUES(_sc_id, _c_id, cur_timestamp, _sc_sub_total,
					 _sc_tax, _sc_total, ''SHIP'', add_timestamp, _c_addr_id,
					 _ship_addr_id, ''PENDING'');

		_ol_id := 0;

		OPEN refcur FOR SELECT scl_i_id, scl_cost, scl_qty 
		FROM shopping_cart_line
		WHERE scl_sc_id = _sc_id;

		WHILE FOUND LOOP
			FETCH refcur INTO _scl_i_id, _scl_cost, _scl_qty;
			IF FOUND THEN
				_ol_id := _ol_id + 1;
				--RAISE NOTICE ''_ol_id=% _sc_id=%'', _ol_id, _sc_id;
				INSERT INTO order_line 
					VALUES(_ol_id, _sc_id, _scl_i_id, _scl_qty,
								 _c_discount, _comment);

				SELECT i_stock 
				INTO _i_stock 
				FROM item 
				WHERE i_id = _scl_i_id;
				
				IF (_i_stock - 10 > _scl_qty) THEN
						_i_stock := _i_stock - _scl_qty;
				ELSE
					_i_stock := _i_stock - _scl_qty + 21;
					UPDATE item 
					SET i_stock = _i_stock 
					WHERE i_id = _scl_i_id;
				END IF;
			END IF;
		END LOOP;

		CLOSE refcur;

		cur_timestamp := CURRENT_TIMESTAMP;
		INSERT INTO cc_xacts 
		VALUES(_sc_id, _cc_type, _cc_num, _cc_name,
					 tmpdate, _auth_id, _sc_total, cur_timestamp, _co_id); 


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
			s_i_id1 NUMERIC(10,0), s_title1 VARCHAR(60), s_cost1 NUMERIC(17,2),
			s_srp1 NUMERIC(17,2), s_backing1 VARCHAR(15), s_qty1 NUMERIC(3,0),
			s_i_id2 NUMERIC(10,0), s_title2 VARCHAR(60), s_cost2 NUMERIC(17,2),
			s_srp2 NUMERIC(17,2), s_backing2 VARCHAR(15), s_qty2 NUMERIC(3,0),
			s_i_id3 NUMERIC(10,0), s_title3 VARCHAR(60), s_cost3 NUMERIC(17,2),
			s_srp3 NUMERIC(17,2), s_backing3 VARCHAR(15), s_qty3 NUMERIC(3,0),
			s_i_id4 NUMERIC(10,0), s_title4 VARCHAR(60), s_cost4 NUMERIC(17,2),
			s_srp4 NUMERIC(17,2), s_backing4 VARCHAR(15), s_qty4 NUMERIC(3,0),
			s_i_id5 NUMERIC(10,0), s_title5 VARCHAR(60), s_cost5 NUMERIC(17,2),
			s_srp5 NUMERIC(17,2), s_backing5 VARCHAR(15), s_qty5 NUMERIC(3,0),
			s_i_id6 NUMERIC(10,0), s_title6 VARCHAR(60), s_cost6 NUMERIC(17,2),
			s_srp6 NUMERIC(17,2), s_backing6 VARCHAR(15), s_qty6 NUMERIC(3,0),
			s_i_id7 NUMERIC(10,0), s_title7 VARCHAR(60), s_cost7 NUMERIC(17,2),
			s_srp7 NUMERIC(17,2), s_backing7 VARCHAR(15), s_qty7 NUMERIC(3,0),
			s_i_id8 NUMERIC(10,0), s_title8 VARCHAR(60), s_cost8 NUMERIC(17,2),
			s_srp8 NUMERIC(17,2), s_backing8 VARCHAR(15), s_qty8 NUMERIC(3,0),
			s_i_id9 NUMERIC(10,0), s_title9 VARCHAR(60), s_cost9 NUMERIC(17,2),
			s_srp9 NUMERIC(17,2), s_backing9 VARCHAR(15), s_qty9 NUMERIC(3,0),
			s_i_id10 NUMERIC(10,0), s_title10 VARCHAR(60), s_cost10 NUMERIC(17,2),
			s_srp10 NUMERIC(17,2), s_backing10 VARCHAR(15), s_qty10 NUMERIC(3,0),
			s_i_id11 NUMERIC(10,0), s_title11 VARCHAR(60), s_cost11 NUMERIC(17,2),
			s_srp11 NUMERIC(17,2), s_backing11 VARCHAR(15), s_qty11 NUMERIC(3,0),
			s_i_id12 NUMERIC(10,0), s_title12 VARCHAR(60), s_cost12 NUMERIC(17,2),
			s_srp12 NUMERIC(17,2), s_backing12 VARCHAR(15), s_qty12 NUMERIC(3,0),
			s_i_id13 NUMERIC(10,0), s_title13 VARCHAR(60), s_cost13 NUMERIC(17,2),
			s_srp13 NUMERIC(17,2), s_backing13 VARCHAR(15), s_qty13 NUMERIC(3,0),
			s_i_id14 NUMERIC(10,0), s_title14 VARCHAR(60), s_cost14 NUMERIC(17,2),
			s_srp14 NUMERIC(17,2), s_backing14 VARCHAR(15), s_qty14 NUMERIC(3,0),
			s_i_id15 NUMERIC(10,0), s_title15 VARCHAR(60), s_cost15 NUMERIC(17,2),
			s_srp15 NUMERIC(17,2), s_backing15 VARCHAR(15), s_qty15 NUMERIC(3,0),
			s_i_id16 NUMERIC(10,0), s_title16 VARCHAR(60), s_cost16 NUMERIC(17,2),
			s_srp16 NUMERIC(17,2), s_backing16 VARCHAR(15), s_qty16 NUMERIC(3,0),
			s_i_id17 NUMERIC(10,0), s_title17 VARCHAR(60), s_cost17 NUMERIC(17,2),
			s_srp17 NUMERIC(17,2), s_backing17 VARCHAR(15), s_qty17 NUMERIC(3,0),
			s_i_id18 NUMERIC(10,0), s_title18 VARCHAR(60), s_cost18 NUMERIC(17,2),
			s_srp18 NUMERIC(17,2), s_backing18 VARCHAR(15), s_qty18 NUMERIC(3,0),
			s_i_id19 NUMERIC(10,0), s_title19 VARCHAR(60), s_cost19 NUMERIC(17,2),
			s_srp19 NUMERIC(17,2), s_backing19 VARCHAR(15), s_qty19 NUMERIC(3,0),
			s_i_id20 NUMERIC(10,0), s_title20 VARCHAR(60), s_cost20 NUMERIC(17,2),
			s_srp20 NUMERIC(17,2), s_backing20 VARCHAR(15), s_qty20 NUMERIC(3,0));


		SELECT 
		_c_discount::NUMERIC(5,2), 
		_sc_sub_total::NUMERIC(17,2),
		_sc_tax::NUMERIC(17,2), 
		_sc_ship_cost::NUMERIC(17,2),
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
--		cc_type VARCHAR(10),
--		cc_num NUMERIC(16),
--		cc_name VARCHAR(31),
--		cc_expiry DATE, -- cc_expiry CHAR(8),
--		sc_id NUMERIC(10),
--		c_id NUMERIC(10),
--		days NUMERIC(1),
--		comment VARCHAR(100),
--		auth_id CHAR(15),
--		addr_street1 VARCHAR(40),
--		addr_street2 VARCHAR(40),
--		addr_city VARCHAR(30),
--		addr_state VARCHAR(20),
--		addr_zip VARCHAR(10),
--		country VARCHAR(50),
-- )
-- AS l(
--		c_discount NUMERIC(5,2),
--		sc_sub_total NUMERIC(17,2),
--		sc_tax NUMERIC(17,2),
--		sc_ship_cost NUMERIC(17,2),
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
-- );
