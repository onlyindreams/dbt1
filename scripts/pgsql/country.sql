\set AUTOCOMMIT off
COPY country FROM '/tmp/country.data' WITH DELIMITER '>';
commit;
