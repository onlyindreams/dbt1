SET autocommit = false ;
COPY customer FROM '/tmp/customer.data' USING DELIMITERS '\\';
commit ;

