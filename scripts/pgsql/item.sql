\set AUTOCOMMIT off
COPY item FROM '/tmp/item.data' WITH DELIMITER '>';
commit ;
