sql_execute create table item ( i_id fixed(10), i_title varchar(60), i_a_id fixed(10), i_pub_date date, i_publisher varchar(60), i_subject varchar(60), i_desc varchar(500), i_related1 fixed(10), i_related2 fixed(10), i_related3 fixed(10), i_related4 fixed(10), i_related5 fixed(10), i_thumbnail fixed(8), i_image fixed(8), i_srp fixed(17, 2), i_cost fixed(17, 2), i_avail date, i_stock fixed(4), i_isbn char(13), i_page fixed(4), i_backing varchar(15), i_dimensions varchar(25) )

sql_execute create table country ( co_id fixed(4), co_name varchar(50), co_exchange fixed(12, 6), co_currency varchar(18) )

sql_execute create table author ( a_id fixed(10), a_fname varchar(20), a_lname varchar(20), a_mname varchar(20), a_dob date, a_bio varchar(500) )

sql_execute create table customer ( c_id fixed(10), c_uname varchar(20), c_passwd varchar(20), c_fname varchar(15), c_lname varchar(15), c_addr_id fixed(10), c_phone varchar(16), c_email varchar(50), c_since date, c_last_visit date, c_login timestamp, c_expiration timestamp, c_discount fixed(5, 2), c_balance fixed(17, 2), c_ytd_pmt fixed(17, 2), c_birthdate date, c_data varchar(500) )

sql_execute create table orders ( o_id fixed(10), o_c_id fixed(10), o_date timestamp, o_sub_total fixed(17, 2), o_tax fixed(17, 2), o_total fixed(17, 2), o_ship_type varchar(10), o_ship_date timestamp, o_bill_addr_id fixed(10), o_ship_addr_id fixed(10), o_status varchar(15) )

sql_execute create table order_line ( ol_id fixed(3), ol_o_id fixed(10), ol_i_id fixed(10), ol_qty fixed(3), ol_discount fixed(5, 2), ol_comments varchar(100) )

sql_execute create table cc_xacts ( cx_o_id fixed(10), cx_type varchar(10), cx_num fixed(16), cx_name varchar(31), cx_expiry date, cx_auth_id char(15), cx_xact_amt fixed(17, 2), cx_xact_date timestamp, cx_co_id fixed(4) )

sql_execute create table address ( addr_id fixed(10), addr_street1 varchar(40), addr_street2 varchar(40), addr_city varchar(30), addr_state varchar(20), addr_zip varchar(10), addr_co_id fixed(4) )

sql_execute create table shopping_cart ( sc_id fixed(10), sc_c_id fixed(10), sc_date timestamp, sc_sub_total fixed(17, 2), sc_tax fixed(17, 2), sc_ship_cost fixed(17, 2), sc_total fixed(17, 2), sc_c_fname varchar(15), sc_c_lname varchar(15), sc_c_discount fixed(5, 2) )

sql_execute create table shopping_cart_line ( scl_sc_id fixed(10), scl_i_id fixed(10), scl_qty fixed(3), scl_cost fixed(17, 2), scl_srp fixed(17, 2), scl_title varchar(60), scl_backing varchar(15) )
