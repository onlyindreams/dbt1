-- DisSyl generate string with length N according to D
--
-- This file is released under the terms of the Artistic License.  Please see
-- the file LICENSE, included in this package, for details.
--
-- Copyright (C) 2002 Open Source Development Lab, Inc.
-- History: 
-- July-2003: Created by Satoshi Nagayasu
--
--
CREATE OR REPLACE FUNCTION DigSyl(INTEGER, INTEGER) RETURNS VARCHAR(64) AS '
  DECLARE
    _D ALIAS FOR $1;
    _N ALIAS FOR $2;
    base INTEGER;
    digits INTEGER;
    i INTEGER;
    start INTEGER;
    Str VARCHAR(64);
-- declare d and n to replace _D and _N since I can not change constant value
    d INTEGER;
    n INTEGER;
  BEGIN
    d=_D;
    n=_N;
    Str := '''';
    digits := 0;
    base := _D;
-- find out how many digits
    WHILE base>0 LOOP
      digits := digits + 1;
      base   := base / 10;
    END LOOP;
-- set n to number of digits if necessary
    IF digits>_N THEN
      n := digits;
    END IF;
-- find out the largest base
    base := 1;
    FOR i IN 1..n-1 LOOP
      base := base*10;
    END LOOP;
-- get the string
    FOR i IN 0..n-1 LOOP 
--RAISE NOTICE ''base=%'', base;
      digits := d / base;
      start := digits * 2 + 1;
      Str := Str || SUBSTR(''BAOGALRIRESEATULINNG'', start, 2);
      d := d % base;
      base := base / 10;
--RAISE NOTICE ''i=%, _N=%, Str=|%|, d=%, start=%'', i, n, Str, d, start;
    END LOOP;
    RETURN Str;
  END;
' LANGUAGE 'plpgsql';
commit;
