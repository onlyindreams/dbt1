--
--
-- This file is released under the terms of the Artistic License.  Please see
-- the file LICENSE, included in this package, for details.
--
-- Copyright (C) 2002 Open Source Development Lab, Inc.
-- History: 
-- July-2003: Created by Satoshi Nagayasu
--
CREATE OR REPLACE FUNCTION home (
  numeric(10),
  numeric(10)
) RETURNS SETOF RECORD AS '
  DECLARE
    _C_ID ALIAS FOR $1;
    _I_ID ALIAS FOR $2;

    _C_FName char(15);
    _C_LName char(15);
    pp_i_id1 numeric(10);
    pp_t_id1 numeric(10);
    pp_i_id2 numeric(10);
    pp_t_id2 numeric(10);
    pp_i_id3 numeric(10);
    pp_t_id3 numeric(10);
    pp_i_id4 numeric(10);
    pp_t_id4 numeric(10);
    pp_i_id5 numeric(10);
    pp_t_id5 numeric(10);

    rec record;
  BEGIN
	SELECT c_fname,c_lname
	INTO _C_FName,_C_LName
	FROM customer
	WHERE c_id=_C_ID;   
	
	SELECT * INTO 
	       pp_i_id1, pp_t_id1,
	       pp_i_id2, pp_t_id2,
	       pp_i_id3, pp_t_id3,
	       pp_i_id4, pp_t_id4,
	       pp_i_id5, pp_t_id5
	       FROM getPromoImages(_I_ID)
	       AS l( I_ID1 numeric(10),
		  I_T1 numeric(10),
		  I_ID2 numeric(10),
		  I_T2 numeric(10),
		  I_ID3 numeric(10),
		  I_T3 numeric(10),
		  I_ID4 numeric(10),
		  I_T4 numeric(10),
                  I_ID5 numeric(10),
                  I_T5 numeric(10) );
	SELECT 	_C_FName::char(15),
		_C_LName::char(15),
	       	pp_i_id1::numeric(10),
 		pp_t_id1::numeric(10),
    		pp_i_id2::numeric(10),
    		pp_t_id2::numeric(10),
    		pp_i_id3::numeric(10),
    		pp_t_id3::numeric(10),
    		pp_i_id4::numeric(10),
    		pp_t_id4::numeric(10),
    		pp_i_id5::numeric(10),
    		pp_t_id5::numeric(10)
	INTO rec;

	RETURN NEXT rec;
	RETURN;
  END;
' LANGUAGE 'plpgsql';
commit;

-- Usage:
-- 
-- SELECT * FROM (
--    C_ID numeric(10),
--    I_ID numeric(10),
-- )
-- AS l(
--    C_FName char(15),
--    C_LName char(15),
--    pp_i_id1 numeric(10),
--    pp_t_id1 numeric(10),
--    pp_i_id2 numeric(10),
--    pp_t_id2 numeric(10),
--    pp_i_id3 numeric(10),
--    pp_t_id3 numeric(10),
--    pp_i_id4 numeric(10),
--    pp_t_id4 numeric(10),
--    pp_i_id5 numeric(10),
--    pp_t_id5 numeric(10),
--);

