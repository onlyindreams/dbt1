--
--
-- This file is released under the terms of the Artistic License.  Please see
-- the file LICENSE, included in this package, for details.
--
-- Copyright (C) 2002 Open Source Development Lab, Inc.
-- History:
-- July-2003: Created by Satoshi Nagayasu & Hideyuki Kawashima
--
\set AUTOCOMMIT off
CREATE OR REPLACE FUNCTION search_results_title (
  VARCHAR(60),
  numeric(10)
) RETURNS RECORD AS '
  DECLARE
    _i_title ALIAS FOR $1;
    _i_id ALIAS FOR $2;
    i_related1 numeric(10);
    i_related2 numeric(10);
    i_related3 numeric(10);
    i_related4 numeric(10);
    i_related5 numeric(10);
    i_thumbnail1 numeric(10);
    i_thumbnail2 numeric(10);
    i_thumbnail3 numeric(10);
    i_thumbnail4 numeric(10);
    i_thumbnail5 numeric(10);
    items numeric(2);
    i_id1 numeric(10);
    i_title1 VARCHAR(60);
    a_fname1 VARCHAR(20);
    a_lname1 VARCHAR(20);
    i_id2 numeric(10);
    i_title2 VARCHAR(60);
    a_fname2 VARCHAR(20);
    a_lname2 VARCHAR(20);
    i_id3 numeric(10);
    i_title3 VARCHAR(60);
    a_fname3 VARCHAR(20);
    a_lname3 VARCHAR(20);
    i_id4 numeric(10);
    i_title4 VARCHAR(60);
    a_fname4 VARCHAR(20);
    a_lname4 VARCHAR(20);
    i_id5 numeric(10);
    i_title5 VARCHAR(60);
    a_fname5 VARCHAR(20);
    a_lname5 VARCHAR(20);
    i_id6 numeric(10);
    i_title6 VARCHAR(60);
    a_fname6 VARCHAR(20);
    a_lname6 VARCHAR(20);
    i_id7 numeric(10);
    i_title7 VARCHAR(60);
    a_fname7 VARCHAR(20);
    a_lname7 VARCHAR(20);
    i_id8 numeric(10);
    i_title8 VARCHAR(60);
    a_fname8 VARCHAR(20);
    a_lname8 VARCHAR(20);
    i_id9 numeric(10);
    i_title9 VARCHAR(60);
    a_fname9 VARCHAR(20);
    a_lname9 VARCHAR(20);
    i_id10 numeric(10);
    i_title10 VARCHAR(60);
    a_fname10 VARCHAR(20);
    a_lname10 VARCHAR(20);
    i_id11 numeric(10);
    i_title11 VARCHAR(60);
    a_fname11 VARCHAR(20);
    a_lname11 VARCHAR(20);
    i_id12 numeric(10);
    i_title12 VARCHAR(60);
    a_fname12 VARCHAR(20);
    a_lname12 VARCHAR(20);
    i_id13 numeric(10);
    i_title13 VARCHAR(60);
    a_fname13 VARCHAR(20);
    a_lname13 VARCHAR(20);
    i_id14 numeric(10);
    i_title14 VARCHAR(60);
    a_fname14 VARCHAR(20);
    a_lname14 VARCHAR(20);
    i_id15 numeric(10);
    i_title15 VARCHAR(60);
    a_fname15 VARCHAR(20);
    a_lname15 VARCHAR(20);
    i_id16 numeric(10);
    i_title16 VARCHAR(60);
    a_fname16 VARCHAR(20);
    a_lname16 VARCHAR(20);
    i_id17 numeric(10);
    i_title17 VARCHAR(60);
    a_fname17 VARCHAR(20);
    a_lname17 VARCHAR(20);
    i_id18 numeric(10);
    i_title18 VARCHAR(60);
    a_fname18 VARCHAR(20);
    a_lname18 VARCHAR(20);
    i_id19 numeric(10);
    i_title19 VARCHAR(60);
    a_fname19 VARCHAR(20);
    a_lname19 VARCHAR(20);
    i_id20 numeric(10);
    i_title20 VARCHAR(60);
    a_fname20 VARCHAR(20);
    a_lname20 VARCHAR(20);
    i_id21 numeric(10);
    i_title21 VARCHAR(60);
    a_fname21 VARCHAR(20);
    a_lname21 VARCHAR(20);
    i_id22 numeric(10);
    i_title22 VARCHAR(60);
    a_fname22 VARCHAR(20);
    a_lname22 VARCHAR(20);
    i_id23 numeric(10);
    i_title23 VARCHAR(60);
    a_fname23 VARCHAR(20);
    a_lname23 VARCHAR(20);
    i_id24 numeric(10);
    i_title24 VARCHAR(60);
    a_fname24 VARCHAR(20);
    a_lname24 VARCHAR(20);
    i_id25 numeric(10);
    i_title25 VARCHAR(60);
    a_fname25 VARCHAR(20);
    a_lname25 VARCHAR(20);
    i_id26 numeric(10);
    i_title26 VARCHAR(60);
    a_fname26 VARCHAR(20);
    a_lname26 VARCHAR(20);
    i_id27 numeric(10);
    i_title27 VARCHAR(60);
    a_fname27 VARCHAR(20);
    a_lname27 VARCHAR(20);
    i_id28 numeric(10);
    i_title28 VARCHAR(60);
    a_fname28 VARCHAR(20);
    a_lname28 VARCHAR(20);
    i_id29 numeric(10);
    i_title29 VARCHAR(60);
    a_fname29 VARCHAR(20);
    a_lname29 VARCHAR(20);
    i_id30 numeric(10);
    i_title30 VARCHAR(60);
    a_fname30 VARCHAR(20);
    a_lname30 VARCHAR(20);
    i_id31 numeric(10);
    i_title31 VARCHAR(60);
    a_fname31 VARCHAR(20);
    a_lname31 VARCHAR(20);
    i_id32 numeric(10);
    i_title32 VARCHAR(60);
    a_fname32 VARCHAR(20);
    a_lname32 VARCHAR(20);
    i_id33 numeric(10);
    i_title33 VARCHAR(60);
    a_fname33 VARCHAR(20);
    a_lname33 VARCHAR(20);
    i_id34 numeric(10);
    i_title34 VARCHAR(60);
    a_fname34 VARCHAR(20);
    a_lname34 VARCHAR(20);
    i_id35 numeric(10);
    i_title35 VARCHAR(60);
    a_fname35 VARCHAR(20);
    a_lname35 VARCHAR(20);
    i_id36 numeric(10);
    i_title36 VARCHAR(60);
    a_fname36 VARCHAR(20);
    a_lname36 VARCHAR(20);
    i_id37 numeric(10);
    i_title37 VARCHAR(60);
    a_fname37 VARCHAR(20);
    a_lname37 VARCHAR(20);
    i_id38 numeric(10);
    i_title38 VARCHAR(60);
    a_fname38 VARCHAR(20);
    a_lname38 VARCHAR(20);
    i_id39 numeric(10);
    i_title39 VARCHAR(60);
    a_fname39 VARCHAR(20);
    a_lname39 VARCHAR(20);
    i_id40 numeric(10);
    i_title40 VARCHAR(60);
    a_fname40 VARCHAR(20);
    a_lname40 VARCHAR(20);
    i_id41 numeric(10);
    i_title41 VARCHAR(60);
    a_fname41 VARCHAR(20);
    a_lname41 VARCHAR(20);
    i_id42 numeric(10);
    i_title42 VARCHAR(60);
    a_fname42 VARCHAR(20);
    a_lname42 VARCHAR(20);
    i_id43 numeric(10);
    i_title43 VARCHAR(60);
    a_fname43 VARCHAR(20);
    a_lname43 VARCHAR(20);
    i_id44 numeric(10);
    i_title44 VARCHAR(60);
    a_fname44 VARCHAR(20);
    a_lname44 VARCHAR(20);
    i_id45 numeric(10);
    i_title45 VARCHAR(60);
    a_fname45 VARCHAR(20);
    a_lname45 VARCHAR(20);
    i_id46 numeric(10);
    i_title46 VARCHAR(60);
    a_fname46 VARCHAR(20);
    a_lname46 VARCHAR(20);
    i_id47 numeric(10);
    i_title47 VARCHAR(60);
    a_fname47 VARCHAR(20);
    a_lname47 VARCHAR(20);
    i_id48 numeric(10);
    i_title48 VARCHAR(60);
    a_fname48 VARCHAR(20);
    a_lname48 VARCHAR(20);
    i_id49 numeric(10);
    i_title49 VARCHAR(60);
    a_fname49 VARCHAR(20);
    a_lname49 VARCHAR(20);
    i_id50 numeric(10);
    i_title50 VARCHAR(60);
    a_fname50 VARCHAR(20);
    a_lname50 VARCHAR(20);
    refcur REFCURSOR;
    rec RECORD;
  BEGIN
    SELECT * 
    INTO i_related1, i_thumbnail1,
         i_related2, i_thumbnail2,
         i_related3, i_thumbnail3,
         i_related4, i_thumbnail4,
         i_related5, i_thumbnail5
    FROM getPromoImages(_i_id)
    AS l(I_R1 NUMERIC(10), 
         I_T1 NUMERIC(10),
         I_R2 NUMERIC(10), 
         I_T2 NUMERIC(10),
         I_R3 NUMERIC(10), 
         I_T3 NUMERIC(10),
         I_R4 NUMERIC(10), 
         I_T4 NUMERIC(10),
         I_R5 NUMERIC(10), 
         I_T5 NUMERIC(10));

