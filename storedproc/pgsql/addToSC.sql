--
--
-- This file is released under the terms of the Artistic License.	Please see
-- the file LICENSE, included in this package, for details.
--
-- Copyright (C) 2002 Open Source Development Lab, Inc.
-- History: 
-- July-2003: Created by Satoshi Nagayasu & Hideyuki Kawashima
-- Aug-12-2003:  Removed initializing values by Jenny Zhang
--
\set AUTOCOMMIT off
CREATE OR REPLACE FUNCTION addToSC (NUMERIC(10,0), NUMERIC(1,0), NUMERIC(10,0) ) RETURNS INT AS '
	DECLARE
		_sc_id ALIAS FOR $1;
		_add_flag ALIAS FOR $2;
		_i_id ALIAS FOR $3;

		_itemcount NUMERIC(3,0);
		_scl_qty NUMERIC(3,0);
		_i_cost NUMERIC(17,2);
		_i_srp NUMERIC(17,2);
		_i_title CHAR(60);
		_i_backing CHAR(15);
		_i_related1 NUMERIC(10,0);
		--VARs
		sc_subtotal NUMERIC(17,2);
	BEGIN
--		RAISE NOTICE ''_add_flag=%'', _add_flag;
		IF (_add_flag = 1) THEN

			SELECT sum(scl_qty) 
			INTO _itemcount 
			FROM shopping_cart_line 
			WHERE scl_sc_id = _sc_id;

--			RAISE NOTICE ''_itemcount=%'', _itemcount;
			IF (_itemcount > 100 ) THEN
				RAISE EXCEPTION ''itemcount(%) > 100'', _itemcount;
			ELSE
				UPDATE shopping_cart_line 
					SET scl_qty = scl_qty + 1
				WHERE scl_sc_id = _sc_id 
					AND scl_i_id = _i_id;

				IF NOT FOUND THEN
--					RAISE NOTICE ''not found'';
					SELECT i_cost, i_srp, i_title, i_backing
						INTO _i_cost, _i_srp, _i_title, _i_backing 
						FROM item 
					 WHERE i_id = _i_id;

					INSERT INTO shopping_cart_line
					VALUES(_sc_id, _i_id, 1, _i_cost, _i_srp, _i_title, _i_backing);

				END IF;
			END IF;
		ELSE

--			PERFORM * 
--			FROM shopping_cart_line 
--			WHERE scl_sc_id = _sc_id;

--			IF NOT FOUND THEN

				SELECT t1.i_cost, t1.i_srp, t1.i_title, t1.i_backing, t2.i_related1
					INTO _i_cost, _i_srp, _i_title, _i_backing, _i_related1
					FROM item t1, item t2 
				 WHERE t1.i_id = t2.i_related1 
					 AND t2.i_id = _i_id;

				INSERT INTO shopping_cart_line 
				VALUES(_sc_id, _i_related1, 1, _i_cost, _i_srp, _i_title, _i_backing);

--			END IF;
		END IF;
		SELECT getSCSubTotal(_sc_id) INTO sc_subtotal;
		UPDATE shopping_cart
			SET sc_sub_total=sc_subtotal, sc_date=now()
			WHERE sc_id=_sc_id;
	RETURN 1;
	END;
' LANGUAGE 'plpgsql';
commit;

-- 
-- Usage:
-- 
-- SELECT addToSC ( 
--				 sc_id NUMERIC(10,0)
--				 add_flag NUMERIC(1,0)
--				 i_id NUMERIC(10,0) );

