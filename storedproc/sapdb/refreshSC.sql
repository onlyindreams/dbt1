/*
/*
/* This file is released under the terms of the Artistic License.  Please see
/* the file LICENSE, included in this package, for details.
/*
/* Copyright (C) 2002 Mark Wong & Jenny Zhang &
/*                    Open Source Development Lab, Inc.
/*
/*/
CREATE DBPROC refreshSC (IN sc_id fixed(10,0), IN itemcount fixed(2,0),
  IN i_id1 fixed(10,0), IN qty1 fixed(3,0),
  IN i_id2 fixed(10,0), IN qty2 fixed(3,0),
  IN i_id3 fixed(10,0), IN qty3 fixed(3,0),
  IN i_id4 fixed(10,0), IN qty4 fixed(3,0),
  IN i_id5 fixed(10,0), IN qty5 fixed(3,0),
  IN i_id6 fixed(10,0), IN qty6 fixed(3,0),
  IN i_id7 fixed(10,0), IN qty7 fixed(3,0),
  IN i_id8 fixed(10,0), IN qty8 fixed(3,0),
  IN i_id9 fixed(10,0), IN qty9 fixed(3,0),
  IN i_id10 fixed(10,0), IN qty10 fixed(3,0),
  IN i_id11 fixed(10,0), IN qty11 fixed(3,0),
  IN i_id12 fixed(10,0), IN qty12 fixed(3,0),
  IN i_id13 fixed(10,0), IN qty13 fixed(3,0),
  IN i_id14 fixed(10,0), IN qty14 fixed(3,0),
  IN i_id15 fixed(10,0), IN qty15 fixed(3,0),
  IN i_id16 fixed(10,0), IN qty16 fixed(3,0),
  IN i_id17 fixed(10,0), IN qty17 fixed(3,0),
  IN i_id18 fixed(10,0), IN qty18 fixed(3,0),
  IN i_id19 fixed(10,0), IN qty19 fixed(3,0),
  IN i_id20 fixed(10,0), IN qty20 fixed(3,0)) AS
  VAR i smallint;
BEGIN
set i=0;
if (i< itemcount and i<100 ) then begin
  if qty1=0 then 
    delete from dbt.shopping_cart_line 
      where scl_sc_id=:sc_id and scl_i_id=:i_id1
  else
    update dbt.shopping_cart_line set scl_qty=:qty1
      where scl_sc_id=:sc_id and scl_i_id=:i_id1;
  set i=i+1;
end;
if (i< itemcount and i<100 ) then begin
  if qty2=0 then
    delete from dbt.shopping_cart_line
      where scl_sc_id=:sc_id and scl_i_id=:i_id2
  else
    update dbt.shopping_cart_line set scl_qty=:qty2
      where scl_sc_id=:sc_id and scl_i_id=:i_id2;
  set i=i+1;
end;
if (i< itemcount and i<100 ) then begin
  if qty3=0 then
    delete from dbt.shopping_cart_line
      where scl_sc_id=:sc_id and scl_i_id=:i_id3
  else
    update dbt.shopping_cart_line set scl_qty=:qty3
      where scl_sc_id=:sc_id and scl_i_id=:i_id3;
  set i=i+1;
end;
if (i< itemcount and i<100 ) then begin
  if qty4=0 then
    delete from dbt.shopping_cart_line
      where scl_sc_id=:sc_id and scl_i_id=:i_id4
  else
    update dbt.shopping_cart_line set scl_qty=:qty4
      where scl_sc_id=:sc_id and scl_i_id=:i_id4;
  set i=i+1;
end;
if (i< itemcount and i<100 ) then begin
  if qty5=0 then
    delete from dbt.shopping_cart_line
      where scl_sc_id=:sc_id and scl_i_id=:i_id5
  else
    update dbt.shopping_cart_line set scl_qty=:qty5
      where scl_sc_id=:sc_id and scl_i_id=:i_id5;
  set i=i+1;
end;
if (i< itemcount and i<100 ) then begin
  if qty6=0 then
    delete from dbt.shopping_cart_line
      where scl_sc_id=:sc_id and scl_i_id=:i_id6
  else
    update dbt.shopping_cart_line set scl_qty=:qty6
      where scl_sc_id=:sc_id and scl_i_id=:i_id1;
  set i=i+1;
end;
if (i< itemcount and i<100 ) then begin
  if qty7=0 then
    delete from dbt.shopping_cart_line
      where scl_sc_id=:sc_id and scl_i_id=:i_id7
  else
    update dbt.shopping_cart_line set scl_qty=:qty7
      where scl_sc_id=:sc_id and scl_i_id=:i_id7;
  set i=i+1;
