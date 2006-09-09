with Asis.Elements;
with Asis.Expressions;
with Asis.Definitions;
with Asis.Declarations;

with XASIS.Utils;
with XASIS.Classes;

package body XASIS.Static.Iter is
   use Asis;
   use Asis.Elements;

   function Evaluate_Static_Function
     (Object  : access Calculator;
      Func    : in     Asis.Element;
      Args    : in     Asis.Association_List;
      Name    : in     Asis.Expression) return Value;

   function Statically_Denote
     (Element : in     Asis.Expression) return Asis.Element;

   function Get_Type_Class (Name : Asis.Expression) return Classes.Type_Info;
   --  Return type info for prefix of an attribute

   function Evaluate_Defined
     (Object  : access Calculator;
      Element : in     Asis.Expression) return Value;

   --  Ranges --

   function Get_Range
     (Object  : access Calculator;
      Element : in     Asis.Range_Constraint) return Static_Range;

   function Static_Indication_Range
     (Object : access Calculator;
      Def    : in     Asis.Subtype_Indication;
      Base   : in     Boolean := False)
     return Static_Range;

   function Static_Subtype_Range
     (Object : access Calculator;
      Mark   : in     Asis.Expression;
      Cons   : in     Asis.Constraint := Asis.Nil_Element;
      Base   : in     Boolean         := False)
     return Static_Range;

   --------------
   -- Evaluate --
   --------------

   function Evaluate
     (Object  : access Calculator;
      Element : in     Asis.Expression) return Value
   is
      use Asis.Expressions;

      Kind : constant Asis.Expression_Kinds := Expression_Kind (Element);
   begin
      case Kind is
         when An_Integer_Literal
           | A_Real_Literal
           | An_Enumeration_Literal
           | A_Character_Literal
           | A_String_Literal =>
            return Literal (Object, Element);

         when An_Identifier
           | A_Selected_Component
           =>
            declare
               Decl : Asis.Declaration :=
                 XASIS.Utils.Selected_Name_Declaration (Element, False);
            begin
               case Declaration_Kind (Decl) is
                  when An_Integer_Number_Declaration
                    | A_Real_Number_Declaration =>
                     return Evaluate
                       (Object,
                        Asis.Declarations.Initialization_Expression (Decl));

                  when others =>
                     return Evaluate_Static_Constant (Object, Decl);
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
               return Evaluate_Static_Function
                 (Object, Func, Args, Prefix (Element));
            end;

         when An_Attribute_Reference =>
            declare
               Mark : Asis.Expression  := Asis.Expressions.Prefix (Element);
               Info : Classes.Type_Info := Get_Type_Class (Name => Mark);
               Kind : Asis.Attribute_Kinds := Attribute_Kind (Element);
            begin
               return Attribute (Object, Info, Kind, Element);
            end;

         when A_Type_Conversion | A_Qualified_Expression =>
            declare
               Arg  : constant Asis.Expression :=
                 Converted_Or_Qualified_Expression (Element);
            begin
               return Evaluate (Object, Arg);
            end;

         when An_In_Range_Membership_Test
           | A_Not_In_Range_Membership_Test
           | An_In_Type_Membership_Test
           | A_Not_In_Type_Membership_Test
           =>
            declare
               function Get_Range return Static_Range is
               begin
                  if Kind = An_In_Range_Membership_Test
                    or Kind = A_Not_In_Range_Membership_Test
                  then
                     return Get_Range
                       (Object, Membership_Test_Range (Element));
                  else
                     return Static_Subtype_Range
                       (Object, Membership_Test_Subtype_Mark (Element));
                  end if;
               end Get_Range;

               Bnd : Static_Range := Get_Range;
               Arg : Asis.Expression := Membership_Test_Expression (Element);
               Inv : constant Boolean := Kind = A_Not_In_Range_Membership_Test
                 or Kind = A_Not_In_Type_Membership_Test;
            begin
               return Check_Range (Object, Arg, Bnd, Inv);
            end;
         when others =>
            raise Evaluation_Error;
      end case;
   end Evaluate;

   ----------------------
   -- Evaluate_Defined --
   ----------------------

   function Evaluate_Defined
     (Object  : access Calculator;
      Element : in     Asis.Expression) return Value is
   begin
      --  Check implementation-defined mark
      if Is_Part_Of_Implicit (Element) then
         return Undefined (Object, Element);
      else
         return Evaluate (Object, Element);
      end if;
   end Evaluate_Defined;

   ------------------------------
   -- Evaluate_Static_Constant --
   ------------------------------

   function Evaluate_Static_Constant
     (Object  : access Calculator;
      Element : in     Asis.Declaration)
     return Value
   is
      use Asis.Declarations;
   begin
      case Declaration_Kind (Element) is
         when An_Object_Renaming_Declaration =>
            return Evaluate (Object, Renamed_Entity (Element));

         when A_Constant_Declaration =>
            return Evaluate (Object, Initialization_Expression (Element));

         when others =>
            raise Evaluation_Error;
      end case;
   end Evaluate_Static_Constant;

   ------------------------------
   -- Evaluate_Static_Function --
   ------------------------------

   function Evaluate_Static_Function
     (Object  : access Calculator;
      Func    : in     Asis.Element;
      Args    : in     Asis.Association_List;
      Name    : in     Asis.Expression) return Value
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
            begin
               return Operator (Object, Info, Operator_Kind (Name), Args);
            end;
         elsif Declaration_Kind (Func) =
           An_Enumeration_Literal_Specification
         then
            return Evaluate (Object, Name);
         end if;

      elsif Expression_Kind (Func) = An_Attribute_Reference then
         declare
            Mark : Asis.Expression   := Asis.Expressions.Prefix (Func);
            Info : Classes.Type_Info := Get_Type_Class (Name => Mark);
         begin
            return Attribute_Call (Object, Info, Attribute_Kind (Func), Args);
         end;
      end if;

      raise Evaluation_Error;
   end Evaluate_Static_Function;

   --------------------
   -- Get_Type_Class --
   --------------------

   function Get_Type_Class (Name : Asis.Expression) return Classes.Type_Info is
      Info : Classes.Type_Info := Classes.Type_From_Subtype_Mark (Name);
      Decl : Asis.Declaration;
   begin
      if Classes.Is_Not_Type (Info) then
         Decl := Statically_Denote (Name);
         Info := Classes.Type_Of_Declaration (Decl);
      end if;

      return Info;
   end Get_Type_Class;

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

   --------- Ranges ------------------------------------

   -------------------------
   -- Array_Subtype_Range --
   -------------------------

   function Array_Subtype_Range
     (Object  : access Calculator;
      Def     : in     Asis.Subtype_Indication;
      Index   : in     Asis.ASIS_Positive)
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
            return Constrained_Array_Range (Object, Decl, Index);
         end;
      else
         declare
            List : Asis.Discrete_Range_List := Discrete_Ranges (Cons);
         begin
            return Get_Discrete_Range (Object, List (Index));
         end;
      end if;
   end Array_Subtype_Range;

   -----------------------------
   -- Constrained_Array_Range --
   -----------------------------

   function Constrained_Array_Range
     (Object  : access Calculator;
      Decl    : in     Asis.Declaration;
      Index   : in     Asis.ASIS_Positive)
     return Static_Range
   is
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

      use Asis.Declarations;
      Kind : Asis.Declaration_Kinds := Declaration_Kind (Decl);
      Def  : Asis.Definition;
   begin
      case Kind is
         when An_Ordinary_Type_Declaration =>
            Def := Type_Declaration_View (Decl);

         when A_Subtype_Declaration =>
            Def := Type_Declaration_View (Decl);
            return Array_Subtype_Range (Object, Def, Index);

         when A_Variable_Declaration | A_Constant_Declaration =>
            Def := Object_Declaration_View (Decl);

            if Is_Constrained (Def) then
               case Definition_Kind (Def) is
                  when A_Type_Definition =>
                     null;
                  when A_Subtype_Indication =>
                     return Array_Subtype_Range (Object, Def, Index);
                  when others =>
                     raise Evaluation_Error;
               end case;
            elsif Kind = A_Constant_Declaration and Index = 1 then
               return String_Constant_Range (Object, Decl);
            else
               raise Evaluation_Error;
            end if;

         when An_Object_Renaming_Declaration =>
            return String_Constant_Range (Object, Decl);

         when others =>
            raise Evaluation_Error;
      end case;

      case Type_Kind (Def) is
         when A_Constrained_Array_Definition =>
            declare
               List : Asis.Definition_List :=
                 Asis.Definitions.Discrete_Subtype_Definitions (Def);
            begin
               return Get_Discrete_Range (Object, List (Index));
            end;
         when others =>
            raise Evaluation_Error;
      end case;
   end Constrained_Array_Range;

   ------------------------
   -- Get_Discrete_Range --
   ------------------------

   function Get_Discrete_Range   -- Is_Static_Discrete_Subtype
     (Object  : access Calculator;
      Element : in     Asis.Definition) return Static_Range
   is
      use Asis.Definitions;
   begin
      case Discrete_Range_Kind (Element) is
         when A_Discrete_Subtype_Indication =>
            return Static_Indication_Range (Object, Element);

         when A_Discrete_Range_Attribute_Reference =>
            return Static_Range_Attribute (Object, Range_Attribute (Element));

         when A_Discrete_Simple_Expression_Range =>
            return (Evaluate_Defined (Object, Lower_Bound (Element)),
                    Evaluate_Defined (Object, Upper_Bound (Element)));

         when others =>
            raise Evaluation_Error;
      end case;
   end Get_Discrete_Range;

   ---------------
   -- Get_Range --
   ---------------

   function Get_Range
     (Object  : access Calculator;
      Element : in     Asis.Range_Constraint) return Static_Range
   is
      use Asis.Expressions;
      use Asis.Definitions;
   begin
      case Constraint_Kind (Element) is
         when A_Range_Attribute_Reference =>
            return Static_Range_Attribute (Object, Range_Attribute (Element));

         when A_Simple_Expression_Range =>
            return (Evaluate_Defined (Object, Lower_Bound (Element)),
                    Evaluate_Defined (Object, Upper_Bound (Element)));

         when others =>
            raise Evaluation_Error;
      end case;
   end Get_Range;

   -----------------------------
   -- Static_Indication_Range --
   -----------------------------

   function Static_Indication_Range
     (Object : access Calculator;
      Def    : in     Asis.Subtype_Indication;
      Base   : in     Boolean := False)
     return Static_Range
   is
      Name : Asis.Expression :=
        Asis.Definitions.Subtype_Mark (Def);
      Cons : Asis.Constraint :=
        Asis.Definitions.Subtype_Constraint (Def);
   begin
      return Static_Subtype_Range (Object, Name, Cons, Base);
   end Static_Indication_Range;

   ----------------------------
   -- Static_Range_Attribute --
   ----------------------------

   function Static_Range_Attribute   --  Is_Static_Bound
     (Object : access Calculator;
      Attr   : in     Asis.Expression) return Static_Range
   is
      Prefix : Asis.Expression := Asis.Expressions.Prefix (Attr);
      Info   : Classes.Type_Info := Classes.Type_From_Subtype_Mark (Prefix);
      Index  : Asis.ASIS_Positive := 1;
   begin  --  Static_Range_Attribute
      if Classes.Is_Scalar (Info) then
         return Static_Subtype_Range (Object, Prefix);
      else
         declare
            Decl : Asis.Declaration := Statically_Denote (Prefix);
         begin
            return Range_Of_Array (Object, Decl, Attr);
         end;
      end if;
   end Static_Range_Attribute;

   --------------------------
   -- Static_Subtype_Range --
   --------------------------

   function Static_Subtype_Range
     (Object : access Calculator;
      Mark   : in     Asis.Expression;
      Cons   : in     Asis.Constraint := Asis.Nil_Element;
      Base   : in     Boolean         := False)
     return Static_Range
   is
      use Asis.Expressions;
      use Asis.Definitions;
      use Asis.Declarations;

      Decl : Asis.Declaration;
      Def  : Asis.Definition;
   begin
      if not Base and not Is_Nil (Cons) then
         return Get_Range (Object, Cons);
      end if;

      if Expression_Kind (Mark) = An_Attribute_Reference then
         if Attribute_Kind (Mark) = A_Base_Attribute then
            return Static_Subtype_Range (Object, Prefix (Mark), Base => True);
         else
            raise Evaluation_Error;
         end if;
      end if;

      Decl := XASIS.Utils.Selected_Name_Declaration (Mark, False);
      Def  := Type_Declaration_View (Decl);

      case Definition_Kind (Def) is
         when A_Subtype_Indication =>
            return Static_Indication_Range (Object, Def, Base);

         when A_Type_Definition =>
            case Type_Kind (Def) is
               when A_Derived_Type_Definition =>
                  Def := Parent_Subtype_Indication (Def);
                  return Static_Indication_Range (Object, Def, Base);

               when An_Enumeration_Type_Definition =>
                  return Range_Of_Type (Object, Def);

               when A_Signed_Integer_Type_Definition =>
                  if Base then
                     return Range_Of_Type (Object, Def);
                  else
                     return Get_Range (Object, Integer_Constraint (Def));
                  end if;

               when A_Modular_Type_Definition =>
                  return Range_Of_Type (Object, Def);

               when A_Floating_Point_Definition
                 | An_Ordinary_Fixed_Point_Definition
                 | A_Decimal_Fixed_Point_Definition
                 =>
                  declare
                     Rng : Asis.Range_Constraint :=
                       Real_Range_Constraint (Def);
                  begin
                     if Is_Nil (Rng) or Base then
                        return Range_Of_Type (Object, Def);
                     else
                        return Get_Range (Object, Rng);
                     end if;
                  end;

               when others =>
                  raise Evaluation_Error;
            end case;

         when others =>
            raise Evaluation_Error;
      end case;
   end Static_Subtype_Range;

end XASIS.Static.Iter;
