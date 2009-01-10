------------------------------------------------------------------------------
--                           G E L A   A S I S                              --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA$:

with Asis.Elements;
with Asis.Expressions;
with Asis.Declarations;
with Asis.Gela.Lists;
with Asis.Gela.Elements.Decl;
with Asis.Gela.Elements.Defs;
with Asis.Gela.Elements.Expr;
with Asis.Gela.Element_Utils;
with Asis.Gela.Elements.Assoc;

package body Asis.Gela.Instances.Utils is

   function New_Direct_Name
     (Inst   : Asis.Declaration;
      Name   : Asis.Defining_Name) return Asis.Expression;

   function Clone_Procedure
     (Item   : Asis.Element;
      Parent : Asis.Element) return Asis.Element;

   function Clone_Function
     (Item   : Asis.Element;
      Parent : Asis.Element) return Asis.Element;

   function Clone_Package
     (Item   : Asis.Element;
      Parent : Asis.Element) return Asis.Element;

   -----------------------
   -- Clone_Declaration --
   -----------------------

   function Clone_Declaration
     (Item   : Asis.Element;
      Parent : Asis.Element) return Asis.Element
   is
      use Asis.Elements;
   begin
      case Declaration_Kind (Parent) is
         when A_Package_Instantiation |
           A_Formal_Package_Declaration |
           A_Formal_Package_Declaration_With_Box =>
            return Clone_Package (Item, Parent);
         when A_Procedure_Instantiation =>
            return Clone_Procedure (Item, Parent);
         when A_Function_Instantiation =>
            return Clone_Function (Item, Parent);
         when others =>
            raise Internal_Error;
      end case;
   end Clone_Declaration;

   --------------------
   -- Clone_Function --
   --------------------

   function Clone_Function
     (Item   : Asis.Element;
      Parent : Asis.Element)
      return Asis.Element
   is
      use Asis.Gela.Elements.Decl;

      Result : Function_Declaration_Ptr := new Function_Declaration_Node;
   begin
      Set_Enclosing_Element (Result.all, Parent);
      Set_Enclosing_Compilation_Unit
        (Result.all, Enclosing_Compilation_Unit (Parent.all));
      Set_Is_Dispatching_Operation
        (Result.all, Is_Dispatching_Operation (Item.all));
      Set_Trait_Kind (Result.all, An_Ordinary_Trait);
      Set_Instance (Asis.Element (Result), Item);

      return Asis.Element (Result);
   end Clone_Function;

   -------------------
   -- Clone_Package --
   -------------------

   function Clone_Package
     (Item   : Asis.Element;
      Parent : Asis.Element)
      return Asis.Element
   is
      use Asis.Gela.Elements.Decl;

      Result : Package_Declaration_Ptr := new Package_Declaration_Node;
   begin
      Set_Enclosing_Element (Result.all, Parent);
      Set_Enclosing_Compilation_Unit
        (Result.all, Enclosing_Compilation_Unit (Parent.all));
      Set_Instance (Asis.Element (Result), Item);

      return Asis.Element (Result);
   end Clone_Package;

   ---------------------
   -- Clone_Procedure --
   ---------------------

   function Clone_Procedure
     (Item   : Asis.Element;
      Parent : Asis.Element)
      return Asis.Element
   is
      use Asis.Gela.Elements.Decl;

      Result : Procedure_Declaration_Ptr := new Procedure_Declaration_Node;
   begin
      Set_Enclosing_Element (Result.all, Parent);
      Set_Enclosing_Compilation_Unit
        (Result.all, Enclosing_Compilation_Unit (Parent.all));
      Set_Is_Dispatching_Operation
        (Result.all, Is_Dispatching_Operation (Item.all));
      Set_Trait_Kind (Result.all, An_Ordinary_Trait);
      Set_Instance (Asis.Element (Result), Item);

      return Asis.Element (Result);
   end Clone_Procedure;

   ---------------------
   -- Set_Declaration --
   ---------------------

   procedure Set_Declaration
     (Result : access Elements.Declaration_Node'Class;
      Object : in     Cloner_Class;
      Inst   : in     Asis.Declaration;
      Name   : in     Asis.Defining_Name)
   is
      use Asis.Elements;
      use Asis.Gela.Lists;
      use Asis.Gela.Elements;
      use Asis.Gela.Elements.Decl;
      use Primary_Defining_Name_Lists;
      Name_List : Asis.Element;
      Formal    : Asis.Declaration := Enclosing_Element (Name);
      Node      : Package_Instantiation_Node'Class
        renames Package_Instantiation_Node'Class (Inst.all);
   begin
      Set_Enclosing_Element (Result.all, Inst);
      Set_Enclosing_Compilation_Unit
        (Result.all, Enclosing_Compilation_Unit (Inst.all));
      Set_Declaration_Origin (Result.all, An_Explicit_Declaration);

      Name_List := Lists.Primary_Defining_Name_Lists.Deep_Copy
        ((1 => Name), Object, Asis.Element (Result));

      Set_Names (Result.all, Name_List);
      Set_Instance (Asis.Element (Result), Formal);
   end Set_Declaration;

   ---------------------
   -- New_Direct_Name --
   ---------------------

   type Base_Identifier_Access is
     access all Asis.Gela.Elements.Expr.Base_Identifier_Node'Class;

   function New_Direct_Name
     (Inst   : Asis.Declaration;
      Name   : Asis.Defining_Name) return Asis.Expression
   is
      use Asis.Elements;
      use Asis.Declarations;
      use Asis.Gela.Elements.Expr;

      Result : Base_Identifier_Access;
   begin
      case Defining_Name_Kind (Name) is
         when A_Defining_Identifier =>
            Result := new Identifier_Node;
         when A_Defining_Operator_Symbol =>
            Result := new Operator_Symbol_Node;
            Set_Operator_Kind
              (Operator_Symbol_Node (Result.all),
               Operator_Kind (Name));
         when others =>
            raise Internal_Error;
      end case;

      Set_Name_Image (Result.all, Defining_Name_Image (Name));
      Set_Enclosing_Element (Result.all, Asis.Nil_Element);  --  Mark the Name
