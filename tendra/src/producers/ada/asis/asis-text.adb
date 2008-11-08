------------------------------------------------------------------------------
--                           G E L A   A S I S                              --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA$
--  Purpose:
--  Implement Asis.Text.
--  Not implemented yet (except Element_Span)

with Gela.Decoders;
with Gela.Source_Buffers;

use Gela;

with Asis.Errors;
with Asis.Elements;
with Asis.Exceptions;
with Asis.Gela.Lines;
with Asis.Implementation;
with Asis.Gela.Text_Utils;
with Asis.Compilation_Units;

package body Asis.Text is

   LF : constant Wide_Character := Wide_Character'Val (10);

   Max_Line_Size : constant := 1024;

   -------------------
   -- Comment_Image --
   -------------------

   function Comment_Image (The_Line : in Line) return Program_Text is
      use Asis.Gela.Text_Utils;
      Line    : Asis.Gela.Lines.Line;
      Decoder : Decoder_Access;
      Source  : Source_Buffer_Access;
   begin
      if Is_Nil (The_Line) then
         Implementation.Set_Status (
            Status    => Asis.Errors.Value_Error,
            Diagnosis => "Line is nil");

         raise Asis.Exceptions.ASIS_Inappropriate_Line;
      end if;

      Line    := Get_Line (The_Line.Unit, The_Line.Index);
      Decoder := Gela.Text_Utils.Decoder (The_Line.Unit);
      Source  := Source_Buffer (The_Line.Unit);

      declare
         Text : Wide_String (1 .. Max_Line_Size);
         Last : Natural;
      begin
         Decoders.Decode
           (Object  => Decoder.all,
            From    => Line.From,
            To      => Line.Comment,
            Result  => Text,
            Last    => Last);

         Text (1 .. Last) := (others => ' ');

         Decoders.Decode
           (Object  => Decoder.all,
            From    => Line.Comment,
            To      => Line.To,
            Result  => Text (Last + 1 .. Text'Last),
            Last    => Last);

         if The_Line.From > 1 then
            Text (1 .. The_Line.From - 1) := (others => ' ');
         end if;

         if The_Line.To < Last then
            Last := The_Line.To;
         end if;

         return Text (1 .. Last);
      end;
   end Comment_Image;

   ----------------------
   -- Compilation_Span --
   ----------------------

   function Compilation_Span
     (Element : in Asis.Element)
      return Span
   is
      use Asis.Gela.Text_Utils;
      Unit : constant Asis.Compilation_Unit :=
        Asis.Elements.Enclosing_Compilation_Unit (Element);
   begin
      return (1, 1, Compilation_Line_Count (Unit), Max_Line_Size);
   end Compilation_Span;

   ---------------------------
   -- Compilation_Unit_Span --
   ---------------------------

   function Compilation_Unit_Span
     (Element : in Asis.Element)
      return Span
   is
   begin
      if not Assigned (Element) then
         return Nil_Span;
      else
         declare
            Unit : constant Asis.Compilation_Unit :=
              Asis.Elements.Enclosing_Compilation_Unit (Element);
            Start : constant Text_Position := Start_Position (Unit.all);
            Stop  : constant Text_Position := End_Position (Unit.all);
         begin
            if Start.Line = 0 or Start.Column = 0 then
               return Nil_Span;
            end if;

            return (First_Line   => Line_Number_Positive (Start.Line),
                    First_Column => Character_Position_Positive (Start.Column),
                    Last_Line    => Line_Number (Stop.Line),
                    Last_Column  => Character_Position (Stop.Column));
         end;
      end if;
   end Compilation_Unit_Span;

   -----------------
   -- Debug_Image --
   -----------------

   function Debug_Image (The_Line : in Line) return Wide_String is

   begin
      if Is_Nil (The_Line) then
         return "[nil_line]";
      else
         declare
            Unit : constant Wide_String :=
              Compilation_Units.Text_Name (The_Line.Unit);
            Image : constant Wide_String :=
              Line_Number'Wide_Image (The_Line.Index);
         begin
            return Unit & "[" & Image (2 .. Image'Last) & "]";
         end;
      end if;
   end Debug_Image;

   ---------------------
   -- Delimiter_Image --
   ---------------------

   function Delimiter_Image return Wide_String is
   begin
      return (1 => LF);
   end Delimiter_Image;

   -------------------
   -- Element_Image --
   -------------------

   function Element_Image (Element : in Asis.Element) return Program_Text is

      function Image (List   : Line_List;
                      Prefix : Program_Text := "") return Program_Text
      is
         Result : Program_Text (1 .. 4096);
         Last   : Natural := 0;
         Index  : Line_Number_Positive := List'First;
      begin
         while Index <= List'Last loop
            declare
               Text : constant Program_Text := Line_Image (List (Index));
            begin
               if Text'Length < Result'Length - Last then
                  Result (Last + 1 .. Last + Text'Length) := Text;
                  Last := Last + Text'Length;

                  if Index < List'Last then
                     Result (Last + 1) := LF;
                     Last := Last + 1;
                  end if;
               elsif Index < List'Last then
                  return Image (List (Index + 1 .. List'Last),
                                Prefix & Result (1 .. Last) & Text & LF);
               else
                  return Prefix & Result (1 .. Last) & Text;
               end if;

               Index := Index + 1;
            end;
         end loop;

         return Prefix & Result (1 .. Last);
      end Image;
   begin
      return Image (Lines (Element));
   end Element_Image;

   ------------------
   -- Element_Span --
   ------------------

   function Element_Span
     (Element : in Asis.Element)
      return Span
   is
   begin
      if not Assigned (Element) then
         return Nil_Span;
      else
         declare
            Start : constant Text_Position := Start_Position (Element.all);
            Stop  : constant Text_Position := End_Position (Element.all);
         begin
            if Start.Line = 0 or Start.Column = 0 then
               return Nil_Span;
            end if;

            return (First_Line   => Line_Number_Positive (Start.Line),
                    First_Column => Character_Position_Positive (Start.Column),
                    Last_Line    => Line_Number (Stop.Line),
                    Last_Column  => Character_Position (Stop.Column));
         end;
      end if;
   end Element_Span;

   -----------------------
   -- First_Line_Number --
   -----------------------

   function First_Line_Number
     (Element : in Asis.Element)
      return Line_Number
   is
      S : constant Span := Element_Span (Element);
   begin
      return S.First_Line;
   end First_Line_Number;

   --------------
   -- Is_Equal --
   --------------

   function Is_Equal
     (Left  : in Line;
      Right : in Line)
      return Boolean
   is
   begin
      return Is_Identical (Left, Right);
   end Is_Equal;

   ------------------
   -- Is_Identical --
   ------------------

   function Is_Identical
     (Left  : in Line;
      Right : in Line)
      return Boolean
   is
   begin
      return Asis.Compilation_Units.Is_Identical (Left.Unit,  Right.Unit) and
        Left.From = Right.From and
        Left.To = Right.To and
        Left.Index = Right.Index;
   end Is_Identical;

   ------------
   -- Is_Nil --
   ------------

   function Is_Nil
     (Right : in Line)
      return Boolean
   is
   begin
      return Asis.Compilation_Units.Is_Nil (Right.Unit);
   end Is_Nil;

   ------------
   -- Is_Nil --
   ------------

   function Is_Nil
     (Right : in Line_List)
      return Boolean
   is
   begin
      return Right'Length = 0;
   end Is_Nil;

   ------------
   -- Is_Nil --
   ------------

   function Is_Nil
     (Right : in Span)
      return Boolean
   is
   begin
      return Right = Nil_Span;
   end Is_Nil;

   -----------------------
   -- Is_Text_Available --
   -----------------------

   function Is_Text_Available (Element : in Asis.Element) return Boolean is
      use Asis.Elements;
   begin
      if Is_Nil (Element) or
        Is_Part_Of_Implicit (Element) or
        Is_Part_Of_Instance (Element)
      then
         return False;
      else
         return True;
      end if;
   end Is_Text_Available;

   ----------------------
   -- Last_Line_Number --
   ----------------------

   function Last_Line_Number
     (Element : in Asis.Element)
      return Line_Number
   is
      S : constant Span := Element_Span (Element);
   begin
      return S.Last_Line;
   end Last_Line_Number;

   ------------
   -- Length --
   ------------

   function Length (The_Line : in Line) return Character_Position is
   begin
      return Line_Image (The_Line)'Length;
   end Length;

   ----------------
   -- Line_Image --
   ----------------

   function Line_Image (The_Line : in Line) return Program_Text is
      use Asis.Gela.Text_Utils;
      Line    : Asis.Gela.Lines.Line;
      Decoder : Decoder_Access;
      Source  : Source_Buffer_Access;
   begin
      if Is_Nil (The_Line) then
         Implementation.Set_Status (
            Status    => Asis.Errors.Value_Error,
            Diagnosis => "Line is nil");

         raise Asis.Exceptions.ASIS_Inappropriate_Line;
      end if;

      Line    := Get_Line (The_Line.Unit, The_Line.Index);
      Decoder := Gela.Text_Utils.Decoder (The_Line.Unit);
      Source  := Source_Buffer (The_Line.Unit);

      declare
         Text : Wide_String (1 .. Max_Line_Size);
         Last : Natural;
      begin
         Decoders.Decode
           (Object  => Decoder.all,
            From    => Line.From,
            To      => Line.To,
            Result  => Text,
            Last    => Last);

         if The_Line.From > 1 then
            Text (1 .. The_Line.From - 1) := (others => ' ');
         end if;

         if The_Line.To < Last then
            Last := The_Line.To;
         end if;

         return Text (1 .. Last);
      end;
   end Line_Image;

   -----------
   -- Lines --
   -----------

   function Lines (Element : in Asis.Element) return Line_List is
      The_Span : constant Span := Element_Span (Element);
   begin
      if Asis.Elements.Is_Nil (Element) then
         return Nil_Line_List;
      else
         return Lines (Element, The_Span);
      end if;
   end Lines;

   -----------
   -- Lines --
   -----------

   function Lines
     (Element  : in Asis.Element;
      The_Span : in Span)
      return Line_List
   is
      Unit   : constant Asis.Compilation_Unit :=
        Asis.Elements.Enclosing_Compilation_Unit (Element);
      Result : Line_List (The_Span.First_Line .. The_Span.Last_Line);
   begin
      if Is_Nil (The_Span) then
         Implementation.Set_Status (
            Status    => Asis.Errors.Value_Error,
            Diagnosis => "Span is nil");

         raise Asis.Exceptions.ASIS_Inappropriate_Line;
      end if;

      for J in Result'Range loop
         Result (J).Unit := Unit;
         Result (J).Index := J;
      end loop;

      Result (Result'First).From := Positive (The_Span.First_Column);
      Result (Result'Last).To    := Natural (The_Span.Last_Column);

      return Result;
   end Lines;

   -----------
   -- Lines --
   -----------

   function Lines
     (Element    : in Asis.Element;
      First_Line : in Line_Number_Positive;
      Last_Line  : in Line_Number)
      return Line_List
   is
      Unit   : constant Asis.Compilation_Unit :=
        Asis.Elements.Enclosing_Compilation_Unit (Element);
      Result : Line_List (First_Line .. Last_Line);
   begin
      if First_Line > Last_Line then
         Implementation.Set_Status (
            Status    => Asis.Errors.Value_Error,
            Diagnosis => "Span is nil");

         raise Asis.Exceptions.ASIS_Inappropriate_Line;
      end if;

      for J in Result'Range loop
         Result (J).Unit := Unit;
         Result (J).Index := J;
      end loop;

      return Result;
   end Lines;

   -----------------------
   -- Non_Comment_Image --
   -----------------------

   function Non_Comment_Image (The_Line : in Line) return Program_Text is
      use Asis.Gela.Text_Utils;
      Line    : Asis.Gela.Lines.Line;
      Decoder : Decoder_Access;
      Source  : Source_Buffer_Access;
   begin
      if Is_Nil (The_Line) then
         Implementation.Set_Status (
            Status    => Asis.Errors.Value_Error,
            Diagnosis => "Line is nil");

         raise Asis.Exceptions.ASIS_Inappropriate_Line;
      end if;

      Line    := Get_Line (The_Line.Unit, The_Line.Index);
      Decoder := Gela.Text_Utils.Decoder (The_Line.Unit);
      Source  := Source_Buffer (The_Line.Unit);

      declare
         Text : Wide_String (1 .. Max_Line_Size);
         Last : Natural;
      begin
         Decoders.Decode
           (Object  => Decoder.all,
            From    => Line.From,
            To      => Line.Comment,
            Result  => Text,
            Last    => Last);

         if The_Line.From > 1 then
            Text (1 .. The_Line.From - 1) := (others => ' ');
         end if;

         if The_Line.To < Last then
            Last := The_Line.To;
         end if;

         return Text (1 .. Last);
      end;
   end Non_Comment_Image;

end Asis.Text;



------------------------------------------------------------------------------
--  Copyright (c) 2006, Maxim Reznik
--  All rights reserved.
--
--  Redistribution and use in source and binary forms, with or without
--  modification, are permitted provided that the following conditions are met:
--
--     * Redistributions of source code must retain the above copyright notice,
--     * this list of conditions and the following disclaimer.
--     * Redistributions in binary form must reproduce the above copyright
--     * notice, this list of conditions and the following disclaimer in the
--     * documentation and/or other materials provided with the distribution.
--
--  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
--  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
--  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
--  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
--  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
--  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
--  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
--  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
--  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
--  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
--  POSSIBILITY OF SUCH DAMAGE.
------------------------------------------------------------------------------
