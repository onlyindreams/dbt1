\set AUTOCOMMIT off
COPY cc_xacts FROM '/tmp/cc_xacts.data' WITH DELIMITER '>';
commit ;
