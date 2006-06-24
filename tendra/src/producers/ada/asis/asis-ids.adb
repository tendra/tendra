------------------------------------------------------------------------------
--                           G E L A   A S I S                              --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA: asis-ada_environments.adb 2270 2005-11-04 19:51:32Z maxr $
--  Purpose:
--  Implement permanent element Id on unmodified sources.
--  For Id we use hash of an element concatenated with unit unique name.

with Asis.Errors;
with Asis.Elements;
with Asis.Iterator;
with Asis.Exceptions;
with Asis.Implementation;
with Asis.Compilation_Units;

package body Asis.Ids is
   use type W.Unbounded_Wide_String;

   type State_Information is record
      Result : Asis.Element;
      Hash   : Asis.ASIS_Integer;
   end record;

   procedure Pre_Operation
     (Element : in     Asis.Element;
      Control : in out Traverse_Control;
      State   : in out State_Information);

   procedure Post_Operation
     (Element : in     Asis.Element;
      Control : in out Traverse_Control;
      State   : in out State_Information);

   ---------
   -- "<" --
   ---------

   function "<"
     (Left  : in Id;
      Right : in Id)
      return Boolean
   is
   begin
      return Left.Hash < Right.Hash or else
        (Left.Hash = Right.Hash and then Left.Unit < Right.Unit);
   end "<";

   ---------
   -- ">" --
   ---------

   function ">"
     (Left  : in Id;
      Right : in Id)
      return Boolean
   is
   begin
      return Left.Hash > Right.Hash or else
        (Left.Hash = Right.Hash and then Left.Unit > Right.Unit);
   end ">";

   -------------------
   -- Pre_Operation --
   -------------------

   procedure Pre_Operation
     (Element : in     Asis.Element;
      Control : in out Traverse_Control;
      State   : in out State_Information)
   is
   begin
      if Hash (Element.all) = State.Hash then
         State.Result := Element;
         Control := Terminate_Immediately;
      end if;
   end Pre_Operation;

   --------------------
   -- Post_Operation --
   --------------------

   procedure Post_Operation
     (Element : in     Asis.Element;
      Control : in out Traverse_Control;
      State   : in out State_Information) is
   begin
      null;
   end Post_Operation;

   --------------------
   -- Create_Element --
   --------------------

   function Create_Element
     (The_Id      : in Id;
      The_Context : in Asis.Context)
      return Asis.Element
   is
      use Asis.Errors;
      use Asis.Compilation_Units;

      procedure Raise_Error (Text : Wide_String);

      procedure Search is
         new Asis.Iterator.Traverse_Element (State_Information);

      procedure Raise_Error (Text : Wide_String) is
      begin
         Asis.Implementation.Set_Status
           (Value_Error, Text);
         raise Asis.Exceptions.ASIS_Inappropriate_Element;
      end Raise_Error;

      Unit    : Asis.Compilation_Unit;
      State   : State_Information;
      Control : Traverse_Control := Continue;
      List    : constant Asis.Compilation_Unit_List :=
        Compilation_Units.Compilation_Units (The_Context);
   begin
      for I in List'Range loop
         if Unique_Name (List (I)) = The_Id.Unit then
            Unit := List (I);
            exit;
         end if;
      end loop;

      if Is_Nil (Unit) then
         Raise_Error ("No such unit");
      else
         State.Hash := The_Id.Hash + Hash (Unit.all);
      end if;

      declare
         Clause : constant Asis.Element_List :=
           Context_Clause_Elements (Unit.all, True);
      begin
         for I in Clause'Range loop
            Search (Clause (I), Control, State);

            if Assigned (State.Result) then
               return State.Result;
            end if;
         end loop;
      end;

      Search (Unit_Declaration (Unit.all), Control, State);

      if Assigned (State.Result) then
         return State.Result;
      else
         Raise_Error ("No element for this id");
         return Nil_Element;
      end if;
   end Create_Element;

   ---------------
   -- Create_Id --
   ---------------

   function Create_Id (Element : in Asis.Element) return Id is
      use Asis.Elements;
      use Asis.Compilation_Units;

      Result   : Asis.ASIS_Integer;
      The_Unit : Asis.Compilation_Unit :=
        Enclosing_Compilation_Unit (Element);
   begin
      if not Assigned (Element) then
         return Nil_Id;
      end if;

      The_Unit := Enclosing_Compilation_Unit (Element);
      Result := Hash (Element) - Hash (The_Unit.all);

      return (Result, W.To_Unbounded_Wide_String (Unique_Name (The_Unit)));
   end Create_Id;

   -----------------
   -- Debug_Image --
   -----------------

   function Debug_Image (The_Id : in Id) return Wide_String is
   begin
      return ASIS_Integer'Wide_Image (The_Id.Hash) & "/"
        & W.To_Wide_String (The_Id.Unit);
   end Debug_Image;

   ----------
   -- Hash --
   ----------

   function Hash (The_Id : in Id) return Asis.ASIS_Integer is
   begin
      return The_Id.Hash;
   end Hash;

   --------------
   -- Is_Equal --
   --------------

   function Is_Equal
     (Left  : in Id;
      Right : in Id)
      return Boolean
   is
   begin
      return Left.Hash = Right.Hash and then Left.Unit = Right.Unit;
   end Is_Equal;

   ------------
   -- Is_Nil --
   ------------

   function Is_Nil (Right : in Id) return Boolean is
   begin
      return Right.Hash = 0 and then Right.Unit = "";
   end Is_Nil;

end Asis.Ids;



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
