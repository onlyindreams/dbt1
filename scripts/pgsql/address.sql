\set AUTOCOMMIT off
COPY address FROM '/tmp/address.data' WITH DELIMITER '>';
commit ;
