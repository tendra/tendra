with Asis.Elements;
with Asis.Statements;
with Asis.Extensions;
with Asis.Expressions;
with Asis.Gela.Debug;
with Asis.Gela.Errors;
with Asis.Definitions;
with Asis.Declarations;
with Asis.Gela.Classes;
with Asis.Gela.Replace;
with Asis.Gela.Resolver;
with Asis.Gela.Overloads.Walk;
with Asis.Gela.Overloads.Iters;
with Asis.Gela.Overloads.Types;
with Asis.Gela.Elements.Assoc;
with Asis.Gela.Element_Utils;
with XASIS.Utils;
with XASIS.Types;
with XASIS.Static;

package body Asis.Gela.Overloads is

   use Asis.Elements;
   use Asis.Declarations;
   use Asis.Gela.Classes;
   use Asis.Gela.Overloads.Types;

   type Expected_Kinds is (Some_Type, Some_Range, Any_Discrete_Range,
     Any_Numeric_Type, Any_Integer_Type, Any_Real_Type, Any_Boolean_Type,
     Any_Discrete_Type, Any_Type, A_Call_Statement, A_Callable_Name,
     A_Requeue, Any_Nonlimited);

   procedure Resolve_To
     (Element : in out Asis.Element;
      Expect  : in     Expected_Kinds;
      Tipe    : in     Type_Info := Not_A_Type;
      Profile : in     Asis.Declaration := Asis.Nil_Element);

   procedure Resolve_In_Declaration
     (Element : in out Asis.Element;
      Parent  : in     Asis.Declaration);

   procedure Resolve_In_Definition
     (Element : in out Asis.Element;
      Parent  : in     Asis.Definition);

   procedure Resolve_In_Statement
     (Element : in out Asis.Element;
      Parent  : in     Asis.Statement);

   procedure Resolve_Definition
     (Element : in out Asis.Definition);

   procedure Resolve_In_Enum_Rep_Clause
     (Element : in out Asis.Element;
      Parent  : in     Asis.Clause);

   procedure Resolve_In_Component_Clause
     (Element : in out Asis.Element;
      Parent  : in     Asis.Clause);

   function Find_Subtype_Of_Constraint (Element : Asis.Definition)
     return Asis.Subtype_Indication;

   function Is_Part_Of_Signed_Type (Element : Asis.Constraint) return Boolean;
   function Is_Part_Of_Float_Type (Element : Asis.Constraint) return Boolean;
   function Is_Part_Of_Fixed_Type (Element : Asis.Constraint) return Boolean;

   function Resolve_Discriminant_Names
     (Info  : Type_Info;
      Names : Asis.Expression_List;
      Index : Asis.List_Index) return Type_Info;

   function Find_Variant_Discriminant (Item : Asis.Variant)
     return Asis.Declaration;

   function Find_Part_Discriminant (Part : Asis.Definition)
     return Asis.Declaration;

   function Find_Discriminant
     (List  : Asis.Discriminant_Specification_List;
      Image : Asis.Program_Text) return Asis.Declaration;

   function Find_Case_Type (Element : Asis.Path) return Type_Info;

   function Is_Resolved
     (Info : Type_Info;
      Item : Asis.Element) return Boolean;

   function Is_Timed_Entry_Call (Element : Asis.Element) return Boolean;
   function Is_Conditional_Entry_Call
     (Element : Asis.Element) return Boolean;
   function First_Statement_Kind (Path : Asis.Element) return Statement_Kinds;
   procedure Check_No_Guards
     (Path : Asis.Element;
      Item : Wide_String);

   function Parent_Of_Requeue (Element : Asis.Statement) return Asis.Element;

   procedure Set_Representation_Value (Element : Asis.Representation_Clause);

   ---------------------
   -- Check_No_Guards --
   ---------------------

   procedure Check_No_Guards
     (Path : Asis.Element;
      Item : Wide_String)
   is
      The_Guard : Asis.Element := Guard (Path.all);
   begin
      if Assigned (The_Guard) then
         Errors.Report (Item => Path, -- The_Guard,
                        What => Errors.Error_Syntax_Guard_Exists,
                        Argument1 => Item);
      end if;
   end Check_No_Guards;

   --------------------
   -- Find_Case_Type --
   --------------------

   function Find_Case_Type (Element : Asis.Path) return Type_Info is
      Parent : Asis.Element := Enclosing_Element (Element);
      Expr   : Asis.Expression :=
        Asis.Statements.Case_Expression (Parent);
      Decl   : Asis.Declaration :=
        Asis.Expressions.Corresponding_Expression_Type (Expr);
   begin
      return Type_From_Declaration (Decl, Element);
   end Find_Case_Type;

   -----------------------
   -- Find_Discriminant --
   -----------------------

   function Find_Discriminant
     (List  : Asis.Discriminant_Specification_List;
      Image : Asis.Program_Text) return Asis.Declaration
   is
   begin
      for K in List'Range loop
         if XASIS.Utils.Has_Defining_Name (List (K), Image) then
            return List (K);
         end if;
      end loop;
      return Asis.Nil_Element;
   end Find_Discriminant;

   --------------------------------
   -- Find_Subtype_Of_Constraint --
   --------------------------------

   function Find_Subtype_Of_Constraint (Element : Asis.Definition)
     return Asis.Subtype_Indication
   is
      Parent : Asis.Element := Enclosing_Element (Element);
   begin
      if Definition_Kind (Parent) = A_Constraint then
         Parent := Enclosing_Element (Parent);
      end if;

      if Element_Kind (Parent) = An_Expression then
         return Asis.Nil_Element;
      end if;

      case Definition_Kind (Parent) is
         when A_Subtype_Indication | A_Discrete_Subtype_Definition |
           A_Discrete_Range =>
            return Parent;
         when A_Type_Definition =>
            return Asis.Nil_Element;
         when others =>
            raise Internal_Error;
      end case;
   end Find_Subtype_Of_Constraint;

   ----------------------------
   -- Find_Part_Discriminant --
   ----------------------------

   function Find_Part_Discriminant (Part : Asis.Definition)
     return Asis.Declaration
   is
      use Asis.Definitions;
      Ident : Asis.Identifier := Discriminant_Direct_Name (Part);
      Decl  : Asis.Declaration := XASIS.Utils.Parent_Declaration (Part);
      Discr : Asis.Definition := Discriminant_Part (Decl);
   begin
      if Definition_Kind (Discr) /= A_Known_Discriminant_Part then
         return Asis.Nil_Element;
      end if;
      declare
         List  : Asis.Declaration_List :=
           Asis.Definitions.Discriminants (Discr);
      begin
         return Find_Discriminant (List, XASIS.Utils.Name_Image (Ident));
      end;
   end Find_Part_Discriminant;

   -------------------------------
   -- Find_Variant_Discriminant --
   -------------------------------

   function Find_Variant_Discriminant (Item : Asis.Variant)
     return Asis.Declaration
   is
      Part  : Asis.Definition := Enclosing_Element (Item);
   begin
      return Find_Part_Discriminant (Part);
   end Find_Variant_Discriminant;

   --------------------------
   -- First_Statement_Kind --
   --------------------------

   function First_Statement_Kind (Path : Asis.Element) return Statement_Kinds
   is
      List : Asis.Element_List := Sequence_Of_Statements (Path.all, False);
   begin
      return Statement_Kind (List (1).all);
   end First_Statement_Kind;

   ----------------------------
   -- Is_Part_Of_Signed_Type --
   ----------------------------

   function Is_Part_Of_Signed_Type (Element : Asis.Constraint) return Boolean
   is
      Parent : constant Asis.Element := Enclosing_Element (Element);
   begin
      return Type_Kind (Parent) = A_Signed_Integer_Type_Definition;
   end Is_Part_Of_Signed_Type;

   ---------------------------
   -- Is_Part_Of_Float_Type --
   ---------------------------

   function Is_Part_Of_Float_Type (Element : Asis.Constraint) return Boolean
   is
      Parent : constant Asis.Element := Enclosing_Element (Element);
   begin
      return Type_Kind (Parent) = A_Floating_Point_Definition;
   end Is_Part_Of_Float_Type;

   ---------------------------
   -- Is_Part_Of_Fixed_Type --
   ---------------------------

   function Is_Part_Of_Fixed_Type (Element : Asis.Constraint) return Boolean
   is
      Parent : constant Asis.Element := Enclosing_Element (Element);
      Kind   : constant Asis.Type_Kinds := Type_Kind (Parent);
   begin
      return Kind = An_Ordinary_Fixed_Point_Definition
        or Kind = A_Decimal_Fixed_Point_Definition;
   end Is_Part_Of_Fixed_Type;

   -------------------------------
   -- Is_Conditional_Entry_Call --
   -------------------------------

   function Is_Conditional_Entry_Call
     (Element : Asis.Element) return Boolean
   is
      Path : constant Asis.Element_List := Statement_Paths (Element.all);
   begin
      if Path'Length = 2
        and then Path_Kind (Path (1).all) = A_Select_Path
        and then Path_Kind (Path (2).all) = An_Else_Path
        and then First_Statement_Kind (Path (1)) = An_Entry_Call_Statement
      then
         Check_No_Guards (Path (1), "Conditional_Entry_Call");
         return True;
      end if;

      return False;
   end Is_Conditional_Entry_Call;

   -------------------------
   -- Is_Timed_Entry_Call --
   -------------------------

   function Is_Timed_Entry_Call (Element : Asis.Element) return Boolean is
      Path : constant Asis.Element_List := Statement_Paths (Element.all);
   begin
      if Path'Length = 2
        and then Path_Kind (Path (1).all) = A_Select_Path
        and then Path_Kind (Path (2).all) = An_Or_Path
        and then First_Statement_Kind (Path (1)) = An_Entry_Call_Statement
        and then First_Statement_Kind (Path (2)) in
        A_Delay_Until_Statement .. A_Delay_Relative_Statement
      then
         Check_No_Guards (Path (1), "Timed_Entry_Call");
         Check_No_Guards (Path (2), "Timed_Entry_Call");
         return True;
      end if;

      return False;
   end Is_Timed_Entry_Call;

   -----------------
   -- Is_Resolved --
   -----------------

   function Is_Resolved
     (Info : Type_Info;
      Item : Asis.Element) return Boolean is
   begin
      if Is_Not_Type (Info) then
         Errors.Report (Item, Errors.Error_Unknown_Type);
         return False;
      end if;
      return True;
   end Is_Resolved;

   -----------------------
   -- Parent_Of_Requeue --
   -----------------------

   function Parent_Of_Requeue (Element : Asis.Statement) return Asis.Element is
      Parent : Asis.Element := Element;
   begin
      while not Is_Nil (Parent)
        and then Statement_Kind (Parent) /= An_Accept_Statement
        and then Declaration_Kind (Parent) /= An_Entry_Body_Declaration
      loop
         Parent := Enclosing_Element (Parent);
      end loop;

      return Parent;
   end Parent_Of_Requeue;

   -------------
   -- Resolve --
   -------------

   procedure Resolve (Item : in out Asis.Element) is
   begin
      if Is_Part_Of_Implicit (Item) then
         return;
      end if;
      case Element_Kind (Item) is
         when An_Association =>
            declare
               Parent_2 : Asis.Element :=
                 Enclosing_Element (Enclosing_Element (Item));
               Kind   : Asis.Representation_Clause_Kinds
                 := Representation_Clause_Kind (Parent_2);
            begin
               case Kind is
                  when An_Enumeration_Representation_Clause =>
                     Resolve_In_Enum_Rep_Clause (Item, Parent_2);
                  when others =>
                     null;
               end case;
            end;

         when A_Declaration =>
            case Declaration_Kind (Item) is
               when An_Integer_Number_Declaration =>

                  declare
                     use Asis.Expressions;
                     Expr : Asis.Expression :=
                       Initialization_Expression (Item);
                     Tipe : Asis.Declaration;
                     Info : Type_Info;
                  begin
                     Tipe := Corresponding_Expression_Type (Expr);
                     Info := Type_From_Declaration (Tipe, Expr);
                     if Is_Real (Info) then
                        Replace.Integer_Real_Number (Item);
                     end if;
                  end;

               when A_Real_Number_Declaration =>
                  raise Internal_Error; --  go to An_Integer_Number_Declaration

               when others =>
                  null;
            end case;
         when An_Expression =>
            declare
               Parent : Asis.Element := Enclosing_Element (Item);
               Kind   : Asis.Element_Kinds := Element_Kind (Parent);
            begin
               case Kind is
                  when An_Association =>
                     declare
                        Parent_2 : Asis.Element :=
                          Enclosing_Element (Enclosing_Element (Parent));
                        Kind   : Asis.Representation_Clause_Kinds
                          := Representation_Clause_Kind (Parent_2);
                     begin
                        case Kind is
                           when An_Enumeration_Representation_Clause =>
                              Resolve_In_Enum_Rep_Clause (Item, Parent_2);
                           when others =>
                              null;
                        end case;
                     end;
                  when A_Declaration =>
                     Resolve_In_Declaration (Item, Parent);
                  when A_Definition =>
                     Resolve_In_Definition (Item, Parent);
                  when A_Path =>
                     case Path_Kind (Parent) is
                        when An_If_Path | An_Elsif_Path =>
                           Resolve_To (Item, Any_Boolean_Type);
                        when A_Case_Path =>
                           Resolve_To (Item, Some_Type,
                             Find_Case_Type (Parent));
                        when others =>
                           null;
                     end case;
                  when A_Statement =>
                     Resolve_In_Statement (Item, Parent);
                  when A_Clause =>
                     case Clause_Kind (Parent) is
                        when A_Component_Clause =>
                           Resolve_In_Component_Clause (Item, Parent);
                        when others =>
                           null;
                     end case;
                  when others =>
                     null;
               end case;
            end;
         when A_Definition =>
            Resolve_Definition (Item);
         when A_Statement =>
            case Statement_Kind (Item) is
               when An_Assignment_Statement =>
                  Resolve_To (Item, Any_Type);
               when A_Procedure_Call_Statement =>
                  Resolve_To (Item, A_Call_Statement);
               when A_Selective_Accept_Statement =>
                  if Is_Timed_Entry_Call (Item) then
                     Replace.To_Timed_Entry_Call (Item);
                  elsif Is_Conditional_Entry_Call(Item) then
                     Replace.To_Conditional_Entry_Call (Item);
                  end if;
               when others =>
                  null;
            end case;
         when A_Clause =>
            case Clause_Kind (Item) is
               when A_Representation_Clause =>
                  case Representation_Clause_Kind (Item) is
                     when An_Enumeration_Representation_Clause =>
                        Set_Representation_Value (Item);
                     when others =>
                        null;
                  end case;
               when others =>
                  null;
            end case;
         when others =>
            null;
      end case;
   end Resolve;

   ------------------------
   -- Resolve_Definition --
   ------------------------

   procedure Resolve_Definition
     (Element : in out Asis.Definition)
   is
      Kind   : Asis.Definition_Kinds := Definition_Kind (Element);
      Constr : Asis.Constraint;
      Parent : Asis.Element;
   begin
      case Kind is
         when A_Discrete_Subtype_Definition =>
            case Discrete_Range_Kind (Element) is
               when A_Discrete_Range_Attribute_Reference |
                 A_Discrete_Simple_Expression_Range =>
