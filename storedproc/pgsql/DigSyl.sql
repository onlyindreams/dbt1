/*
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2002 Mark Wong & Jenny Zhang &
 *                    Open Source Development Lab, Inc.
 * Contributors : Virginie Megy & Thierry Missimilly
 *		  Bull, Linux Competence Center
 *
 */
CREATE FUNCTION DigSyl(NUMERIC(10,0), INTEGER) RETURNS VARCHAR(64) AS'

DECLARE
	D ALIAS FOR $1;
	N ALIAS FOR $2;
	Str VARCHAR(64);
	base INTEGER;
	i INTEGER;
	digits INTEGER;
	debut INTEGER;
	New INTEGER;
	NewD INTEGER;

BEGIN
Str:='''';
digits:=0;
base:=D;
NewD:=D;
New:=N;

while base>0 loop
  digits:=digits+1;
  base:=base/10;
end loop;

if digits>N then
	New:=digits;
end if;

base:=1;
i:=0;
while i<New-1 loop
  base:=base*10;
  i:=i+1;
end loop;

i:=0;
while i<New loop
  digits:=NewD/base;
  debut:=digits*2+1;
  Str:=Str||SUBSTR(''BAOGALRIRESEATULINNG'', debut, 2);
  NewD:=NewD%base;
  base:=base/10;
  i:=i+1;
end loop;

return Str;
END;
' LANGUAGE 'plpgsql';
