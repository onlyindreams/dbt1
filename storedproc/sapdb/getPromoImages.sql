/*
/*
/* This file is released under the terms of the Artistic License.  Please see
/* the file LICENSE, included in this package, for details.
/*
/* Copyright (C) 2002 Mark Wong & Jenny Zhang &
/*                    Open Source Development Lab, Inc.
/*
/*/
CREATE DBPROC GetPromoImages(IN I_ID fixed(10, 0), 
OUT I_ID1 fixed(10), OUT I_T1 fixed(10), 
OUT I_ID2 fixed(10), OUT I_T2 fixed(10), 
OUT I_ID3 fixed(10), OUT I_T3 fixed(10), 
OUT I_ID4 fixed(10), OUT I_T4 fixed(10), 
OUT I_ID5 fixed(10), OUT I_T5 fixed(10)) AS 
        VAR r1 fixed(10); r2 fixed(10);r3 fixed(10);r4 fixed(10);r5 fixed(10);
BEGIN
SELECT i_related1, i_related2, i_related3, i_related4, i_related5 INTO :r1, :r2, :r3, :r4, :r5 FROM dbt.item WHERE i_id = :I_ID;
SELECT i_id, i_thumbnail FROM dbt.item WHERE i_id IN (:r1, :r2, :r3, :r4, :r5); 
FETCH INTO :I_ID1, :I_T1;
FETCH INTO :I_ID2, :I_T2;
FETCH INTO :I_ID3, :I_T3;
FETCH INTO :I_ID4, :I_T4;
FETCH INTO :I_ID5, :I_T5;
END;;
