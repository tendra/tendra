with ada_parse, ada_lex.io, ada_lex, text_io;
use  ada_parse, text_io;

procedure parse is
  in_file_name: string(1..80);
  last        : natural;
begin
    text_io.put("Enter input file: ");
    text_io.get_line(in_file_name, last);
    ada_lex.io.open_input(in_file_name(1..last));
    ada_lex.io.create_output;

    put_line("---- Starting parse ----");

    ada_lex.linenum;
    yyparse;


    ada_lex.io.close_input;
    ada_lex.io.close_output;

    put_line("---- Finished parse ----");
    new_line;
    put(integer'image(number_of_errors));
    put_line(" errors found");

end parse;

