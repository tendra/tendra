--with Ada.Text_IO; 
with Ada.Command_Line;      use Ada.Command_Line;
separate (Command_Line_Interface)

procedure Read_Command_Line (Command_Args : out Command_Line_Type) is

  -- mytest
  --Maximum_Command_Length : constant := 1024;

  --subtype Command_Line_Type is String (1 .. Maximum_Command_Length);
  --Command_Args :  Command_Line_Type;
  -- mytest

  last : integer := command_args'first - 1;

  procedure put ( s : string ) is
  begin
    command_args ( last+1.. last+s'length) := s;
    last := last + s'length;
  end;

begin

  for i in 1 .. Ada.Command_Line.Argument_count -- - 1
  loop
    if i/=1 then 
       put(" "); end if;
    put (  Ada.Command_Line.argument(i) );
  end loop;

  command_args (last+1..command_args'last) := ( others => ' ' );
--  Ada.Text_IO.Put_Line(Command_Args);
end Read_Command_Line;

