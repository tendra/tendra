
-- Module       : string_scanner_.ada
-- Component of : common_library
-- Version      : 1.2
-- Date         : 11/21/86  16:37:08
-- SCCS File    : disk21~/rschm/hasee/sccs/common_library/sccs/sxstring_scanner_.ada

with String_Pkg;			use String_Pkg;

package String_Scanner is

--| Functions for scanning tokens from strings.
													pragma Page;
--| Overview
--| This package provides a set of functions used to scan tokens from
--| strings.  After the function make_Scanner is called to convert a string
--| into a string Scanner, the following functions may be called to scan
--| various tokens from the string:
--|-
--| Make_Scanner	Given a string returns a Scanner
--| Destroy_Scanner	Free storage used by Scanner
--| More		Return TRUE iff unscanned characters remain
--| Forward             Bump the Scanner
--| Backward		Bump back the Scanner
--| Get			Return character 
--| Next		Return character and bump the Scanner
--| Get_String		Return String_Type in Scanner
--| Get_Remainder	Return String_Type in Scanner from current Index
--| Mark		Mark the current Index for Restore 
--| Restore		Restore the previously marked Index
--| Position		Return the current position of the Scanner
--| Is_Word		Return TRUE iff Scanner is at a non-blank character
--| Scan_Word		Return sequence of non blank characters
--| Is_Number		Return TRUE iff Scanner is at a digit
--| Scan_Number (2)	Return sequence of decimal digits
--| Is_Signed_Number	Return TRUE iff Scanner is at a digit or sign
--| Scan_Signed_Number (2)
--|			sequence of decimal digits with optional sign (+/-)
--| Is_Space		Return TRUE iff Scanner is at a space or tab
--| Scan_Space		Return sequence of spaces or tabs
--| Skip_Space		Advance Scanner past white space
--| Is_Ada_Id		Return TRUE iff Scanner is at first character of ada id
--| Scan_Ada_Id		Scan an Ada identifier
--| Is_Quoted		Return TRUE iff Scanner is at a double quote
--| Scan_Quoted		Scan quoted string, embedded quotes doubled
--| Is_Enclosed		Return TRUE iff Scanner is at an enclosing character
--| Scan_Enclosed	Scan enclosed string, embedded enclosing character doubled
--| Is_Sequence		Return TRUE iff Scanner is at some character in sequence
--| Scan_Sequence	Scan user specified sequence of chars
--| Is_Not_Sequence	Return TRUE iff Scanner is not at the characters in sequence
--| Scan_Not_Sequence	Scan string up to but not including a given sequence of chars
--| Is_Literal	        Return TRUE iff Scanner is at literal
--| Scan_Literal	Scan user specified literal
--| Is_Not_Literal	Return TRUE iff Scanner is not a given literal
--| Scan_Not_Literal	Scan string up to but not including a given literal
--|+

----------------------------------------------------------------

Out_Of_Bounds : exception;	--| Raised when a operation is attempted on a
				--| Scanner that has passed the end
Scanner_Already_Marked : exception;
				--| Raised when a Mark is attemped on a Scanner
				--| that has already been marked

----------------------------------------------------------------

type Scanner is private;	--| Scanner type

----------------------------------------------------------------
													pragma Page;
function Make_Scanner(		--| Construct a Scanner from S.
    S : in String_Type		--| String to be scanned.
    ) return Scanner;

--| Effects: Construct a Scanner from S.
--| N/A: Raises, Modifies, Errors

----------------------------------------------------------------

procedure Destroy_Scanner(	--| Free Scanner storage
    T : in out Scanner		--| Scanner to be freed
    );

--| Effects: Free space occupied by the Scanner.
--| N/A: Raises, Modifies, Errors

----------------------------------------------------------------

function More(			--| Check if Scanner is exhausted
    T : in Scanner		--| Scanner to check
    ) return boolean;

--| Effects: Return TRUE iff additional characters remain to be scanned.
--| N/A: Raises, Modifies, Errors

----------------------------------------------------------------

procedure Forward(		--| Bump scanner
    T : in Scanner		--| Scanner
    );

--| Effects: Update the scanner position.
--| N/A: Raises, Modifies, Errors

----------------------------------------------------------------

procedure Backward(		--| Bump back scanner
    T : in Scanner		--| Scanner
    );

--| Effects: Update the scanner position.
--| N/A: Raises, Modifies, Errors

----------------------------------------------------------------

function Get(			--| Return character
    T : in     Scanner		--| Scanner to check
    ) return character;

