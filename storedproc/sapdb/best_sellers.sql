/*
/*
/* This file is released under the terms of the Artistic License.  Please see
/* the file LICENSE, included in this package, for details.
/*
/* Copyright (C) 2002 Mark Wong & Jenny Zhang &
/*                    Open Source Development Lab, Inc.
/*
/*/
/* Clause 2.13.3 */
/* Non-complient, exactly the same as New Products. */
/* This stored procedure is too big to for repmcli to handle.  Use the
 * odbc_test tool. */
CREATE DBPROC best_sellers(IN i_subject VARCHAR(60), IN i_id FIXED(10),
OUT i_related1 FIXED(10), OUT i_related2 FIXED(10), OUT i_related3 FIXED(10),
OUT i_related4 FIXED(10), OUT i_related5 FIXED(10),
OUT i_thumbnail1 FIXED(10), OUT i_thumbnail2 FIXED(10),
OUT i_thumbnail3 FIXED(10), OUT i_thumbnail4 FIXED(10),
OUT i_thumbnail5 FIXED(10),
OUT items FIXED(2),
OUT i_id1 FIXED(10), OUT i_title1 VARCHAR(60),
OUT a_fname1 VARCHAR(20), OUT a_lname1 VARCHAR(20),
OUT i_id2 FIXED(10), OUT i_title2 VARCHAR(60),
OUT a_fname2 VARCHAR(20), OUT a_lname2 VARCHAR(20),
OUT i_id3 FIXED(10), OUT i_title3 VARCHAR(60),
OUT a_fname3 VARCHAR(20), OUT a_lname3 VARCHAR(20),
OUT i_id4 FIXED(10), OUT i_title4 VARCHAR(60),
OUT a_fname4 VARCHAR(20), OUT a_lname4 VARCHAR(20),
OUT i_id5 FIXED(10), OUT i_title5 VARCHAR(60),
OUT a_fname5 VARCHAR(20), OUT a_lname5 VARCHAR(20),
OUT i_id6 FIXED(10), OUT i_title6 VARCHAR(60),
OUT a_fname6 VARCHAR(20), OUT a_lname6 VARCHAR(20),
OUT i_id7 FIXED(10), OUT i_title7 VARCHAR(60),
OUT a_fname7 VARCHAR(20), OUT a_lname7 VARCHAR(20),
OUT i_id8 FIXED(10), OUT i_title8 VARCHAR(60),
OUT a_fname8 VARCHAR(20), OUT a_lname8 VARCHAR(20),
OUT i_id9 FIXED(10), OUT i_title9 VARCHAR(60),
OUT a_fname9 VARCHAR(20), OUT a_lname9 VARCHAR(20),
OUT i_id10 FIXED(10), OUT i_title10 VARCHAR(60),
OUT a_fname10 VARCHAR(20), OUT a_lname10 VARCHAR(20),
OUT i_id11 FIXED(10), OUT i_title11 VARCHAR(60),
OUT a_fname11 VARCHAR(20), OUT a_lname11 VARCHAR(20),
OUT i_id12 FIXED(10), OUT i_title12 VARCHAR(60),
OUT a_fname12 VARCHAR(20), OUT a_lname12 VARCHAR(20),
OUT i_id13 FIXED(10), OUT i_title13 VARCHAR(60),
OUT a_fname13 VARCHAR(20), OUT a_lname13 VARCHAR(20),
OUT i_id14 FIXED(10), OUT i_title14 VARCHAR(60),
OUT a_fname14 VARCHAR(20), OUT a_lname14 VARCHAR(20),
OUT i_id15 FIXED(10), OUT i_title15 VARCHAR(60),
OUT a_fname15 VARCHAR(20), OUT a_lname15 VARCHAR(20),
OUT i_id16 FIXED(10), OUT i_title16 VARCHAR(60),
OUT a_fname16 VARCHAR(20), OUT a_lname16 VARCHAR(20),
OUT i_id17 FIXED(10), OUT i_title17 VARCHAR(60),
OUT a_fname17 VARCHAR(20), OUT a_lname17 VARCHAR(20),
OUT i_id18 FIXED(10), OUT i_title18 VARCHAR(60),
OUT a_fname18 VARCHAR(20), OUT a_lname18 VARCHAR(20),
OUT i_id19 FIXED(10), OUT i_title19 VARCHAR(60),
OUT a_fname19 VARCHAR(20), OUT a_lname19 VARCHAR(20),
OUT i_id20 FIXED(10), OUT i_title20 VARCHAR(60),
OUT a_fname20 VARCHAR(20), OUT a_lname20 VARCHAR(20),
OUT i_id21 FIXED(10), OUT i_title21 VARCHAR(60),
OUT a_fname21 VARCHAR(20), OUT a_lname21 VARCHAR(20),
OUT i_id22 FIXED(10), OUT i_title22 VARCHAR(60),
OUT a_fname22 VARCHAR(20), OUT a_lname22 VARCHAR(20),
OUT i_id23 FIXED(10), OUT i_title23 VARCHAR(60),
OUT a_fname23 VARCHAR(20), OUT a_lname23 VARCHAR(20),
OUT i_id24 FIXED(10), OUT i_title24 VARCHAR(60),
OUT a_fname24 VARCHAR(20), OUT a_lname24 VARCHAR(20),
OUT i_id25 FIXED(10), OUT i_title25 VARCHAR(60),
OUT a_fname25 VARCHAR(20), OUT a_lname25 VARCHAR(20),
OUT i_id26 FIXED(10), OUT i_title26 VARCHAR(60),
OUT a_fname26 VARCHAR(20), OUT a_lname26 VARCHAR(20),
OUT i_id27 FIXED(10), OUT i_title27 VARCHAR(60),
OUT a_fname27 VARCHAR(20), OUT a_lname27 VARCHAR(20),
OUT i_id28 FIXED(10), OUT i_title28 VARCHAR(60),
OUT a_fname28 VARCHAR(20), OUT a_lname28 VARCHAR(20),
OUT i_id29 FIXED(10), OUT i_title29 VARCHAR(60),
OUT a_fname29 VARCHAR(20), OUT a_lname29 VARCHAR(20),
OUT i_id30 FIXED(10), OUT i_title30 VARCHAR(60),
OUT a_fname30 VARCHAR(20), OUT a_lname30 VARCHAR(20),
OUT i_id31 FIXED(10), OUT i_title31 VARCHAR(60),
OUT a_fname31 VARCHAR(20), OUT a_lname31 VARCHAR(20),
OUT i_id32 FIXED(10), OUT i_title32 VARCHAR(60),
OUT a_fname32 VARCHAR(20), OUT a_lname32 VARCHAR(20),
OUT i_id33 FIXED(10), OUT i_title33 VARCHAR(60),
OUT a_fname33 VARCHAR(20), OUT a_lname33 VARCHAR(20),
OUT i_id34 FIXED(10), OUT i_title34 VARCHAR(60),
OUT a_fname34 VARCHAR(20), OUT a_lname34 VARCHAR(20),
OUT i_id35 FIXED(10), OUT i_title35 VARCHAR(60),
OUT a_fname35 VARCHAR(20), OUT a_lname35 VARCHAR(20),
OUT i_id36 FIXED(10), OUT i_title36 VARCHAR(60),
OUT a_fname36 VARCHAR(20), OUT a_lname36 VARCHAR(20),
OUT i_id37 FIXED(10), OUT i_title37 VARCHAR(60),
OUT a_fname37 VARCHAR(20), OUT a_lname37 VARCHAR(20),
OUT i_id38 FIXED(10), OUT i_title38 VARCHAR(60),
OUT a_fname38 VARCHAR(20), OUT a_lname38 VARCHAR(20),
OUT i_id39 FIXED(10), OUT i_title39 VARCHAR(60),
OUT a_fname39 VARCHAR(20), OUT a_lname39 VARCHAR(20),
OUT i_id40 FIXED(10), OUT i_title40 VARCHAR(60),
OUT a_fname40 VARCHAR(20), OUT a_lname40 VARCHAR(20),
OUT i_id41 FIXED(10), OUT i_title41 VARCHAR(60),
OUT a_fname41 VARCHAR(20), OUT a_lname41 VARCHAR(20),
OUT i_id42 FIXED(10), OUT i_title42 VARCHAR(60),
OUT a_fname42 VARCHAR(20), OUT a_lname42 VARCHAR(20),
OUT i_id43 FIXED(10), OUT i_title43 VARCHAR(60),
OUT a_fname43 VARCHAR(20), OUT a_lname43 VARCHAR(20),
OUT i_id44 FIXED(10), OUT i_title44 VARCHAR(60),
OUT a_fname44 VARCHAR(20), OUT a_lname44 VARCHAR(20),
OUT i_id45 FIXED(10), OUT i_title45 VARCHAR(60),
OUT a_fname45 VARCHAR(20), OUT a_lname45 VARCHAR(20),
OUT i_id46 FIXED(10), OUT i_title46 VARCHAR(60),
OUT a_fname46 VARCHAR(20), OUT a_lname46 VARCHAR(20),
OUT i_id47 FIXED(10), OUT i_title47 VARCHAR(60),
OUT a_fname47 VARCHAR(20), OUT a_lname47 VARCHAR(20),
OUT i_id48 FIXED(10), OUT i_title48 VARCHAR(60),
OUT a_fname48 VARCHAR(20), OUT a_lname48 VARCHAR(20),
OUT i_id49 FIXED(10), OUT i_title49 VARCHAR(60),
OUT a_fname49 VARCHAR(20), OUT a_lname49 VARCHAR(20),
OUT i_id50 FIXED(10), OUT i_title50 VARCHAR(60),
OUT a_fname50 VARCHAR(20), OUT a_lname50 VARCHAR(20)) AS
BEGIN
  set items=0;
  CALL initItems(
    :i_id1, :i_title1, :a_lname1, :a_fname1,
    :i_id2, :i_title2, :a_lname2, :a_fname2,
    :i_id3, :i_title3, :a_lname3, :a_fname3,
    :i_id4, :i_title4, :a_lname4, :a_fname4,
    :i_id5, :i_title5, :a_lname5, :a_fname5,
    :i_id6, :i_title6, :a_lname6, :a_fname6,
    :i_id7, :i_title7, :a_lname7, :a_fname7,
    :i_id8, :i_title8, :a_lname8, :a_fname8,
    :i_id9, :i_title9, :a_lname9, :a_fname9,
    :i_id10, :i_title10, :a_lname10, :a_fname10,
    :i_id11, :i_title11, :a_lname11, :a_fname11,
    :i_id12, :i_title12, :a_lname12, :a_fname12,
    :i_id13, :i_title13, :a_lname13, :a_fname13,
    :i_id14, :i_title14, :a_lname14, :a_fname14,
    :i_id15, :i_title15, :a_lname15, :a_fname15,
    :i_id16, :i_title16, :a_lname16, :a_fname16,
    :i_id17, :i_title17, :a_lname17, :a_fname17,
    :i_id18, :i_title18, :a_lname18, :a_fname18,
    :i_id19, :i_title19, :a_lname19, :a_fname19,
    :i_id20, :i_title20, :a_lname20, :a_fname20,
    :i_id21, :i_title21, :a_lname21, :a_fname21,
    :i_id22, :i_title22, :a_lname22, :a_fname22,
    :i_id23, :i_title23, :a_lname23, :a_fname23,
    :i_id24, :i_title24, :a_lname24, :a_fname24,
    :i_id25, :i_title25, :a_lname25, :a_fname25,
    :i_id26, :i_title26, :a_lname26, :a_fname26,
    :i_id27, :i_title27, :a_lname27, :a_fname27,
    :i_id28, :i_title28, :a_lname28, :a_fname28,
    :i_id29, :i_title29, :a_lname29, :a_fname29,
    :i_id30, :i_title30, :a_lname30, :a_fname30,
    :i_id31, :i_title31, :a_lname31, :a_fname31,
    :i_id32, :i_title32, :a_lname32, :a_fname32,
    :i_id33, :i_title33, :a_lname33, :a_fname33,
    :i_id34, :i_title34, :a_lname34, :a_fname34,
    :i_id35, :i_title35, :a_lname35, :a_fname35,
    :i_id36, :i_title36, :a_lname36, :a_fname36,
    :i_id37, :i_title37, :a_lname37, :a_fname37,
    :i_id38, :i_title38, :a_lname38, :a_fname38,
    :i_id39, :i_title39, :a_lname39, :a_fname39,
    :i_id40, :i_title40, :a_lname40, :a_fname40,
    :i_id41, :i_title41, :a_lname41, :a_fname41,
    :i_id42, :i_title42, :a_lname42, :a_fname42,
    :i_id43, :i_title43, :a_lname43, :a_fname43,
    :i_id44, :i_title44, :a_lname44, :a_fname44,
    :i_id45, :i_title45, :a_lname45, :a_fname45,
    :i_id46, :i_title46, :a_lname46, :a_fname46,
    :i_id47, :i_title47, :a_lname47, :a_fname47,
    :i_id48, :i_title48, :a_lname48, :a_fname48,
    :i_id49, :i_title49, :a_lname49, :a_fname49,
    :i_id50, :i_title50, :a_lname50, :a_fname50);
  CALL GetPromoImages(:i_id,
                      :i_related1, :i_thumbnail1,
                      :i_related2, :i_thumbnail2,
                      :i_related3, :i_thumbnail3,
                      :i_related4, :i_thumbnail4,
                      :i_related5, :i_thumbnail5);
  declare recent_order cursor for 
    select ol_i_id, ol_qty from dbt.order_line, dbt.orders
    where ol_o_id=o_id
    order by o_date desc;
  declare popular_order cursor for
    select ol_i_id, sum(ol_qty) as sum_qty
    from dbt.recent_order
    where rowno<3333
    group by ol_i_id
    order by sum_qty;
  select i_id, i_title, a_lname, a_fname
    from dbt.item, dbt.author, dbt.popular_order
    where i_subject=:i_subject and i_id=ol_i_id and a_id=i_a_id;
  if $rc=0 THEN fetch into :i_id1, :i_title1, :a_lname1, :a_fname1;
  if $rc=0 THEN begin
     set items=items+1;
     fetch into :i_id2, :i_title2, :a_lname2, :a_fname2;
  end;
  if $rc=0 THEN begin
     set items=items+1;
     fetch into :i_id3, :i_title3, :a_lname3, :a_fname3;
  end;
  if $rc=0 THEN begin
     set items=items+1;
     fetch into :i_id4, :i_title4, :a_lname4, :a_fname4;
  end;
  if $rc=0 THEN begin
     set items=items+1;
     fetch into :i_id5, :i_title5, :a_lname5, :a_fname5;
  end;
  if $rc=0 THEN begin
     set items=items+1;
     fetch into :i_id6, :i_title6, :a_lname6, :a_fname6;
  end;
  if $rc=0 THEN begin
     set items=items+1;
     fetch into :i_id7, :i_title7, :a_lname7, :a_fname7;
  end;
  if $rc=0 THEN begin
     set items=items+1;
     fetch into :i_id8, :i_title8, :a_lname8, :a_fname8;
  end;
  if $rc=0 THEN begin
     set items=items+1;
     fetch into :i_id9, :i_title9, :a_lname9, :a_fname9;
  end;
  if $rc=0 THEN begin
     set items=items+1;
     fetch into :i_id10, :i_title10, :a_lname10, :a_fname10;
  end;
  if $rc=0 THEN begin
     set items=items+1;
     fetch into :i_id11, :i_title11, :a_lname11, :a_fname11;
  end;
  if $rc=0 THEN begin
     set items=items+1;
     fetch into :i_id12, :i_title12, :a_lname12, :a_fname12;
  end;
  if $rc=0 THEN begin
     set items=items+1;
     fetch into :i_id13, :i_title13, :a_lname13, :a_fname13;
  end;
  if $rc=0 THEN begin
     set items=items+1;
     fetch into :i_id14, :i_title14, :a_lname14, :a_fname14;
  end;
  if $rc=0 THEN begin
     set items=items+1;
     fetch into :i_id15, :i_title15, :a_lname15, :a_fname15;
  end;
  if $rc=0 THEN begin
     set items=items+1;
     fetch into :i_id16, :i_title16, :a_lname16, :a_fname16;
  end;
  if $rc=0 THEN begin
     set items=items+1;
     fetch into :i_id17, :i_title17, :a_lname17, :a_fname17;
  end;
  if $rc=0 THEN begin
     set items=items+1;
     fetch into :i_id18, :i_title18, :a_lname18, :a_fname18;
  end;
  if $rc=0 THEN begin
     set items=items+1;
     fetch into :i_id19, :i_title19, :a_lname19, :a_fname19;
  end;
  if $rc=0 THEN begin
     set items=items+1;
     fetch into :i_id20, :i_title20, :a_lname20, :a_fname20;
  end;
  if $rc=0 THEN begin
     set items=items+1;
     fetch into :i_id21, :i_title21, :a_lname21, :a_fname21;
  end;
  if $rc=0 THEN begin
     set items=items+1;
     fetch into :i_id22, :i_title22, :a_lname22, :a_fname22;
  end;
  if $rc=0 THEN begin
     set items=items+1;
     fetch into :i_id23, :i_title23, :a_lname23, :a_fname23;
  end;
  if $rc=0 THEN begin
     set items=items+1;
     fetch into :i_id24, :i_title24, :a_lname24, :a_fname24;
  end;
  if $rc=0 THEN begin
     set items=items+1;
     fetch into :i_id25, :i_title25, :a_lname25, :a_fname25;
  end;
  if $rc=0 THEN begin
     set items=items+1;
     fetch into :i_id26, :i_title26, :a_lname26, :a_fname26;
  end;
  if $rc=0 THEN begin
     set items=items+1;
     fetch into :i_id27, :i_title27, :a_lname27, :a_fname27;
  end;
  if $rc=0 THEN begin
     set items=items+1;
     fetch into :i_id28, :i_title28, :a_lname28, :a_fname28;
  end;
  if $rc=0 THEN begin
     set items=items+1;
     fetch into :i_id29, :i_title29, :a_lname29, :a_fname29;
  end;
  if $rc=0 THEN begin
     set items=items+1;
     fetch into :i_id30, :i_title30, :a_lname30, :a_fname30;
  end;
  if $rc=0 THEN begin
     set items=items+1;
     fetch into :i_id31, :i_title31, :a_lname31, :a_fname31;
  end;
  if $rc=0 THEN begin
     set items=items+1;
     fetch into :i_id32, :i_title32, :a_lname32, :a_fname32;
  end;
  if $rc=0 THEN begin
     set items=items+1;
     fetch into :i_id33, :i_title33, :a_lname33, :a_fname33;
  end;
  if $rc=0 THEN begin
     set items=items+1;
     fetch into :i_id34, :i_title34, :a_lname34, :a_fname34;
  end;
  if $rc=0 THEN begin
     set items=items+1;
     fetch into :i_id35, :i_title35, :a_lname35, :a_fname35;
  end;
  if $rc=0 THEN begin
     set items=items+1;
     fetch into :i_id36, :i_title36, :a_lname36, :a_fname36;
  end;
  if $rc=0 THEN begin
     set items=items+1;
     fetch into :i_id37, :i_title37, :a_lname37, :a_fname37;
  end;
  if $rc=0 THEN begin
     set items=items+1;
     fetch into :i_id38, :i_title38, :a_lname38, :a_fname38;
  end;
  if $rc=0 THEN begin
     set items=items+1;
     fetch into :i_id39, :i_title39, :a_lname39, :a_fname39;
  end;
  if $rc=0 THEN begin
     set items=items+1;
     fetch into :i_id40, :i_title40, :a_lname40, :a_fname40;
  end;
  if $rc=0 THEN begin
     set items=items+1;
     fetch into :i_id41, :i_title41, :a_lname41, :a_fname41;
  end;
  if $rc=0 THEN begin
     set items=items+1;
     fetch into :i_id42, :i_title42, :a_lname42, :a_fname42;
  end;
  if $rc=0 THEN begin
     set items=items+1;
     fetch into :i_id43, :i_title43, :a_lname43, :a_fname43;
  end;
  if $rc=0 THEN begin
     set items=items+1;
     fetch into :i_id44, :i_title44, :a_lname44, :a_fname44;
  end;
  if $rc=0 THEN begin
     set items=items+1;
     fetch into :i_id45, :i_title45, :a_lname45, :a_fname45;
  end;
  if $rc=0 THEN begin
     set items=items+1;
     fetch into :i_id46, :i_title46, :a_lname46, :a_fname46;
  end;
  if $rc=0 THEN begin
     set items=items+1;
     fetch into :i_id47, :i_title47, :a_lname47, :a_fname47;
  end;
  if $rc=0 THEN begin
     set items=items+1;
     fetch into :i_id48, :i_title48, :a_lname48, :a_fname48;
  end;
  if $rc=0 THEN begin
     set items=items+1;
     fetch into :i_id49, :i_title49, :a_lname49, :a_fname49;
  end;
  if $rc=0 THEN begin
     set items=items+1;
     fetch into :i_id50, :i_title50, :a_lname50, :a_fname50;
  end;
END;
;
