SET autocommit = false ;
COPY orders FROM '/tmp/orders.data' USING DELIMITERS '\\';
commit ;

