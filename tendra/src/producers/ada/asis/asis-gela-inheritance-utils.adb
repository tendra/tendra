with Asis.Gela.Elements.Expr;
with Asis.Gela.Elements.Decl;
with Asis.Gela.Elements.Defs;
with Asis.Gela.Element_Utils;
--  with Asis.Gela.Elements.Def_Names;

package body Asis.Gela.Inheritance.Utils is

   --------------------
   -- Clone_Function --
   --------------------

   function Clone_Function
     (Item   : Asis.Element;
      Parent : Asis.Element)
      return Asis.Element
   is
      use Asis.Gela.Elements.Decl;

      Result : constant Function_Declaration_Ptr :=
        new Function_Declaration_Node;
   begin
      Set_Enclosing_Element (Result.all, Parent);
      Set_Is_Part_Of_Instance (Result.all, False);
      Set_Enclosing_Compilation_Unit (Result.all,
        Enclosing_Compilation_Unit (Parent.all));
      Set_Is_Dispatching_Operation
        (Result.all, Is_Dispatching_Operation (Item.all));
      Set_Trait_Kind (Result.all, An_Ordinary_Trait);
      Set_Inherited (Asis.Element (Result));
      Set_Corresponding_Type (Result.all, Parent);
      Set_Corresponding_Subprogram_Derivation
        (Result.all, Item);

      return Asis.Element (Result);
   end Clone_Function;

   ---------------------
   -- Clone_Procedure --
   ---------------------

   function Clone_Procedure
     (Item   : Asis.Element;
      Parent : Asis.Element)
      return Asis.Element
   is
      use Asis.Gela.Elements.Decl;

      Result : constant Procedure_Declaration_Ptr :=
        new Procedure_Declaration_Node;
   begin
      Set_Enclosing_Element (Result.all, Parent);
      Set_Is_Part_Of_Instance (Result.all, False);
      Set_Enclosing_Compilation_Unit (Result.all,
        Enclosing_Compilation_Unit (Parent.all));
      Set_Is_Dispatching_Operation
        (Result.all, Is_Dispatching_Operation (Item.all));
      Set_Trait_Kind (Result.all, An_Ordinary_Trait);
      Set_Inherited (Asis.Element (Result));
      Set_Corresponding_Type (Result.all, Parent);
      Set_Corresponding_Subprogram_Derivation
        (Result.all, Item);

      return Asis.Element (Result);
   end Clone_Procedure;

   ----------------
   -- Clone_Type --
   ----------------

   function Clone_Type
     (Parent : Asis.Element;
      Tipe   : Classes.Type_Info) return Asis.Element
   is
      use Asis.Gela.Elements.Expr;

      Result : constant Identifier_Ptr := new Identifier_Node;
      Decl   : constant Asis.Declaration := Classes.Get_Declaration (Tipe);
      List   : constant Asis.Defining_Name_List := Names (Decl.all);
   begin
      Set_Enclosing_Element (Result.all, Parent);
      Set_Is_Part_Of_Instance (Result.all, False);
      Set_Enclosing_Compilation_Unit (Result.all,
        Enclosing_Compilation_Unit (Parent.all));

      if List'Length > 0 then
         Set_Name_Image (Result.all, Defining_Name_Image (List (1).all));
         Element_Utils.Set_Resolved (Asis.Element (Result), List);
      else
         Set_Corresponding_Name_Declaration (Result.all, Decl);
      end if;

      Set_Inherited (Asis.Element (Result));

      return Asis.Element (Result);
   end Clone_Type;

   -------------------
   -- Set_Inherited --
   -------------------

   procedure Set_Inherited (Item : Asis.Element) is
      use Asis.Gela.Elements;

      Result : constant Base_Element_Ptr := Base_Element_Ptr (Item);
   begin
      Set_Is_Part_Of_Implicit (Result.all, True);
      Set_Is_Part_Of_Inherited (Result.all, True);
      Set_Start_Position (Result.all, (1, 1));
      Set_End_Position (Result.all, Nil_Text_Position);

      if Element_Kind (Result.all) = A_Declaration then
         Set_Declaration_Origin
           (Declaration_Node (Item.all), An_Implicit_Inherited_Declaration);
      end if;
   end Set_Inherited;

   ------------------------
   -- Set_Result_Profile --
   ------------------------

   procedure Set_Result_Profile
     (Funct : Asis.Declaration;
      Tipe  : Classes.Type_Info)
   is
      use Asis.Gela.Elements.Defs;
      use Asis.Gela.Elements.Decl;

      Mark   : constant Asis.Element := Clone_Type (Funct, Tipe);
      Ind    : constant Subtype_Indication_Ptr := new Subtype_Indication_Node;
      Result : Function_Declaration_Node
        renames Function_Declaration_Node (Funct.all);
   begin
      Set_Enclosing_Element (Ind.all, Funct);
      Set_Is_Part_Of_Instance (Ind.all, False);
      Set_Inherited (Asis.Element (Ind));
      Set_Enclosing_Compilation_Unit (Ind.all,
        Enclosing_Compilation_Unit (Funct.all));
      Set_Subtype_Mark (Ind.all, Mark);
      Set_Result_Subtype (Result, Asis.Element (Ind));
   end Set_Result_Profile;

end Asis.Gela.Inheritance.Utils;



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
