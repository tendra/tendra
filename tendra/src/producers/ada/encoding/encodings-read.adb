with Ada.Text_IO;
with Ada.IO_Exceptions;

package body Encodings.Read is

   -----------
   -- Table --
   -----------

   function Table (File_Name : String) return Mapping is
      use Ada.Text_IO;
      use Encodings.Maps;

      type Pair is record
         Char : Character;
         Wide : Wide_Character;
      end record;

      type Pairs is array (Positive range <>) of Pair;

      Max_Pairs : constant := 2**16;

      Input : File_Type;
      Line  : String (1 .. 120);
      Last  : Natural;
      Char  : Integer range 0 .. 255;
      Wide  : Integer range 0 .. 2**16 - 1;
      Start : Character := Character'Last;
      Again : Boolean := True;
      Swap  : Pair;
      Count : Range_Count := 1;
      Chars : Forward_Map (Character'Range);

      Table : Pairs (1 .. Max_Pairs);
      Index : Natural := 0;
   begin
      for I in Chars'Range loop
         Chars (I) := Wide_Character'Val (Character'Pos (I));
      end loop;

      Open (Input, In_File, File_Name);

      while not End_Of_File (Input) loop
         Get_Line (Input, Line, Last);

         if Last > 12 and then Line (1) /= '#' then
            if Line (1 .. 2) = "0x" and Line (5) = ASCII.HT
              and ((Line (6 .. 7) = "0x" and Line (12) = ASCII.HT)
                   or Line (6) = ' '
                   or Line (6) = ASCII.HT)
            then
               if Line (6 .. 7) = "0x" then
                  Wide := Integer'Value ("16#" & Line (8 .. 11) & "#");
               else --  Undefined character
                  Wide := Wide_Character'Pos (Undefined);
               end if;

               Char := Integer'Value ("16#" & Line (3 .. 4) & "#");
               Index := Index + 1;
               Table (Index).Char := Character'Val (Char);
               Table (Index).Wide := Wide_Character'Val (Wide);
               Chars (Table (Index).Char) := Table (Index).Wide;
            else
               Put_Line (Line (1 .. Last));
            end if;
         end if;
      end loop;

      Close (Input);

      for I in Chars'Range loop
         if Character'Pos (I) /= Wide_Character'Pos (Chars (I)) then
            Start := I;
            exit;
         end if;
      end loop;

      Bubbel_Sort :
         while Again loop
            Again := False;

            for I in 2 .. Index loop
               if Table (I).Wide < Table (I - 1).Wide then
                  Swap := Table (I);
                  Table (I) := Table (I - 1);
                  Table (I - 1) := Swap;
                  Again := True;
               end if;
            end loop;
         end loop Bubbel_Sort;

      Count_Ranges :
         for I in 2 .. Index loop
            if Table (I - 1).Wide = Wide_Character'Last or else
              Wide_Character'Succ (Table (I - 1).Wide) /= Table (I).Wide
            then
               Count := Count + 1;
            end if;
         end loop Count_Ranges;

      declare
         Ranges   : Maps.Wide_Ranges  (1 .. Count);
         Backward : Maps.Backward_Map (1 .. Backward_Index (Index));
         Back     : Backward_Index := 1;
      begin
         for I in 1 .. Index loop
            Backward (Back) := Table (I).Char;

            if I = 1 then
               Count := 1;
               Ranges (Count).Lower := Table (I).Wide;
               Ranges (Count).Index := Back;
            elsif Table (I - 1).Wide = Wide_Character'Last or else
              Wide_Character'Succ (Table (I - 1).Wide) /= Table (I).Wide
            then
               Ranges (Count).Upper := Table (I - 1).Wide;
               Count := Count + 1;
               Ranges (Count).Lower := Table (I).Wide;
               Ranges (Count).Index := Back;
            end if;

            Back := Back + 1;
         end loop;

         Ranges (Count).Upper := Table (Index).Wide;

         return (Start        => Start,
                 Ranges_Count => Ranges'Length,
                 Char_Count   => Backward'Length,
                 Forward      => Chars (Start .. Chars'Last),
                 Ranges       => Ranges,
                 Backward     => Backward);
      end;

   exception
      when Ada.IO_Exceptions.Name_Error =>
         raise Invalid_Encoding;
   end Table;

end Encodings.Read;

