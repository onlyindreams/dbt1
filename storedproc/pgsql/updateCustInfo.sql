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
CREATE FUNCTION updateCustinfo (NUMERIC(10,0)) RETURNS INTEGER AS '

DECLARE

	customer_id alias for $1;
	tmptime timestamp;

BEGIN
--Change c_expiration=''tomorrow'' by c_expiration := addTime(0 5:00:00)
	UPDATE customer set c_login=''now'', c_expiration=''tomorrow''
	WHERE c_id=customer_id;
	RETURN 1;
END;
' LANGUAGE 'plpgsql';