/* PERFORM i_id, i_title, a_fname, a_lname
  FROM item, author
  WHERE i_a_id = a_id
    AND i_title LIKE ''%''||_i_title||''%''
  ORDER BY i_title ASC;

  IF NOT FOUND THEN
    RETURN;
  END IF;
*/
  OPEN refcur FOR SELECT i_id, i_title, a_fname, a_lname
  FROM item, author
  WHERE i_a_id = a_id
    AND i_title LIKE ''%''||_i_title||''%''
  ORDER BY i_title ASC;

--
--  The first fetch
--    
    items := 0;
    FETCH refcur INTO i_id1, i_title1, a_fname1, a_lname1;

    IF FOUND THEN
      FETCH refcur INTO i_id2, i_title2, a_fname2, a_lname2;
      items := items + 1;
    END IF;
    IF FOUND THEN
      FETCH refcur INTO i_id3, i_title3, a_fname3, a_lname3;
      items := items + 1;
    END IF;
    IF FOUND THEN
      FETCH refcur INTO i_id4, i_title4, a_fname4, a_lname4;
      items := items + 1;
    END IF;
    IF FOUND THEN
      FETCH refcur INTO i_id5, i_title5, a_fname5, a_lname5;
      items := items + 1;
    END IF;
    IF FOUND THEN
      FETCH refcur INTO i_id6, i_title6, a_fname6, a_lname6;
      items := items + 1;
    END IF;
    IF FOUND THEN
      FETCH refcur INTO i_id7, i_title7, a_fname7, a_lname7;
      items := items + 1;
    END IF;
    IF FOUND THEN
      FETCH refcur INTO i_id8, i_title8, a_fname8, a_lname8;
      items := items + 1;
    END IF;
    IF FOUND THEN
      FETCH refcur INTO i_id9, i_title9, a_fname9, a_lname9;
      items := items + 1;
    END IF;
    IF FOUND THEN
      FETCH refcur INTO i_id10, i_title10, a_fname10, a_lname10;
      items := items + 1;
    END IF;
    IF FOUND THEN
      FETCH refcur INTO i_id11, i_title11, a_fname11, a_lname11;
      items := items + 1;
    END IF;
    IF FOUND THEN
      FETCH refcur INTO i_id12, i_title12, a_fname12, a_lname12;
      items := items + 1;
    END IF;
    IF FOUND THEN
      FETCH refcur INTO i_id13, i_title13, a_fname13, a_lname13;
      items := items + 1;
    END IF;
    IF FOUND THEN
      FETCH refcur INTO i_id14, i_title14, a_fname14, a_lname14;
      items := items + 1;
    END IF;
    IF FOUND THEN
      FETCH refcur INTO i_id15, i_title15, a_fname15, a_lname15;
      items := items + 1;
    END IF;
    IF FOUND THEN
      FETCH refcur INTO i_id16, i_title16, a_fname16, a_lname16;
      items := items + 1;
    END IF;
    IF FOUND THEN
      FETCH refcur INTO i_id17, i_title17, a_fname17, a_lname17;
      items := items + 1;
    END IF;
    IF FOUND THEN
      FETCH refcur INTO i_id18, i_title18, a_fname18, a_lname18;
      items := items + 1;
    END IF;
    IF FOUND THEN
      FETCH refcur INTO i_id19, i_title19, a_fname19, a_lname19;
      items := items + 1;
    END IF;
    IF FOUND THEN
      FETCH refcur INTO i_id20, i_title20, a_fname20, a_lname20;
      items := items + 1;
    END IF;
    IF FOUND THEN
      FETCH refcur INTO i_id21, i_title21, a_fname21, a_lname21;
      items := items + 1;
    END IF;
    IF FOUND THEN
      FETCH refcur INTO i_id22, i_title22, a_fname22, a_lname22;
      items := items + 1;
    END IF;
    IF FOUND THEN
      FETCH refcur INTO i_id23, i_title23, a_fname23, a_lname23;
      items := items + 1;
    END IF;
    IF FOUND THEN
      FETCH refcur INTO i_id24, i_title24, a_fname24, a_lname24;
      items := items + 1;
    END IF;
    IF FOUND THEN
      FETCH refcur INTO i_id25, i_title25, a_fname25, a_lname25;
      items := items + 1;
    END IF;
    IF FOUND THEN
      FETCH refcur INTO i_id26, i_title26, a_fname26, a_lname26;
      items := items + 1;
    END IF;
    IF FOUND THEN
      FETCH refcur INTO i_id27, i_title27, a_fname27, a_lname27;
      items := items + 1;
    END IF;
    IF FOUND THEN
      FETCH refcur INTO i_id28, i_title28, a_fname28, a_lname28;
      items := items + 1;
    END IF;
    IF FOUND THEN
      FETCH refcur INTO i_id29, i_title29, a_fname29, a_lname29;
      items := items + 1;
    END IF;
    IF FOUND THEN
      FETCH refcur INTO i_id30, i_title30, a_fname30, a_lname30;
      items := items + 1;
    END IF;
    IF FOUND THEN
      FETCH refcur INTO i_id31, i_title31, a_fname31, a_lname31;
      items := items + 1;
    END IF;
    IF FOUND THEN
      FETCH refcur INTO i_id32, i_title32, a_fname32, a_lname32;
      items := items + 1;
    END IF;
    IF FOUND THEN
      FETCH refcur INTO i_id33, i_title33, a_fname33, a_lname33;
      items := items + 1;
    END IF;
    IF FOUND THEN
      FETCH refcur INTO i_id34, i_title34, a_fname34, a_lname34;
      items := items + 1;
    END IF;
    IF FOUND THEN
      FETCH refcur INTO i_id35, i_title35, a_fname35, a_lname35;
      items := items + 1;
    END IF;
    IF FOUND THEN
      FETCH refcur INTO i_id36, i_title36, a_fname36, a_lname36;
      items := items + 1;
    END IF;
    IF FOUND THEN
      FETCH refcur INTO i_id37, i_title37, a_fname37, a_lname37;
      items := items + 1;
    END IF;
    IF FOUND THEN
      FETCH refcur INTO i_id38, i_title38, a_fname38, a_lname38;
      items := items + 1;
    END IF;
    IF FOUND THEN
      FETCH refcur INTO i_id39, i_title39, a_fname39, a_lname39;
      items := items + 1;
    END IF;
    IF FOUND THEN
      FETCH refcur INTO i_id40, i_title40, a_fname40, a_lname40;
      items := items + 1;
    END IF;
    IF FOUND THEN
      FETCH refcur INTO i_id41, i_title41, a_fname41, a_lname41;
      items := items + 1;
    END IF;
    IF FOUND THEN
      FETCH refcur INTO i_id42, i_title42, a_fname42, a_lname42;
      items := items + 1;
    END IF;
    IF FOUND THEN
      FETCH refcur INTO i_id43, i_title43, a_fname43, a_lname43;
      items := items + 1;
    END IF;
    IF FOUND THEN
      FETCH refcur INTO i_id44, i_title44, a_fname44, a_lname44;
      items := items + 1;
    END IF;
    IF FOUND THEN
      FETCH refcur INTO i_id45, i_title45, a_fname45, a_lname45;
      items := items + 1;
    END IF;
    IF FOUND THEN
      FETCH refcur INTO i_id46, i_title46, a_fname46, a_lname46;
      items := items + 1;
    END IF;
    IF FOUND THEN
      FETCH refcur INTO i_id47, i_title47, a_fname47, a_lname47;
      items := items + 1;
    END IF;
    IF FOUND THEN
      FETCH refcur INTO i_id48, i_title48, a_fname48, a_lname48;
      items := items + 1;
    END IF;
    IF FOUND THEN
      FETCH refcur INTO i_id49, i_title49, a_fname49, a_lname49;
      items := items + 1;
    END IF;
    IF FOUND THEN
      FETCH refcur INTO i_id50, i_title50, a_fname50, a_lname50;
      items := items + 1;
    END IF;

