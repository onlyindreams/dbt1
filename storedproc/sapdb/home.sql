/*
/*
/* This file is released under the terms of the Artistic License.  Please see
/* the file LICENSE, included in this package, for details.
/*
/* Copyright (C) 2002 Mark Wong & Jenny Zhang &
/*                    Open Source Development Lab, Inc.
/*
/*/
CREATE DBPROC home (IN C_ID fixed(10), IN I_ID fixed(10),
OUT C_FName char(15), OUT C_LName char(15),
OUT pp_i_id1 fixed(10), OUT pp_t_id1 fixed(10),
OUT pp_i_id2 fixed(10), OUT pp_t_id2 fixed(10),
OUT pp_i_id3 fixed(10), OUT pp_t_id3 fixed(10),
OUT pp_i_id4 fixed(10), OUT pp_t_id4 fixed(10),
OUT pp_i_id5 fixed(10), OUT pp_t_id5 fixed(10)) AS
BEGIN
if (C_ID = 0) then begin
  C_FName='';
  C_LName='';
end
else
SELECT c_fname, c_lname INTO :C_FName, :C_LName from dbt.customer where c_id=:C_ID;
CALL getPromoImages(:I_ID, :pp_i_id1, :pp_t_id1, :pp_i_id2, :pp_t_id2, :pp_i_id3, :pp_t_id3, :pp_i_id4, :pp_t_id4, :pp_i_id5, :pp_t_id5);
END;
