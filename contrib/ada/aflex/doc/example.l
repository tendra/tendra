LOWER    [a-z]
UPPER    [A-Z]

%%

{LOWER}+       { Lower_Case := Lower_Case + 1; 
                 TEXT_IO.PUT(To_Upper_Case(Example_DFA.YYText)); }

		  -- convert all alphabetic words in lower case
		  -- to upper case

{UPPER}+       { Upper_Case := Upper_Case + 1;
                 TEXT_IO.PUT(Example_DFA.YYText); }

		  -- write uppercase word as is

\n             { TEXT_IO.NEW_LINE;}

.              { TEXT_IO.PUT(Example_DFA.YYText); }
                 -- write anything else as is

%% -- The next section will go to example.ads before the package statement
with Ada.Command_Line;
## -- The next section will go to example.ads after  the package statement
procedure Sample;
## -- The next section will go to example.adb before the package statement

## -- The next section will go to example.adb after  the package statement
procedure Sample is

  type Token is (End_of_Input, Error);

  Tok        : Token;
  Lower_Case : NATURAL := 0;   -- frequency of lower case words
  Upper_Case : NATURAL := 0;   -- frequency of upper case words

  function To_Upper_Case (Word : STRING) return STRING is
  Temp : STRING(1..Word'LENGTH);
  begin
    for i in 1.. Word'LENGTH loop
      Temp(i) := CHARACTER'VAL(CHARACTER'POS(Word(i)) - 32); 
    end loop;
    return Temp;
  end To_Upper_Case;  
##  -- function YYLex will go here, the follwing lines after YYLex
begin  -- Sample

  Example_IO.Open_Input     (Ada.Command_Line.Argument (1));

  Read_Input :
  loop
    Tok := YYLex;
    exit Read_Input
      when Tok = End_of_Input;
  end loop Read_Input;

  TEXT_IO.NEW_LINE;
  TEXT_IO.PUT_LINE("Number of lowercase words is => " & 
		   INTEGER'IMAGE(Lower_Case));
  TEXT_IO.PUT_LINE("Number of uppercase words is => " & 
		   INTEGER'IMAGE(Upper_Case));
end Sample;
