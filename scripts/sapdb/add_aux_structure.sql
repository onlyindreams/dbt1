ql_execute create table new_products (i_id fixed(10), i_title varchar(60), i_subject varchar(60), i_pub_date date, a_fname varchar(20), a_lname varchar(20), primary key (i_id))

sql_execute create table best_sellers (i_id fixed(10), i_title varchar(60), i_subject varchar(60), i_pub_date date, a_fname varchar(20), a_lname varchar(20), primary key (i_id))

sql_execute create table search_results_subject (i_id fixed(10), i_title varchar(60), i_subject varchar(60), i_pub_date date, a_fname varchar(20), a_lname varchar(20), primary key (i_id))

sql_execute create table i_related (i_id fixed(10), i_related1 fixed(10), i_related2 fixed(10), i_related3 fixed(10), i_related4 fixed(10), i_related5 fixed(10), primary key (i_id))

sql_execute commit

sql_execute insert into new_products (select i_id, i_title, i_subject, i_pub_date, a_fname, a_lname from item, author where i_a_id=a_id)
sql_execute commit

sql_execute insert into best_sellers (select i_id, i_title, i_subject, i_pub_date, a_fname, a_lname from item, author where i_a_id=a_id)
sql_execute commit

sql_execute insert into search_results_subject (select i_id, i_title, i_subject, i_pub_date, a_fname, a_lname from item, author where i_a_id=a_id)
sql_execute commit

sql_execute insert into i_related (select i_id, i_related1, i_related2, i_related3, i_related4, i_related5 from item)
sql_execute commit