--
--  Closing the cursor
--    
    CLOSE refcur;

    SELECT
    i_related1::NUMERIC(10),
    i_related2::NUMERIC(10),
    i_related3::NUMERIC(10),
    i_related4::NUMERIC(10),
    i_related5::NUMERIC(10),
    i_thumbnail1::NUMERIC(10),
    i_thumbnail2::NUMERIC(10),
    i_thumbnail3::NUMERIC(10),
    i_thumbnail4::NUMERIC(10),
    i_thumbnail5::NUMERIC(10),
    items::NUMERIC(2),
    i_id1::NUMERIC(10),
    i_title1::VARCHAR(60),
    a_fname1::VARCHAR(20),
    a_lname1::VARCHAR(20),
    i_id2::NUMERIC(10),
    i_title2::VARCHAR(60),
    a_fname2::VARCHAR(20),
    a_lname2::VARCHAR(20),
    i_id3::NUMERIC(10),
    i_title3::VARCHAR(60),
    a_fname3::VARCHAR(20),
    a_lname3::VARCHAR(20),
    i_id4::NUMERIC(10),
    i_title4::VARCHAR(60),
    a_fname4::VARCHAR(20),
    a_lname4::VARCHAR(20),
    i_id5::NUMERIC(10),
    i_title5::VARCHAR(60),
    a_fname5::VARCHAR(20),
    a_lname5::VARCHAR(20),
    i_id6::NUMERIC(10),
    i_title6::VARCHAR(60),
    a_fname6::VARCHAR(20),
    a_lname6::VARCHAR(20),
    i_id7::NUMERIC(10),
    i_title7::VARCHAR(60),
    a_fname7::VARCHAR(20),
    a_lname7::VARCHAR(20),
    i_id8::NUMERIC(10),
    i_title8::VARCHAR(60),
    a_fname8::VARCHAR(20),
    a_lname8::VARCHAR(20),
    i_id9::NUMERIC(10),
    i_title9::VARCHAR(60),
    a_fname9::VARCHAR(20),
    a_lname9::VARCHAR(20),
    i_id10::NUMERIC(10),
    i_title10::VARCHAR(60),
    a_fname10::VARCHAR(20),
    a_lname10::VARCHAR(20),
    i_id11::NUMERIC(10),
    i_title11::VARCHAR(60),
    a_fname11::VARCHAR(20),
    a_lname11::VARCHAR(20),
    i_id12::NUMERIC(10),
    i_title12::VARCHAR(60),
    a_fname12::VARCHAR(20),
    a_lname12::VARCHAR(20),
    i_id13::NUMERIC(10),
    i_title13::VARCHAR(60),
    a_fname13::VARCHAR(20),
    a_lname13::VARCHAR(20),
    i_id14::NUMERIC(10),
    i_title14::VARCHAR(60),
    a_fname14::VARCHAR(20),
    a_lname14::VARCHAR(20),
    i_id15::NUMERIC(10),
    i_title15::VARCHAR(60),
    a_fname15::VARCHAR(20),
    a_lname15::VARCHAR(20),
    i_id16::NUMERIC(10),
    i_title16::VARCHAR(60),
    a_fname16::VARCHAR(20),
    a_lname16::VARCHAR(20),
    i_id17::NUMERIC(10),
    i_title17::VARCHAR(60),
    a_fname17::VARCHAR(20),
    a_lname17::VARCHAR(20),
    i_id18::NUMERIC(10),
    i_title18::VARCHAR(60),
    a_fname18::VARCHAR(20),
    a_lname18::VARCHAR(20),
    i_id19::NUMERIC(10),
    i_title19::VARCHAR(60),
    a_fname19::VARCHAR(20),
    a_lname19::VARCHAR(20),
    i_id20::NUMERIC(10),
    i_title20::VARCHAR(60),
    a_fname20::VARCHAR(20),
    a_lname20::VARCHAR(20),
    i_id21::NUMERIC(10),
    i_title21::VARCHAR(60),
    a_fname21::VARCHAR(20),
    a_lname21::VARCHAR(20),
    i_id22::NUMERIC(10),
    i_title22::VARCHAR(60),
    a_fname22::VARCHAR(20),
    a_lname22::VARCHAR(20),
    i_id23::NUMERIC(10),
    i_title23::VARCHAR(60),
    a_fname23::VARCHAR(20),
    a_lname23::VARCHAR(20),
    i_id24::NUMERIC(10),
    i_title24::VARCHAR(60),
    a_fname24::VARCHAR(20),
    a_lname24::VARCHAR(20),
    i_id25::NUMERIC(10),
    i_title25::VARCHAR(60),
    a_fname25::VARCHAR(20),
    a_lname25::VARCHAR(20),
    i_id26::NUMERIC(10),
    i_title26::VARCHAR(60),
    a_fname26::VARCHAR(20),
    a_lname26::VARCHAR(20),
    i_id27::NUMERIC(10),
    i_title27::VARCHAR(60),
    a_fname27::VARCHAR(20),
    a_lname27::VARCHAR(20),
    i_id28::NUMERIC(10),
    i_title28::VARCHAR(60),
    a_fname28::VARCHAR(20),
    a_lname28::VARCHAR(20),
    i_id29::NUMERIC(10),
    i_title29::VARCHAR(60),
    a_fname29::VARCHAR(20),
    a_lname29::VARCHAR(20),
    i_id30::NUMERIC(10),
    i_title30::VARCHAR(60),
    a_fname30::VARCHAR(20),
    a_lname30::VARCHAR(20),
    i_id31::NUMERIC(10),
    i_title31::VARCHAR(60),
    a_fname31::VARCHAR(20),
    a_lname31::VARCHAR(20),
    i_id32::NUMERIC(10),
    i_title32::VARCHAR(60),
    a_fname32::VARCHAR(20),
    a_lname32::VARCHAR(20),
    i_id33::NUMERIC(10),
    i_title33::VARCHAR(60),
    a_fname33::VARCHAR(20),
    a_lname33::VARCHAR(20),
    i_id34::NUMERIC(10),
    i_title34::VARCHAR(60),
    a_fname34::VARCHAR(20),
    a_lname34::VARCHAR(20),
    i_id35::NUMERIC(10),
    i_title35::VARCHAR(60),
    a_fname35::VARCHAR(20),
    a_lname35::VARCHAR(20),
    i_id36::NUMERIC(10),
    i_title36::VARCHAR(60),
    a_fname36::VARCHAR(20),
    a_lname36::VARCHAR(20),
    i_id37::NUMERIC(10),
    i_title37::VARCHAR(60),
    a_fname37::VARCHAR(20),
    a_lname37::VARCHAR(20),
    i_id38::NUMERIC(10),
    i_title38::VARCHAR(60),
    a_fname38::VARCHAR(20),
    a_lname38::VARCHAR(20),
    i_id39::NUMERIC(10),
    i_title39::VARCHAR(60),
    a_fname39::VARCHAR(20),
    a_lname39::VARCHAR(20),
    i_id40::NUMERIC(10),
    i_title40::VARCHAR(60),
    a_fname40::VARCHAR(20),
    a_lname40::VARCHAR(20),
    i_id41::NUMERIC(10),
    i_title41::VARCHAR(60),
    a_fname41::VARCHAR(20),
    a_lname41::VARCHAR(20),
    i_id42::NUMERIC(10),
    i_title42::VARCHAR(60),
    a_fname42::VARCHAR(20),
    a_lname42::VARCHAR(20),
    i_id43::NUMERIC(10),
    i_title43::VARCHAR(60),
    a_fname43::VARCHAR(20),
    a_lname43::VARCHAR(20),
    i_id44::NUMERIC(10),
    i_title44::VARCHAR(60),
    a_fname44::VARCHAR(20),
    a_lname44::VARCHAR(20),
    i_id45::NUMERIC(10),
    i_title45::VARCHAR(60),
    a_fname45::VARCHAR(20),
    a_lname45::VARCHAR(20),
    i_id46::NUMERIC(10),
    i_title46::VARCHAR(60),
    a_fname46::VARCHAR(20),
    a_lname46::VARCHAR(20),
    i_id47::NUMERIC(10),
    i_title47::VARCHAR(60),
    a_fname47::VARCHAR(20),
    a_lname47::VARCHAR(20),
    i_id48::NUMERIC(10),
    i_title48::VARCHAR(60),
    a_fname48::VARCHAR(20),
    a_lname48::VARCHAR(20),
    i_id49::NUMERIC(10),
    i_title49::VARCHAR(60),
    a_fname49::VARCHAR(20),
    a_lname49::VARCHAR(20),
    i_id50::NUMERIC(10),
    i_title50::VARCHAR(60),
    a_fname50::VARCHAR(20),
    a_lname50::VARCHAR(20)
    INTO rec;
    RETURN rec;
   
  END;
