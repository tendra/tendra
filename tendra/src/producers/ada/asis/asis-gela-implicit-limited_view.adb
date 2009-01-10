------------------------------------------------------------------------------
--                           G E L A   A S I S                              --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA$:

with Asis.Iterator;
with Asis.Elements;
with Asis.Declarations;
with Asis.Gela.Lists;
with Asis.Gela.Utils;
with Asis.Gela.Unit_Utils;
with Asis.Gela.Elements.Decl;
with Asis.Gela.Elements.Defs;
with Asis.Gela.Element_Utils;

package body Asis.Gela.Implicit.Limited_View is

   type State_Information is record
      Unit : Asis.Compilation_Unit;
      Pkg  : Asis.Element;
   end record;

   procedure Pre_Operation
     (Element : in     Asis.Element;
      Control : in out Traverse_Control;
      State   : in out State_Information);

   procedure Post_Operation
     (Element : in     Asis.Element;
      Control : in out Traverse_Control;
      State   : in out State_Information);

   type Cloner is new Asis.Cloner with null record;

   function Clone
     (Object : Cloner;
      Item   : Element;
      Parent : Element) return Element;

   -----------
   -- Clone --
   -----------

   function Clone
     (Object : Cloner;
      Item   : Element;
      Parent : Element) return Element
   is
      use Asis.Gela.Elements;
      Result : constant Asis.Element := Clone (Item.all, Parent);
      Node   : Base_Element_Node renames Base_Element_Node (Result.all);
   begin
      Set_Is_Part_Of_Implicit (Node, True);
      return Result;
   end Clone;

   --------------------
   -- Post_Operation --
   --------------------

   procedure Post_Operation
     (Element : in     Asis.Element;
      Control : in out Traverse_Control;
      State   : in out State_Information)
   is
      use Asis.Gela.Elements.Decl;
      Parent : Asis.Element;
   begin
      if Asis.Elements.Declaration_Kind (Element) = A_Package_Declaration then
         Parent := Enclosing_Element (State.Pkg.all);

         if Assigned (Parent) then
            State.Pkg := Parent;
         end if;
      end if;
   end Post_Operation;

   -------------------
   -- Pre_Operation --
   -------------------

   procedure Pre_Operation
     (Element : in     Asis.Element;
      Control : in out Traverse_Control;
      State   : in out State_Information)
   is
      use Asis.Declarations;
      use Asis.Gela.Elements;
      use Asis.Gela.Elements.Decl;
      use Asis.Gela.Lists;

      --------------------------
      -- Implicit_Declaration --
      --------------------------

      procedure Implicit_Declaration
        (Node : in out Declaration_Node'Class;
         Self : Asis.Element)
      is
         Copy : Cloner;
         Name : constant Asis.Element_List := Names (Element);
         List : Asis.Element;
      begin
         Set_Declaration_Origin (Node, An_Implicit_Predefined_Declaration);
         Set_Enclosing_Compilation_Unit (Node, State.Unit);
         Set_Start_Position (Node, (1, 1));
         Set_End_Position (Node, (0, 0));
         Set_Is_Part_Of_Implicit (Node, True);
         Set_Enclosing_Element (Node, State.Pkg);
         List := Primary_Defining_Name_Lists.Deep_Copy (Name, Copy, Self);
         Set_Names (Node, List);

         if Assigned (State.Pkg) then
            Element_Utils.Add_To_Visible (State.Pkg, Self);
         end if;
      end Implicit_Declaration;

      ---------------
      -- Is_Tagged --
      ---------------

      function Is_Tagged (Element : Asis.Declaration) return Boolean is
         View : constant Asis.Definition :=
           Asis.Declarations.Type_Declaration_View (Element);
      begin
         case Asis.Elements.Definition_Kind (View) is
            when A_Type_Definition |
              An_Incomplete_Type_Definition |
              A_Private_Type_Definition |
              A_Task_Definition |
              A_Protected_Definition =>
               return False;
            when A_Tagged_Incomplete_Type_Definition |
              A_Tagged_Private_Type_Definition |
              A_Private_Extension_Definition =>
               return True;
            when others =>
               raise Internal_Error;
         end case;
      end Is_Tagged;

   begin
      if Asis.Elements.Element_Kind (Element) = A_Declaration and
        Assigned (State.Pkg)
      then
         if not Utils.In_Visible_Part (Element) then
            Control := Abandon_Siblings;
            return;
         end if;
      end if;

      case Asis.Elements.Declaration_Kind (Element) is
         when An_Ordinary_Type_Declaration |
           An_Incomplete_Type_Declaration |
           A_Task_Type_Declaration |
           A_Protected_Type_Declaration |
           A_Private_Type_Declaration |
           A_Private_Extension_Declaration
           =>
            declare
               Node : Incomplete_Type_Declaration_Ptr :=
                 new Incomplete_Type_Declaration_Node;
            begin
               Implicit_Declaration (Node.all, Asis.Element (Node));
               if Is_Tagged (Element) then
                  declare
                     use Asis.Gela.Elements.Defs;
                     Child : Tagged_Incomplete_Type_Definition_Ptr :=
                       new Tagged_Incomplete_Type_Definition_Node;
                  begin
                     Set_Enclosing_Compilation_Unit (Child.all, State.Unit);
                     Set_Start_Position (Child.all, (1, 1));
                     Set_End_Position (Child.all, (0, 0));
                     Set_Is_Part_Of_Implicit (Child.all, True);
                     Set_Enclosing_Element (Child.all, Asis.Element (Node));
                     Set_Type_Declaration_View
                       (Node.all, Asis.Element (Child));
                  end;
               else
                  declare
                     use Asis.Gela.Elements.Defs;
                     Child : Tagged_Incomplete_Type_Definition_Ptr :=
                       new Tagged_Incomplete_Type_Definition_Node;
                  begin
                     Set_Enclosing_Compilation_Unit (Child.all, State.Unit);
                     Set_Start_Position (Child.all, (1, 1));
                     Set_End_Position (Child.all, (0, 0));
                     Set_Is_Part_Of_Implicit (Child.all, True);
                     Set_Enclosing_Element (Child.all, Asis.Element (Node));
                     Set_Type_Declaration_View
                       (Node.all, Asis.Element (Child));
                  end;
               end if;

               Control := Abandon_Children;
            end;
         when A_Package_Declaration =>
            declare
               List : Primary_Declaration_Lists.List :=
                 new Primary_Declaration_Lists.List_Node;
               Node : Package_Declaration_Ptr :=
                 new Package_Declaration_Node;
            begin
               Set_Is_Private_Present (Node.all, Is_Private_Present (Element));
               Set_Visible_Part_Declarative_Items
                 (Node.all, Asis.Element (List));
               Implicit_Declaration (Node.all, Asis.Element (Node));
               State.Pkg := Asis.Element (Node);
               Control   := Continue;
            end;
         when others =>
            Control := Abandon_Children;
      end case;
   end Pre_Operation;

   procedure Walk is new Asis.Iterator.Traverse_Element (State_Information);

   --------------
   -- Populate --
   --------------

   procedure Populate
     (View_Unit   : Asis.Compilation_Unit;
      Declaration : Asis.Declaration)
   is
      Control : Traverse_Control := Continue;
      State   : State_Information;
   begin
      State.Unit := View_Unit;
      Walk (Declaration, Control, State);
      Unit_Utils.Set_Unit_Declaration (View_Unit, State.Pkg);
   end Populate;

end Asis.Gela.Implicit.Limited_View;


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
