create index i_i_subject on item (i_subject);
create index i_i_a_id on item (i_a_id);
create index i_address_table on address (addr_street1, addr_street2, addr_city, addr_state, addr_zip, addr_co_id);
create index i_c_uname on customer (c_uname);
create index i_o_c_id on orders (o_c_id);
create index i_i_title on item (i_title);
create index i_a_lname on author (a_lname);
