\set AUTOCOMMIT off
COPY orders FROM '/tmp/orders.data' WITH DELIMITER '>';
commit ;
