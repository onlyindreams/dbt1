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
CREATE FUNCTION GetPromoImages_Id(NUMERIC(10)) RETURNS NUMERIC(10) AS'
DECLARE
	item_id alias for $1;
	res_id numeric(10);
BEGIN
SELECT i_id FROM item WHERE i_id=item_id ;
RETURN res_id;
END;
' LANGUAGE 'plpgsql';
commit;
