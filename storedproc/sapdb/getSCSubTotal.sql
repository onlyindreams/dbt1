/*
/*
/* This file is released under the terms of the Artistic License.  Please see
/* the file LICENSE, included in this package, for details.
/*
/* Copyright (C) 2002 Mark Wong & Jenny Zhang &
/*                    Open Source Development Lab, Inc.
/*
/*/
CREATE DBPROC getSCSubTotal (IN sc_id fixed(10,0), OUT sub_total fixed(17,2)) AS
VAR cost fixed(17,2); qty fixed(3,0);
BEGIN
set sub_total=0;
SELECT scl_cost,scl_qty from dbt.shopping_cart_line where scl_sc_id=:sc_id;
while $rc=0 do begin
fetch into :cost, :qty;
if $rc=0 then set sub_total=sub_total+cost*qty;
end;
END;
;
/
/