--| Raises: Out_Of_Bounds
--| Effects: Return character at the current Scanner position.
--| The scanner position remains unchanged.
--| N/A: Modifies, Errors

----------------------------------------------------------------

procedure Next(			--| Return character and bump scanner
    T : in     Scanner;		--| Scanner to check
    C :    out character	--| Character to be returned
    );

--| Raises: Out_Of_Bounds
--| Effects: Return character at the current Scanner position and update
--| the position.
--| N/A: Modifies, Errors

----------------------------------------------------------------

function Position(		--| Return current Scanner position
    T : in Scanner		--| Scanner to check
    ) return positive;

--| Raises: Out_Of_Bounds
--| Effects: Return a positive integer indicating the current Scanner position,
--| N/A: Modifies, Errors

----------------------------------------------------------------

function Get_String(		--| Return contents of Scanner
    T : in Scanner		--| Scanner
    ) return String_Type;

--| Effects: Return a String_Type corresponding to the contents of the Scanner
--| N/A: Raises, Modifies, Errors

----------------------------------------------------------------

function Get_Remainder(		--| Return contents of Scanner from index
    T : in Scanner
    ) return String_Type;

--| Effects: Return a String_Type starting at the current index of the Scanner
--| N/A: Raises, Modifies, Errors

----------------------------------------------------------------

procedure Mark(
    T : in Scanner
    );

--| Raises: Scanner_Already_Marked
--| Effects: Mark the current index for possible future use
--| N/A: Modifies, Errors

----------------------------------------------------------------

procedure Restore(
    T : in Scanner
    );

--| Effects: Restore the index to the previously marked value
--| N/A: Raises, Modifies, Errors

----------------------------------------------------------------

													pragma Page;
function Is_Word(		--| Check if Scanner is at the start of a word.
    T : in Scanner		--| Scanner to check
    ) return boolean;

--| Effects: Return TRUE iff Scanner is at the start of a word.
--| N/A: Raises, Modifies, Errors

----------------------------------------------------------------

procedure Scan_word(		--| Scan sequence of non blank characters
    T      : in     Scanner;	--| String to be scanned
    Found  :    out boolean;	--| TRUE iff a word found
    Result :    out String_Type;--| Word scanned from string
    Skip   : in     boolean := false
				--| Skip white spaces before scan
    );

--| Effects: Scan T for a sequence of non blank 
--| characters.  If at least one is found, return Found => TRUE, 
--| Result => <the characters>.
--| Otherwise return Found => FALSE and Result is unpredictable.

--| N/A: Raises, Modifies, Errors
													pragma Page;
function Is_Number(		--| Return TRUE iff Scanner is at a decimal digit
    T : in Scanner		--| The string being scanned
    ) return boolean;

--| Effects: Return TRUE iff Scan_Number would return a non-null string.
--| N/A: Raises, Modifies, Errors

----------------------------------------------------------------

procedure Scan_Number(		--| Scan sequence of digits
    T      : in     Scanner;	--| String to be scanned
    Found  :    out boolean;	--| TRUE iff one or more digits found
    Result :    out String_Type;--| Number scanned from string
    Skip   : in     boolean := false
				--| Skip white spaces before scan
    );

--| Effects: Scan T for a sequence of digits.
--| If at least one is found, return Found => TRUE, Result => <the digits>.
--| Otherwise return Found => FALSE and Result is unpredictable.

--| Modifies: Raises, Modifies, Errors

----------------------------------------------------------------

procedure Scan_Number(		--| Scan sequence of digits
    T      : in     Scanner;	--| String to be scanned
    Found  :    out boolean;	--| TRUE iff one or more digits found
    Result :    out integer;	--| Number scanned from string
    Skip   : in     boolean := false
				--| Skip white spaces before scan
    );

--| Effects: Scan T for a sequence of digits.
--| If at least one is found, return Found => TRUE, Result => <the digits>.
--| Otherwise return Found => FALSE and Result is unpredictable.

--| Modifies: Raises, Modifies, Errors
													pragma Page;
function Is_Signed_Number(	--| Check if Scanner is at a decimal digit or
				--| sign (+/-)
    T : in Scanner		--| The string being scanned
    ) return boolean;

--| Effects: Return TRUE iff Scan_Signed_Number would return a non-null
--| string.

--| N/A: Raises, Modifies, Errors

----------------------------------------------------------------

procedure Scan_Signed_Number(	--| Scan signed sequence of digits 
    T      : in     Scanner;	--| String to be scanned
    Found  :    out boolean;	--| TRUE iff one or more digits found
    Result :    out String_Type;--| Number scanned from string
    Skip   : in     boolean := false
				--| Skip white spaces before scan
    );

