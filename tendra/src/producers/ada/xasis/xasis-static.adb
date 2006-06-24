with Asis.Elements;
with Asis.Expressions;
with Asis.Definitions;
with Asis.Declarations;
with Ada.Characters.Handling;
with Ada.Unchecked_Deallocation;

with XASIS.Utils;
with XASIS.Classes;

with XASIS.Static.Signed;
with XASIS.Static.Discrete;
with XASIS.Static.Unsigned;

package body XASIS.Static is

   use Asis;
   use Asis.Elements;
   use Asis.Expressions;

   function Evaluate_Static_Constant
     (Element : in Asis.Declaration)
     return Value;

   function Evaluate_Static_Function
     (Func : Asis.Element;
      Args : Asis.Association_List;
      Name : Asis.Expression) return Value;

   function Get_Type_Class
     (Info : Classes.Type_Info;
      Name : Asis.Expression := Asis.Nil_Element) return Type_Class'Class;

   function Get_Type_Class (Name : Asis.Expression) return Type_Class'Class;

   function Statically_Denote
     (Element : in     Asis.Expression) return Asis.Element;

   function Evaluate_Defined (Element : Asis.Expression) return Value;

   --  Ranges --

   function Get_Range (Element : Asis.Range_Constraint) return Static_Range;
   function Get_Discrete_Range
     (Element : Asis.Definition) return Static_Range;

   function Static_Subtype_Range
     (Mark : Asis.Expression;
      Cons : Asis.Constraint := Asis.Nil_Element;
      Base : Boolean         := False)
     return Static_Range;

   function Static_Indication_Range
     (Def  : Asis.Subtype_Indication;
      Base : Boolean := False)
     return Static_Range;

   function Check_Range
     (Val : Value;
      Bnd : Static_Range;
      Inv : Boolean := False) return Value;

   ---------
   -- "+" --
   ---------

   function "+" (Item : Value) return Asis.ASIS_Integer is
   begin
      if Item.Kind = Static_Discrete then
         return Asis.ASIS_Integer'Value (XASIS.Integers.Image (Item.Pos));
      else
         raise Evaluation_Error;
      end if;
   end "+";

   ---------
   -- "+" --
   ---------

   function "+" (Item : Asis.ASIS_Integer) return XASIS.Integers.Value is
   begin
      return XASIS.Integers.Literal (Asis.ASIS_Integer'Image (Item));
   end "+";

   ------------
   -- Adjust --
   ------------

   procedure Adjust (Object : in out Integer_Array_Node) is
   begin
      if Object.Data /= null then
         Object.Data := new Integer_Array'(Object.Data.all);
      end if;
   end Adjust;

   -------------------------------------
   -- Attribute_Designator_Expression --
   -------------------------------------

   function Attribute_Designator_Expression
     (Attr : Asis.Expression) return Value
   is
      Args : Asis.Expression_List :=
        Asis.Expressions.Attribute_Designator_Expressions (Attr);
   begin
      if Args'Length > 0 then
         return Evaluate (Args (1));
      else
         return Static_One;
      end if;
   end Attribute_Designator_Expression;

   -----------------
   -- Check_Range --
   -----------------

   function Check_Range
     (Val : Value;
      Bnd : Static_Range;
      Inv : Boolean := False) return Value
   is
      use XASIS.Integers;
   begin
      if Discrete.Is_Discrete (Val)
        and then Discrete.Is_Discrete (Bnd.Lower)
      then
         if Val.Pos < Bnd.Lower.Pos then
            if Inv then
               return Static_True;
            else
               return Static_False;
            end if;
         elsif Discrete.Is_Discrete (Bnd.Upper) then
            if Val.Pos <= Bnd.Upper.Pos xor Inv then
               return Static_True;
            else
               return Static_False;
            end if;
         end if;
      end if;

      return Undefined;
   end Check_Range;

   -----------------
   -- Debug_Image --
   -----------------

   function Debug_Image (Item : Value) return Wide_String is
      use Ada.Characters.Handling;
   begin
      case Item.Kind is
         when Static_Discrete =>
            return "Static_Discrete:" &
              To_Wide_String (XASIS.Integers.Image (Item.Pos));
         when Static_Undefined =>
            return "Static_Undefined";
         when others =>
            return "";
      end case;
   end Debug_Image;

   --------------
   -- Evaluate --
   --------------

   function Evaluate (Element : Asis.Expression) return Value is
      function Dequote (Text : Wide_String) return Wide_String is
         Result : Wide_String (Text'Range);
         Last   : Natural := Result'First - 1;
         Skip   : Boolean := True;
      begin
         for J in Text'Range loop
            if Skip then
               Skip := False;
            else
               Last := Last + 1;
               Result (Last) := Text (J);
            end if;
         end loop;

         return Result (Result'First .. Last);
      end Dequote;

      Kind : constant Asis.Expression_Kinds := Expression_Kind (Element);
   begin
      case Kind is
         when An_Integer_Literal =>
            declare
               Image : Wide_String := Value_Image (Element);
               Text  : String :=
                 Ada.Characters.Handling.To_String (Image);
            begin
               return (Kind   => Static_Discrete,
                       Pos    => XASIS.Integers.Literal (Text));
            end;
--         | A_Real_Literal
         when An_Enumeration_Literal | A_Character_Literal =>
            declare
               Name : Asis.Defining_Name :=
                 Corresponding_Name_Definition (Element);
               Decl : Asis.Declaration := Enclosing_Element (Name);
               Pos  : Wide_String :=
                 Asis.Declarations.Position_Number_Image (Name);
               Text : String :=
                 Ada.Characters.Handling.To_String (Pos);
            begin
               if Is_Part_Of_Implicit (Decl) then  --  impl defined character
                  declare
                     Img : constant Wide_String := Name_Image (Element);
                     Pos : constant Asis.ASIS_Natural :=
                       Wide_Character'Pos (Img (2));
                  begin
                     return (Kind   => Static_Discrete,
                             Pos    => +Pos);
                  end;
               else
                  return (Kind   => Static_Discrete,
                          Pos    => XASIS.Integers.Literal (Text));
               end if;
            end;

         when A_String_Literal =>
            declare
               use Ada.Finalization;
               Image : Wide_String :=
                 Dequote (Value_Image (Element));
               Text  : Integer_Array (1 .. Image'Length);
            begin
               for J in Image'Range loop
                  Text (Asis.ASIS_Positive (J)) :=
                    +Wide_Character'Pos (Image (J));
               end loop;

               return (Kind   => Static_String,
                       Lower  => XASIS.Integers.One,  --  TODO
                       Upper  => + (Text'Last),
                       String => (Controlled with new Integer_Array'(Text)));
            end;

         when An_Identifier
           | A_Selected_Component =>
            declare
               Decl : Asis.Declaration :=
                 XASIS.Utils.Selected_Name_Declaration (Element, False);
            begin
               case Declaration_Kind (Decl) is
                  when An_Integer_Number_Declaration
                    | A_Real_Number_Declaration =>
                     return Evaluate
                       (Asis.Declarations.Initialization_Expression (Decl));

                  when others =>
                     return Evaluate_Static_Constant (Decl);
               end case;
            end;

         when A_Function_Call =>
            declare
               Func : Asis.Element := Statically_Denote (Prefix (Element));
               Attr : Boolean := Expression_Kind (Prefix (Element)) =
                 An_Attribute_Reference;
               Args : Asis.Association_List :=
                 Function_Call_Parameters (Element, not Attr);
            begin
               return Evaluate_Static_Function (Func, Args, Prefix (Element));
            end;

         when An_Attribute_Reference =>
            declare
               Mark   : Asis.Expression  := Asis.Expressions.Prefix (Element);
               Switch : Type_Class'Class := Get_Type_Class (Name => Mark);
            begin
               return Evaluate (Switch, Attribute_Kind (Element), Element);
            end;

         when A_Type_Conversion | A_Qualified_Expression =>
            declare
               Arg  : constant Asis.Expression :=
                 Converted_Or_Qualified_Expression (Element);
            begin
               return Evaluate (Arg);
            end;

         when An_In_Range_Membership_Test
           | A_Not_In_Range_Membership_Test
           | An_In_Type_Membership_Test
           | A_Not_In_Type_Membership_Test
           =>
            declare
               use XASIS.Integers;

               function Get_Range return Static_Range is
               begin
                  if Kind = An_In_Range_Membership_Test
                    or Kind = A_Not_In_Range_Membership_Test
                  then
                     return Get_Range (Membership_Test_Range (Element));
                  else
                     return Static_Subtype_Range
                       (Membership_Test_Subtype_Mark (Element));
                  end if;
               end Get_Range;

               Bnd : Static_Range := Get_Range;
               Arg : Asis.Expression := Membership_Test_Expression (Element);
               Val : Value renames Evaluate (Arg);
            begin
               return Check_Range
                 (Val, Bnd, Inv => Kind = A_Not_In_Range_Membership_Test
                                   or Kind = A_Not_In_Type_Membership_Test);
            end;

         when An_And_Then_Short_Circuit =>
            declare
               Left  : constant Asis.Expression :=
                 Short_Circuit_Operation_Left_Expression (Element);
               Right : constant Asis.Expression :=
                 Short_Circuit_Operation_Right_Expression (Element);
               Item  : Value renames Evaluate (Left);
            begin
               if Item = Static_False then
                  return Item;
               else
                  return Evaluate (Right);
               end if;
            end;

         when An_Or_Else_Short_Circuit =>
            declare
               Left  : constant Asis.Expression :=
                 Short_Circuit_Operation_Left_Expression (Element);
               Right : constant Asis.Expression :=
                 Short_Circuit_Operation_Right_Expression (Element);
               Item  : Value renames Evaluate (Left);
            begin
               if Item = Static_True then
                  return Item;
               else
                  return Evaluate (Right);
               end if;
            end;

         when A_Parenthesized_Expression =>
            return Evaluate (Expression_Parenthesized (Element));

         when others =>
            raise Evaluation_Error;
      end case;
   end Evaluate;

   function Evaluate_Defined (Element : Asis.Expression) return Value is
   begin
      --  Check implementation-defined mark
      if Is_Part_Of_Implicit (Element) then
         return Undefined;
      else
         return Evaluate (Element);
      end if;
   end Evaluate_Defined;

   ------------------------------
   -- Evaluate_Static_Constant --
   ------------------------------

   function Evaluate_Static_Constant
     (Element : in Asis.Declaration)
     return Value
   is
      use Asis.Declarations;
   begin
      case Declaration_Kind (Element) is
         when An_Object_Renaming_Declaration =>
            return Evaluate (Renamed_Entity (Element));

         when A_Constant_Declaration =>
            return Evaluate (Initialization_Expression (Element));

         when others =>
            raise Evaluation_Error;
      end case;
   end Evaluate_Static_Constant;

   ------------------------------
   -- Evaluate_Static_Function --
   ------------------------------

   function Evaluate_Static_Function
     (Func : Asis.Element;
      Args : Asis.Association_List;
      Name : Asis.Expression) return Value
   is
   begin
      if Element_Kind (Func) = A_Declaration then
         if XASIS.Utils.Is_Predefined_Operator (Func) then
            declare
               use Asis.Declarations;

               Name   : Asis.Defining_Name :=
                 XASIS.Utils.Declaration_Name (Func);
               Decl   : Asis.Declaration :=
                 Enclosing_Element (Corresponding_Type (Func));
               Info   : Classes.Type_Info :=
                 XASIS.Classes.Type_From_Declaration (Decl);
               Switch : Type_Class'Class := Get_Type_Class (Info);
            begin
               return Evaluate (Switch, Operator_Kind (Name), Args);
            end;
         elsif Declaration_Kind (Func) =
           An_Enumeration_Literal_Specification
         then
            return Evaluate (Name);
         end if;

      elsif Expression_Kind (Func) = An_Attribute_Reference then
         declare
            Mark   : Asis.Expression  := Asis.Expressions.Prefix (Func);
            Switch : Type_Class'Class := Get_Type_Class (Name => Mark);
         begin
            return Evaluate (Switch, Attribute_Kind (Func), Args);
         end;
      end if;

      raise Evaluation_Error;
   end Evaluate_Static_Function;

   --------------
   -- Finalize --
   --------------

   procedure Finalize (Object : in out Integer_Array_Node) is
      procedure Free is
         new Ada.Unchecked_Deallocation (Integer_Array, Integer_Array_Access);
   begin
      if Object.Data /= null then
         Free (Object.Data);
      end if;
   end Finalize;

   --------- Ranges ------------------------------------

   ---------------
   -- Get_Range --
   ---------------

   function Get_Range (Element : Asis.Range_Constraint) return Static_Range is
      use Asis.Expressions;
      use Asis.Definitions;
   begin
      case Constraint_Kind (Element) is
         when A_Range_Attribute_Reference =>
            return Static_Range_Attribute (Range_Attribute (Element));

         when A_Simple_Expression_Range =>
            return (Lower => Evaluate_Defined (Lower_Bound (Element)),
                    Upper => Evaluate_Defined (Upper_Bound (Element)));

         when others =>
            raise Evaluation_Error;
      end case;
   end Get_Range;

   ------------------------
   -- Get_Discrete_Range --
   ------------------------

   function Get_Discrete_Range   -- Is_Static_Discrete_Subtype
     (Element : Asis.Definition) return Static_Range
   is
      use Asis.Definitions;
   begin
      case Discrete_Range_Kind (Element) is
         when A_Discrete_Subtype_Indication =>
            return Static_Indication_Range (Element);

         when A_Discrete_Range_Attribute_Reference =>
            return Static_Range_Attribute (Range_Attribute (Element));

         when A_Discrete_Simple_Expression_Range =>
            return (Lower => Evaluate_Defined (Lower_Bound (Element)),
                    Upper => Evaluate_Defined (Upper_Bound (Element)));

         when others =>
            raise Evaluation_Error;
      end case;
   end Get_Discrete_Range;

   ----------------------------
   -- Static_Range_Attribute --
   ----------------------------

   function Static_Range_Attribute   --  Is_Static_Bound
     (Attr   : Asis.Expression) return Static_Range
   is

      function Array_Subtype_Range
        (Def   : Asis.Subtype_Indication;
         Index : Asis.ASIS_Positive)
        return Static_Range;

      function Constrained_Array_Range
        (Decl  : Asis.Declaration;
         Index : Asis.ASIS_Positive)
        return Static_Range;

      -------------------------
      -- Array_Subtype_Range --
      -------------------------

      function Array_Subtype_Range
        (Def   : Asis.Subtype_Indication;
         Index : Asis.ASIS_Positive)
        return Static_Range
      is
         use Asis.Definitions;
         Cons : Asis.Constraint := Subtype_Constraint (Def);
      begin
         if Is_Nil (Cons) then
            declare
               Name : Asis.Expression := Asis.Definitions.Subtype_Mark (Def);
               Decl : Asis.Declaration :=
                 XASIS.Utils.Selected_Name_Declaration (Name, False);
            begin
               return Constrained_Array_Range (Decl, Index);
            end;
         else
            declare
               List : Asis.Discrete_Range_List := Discrete_Ranges (Cons);
            begin
               return Get_Discrete_Range (List (Index));
            end;
         end if;
      end Array_Subtype_Range;

      ---------------------------
      -- String_Constant_Range --
      ---------------------------

      function String_Constant_Range
        (Decl  : Asis.Declaration) return Static_Range
      is
         use XASIS.Static.Discrete;
         Val : Value := Evaluate_Static_Constant (Decl);
      begin
         if Val.Kind = Static_Undefined then
            return (Val, Val);
         elsif Val.Kind = Static_String then
            return (I (Val.Lower), I (Val.Upper));
         else
            raise Evaluation_Error;
         end if;
      end String_Constant_Range;

      --------------------
      -- Is_Constrained --
      --------------------

      function Is_Constrained (Def : Asis.Definition) return Boolean is
      begin
         case Definition_Kind (Def) is
            when A_Type_Definition =>
               return Type_Kind (Def) = A_Constrained_Array_Definition;

            when A_Subtype_Indication =>
               declare
                  Cons : Asis.Constraint :=
                    Asis.Definitions.Subtype_Constraint (Def);
               begin
                  if not Is_Nil (Cons) then
                     return True;
                  else
                     declare
                        Name : Asis.Expression :=
                          Asis.Definitions.Subtype_Mark (Def);
                        Decl : Asis.Declaration :=
                          XASIS.Utils.Selected_Name_Declaration (Name, False);
                     begin
                        return Is_Constrained
                          (Asis.Declarations.Type_Declaration_View (Decl));
                     end;
                  end if;
               end;
            when others =>
               return False;
         end case;
      end Is_Constrained;

      -----------------------------
      -- Constrained_Array_Range --
      -----------------------------

      function Constrained_Array_Range
        (Decl  : Asis.Declaration;
         Index : Asis.ASIS_Positive)
        return Static_Range
      is
         use Asis.Declarations;
         Kind : Asis.Declaration_Kinds := Declaration_Kind (Decl);
         Def  : Asis.Definition;
      begin
         case Kind is
            when An_Ordinary_Type_Declaration =>
               Def := Type_Declaration_View (Decl);

            when A_Subtype_Declaration =>
               Def := Type_Declaration_View (Decl);
               return Array_Subtype_Range (Def, Index);

            when A_Variable_Declaration | A_Constant_Declaration =>
               Def := Object_Declaration_View (Decl);

               if Is_Constrained (Def) then
                  case Definition_Kind (Def) is
                     when A_Type_Definition =>
                        null;
                     when A_Subtype_Indication =>
                        return Array_Subtype_Range (Def, Index);
                     when others =>
                        raise Evaluation_Error;
                  end case;
               elsif Kind = A_Constant_Declaration
                 and then Index = 1
               then
                  return String_Constant_Range (Decl);
               else
                  raise Evaluation_Error;
               end if;

            when An_Object_Renaming_Declaration =>
               return String_Constant_Range (Decl);

            when others =>
               raise Evaluation_Error;
         end case;

         case Type_Kind (Def) is
            when A_Constrained_Array_Definition =>
               declare
                  List : Asis.Definition_List :=
                    Asis.Definitions.Discrete_Subtype_Definitions (Def);
               begin
                  return Get_Discrete_Range (List (Index));
               end;
            when others =>
               raise Evaluation_Error;
         end case;
      end Constrained_Array_Range;

      Prefix : Asis.Expression := Asis.Expressions.Prefix (Attr);
      Info   : Classes.Type_Info := Classes.Type_From_Subtype_Mark (Prefix);
      Index  : Asis.ASIS_Positive := 1;
   begin  --  Static_Range_Attribute
      if Classes.Is_Scalar (Info) then
         return Static_Subtype_Range (Prefix);
      else
         declare
            Decl : Asis.Declaration := Statically_Denote (Prefix);
            Val  : Value := Attribute_Designator_Expression (Attr);
         begin
            if Discrete.Is_Discrete (Val) then
               Index := +Val;
            else
               return (Undefined, Undefined);
            end if;

            return Constrained_Array_Range (Decl, Index);
         end;
      end if;
   end Static_Range_Attribute;

   -----------------------------
   -- Static_Indication_Range --
   -----------------------------

   function Static_Indication_Range
     (Def  : Asis.Subtype_Indication;
      Base : Boolean := False)
     return Static_Range
   is
      Name : Asis.Expression :=
        Asis.Definitions.Subtype_Mark (Def);
      Cons : Asis.Constraint :=
        Asis.Definitions.Subtype_Constraint (Def);
   begin
      return Static_Subtype_Range (Name, Cons, Base);
   end Static_Indication_Range;

   --------------------------
   -- Static_Subtype_Range --
   --------------------------

   function Static_Subtype_Range
     (Mark : Asis.Expression;
      Cons : Asis.Constraint := Asis.Nil_Element;
      Base : Boolean         := False)
     return Static_Range
   is
      use Asis.Definitions;
      use Asis.Declarations;

      Decl : Asis.Declaration;
      Def  : Asis.Definition;
   begin
      if not Base and not Is_Nil (Cons) then
         return Get_Range (Cons);
      end if;

      if Expression_Kind (Mark) = An_Attribute_Reference then
         if Attribute_Kind (Mark) = A_Base_Attribute then
            return Static_Subtype_Range (Prefix (Mark), Base => True);
         else
            raise Evaluation_Error;
         end if;
      end if;

      Decl := XASIS.Utils.Selected_Name_Declaration (Mark, False);
      Def  := Type_Declaration_View (Decl);

      case Definition_Kind (Def) is
         when A_Subtype_Indication =>
            return Static_Indication_Range (Def, Base);

         when A_Type_Definition =>
            case Type_Kind (Def) is
               when A_Derived_Type_Definition =>
                  Def := Parent_Subtype_Indication (Def);
                  return Static_Indication_Range (Def, Base);

               when An_Enumeration_Type_Definition =>
                  declare
                     List : Asis.Declaration_List :=
                       Enumeration_Literal_Declarations (Def);
                  begin
                     return (Static_Zero, Discrete.I (+(List'Length - 1)));
                  end;

               when A_Signed_Integer_Type_Definition =>
                  if Base then
                     return (Undefined, Undefined);
                  else
                     return Get_Range (Integer_Constraint (Def));
                  end if;

               when A_Modular_Type_Definition =>
                  declare
                     use XASIS.Integers;

                     Module : Asis.Expression := Mod_Static_Expression (Def);
                     Val    : Value := Evaluate (Module);
                  begin
                     if Discrete.Is_Discrete (Val) then
                        return (Static_Zero, Discrete.I (Val.Pos - One));
                     else
                        return (Undefined, Undefined);
                     end if;
                  end;

               when A_Floating_Point_Definition
                 | An_Ordinary_Fixed_Point_Definition
                 | A_Decimal_Fixed_Point_Definition
                 =>
                  declare
                     Rng : Asis.Range_Constraint :=
                       Real_Range_Constraint (Def);
                  begin
                     if Is_Nil (Rng) or Base then
                        return (Undefined, Undefined);
                     else
                        return Get_Range (Rng);
                     end if;
                  end;
               when others =>
                  raise Evaluation_Error;
            end case;

         when others =>
            raise Evaluation_Error;
      end case;
   end Static_Subtype_Range;

   --------- Ranges ------------------------------------

   --------------------
   -- Get_Type_Class --
   --------------------

   function Get_Type_Class
     (Info : Classes.Type_Info;
      Name : Asis.Expression := Asis.Nil_Element) return Type_Class'Class
   is
   begin
      if Classes.Is_Discrete (Info) then
         if Classes.Is_Integer (Info) then
            if Classes.Is_Modular_Integer (Info) then
               return Unsigned.Type_Class'(Info => Info, Prefix => Name);
            else
               return Signed.Type_Class'(Info => Info, Prefix => Name);
            end if;
         else
            return Discrete.Type_Class'(Info => Info, Prefix => Name);
         end if;
      else
         raise Evaluation_Error;
      end if;
   end Get_Type_Class;

   --------------------
   -- Get_Type_Class --
   --------------------

   function Get_Type_Class (Name : Asis.Expression) return Type_Class'Class is
      Info : Classes.Type_Info := Classes.Type_From_Subtype_Mark (Name);
      Decl : Asis.Declaration;
   begin
      if Classes.Is_Not_Type (Info) then
         Decl := Statically_Denote (Name);
         Info := Classes.Type_Of_Declaration (Decl);
      end if;

      return Get_Type_Class (Info, Name);
   end Get_Type_Class;

   -----------
   -- Image --
   -----------

   function Image (Item : Value) return Wide_String is
      use Ada.Characters.Handling;
   begin
      case Item.Kind is
         when Static_Discrete =>
            return To_Wide_String (XASIS.Integers.Image (Item.Pos));
         when others =>
            raise Evaluation_Error;
      end case;
   end Image;

   --------------
   -- In_Range --
   --------------

   function In_Range
     (Item    : Value;
      Element : Asis.Definition) return Boolean
   is
      Rng : Static_Range := Get_Discrete_Range (Element);
   begin
      return Check_Range (Item, Rng) = Static_True;
   end In_Range;

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
            return Element;

         when An_Identifier | An_Operator_Symbol
           | A_Character_Literal | An_Enumeration_Literal
           | A_Selected_Component =>

            if Expression_Kind (Element) = A_Selected_Component then
               Expr := Selector (Element);
            end if;

            Decl := Corresponding_Name_Declaration (Expr);

            if Declaration_Kind (Decl) = An_Object_Renaming_Declaration then
               return Statically_Denote (Renamed_Entity (Decl));
            else
               return Decl;
            end if;

         when others =>
            raise Evaluation_Error;
      end case;
   end Statically_Denote;

end XASIS.Static;


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
