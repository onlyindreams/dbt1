SET autocommit = false ;
COPY cc_xacts FROM '/tmp/cc_xacts.data' USING DELIMITERS '\\';
commit ;
