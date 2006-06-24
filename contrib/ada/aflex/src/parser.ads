
with Parse_Tokens, Parse_Goto, Parse_Shift_Reduce, Text_IO, scanner;
with NFA, ccl, misc, misc_defs, sym, ecs, aflex_scanner;
with tstring, int_io, main_body, text_io, external_file_manager;
use aflex_scanner, external_file_manager;

package parser is
  procedure build_eof_action;
  procedure yyerror(msg: string);
  procedure YYParse;
  def_rule:integer;
end parser;
