/*
/*
/* This file is released under the terms of the Artistic License.  Please see
/* the file LICENSE, included in this package, for details.
/*
/* Copyright (C) 2002 Mark Wong & Jenny Zhang &
/*                    Open Source Development Lab, Inc.
/*
/*/
/* Clause 2.11.3 */
/* Not quite sure if the query in 100% compliant. */
CREATE DBPROC search_results_title(IN i_title VARCHAR(60), IN i_id FIXED(10),
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
  SET i_id1 = 0;
  SET i_title1 = '';
  SET a_fname1 = '';
  SET a_lname1 = '';
  SET i_id2 = 0;
  SET i_title2 = '';
  SET a_fname2 = '';
  SET a_lname2 = '';
  SET i_id3 = 0;
  SET i_title3 = '';
  SET a_fname3 = '';
  SET a_lname3 = '';
  SET i_id4 = 0;
  SET i_title4 = '';
  SET a_fname4 = '';
  SET a_lname4 = '';
  SET i_id5 = 0;
  SET i_title5 = '';
  SET a_fname5 = '';
  SET a_lname5 = '';
  SET i_id6 = 0;
  SET i_title6 = '';
  SET a_fname6 = '';
  SET a_lname6 = '';
  SET i_id7 = 0;
  SET i_title7 = '';
  SET a_fname7 = '';
  SET a_lname7 = '';
  SET i_id8 = 0;
  SET i_title8 = '';
  SET a_fname8 = '';
  SET a_lname8 = '';
  SET i_id9 = 0;
  SET i_title9 = '';
  SET a_fname9 = '';
  SET a_lname9 = '';
  SET i_id10 = 0;
  SET i_title10 = '';
  SET a_fname10 = '';
  SET a_lname10 = '';
  SET i_id11 = 0;
  SET i_title11 = '';
  SET a_fname11 = '';
  SET a_lname11 = '';
  SET i_id12 = 0;
  SET i_title12 = '';
  SET a_fname12 = '';
  SET a_lname12 = '';
  SET i_id13 = 0;
  SET i_title13 = '';
  SET a_fname13 = '';
  SET a_lname13 = '';
  SET i_id14 = 0;
  SET i_title14 = '';
  SET a_fname14 = '';
  SET a_lname14 = '';
  SET i_id15 = 0;
  SET i_title15 = '';
  SET a_fname15 = '';
  SET a_lname15 = '';
  SET i_id16 = 0;
  SET i_title16 = '';
  SET a_fname16 = '';
  SET a_lname16 = '';
  SET i_id17 = 0;
  SET i_title17 = '';
  SET a_fname17 = '';
  SET a_lname17 = '';
  SET i_id18 = 0;
  SET i_title18 = '';
  SET a_fname18 = '';
  SET a_lname18 = '';
  SET i_id19 = 0;
  SET i_title19 = '';
  SET a_fname19 = '';
  SET a_lname19 = '';
  SET i_id20 = 0;
  SET i_title20 = '';
  SET a_fname20 = '';
  SET a_lname20 = '';
  SET i_id21 = 0;
  SET i_title21 = '';
  SET a_fname21 = '';
  SET a_lname21 = '';
  SET i_id22 = 0;
  SET i_title22 = '';
  SET a_fname22 = '';
  SET a_lname22 = '';
  SET i_id23 = 0;
  SET i_title23 = '';
  SET a_fname23 = '';
  SET a_lname23 = '';
  SET i_id24 = 0;
  SET i_title24 = '';
  SET a_fname24 = '';
  SET a_lname24 = '';
  SET i_id25 = 0;
  SET i_title25 = '';
  SET a_fname25 = '';
  SET a_lname25 = '';
  SET i_id26 = 0;
  SET i_title26 = '';
  SET a_fname26 = '';
  SET a_lname26 = '';
  SET i_id27 = 0;
  SET i_title27 = '';
  SET a_fname27 = '';
  SET a_lname27 = '';
  SET i_id28 = 0;
  SET i_title28 = '';
  SET a_fname28 = '';
  SET a_lname28 = '';
  SET i_id29 = 0;
  SET i_title29 = '';
  SET a_fname29 = '';
  SET a_lname29 = '';
  SET i_id30 = 0;
  SET i_title30 = '';
  SET a_fname30 = '';
  SET a_lname30 = '';
  SET i_id31 = 0;
  SET i_title31 = '';
  SET a_fname31 = '';
  SET a_lname31 = '';
  SET i_id32 = 0;
  SET i_title32 = '';
  SET a_fname32 = '';
  SET a_lname32 = '';
  SET i_id33 = 0;
  SET i_title33 = '';
  SET a_fname33 = '';
  SET a_lname33 = '';
  SET i_id34 = 0;
  SET i_title34 = '';
  SET a_fname34 = '';
  SET a_lname34 = '';
  SET i_id35 = 0;
  SET i_title35 = '';
  SET a_fname35 = '';
  SET a_lname35 = '';
  SET i_id36 = 0;
  SET i_title36 = '';
  SET a_fname36 = '';
  SET a_lname36 = '';
  SET i_id37 = 0;
  SET i_title37 = '';
  SET a_fname37 = '';
  SET a_lname37 = '';
  SET i_id38 = 0;
  SET i_title38 = '';
  SET a_fname38 = '';
  SET a_lname38 = '';
  SET i_id39 = 0;
  SET i_title39 = '';
  SET a_fname39 = '';
  SET a_lname39 = '';
  SET i_id40 = 0;
  SET i_title40 = '';
  SET a_fname40 = '';
  SET a_lname40 = '';
  SET i_id41 = 0;
  SET i_title41 = '';
  SET a_fname41 = '';
  SET a_lname41 = '';
  SET i_id42 = 0;
  SET i_title42 = '';
  SET a_fname42 = '';
  SET a_lname42 = '';
  SET i_id43 = 0;
  SET i_title43 = '';
  SET a_fname43 = '';
  SET a_lname43 = '';
  SET i_id44 = 0;
  SET i_title44 = '';
  SET a_fname44 = '';
  SET a_lname44 = '';
  SET i_id45 = 0;
  SET i_title45 = '';
  SET a_fname45 = '';
  SET a_lname45 = '';
  SET i_id46 = 0;
  SET i_title46 = '';
  SET a_fname46 = '';
  SET a_lname46 = '';
  SET i_id47 = 0;
  SET i_title47 = '';
  SET a_fname47 = '';
  SET a_lname47 = '';
  SET i_id48 = 0;
  SET i_title48 = '';
  SET a_fname48 = '';
  SET a_lname48 = '';
  SET i_id49 = 0;
  SET i_title49 = '';
  SET a_fname49 = '';
  SET a_lname49 = '';
  SET i_id50 = 0;
  SET i_title50 = '';
  SET a_fname50 = '';
  SET a_lname50 = '';
  i_title='%'||i_title||'%';
  CALL GetPromoImages(:i_id,
                      :i_related1, :i_thumbnail1,
                      :i_related2, :i_thumbnail2,
                      :i_related3, :i_thumbnail3,
                      :i_related4, :i_thumbnail4,
                      :i_related5, :i_thumbnail5);
  SELECT i_id, i_title, a_fname, a_lname
  FROM dbt.item, dbt.author
  WHERE i_title LIKE :i_title
    AND i_a_id = a_id
  ORDER BY i_title ASC;
  SET items = 0;
  IF $rc = 0 THEN
    BEGIN
      FETCH INTO :i_id1, :i_title1, :a_fname1, :a_lname1;
    END;
  IF $rc = 0 THEN
    BEGIN
      FETCH INTO :i_id2, :i_title2, :a_fname2, :a_lname2;
      SET items = items + 1;
    END;
  IF $rc = 0 THEN
    BEGIN
      FETCH INTO :i_id3, :i_title3, :a_fname3, :a_lname3;
      SET items = items + 1;
    END;
  IF $rc = 0 THEN
    BEGIN
      FETCH INTO :i_id4, :i_title4, :a_fname4, :a_lname4;
      SET items = items + 1;
    END;
  IF $rc = 0 THEN
    BEGIN
      FETCH INTO :i_id5, :i_title5, :a_fname5, :a_lname5;
      SET items = items + 1;
    END;
  IF $rc = 0 THEN
    BEGIN
      FETCH INTO :i_id6, :i_title6, :a_fname6, :a_lname6;
      SET items = items + 1;
    END;
  IF $rc = 0 THEN
    BEGIN
      FETCH INTO :i_id7, :i_title7, :a_fname7, :a_lname7;
      SET items = items + 1;
    END;
  IF $rc = 0 THEN
    BEGIN
      FETCH INTO :i_id8, :i_title8, :a_fname8, :a_lname8;
      SET items = items + 1;
    END;
  IF $rc = 0 THEN
    BEGIN
      FETCH INTO :i_id9, :i_title9, :a_fname9, :a_lname9;
      SET items = items + 1;
    END;
  IF $rc = 0 THEN
    BEGIN
      FETCH INTO :i_id10, :i_title10, :a_fname10, :a_lname10;
      SET items = items + 1;
    END;
  IF $rc = 0 THEN
    BEGIN
      FETCH INTO :i_id11, :i_title11, :a_fname11, :a_lname11;
      SET items = items + 1;
    END;
  IF $rc = 0 THEN
    BEGIN
      FETCH INTO :i_id12, :i_title12, :a_fname12, :a_lname12;
      SET items = items + 1;
    END;
  IF $rc = 0 THEN
    BEGIN
      FETCH INTO :i_id13, :i_title13, :a_fname13, :a_lname13;
      SET items = items + 1;
    END;
  IF $rc = 0 THEN
    BEGIN
      FETCH INTO :i_id14, :i_title14, :a_fname14, :a_lname14;
      SET items = items + 1;
    END;
  IF $rc = 0 THEN
    BEGIN
      FETCH INTO :i_id15, :i_title15, :a_fname15, :a_lname15;
      SET items = items + 1;
    END;
  IF $rc = 0 THEN
    BEGIN
      FETCH INTO :i_id16, :i_title16, :a_fname16, :a_lname16;
      SET items = items + 1;
    END;
  IF $rc = 0 THEN
    BEGIN
      FETCH INTO :i_id17, :i_title17, :a_fname17, :a_lname17;
      SET items = items + 1;
    END;
  IF $rc = 0 THEN
    BEGIN
      FETCH INTO :i_id18, :i_title18, :a_fname18, :a_lname18;
      SET items = items + 1;
    END;
  IF $rc = 0 THEN
    BEGIN
      FETCH INTO :i_id19, :i_title19, :a_fname19, :a_lname19;
      SET items = items + 1;
    END;
  IF $rc = 0 THEN
    BEGIN
      FETCH INTO :i_id20, :i_title20, :a_fname20, :a_lname20;
      SET items = items + 1;
    END;
  IF $rc = 0 THEN
    BEGIN
      FETCH INTO :i_id21, :i_title21, :a_fname21, :a_lname21;
      SET items = items + 1;
    END;
  IF $rc = 0 THEN
    BEGIN
      FETCH INTO :i_id22, :i_title22, :a_fname22, :a_lname22;
      SET items = items + 1;
    END;
  IF $rc = 0 THEN
    BEGIN
      FETCH INTO :i_id23, :i_title23, :a_fname23, :a_lname23;
      SET items = items + 1;
    END;
  IF $rc = 0 THEN
    BEGIN
      FETCH INTO :i_id24, :i_title24, :a_fname24, :a_lname24;
      SET items = items + 1;
    END;
  IF $rc = 0 THEN
    BEGIN
      FETCH INTO :i_id25, :i_title25, :a_fname25, :a_lname25;
      SET items = items + 1;
    END;
  IF $rc = 0 THEN
    BEGIN
      FETCH INTO :i_id26, :i_title26, :a_fname26, :a_lname26;
      SET items = items + 1;
    END;
  IF $rc = 0 THEN
    BEGIN
      FETCH INTO :i_id27, :i_title27, :a_fname27, :a_lname27;
      SET items = items + 1;
    END;
  IF $rc = 0 THEN
    BEGIN
      FETCH INTO :i_id28, :i_title28, :a_fname28, :a_lname28;
      SET items = items + 1;
    END;
  IF $rc = 0 THEN
    BEGIN
      FETCH INTO :i_id29, :i_title29, :a_fname29, :a_lname29;
      SET items = items + 1;
    END;
  IF $rc = 0 THEN
    BEGIN
      FETCH INTO :i_id30, :i_title30, :a_fname30, :a_lname30;
      SET items = items + 1;
    END;
  IF $rc = 0 THEN
    BEGIN
      FETCH INTO :i_id31, :i_title31, :a_fname31, :a_lname31;
      SET items = items + 1;
    END;
  IF $rc = 0 THEN
    BEGIN
      FETCH INTO :i_id32, :i_title32, :a_fname32, :a_lname32;
      SET items = items + 1;
    END;
  IF $rc = 0 THEN
    BEGIN
      FETCH INTO :i_id33, :i_title33, :a_fname33, :a_lname33;
      SET items = items + 1;
    END;
  IF $rc = 0 THEN
    BEGIN
      FETCH INTO :i_id34, :i_title34, :a_fname34, :a_lname34;
      SET items = items + 1;
    END;
  IF $rc = 0 THEN
    BEGIN
      FETCH INTO :i_id35, :i_title35, :a_fname35, :a_lname35;
      SET items = items + 1;
    END;
  IF $rc = 0 THEN
    BEGIN
      FETCH INTO :i_id36, :i_title36, :a_fname36, :a_lname36;
      SET items = items + 1;
    END;
  IF $rc = 0 THEN
    BEGIN
      FETCH INTO :i_id37, :i_title37, :a_fname37, :a_lname37;
      SET items = items + 1;
    END;
  IF $rc = 0 THEN
    BEGIN
      FETCH INTO :i_id38, :i_title38, :a_fname38, :a_lname38;
      SET items = items + 1;
    END;
  IF $rc = 0 THEN
    BEGIN
      FETCH INTO :i_id39, :i_title39, :a_fname39, :a_lname39;
      SET items = items + 1;
    END;
  IF $rc = 0 THEN
    BEGIN
      FETCH INTO :i_id40, :i_title40, :a_fname40, :a_lname40;
      SET items = items + 1;
    END;
  IF $rc = 0 THEN
    BEGIN
      FETCH INTO :i_id41, :i_title41, :a_fname41, :a_lname41;
      SET items = items + 1;
    END;
  IF $rc = 0 THEN
    BEGIN
      FETCH INTO :i_id42, :i_title42, :a_fname42, :a_lname42;
      SET items = items + 1;
    END;
  IF $rc = 0 THEN
    BEGIN
      FETCH INTO :i_id43, :i_title43, :a_fname43, :a_lname43;
      SET items = items + 1;
    END;
  IF $rc = 0 THEN
    BEGIN
      FETCH INTO :i_id44, :i_title44, :a_fname44, :a_lname44;
      SET items = items + 1;
    END;
  IF $rc = 0 THEN
    BEGIN
      FETCH INTO :i_id45, :i_title45, :a_fname45, :a_lname45;
      SET items = items + 1;
    END;
  IF $rc = 0 THEN
    BEGIN
      FETCH INTO :i_id46, :i_title46, :a_fname46, :a_lname46;
      SET items = items + 1;
    END;
  IF $rc = 0 THEN
    BEGIN
      FETCH INTO :i_id47, :i_title47, :a_fname47, :a_lname47;
      SET items = items + 1;
    END;
  IF $rc = 0 THEN
    BEGIN
      FETCH INTO :i_id48, :i_title48, :a_fname48, :a_lname48;
      SET items = items + 1;
    END;
  IF $rc = 0 THEN
    BEGIN
      FETCH INTO :i_id49, :i_title49, :a_fname49, :a_lname49;
      SET items = items + 1;
    END;
  IF $rc = 0 THEN
    BEGIN
      FETCH INTO :i_id50, :i_title50, :a_fname50, :a_lname50;
      SET items = items + 1;
    END;
END;