--| Effects: Scan T for a sequence of digits preceeded with optional sign.
--| If at least one digit is found, return Found => TRUE, 
--| Result => <the digits>.
--| Otherwise return Found => FALSE and Result is unpredictable.

--| Modifies: Raises, Modifies, Errors

----------------------------------------------------------------

procedure Scan_Signed_Number(	--| Scan signed sequence of digits 
    T      : in     Scanner;	--| String to be scanned
    Found  :    out boolean;	--| TRUE iff one or more digits found
    Result :    out integer;	--| Number scanned from string
    Skip   : in     boolean := false
				--| Skip white spaces before scan
    );

--| Effects: Scan T for a sequence of digits preceeded with optional sign.
--| If at least one digit is found, return Found => TRUE, 
--| Result => <the digits>.
--| Otherwise return Found => FALSE and Result is unpredictable.

--| Modifies: Raises, Modifies, Errors
													pragma Page;
function Is_Space(		--| Check if T is at a space or tab
    T : in Scanner		--| The string being scanned
    ) return boolean;

--| Effects: Return TRUE iff Scan_Space would return a non-null string.
--| Modifies: Raises, Modifies, Errors

----------------------------------------------------------------

procedure Scan_Space(		--| Scan sequence of white space characters
    T      : in     Scanner;	--| String to be scanned
    Found  :    out boolean;	--| TRUE iff space found
    Result :    out String_Type	--| Spaces scanned from string
    );

