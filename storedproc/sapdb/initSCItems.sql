/*
/*
/* This file is released under the terms of the Artistic License.  Please see
/* the file LICENSE, included in this package, for details.
/*
/* Copyright (C) 2002 Mark Wong & Jenny Zhang &
/*                    Open Source Development Lab, Inc.
/*
/*/
CREATE DBPROC initSCItems(
  INOUT scl_i_id1 fixed(10,0), INOUT scl_title1 varchar(60),
  INOUT scl_cost1 fixed(17,2), INOUT scl_srp1 fixed(17,2),
  INOUT scl_backing1 varchar(15), INOUT scl_qty1 fixed(3,0),
  INOUT scl_i_id2 fixed(10,0), INOUT scl_title2 varchar(60),
  INOUT scl_cost2 fixed(17,2), INOUT scl_srp2 fixed(17,2),
  INOUT scl_backing2 varchar(15), INOUT scl_qty2 fixed(3,0),
  INOUT scl_i_id3 fixed(10,0), INOUT scl_title3 varchar(60),
  INOUT scl_cost3 fixed(17,2), INOUT scl_srp3 fixed(17,2),
  INOUT scl_backing3 varchar(15), INOUT scl_qty3 fixed(3,0),
  INOUT scl_i_id4 fixed(10,0), INOUT scl_title4 varchar(60),
  INOUT scl_cost4 fixed(17,2), INOUT scl_srp4 fixed(17,2),
  INOUT scl_backing4 varchar(15), INOUT scl_qty4 fixed(3,0),
  INOUT scl_i_id5 fixed(10,0), INOUT scl_title5 varchar(60),
  INOUT scl_cost5 fixed(17,2), INOUT scl_srp5 fixed(17,2),
  INOUT scl_backing5 varchar(15), INOUT scl_qty5 fixed(3,0),
  INOUT scl_i_id6 fixed(10,0), INOUT scl_title6 varchar(60),
  INOUT scl_cost6 fixed(17,2), INOUT scl_srp6 fixed(17,2),
  INOUT scl_backing6 varchar(15), INOUT scl_qty6 fixed(3,0),
  INOUT scl_i_id7 fixed(10,0), INOUT scl_title7 varchar(60),
  INOUT scl_cost7 fixed(17,2), INOUT scl_srp7 fixed(17,2),
  INOUT scl_backing7 varchar(15), INOUT scl_qty7 fixed(3,0),
  INOUT scl_i_id8 fixed(10,0), INOUT scl_title8 varchar(60),
  INOUT scl_cost8 fixed(17,2), INOUT scl_srp8 fixed(17,2),
  INOUT scl_backing8 varchar(15), INOUT scl_qty8 fixed(3,0),
  INOUT scl_i_id9 fixed(10,0), INOUT scl_title9 varchar(60),
  INOUT scl_cost9 fixed(17,2), INOUT scl_srp9 fixed(17,2),
  INOUT scl_backing9 varchar(15), INOUT scl_qty9 fixed(3,0),
  INOUT scl_i_id10 fixed(10,0), INOUT scl_title10 varchar(60),
  INOUT scl_cost10 fixed(17,2), INOUT scl_srp10 fixed(17,2),
  INOUT scl_backing10 varchar(15), INOUT scl_qty10 fixed(3,0),
  INOUT scl_i_id11 fixed(10,0), INOUT scl_title11 varchar(60),
  INOUT scl_cost11 fixed(17,2), INOUT scl_srp11 fixed(17,2),
  INOUT scl_backing11 varchar(15), INOUT scl_qty11 fixed(3,0),
  INOUT scl_i_id12 fixed(10,0), INOUT scl_title12 varchar(60),
  INOUT scl_cost12 fixed(17,2), INOUT scl_srp12 fixed(17,2),
  INOUT scl_backing12 varchar(15), INOUT scl_qty12 fixed(3,0),
  INOUT scl_i_id13 fixed(10,0), INOUT scl_title13 varchar(60),
  INOUT scl_cost13 fixed(17,2), INOUT scl_srp13 fixed(17,2),
  INOUT scl_backing13 varchar(15), INOUT scl_qty13 fixed(3,0),
  INOUT scl_i_id14 fixed(10,0), INOUT scl_title14 varchar(60),
  INOUT scl_cost14 fixed(17,2), INOUT scl_srp14 fixed(17,2),
  INOUT scl_backing14 varchar(15), INOUT scl_qty14 fixed(3,0),
  INOUT scl_i_id15 fixed(10,0), INOUT scl_title15 varchar(60),
  INOUT scl_cost15 fixed(17,2), INOUT scl_srp15 fixed(17,2),
  INOUT scl_backing15 varchar(15), INOUT scl_qty15 fixed(3,0),
  INOUT scl_i_id16 fixed(10,0), INOUT scl_title16 varchar(60),
  INOUT scl_cost16 fixed(17,2), INOUT scl_srp16 fixed(17,2),
  INOUT scl_backing16 varchar(15), INOUT scl_qty16 fixed(3,0),
  INOUT scl_i_id17 fixed(10,0), INOUT scl_title17 varchar(60),
  INOUT scl_cost17 fixed(17,2), INOUT scl_srp17 fixed(17,2),
  INOUT scl_backing17 varchar(15), INOUT scl_qty17 fixed(3,0),
  INOUT scl_i_id18 fixed(10,0), INOUT scl_title18 varchar(60),
  INOUT scl_cost18 fixed(17,2), INOUT scl_srp18 fixed(17,2),
  INOUT scl_backing18 varchar(15), INOUT scl_qty18 fixed(3,0),
  INOUT scl_i_id19 fixed(10,0), INOUT scl_title19 varchar(60),
  INOUT scl_cost19 fixed(17,2), INOUT scl_srp19 fixed(17,2),
  INOUT scl_backing19 varchar(15), INOUT scl_qty19 fixed(3,0),
  INOUT scl_i_id20 fixed(10,0), INOUT scl_title20 varchar(60),
  INOUT scl_cost20 fixed(17,2), INOUT scl_srp20 fixed(17,2),
  INOUT scl_backing20 varchar(15), INOUT scl_qty20 fixed(3,0)) AS