' LANGUAGE 'plpgsql';
commit;
-- Usage:
-- 
-- SELECT * FROM (
--    i_title VARCHAR(60),
--    i_id numeric(10),
-- )
-- AS l(
--    i_related1 numeric(10),
--    i_related2 numeric(10),
--    i_related3 numeric(10),
--    i_related4 numeric(10),
--    i_related5 numeric(10),
--    i_thumbnail1 numeric(10),
--    i_thumbnail2 numeric(10),
--    i_thumbnail3 numeric(10),
--    i_thumbnail4 numeric(10),
--    i_thumbnail5 numeric(10),
--    items numeric(2),
--    i_id1 numeric(10),
--    i_title1 VARCHAR(60),
--    a_fname1 VARCHAR(20),
--    a_lname1 VARCHAR(20),
--    i_id2 numeric(10),
--    i_title2 VARCHAR(60),
--    a_fname2 VARCHAR(20),
--    a_lname2 VARCHAR(20),
--    i_id3 numeric(10),
--    i_title3 VARCHAR(60),
--    a_fname3 VARCHAR(20),
--    a_lname3 VARCHAR(20),
--    i_id4 numeric(10),
--    i_title4 VARCHAR(60),
--    a_fname4 VARCHAR(20),
--    a_lname4 VARCHAR(20),
--    i_id5 numeric(10),
--    i_title5 VARCHAR(60),
--    a_fname5 VARCHAR(20),
--    a_lname5 VARCHAR(20),
--    i_id6 numeric(10),
--    i_title6 VARCHAR(60),
--    a_fname6 VARCHAR(20),
--    a_lname6 VARCHAR(20),
--    i_id7 numeric(10),
--    i_title7 VARCHAR(60),
--    a_fname7 VARCHAR(20),
--    a_lname7 VARCHAR(20),
--    i_id8 numeric(10),
--    i_title8 VARCHAR(60),
--    a_fname8 VARCHAR(20),
--    a_lname8 VARCHAR(20),
--    i_id9 numeric(10),
--    i_title9 VARCHAR(60),
--    a_fname9 VARCHAR(20),
--    a_lname9 VARCHAR(20),
--    i_id10 numeric(10),
--    i_title10 VARCHAR(60),
--    a_fname10 VARCHAR(20),
--    a_lname10 VARCHAR(20),
--    i_id11 numeric(10),
--    i_title11 VARCHAR(60),
--    a_fname11 VARCHAR(20),
--    a_lname11 VARCHAR(20),
--    i_id12 numeric(10),
--    i_title12 VARCHAR(60),
--    a_fname12 VARCHAR(20),
--    a_lname12 VARCHAR(20),
--    i_id13 numeric(10),
--    i_title13 VARCHAR(60),
--    a_fname13 VARCHAR(20),
--    a_lname13 VARCHAR(20),
--    i_id14 numeric(10),
--    i_title14 VARCHAR(60),
--    a_fname14 VARCHAR(20),
--    a_lname14 VARCHAR(20),
--    i_id15 numeric(10),
--    i_title15 VARCHAR(60),
--    a_fname15 VARCHAR(20),
--    a_lname15 VARCHAR(20),
--    i_id16 numeric(10),
--    i_title16 VARCHAR(60),
--    a_fname16 VARCHAR(20),
--    a_lname16 VARCHAR(20),
--    i_id17 numeric(10),
--    i_title17 VARCHAR(60),
--    a_fname17 VARCHAR(20),
--    a_lname17 VARCHAR(20),
--    i_id18 numeric(10),
--    i_title18 VARCHAR(60),
--    a_fname18 VARCHAR(20),
--    a_lname18 VARCHAR(20),
--    i_id19 numeric(10),
--    i_title19 VARCHAR(60),
--    a_fname19 VARCHAR(20),
--    a_lname19 VARCHAR(20),
--    i_id20 numeric(10),
--    i_title20 VARCHAR(60),
--    a_fname20 VARCHAR(20),
--    a_lname20 VARCHAR(20),
--    i_id21 numeric(10),
--    i_title21 VARCHAR(60),
--    a_fname21 VARCHAR(20),
--    a_lname21 VARCHAR(20),
--    i_id22 numeric(10),
--    i_title22 VARCHAR(60),
--    a_fname22 VARCHAR(20),
--    a_lname22 VARCHAR(20),
--    i_id23 numeric(10),
--    i_title23 VARCHAR(60),
--    a_fname23 VARCHAR(20),
--    a_lname23 VARCHAR(20),
--    i_id24 numeric(10),
--    i_title24 VARCHAR(60),
--    a_fname24 VARCHAR(20),
--    a_lname24 VARCHAR(20),
--    i_id25 numeric(10),
--    i_title25 VARCHAR(60),
--    a_fname25 VARCHAR(20),
--    a_lname25 VARCHAR(20),
--    i_id26 numeric(10),
--    i_title26 VARCHAR(60),
--    a_fname26 VARCHAR(20),
--    a_lname26 VARCHAR(20),
--    i_id27 numeric(10),
--    i_title27 VARCHAR(60),
--    a_fname27 VARCHAR(20),
--    a_lname27 VARCHAR(20),
--    i_id28 numeric(10),
--    i_title28 VARCHAR(60),
--    a_fname28 VARCHAR(20),
--    a_lname28 VARCHAR(20),
--    i_id29 numeric(10),
--    i_title29 VARCHAR(60),
--    a_fname29 VARCHAR(20),
--    a_lname29 VARCHAR(20),
--    i_id30 numeric(10),
--    i_title30 VARCHAR(60),
--    a_fname30 VARCHAR(20),
--    a_lname30 VARCHAR(20),
--    i_id31 numeric(10),
--    i_title31 VARCHAR(60),
--    a_fname31 VARCHAR(20),
--    a_lname31 VARCHAR(20),
--    i_id32 numeric(10),
--    i_title32 VARCHAR(60),
--    a_fname32 VARCHAR(20),
--    a_lname32 VARCHAR(20),
--    i_id33 numeric(10),
--    i_title33 VARCHAR(60),
--    a_fname33 VARCHAR(20),
--    a_lname33 VARCHAR(20),
--    i_id34 numeric(10),
--    i_title34 VARCHAR(60),
--    a_fname34 VARCHAR(20),
--    a_lname34 VARCHAR(20),
--    i_id35 numeric(10),
--    i_title35 VARCHAR(60),
--    a_fname35 VARCHAR(20),
--    a_lname35 VARCHAR(20),
--    i_id36 numeric(10),
--    i_title36 VARCHAR(60),
--    a_fname36 VARCHAR(20),
--    a_lname36 VARCHAR(20),
--    i_id37 numeric(10),
--    i_title37 VARCHAR(60),
--    a_fname37 VARCHAR(20),
--    a_lname37 VARCHAR(20),
--    i_id38 numeric(10),
--    i_title38 VARCHAR(60),
--    a_fname38 VARCHAR(20),
--    a_lname38 VARCHAR(20),
--    i_id39 numeric(10),
--    i_title39 VARCHAR(60),
--    a_fname39 VARCHAR(20),
--    a_lname39 VARCHAR(20),
--    i_id40 numeric(10),
--    i_title40 VARCHAR(60),
--    a_fname40 VARCHAR(20),
--    a_lname40 VARCHAR(20),
--    i_id41 numeric(10),
--    i_title41 VARCHAR(60),
--    a_fname41 VARCHAR(20),
--    a_lname41 VARCHAR(20),
--    i_id42 numeric(10),
--    i_title42 VARCHAR(60),
--    a_fname42 VARCHAR(20),
--    a_lname42 VARCHAR(20),
--    i_id43 numeric(10),
--    i_title43 VARCHAR(60),
--    a_fname43 VARCHAR(20),
--    a_lname43 VARCHAR(20),
--    i_id44 numeric(10),
--    i_title44 VARCHAR(60),
--    a_fname44 VARCHAR(20),
--    a_lname44 VARCHAR(20),
--    i_id45 numeric(10),
--    i_title45 VARCHAR(60),
--    a_fname45 VARCHAR(20),
--    a_lname45 VARCHAR(20),
--    i_id46 numeric(10),
--    i_title46 VARCHAR(60),
--    a_fname46 VARCHAR(20),
--    a_lname46 VARCHAR(20),
--    i_id47 numeric(10),
--    i_title47 VARCHAR(60),
--    a_fname47 VARCHAR(20),
--    a_lname47 VARCHAR(20),
--    i_id48 numeric(10),
--    i_title48 VARCHAR(60),
--    a_fname48 VARCHAR(20),
--    a_lname48 VARCHAR(20),
--    i_id49 numeric(10),
--    i_title49 VARCHAR(60),
--    a_fname49 VARCHAR(20),
--    a_lname49 VARCHAR(20),
--    i_id50 numeric(10),
--    i_title50 VARCHAR(60),
--    a_fname50 VARCHAR(20),
--    a_lname50 VARCHAR(20),
--);

