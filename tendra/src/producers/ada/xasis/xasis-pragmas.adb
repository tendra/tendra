with XASIS.Utils;

with Asis.Elements;
with Asis.Expressions;

package body XASIS.Pragmas is

   -------------------
   --  Find_Pragmas --
   -------------------

   function Find_Pragmas
     (Name    : Asis.Defining_Name;
      Request : Pragma_Kinds_Array)
     return Asis.Pragma_Element_List
   is
      use type Asis.ASIS_Natural;

      function Needed (Kind : Asis.Pragma_Kinds) return Boolean is
         use type Asis.Pragma_Kinds;
      begin
         for J in Request'Range loop
            if Kind = Request (J) then
               return True;
            end if;
         end loop;

         return False;
      end Needed;

      Result : Asis.Pragma_Element_List (Request'Range);
      Last   : Asis.ASIS_Natural := 0;
      Parent : constant Asis.Element :=
        Asis.Elements.Enclosing_Element (Name);
      List   : constant Asis.Pragma_Element_List :=
        Asis.Elements.Corresponding_Pragmas (Parent);
   begin
      for J in List'Range loop
         if Needed (Asis.Elements.Pragma_Kind (List (J))) then
            Last := Last + 1;
            Result (Last) := List (J);
         end if;
      end loop;

      return Result (1 .. Last);
   end Find_Pragmas;

   ---------------
   -- Parameter --
   ---------------

   function Parameter
     (Element : Asis.Pragma_Element;
      Kind    : Argument_Kinds) return Asis.Expression
   is
      use Asis.Elements;
      use Asis.Expressions;

      List : constant Asis.Association_List :=
        Pragma_Argument_Associations (Element);

      ----------------
      -- Find_Named --
      ----------------

      function Find_Named (Start : Asis.List_Index) return Asis.Expression is
         Image  : constant Wide_String := Argument_Kinds'Wide_Image (Kind);
         Formal : Asis.Identifier;
      begin
         for J in Start .. List'Last loop
            Formal := Formal_Parameter (List (J));

            if Utils.Are_Equal_Identifiers (Image, Name_Image (Formal)) then
               return Actual_Parameter (List (J));
            end if;
         end loop;

         return Asis.Nil_Element;
      end Find_Named;

      ---------------------
      -- Find_Positional --
      ---------------------

      function Find_Positional (Position : Asis.List_Index)
                               return Asis.Expression is
      begin
         for J in 1 .. Position loop
            if J not in List'Range then
               return Asis.Nil_Element;
            elsif not Is_Nil (Formal_Parameter (List (J))) then
               return Find_Named (J);
            end if;
         end loop;

         return Actual_Parameter (List (Position));
      end Find_Positional;

      Index : constant array (Asis.Pragma_Kinds, Argument_Kinds)
        of Asis.ASIS_Natural :=
        (Asis.A_Convention_Pragma =>
           (Convention => 1, Entity =>2, others => 0),

         Asis.A_Discard_Names_Pragma =>
           (On => 1, others => 0),

         Asis.An_Export_Pragma =>
           (Convention => 1, Entity => 2, External_Name => 3, Link_Name => 4,
            others => 0),

         Asis.An_Import_Pragma =>
           (Convention => 1, Entity => 2, External_Name => 3, Link_Name => 4,
            others => 0),

         Asis.A_Suppress_Pragma =>
           (On => 2, others => 0),

         others => (others => 0));
   begin
      return Find_Positional (Index (Pragma_Kind (Element), Kind));
   end Parameter;

end XASIS.Pragmas;


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
