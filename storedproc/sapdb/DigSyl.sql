/
/*DROP DBPROC DigSyl;*/
/
CREATE DBPROC DigSyl(IN D INT, IN N INT, OUT Str varchar(64)) AS
  VAR base int; i int; digits int; start int;
BEGIN
set Str='';
set digits=0;
set base=D;
while base>0 do begin
  set digits=digits+1;
  set base=base DIV 10;
  end;
if digits>N then set n=digits;
set base=1;
set i=0;
while i<N-1 do begin
  set base=base*10;
  set i=i+1;
end;
set i=0;
while i<N do begin
  set digits=D DIV base;
  set start=digits*2+1;
  set Str=Str||SUBSTR('BAOGALRIRESEATULINNG', start, 2);
  set D=D MOD base;
  set base=base DIV 10;
  set i=i+1;
end;
END;
;
/
/
