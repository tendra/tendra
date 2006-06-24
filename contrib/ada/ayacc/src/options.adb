
package body Options is

  SCCS_ID : constant String := "@(#) options.ada, Version 1.2";



  Rcs_ID : constant String := "$Header: options.a,v 0.1 86/04/01 15:08:15 ada Exp $";

    Verbose_Option          : Boolean := False;
    Verbose_Conflict_Option : Boolean := False;
    Debug_Option            : Boolean := False;
    Interface_to_C_Option   : Boolean := False;
    Summary_Option 	    : Boolean := False;
    Loud_Option		    : Boolean := False;
-- UMASS CODES :
    Error_Recovery_Extension_Option : Boolean := False;
-- END OF UMASS CODES.

    procedure Set_Options(S: in String) is
    begin
	for I in S'First..S'Last loop
	    case S(I) is
		when 'v' | 'V' =>
		    Verbose_Option := True;
		when 'c' | 'C' =>
		    Verbose_Conflict_Option := True;
		when 'd' | 'D' =>
		    Debug_Option := True;
		when 'i' | 'I' =>
		    Interface_to_C_Option := True;
		when 's' | 'S' =>
		    Summary_Option := True;
		when 'l' | 'L' =>
		    Loud_Option := True;
-- UMASS CODES :
                when 'e' | 'E' =>
                    Error_Recovery_Extension_Option := True;
-- END OF UMASS CODES.
		when others =>
		    raise Illegal_Option;
	    end case;
	end loop;
    end Set_Options;

    function Verbose return Boolean is
    begin
	return Verbose_Option;
    end;

    function Verbose_Conflict return Boolean is
    begin
	return Verbose_Conflict_Option;
    end;

    function Debug return Boolean is
    begin
	return Debug_Option;
    end;

    function Interface_to_C return Boolean is
    begin
	return Interface_to_C_Option;
    end;

    function Summary return Boolean is
    begin
	return Summary_Option;
    end;

    function Loud return Boolean is
    begin
	return Loud_Option;
    end;

-- UMASS CODES :
    function Error_Recovery_Extension return Boolean is
    begin
        return Error_Recovery_Extension_Option;
    end;
-- END OF UMASS CODES.
end Options;
