sql_execute alter table item add foreign key fk_i_a_id ( i_a_id ) references author ( a_id )

sql_execute alter table customer add foreign key fk_c_addr_id ( c_addr_id )  references address ( addr_id )

sql_execute alter table orders add foreign key fk_o_c_id ( o_c_id ) references customer ( c_id )
sql_execute alter table orders add foreign key fk_o_bill_addr_id ( o_bill_addr_id ) references address ( addr_id )
sql_execute alter table orders add foreign key fk_o_ship_addr_id ( o_ship_addr_id ) references address ( addr_id )

sql_execute alter table order_line add foreign key fk_line_ol_i_id ( ol_i_id ) references item ( i_id )
sql_execute alter table order_line add foreign key fk_line_ol_o_id ( ol_o_id ) references orders ( o_id )

sql_execute alter table cc_xacts add foreign key fk_cx_o_id ( cx_o_id ) references orders ( o_id )
sql_execute alter table cc_xacts add foreign key fk_cx_co_id ( cx_co_id ) references country ( co_id )

sql_execute alter table address add foreign key fk_addr_co_id ( addr_co_id ) references country ( co_id )
