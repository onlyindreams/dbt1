SET autocommit = false ;
COPY country FROM '/tmp/country.data' USING DELIMITERS '\\';
commit;
