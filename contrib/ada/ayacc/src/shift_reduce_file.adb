
with Text_IO, Ayacc_File_Names;
use  Text_IO, Ayacc_File_Names;
package body Shift_Reduce_File is

  SCCS_ID : constant String := "@(#) shift_reduce_file.ada, Version 1.2";



  Rcs_ID : constant String := "$Header: /dc/uc/self/arcadia/ayacc/src/RCS/shift_reduce_file.a,v 1.2 1993/05/31 22:36:35 self Exp self $";
    
    The_File : File_Type; 

    procedure Open_Write is
    begin
        Create(The_File, Out_File, Get_Shift_Reduce_File_Name); 
        Write_Line("package " & Shift_Reduce_Tables_Unit_Name & " is"); 
        Write_Line("");
        Write_Line("    type Small_Integer is range -32_000 .. 32_000;");
        Write_Line("");
        Write_Line("    type Shift_Reduce_Entry is record");
        Write_Line("        T   : Small_Integer;");
        Write_Line("        Act : Small_Integer;");
        Write_Line("    end record;");
        Write_Line("    pragma Pack(Shift_Reduce_Entry);");
        Write_Line("");
        Write_Line("    subtype Row is Integer range -1 .. Integer'Last;"); 
        Write_Line("");
        Write_Line("  --pragma suppress(index_check);");
        Write_Line("");
        Write_Line("    type Shift_Reduce_Array is array " &
                   "(Row  range <>) of Shift_Reduce_Entry;");
        Write_Line("");
        Write_Line("    Shift_Reduce_Matrix : constant Shift_Reduce_Array :=");
        Write_Line("        ( (-1,-1) -- Dummy Entry");
	New_Line(The_File);
	exception
             when Name_Error | Use_Error =>
                  Put_Line("Ayacc: Error Opening """ & Get_Shift_Reduce_File_Name & """.");
                  raise;
    end Open_Write;

    procedure Close_Read is
    begin
       Delete(The_File);
    end Close_Read;

    procedure Close_Write is
    begin
        Write_Line("end " & Shift_Reduce_Tables_Unit_Name & ";"); 
	Close(The_File);
    end Close_Write;

    procedure Write(S: in String) is 
    begin 
        Put(The_File, S) ;
    end;

    procedure Write_Line(S: in String) is
    begin
	Put_Line(The_File, S); 
    end Write_Line;

    procedure Write(C: in Character) is
    begin
        Put(The_File,C);   
    end;

end Shift_Reduce_File;
