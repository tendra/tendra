with Calc, calc_lex.IO, Text_IO;
procedure driver is
  in_file_name: string(1..80);
  last        : natural;
begin
    Text_IO.Put("Enter input file: ");
    Text_IO.Get_Line(in_file_name, last);
    calc_lex.IO.open_input(in_file_name(1..last));
    --calc_lex.IO.open_input("/dev/tty");
    calc_lex.IO.create_output;
    Calc.yyparse;
    calc_lex.IO.close_input;
    calc_lex.IO.close_output;
end driver;
