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
CREATE FUNCTION order_inquiry(NUMERIC(10)) RETURNS VARCHAR(20) AS '
DECLARE id_client ALIAS FOR $1;
DECLARE client_name VARCHAR(20);
BEGIN
  SELECT c_uname INTO client_name
  FROM customer WHERE c_id = id_client;
  return client_name;
END;
' LANGUAGE 'plpgsql';