--      Set_Enclosing_Element (Result.all, Inst);
      Set_Start_Position (Result.all, (1, 1));
      Set_End_Position (Result.all, Nil_Text_Position);
      Set_Enclosing_Compilation_Unit
        (Result.all, Enclosing_Compilation_Unit (Inst.all));

      return Asis.Expression (Result);
   end New_Direct_Name;

   --------------------------------
   -- New_Normalized_Association --
   --------------------------------

   procedure New_Normalized_Association
     (Inst     : in     Asis.Declaration;
      Name     : in     Asis.Defining_Name;
      Actual   : in out Asis.Expression;
      With_Box : in     Boolean)
   is
      use Asis.Elements;
      use Asis.Declarations;
      use Asis.Gela.Elements.Decl;
      use Asis.Gela.Elements.Assoc;

      Formal : Asis.Declaration := Enclosing_Element (Name);
      Result : Generic_Association_Ptr := new Generic_Association_Node;
      Node   : Formal_Package_Declaration_With_Box_Node'Class renames
        Formal_Package_Declaration_With_Box_Node'Class (Inst.all);
   begin
      if Assigned (Actual) then
         null;
      elsif With_Box then
         declare
            use Asis.Gela.Elements.Expr;
            Node : constant Box_Expression_Ptr := new Box_Expression_Node;
         begin
            Set_Enclosing_Element (Node.all, Asis.Element (Result));
            Actual := Asis.Element (Node);
         end;
      else
         case Declaration_Kind (Formal) is
            when A_Formal_Object_Declaration =>
               Actual := Initialization_Expression (Formal);

            when A_Formal_Function_Declaration
              | A_Formal_Procedure_Declaration =>
               case Default_Kind (Formal) is
                  when A_Name_Default =>
                     Actual := Formal_Subprogram_Default (Formal);

                  when A_Box_Default =>
                     Actual := New_Direct_Name (Inst, Name);

                  when others =>
                     null;
               end case;

            when others =>
               null;
         end case;

         Set_Is_Defaulted_Association (Result.all, True);
      end if;

      Set_Is_Normalized (Result.all, True);
      Set_Enclosing_Element (Result.all, Inst);
      Set_Enclosing_Compilation_Unit
        (Result.all, Enclosing_Compilation_Unit (Inst.all));
      Set_Formal_Parameter (Result.all, Name);
      Set_Actual_Parameter (Result.all, Actual);
      Set_Start_Position (Result.all, (1, 1));
      Set_End_Position (Result.all, Nil_Text_Position);

      Add_To_Normalized_Generic_Actual_Part (Node, Asis.Element (Result));
   end New_Normalized_Association;

   ----------------------------
   -- Set_Corresponding_Body --
   ----------------------------

   procedure Set_Corresponding_Body (Item, Source : Asis.Element) is
      use Asis.Gela.Elements.Decl;
      Node : Package_Instantiation_Node'Class renames
        Package_Instantiation_Node'Class (Source.all);
   begin
      Set_Corresponding_Body (Node, Item);
   end Set_Corresponding_Body;

   -----------------------------------
   -- Set_Corresponding_Declaration --
   -----------------------------------

   procedure Set_Corresponding_Declaration (Item, Source : Asis.Element) is
      use Asis.Elements;
      use Asis.Gela.Elements.Decl;
   begin
      if Declaration_Kind (Source) = A_Formal_Package_Declaration_With_Box then
         declare
            Node : Formal_Package_Declaration_With_Box_Node renames
              Formal_Package_Declaration_With_Box_Node (Source.all);
         begin
            Set_Corresponding_Declaration (Node, Item);
         end;
      else
         declare
            Node : Package_Instantiation_Node'Class renames
              Package_Instantiation_Node'Class (Source.all);
         begin
            Set_Corresponding_Declaration (Node, Item);
         end;
      end if;
   end Set_Corresponding_Declaration;

   ------------------------
   -- Set_Generic_Actual --
   ------------------------

   procedure Set_Generic_Actual
     (Cloned_Item : Asis.Declaration;
      Formal_Item : Asis.Declaration;
      Instance    : Asis.Declaration)
   is
      use Asis.Elements;
      use Asis.Gela.Elements.Decl;
      Formal : Asis.Declaration;
      Actual : Asis.Expression;
      List   : constant Asis.Element_List :=
        Normalized_Generic_Actual_Part (Instance.all);
   begin
      for J in List'Range loop
         Formal := Enclosing_Element (Expressions.Formal_Parameter (List (J)));

         if Is_Equal (Formal, Formal_Item) then
            Actual := Expressions.Actual_Parameter (List (J));
         end if;
      end loop;

      if Assigned (Actual) then
         case Declaration_Kind (Cloned_Item) is
            when A_Formal_Type_Declaration =>
               Set_Generic_Actual
                 (Formal_Type_Declaration_Node (Cloned_Item.all), Actual);
            when A_Formal_Package_Declaration |
              A_Formal_Package_Declaration_With_Box
              =>
               Set_Generic_Actual
                 (Formal_Package_Declaration_With_Box_Node'Class
                  (Cloned_Item.all), Actual);
            when A_Formal_Procedure_Declaration |
              A_Formal_Function_Declaration
              =>
               Set_Generic_Actual
                 (Formal_Procedure_Declaration_Node'Class (Cloned_Item.all),
                  Actual);

            when A_Formal_Object_Declaration =>
               Set_Generic_Actual
                 (Formal_Object_Declaration_Node (Cloned_Item.all), Actual);

            when others =>
               null;
         end case;
      end if;
   end Set_Generic_Actual;

   -------------------------
   -- Set_Generic_Element --
   -------------------------

   procedure Set_Generic_Element (Item, Source : Asis.Element) is
      use Asis.Gela.Elements.Expr;
      Node : Base_Identifier_Node'Class renames
        Base_Identifier_Node'Class (Item.all);
   begin
      Set_Corresponding_Generic_Element (Node, Source);
      Element_Utils.Set_Resolved (Item, (1 => Source));
   end Set_Generic_Element;

   ------------------
   -- Set_Instance --
   ------------------

   procedure Set_Instance (Item, Source : Asis.Element) is
      use Asis.Gela.Elements;

      Result : Base_Element_Ptr := Base_Element_Ptr (Item);
   begin
      Set_Is_Part_Of_Instance (Result.all, True);
      Set_Start_Position (Result.all, (1, 1));
      Set_End_Position (Result.all, Nil_Text_Position);

      if Element_Kind (Item.all) = A_Defining_Name then
         Set_Corresponding_Generic_Element
           (Defining_Name_Node (Item.all), Source);
      end if;
   end Set_Instance;

end Asis.Gela.Instances.Utils;



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
