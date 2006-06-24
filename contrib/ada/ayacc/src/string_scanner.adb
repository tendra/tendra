
-- Module       : string_scanner.ada
-- Component of : common_library
-- Version      : 1.2
-- Date         : 11/21/86  16:36:26
-- SCCS File    : disk21~/rschm/hasee/sccs/common_library/sccs/sxstring_scanner.ada

with String_Pkg;			use String_Pkg;
with Unchecked_Deallocation;

package body String_Scanner is

  SCCS_ID : constant String := "@(#) string_scanner.ada, Version 1.2";




White_Space   : constant string := " " & ASCII.HT;
Number_1      : constant string := "0123456789";
Number        : constant string := Number_1 & "_";
Quote         : constant string := """";
Ada_Id_1      : constant string := "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
Ada_Id        : constant string := Ada_Id_1 & Number;

procedure Free_Scanner is
	new Unchecked_Deallocation(Scan_Record, Scanner);
													pragma Page;
function Is_Valid(
    T : in Scanner
    ) return boolean is

begin

    return T /= null;

end Is_Valid;

function Make_Scanner(
    S : in String_Type
    ) return Scanner is

    T : Scanner := new Scan_Record;

begin

    T.text := String_Pkg.Make_Persistent(S);
    return T;

end Make_Scanner;

----------------------------------------------------------------

procedure Destroy_Scanner(
    T : in out Scanner
    ) is

begin

    if Is_Valid(T) then
	String_Pkg.Flush(T.text);
	Free_Scanner(T);
    end if;

end Destroy_Scanner;

----------------------------------------------------------------

function More(
    T : in Scanner
    ) return boolean is

begin

    if Is_Valid(T) then
	if T.index > String_Pkg.Length(T.text) then
	    return false;
	else
            return true;
	end if;
    else
	return false;
    end if;

end More;

----------------------------------------------------------------

function Get(
    T : in Scanner
    ) return character is

begin

    if not More(T) then
	raise Out_Of_Bounds;
    end if;
    return String_Pkg.Fetch(T.text, T.index);

end Get;

----------------------------------------------------------------

procedure Forward(
    T : in Scanner
    ) is

begin

    if Is_Valid(T) then
	if String_Pkg.Length(T.text) >= T.index then
	    T.index := T.index + 1;
	end if;
    end if;

end Forward;

----------------------------------------------------------------

procedure Backward(
    T : in Scanner
    ) is

begin

    if Is_Valid(T) then
	if T.index > 1 then
	    T.index := T.index - 1;
	end if;
    end if;

end Backward;

----------------------------------------------------------------

procedure Next(
    T : in     Scanner;
    C :    out character
    ) is

begin

    C := Get(T);
    Forward(T);

end Next;

----------------------------------------------------------------

function Position(
    T : in Scanner
    ) return positive is

begin

    if not More(T) then
	raise Out_Of_Bounds;
    end if;
    return T.index;

end Position;

----------------------------------------------------------------

function Get_String(
    T : in Scanner
    ) return String_Type is

begin

    if Is_Valid(T) then
	return String_Pkg.Make_Persistent(T.text);
    else
	return String_Pkg.Make_Persistent("");
    end if;

end Get_String;

----------------------------------------------------------------

function Get_Remainder(
    T : in Scanner
    ) return String_Type is

    S_Str : String_Type;

begin

    if More(T) then
	String_Pkg.Mark;
	S_Str := String_Pkg.Make_Persistent(
	String_Pkg.Substr(T.text,
			  T.index,
			  String_Pkg.Length(T.text) - T.index + 1));
	String_Pkg.Release;
    else
	S_Str := String_Pkg.Make_Persistent("");
    end if;
    return S_Str;

end Get_Remainder;

----------------------------------------------------------------

procedure Mark(
    T : in Scanner
    ) is

begin

    if Is_Valid(T) then
	if T.mark /= 0 then
	    raise Scanner_Already_Marked;
	else
	    T.mark := T.index;
	end if;
    end if;

end Mark;

----------------------------------------------------------------

procedure Restore(
    T : in Scanner
    ) is

begin

    if Is_Valid(T) then
	if T.mark /= 0 then
	    T.index := T.mark;
	    T.mark  := 0;
	end if;
    end if;

end Restore;
													pragma Page;
function Is_Any(
    T : in Scanner;
    Q : in string
    ) return boolean is

    N     : natural;

begin

    if not More(T) then
	return false;
    end if;
    String_Pkg.Mark;
    N := String_Pkg.Match_Any(T.text, Q, T.index);
    if N /= T.index then
	N := 0;
    end if;
    String_Pkg.Release;
    return N /= 0;

end Is_Any;
 													pragma Page;
procedure Scan_Any(
    T      : in     Scanner;
    Q      : in     string;
    Found  :    out boolean;
    Result : in out String_Type
    ) is

    S_Str : String_Type;
    N     : natural;

begin

    if Is_Any(T, Q) then
	N := String_Pkg.Match_None(T.text, Q, T.index);
	if N = 0 then
	    N := String_Pkg.Length(T.text) + 1;
	end if;
	Result  := Result & String_Pkg.Substr(T.text, T.index, N - T.index);
	T.index := N;	
	Found   := true;
    else
	Found := false;
    end if;

end Scan_Any;
													pragma Page;
function Quoted_String(
    T : in Scanner
    ) return integer is

    Count : integer := 0;
    I     : positive;
    N     : natural;

begin

    if not Is_Valid(T) then
	return Count;
    end if;
    I := T.index;
    while Is_Any(T, """") loop
	T.index := T.index + 1;
	if not More(T) then
	    T.index := I;
	    return 0;
	end if;
	String_Pkg.Mark;
	N := String_Pkg.Match_Any(T.text, """", T.index);
	String_Pkg.Release;
	if N = 0 then
	    T.index := I;
	    return 0;
	end if;
	T.index := N + 1;
    end loop;
    Count := T.index - I;
    T.index := I;
    return Count;

end Quoted_String;
													pragma Page;
function Enclosed_String(
    B : in character;
    E : in character;
    T : in Scanner
    ) return natural is

    Count : natural := 1;
    I     : positive;
    Inx_B : natural;
    Inx_E : natural;
    Depth : natural := 1;

begin

    if not Is_Any(T, B & "") then
	return 0;
    end if;
    I := T.index;
    Forward(T);
    while Depth /= 0 loop
	if not More(T) then
	    T.index := I;
	    return 0;
	end if;
	String_Pkg.Mark;
	Inx_B   := String_Pkg.Match_Any(T.text, B & "", T.index);
	Inx_E   := String_Pkg.Match_Any(T.text, E & "", T.index);
	String_Pkg.Release;
	if Inx_E = 0 then
	    T.index := I;
	    return 0;
	end if;
	if Inx_B /= 0 and then Inx_B < Inx_E then
	    Depth := Depth + 1;
	else
	    Inx_B := Inx_E;
	    Depth := Depth - 1;
	end if;
	T.index := Inx_B + 1;
    end loop;
    Count := T.index - I;
    T.index := I;
    return Count;

end Enclosed_String;
 													pragma Page;
function Is_Word(
    T : in Scanner
    ) return boolean is

begin

    if not More(T) then
	return false;
    else
	return not Is_Any(T, White_Space);
    end if;

end Is_Word;

----------------------------------------------------------------

procedure Scan_Word(
    T      : in     Scanner;
    Found  :    out boolean;
    Result :    out String_Type;
    Skip   : in     boolean := false
    ) is

    S_Str : String_Type;
    N     : natural;

begin

    if Skip then
	Skip_Space(T);
    end if;
    if Is_Word(T) then
	String_Pkg.Mark;
	N := String_Pkg.Match_Any(T.text, White_Space, T.index);
	if N = 0 then
	    N := String_Pkg.Length(T.text) + 1;
	end if;
	Result  := String_Pkg.Make_Persistent
		   (String_Pkg.Substr(T.text, T.index, N - T.index));
	T.index := N;	
	Found   := true;
	String_Pkg.Release;
    else
	Found   := false;
    end if;
    return;

end Scan_Word;
													pragma Page;
function Is_Number(
    T : in Scanner
    ) return boolean is

begin

    return Is_Any(T, Number_1);

end Is_Number;

----------------------------------------------------------------

procedure Scan_Number(
    T      : in     Scanner;
    Found  :    out boolean;
    Result :    out String_Type;
    Skip   : in     boolean := false
    ) is

    C     : character;
    S_Str : String_Type;

begin

    if Skip then
	Skip_Space(T);
    end if;
    if not Is_Number(T) then
	Found := false;
	return;
    end if;
    String_Pkg.Mark;
    while Is_Number(T) loop
	Scan_Any(T, Number_1, Found, S_Str);
	if More(T) then
	    C := Get(T);
	    if C = '_' then
		Forward(T);
		if Is_Number(T) then
		    S_Str := S_Str & "_";
		else
		    Backward(T);
		end if;
	    end if;
	end if;
    end loop;
    Result := String_Pkg.Make_Persistent(S_Str);
    String_Pkg.Release;

end Scan_Number;

----------------------------------------------------------------

procedure Scan_Number(
    T      : in     Scanner;
    Found  :    out boolean;
    Result :    out integer;
    Skip   : in     boolean := false
    ) is

    F     : boolean;
    S_Str : String_Type;

begin

    Scan_Number(T, F, S_Str, Skip);
    if F then
	Result := integer'value(String_Pkg.Value(S_Str));
    end if;
    Found := F;

end Scan_Number;
													pragma Page;
function Is_Signed_Number(
    T : in Scanner
    ) return boolean is

    I : positive;
    C : character;
    F : boolean;

begin

    if More(T) then
	I := T.index;
	C := Get(T);
	if C = '+' or C = '-' then
	    T.index := T.index + 1;
	end if;
	F := Is_Any(T, Number_1);
	T.index := I;
	return F;
    else
	return false;
    end if;

end Is_Signed_Number;

----------------------------------------------------------------

procedure Scan_Signed_Number(
    T      : in     Scanner;
    Found  :    out boolean;
    Result :    out String_Type;
    Skip   : in     boolean := false
    ) is

    C     : character;
    S_Str : String_Type;

begin

    if Skip then
	Skip_Space(T);
    end if;
    if Is_Signed_Number(T) then
	C := Get(T);
	if C = '+' or C = '-' then
	    Forward(T);
	end if;
	Scan_Number(T, Found, S_Str);
	String_Pkg.Mark;
	if C = '+' or C = '-' then
	    Result := String_Pkg.Make_Persistent(("" & C) & S_Str);
	else
	    Result := String_Pkg.Make_Persistent(S_Str);
	end if;
	String_Pkg.Release;
	String_Pkg.Flush(S_Str);
    else
	Found := false;
    end if;

end Scan_Signed_Number;

----------------------------------------------------------------

procedure Scan_Signed_Number(
    T      : in     Scanner;
    Found  :    out boolean;
    Result :    out integer;
    Skip   : in     boolean := false
    ) is

    F     : boolean;
    S_Str : String_Type;

begin

    Scan_Signed_Number(T, F, S_Str, Skip);
    if F then
	Result := integer'value(String_Pkg.Value(S_Str));
    end if;
    Found := F;

end Scan_Signed_Number;
													pragma Page;
function Is_Space(
    T : in Scanner
    ) return boolean is

begin

    return Is_Any(T, White_Space);

end Is_Space;

----------------------------------------------------------------

procedure Scan_Space(
    T      : in     Scanner;
    Found  :    out boolean;
    Result :    out String_Type
    ) is

    S_Str : String_Type;

begin

    String_Pkg.Mark;
    Scan_Any(T, White_Space, Found, S_Str);
    Result := String_Pkg.Make_Persistent(S_Str);
    String_Pkg.Release;

end Scan_Space;

----------------------------------------------------------------

procedure Skip_Space(
    T : in Scanner
    ) is

    S_Str : String_Type;
    Found : boolean;

begin

    String_Pkg.Mark;
    Scan_Any(T, White_Space, Found, S_Str);
    String_Pkg.Release;

end Skip_Space;
													pragma Page;
function Is_Ada_Id(
    T : in Scanner
    ) return boolean is

begin

    return Is_Any(T, Ada_Id_1);

end Is_Ada_Id;

----------------------------------------------------------------

procedure Scan_Ada_Id(
    T      : in     Scanner;
    Found  :    out boolean;
    Result :    out String_Type;
    Skip   : in     boolean := false
    ) is

    C     : character;
    F     : boolean;
    S_Str : String_Type;

begin

    if Skip then
	Skip_Space(T);
    end if;
    if Is_Ada_Id(T) then
	String_Pkg.Mark;
	Next(T, C);
	Scan_Any(T, Ada_Id, F, S_Str);
	Result := String_Pkg.Make_Persistent(("" & C) & S_Str);
	Found := true;
	String_Pkg.Release;
    else
	Found := false;
    end if;

end Scan_Ada_Id;
													pragma Page;
function Is_Quoted(
    T : in Scanner
    ) return boolean is

begin

    if Quoted_String(T) = 0 then
	return false;
    else
	return true;
    end if;

end Is_Quoted;

----------------------------------------------------------------

procedure Scan_Quoted(
    T      : in     Scanner;
    Found  :    out boolean;
    Result :    out String_Type;
    Skip   : in     boolean := false
    ) is

    Count : integer;

begin

    if Skip then
	Skip_Space(T);
    end if;
    Count := Quoted_String(T);
    if Count /= 0 then
	Count := Count - 2;
	T.index := T.index + 1;
	if Count /= 0 then
	    String_Pkg.Mark;
	    Result := String_Pkg.Make_Persistent
		      (String_Pkg.Substr(T.text, T.index, positive(Count)));
	    String_Pkg.Release;
	else
	    Result := String_Pkg.Make_Persistent("");
	end if;
	T.index := T.index + Count + 1;
	Found := true;
    else
	Found := false;
    end if;

end Scan_Quoted;
													pragma Page;
function Is_Enclosed(
    B : in character;
    E : in character;
    T : in Scanner
    ) return boolean is

begin

    if Enclosed_String(B, E, T) = 0 then
	return false;
    else
	return true;
    end if;

end Is_Enclosed;

----------------------------------------------------------------

procedure Scan_Enclosed(
    B      : in     character;
    E      : in     character;
    T      : in     Scanner;
    Found  :    out boolean;
    Result :    out String_Type;
    Skip   : in     boolean := false
    ) is

    Count : natural;

begin

    if Skip then
	Skip_Space(T);
    end if;
    Count := Enclosed_String(B, E, T);
    if Count /= 0 then
	Count := Count - 2;
	T.index := T.index + 1;
	if Count /= 0 then
	    String_Pkg.Mark;
	    Result := String_Pkg.Make_Persistent(String_Pkg.Substr(T.text, T.index, positive(Count)));
	    String_Pkg.Release;
	else
	    Result := String_Pkg.Make_Persistent("");
	end if;
	T.index := T.index + Count + 1;
	Found := true;
    else
	Found := false;
    end if;

end Scan_Enclosed;
													pragma Page;
function Is_Sequence(
    Chars  : in String_Type;
    T      : in Scanner
    ) return boolean is

begin

    return Is_Any(T, String_Pkg.Value(Chars));

end Is_Sequence;

----------------------------------------------------------------

function Is_Sequence(
    Chars  : in string;
    T      : in Scanner
    ) return boolean is

begin

    return Is_Any(T, Chars);

end Is_Sequence;

----------------------------------------------------------------

procedure Scan_Sequence(
    Chars  : in     String_Type;
    T      : in     Scanner;
    Found  :    out boolean;
    Result :    out String_Type;
    Skip   : in     boolean := false
    ) is

    I     : positive;
    Count : integer := 0;

begin

    if Skip then
	Skip_Space(T);
    end if;
    if not Is_Valid(T) then
	Found := false;
	return;
    end if;
    I := T.index;
    while Is_Any(T, Value(Chars)) loop
	Forward(T);
	Count := Count + 1;
    end loop;
    if Count /= 0 then
	String_Pkg.Mark;
	Result := String_Pkg.Make_Persistent
		  (String_Pkg.Substr(T.text, I, positive(Count)));
	Found  := true;
	String_Pkg.Release;
    else
	Found := false;
    end if;

end Scan_Sequence;

----------------------------------------------------------------

procedure Scan_Sequence(
    Chars  : in     string;
    T      : in     Scanner;
    Found  :    out boolean;
    Result :    out String_Type;
    Skip   : in     boolean := false
    ) is

begin

    String_Pkg.Mark;
    Scan_Sequence(String_Pkg.Create(Chars), T, Found, Result, Skip);
    String_Pkg.Release;

end Scan_Sequence;
													pragma Page;
function Is_Not_Sequence(
    Chars  : in String_Type;
    T      : in Scanner
    ) return boolean is

    N : natural;

begin

    if not Is_Valid(T) then
	return false;
    end if;
    String_Pkg.Mark;
    N := String_Pkg.Match_Any(T.text, Chars, T.index);
    if N = T.index then
	N := 0;
    end if;
    String_Pkg.Release;
    return N /= 0;

end Is_Not_Sequence;

----------------------------------------------------------------

function Is_Not_Sequence(
    Chars  : in string;
    T      : in Scanner
    ) return boolean is

begin

    return Is_Not_Sequence(String_Pkg.Create(Chars), T);

end Is_Not_Sequence;

----------------------------------------------------------------

procedure Scan_Not_Sequence(
    Chars  : in     string;
    T      : in     Scanner;
    Found  :    out boolean;
    Result :    out String_Type;
    Skip   : in     boolean := false
    ) is

    N     : natural;

begin

    if Skip then
	Skip_Space(T);
    end if;
    if Is_Not_Sequence(Chars, T) then
	String_Pkg.Mark;
	N := String_Pkg.Match_Any(T.text, Chars, T.index);
	Result := String_Pkg.Make_Persistent
		  (String_Pkg.Substr(T.text, T.index, N - T.index));
	T.index := N;
	Found   := true;
	String_Pkg.Release;
    else
	Found := false;
    end if;

end Scan_Not_Sequence;

----------------------------------------------------------------

procedure Scan_Not_Sequence(
    Chars  : in     String_Type;
    T      : in     Scanner;
    Found  :    out boolean;
    Result :    out String_Type;
    Skip   : in     boolean := false
    ) is

begin

    Scan_Not_Sequence(String_Pkg.Value(Chars), T, Found, Result, Skip);

end Scan_Not_Sequence;
													pragma Page;
function Is_Literal(
    Chars  : in String_Type;
    T      : in Scanner
    ) return boolean is

    N : natural;

begin

    if not Is_Valid(T) then
	return false;
    end if;
    String_Pkg.Mark;
    N := String_Pkg.Match_S(T.text, Chars, T.index);
    if N /= T.index then
	N := 0;
    end if;
    String_Pkg.Release;
    return N /= 0;

end Is_Literal;

----------------------------------------------------------------

function Is_Literal(
    Chars  : in string;
    T      : in Scanner
    ) return boolean is

    Found : boolean;

begin

    String_Pkg.Mark;
    Found := Is_Literal(String_Pkg.Create(Chars), T);
    String_Pkg.Release;
    return Found;

end Is_Literal;

----------------------------------------------------------------

procedure Scan_Literal(
    Chars  : in     String_Type;
    T      : in     Scanner;
    Found  :    out boolean;
    Skip   : in     boolean := false
    ) is

begin

    if Skip then
	Skip_Space(T);
    end if;
    if Is_Literal(Chars, T) then
	T.index := T.index + String_Pkg.Length(Chars);
	Found   := true;
    else
	Found   := false;
    end if;

end Scan_Literal;

----------------------------------------------------------------

procedure Scan_Literal(
    Chars  : in     string;
    T      : in     Scanner;
    Found  :    out boolean;
    Skip   : in     boolean := false
    ) is

begin

    String_Pkg.Mark;
    Scan_Literal(String_Pkg.Create(Chars), T, Found, Skip);
    String_Pkg.Release;

end Scan_Literal;
													pragma Page;
function Is_Not_Literal(
    Chars : in string;
    T     : in Scanner
    ) return boolean is

    N     : natural;

begin

    if not Is_Valid(T) then
	return false;
    end if;
    String_Pkg.Mark;
    N := String_Pkg.Match_S(T.text, Chars, T.index);
    if N = T.index then
	N := 0;
    end if;
    String_Pkg.Release;
    return N /= 0;

end Is_Not_Literal;

----------------------------------------------------------------

function Is_Not_Literal(
    Chars : in String_Type;
    T     : in Scanner
    ) return boolean is

begin

    if not More(T) then
	return false;
    end if;
    return Is_Not_Literal(String_Pkg.Value(Chars), T);

end Is_Not_Literal;

----------------------------------------------------------------

procedure Scan_Not_Literal(
    Chars  : in     string;
    T      : in     Scanner;
    Found  :    out boolean;
    Result :    out String_Type;
    Skip   : in     boolean := false
    ) is

    N : natural;

begin

    if Skip then
	Skip_Space(T);
    end if;
    if Is_Not_Literal(Chars, T) then
	String_Pkg.Mark;
	N := String_Pkg.Match_S(T.text, Chars, T.index);
	Result := String_Pkg.Make_Persistent(String_Pkg.Substr(T.text, T.index, N - T.index));
	T.index := N;
	Found   := true;
	String_Pkg.Release;
    else
	Found := false;
	return;
    end if;

end Scan_Not_Literal;

----------------------------------------------------------------

procedure Scan_Not_Literal(
    Chars  : in     String_Type;
    T      : in     Scanner;
    Found  :    out boolean;
    Result :    out String_Type;
    Skip   : in     boolean := false
    ) is

begin

    Scan_Not_Literal(String_Pkg.Value(Chars), T, Found, Result, Skip);

end Scan_Not_Literal;


end String_Scanner;
													pragma Page;