--| Effects: Scan T past all white space (spaces
--| and tabs.  If at least one is found, return Found => TRUE,
--| Result => <the characters>.
--| Otherwise return Found => FALSE and Result is unpredictable.

--| Modifies: Raises, Modifies, Errors

----------------------------------------------------------------

procedure Skip_Space(		--| Skip white space
    T : in Scanner		--| String to be scanned
    );

--| Effects: Scan T past all white space (spaces and tabs).  
--| Modifies: Raises, Modifies, Errors
													pragma Page;
function Is_Ada_Id(		--| Check if T is at an Ada identifier
    T : in Scanner		--| The string being scanned
    ) return boolean;

--| Effects: Return TRUE iff Scan_Ada_Id would return a non-null string.
--| Modifies: Raises, Modifies, Errors

----------------------------------------------------------------

procedure Scan_Ada_Id(		--| Scan Ada identifier
    T      : in     Scanner;	--| String to be scanned
    Found  :    out boolean;	--| TRUE iff an Ada identifier found
    Result :    out String_Type;--| Identifier scanned from string
    Skip   : in     boolean := false
				--| Skip white spaces before scan
    );

--| Effects: Scan T for a valid Ada identifier.
--| If one is found, return Found => TRUE, Result => <the characters>.
--| Otherwise return Found => FALSE and Result is unpredictable.

--| Modifies: Raises, Modifies, Errors
													pragma Page;
function Is_Quoted(		--| Check if T is at a double quote
    T : in Scanner		--| The string being scanned
    ) return boolean;

--| Effects: Return TRUE iff T is at a quoted string (eg. ... "Hello" ...).
--| Modifies: Raises, Modifies, Errors

----------------------------------------------------------------

procedure Scan_Quoted(		--| Scan a quoted string
    T      : in     Scanner;	--| String to be scanned
    Found  :    out boolean;	--| TRUE iff a quoted string found
    Result :    out String_Type;--| Quoted string scanned from string
    Skip   : in     boolean := false
				--| Skip white spaces before scan
    );

--| Effects: Scan at T for an opening quote
--| followed by a sequence of characters and ending with a closing
--| quote.  If successful, return Found => TRUE, Result => <the characters>.
--| Otherwise return Found => FALSE and Result is unpredictable.
--| A pair of quotes within the quoted string is converted to a single quote.
--| The outer quotes are stripped. 

--| Modifies: Raises, Modifies, Errors
													pragma Page;
function Is_Enclosed(		--| Check if T is at an enclosing character
    B : in character;		--| Enclosing open character
    E : in character;		--| Enclosing close character
    T : in Scanner		--| The string being scanned
    ) return boolean;

--| Effects: Return TRUE iff T as encosed by B and E (eg. ... [ABC] ...).
--| Modifies: Raises, Modifies, Errors

----------------------------------------------------------------

procedure Scan_Enclosed(	--| Scan an enclosed string
    B      : in character;	--| Enclosing open character
    E      : in character;	--| Enclosing close character
    T      : in     Scanner;	--| String to be scanned
    Found  :    out boolean;	--| TRUE iff a quoted string found
    Result :    out String_Type;--| Quoted string scanned from string
    Skip   : in     boolean := false
				--| Skip white spaces before scan
    );

--| Effects: Scan at T for an enclosing character
--| followed by a sequence of characters and ending with an enclosing character.
--| If successful, return Found => TRUE, Result => <the characters>.
--| Otherwise return Found => FALSE and Result is unpredictable.
--| The enclosing characters are stripped. 

--| Modifies: Raises, Modifies, Errors
													pragma Page;
function Is_Sequence(		--| Check if T is at some sequence characters 
    Chars : in String_Type;	--| Characters to be scanned
    T     : in Scanner		--| The string being scanned
    ) return boolean;

--| Effects: Return TRUE iff T is at some character of Chars.
--| Modifies: Raises, Modifies, Errors

----------------------------------------------------------------

function Is_Sequence(		--| Check if T is at some sequence characters 
    Chars : in string;		--| Characters to be scanned
    T     : in Scanner		--| The string being scanned
    ) return boolean;

--| Effects: Return TRUE iff T is at some character of Chars.
--| Modifies: Raises, Modifies, Errors

----------------------------------------------------------------

procedure Scan_Sequence(	--| Scan arbitrary sequence of characters
    Chars  : in     String_Type;--| Characters that should be scanned
    T      : in     Scanner;	--| String to be scanned
    Found  :    out boolean;	--| TRUE iff a sequence found
    Result :    out String_Type;--| Sequence scanned from string
    Skip   : in     boolean := false
				--| Skip white spaces before scan
    );

--| Effects: Scan T for a sequence of characters C such that C appears in 
--| Char.  If at least one is found, return Found => TRUE, 
--| Result => <the characters>.
--| Otherwise return Found => FALSE and Result is unpredictable.

--| Modifies: Raises, Modifies, Errors

--| Notes:
--| Scan_Sequence("0123456789", S, Index, Found, Result)
--| is equivalent to Scan_Number(S, Index, Found, Result)
--| but is less efficient.

----------------------------------------------------------------

procedure Scan_Sequence(	--| Scan arbitrary sequence of characters
    Chars  : in     string;	--| Characters that should be scanned
    T      : in     Scanner;	--| String to be scanned
    Found  :    out boolean;	--| TRUE iff a sequence found
    Result :    out String_Type;--| Sequence scanned from string
    Skip   : in     boolean := false
				--| Skip white spaces before scan
    );

--| Effects: Scan T for a sequence of characters C such that C appears in 
--| Char.  If at least one is found, return Found => TRUE, 
--| Result => <the characters>.
--| Otherwise return Found => FALSE and Result is unpredictable.

--| Modifies: Raises, Modifies, Errors

--| Notes:
--| Scan_Sequence("0123456789", S, Index, Found, Result)
--| is equivalent to Scan_Number(S, Index, Found, Result)
--| but is less efficient.
													pragma Page;
function Is_Not_Sequence(	--| Check if T is not at some seuqnce of character 
    Chars : in String_Type;	--| Characters to be scanned
    T     : in Scanner		--| The string being scanned
    ) return boolean;

--| Effects: Return TRUE iff T is not at some character of Chars.
--| Modifies: Raises, Modifies, Errors

----------------------------------------------------------------

function Is_Not_Sequence(	--| Check if T is at some sequence of characters 
    Chars : in string;		--| Characters to be scanned
    T     : in Scanner		--| The string being scanned
    ) return boolean;

--| Effects: Return TRUE iff T is not at some character of Chars.
--| Modifies: Raises, Modifies, Errors

----------------------------------------------------------------

procedure Scan_Not_Sequence(	--| Scan arbitrary sequence of characters
    Chars  : in     String_Type;--| Characters that should be scanned
    T      : in     Scanner;	--| String to be scanned
    Found  :    out boolean;	--| TRUE iff a sequence found
    Result :    out String_Type;--| Sequence scanned from string
    Skip   : in     boolean := false
				--| Skip white spaces before scan
    );

--| Effects: Scan T for a sequence of characters C such that C does not appear
--| in Chars.  If at least one such C is found, return Found => TRUE, 
--| Result => <the characters>.
--| Otherwise return Found => FALSE and Result is unpredictable.

--| Modifies: Raises, Modifies, Errors

----------------------------------------------------------------

procedure Scan_Not_Sequence(	--| Scan arbitrary sequence of characters
    Chars  : in     string;	--| Characters that should be scanned
    T      : in     Scanner;	--| String to be scanned
    Found  :    out boolean;	--| TRUE iff a sequence found
    Result :    out String_Type;--| Sequence scanned from string
    Skip   : in     boolean := false
				--| Skip white spaces before scan
    );

--| Effects: Scan T for a sequence of characters C such that C does not appear
--| in Chars.  If at least one such C is found, return Found => TRUE, 
--| Result => <the characters>.
--| Otherwise return Found => FALSE and Result is unpredictable.

--| Modifies: Raises, Modifies, Errors
													pragma Page;
function Is_Literal(		--| Check if T is at literal Chars
    Chars : in String_Type;	--| Characters to be scanned
    T     : in Scanner		--| The string being scanned
    ) return boolean;

--| Effects: Return TRUE iff T is at literal Chars.
--| Modifies: Raises, Modifies, Errors

----------------------------------------------------------------

function Is_Literal(		--| Check if T is at literal Chars
    Chars : in string;		--| Characters to be scanned
    T     : in Scanner		--| The string being scanned
    ) return boolean;

--| Effects: Return TRUE iff T is at literal Chars.
--| Modifies: Raises, Modifies, Errors

----------------------------------------------------------------

procedure Scan_Literal(		--| Scan arbitrary literal
    Chars  : in     String_Type;--| Literal that should be scanned
    T      : in     Scanner;	--| String to be scanned
    Found  :    out boolean;	--| TRUE iff a sequence found
    Skip   : in     boolean := false
				--| Skip white spaces before scan
    );

--| Effects: Scan T for a litral Chars such that Char matches the sequence
--| of characters in T.  If found, return Found => TRUE, 
--| Otherwise return Found => FALSE

--| Modifies: Raises, Modifies, Errors

----------------------------------------------------------------

procedure Scan_Literal(		--| Scan arbitrary literal
    Chars  : in     string;	--| Literal that should be scanned
    T      : in     Scanner;	--| String to be scanned
    Found  :    out boolean;	--| TRUE iff a sequence found
    Skip   : in     boolean := false
				--| Skip white spaces before scan
    );

--| Effects: Scan T for a litral Chars such that Char matches the sequence
--| of characters in T.  If found, return Found => TRUE, 
--| Otherwise return Found => FALSE

--| Modifies: Raises, Modifies, Errors
													pragma Page;
function Is_Not_Literal(	--| Check if T is not at literal Chars
    Chars : in string;		--| Characters to be scanned
    T     : in Scanner		--| The string being scanned
    ) return boolean;

--| Effects: Return TRUE iff T is not at literal Chars
--| Modifies: Raises, Modifies, Errors

----------------------------------------------------------------

function Is_Not_Literal(	--| Check if T is not at literal Chars
    Chars : in String_Type;	--| Characters to be scanned
    T     : in Scanner		--| The string being scanned
    ) return boolean;

--| Effects: Return TRUE iff T is not at literal Chars
--| Modifies: Raises, Modifies, Errors

----------------------------------------------------------------

procedure Scan_Not_Literal(	--| Scan arbitrary literal
    Chars  : in     string;	--| Literal that should be scanned
    T      : in     Scanner;	--| String to be scanned
    Found  :    out boolean;	--| TRUE iff a sequence found
    Result :    out String_Type;--| String up to literal
    Skip   : in     boolean := false
				--| Skip white spaces before scan
    );

--| Effects: Scan T for a litral Chars such that Char does not match the
--| sequence of characters in T.  If found, return Found => TRUE, 
--| Otherwise return Found => FALSE

--| Modifies: Raises, Modifies, Errors

----------------------------------------------------------------

procedure Scan_Not_Literal(	--| Scan arbitrary literal
    Chars  : in     String_Type;--| Literal that should be scanned
    T      : in     Scanner;	--| String to be scanned
    Found  :    out boolean;	--| TRUE iff a sequence found
    Result :    out String_Type;--| String up to literal
    Skip   : in     boolean := false
				--| Skip white spaces before scan
    );

--| Effects: Scan T for a litral Chars such that Char does not match the
--| sequence of characters in T.  If found, return Found => TRUE, 
--| Otherwise return Found => FALSE

--| Modifies: Raises, Modifies, Errors
													pragma Page;
private
													pragma List(off);
    type Scan_Record is
	record
	    text  : String_Type;	--| Copy of string being scanned
	    index : positive := 1;	--| Current position of Scanner
	    mark  : natural := 0;	--| Mark
	end record;

    type Scanner is access Scan_Record;
													pragma List(on);
end String_Scanner;
													pragma Page;
