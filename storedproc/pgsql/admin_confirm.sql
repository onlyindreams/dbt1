/*
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2002 Mark Wong & Jenny Zhang &
 *                    Open Source Development Lab, Inc.
 * Contributors : Virginie Megy & Thierry Missimilly
 *		  Bull, Linux Competence Center
 *
 */
CREATE FUNCTION admin_confirm (NUMERIC(10), NUMERIC(10), NUMERIC(10), FLOAT) RETURNS INTEGER AS'
DECLARE 
	item_id alias for $1;
	item_image alias for $2;
	item_thumbnail alias for $3;
	item_cost alias for $4;
BEGIN
  UPDATE item set i_image=item_image, i_thumbnail=item_thumbnail, i_cost=item_cost, i_pub_date=current_date
  WHERE i_id = item_id;
  return 1;
END;
'LANGUAGE 'plpgsql'
