alter table item add constraint fk_i_a_id foreign key ( i_a_id ) references author ( a_id );

commit;

alter table customer add constraint fk_c_addr_id foreign key ( c_addr_id ) references address ( addr_id );

commit;

alter table orders add constraint fk_o_c_id foreign key ( o_c_id ) references customer ( c_id );

commit;

alter table orders add constraint fk_o_bill_addr_id foreign key ( o_bill_addr_id ) references address ( addr_id );

commit;

alter table orders add constraint fk_o_ship_addr_id foreign key ( o_ship_addr_id ) references address ( addr_id );

commit;

alter table order_line add constraint fk_line_ol_i_id foreign key ( ol_i_id ) references item ( i_id );

commit;

alter table order_line add constraint fk_line_ol_o_id foreign key ( ol_o_id ) references orders ( o_id );

commit;

alter table cc_xacts add constraint fk_cx_o_id foreign key ( cx_o_id ) references orders ( o_id );

commit;

alter table cc_xacts add constraint fk_cx_co_id foreign key ( cx_co_id ) references country ( co_id );

commit;

alter table address add constraint fk_addr_co_id foreign key ( addr_co_id ) references country ( co_id );

commit;