end;
if (i< itemcount and i<100 ) then begin
  if qty8=0 then
    delete from dbt.shopping_cart_line
      where scl_sc_id=:sc_id and scl_i_id=:i_id8
  else
    update dbt.shopping_cart_line set scl_qty=:qty8
      where scl_sc_id=:sc_id and scl_i_id=:i_id8;
  set i=i+1;
end;
if (i< itemcount and i<100 ) then begin
  if qty9=0 then
    delete from dbt.shopping_cart_line
      where scl_sc_id=:sc_id and scl_i_id=:i_id9
  else
    update dbt.shopping_cart_line set scl_qty=:qty9
      where scl_sc_id=:sc_id and scl_i_id=:i_id9;
  set i=i+1;
end;
if (i< itemcount and i<100 ) then begin
  if qty10=0 then
    delete from dbt.shopping_cart_line
      where scl_sc_id=:sc_id and scl_i_id=:i_id10
  else
    update dbt.shopping_cart_line set scl_qty=:qty10
      where scl_sc_id=:sc_id and scl_i_id=:i_id10;
  set i=i+1;
end;
if (i< itemcount and i<100 ) then begin
  if qty11=0 then 
    delete from dbt.shopping_cart_line 
      where scl_sc_id=:sc_id and scl_i_id=:i_id11
  else
    update dbt.shopping_cart_line set scl_qty=:qty11
      where scl_sc_id=:sc_id and scl_i_id=:i_id11;
  set i=i+1;
end;
if (i< itemcount and i<100 ) then begin
  if qty12=0 then
    delete from dbt.shopping_cart_line
      where scl_sc_id=:sc_id and scl_i_id=:i_id12
  else
    update dbt.shopping_cart_line set scl_qty=:qty12
      where scl_sc_id=:sc_id and scl_i_id=:i_id12;
  set i=i+1;
end;
if (i< itemcount and i<100 ) then begin
  if qty13=0 then
    delete from dbt.shopping_cart_line
      where scl_sc_id=:sc_id and scl_i_id=:i_id13
  else
    update dbt.shopping_cart_line set scl_qty=:qty13
      where scl_sc_id=:sc_id and scl_i_id=:i_id13;
  set i=i+1;
end;
if (i< itemcount and i<100 ) then begin
  if qty14=0 then
    delete from dbt.shopping_cart_line
      where scl_sc_id=:sc_id and scl_i_id=:i_id14
  else
    update dbt.shopping_cart_line set scl_qty=:qty14
      where scl_sc_id=:sc_id and scl_i_id=:i_id14;
  set i=i+1;
end;
if (i< itemcount and i<100 ) then begin
  if qty15=0 then
    delete from dbt.shopping_cart_line
      where scl_sc_id=:sc_id and scl_i_id=:i_id15
  else
    update dbt.shopping_cart_line set scl_qty=:qty15
      where scl_sc_id=:sc_id and scl_i_id=:i_id15;
  set i=i+1;
end;
if (i< itemcount and i<100 ) then begin
  if qty16=0 then
    delete from dbt.shopping_cart_line
      where scl_sc_id=:sc_id and scl_i_id=:i_id16
  else
    update dbt.shopping_cart_line set scl_qty=:qty16
      where scl_sc_id=:sc_id and scl_i_id=:i_id11;
  set i=i+1;
end;
if (i< itemcount and i<100 ) then begin
  if qty17=0 then
    delete from dbt.shopping_cart_line
      where scl_sc_id=:sc_id and scl_i_id=:i_id17
  else
    update dbt.shopping_cart_line set scl_qty=:qty17
      where scl_sc_id=:sc_id and scl_i_id=:i_id17;
  set i=i+1;
end;
if (i< itemcount and i<100 ) then begin
  if qty18=0 then
    delete from dbt.shopping_cart_line
      where scl_sc_id=:sc_id and scl_i_id=:i_id18
  else
    update dbt.shopping_cart_line set scl_qty=:qty18
      where scl_sc_id=:sc_id and scl_i_id=:i_id18;
  set i=i+1;
end;
if (i< itemcount and i<100 ) then begin
  if qty19=0 then
    delete from dbt.shopping_cart_line
      where scl_sc_id=:sc_id and scl_i_id=:i_id19
  else
    update dbt.shopping_cart_line set scl_qty=:qty19
      where scl_sc_id=:sc_id and scl_i_id=:i_id19;
  set i=i+1;
end;
if (i< itemcount and i<100 ) then begin
  if qty20=0 then
    delete from dbt.shopping_cart_line
      where scl_sc_id=:sc_id and scl_i_id=:i_id20
  else
    update dbt.shopping_cart_line set scl_qty=:qty20
      where scl_sc_id=:sc_id and scl_i_id=:i_id20;
  set i=i+1;
end;
END;
;
