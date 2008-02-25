with Asis.Elements;
with Asis.Gela.Iterator;
with Asis.Gela.Overloads;
with Asis.Gela.Visibility;
with Asis.Gela.Implicit.Decl;
with Asis.Gela.Resolver.Polish;
with Asis.Gela.Private_Operations;

package body Asis.Gela.Resolver is

   type State_Information is record
      Point : Visibility.Point;
      Stack : Private_Operations.Package_Data_Stack;
   end record;

   procedure Pre_Operation
     (Element : in out Asis.Element;
      Control : in out Traverse_Control;
      State   : in out State_Information);

   procedure Post_Operation
     (Element : in out Asis.Element;
      Control : in out Traverse_Control;
      State   : in out State_Information);

   package Iterator is new Asis.Gela.Iterator (State_Information);

   type Polish_State is null record;

   procedure Pre_Operation
     (Element : in out Asis.Element;
      Control : in out Traverse_Control;
      State   : in out Polish_State);

   procedure Post_Operation
     (Element : in out Asis.Element;
      Control : in out Traverse_Control;
      State   : in out Polish_State);

   package Polish_Iterator is new Asis.Gela.Iterator (Polish_State);

   --------------------------
   -- Polish_Subexpression --
   --------------------------

   procedure Polish_Subexpression (Element : Asis.Expression) is
      State   : Polish_State;
      Control : Traverse_Control := Continue;
   begin
      Polish_Iterator.Walk_Element (Element, Control, State);
   end Polish_Subexpression;

   --------------------
   -- Post_Operation --
   --------------------

   procedure Post_Operation
     (Element : in out Asis.Element;
      Control : in out Traverse_Control;
      State   : in out State_Information)
   is
      use Asis.Elements;
      Inner : Visibility.Point := State.Point;
   begin
      Visibility.Leave_Construction (Element, State.Point);
      Implicit.Decl.Process (Element, State.Point, Inner);

      if not Is_Part_Of_Instance (Element.all) then
         Overloads.Resolve (Element);
      end if;

      case Declaration_Kind (Element) is
         when A_Type_Declaration =>
            if Declaration_Kind (Enclosing_Element (Element)) =
              Asis.A_Package_Declaration
            then
               Private_Operations.Check_Type
                 (Element => Element,
                  Data    => Private_Operations.Top (State.Stack),
                  Point   => State.Point);
            end if;
         when A_Package_Declaration =>
            Private_Operations.Pop (State.Stack);
         when others =>
            null;
      end case;
   end Post_Operation;

   --------------------
   -- Post_Operation --
   --------------------

   procedure Post_Operation
     (Element : in out Asis.Element;
      Control : in out Traverse_Control;
      State   : in out Polish_State) is
   begin
      Polish.Each_Element (Element);
   end Post_Operation;

   -------------------
   -- Pre_Operation --
   -------------------

   procedure Pre_Operation
     (Element : in out Asis.Element;
      Control : in out Traverse_Control;
      State   : in out State_Information)
   is
      use Asis.Elements;
      use Asis.Gela.Private_Operations;

      Expr : constant Expression_Kinds := Expression_Kind (Element);
   begin
      Visibility.Enter_Construction (Element, State.Point);

      if (Expr = An_Identifier or
          Expr = An_Operator_Symbol or
          Expr = A_Character_Literal)
        and not Is_Part_Of_Implicit (Element)
        and not Is_Part_Of_Instance (Element)
      then
         Visibility.Try_To_Resolve (Element, State.Point);
      end if;

      case Declaration_Kind (Element) is
         when A_Package_Declaration =>
            Private_Operations.Push
              (State.Stack, Private_Operations.Create (Element));
         when A_Package_Body_Declaration =>
            Private_Operations.On_Package_Body
              (Element, State.Point);
         when others =>
            null;
      end case;
   end Pre_Operation;

   -------------------
   -- Pre_Operation --
   -------------------

   procedure Pre_Operation
     (Element : in out Asis.Element;
      Control : in out Traverse_Control;
      State   : in out Polish_State) is
   begin
      null;
   end Pre_Operation;

   ----------------------
   -- Process_Instance --
   ----------------------

   procedure Process_Instance
     (Decl  : Asis.Declaration;
      Point : Visibility.Point)
   is
      State    : State_Information;
      Control  : Traverse_Control := Continue;
      Instance : Asis.Declaration := Decl;
   begin
      State.Point       := Point;
      Iterator.Walk_Element_And_Free (Instance, Control, State);
      pragma Assert (Is_Equal (Decl, Instance));
   end Process_Instance;

   ---------
   -- Run --
   ---------

   procedure Run (Unit : Asis.Compilation_Unit) is
      State   : State_Information;
      Control : Traverse_Control := Continue;
      Decl    : Asis.Element;
      P_State : Polish_State;
   begin
      State.Point := Visibility.Enter_Unit (Unit);

      declare
         List : constant Asis.Element_List :=
           Context_Clause_Elements (Unit.all);
      begin
         for I in List'Range loop
            Iterator.Walk_Element (List (I), Control, State);
         end loop;
      end;

      Decl := Unit_Declaration (Unit.all);
      Iterator.Walk_Element_And_Free (Decl, Control, State);
      pragma Assert (Is_Equal (Decl, Unit_Declaration (Unit.all)));

      Polish_Iterator.Walk_Element (Decl, Control, P_State);
   end Run;

end Asis.Gela.Resolver;



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
