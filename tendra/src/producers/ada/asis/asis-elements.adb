------------------------------------------------------------------------------
--                           G E L A   A S I S                              --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA$
--  Purpose:
--  Procedural wrapper over Object-Oriented ASIS implementation

with XASIS.Utils;

package body Asis.Elements is

   ----------------------------
   -- Access_Definition_Kind --
   ----------------------------

   function Access_Definition_Kind
     (Definition : Asis.Definition)
      return Asis.Access_Definition_Kinds
   is
   begin
      if Assigned (Definition) then
         return Access_Definition_Kind (Definition.all);
      else
         return Not_An_Access_Definition;
      end if;
   end Access_Definition_Kind;

   ----------------------
   -- Access_Type_Kind --
   ----------------------

   function Access_Type_Kind
     (Definition : in Asis.Access_Type_Definition)
      return Asis.Access_Type_Kinds
   is
   begin
      if Assigned (Definition) then
         return Access_Type_Kind (Definition.all);
      else
         return Not_An_Access_Type_Definition;
      end if;
   end Access_Type_Kind;

   ----------------------
   -- Association_Kind --
   ----------------------

   function Association_Kind
     (Association : in Asis.Association)
      return Asis.Association_Kinds
   is
   begin
      if Assigned (Association) then
         return Association_Kind (Association.all);
      else
         return Not_An_Association;
      end if;
   end Association_Kind;

   --------------------
   -- Attribute_Kind --
   --------------------

   function Attribute_Kind
     (Expression : in Asis.Expression)
      return Asis.Attribute_Kinds
   is
   begin
      if Assigned (Expression) then
         return Attribute_Kind (Expression.all);
      else
         return Not_An_Attribute;
      end if;
   end Attribute_Kind;

   -----------------
   -- Clause_Kind --
   -----------------

   function Clause_Kind
     (Clause : in Asis.Clause)
      return Asis.Clause_Kinds
   is
   begin
      if Assigned (Clause) then
         return Clause_Kind (Clause.all);
      else
         return Not_A_Clause;
      end if;
   end Clause_Kind;

   -------------------------
   -- Compilation_Pragmas --
   -------------------------

   function Compilation_Pragmas
     (Compilation_Unit : in Asis.Compilation_Unit)
      return Asis.Pragma_Element_List
   is
   begin
      Check_Nil_Unit (Compilation_Unit, "Compilation_Pragmas");
      return Compilation_Pragmas (Compilation_Unit.all, True);
   end Compilation_Pragmas;

   ---------------------------
   -- Configuration_Pragmas --
   ---------------------------

   function Configuration_Pragmas
     (The_Context : in Asis.Context)
      return Asis.Pragma_Element_List
   is
   begin
      Check_Context (The_Context);
      return Configuration_Pragmas (The_Context.all);
   end Configuration_Pragmas;

   ---------------------
   -- Constraint_Kind --
   ---------------------

   function Constraint_Kind
     (Definition : in Asis.Constraint)
      return Asis.Constraint_Kinds
   is
   begin
      if Assigned (Definition) then
         return Constraint_Kind (Definition.all);
      else
         return Not_A_Constraint;
      end if;
   end Constraint_Kind;

   -----------------------------
   -- Context_Clause_Elements --
   -----------------------------

   function Context_Clause_Elements
     (Compilation_Unit : in Asis.Compilation_Unit;
      Include_Pragmas  : in Boolean := False)
      return Asis.Context_Clause_List
   is
   begin
      Check_Nil_Unit (Compilation_Unit, "Context_Clause_Elements");
      return Context_Clause_Elements (Compilation_Unit.all, Include_Pragmas);
   end Context_Clause_Elements;

   ---------------------------
   -- Corresponding_Pragmas --
   ---------------------------

   function Corresponding_Pragmas
     (Element : in Asis.Element)
      return Asis.Pragma_Element_List
   is
   begin
      Check_Nil_Element (Element, "Corresponding_Pragmas");
      return Corresponding_Pragmas (Element.all, True);
   end Corresponding_Pragmas;

   -----------------
   -- Debug_Image --
   -----------------

   function Debug_Image (Element : in Asis.Element) return Wide_String
     renames XASIS.Utils.Debug_Image;

   ----------------------
   -- Declaration_Kind --
   ----------------------

   function Declaration_Kind
     (Declaration : in Asis.Declaration)
      return Asis.Declaration_Kinds
   is
   begin
      if Assigned (Declaration) then
         return Declaration_Kind (Declaration.all);
      else
         return Not_A_Declaration;
      end if;
   end Declaration_Kind;

   ------------------------
   -- Declaration_Origin --
   ------------------------

   function Declaration_Origin
     (Declaration : in Asis.Declaration)
      return Asis.Declaration_Origins
   is
   begin
      if Assigned (Declaration) then
         return Declaration_Origin (Declaration.all);
      else
         return Not_A_Declaration_Origin;
      end if;
   end Declaration_Origin;

   ------------------
   -- Default_Kind --
   ------------------

   function Default_Kind
     (Declaration : in Asis.Generic_Formal_Parameter)
      return Asis.Subprogram_Default_Kinds
   is
   begin
      if Assigned (Declaration) then
         return Default_Kind (Declaration.all);
      else
         return Not_A_Default;
      end if;
   end Default_Kind;

   ------------------------
   -- Defining_Name_Kind --
   ------------------------

   function Defining_Name_Kind
     (Defining_Name : in Asis.Defining_Name)
      return Asis.Defining_Name_Kinds
   is
   begin
      if Assigned (Defining_Name) then
         return Defining_Name_Kind (Defining_Name.all);
      else
         return Not_A_Defining_Name;
      end if;
   end Defining_Name_Kind;

   ---------------------
   -- Definition_Kind --
   ---------------------

   function Definition_Kind
     (Definition : in Asis.Definition)
      return Asis.Definition_Kinds
   is
   begin
      if Assigned (Definition) then
         return Definition_Kind (Definition.all);
      else
         return Not_A_Definition;
      end if;
   end Definition_Kind;

   -------------------------
   -- Discrete_Range_Kind --
   -------------------------

   function Discrete_Range_Kind
     (Definition : in Asis.Discrete_Range)
      return Asis.Discrete_Range_Kinds
   is
   begin
      if Assigned (Definition) then
         return Discrete_Range_Kind (Definition.all);
      else
         return Not_A_Discrete_Range;
      end if;
   end Discrete_Range_Kind;

   ------------------
   -- Element_Kind --
   ------------------

   function Element_Kind
     (Element : in Asis.Element)
      return Asis.Element_Kinds
   is
   begin
      if Assigned (Element) then
         return Element_Kind (Element.all);
      else
         return Not_An_Element;
      end if;
   end Element_Kind;

   --------------------------------
   -- Enclosing_Compilation_Unit --
   --------------------------------

   function Enclosing_Compilation_Unit
     (Element : in Asis.Element)
      return Asis.Compilation_Unit
   is
   begin
      Check_Nil_Element (Element, "Enclosing_Compilation_Unit");
      return Enclosing_Compilation_Unit (Element.all);
   end Enclosing_Compilation_Unit;

   -----------------------
   -- Enclosing_Element --
   -----------------------

   function Enclosing_Element
     (Element : in Asis.Element)
      return Asis.Element
   is
   begin
      Check_Nil_Element (Element, "Enclosing_Element");
      return Enclosing_Element (Element.all);
   end Enclosing_Element;

   -----------------------
   -- Enclosing_Element --
   -----------------------

   function Enclosing_Element
     (Element                    : in Asis.Element;
      Expected_Enclosing_Element : in Asis.Element)
      return Asis.Element
   is
   begin
      Check_Nil_Element (Element, "Enclosing_Element");
      return Enclosing_Element (Element.all);
   end Enclosing_Element;

   ---------------------
   -- Expression_Kind --
   ---------------------

   function Expression_Kind
     (Expression : in Asis.Expression)
      return Asis.Expression_Kinds
   is
   begin
      if Assigned (Expression) then
         return Expression_Kind (Expression.all);
      else
         return Not_An_Expression;
      end if;
   end Expression_Kind;

   ----------------------
   -- Formal_Type_Kind --
   ----------------------

   function Formal_Type_Kind
     (Definition : in Asis.Formal_Type_Definition)
      return Asis.Formal_Type_Kinds
   is
   begin
      if Assigned (Definition) then
         return Formal_Type_Definition_Kind (Definition.all);
      else
         return Not_A_Formal_Type_Definition;
      end if;
   end Formal_Type_Kind;

   -----------------
   -- Has_Limited --
   -----------------

   function Has_Limited (Element : in Asis.Element) return Boolean is
   begin
      if Assigned (Element) then
         return Has_Limited (Element.all);
      else
         return False;
      end if;
   end Has_Limited;

   -----------------
   -- Has_Private --
   -----------------

   function Has_Private (Element : in Asis.Element) return Boolean is
   begin
      if Assigned (Element) then
         return Has_Private (Element.all);
      else
         return False;
      end if;
   end Has_Private;

   ------------------
   -- Has_Abstract --
   ------------------

   function Has_Abstract (Element : in Asis.Element) return Boolean is
   begin
      if Assigned (Element) then
         return Has_Abstract (Element.all);
      else
         return False;
      end if;
   end Has_Abstract;

   -----------------
   -- Has_Reverse --
   -----------------

   function Has_Reverse (Element : in Asis.Element) return Boolean is
   begin
      return Trait_Kind (Element) = A_Reverse_Trait;
   end Has_Reverse;

   -----------------
   -- Has_Aliased --
   -----------------

   function Has_Aliased (Element : in Asis.Element) return Boolean is
   begin
      return Trait_Kind (Element) = An_Aliased_Trait;
   end Has_Aliased;

   ----------------------
   -- Has_Synchronized --
   ----------------------

   function Has_Synchronized (Element : in Asis.Element) return Boolean is
   begin
      if Assigned (Element) then
         return Has_Synchronized (Element.all);
      else
         return False;
      end if;
   end Has_Synchronized;

   -------------------
   -- Has_Protected --
   -------------------

   function Has_Protected (Element : in Asis.Element) return Boolean is
   begin
      if Assigned (Element) then
         return Has_Protected (Element.all);
      else
         return False;
      end if;
   end Has_Protected;

   --------------
   -- Has_Task --
   --------------

   function Has_Task (Element : in Asis.Element) return Boolean is
   begin
      if Assigned (Element) then
         return Has_Task (Element.all);
      else
         return False;
      end if;
   end Has_Task;

   ------------------------
   -- Has_Null_Exclusion --
   ------------------------

   function Has_Null_Exclusion (Element : Asis.Element) return Boolean is
   begin
      if Assigned (Element) then
         return Has_Null_Exclusion (Element.all);
      else
         return False;
      end if;
   end Has_Null_Exclusion;

   ----------
   -- Hash --
   ----------

   function Hash (Element : in Asis.Element) return Asis.ASIS_Integer is
   begin
      if Assigned (Element) then
         return Hash (Element.all);
      else
         return 0;
      end if;
   end Hash;

   --------------------
   -- Interface_Kind --
   --------------------

   function Interface_Kind
     (Definition : Asis.Definition)
     return Asis.Interface_Kinds is
   begin
      if Assigned (Definition) then
         if Type_Kind (Definition) = An_Interface_Type_Definition or
           Formal_Type_Kind (Definition) =
           A_Formal_Interface_Type_Definition
         then
            if Has_Task (Definition.all) then
               return A_Task_Interface;
            elsif Has_Limited (Definition.all) then
               return A_Limited_Interface;
            elsif Has_Protected (Definition.all) then
               return A_Protected_Interface;
            elsif Has_Synchronized (Definition.all) then
               return A_Synchronized_Interface;
            else
               return An_Ordinary_Interface;
            end if;
         end if;
      end if;

      return Not_An_Interface;
   end Interface_Kind;

   ----------------------------
   -- Is_Abstract_Subprogram --
   ----------------------------

   function Is_Abstract_Subprogram
     (Element : in Asis.Element)
      return Boolean
   is
   begin
      case Declaration_Kind (Element) is
         when A_Procedure_Declaration |
           A_Function_Declaration |
           A_Formal_Procedure_Declaration |
           A_Formal_Function_Declaration =>
            return Has_Abstract (Element.all);
         when others =>
            return False;
      end case;
   end Is_Abstract_Subprogram;

   --------------
   -- Is_Equal --
   --------------

   function Is_Equal
     (Left  : in Asis.Element;
      Right : in Asis.Element)
      return Boolean
     renames Asis.Is_Equal;

   ------------------
   -- Is_Identical --
   ------------------

   function Is_Identical
     (Left  : in Asis.Element;
      Right : in Asis.Element)
      return Boolean
     renames Asis.Is_Equal;

   ------------
   -- Is_Nil --
   ------------

   function Is_Nil (Right : in Asis.Element) return Boolean is
   begin
      return not Assigned (Right);
   end Is_Nil;

   ------------
   -- Is_Nil --
   ------------

   function Is_Nil (Right : in Asis.Element_List) return Boolean is
   begin
      return Right'Length = 0;
   end Is_Nil;

   -----------------------
   -- Is_Null_Procedure --
   -----------------------

   function Is_Null_Procedure (Element : in Asis.Element) return Boolean is
   begin
      if Assigned (Element) then
         if Declaration_Kind (Element) = A_Formal_Procedure_Declaration then
            return Expression_Kind (Formal_Subprogram_Default (Element.all))
              = A_Null_Literal;
         else
            return Is_Null_Procedure (Element.all);
         end if;
      else
         return False;
      end if;
   end Is_Null_Procedure;

   -------------------------
   -- Is_Part_Of_Implicit --
   -------------------------

   function Is_Part_Of_Implicit (Element : in Asis.Element) return Boolean is
   begin
      if Assigned (Element) then
         return Is_Part_Of_Implicit (Element.all);
      else
         return False;
      end if;
   end Is_Part_Of_Implicit;

   --------------------------
   -- Is_Part_Of_Inherited --
   --------------------------

   function Is_Part_Of_Inherited
     (Element : in Asis.Element)
      return Boolean
   is
   begin
      if Assigned (Element) then
         return Is_Part_Of_Inherited (Element.all);
      else
         return False;
      end if;
   end Is_Part_Of_Inherited;

   -------------------------
   -- Is_Part_Of_Instance --
   -------------------------

   function Is_Part_Of_Instance (Element : in Asis.Element) return Boolean is
   begin
      if Assigned (Element) then
         return Is_Part_Of_Instance (Element.all);
      else
         return False;
      end if;
   end Is_Part_Of_Instance;

   ---------------
   -- Mode_Kind --
   ---------------

   function Mode_Kind
     (Declaration : in Asis.Declaration)
      return Asis.Mode_Kinds
   is
   begin
      if Assigned (Declaration) then
         return Mode_Kind (Declaration.all);
      else
         return Not_A_Mode;
      end if;
   end Mode_Kind;

   -------------------
   -- Operator_Kind --
   -------------------

   function Operator_Kind
     (Element : in Asis.Element)
      return Asis.Operator_Kinds
   is
   begin
      if Assigned (Element) then
         return Operator_Kind (Element.all);
      else
         return Not_An_Operator;
      end if;
   end Operator_Kind;

   ---------------
   -- Path_Kind --
   ---------------

   function Path_Kind (Path : in Asis.Path) return Asis.Path_Kinds is
   begin
      if Assigned (Path) then
         return Path_Kind (Path.all);
      else
         return Not_A_Path;
      end if;
   end Path_Kind;

   ----------------------------------
   -- Pragma_Argument_Associations --
   ----------------------------------

   function Pragma_Argument_Associations
     (Pragma_Element : in Asis.Pragma_Element)
      return Asis.Association_List
   is
   begin
      Check_Nil_Element (Pragma_Element, "Pragma_Argument_Associations");
      return Pragma_Argument_Associations (Pragma_Element.all);
   end Pragma_Argument_Associations;

   -----------------
   -- Pragma_Kind --
   -----------------

   function Pragma_Kind
     (Pragma_Element : in Asis.Pragma_Element)
      return Asis.Pragma_Kinds
   is
   begin
      if Assigned (Pragma_Element) then
         return Pragma_Kind (Pragma_Element.all);
      else
         return Not_A_Pragma;
      end if;
   end Pragma_Kind;

   -----------------------
   -- Pragma_Name_Image --
   -----------------------

   function Pragma_Name_Image
     (Pragma_Element : in Asis.Pragma_Element)
      return Program_Text
   is
   begin
      Check_Nil_Element (Pragma_Element, "Pragma_Name_Image");
      return Pragma_Name_Image (Pragma_Element.all);
   end Pragma_Name_Image;

   -------------
   -- Pragmas --
   -------------

   function Pragmas
     (The_Element : in Asis.Element)
      return Asis.Pragma_Element_List
   is
   begin
      Check_Nil_Element (The_Element, "Pragmas");
      return Pragmas (The_Element.all);
   end Pragmas;

   --------------------------------
   -- Representation_Clause_Kind --
   --------------------------------

   function Representation_Clause_Kind
     (Clause : in Asis.Representation_Clause)
      return Asis.Representation_Clause_Kinds
   is
   begin
      if Assigned (Clause) then
         return Representation_Clause_Kind (Clause.all);
      else
         return Not_A_Representation_Clause;
      end if;
   end Representation_Clause_Kind;

   --------------------
   -- Root_Type_Kind --
   --------------------

   function Root_Type_Kind
     (Definition : in Asis.Root_Type_Definition)
      return Asis.Root_Type_Kinds
   is
   begin
      if Assigned (Definition) then
         return Root_Type_Kind (Definition.all);
      else
         return Not_A_Root_Type_Definition;
      end if;
   end Root_Type_Kind;

   --------------------
   -- Statement_Kind --
   --------------------

   function Statement_Kind
     (Statement : in Asis.Statement)
      return Asis.Statement_Kinds
   is
   begin
      if Assigned (Statement) then
         return Statement_Kind (Statement.all);
      else
         return Not_A_Statement;
      end if;
   end Statement_Kind;

   ----------------
   -- Trait_Kind --
   ----------------

   function Trait_Kind
     (Element : in Asis.Element)
      return Asis.Trait_Kinds
   is
   begin
      if Assigned (Element) then
         return Trait_Kind (Element.all);
      else
         return Not_A_Trait;
      end if;
   end Trait_Kind;

   ---------------
   -- Type_Kind --
   ---------------

   function Type_Kind
     (Definition : in Asis.Type_Definition)
      return Asis.Type_Kinds
   is
   begin
      if Assigned (Definition) then
         return Type_Definition_Kind (Definition.all);
      else
         return Not_A_Type_Definition;
      end if;
   end Type_Kind;

   ----------------------
   -- Unit_Declaration --
   ----------------------

   function Unit_Declaration
     (Compilation_Unit : in Asis.Compilation_Unit)
      return Asis.Declaration
   is
   begin
      Check_Nil_Unit (Compilation_Unit, "Unit_Declaration");
      return Unit_Declaration (Compilation_Unit.all);
   end Unit_Declaration;

end Asis.Elements;


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
