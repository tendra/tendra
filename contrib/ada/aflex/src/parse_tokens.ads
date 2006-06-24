with  Text_Io;
with  Ccl;
with  Nfa;
with  Parse_Shift_Reduce;
with  Parse_Goto;
with  Misc_Defs;
use   Misc_Defs;
with  External_File_Manager;
use   External_File_Manager;
package Parse_Tokens is


  subtype YYSType is Integer;

    YYLVal, YYVal : YYSType; 
    type Token is
        (End_Of_Input, Error, Char, Number,
         Sectend, Scdecl, Xscdecl,
         Whitespace, Name, Prevccl,
         Eof_Op, Newline, '^',
         '<', '>', ',',
         '$', '|', '/',
         '*', '+', '?',
         '{', '}', '.',
         '"', '(', ')',
         '[', ']', '-' );

    Syntax_Error : exception;

end Parse_Tokens;
