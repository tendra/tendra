------------------------------------------------------------------------------
--                           G E L A   A S I S                              --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA: asis-ada_environments.adb 2270 2005-11-04 19:51:32Z maxr $
--  Purpose:
--  Implement Asis.Text.
--  Not implemented yet (except Element_Span)

package body Asis.Text is

   -------------------
   -- Comment_Image --
   -------------------

   function Comment_Image (The_Line : in Line) return Program_Text is
   begin
      return "";
   end Comment_Image;

   ----------------------
   -- Compilation_Span --
   ----------------------

   function Compilation_Span
     (Element : in Asis.Element)
      return Span
   is
   begin
      return Nil_Span;
   end Compilation_Span;

   ---------------------------
   -- Compilation_Unit_Span --
   ---------------------------

   function Compilation_Unit_Span
     (Element : in Asis.Element)
      return Span
   is
   begin
      return Nil_Span;
   end Compilation_Unit_Span;

   -----------------
   -- Debug_Image --
   -----------------

   function Debug_Image (The_Line : in Line) return Wide_String is
   begin
      return "Debug_Image";
   end Debug_Image;

   ---------------------
   -- Delimiter_Image --
   ---------------------

   function Delimiter_Image return Wide_String is
   begin
      return " ";
   end Delimiter_Image;

   -------------------
   -- Element_Image --
   -------------------

   function Element_Image (Element : in Asis.Element) return Program_Text is
   begin
      return "";
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
      return False;
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
      return False;
   end Is_Identical;

   ------------
   -- Is_Nil --
   ------------

   function Is_Nil
     (Right : in Line)
      return Boolean
   is
   begin
      return True;
   end Is_Nil;

   ------------
   -- Is_Nil --
   ------------

   function Is_Nil
     (Right : in Line_List)
      return Boolean
   is
   begin
      return True;
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
   begin
      return False;
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
      return 0;
   end Length;

   ----------------
   -- Line_Image --
   ----------------

   function Line_Image (The_Line : in Line) return Program_Text is
   begin
      return "";
   end Line_Image;

   -----------
   -- Lines --
   -----------

   function Lines (Element : in Asis.Element) return Line_List is
   begin
      return Nil_Line_List;
   end Lines;

   -----------
   -- Lines --
   -----------

   function Lines
     (Element  : in Asis.Element;
      The_Span : in Span)
      return Line_List
   is
   begin
      return Nil_Line_List;
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
   begin
      return Nil_Line_List;
   end Lines;

   -----------------------
   -- Non_Comment_Image --
   -----------------------

   function Non_Comment_Image (The_Line : in Line) return Program_Text is
   begin
      return "";
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