--                  Parent := Definition_Kind (Enclosing_Element (Element));
                  Resolve_To (Element, Any_Discrete_Range);
               when others =>
                  null;
            end case;
         when A_Subtype_Indication =>
            Constr := Asis.Definitions.Subtype_Constraint (Element);
            case Constraint_Kind (Constr) is
               when An_Index_Constraint =>
                  declare
                     Info : Type_Info :=
                       Type_From_Indication (Element, Element);
                     List : Asis.Discrete_Range_List :=
                       Asis.Definitions.Discrete_Ranges (Constr);
                  begin
                     if Is_Resolved (Info, Element) then
                        for I in List'Range loop
                           if Discrete_Range_Kind (List (I)) in
                             A_Discrete_Range_Attribute_Reference ..
                             A_Discrete_Simple_Expression_Range
                           then
                              Resolve_To (List (I), Some_Range,
                                          Get_Array_Index_Type (Info, I));
                           end if;
                        end loop;
                     end if;
                  end;
               when A_Discriminant_Constraint =>
                  declare
                     Info : Type_Info :=
                       Type_From_Indication (Element, Element);
                     List : Asis.Discriminant_Association_List :=
                       Asis.Definitions.Discriminant_Associations (Constr);
                  begin
                     if Is_Resolved (Info, Element) then
                        for I in List'Range loop
                           declare
                              use Asis.Expressions;
                              use Asis.Gela.Elements.Assoc;
                              Expr  : Asis.Expression :=
                                Discriminant_Expression (List (I));
                              Saved : Asis.Expression := Expr;
                              Names : Asis.Expression_List :=
                                Discriminant_Selector_Names (List (I));
                              Tipe  : Type_Info :=
                                Resolve_Discriminant_Names (Info, Names, I);
                           begin
                              if Is_Not_Type (Tipe) then
                                 return;
                              end if;

                              Resolve_To (Expr, Some_Type, Tipe);

                              if not Is_Equal (Expr, Saved) then
                                 Set_Discriminant_Expression
                                   (Discriminant_Association_Node
                                     (List (I).all),
                                    Expr);
                              end if;
                           end;
                        end loop;
                     end if;
                  end;
               when others =>
                  null;
            end case;
         when A_Discrete_Range =>
            Parent := Enclosing_Element (Element);
            if Definition_Kind (Parent) = A_Variant then
               declare
                  Discr : Asis.Declaration :=
                    Find_Variant_Discriminant (Parent);
                  Info : Type_Info;
               begin
                  if Assigned (Discr) then
                     Info := Type_Of_Declaration (Discr, Element);
                     if Is_Resolved (Info, Discr) then
                        Resolve_To (Element, Some_Range, Info);
                     end if;
                  end if;
               end;
            elsif Path_Kind (Parent) = A_Case_Path then
               declare
                  Info : Type_Info := Find_Case_Type (Parent);
               begin
                  if Is_Resolved (Info, Parent) then
                     Resolve_To (Element, Some_Range, Info);
                  end if;
               end;
            end if;
         when others =>
            null;
      end case;
   end Resolve_Definition;

   --------------------------------
   -- Resolve_Discriminant_Names --
   --------------------------------

   function Resolve_Discriminant_Names
     (Info  : Type_Info;
      Names : Asis.Expression_List;
      Index : Asis.List_Index) return Type_Info
   is
      Result : Type_Info;
      Found  : Boolean := False;
      Decl   : Asis.Declaration := Get_Declaration (Info);
      Place  : Asis.Element := Get_Place (Info);
      Part   : Asis.Definition := Discriminant_Part (Decl);
   begin
      if Definition_Kind (Part) /= A_Known_Discriminant_Part then
         return Result;
      end if;

      declare
         List : Asis.Declaration_List :=
           Asis.Definitions.Discriminants (Part);
      begin
         for J in Names'Range loop
            declare
               Image : Asis.Program_Text := XASIS.Utils.Name_Image (Names (J));
               Discr : Asis.Declaration := Find_Discriminant (List, Image);
               Name  : Asis.Expression := Names (J);
            begin
               if Assigned (Discr) then
                  if not Found then
                     Result := Type_Of_Declaration (Discr, Place);
                     Found  := True;
                  end if;
                  Walk.Set_Declaration (Name, Discr);
               end if;
            end;
         end loop;

         if Names'Length = 0 and Index in List'Range then
            Result := Type_Of_Declaration (List (Index), Place);
         end if;
      end;

      return Result;
   end Resolve_Discriminant_Names;

   ---------------------------------
   -- Resolve_In_Component_Clause --
   ---------------------------------

   procedure Resolve_In_Component_Clause
     (Element : in out Asis.Element;
      Parent  : in     Asis.Clause)
   is
      Name : Asis.Name := Representation_Clause_Name (Parent.all);
   begin
      if not Is_Equal (Element, Name) then
         Resolve_To (Element, Any_Integer_Type);
      end if;
   end Resolve_In_Component_Clause;

   ----------------------------
   -- Resolve_In_Declaration --
   ----------------------------

   procedure Resolve_In_Declaration
     (Element : in out Asis.Element;
      Parent  : in     Asis.Declaration)
   is
      Kind : Asis.Declaration_Kinds := Declaration_Kind (Parent);
   begin
      case Kind is
         when An_Integer_Number_Declaration =>
            Resolve_To (Element, Any_Numeric_Type);

         when A_Variable_Declaration |
           A_Constant_Declaration |
           A_Component_Declaration =>

            declare
               Info : Type_Info := Type_Of_Declaration (Parent, Element);
            begin
               if Is_Resolved (Info, Parent) then
                  Resolve_To (Element, Some_Type, Info);
               end if;
            end;

         when A_Discriminant_Specification |
           A_Parameter_Specification |
           A_Formal_Object_Declaration |
           A_Return_Object_Specification =>

            if Is_Equal (Initialization_Expression (Parent), Element) then
               declare
                  Info : Type_Info := Type_Of_Declaration (Parent, Element);
               begin
                  if Is_Resolved (Info, Parent) then
                     Resolve_To (Element, Some_Type, Info);
                  end if;
               end;
            end if;

         when An_Object_Renaming_Declaration =>
            if Is_Equal (Renamed_Entity (Parent), Element) then
               declare
                  Info : Type_Info := Type_Of_Declaration (Parent, Element);
               begin
                  if Is_Resolved (Info, Parent) then
                     Resolve_To (Element, Some_Type, Info);
                  end if;
               end;
            end if;

         when A_Procedure_Renaming_Declaration |
           A_Function_Renaming_Declaration =>
            if Is_Equal (Renamed_Entity (Parent), Element) then
               Resolve_To (Element, A_Callable_Name, Profile => Parent);
            end if;

         when A_Formal_Function_Declaration |
           A_Formal_Procedure_Declaration =>
            declare
               Default : constant Asis.Expression :=
                 Formal_Subprogram_Default (Parent);
            begin
               if Is_Equal (Element, Default) and then
                 Expression_Kind (Element) /= Asis.A_Null_Literal
               then
                  Resolve_To (Element, A_Callable_Name, Profile => Parent);
               end if;
            end;
         when An_Entry_Body_Declaration =>
            Resolve_To (Element, Any_Boolean_Type);

         when others =>
            null;
      end case;
   end Resolve_In_Declaration;

   ---------------------------
   -- Resolve_In_Definition --
   ---------------------------

   procedure Resolve_In_Definition
     (Element : in out Asis.Element;
      Parent  : in     Asis.Definition)
   is
      use Asis.Definitions;
      Kind : Asis.Definition_Kinds := Definition_Kind (Parent);
   begin
      case Kind is
         when A_Constraint =>
            case Constraint_Kind (Parent) is
               when A_Range_Attribute_Reference =>
                  declare
                     Ind  : Asis.Subtype_Indication :=
                       Find_Subtype_Of_Constraint (Parent);
                     Info : Type_Info;
                  begin
                     if Assigned (Ind) then
                        Info := Type_From_Indication (Ind, Element);

                        if Is_Resolved (Info, Ind) then
                           Resolve_To (Element, Some_Range, Info);
                        end if;
                     end if;
                  end;

               when A_Simple_Expression_Range =>
                  if Clause_Kind (Enclosing_Element (Parent))
                    = A_Component_Clause
                  then
                     Resolve_To (Element, Any_Integer_Type);
                     return;
                  end if;

                  declare
                     Ind  : Asis.Subtype_Indication :=
                       Find_Subtype_Of_Constraint (Parent);
                     Info : Type_Info;
                  begin
                     if Assigned (Ind) then
                        Info := Type_From_Indication (Ind, Element);

                        if Is_Resolved (Info, Ind) then
                           Resolve_To (Element, Some_Type, Info);
                        end if;
                     elsif Is_Part_Of_Signed_Type (Parent) then
                        Resolve_To (Element, Any_Integer_Type);
                     elsif Is_Part_Of_Float_Type (Parent)
                       or Is_Part_Of_Fixed_Type (Parent)
                     then
                        Resolve_To (Element, Any_Real_Type);
                     end if;
                  end;

               when A_Digits_Constraint =>
                  Resolve_To (Element, Any_Integer_Type);

               when A_Delta_Constraint =>
                  Resolve_To (Element, Any_Real_Type);

               when others =>
                  null;
            end case;
         when A_Type_Definition =>
            case Type_Kind (Parent) is
               when A_Modular_Type_Definition |
                    A_Floating_Point_Definition =>
                  Resolve_To (Element, Any_Integer_Type);

               when An_Ordinary_Fixed_Point_Definition =>
                  Resolve_To (Element, Any_Real_Type);

               when A_Decimal_Fixed_Point_Definition =>
                  if Is_Equal (Element, Delta_Expression (Parent)) then
                     Resolve_To (Element, Any_Real_Type);
                  else
                     Resolve_To (Element, Any_Integer_Type);
                  end if;

               when others =>
                  null;
            end case;
         when A_Variant =>
            declare
               Discr : Asis.Declaration := Find_Variant_Discriminant (Parent);
               Info  : Type_Info;
            begin
               if Assigned (Discr) then
                  Info := Type_Of_Declaration (Discr, Element);
                  if Is_Resolved (Info, Discr) then
                     Resolve_To (Element, Some_Type, Info);
                  end if;
               end if;
            end;
         when A_Variant_Part =>
            declare
               Discr : Asis.Declaration := Find_Part_Discriminant (Parent);
            begin
               if Assigned (Discr) then
                  Walk.Set_Declaration (Element, Discr);
               end if;
            end;
         when others =>
            null;
      end case;
   end Resolve_In_Definition;


   --------------------------------
   -- Resolve_In_Enum_Rep_Clause --
   --------------------------------

   procedure Resolve_In_Enum_Rep_Clause
     (Element : in out Asis.Element;
      Parent  : in     Asis.Clause)
   is
      Name : Asis.Element;
      Info : Type_Info;
      Assc : Asis.Element;
   begin
      if Element_Kind (Element.all) = An_Association then
         Walk.Check_Association (Element);
         return;
      end if;

      Assc := Enclosing_Element (Element.all);

      if Is_Equal (Element, Component_Expression (Assc.all)) then
         Resolve_To (Element, Any_Integer_Type);
         Gela.Resolver.Polish_Subexpression (Element);
         return;
      end if;

      Name := Representation_Clause_Name (Parent.all);
      Info := Type_From_Subtype_Mark (Name, Element);

      if Is_Resolved (Info, Name) then
         Resolve_To (Element, Some_Type, Info);
      end if;
   end Resolve_In_Enum_Rep_Clause;

   --------------------------
   -- Resolve_In_Statement --
   --------------------------

   procedure Resolve_In_Statement
     (Element : in out Asis.Element;
      Parent  : in     Asis.Statement)
   is
      use Asis.Statements;
      use Asis.Expressions;
   begin
      case Statement_Kind (Parent) is
         when A_Case_Statement =>
            Resolve_To (Element, Any_Discrete_Type);

         when A_While_Loop_Statement | An_Exit_Statement =>
            Resolve_To (Element, Any_Boolean_Type);

         when A_Return_Statement =>
            declare
               Decl : Asis.Declaration :=
                 XASIS.Utils.Parent_Declaration (Parent);
               Mark : Asis.Definition :=
                 XASIS.Utils.Get_Result_Subtype (Decl);
               Info : Type_Info :=
                 Type_From_Indication (Mark, Element);
            begin
               if Is_Resolved (Info, Mark) then
                  Resolve_To (Element, Some_Type, Info);
               end if;
            end;

         when An_Accept_Statement =>
            if Is_Equal (Element, Accept_Entry_Direct_Name (Parent)) then
               Resolve_To (Element, A_Callable_Name, Profile => Parent);
            elsif Is_Equal (Element, Accept_Entry_Index (Parent)) then
               declare
                  Ident : Asis.Identifier := Accept_Entry_Direct_Name (Parent);
                  Decl  : Asis.Declaration;
                  Def   : Asis.Discrete_Subtype_Definition;
                  Info  : Type_Info;
               begin
                  if not Assigned (Ident) then
                     return;
                  end if;
                  Decl := Corresponding_Name_Declaration (Ident);
                  if not Assigned (Decl) then
                     return;
                  end if;
                  Def := Entry_Family_Definition (Decl);
                  Info := Type_From_Discrete_Def (Def, Element);
                  if Is_Resolved (Info, Def) then
                     Resolve_To (Element, Some_Type, Info);
                  end if;
               end;
            end if;
         when A_Delay_Until_Statement =>
            Resolve_To (Element, Any_Nonlimited);

         when A_Delay_Relative_Statement =>
            declare
               Info  : Type_Info :=
                 Type_From_Declaration (XASIS.Types.Duration, Element);
            begin
               if Is_Resolved (Info, XASIS.Types.Duration) then
                  Resolve_To (Element, Some_Type, Info);
               end if;
            end;
         when A_Code_Statement =>
            Resolve_To (Element, Any_Type);
         when A_Requeue_Statement | A_Requeue_Statement_With_Abort =>
            declare
               Decl : Asis.Element := Parent_Of_Requeue (Parent);
            begin
               Resolve_To (Element, A_Requeue, Profile => Decl);
            end;
         when A_Raise_Statement =>
            if Is_Equal (Element, Raise_Statement_Message (Parent)) then
               declare
                  Info  : Type_Info :=
                    Type_From_Declaration (XASIS.Types.String, Element);
               begin
                  Resolve_To (Element, Some_Type, Info);
               end;
            end if;
         when others =>
            null;
      end case;
   end Resolve_In_Statement;

   ----------------
   -- Resolve_To --
   ----------------

   procedure Resolve_To
     (Element : in out Asis.Element;
      Expect  : in     Expected_Kinds;
      Tipe    : in     Type_Info := Not_A_Type;
      Profile : in     Asis.Declaration := Asis.Nil_Element)
   is
      use Asis.Gela.Overloads.Walk;
      use Asis.Gela.Overloads.Iters;

      Up      : Up_Resolver;
      Down    : Down_Resolver;
      Control : Traverse_Control := Continue;
      Set     : Up_Interpretation_Set;
      Result  : Up_Interpretation;
      Impl    : Implicit_Set;
   begin
      Up_Iterator.Walk_Element (Element, Control, Up);
      Set := Get_Interpretations (Up);
      Impl := Get_Implicits (Up);

      case Expect is
         when Any_Numeric_Type =>
            Constrain_To_Numeric_Types (Set, Impl, Element);
         when Any_Integer_Type =>
            Constrain_To_Integer_Types (Set, Impl, Element);
         when Any_Real_Type =>
            Constrain_To_Real_Types (Set, Impl, Element);
         when Some_Type =>
            Constrain_To_Type (Set, Impl, Element, Tipe);
         when Some_Range =>
            Constrain_To_Range (Set, Impl, Element, Tipe);
         when Any_Discrete_Range =>
            Constrain_To_Discrete_Range (Set, Impl, Element);
         when Any_Boolean_Type =>
            Constrain_To_Boolean_Types (Set, Impl, Element);
         when Any_Discrete_Type =>
            Constrain_To_Discrete_Types (Set, Impl, Element);
         when Any_Type =>
            null;
         when A_Call_Statement =>
            Constrain_To_Calls (Set);
         when A_Callable_Name =>
            Constrain_To_Expected_Profile (Set, Profile, Element);
         when Any_Nonlimited =>
            Constrain_To_Non_Limited_Types (Set, Impl, Element);
         when A_Requeue =>
            Constrain_To_Expected_Profile (Set, Profile, Element, True);
      end case;

      Select_Prefered (Set);

      pragma Assert (Debug.Run (Element, Debug.Overload) or else
                     Debug.Dump (Types.Image (Set)));

      if Has_Interpretation (Set, Element) then
         if Expect = Some_Type then
            Result := Up_Expression (Tipe);
         else
            Get (Set, 1, Result);
         end if;

         Set_Interpretation (Down, To_Down_Interpretation (Result));
         Copy_Store_Set (Up, Down);
         Down_Iterator.Walk_Element (Element, Control, Down, False);
      end if;

      Destroy_Store_Set (Up);
      Destroy (Set);
      Destroy (Impl);
   end Resolve_To;

   ------------------------------
   -- Set_Representation_Value --
   ------------------------------

   procedure Set_Representation_Value (Element : Asis.Representation_Clause) is
      Name : Asis.Name := Representation_Clause_Name (Element.all);
      Info : Type_Info := Type_From_Subtype_Mark (Name, Element);
      View : Asis.Definition;
      Aggr : Asis.Expression := Representation_Clause_Expression (Element.all);
      Assc : Asis.Association_List := Array_Component_Associations (Aggr.all);
   begin
      if not Is_Enumeration (Info) then
         return;
      end if;

      View := Get_Type_Def (Top_Parent_Type (Info));

      declare
         List  : Asis.Declaration_List :=
           Enumeration_Literal_Declarations (View.all);
         Index : Asis.List_Index := 1;
      begin
         for J in Assc'Range loop
            declare
               use XASIS;

               Enum   : Asis.Declaration;
               Expr   : Asis.Expression := Component_Expression (Assc (J).all);
               Val    : Static.Value;
               Choice : Asis.Expression_List :=
                 Array_Component_Choices (Assc (J).all);
            begin
               if Asis.Extensions.Is_Static_Expression (Expr) then
                  Val := Static.Evaluate (Expr);

                  if Choice'Length = 0 then
--                     Enum := XASIS.Utils.Declaration_Name (List (Index));
                     Enum := List (Index);
                     Index := Index + 1;
                  else
                     Enum := Corresponding_Name_Declaration (Choice (1).all);
                  end if;

                  Element_Utils.Set_Representation_Value
                    (Enum, Static.Image (Val));
               end if;
            end;
         end loop;
      end;
   end Set_Representation_Value;

end Asis.Gela.Overloads;



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
