/*
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2002 Open Source Development Lab, Inc.
 * History:
 * Feb 2002: Original version created by Mark Wong & Jenny Zhang 
 * Apr 2003: Rewritten for PostgreSQL by Virginie Megy & Thierry Missimilly
 *		  Bull, Linux Competence Center
 *
 */
CREATE FUNCTION getSCSubTotal (NUMERIC(10)) RETURNS NUMERIC(17,2) AS'
DECLARE
	shop_cart_id alias for $1;
	sub_total numeric(17,2);

	cost numeric(17,2);
	qty numeric(3,0);
	curs_cost_qty refcursor;

BEGIN
sub_total:=0;
OPEN curs_cost_qty FOR SELECT scl_cost,scl_qty FROM shopping_cart_line WHERE scl_sc_id=shop_cart_id;
FETCH curs_cost_qty INTO cost,qty;
WHILE FOUND LOOP
	sub_total:=sub_total+cost*qty;
	FETCH curs_cost_qty INTO cost,qty;
END LOOP;
CLOSE curs_cost_qty;
RETURN sub_total;
END;
' LANGUAGE 'plpgsql';
