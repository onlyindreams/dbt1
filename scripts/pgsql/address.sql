SET autocommit = false ;
COPY address FROM '/tmp/address.data' USING DELIMITERS '\\';
commit ;
