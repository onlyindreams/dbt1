SET autocommit = false ;
COPY author FROM '/tmp/author.data' USING DELIMITERS '\\';
commit;
