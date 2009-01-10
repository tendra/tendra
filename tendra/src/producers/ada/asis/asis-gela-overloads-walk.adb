------------------------------------------------------------------------------
--                           G E L A   A S I S                              --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA$:

with Ada.Wide_Text_IO;

with Asis.Elements;
with Asis.Expressions;
with Asis.Statements;
with Asis.Declarations;
with Asis.Gela.Debug;
with Asis.Gela.Element_Utils;
with Asis.Gela.Overloads.Walk.Up;
with Asis.Gela.Overloads.Walk.Down;
with Asis.Gela.Replace;
with XASIS.Types;
with XASIS.Utils;
with Asis.Gela.Classes;

package body Asis.Gela.Overloads.Walk is

   use Asis.Elements;
   use Asis.Gela.Classes;

   package R renames Asis.Gela.Replace;

   function Universal_Integer return Asis.Declaration
     renames XASIS.Types.Universal_Integer;

   function Universal_Real return Asis.Declaration
     renames XASIS.Types.Universal_Real;

   function Universal_Access return Asis.Declaration
     renames XASIS.Types.Universal_Access;

   procedure Set_Identifier
     (Element : in out Asis.Expression;
      Tipe    : in     Type_Info);

   procedure Set_Defining_Name
     (Element : in out Asis.Identifier;
      Name    : in     Asis.Defining_Name);

   -----------
   -- After --
   -----------

   procedure After
     (Element  : in out Asis.Element;
      Control  : in out Traverse_Control;
      Resolver : in out Up_Resolver)
   is
   begin
      case Element_Kind (Element) is

         when An_Expression =>
            case Expression_Kind (Element) is
               when A_Box_Expression =>
                  Up.Push_Single (Resolver, (Kind => A_Box));
               when An_Integer_Literal =>
                  Up.Push_Single (Resolver,
                                  Up_Expression (Universal_Integer, Element));

               when A_Real_Literal =>
                  Up.Push_Single (Resolver,
                                  Up_Expression (Universal_Real, Element));

               when A_String_Literal =>
                  raise Internal_Error;  --  go to An_Operator_Symbol

               when An_Identifier =>
                  Up.Push_Single (Resolver, (An_Identifier, Element));

               when An_Operator_Symbol =>
                  Up.Operator_Symbol_Or_String (Resolver, Element);

               when A_Character_Literal =>
                  Up.Push_Single (Resolver, (An_Identifier, Element),
                    Resolve => True);

               when An_Enumeration_Literal =>
                  raise Internal_Error;  --  go to An_Identifier

               when An_Explicit_Dereference =>
                  Up.Explicit_Dereference (Resolver, Element);

               when A_Function_Call =>
                  Up.Function_Call (Resolver, Element);

               when An_Indexed_Component =>
                  raise Internal_Error;  --  go to A_Function_Call

               when A_Slice =>
                  raise Internal_Error;  --  go to A_Function_Call

               when A_Selected_Component =>
                  Up.Selected_Component (Resolver, Element);

               when An_Attribute_Reference =>
                  Up.Attribute_Reference (Resolver, Element);

               when A_Record_Aggregate =>
                  Up.Aggregate (Resolver, Element);

               when An_Extension_Aggregate =>
                  Up.Aggregate (Resolver, Element, True);

               when A_Positional_Array_Aggregate |
                 A_Named_Array_Aggregate =>

                  raise Internal_Error;  --  go to A_Record_Aggregate

               when An_In_Range_Membership_Test |
                 A_Not_In_Range_Membership_Test |
                 An_In_Type_Membership_Test |
                 A_Not_In_Type_Membership_Test =>

                 Up.Membership (Resolver, Element);

               when An_And_Then_Short_Circuit |
                 An_Or_Else_Short_Circuit =>

                 Up.Short_Circuit (Resolver, Element);

               when A_Null_Literal =>
                  Up.Push_Single (Resolver,
                                  Up_Expression (Universal_Access, Element));

               when A_Parenthesized_Expression =>
                  null;

               when A_Type_Conversion =>
                  raise Internal_Error;  --  go to function call

               when A_Qualified_Expression =>
                  Up.Qualified_Expression (Resolver, Element);

               when An_Allocation_From_Subtype =>
                  Up.Allocation (Resolver, Element);

               when An_Allocation_From_Qualified_Expression =>
                  Up.Allocation (Resolver, Element, True);

               when Not_An_Expression =>
                  raise Internal_Error;
            end case;

         when An_Association =>
            case Association_Kind (Element) is
               when A_Record_Component_Association =>
                  declare
                     Choises : Asis.Element_List :=
                       Asis.Expressions.Record_Component_Choices (Element);
                  begin
                     for I in reverse Choises'Range loop
                        case Definition_Kind (Choises (I)) is
                           when An_Others_Choice =>
                              null;
                           when A_Discrete_Range =>
                              Drop_One (Resolver);
                           when others =>
                              Drop_One (Resolver);
                        end case;
                     end loop;
                  end;
               when A_Parameter_Association =>
                  if not Is_Nil (Asis.Expressions.Formal_Parameter (Element))
                  then
                     Drop_One (Resolver);
                  end if;
               when others =>
                  Ada.Wide_Text_IO.Put_Line ("After An_Association : " &
                    Asis.Elements.Debug_Image (Element));
                  raise Internal_Error;
            end case;

         when A_Definition =>
            case Definition_Kind (Element) is
               when A_Constraint =>
                  case Constraint_Kind (Element) is
                     when A_Simple_Expression_Range =>
                        Up.Simple_Range (Resolver, Element);
                     when A_Range_Attribute_Reference =>
                        null;
                     when others =>
                        Ada.Wide_Text_IO.Put_Line
                         ("After A_Constraint : " &
                          Asis.Elements.Debug_Image (Element));
                        raise Unimplemented;
                  end case;

               --  FIXME: Delete this case (A_Constraint instead)
               when A_Discrete_Range | A_Discrete_Subtype_Definition =>
                  case Discrete_Range_Kind (Element) is
                     when A_Discrete_Simple_Expression_Range =>
                        Up.Simple_Range (Resolver, Element);
                     when A_Discrete_Range_Attribute_Reference =>
                        null;
                     when others =>
                        Ada.Wide_Text_IO.Put_Line
                         ("After A_Discrete_Range : " &
                          Asis.Elements.Debug_Image (Element));
                        raise Unimplemented;
                  end case;
               when An_Others_Choice =>
                  null;
               when others =>
                  Ada.Wide_Text_IO.Put_Line ("After A_Definition : " &
                    Asis.Elements.Debug_Image (Element) &
                    Definition_Kinds'Wide_Image
                     (Definition_Kind (Element)));
                  raise Unimplemented;
            end case;

         when A_Statement =>
            case Statement_Kind (Element) is
               when An_Assignment_Statement =>
                  Up.Assignment (Resolver, Element);
               when A_Procedure_Call_Statement =>
                  Up.Function_Call (Resolver, Element);
               when others =>
                  raise Unimplemented;
            end case;

         when A_Defining_Name =>
            --  Labels as child of statements
            null;

         when others =>
            Ada.Wide_Text_IO.Put_Line ("After : " &
              Asis.Elements.Debug_Image (Element));
            raise Unimplemented;

      end case;

      pragma Assert (Debug.Run (Element, Debug.Overload_Up) or else
                     Debug.Dump (Types.Image (U.Top (Resolver.Stack))));
   end After;

   -----------
   -- After --
   -----------

   procedure After
     (Element  : in out Asis.Element;
      Control  : in out Traverse_Control;
      Resolver : in out Down_Resolver)
   is
   begin
      null;
   end After;

   ------------
   -- Before --
   ------------

   procedure Before
     (Element  : in out Asis.Element;
      Control  : in out Traverse_Control;
      Resolver : in out Up_Resolver)
   is
   begin
      case Element_Kind (Element) is
         when An_Expression =>
            case Expression_Kind (Element) is
               when An_Allocation_From_Subtype  =>
                  Up.Allocation (Resolver, Element);
                  Control := Abandon_Children;
               when others =>
                  null;
            end case;
         when others =>
            null;
      end case;
   end Before;

   ------------
   -- Before --
   ------------

   procedure Before
     (Element  : in out Asis.Element;
      Control  : in out Traverse_Control;
      Resolver : in out Down_Resolver)
   is
      use Asis.Expressions;

      Got  : Down_Interpretation;
      Next : Down_Interpretation;
   begin
      Down.Check_Implicit (Resolver, Element, Control);

      pragma Assert (Debug.Run (Element, Debug.Overload_Down) or else
                     Debug.Dump (Types.Image (D.Top (Resolver.Stack))));

      if Control = Abandon_Children then
         return;
      end if;

      case Element_Kind (Element) is
         when An_Expression =>
            case Expression_Kind (Element) is
               when A_Box_Expression =>
                  D.Pop (Resolver.Stack, Next);

                  if Next.Kind = An_Expression then
                     Down.Set_Expression_Type (Element, Next.Expression_Type);
                  end if;

               when An_Integer_Literal =>
                  D.Pop (Resolver.Stack, Next);
                  if Next.Kind /= An_Expression then
                     raise Internal_Error;
                  end if;
                  Down.Set_Expression_Type (Element, Universal_Integer);

               when A_Real_Literal =>
                  D.Pop (Resolver.Stack, Next);
                  if Next.Kind /= An_Expression then
                     raise Internal_Error;
                  end if;
                  Down.Set_Expression_Type (Element, Universal_Real);

               when A_String_Literal =>
                  raise Internal_Error;  --  go to An_Operator_Symbol

               when An_Identifier =>
                  D.Pop (Resolver.Stack, Next);
                  --  FIXME function without parameters
                  case Next.Kind is
                     when An_Expression =>
                        Set_Identifier (Element, Next.Expression_Type);
                        Down.Set_Expression_Type (Element, Next.Expression_Type);
                     when A_Declaration =>
                        Set_Declaration (Element, Next.Declaration);
                     when A_Procedure_Call |
                          A_Prefixed_View |
                          A_Family_Member |
                          A_Subprogram_Reference |
                          A_Range |
                          A_Subaggregate |
                          A_Skip |
                          An_Attribute_Function |
                          Up_Only_Kinds =>
                        raise Internal_Error;
                  end case;

               when An_Operator_Symbol =>
                  D.Pop (Resolver.Stack, Next);
                  case Next.Kind is
                     when An_Expression =>
                        if Is_String (Next.Expression_Type) then

                           R.Operator_Symbol_To_String_Literal (Element);
                           Down.Set_Expression_Type
                            (Element, Next.Expression_Type);

                        else
                           raise Internal_Error;
                        end if;
                     when A_Declaration =>
                        Set_Declaration (Element, Next.Declaration);
                     when A_Procedure_Call |
                          A_Prefixed_View |
                          A_Family_Member |
                          A_Range |
                          A_Subprogram_Reference |
                          Up_Only_Kinds |
                          A_Subaggregate |
                          An_Attribute_Function |
                          A_Skip =>
                        raise Internal_Error;
                  end case;

               when A_Character_Literal =>
                  D.Pop (Resolver.Stack, Next);
                  case Next.Kind is
                     when An_Expression =>
                        Set_Identifier (Element, Next.Expression_Type);
                        Down.Set_Expression_Type
                          (Element, Next.Expression_Type);

                     when A_Declaration =>
                        Set_Declaration (Element, Next.Declaration);
                        -- Set_Identifier (Element, Next.Declaration);
                     when A_Procedure_Call |
                          A_Prefixed_View |
                          A_Family_Member |
                          A_Range |
                          A_Subprogram_Reference |
                          Up_Only_Kinds |
                          A_Subaggregate |
                          An_Attribute_Function |
                          A_Skip =>
                        raise Internal_Error;
                  end case;

               when An_Enumeration_Literal =>
                  raise Internal_Error;  --  go to An_Identifier

               when An_Explicit_Dereference =>
                  Down.Explicit_Dereference (Resolver, Element);

               when A_Function_Call =>
                  Down.Function_Call (Resolver, Element);

               when An_Indexed_Component =>
                  null;
                  --  this is new Element introduced
                  --  by R.Procedure_To_Indexed_Entry_Call
                  --  we skip it.
                  --  actual Indexed_Component goes into A_Function_Call

               when A_Slice =>
                  raise Internal_Error;  --  go to A_Function_Call

               when A_Selected_Component =>
                  Down.Selected_Component (Resolver, Element);

               when An_Attribute_Reference =>
                  Down.Attribute_Reference (Resolver, Element);

               when A_Record_Aggregate =>
                  Down.Aggregate (Resolver, Element);

               when An_Extension_Aggregate =>
                  Down.Aggregate (Resolver, Element, True);

               when A_Positional_Array_Aggregate | A_Named_Array_Aggregate =>
                  raise Internal_Error;  --  go to A_Record_Aggregate

               when An_In_Range_Membership_Test |
                 A_Not_In_Range_Membership_Test |
                 An_In_Type_Membership_Test |
                 A_Not_In_Type_Membership_Test =>

                 Down.Membership (Resolver, Element);

               when An_And_Then_Short_Circuit |
                 An_Or_Else_Short_Circuit =>

                  D.Pop (Resolver.Stack, Next);
                  if Next.Kind /= An_Expression then
                     raise Internal_Error;
                  end if;
                  Down.Set_Expression_Type (Element, Next.Expression_Type);
                  D.Push (Resolver.Stack, Next);
                  D.Push (Resolver.Stack, Next);

               when A_Null_Literal =>
                  D.Pop (Resolver.Stack, Next);
                  if Next.Kind /= An_Expression then
                     raise Internal_Error;
                  end if;
                  Down.Set_Expression_Type (Element, Universal_Access);

               when A_Parenthesized_Expression =>
                  D.Pop (Resolver.Stack, Next);

                  if Next.Kind = An_Expression then
                     Down.Set_Expression_Type (Element, Next.Expression_Type);
                  end if;

                  D.Push (Resolver.Stack, Next);

               when A_Type_Conversion =>
                  raise Internal_Error;  --  go to function call

               when A_Qualified_Expression =>
                  Down.Qualified_Expression (Resolver, Element);

               when An_Allocation_From_Subtype  =>
                  D.Pop (Resolver.Stack, Next);
                  if Next.Kind /= An_Expression then
                     raise Internal_Error;
                  end if;
                  Down.Set_Expression_Type (Element, Next.Expression_Type);
                  Control := Abandon_Children;

               when An_Allocation_From_Qualified_Expression =>
                  D.Pop (Resolver.Stack, Got);
                  if Got.Kind /= An_Expression then
                     raise Internal_Error;
                  end if;
                  Down.Set_Expression_Type (Element, Got.Expression_Type);
                  Next := To_Down_Interpretation
                    (Dereference (Got.Expression_Type));
                  D.Push (Resolver.Stack, Next);

               when Not_An_Expression =>
                  raise Internal_Error;
            end case;   --  End of Expressions

         when An_Association =>
            case Association_Kind (Element) is
               when A_Record_Component_Association =>
                  Check_Association (Element);
               when A_Parameter_Association =>
                  null; -- FIXME
               when others =>
                  Ada.Wide_Text_IO.Put_Line ("Before2 : " &
                    Asis.Elements.Debug_Image (Element));
                  raise Unimplemented;
            end case;

         when A_Definition =>
            case Definition_Kind (Element) is
               when A_Constraint =>
                  case Constraint_Kind (Element) is
                     when A_Simple_Expression_Range =>
                        D.Pop (Resolver.Stack, Got);
                        if Got.Kind = A_Range then
                           Next := (An_Expression, Got.Range_Type);
                        elsif Got.Kind /= An_Expression then
                           Ada.Wide_Text_IO.Put_Line ("Before7");
                           raise Internal_Error;
                        else
                           Next := Got;
                        end if;
                        D.Push (Resolver.Stack, Next);
                        D.Push(Resolver.Stack, Next);

                     when A_Range_Attribute_Reference =>
                        null;
                     when others =>
                        Ada.Wide_Text_IO.Put_Line ("Before4 : " &
                          Asis.Elements.Debug_Image (Element));
                        raise Unimplemented;
                  end case;

               --  FIXME: Delete this case (A_Constraint instead)
               when A_Discrete_Range | A_Discrete_Subtype_Definition =>
                  case Discrete_Range_Kind (Element) is
                     when A_Discrete_Simple_Expression_Range =>
                        D.Pop (Resolver.Stack, Got);
                        if Got.Kind = A_Range then
                           Next := (An_Expression, Got.Range_Type);
                        elsif Got.Kind /= An_Expression then
                           Ada.Wide_Text_IO.Put_Line ("Before6");
                           raise Internal_Error;
                        else
                           Next := Got;
                        end if;
                        D.Push (Resolver.Stack, Next);
                        D.Push(Resolver.Stack, Next);
                     when A_Discrete_Range_Attribute_Reference =>
                        null;
                     when others =>
                        Ada.Wide_Text_IO.Put_Line ("Before4 : " &
                          Asis.Elements.Debug_Image (Element));
                        raise Unimplemented;
                  end case;
               when An_Others_Choice =>
                  null;
               when others =>
                  Ada.Wide_Text_IO.Put_Line ("Before3 : " &
                    Asis.Elements.Debug_Image (Element));
                  raise Unimplemented;
            end case;

         when A_Statement =>
            case Statement_Kind (Element) is
               when An_Assignment_Statement =>
                  Down.Assignment (Resolver, Element);
               when A_Procedure_Call_Statement =>
                  Down.Function_Call (Resolver, Element);
               when others =>
                  raise Unimplemented;
            end case;

         when A_Defining_Name =>
            --  Labels as child of statements
            null;

         when others =>
            Ada.Wide_Text_IO.Put_Line ("Before : " &
              Asis.Elements.Debug_Image (Element));
            raise Unimplemented;
      end case;
   end Before;

   -----------------------
   -- Check_Association --
   -----------------------

   procedure Check_Association (Element : in out Asis.Element) is
      Parent : Asis.Element := Enclosing_Element (Element);
   begin
      case Expression_Kind (Parent) is
         when A_Function_Call =>
            R.Record_To_Parameter_Association (Element);
         when A_Positional_Array_Aggregate | A_Named_Array_Aggregate =>
            R.Record_To_Array_Association (Element);
         when A_Record_Aggregate | An_Extension_Aggregate =>
            null;
         when Not_An_Expression =>
            case Statement_Kind (Parent) is
               when A_Procedure_Call_Statement
                 | An_Entry_Call_Statement
                 =>
                  R.Record_To_Parameter_Association (Element);
               when others =>
                  Ada.Wide_Text_IO.Put_Line ("Check_Association2");
            end case;
         when others =>
            Ada.Wide_Text_IO.Put_Line ("Check_Association : " &
              Asis.Elements.Debug_Image (Parent) & ' ' &
              Expression_Kinds'Wide_Image (Expression_Kind (Parent)));
            raise Internal_Error;
      end case;
   end Check_Association;

   --------------------
   -- Copy_Store_Set --
   --------------------

   procedure Copy_Store_Set
     (Source  : in     Up_Resolver;
      Target  : in out Down_Resolver) is
   begin
      Target.Store := Source.Store;
      Target.Implicit := Source.Implicit;
   end Copy_Store_Set;

   ------------------------------------
   -- Could_Be_Named_Array_Aggregate --
   ------------------------------------

   function Could_Be_Named_Array_Aggregate
     (Item : Asis.Element) return Boolean
   is
      use Asis.Expressions;
      List : Asis.Association_List := Record_Component_Associations (Item);
   begin
      if List'Length = 0 then  --  null record
         return False;
      end if;
      for I in List'Range loop
         declare
            Choises : Asis.Expression_List :=
              Record_Component_Choices (List (I));
         begin
            if List'Length = 1 and then Choises'Length = 0 then
               return False;
            end if;
            if Element_Kind (Component_Expression (List(I))) /= An_Expression
            then
               return False;
            end if;
         end;
      end loop;
      return True;
   end Could_Be_Named_Array_Aggregate;

   -----------------------------------------
   -- Could_Be_Positional_Array_Aggregate --
   -----------------------------------------

   function Could_Be_Positional_Array_Aggregate
     (Item : Asis.Element) return Boolean
     renames R.Could_Be_Positional_Array_Aggregate;

   -------------------------------
   -- Could_Be_Record_Aggregate --
   -------------------------------

   function Could_Be_Record_Aggregate
     (Item      : Asis.Element;
      Extension : Boolean) return Boolean
   is
      use Asis.Expressions;
      List : Asis.Association_List := Record_Component_Associations (Item);
   begin
      for I in List'Range loop
         if Element_Kind (Component_Expression (List(I))) /= An_Expression then
            return False;
         end if;
         declare
            Choises : Asis.Expression_List :=
              Record_Component_Choices (List (I));
         begin
            if not Extension
              and then List'Length = 1
              and then Choises'Length = 0
            then
               return False;
            end if;

            for J in Choises'Range loop
               if Expression_Kind (Choises (J)) /= An_Identifier and then
                 Definition_Kind (Choises (J)) /= An_Others_Choice
               then
                  return False;
               end if;
            end loop;
         end;
      end loop;
      return True;
   end Could_Be_Record_Aggregate;

   -----------------------
   -- Destroy_Store_Set --
   -----------------------

   procedure Destroy_Store_Set (Source : in out Up_Resolver) is
   begin
      Destroy (Source.Store);
   end Destroy_Store_Set;

   --------------
   -- Drop_One --
   --------------

   procedure Drop_One (Resolver : in out Up_Resolver) is
      Top  : Up_Interpretation_Set;
      Drop : Up_Interpretation_Set;
   begin
      U.Pop (Resolver.Stack, Top);
      U.Pop (Resolver.Stack, Drop);
      U.Push (Resolver.Stack, Top);
      Destroy (Drop);
   end Drop_One;

   -----------------------
   -- Find_Formal_Index --
   -----------------------

   procedure Find_Formal_Index
     (Params       : in     Asis.Association_List;
      Actual_Index : in     List_Index;
      Profile      : in     Asis.Parameter_Specification_List;
      Formal_Index :    out List_Index;
      Found        :    out Boolean)
   is
      Formal : Asis.Identifier := Get_Formal_Parameter (Params, Actual_Index);
      Index  : List_Index := Actual_Index;
      Fake   : Boolean :=
        Profile'Length = 0 or else
        not XASIS.Utils.Is_Parameter_Specification (Profile (1));
   begin
      if Fake then

         Formal_Index := Actual_Index;
         Found := Formal_Index <= Profile'Last;

      elsif not Is_Nil (Formal) then
         Found := False;

         Find_Formal :
            for I in Profile'Range loop
               declare
                  List : constant Asis.Defining_Name_List :=
                    Asis.Declarations.Names (Profile (I));
                  Img  : constant Wide_String :=
                    Asis.Expressions.Name_Image (Formal);
               begin
                  for J in List'Range loop
                     if XASIS.Utils.Has_Name (List (J), Img) then
                        Found := True;
                        Formal_Index := I;
                        exit Find_Formal;
                     end if;
                  end loop;
               end;
            end loop Find_Formal;

      else
         Found := False;

         Find_Position :
            for I in Profile'Range loop
               declare
                  List : constant Asis.Defining_Name_List :=
                    Asis.Declarations.Names (Profile (I));
               begin
                  for J in List'Range loop
                     if Index = 1 then
                        Found := True;
                        Formal_Index := I;
                        exit Find_Position;
                     end if;
                     Index := Index - 1;
                  end loop;
               end;
            end loop Find_Position;
      end if;
   end Find_Formal_Index;

   --------------------------
   -- Get_Actual_Parameter --
   --------------------------

   function Get_Actual_Parameter
     (Params  : Asis.Association_List;
      Index   : List_Index) return Asis.Expression
   is
      use Asis.Expressions;
      Result : Asis.Expression;
   begin
      case Association_Kind (Params (Index)) is
         when A_Parameter_Association =>
            Result := Actual_Parameter (Params (Index));
         when A_Record_Component_Association =>
            Result := Component_Expression (Params (Index));
         when others =>
            raise Internal_Error;
      end case;
      return Result;
   end Get_Actual_Parameter;

   -------------------------
   -- Get_Call_Parameters --
   -------------------------

   function Get_Call_Parameters (Element : Asis.Element )
     return Asis.Association_List
   is
   begin
      if Expression_Kind (Element) = A_Function_Call then
         return Asis.Expressions.Function_Call_Parameters (Element);
      elsif Statement_Kind (Element) = A_Procedure_Call_Statement then
         return Asis.Statements.Call_Statement_Parameters (Element);
      else
         raise Internal_Error;
      end if;
   end Get_Call_Parameters;

   --------------------------
   -- Get_Formal_Parameter --
   --------------------------

   function Get_Formal_Parameter
     (Params  : Asis.Association_List;
      Index   : List_Index) return Asis.Identifier
   is
      use Asis.Expressions;
      Result : Asis.Identifier;
   begin
      case Association_Kind (Params (Index)) is
         when A_Parameter_Association =>
            Result := Formal_Parameter (Params (Index));
         when A_Record_Component_Association =>
            declare
               List : Asis.Expression_List :=
                 Record_Component_Choices (Params (Index));
            begin
               if List'Length /= 1 or else
                 Element_Kind (List (1)) /= An_Expression then
                  Result := Nil_Element;
               else
                  Result := List (1);
               end if;
            end;
         when others =>
            raise Internal_Error;
      end case;
      return Result;
   end Get_Formal_Parameter;

   -------------------
   -- Get_Implicits --
   -------------------

   function Get_Implicits
     (Resolver : in     Up_Resolver) return Implicit_Set
   is
   begin
      return Resolver.Implicit;
   end Get_Implicits;

   -------------------------
   -- Get_Interpretations --
   -------------------------

   function Get_Interpretations
     (Resolver : in     Up_Resolver)
      return Up_Interpretation_Set
   is
   begin
      return U.Top (Resolver.Stack);
   end Get_Interpretations;

   ----------------------
   -- Is_Expanded_Name --
   ----------------------

   function Is_Expanded_Name (Item : Asis.Element) return Boolean is
      use Asis.Expressions;

      Name : Asis.Expression := Selector (Item);
      Def  : Asis.Defining_Name := Corresponding_Name_Definition (Name);
   begin
      return not Is_Nil (Def);
   end Is_Expanded_Name;

   -------------------
   -- Is_Subprogram --
   -------------------

   function Is_Subprogram (Decl : Asis.Declaration) return Boolean is
      Kind : Asis.Declaration_Kinds := Declaration_Kind (Decl);
   begin
      case Kind is
         when A_Procedure_Declaration |
              A_Function_Declaration |
              A_Procedure_Body_Declaration |
              A_Function_Body_Declaration |
              A_Procedure_Renaming_Declaration |
              A_Function_Renaming_Declaration |
              A_Procedure_Instantiation |
              A_Function_Instantiation =>
            return True;
         when others =>
            return False;
      end case;
   end Is_Subprogram;

   ------------------------
   -- Set_Interpretation --
   ------------------------

   procedure Set_Interpretation
     (Resolver : in out Down_Resolver;
      Item     : in     Down_Interpretation)
   is
   begin
      D.Push (Resolver.Stack, Item);
   end Set_Interpretation;

   --------------------
   -- Set_Identifier --
   --------------------

   procedure Set_Identifier
     (Element : in out Asis.Expression;
      Tipe    : in     Type_Info)
   is
      use Asis.Expressions;

      List   : Asis.Defining_Name_List :=
        Corresponding_Name_Definition_List (Element);
      Parent : Asis.Declaration;
      Found  : Asis.Defining_Name;
      E_Type : Type_Info;
      Count  : Natural := 0;
   begin
      for I in List'Range loop
         Parent := Enclosing_Element (List (I));
         E_Type := Type_Of_Declaration (Parent, Element);

         if not Is_Not_Type (E_Type) and then Is_Expected_Type (E_Type, Tipe)
         then
            Count := Count + 1;
            Found := List (I);
         end if;
      end loop;

      if Count /= 1 then
         Ada.Wide_Text_IO.Put_Line ("Set_Identifier: " & Debug_Image (Element)
          & " " & Natural'Wide_Image (Count));
         Ada.Wide_Text_IO.Put_Line ("Tipe: " & Debug_Image (Tipe));
         Ada.Wide_Text_IO.Put_Line ("Found: " & Debug_Image (Found));
      else
         Set_Defining_Name (Element, Found);
      end if;
   end Set_Identifier;

   ---------------------
   -- Set_Declaration --
   ---------------------

   procedure Set_Declaration
     (Element : in out Asis.Identifier;
      Decl    : in     Asis.Declaration)
   is
      Img  : constant Wide_String :=
        Asis.Expressions.Name_Image (Element);
      Name : Asis.Defining_Name :=
        XASIS.Utils.Get_Defining_Name (Decl, Img);
   begin
      Set_Defining_Name (Element, Name);
   end Set_Declaration;

   -----------------------
   -- Set_Defining_Name --
   -----------------------

   procedure Set_Defining_Name
     (Element : in out Asis.Identifier;
      Name    : in     Asis.Defining_Name)
   is
   begin
      if Expression_Kind (Element) = An_Identifier and then
        Defining_Name_Kind (Name) = A_Defining_Enumeration_Literal
      then
         R.Identifier_To_Enumeration_Literal (Element);
      end if;

      Element_Utils.Set_Resolved (Element, (1 => Name));
   end Set_Defining_Name;

end Asis.Gela.Overloads.Walk;



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
