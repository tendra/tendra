------------------------------------------------------------------------------
--                           G E L A   A S I S                              --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA$:

with XASIS.Utils;

with Asis.Elements;
with Asis.Extensions;
with Asis.Definitions;
with Asis.Expressions;
with Asis.Declarations;
with Asis.Gela.Classes;

package body Asis.Gela.Static is
   use Asis.Elements;

   package E renames Asis.Extensions;

   --  return function declaration or attribute_reference
   function Statically_Denote
     (Element : in     Asis.Expression) return Asis.Element;

   function Has_Static_Params
     (Call    : in     Asis.Expression;
      Func    : in     Asis.Element) return Boolean;

   function Is_Static_Function
     (Element : in     Asis.Element;
      Place   : in     Asis.Element) return Boolean;

   function Is_Statically_Constrained
     (Place   : in     Asis.Element;
      Element : in     Asis.Declaration) return Boolean;

   function Is_Static_Range
     (Place   : in     Asis.Element;
      Element : in     Asis.Range_Constraint) return Boolean;

   function Is_Static_Discrete_Subtype
     (Place   : in     Asis.Element;
      Element : in     Asis.Definition) return Boolean;

   function Is_Static_Bound
     (Place   : in     Asis.Element;
      Element : in     Asis.Expression) return Boolean;

   function Is_Static_Indication
     (Place   : in     Asis.Element;
      Element : in     Asis.Definition) return Boolean;

   function Is_Static_Constraint
     (Place   : in     Asis.Element;
      Element : in     Asis.Constraint) return Boolean;

   function Is_Static_Constant
     (Place   : in     Asis.Element;
      Element : in     Asis.Declaration) return Boolean;

   function Denote_Static_Subtype
     (Place      : Asis.Element;
      Mark       : Asis.Expression;
      Constraint : Asis.Constraint := Asis.Nil_Element;
      Scalar     : Boolean := False) return Boolean;

   function Is_Descendant_Of_Formal (Info : Classes.Type_Info) return Boolean;

   ---------------------------
   -- Denote_Static_Subtype --
   ---------------------------

   function Denote_Static_Subtype
     (Place      : Asis.Element;
      Mark       : Asis.Expression;
      Constraint : Asis.Constraint := Asis.Nil_Element;
      Scalar     : Boolean := False) return Boolean
   is
      use Asis.Gela.Classes;
      Info   : Type_Info := Type_From_Subtype_Mark (Mark, Place);
      Constr : Asis.Constraint := Constraint;
      Name   : Asis.Expression := Mark;
      Decl   : Asis.Declaration;
      Def    : Asis.Definition;
   begin
      if Is_Descendant_Of_Formal (Info) then
         return False;
      elsif Is_String (Info) then
         if Scalar then
            return False;
         end if;

         declare
            use Asis.Definitions;
            Def  : Asis.Definition := Get_Type_Def (Info);
            Comp : Asis.Definition := Array_Component_Definition (Def);
            Ind  : Asis.Definition := Component_Subtype_Indication (Comp);
         begin
            if not Is_Static_Indication (Place, Ind) then
               return False;
            end if;

            case Type_Kind (Def) is
               when An_Unconstrained_Array_Definition =>
                  if not Denote_Static_Subtype
                    (Place, Index_Subtype_Definitions (Def) (1))
                  then
                     return False;
                  end if;
               when A_Constrained_Array_Definition =>
                  if not Is_Static_Discrete_Subtype
                    (Place, Discrete_Subtype_Definitions (Def) (1))
                  then
                     return False;
                  end if;
               when others =>
                  return False;
            end case;
         end;
      elsif not Is_Scalar (Info) then
         return False;
      end if;

      loop
         if not Is_Static_Constraint (Place, Constr) then
            return False;
         end if;

         case Expression_Kind (Name) is
            when An_Attribute_Reference =>
               return Attribute_Kind (Name) = A_Base_Attribute;
            when others =>
               Decl := XASIS.Utils.Selected_Name_Declaration (Name, False);

               case Declaration_Kind (Decl) is
                  when A_Subtype_Declaration =>
                     Def := Asis.Declarations.Type_Declaration_View (Decl);
                     Name := Asis.Definitions.Subtype_Mark (Def);
                     Constr := Asis.Definitions.Subtype_Constraint (Def);
                  when An_Ordinary_Type_Declaration =>
                     return True;
                  when others =>
                     return False;
               end case;
         end case;
      end loop;
   end Denote_Static_Subtype;

   -----------------------
   -- Has_Static_Params --
   -----------------------

   function Has_Static_Params
     (Call    : in     Asis.Expression;
      Func    : in     Asis.Element) return Boolean
   is
      use Asis.Expressions;
      Norm : constant Boolean :=
        Expression_Kind (Func) /= An_Attribute_Reference;
      Args : Asis.Association_List := Function_Call_Parameters (Call, Norm);
   begin
      for J in Args'Range loop
         if not E.Is_Static_Expression (Actual_Parameter (Args (J))) then
            return False;
         end if;
      end loop;

      return True;
   end Has_Static_Params;

   -----------------------------
   -- Is_Descendant_Of_Formal --
   -----------------------------

   function Is_Descendant_Of_Formal
     (Info : Classes.Type_Info) return Boolean
   is
      use Asis.Gela.Classes;
      Temp : Type_Info := Info;
   begin
      while not Is_Not_Type (Temp) loop
         case Definition_Kind (Get_Type_Def (Temp)) is
            when A_Formal_Type_Definition =>
               return True;
            when others =>
               Temp := Parent_Type (Temp);
         end case;
      end loop;

      return False;
   end Is_Descendant_Of_Formal;

   ---------------------
   -- Is_Static_Bound --
   ---------------------

   function Is_Static_Bound
     (Place   : in     Asis.Element;
      Element : in     Asis.Expression) return Boolean
   is
      use Asis.Expressions;
      use Asis.Gela.Classes;

      Info : Type_Info;
      Arr  : Asis.Element;
   begin
      if Denote_Static_Subtype (Place, Prefix (Element), Scalar => True) then
         return True;
      end if;

      Arr  := Statically_Denote (Prefix (Element));
      Info := Type_From_Declaration (Arr, Place);

      if Is_Array (Info) then
         return Is_Statically_Constrained (Place, Arr);
      end if;

      Info := Type_Of_Declaration (Arr, Place);

      return Is_Array (Info) and then Is_Statically_Constrained (Place, Arr);
   end Is_Static_Bound;

   --------------------------
   -- Is_Static_Constraint --
   --------------------------

   function Is_Static_Constraint
     (Place   : in Asis.Element;
      Element : in Asis.Constraint) return Boolean
   is
      use Asis.Definitions;
      use Asis.Expressions;

      To_Do_Error : exception;
   begin
      case Constraint_Kind (Element) is
         when A_Range_Attribute_Reference =>
            return Is_Static_Bound (Place, Range_Attribute (Element));

         when A_Simple_Expression_Range =>
            return E.Is_Static_Expression (Lower_Bound (Element))
              and then E.Is_Static_Expression (Upper_Bound (Element));

         when A_Digits_Constraint | A_Delta_Constraint =>
            return Is_Static_Constraint
              (Place, Real_Range_Constraint (Element));

         when An_Index_Constraint =>
            declare
               List : Asis.Discrete_Range_List :=
                 Discrete_Ranges (Element);
            begin
               for J in List'Range loop
                  if not Is_Static_Discrete_Subtype (Place, List (J)) then
                     return False;
                  end if;
               end loop;

               --  TODO 4.9 (30) (and index subtype of array is static)
               return True;
            end;
         when Not_A_Constraint =>
            return Is_Nil (Element);

         when others =>
            raise To_Do_Error;   --   RM 4.9 (31) why we need it?
      end case;
   end Is_Static_Constraint;

   ---------------------------------------
   -- Is_Statically_Constrained_Subtype --
   ---------------------------------------

   function Is_Statically_Constrained_Subtype
     (Place   : in     Asis.Element;
      Element : in     Asis.Declaration) return Boolean
   is
      use Asis.Definitions;
      use Asis.Declarations;
      Def : Asis.Definition;
   begin
      case Declaration_Kind (Element) is
         when An_Ordinary_Type_Declaration =>
            Def := Type_Declaration_View (Element);
         when A_Variable_Declaration | A_Constant_Declaration =>
            Def := Object_Declaration_View (Element);

            case Definition_Kind (Def) is
               when A_Type_Definition =>
                  null;
               when A_Subtype_Indication =>
                  declare
                     Name : Asis.Expression :=
                       Asis.Definitions.Subtype_Mark (Def);
                     Constr : Asis.Constraint :=
                       Asis.Definitions.Subtype_Constraint (Def);
                     Decl : Asis.Declaration :=
                       XASIS.Utils.Selected_Name_Declaration (Name, False);
                  begin
                     if Is_Nil (Constr) then
                        return Is_Statically_Constrained_Subtype (Place, Decl);
                     else
                        return Is_Static_Constraint (Place, Constr);
                     end if;
                  end;
               when others =>
                  return False;
            end case;
         when others =>
            return False;
      end case;

      case Type_Kind (Def) is
         when A_Constrained_Array_Definition =>
            declare
               List : Asis.Definition_List :=
                 Discrete_Subtype_Definitions (Def);
            begin
               for J in List'Range loop
                  if not Is_Static_Discrete_Subtype (Place, List (J)) then
                     return False;
                  end if;
               end loop;

               return True;
            end;
         when others =>
            return False;
      end case;
   end Is_Statically_Constrained_Subtype;

   -------------------------------
   -- Is_Statically_Constrained --
   -------------------------------

   function Is_Statically_Constrained
     (Place   : in     Asis.Element;
      Element : in     Asis.Declaration) return Boolean
   is
      use Asis.Gela.Classes;
      Info : Type_Info;
   begin
      case Declaration_Kind (Element) is
         when A_Constant_Declaration =>
            if Is_Statically_Constrained_Subtype (Place, Element) then
               return True;
            end if;

            Info := Type_Of_Declaration (Element, Place);

            return Is_String (Info)
              and then Is_Static_Constant (Place, Element);

         when others =>
            return Is_Statically_Constrained_Subtype (Place, Element);
      end case;
   end Is_Statically_Constrained;

   ------------------------
   -- Is_Static_Constant --
   ------------------------

   function Is_Static_Constant
     (Place   : in     Asis.Element;
      Element : in     Asis.Declaration) return Boolean
   is
   begin
      case Declaration_Kind (Element) is
         when An_Object_Renaming_Declaration =>
            declare
               use Asis.Declarations;

               Mark : Asis.Expression :=
                 Declaration_Subtype_Mark (Element);
            begin
               return Denote_Static_Subtype (Place, Mark) and then
                 E.Is_Static_Expression (Renamed_Entity (Element));
            end;

         when A_Constant_Declaration =>
            declare
               use Asis.Declarations;

               View : Asis.Definition :=
                 Object_Declaration_View (Element);
               Init : Asis.Expression :=
                 Initialization_Expression (Element);
            begin
               return Is_Static_Indication (Place, View)
                 and then E.Is_Static_Expression (Init);
            end;

         when others =>
            return False;
      end case;
   end Is_Static_Constant;

   --------------------------------
   -- Is_Static_Discrete_Subtype --
   --------------------------------

   function Is_Static_Discrete_Subtype
     (Place   : in     Asis.Element;
      Element : in     Asis.Definition) return Boolean
   is
      use Asis.Definitions;
   begin
      case Discrete_Range_Kind (Element) is
         when A_Discrete_Subtype_Indication =>
            return Is_Static_Indication (Place, Element);

         when A_Discrete_Range_Attribute_Reference =>
            return Is_Static_Bound (Place, Range_Attribute (Element));

         when A_Discrete_Simple_Expression_Range =>
            return E.Is_Static_Expression (Lower_Bound (Element))
              and then E.Is_Static_Expression (Upper_Bound (Element));

         when others =>
            null;
      end case;

      return False;
   end Is_Static_Discrete_Subtype;

   --------------------------
   -- Is_Static_Expression --
   --------------------------

   function Is_Static_Expression
     (Element : in     Asis.Expression) return Boolean
   is
      use Asis.Expressions;
   begin
      case Expression_Kind (Element) is
         when An_Integer_Literal
           | A_Real_Literal
           | An_Enumeration_Literal
           | A_Character_Literal
           =>
            return True;

         when A_String_Literal =>
            --  TODO
            return True;

         when An_Identifier
           | A_Selected_Component =>
            declare
               Decl : Asis.Declaration :=
                 XASIS.Utils.Selected_Name_Declaration (Element, False);
            begin
               case Declaration_Kind (Decl) is
                  when An_Integer_Number_Declaration
                    | A_Real_Number_Declaration =>
                     return True;

                  when others =>
                     return Is_Static_Constant (Element, Decl);
               end case;
            end;

         when A_Function_Call =>
            declare
               Func : Asis.Element := Statically_Denote (Prefix (Element));
            begin
               return Is_Static_Function (Func, Element)
                 and then Has_Static_Params (Element, Func);
            end;

         when An_Attribute_Reference =>
            case Attribute_Kind (Element) is
               when An_Aft_Attribute
                 | An_Alignment_Attribute
                 | A_Bit_Order_Attribute
                 | A_Delta_Attribute
                 | A_Denorm_Attribute
                 | A_Digits_Attribute
                 | A_Fore_Attribute
                 | A_Machine_Emax_Attribute
                 | A_Machine_Emin_Attribute
                 | A_Machine_Mantissa_Attribute
                 | A_Machine_Overflows_Attribute
                 | A_Machine_Radix_Attribute
                 | A_Machine_Rounds_Attribute
                 | A_Max_Size_In_Storage_Elements_Attribute
                 | A_Model_Emin_Attribute
                 | A_Model_Epsilon_Attribute
                 | A_Model_Mantissa_Attribute
                 | A_Model_Small_Attribute
                 | A_Modulus_Attribute
                 | A_Safe_First_Attribute
                 | A_Safe_Last_Attribute
                 | A_Scale_Attribute
                 | A_Signed_Zeros_Attribute
                 | A_Size_Attribute
                 | A_Small_Attribute
                 | A_Stream_Size_Attribute
                 | A_Wide_Wide_Width_Attribute
                 | A_Wide_Width_Attribute
                 | A_Width_Attribute
                 =>
                  return Denote_Static_Subtype
                    (Element, Prefix (Element), Scalar => True);

               when A_First_Attribute
                 | A_Last_Attribute
                 | A_Length_Attribute
                 =>
                  return Is_Static_Bound (Element, Element);

               when others =>
                  null;
            end case;

         when A_Type_Conversion =>
            declare
               Mark : Asis.Expression :=
                 Converted_Or_Qualified_Subtype_Mark (Element);
               Arg  : Asis.Expression :=
                 Converted_Or_Qualified_Expression (Element);
            begin
               return Denote_Static_Subtype (Element, Mark, Scalar => True)
                 and then E.Is_Static_Expression (Arg);
            end;

         when A_Qualified_Expression =>
            declare
               Mark : Asis.Expression :=
                 Converted_Or_Qualified_Subtype_Mark (Element);
               Arg  : Asis.Expression :=
                 Converted_Or_Qualified_Expression (Element);
            begin
               return Denote_Static_Subtype (Element, Mark)
                 and then E.Is_Static_Expression (Arg);
            end;

         when An_In_Range_Membership_Test
           | A_Not_In_Range_Membership_Test
           =>
            declare
               Rng : Asis.Range_Constraint := Membership_Test_Range (Element);
               Arg : Asis.Expression := Membership_Test_Expression (Element);
            begin
               return E.Is_Static_Expression (Arg)
                 and then Is_Static_Range (Element, Rng);
            end;

         when An_In_Type_Membership_Test
           | A_Not_In_Type_Membership_Test
           =>
            declare
               Mark : Asis.Expression :=
                 Membership_Test_Subtype_Mark (Element);
               Arg  : Asis.Expression := Membership_Test_Expression (Element);
            begin
               return E.Is_Static_Expression (Arg)
                 and then Denote_Static_Subtype (Element, Mark);
            end;

         when An_And_Then_Short_Circuit | An_Or_Else_Short_Circuit =>
            declare
               Left  : Asis.Expression :=
                 Short_Circuit_Operation_Left_Expression (Element);
               Right : Asis.Expression :=
                 Short_Circuit_Operation_Right_Expression (Element);
            begin
               return E.Is_Static_Expression (Left)
                 and then E.Is_Static_Expression (Right);
            end;

         when A_Parenthesized_Expression =>
            return E.Is_Static_Expression (Expression_Parenthesized (Element));

         when others =>
            null;
      end case;

      return False;
   end Is_Static_Expression;

   ------------------------
   -- Is_Static_Function --
   ------------------------

   function Is_Static_Function
     (Element : in     Asis.Element;
      Place   : in     Asis.Element) return Boolean
   is
      function Check (Info : Classes.Type_Info) return Boolean is
         use Asis.Gela.Classes;
      begin
         return Is_Scalar (Info) and then not Is_Descendant_Of_Formal (Info);
      end Check;

   begin
      if Element_Kind (Element) = A_Declaration then
         if XASIS.Utils.Is_Predefined_Operator (Element) then
            declare
               use Asis.Declarations;

               Name   : Asis.Defining_Name :=
                 XASIS.Utils.Declaration_Name (Element);
               Result : Asis.Expression := Result_Profile (Element);
               Info   : Classes.Type_Info :=
                Classes.Type_From_Subtype_Mark (Result, Place);
               List   : Asis.Parameter_Specification_List :=
                 Parameter_Profile (Element);
            begin
               if Operator_Kind (Name) = A_Concatenate_Operator then
                  return Classes.Is_String (Info);
               end if;

               if not Check (Info) then
                  return False;
               end if;

               for J in List'Range loop
                  Info := Classes.Type_Of_Declaration (List (J), Place);

                  if not Check (Info) then
                     return False;
                  end if;
               end loop;

               return True;
            end;
         elsif Declaration_Kind (Element) =
           An_Enumeration_Literal_Specification
         then
            return True;
         end if;

      elsif Expression_Kind (Element) = An_Attribute_Reference then
         declare
            Mark : Asis.Expression   := Asis.Expressions.Prefix (Element);
         begin
            if not Denote_Static_Subtype (Place, Mark, Scalar => True) then
               return False;
            end if;

            case Attribute_Kind (Element) is
               when An_Adjacent_Attribute
                 | A_Ceiling_Attribute
                 | A_Compose_Attribute
                 | A_Copy_Sign_Attribute
                 | An_Exponent_Attribute
                 | A_Floor_Attribute
                 | A_Fraction_Attribute
                 | A_Leading_Part_Attribute
                 | A_Machine_Attribute
                 | A_Machine_Rounding_Attribute
                 | A_Max_Attribute
                 | A_Min_Attribute
                 | A_Mod_Attribute
                 | A_Model_Attribute
                 | A_Pos_Attribute
                 | A_Pred_Attribute
                 | A_Remainder_Attribute
                 | A_Round_Attribute
                 | A_Rounding_Attribute
                 | A_Scaling_Attribute
                 | A_Succ_Attribute
                 | A_Truncation_Attribute
                 | An_Unbiased_Rounding_Attribute
                 | A_Val_Attribute
                 =>
                  return True;

               when others =>
                  null;
            end case;
         end;
      end if;

      return False;
   end Is_Static_Function;

   --------------------------
   -- Is_Static_Indication --
   --------------------------

   function Is_Static_Indication
     (Place   : in     Asis.Element;
      Element : in     Asis.Definition) return Boolean
   is
      Mark : Asis.Expression := Asis.Definitions.Subtype_Mark (Element);
      Cons : Asis.Expression := Asis.Definitions.Subtype_Constraint (Element);
   begin
      return Denote_Static_Subtype (Place, Mark, Cons);
   end Is_Static_Indication;

   ---------------------
   -- Is_Static_Range --
   ---------------------

   function Is_Static_Range
     (Place   : in     Asis.Element;
      Element : in     Asis.Range_Constraint) return Boolean
   is
   begin
      return Is_Static_Constraint (Place, Element);
   end Is_Static_Range;

   -----------------------
   -- Statically_Denote --
   -----------------------

   function Statically_Denote
     (Element : in     Asis.Expression) return Asis.Element
   is
      use Asis.Expressions;
      use Asis.Declarations;

      Expr : Asis.Expression  := Element;
      Decl : Asis.Declaration;
   begin
      case Expression_Kind (Element) is
         when An_Attribute_Reference =>
            if Assigned (Statically_Denote (Prefix (Element))) then
               return Element;
            else
               return Asis.Nil_Element;
            end if;

         when An_Identifier | An_Operator_Symbol
           | A_Character_Literal | An_Enumeration_Literal
           | A_Selected_Component =>

            if Expression_Kind (Element) = A_Selected_Component then
               if XASIS.Utils.Is_Expanded_Name (Element) then
                  Expr := Selector (Element);
               else
                  return Asis.Nil_Element;
               end if;
            end if;

            Decl := Corresponding_Name_Declaration (Expr);

            if Declaration_Kind (Decl) = An_Object_Renaming_Declaration then
               return Statically_Denote (Renamed_Entity (Decl));
            else
               return Decl;
            end if;

         when others =>
            return Asis.Nil_Element;
      end case;
   end Statically_Denote;

end Asis.Gela.Static;


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