BEGIN
  set scl_i_id1=0;
  set scl_title1='';
  set scl_cost1=0;
  set scl_srp1=0;
  set scl_backing1='';
  set scl_qty1=0;
  set scl_i_id2=0;
  set scl_title2='';
  set scl_cost2=0;
  set scl_srp2=0;
  set scl_backing2='';
  set scl_qty2=0;
  set scl_i_id3=0;
  set scl_title3='';
  set scl_cost3=0;
  set scl_srp3=0;
  set scl_backing3='';
  set scl_qty3=0;
  set scl_i_id4=0;
  set scl_title4='';
  set scl_cost4=0;
  set scl_srp4=0;
  set scl_backing4='';
  set scl_qty4=0;
  set scl_i_id5=0;
  set scl_title5='';
  set scl_cost5=0;
  set scl_srp5=0;
  set scl_backing5='';
  set scl_qty5=0;
  set scl_i_id6=0;
  set scl_title6='';
  set scl_cost6=0;
  set scl_srp6=0;
  set scl_backing6='';
  set scl_qty6=0;
  set scl_i_id7=0;
  set scl_title7='';
  set scl_cost7=0;
  set scl_srp7=0;
  set scl_backing7='';
  set scl_qty7=0;
  set scl_i_id8=0;
  set scl_title8='';
  set scl_cost8=0;
  set scl_srp8=0;
  set scl_backing8='';
  set scl_qty8=0;
  set scl_i_id9=0;
  set scl_title9='';
  set scl_cost9=0;
  set scl_srp9=0;
  set scl_backing9='';
  set scl_qty9=0;
  set scl_i_id10=0;
  set scl_title10='';
  set scl_cost10=0;
  set scl_srp10=0;
  set scl_backing10='';
  set scl_qty10=0;
  set scl_i_id11=0;
  set scl_title11='';
  set scl_cost11=0;
  set scl_srp11=0;
  set scl_backing11='';
  set scl_qty11=0;
  set scl_i_id12=0;
  set scl_title12='';
  set scl_cost12=0;
  set scl_srp12=0;
  set scl_backing12='';
  set scl_qty12=0;
  set scl_i_id13=0;
  set scl_title13='';
  set scl_cost13=0;
  set scl_srp13=0;
  set scl_backing13='';
  set scl_qty13=0;
  set scl_i_id14=0;
  set scl_title14='';
  set scl_cost14=0;
  set scl_srp14=0;
  set scl_backing14='';
  set scl_qty14=0;
  set scl_i_id15=0;
  set scl_title15='';
  set scl_cost15=0;
  set scl_srp15=0;
  set scl_backing15='';
  set scl_qty15=0;
  set scl_i_id16=0;
  set scl_title16='';
  set scl_cost16=0;
  set scl_srp16=0;
  set scl_backing16='';
  set scl_qty16=0;
  set scl_i_id17=0;
  set scl_title17='';
  set scl_cost17=0;
  set scl_srp17=0;
  set scl_backing17='';
  set scl_qty17=0;
  set scl_i_id18=0;
  set scl_title18='';
  set scl_cost18=0;
  set scl_srp18=0;
  set scl_backing18='';
  set scl_qty18=0;
  set scl_i_id19=0;
  set scl_title19='';
  set scl_cost19=0;
  set scl_srp19=0;
  set scl_backing19='';
  set scl_qty19=0;
  set scl_i_id20=0;
  set scl_title20='';
  set scl_cost20=0;
  set scl_srp20=0;
  set scl_backing20='';
  set scl_qty20=0;
END;
;
