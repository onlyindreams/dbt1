\set AUTOCOMMIT off
COPY order_line FROM '/tmp/order_line.data' USING DELIMITERS '>';
commit ;
