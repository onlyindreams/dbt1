\set AUTOCOMMIT off
COPY author FROM '/tmp/author.data' WITH DELIMITER '>';
commit;
