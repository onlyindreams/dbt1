\set AUTOCOMMIT off
COPY customer FROM '/tmp/customer.data' WITH DELIMITER '>';
commit ;

