
sql_execute create unique index i_sc_id on shopping_cart (sc_id asc)
sql_execute create unique index i_scl_sc_id_scl_i_id on shopping_cart_line ( scl_sc_id, scl_i_id )

sql_execute create index i_c_uname on customer (c_uname asc)
sql_execute create index i_o_c_id on orders (o_c_id asc)
sql_execute create index i_ol_i_id on order_line (ol_i_id asc)
sql_execute create index i_address_table on address (addr_street1, addr_street2, addr_city, addr_state, addr_zip, addr_co_id)
sql_execute create index i_i_subject on item (i_subject asc)
sql_execute create index i_i_title on item (i_title asc)
sql_execute create index i_i_a_id on item (i_a_id asc)
sql_execute create index i_a_lname on author (a_lname asc)
