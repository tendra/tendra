with Asis.Elements;
with Asis.Gela.Errors;
with Asis.Gela.Replace;
with Asis.Expressions;
with Asis.Definitions;
with Asis.Declarations;
with Asis.Gela.Utils;
with Asis.Gela.Resolver;
with Asis.Gela.Elements.Assoc;
with Asis.Gela.Overloads.Iters;
with XASIS.Types;
with XASIS.Static;

package body Asis.Gela.Overloads.Walk.Down is

   use Asis.Elements;
   use Asis.Gela.Classes;

   package R renames Asis.Gela.Replace;

   procedure Push_Array_Indexes
     (Resolver : in out Down_Resolver;
      Tipe     : in     Type_Info);

   procedure Simple_Attribute_Reference
     (Resolver : in out Down_Resolver;
      Element  : in     Asis.Element);

   procedure Access_Attribute_Reference
     (Resolver : in out Down_Resolver;
      Element  : in     Asis.Element);

   procedure Length_Attribute_Reference
     (Resolver : in out Down_Resolver;
      Element  : in     Asis.Element);

   procedure First_Attribute_Reference
     (Resolver : in out Down_Resolver;
      Element  : in     Asis.Element);

   function Array_Dimention (Tipe : Type_Info) return Asis.List_Index;

   type Component_Info is record
      Declaration : Asis.Declaration;
      Association : Asis.Association;
      Processed   : Boolean := False;   --  For positional discr only
   end record;

   --------------------------------
   -- Access_Attribute_Reference --
   --------------------------------

   procedure Access_Attribute_Reference
     (Resolver : in out Down_Resolver;
      Element  : in     Asis.Element)
   is
      use Asis.Gela.Errors;
      use Asis.Expressions;

      Store  : Stored_Set;
      Stored : Stored_Interpretation;
      Down   : Down_Interpretation;
      Next   : Down_Interpretation;
      Found  : Boolean := False;
   begin
      Get (Resolver.Store, Element, Store);
      D.Pop (Resolver.Stack, Down);

      if Down.Kind = An_Expression then
         Set_Expression_Type (Element, Down.Expression_Type);
      else
         raise Internal_Error;
      end if;

      Get (Store, 1, Stored);

      if Stored.Down.Kind = A_Declaration and then
         Is_Subprogram (Stored.Down.Declaration)
      then
         for I in 1 .. Length (Store) loop
            Get (Store, I, Stored);
            if Conform_Access_Type (Stored.Down.Declaration,
                                    Down.Expression_Type)
            then
               if Found then
                  Report (Element, Error_Ambiguous_Interprentation);
               else
                  Next := To_Down_Interpretation (Stored.Down);
                  Found := True;
               end if;
            end if;
         end loop;
      else
         Next := To_Down_Interpretation (Stored.Down);
         Found := True;
      end if;

      if not Found then
         Report (Element, Error_No_Interprentation);
         Down := (Kind => A_Skip);
      end if;

      D.Push (Resolver.Stack, (Kind => A_Skip));
      D.Push (Resolver.Stack, Next);
      Destroy (Store);
   end Access_Attribute_Reference;

   ---------------
   -- Aggregate --
   ---------------

   procedure Aggregate
     (Resolver  : in out Down_Resolver;
      Element   : in out Asis.Element;
      Extension : in     Boolean := False)
   is
      use Asis.Gela.Errors;
      use Asis.Expressions;

      type Component_Info_List is
         array (Asis.List_Index range <>) of Component_Info;

      function Needed_Components
        (List      : Asis.Association_List;
         Tipe      : Type_Info) return Component_Info_List;

      procedure Resolve_Expression
        (Element : Asis.Association;
         Decl    : Asis.Declaration);

      ------------------------
      -- Resolve_Expression --
      ------------------------

      procedure Resolve_Expression
        (Element : Asis.Association;
         Decl    : Asis.Declaration)
      is
         use Asis.Gela.Elements.Assoc;

         Control : Traverse_Control := Continue;
         Expr    : Asis.Expression := Component_Expression (Element);
         Info    : Type_Info := Type_Of_Declaration (Decl, Element);
      begin
         D.Push (Resolver.Stack, Up_Expression (Info));
         Iters.Down_Iterator.Walk_Element (Expr, Control, Resolver);
         Set_Component_Expression
           (Record_Component_Association_Node (Element.all), Expr);
         Gela.Resolver.Polish_Subexpression (Expr);
      end Resolve_Expression;

      -----------------------
      -- Needed_Components --
      -----------------------

      function Needed_Components
        (List      : Asis.Association_List;
         Tipe      : Type_Info) return Component_Info_List
      is
         use Asis.Expressions;
         use Asis.Gela.Errors;

         type Discriminant_Info is record
            Decl      : Asis.Declaration;
            Value     : XASIS.Static.Value;
            Processed : Boolean := False;
            Found     : Boolean := False;
         end record;

         type Discriminant_Info_List is
           array (Asis.List_Index range <>) of Discriminant_Info;

         function Get_Discriminants (Decl : Asis.Declaration)
           return Discriminant_Info_List;

         function Count_Component (List : Asis.Association_List)
           return Natural;

         procedure Check_Variant
           (Item     : in     Asis.Variant;
            Continue :    out Boolean);

         procedure Find_Companent
           (Item     : in     Asis.Declaration;
            Continue :    out Boolean);

         procedure Find_Other_Companent
           (Item     : in     Asis.Declaration;
            Continue :    out Boolean);

         function Get_Discr_Index (Item : Asis.Variant)
           return Asis.List_Index;

         ---------------------
         -- Count_Component --
         ---------------------

         function Count_Component
           (List : Asis.Association_List)
            return Natural
         is
            Count : Natural := 0;
         begin
            for I in List'Range loop
               declare
                  Choices : Asis.Element_List :=
                    Asis.Expressions.Record_Component_Choices (List (I));
               begin
                  if Choices'Length = 0 then
                     Count := Count + 1;
                  elsif Choices'Length = 1 and then
                    Definition_Kind (Choices (1)) = An_Others_Choice
                  then
                     Count := Count + 1;
                  else
                     Count := Count + Choices'Length;
                  end if;
               end;
            end loop;
            return Count;
         end Count_Component;

         -----------------------
         -- Get_Discriminants --
         -----------------------

         function Get_Discriminants (Decl : Asis.Declaration)
           return Discriminant_Info_List
         is
            use Asis.Definitions;
            use Asis.Declarations;
            Part   : Asis.Definition := Discriminant_Part (Decl);
         begin
            if not Assigned (Part) or else
              Definition_Kind (Part) /= A_Known_Discriminant_Part
            then
               declare
                  Empty : Discriminant_Info_List (1 .. 0);
               begin
                  return Empty;
               end;
            end if;

            declare
               List   : Asis.Discriminant_Specification_List :=
                 Discriminants (Part);
               Result : Discriminant_Info_List (List'Range);
            begin
               for I in Result'Range loop
                  Result (I).Decl := List (I);
               end loop;
               return Result;
            end;
         end Get_Discriminants;

         Index   : Asis.List_Index := 1;
         Ignore  : Boolean;
         First   : Asis.List_Index := List'First;
         Last    : constant Asis.ASIS_Natural :=
            Asis.ASIS_Natural (Count_Component (List));
         Result  : Component_Info_List (1 .. Last);
         Decl    : Asis.Declaration := Get_Type_View (Tipe);
         Discr   : Discriminant_Info_List := Get_Discriminants (Decl);

         ---------------------
         -- Get_Discr_Index --
         ---------------------

         function Get_Discr_Index (Item : Asis.Variant)
           return Asis.List_Index
         is
            use Asis.Definitions;
            Parent : Asis.Element := Enclosing_Element (Item);
            Name   : Asis.Name := Discriminant_Direct_Name (Parent);
            Decl   : Asis.Declaration := Corresponding_Name_Declaration (Name);
            Found  : Asis.List_Index := 1;
            Expr   : Asis.Expression;
         begin
            for I in Discr'Range loop
               if Is_Equal (Discr (I).Decl, Decl) then
                  Found := I;
                  exit;
               end if;
            end loop;
            if not Discr (Found).Processed then
               for I in 1 .. Index - 1 loop
                  if Is_Equal (Result (I).Declaration, Decl) then
                     -------------------------------------------------
                     Resolve_Expression (Result (I).Association, Decl);
                     -------------------------------------------------

                     Result (I).Processed := True;
                     Expr := Component_Expression (Result (I).Association);
                     Discr (Found).Value := XASIS.Static.Evaluate (Expr);
                  end if;
               end loop;
               Discr (Found).Processed := True;
               Discr (Found).Found := False;
            end if;
            return Found;
         end Get_Discr_Index;

         -------------------
         -- Check_Variant --
         -------------------

         procedure Check_Variant
           (Item     : in     Asis.Variant;
            Continue :    out Boolean)
         is
            use XASIS.Static;
            Index       : Asis.List_Index := Get_Discr_Index (Item);
            Value       : XASIS.Static.Value;
            Choises     : Asis.Element_List :=
              Asis.Definitions.Variant_Choices (Item);
         begin
            if Discr (Index).Found then
               Continue := False;
               return;
            end if;

            for I in Choises'Range loop
               if Element_Kind (Choises (I)) = An_Expression then
                  Value := XASIS.Static.Evaluate (Choises (I));
                  if Discr (Index).Value = Value then
                     Discr (Index).Found := True;
                     Continue := True;
                  end if;
               elsif Definition_Kind (Choises (I)) = An_Others_Choice then
                  Discr (Index).Found := True;
                  Continue := True;
               else
                  if In_Range (Discr (Index).Value, Choises (I)) then
                     Discr (Index).Found := True;
                     Continue := True;
                  end if;
               end if;
            end loop;
            Continue := False;
         end Check_Variant;

         --------------------
         -- Find_Companent --
         --------------------

         procedure Find_Companent
           (Item     : in     Asis.Declaration;
            Continue :    out Boolean)
         is
         begin
            if Index in List'Range and then
              Record_Component_Choices (List (Index))'Length = 0
            then
               Continue := True;
               Result (Index).Declaration := Item;
               Result (Index).Association := List (Index);
               Index := Index + 1;
            else
               Continue := False;
            end if;
         end Find_Companent;

         --------------------------
         -- Find_Other_Companent --
         --------------------------

         procedure Find_Other_Companent
           (Item     : in     Asis.Declaration;
            Continue :    out Boolean)
         is
         begin
            for I in 1 .. Index - 1 loop
               if Is_Equal (Item, Result (I).Declaration) then
                  Continue := True;
                  return;
               end if;
            end loop;
            Result (Index).Declaration := Item;
            Continue := False;
         end Find_Other_Companent;

         procedure Find_Positional is
            new Gela.Utils.Walk_Components
                  (Element, Check_Variant, Find_Companent);

         procedure Find_Other is
            new Gela.Utils.Walk_Components
                  (Element, Check_Variant, Find_Other_Companent);

      begin  --  Needed_Components

         Find_Positional (Decl, Ignore);

         for I in First .. List'Last loop
            declare
               Choises : Asis.Element_List :=
                 Record_Component_Choices (List (I));
               Choice  : Asis.Identifier;
            begin
               for J in Choises'Range loop
                  Choice := Choises (J);
                  if Is_Nil (Choice) then
                     Report (List (I), Error_Syntax_Misplaced_Association);
                  elsif Definition_Kind (Choice) = An_Others_Choice then
                     Find_Other (Decl, Ignore);
                  elsif Expression_Kind (Choice) = An_Identifier then
                     declare
                        Name : Asis.Program_Text :=
                          Asis.Expressions.Name_Image (Choice);
                     begin
                        Result (Index).Association := List (I);
                        Result (Index).Declaration :=
                          Find_Component (Tipe, Name);
                     end;
                  else
                     raise Internal_Error;
                  end if;
                  Index := Index + 1;
               end loop;
            end;
         end loop;
         return Result;
      end Needed_Components;


      Store     : Stored_Set;
      Stored    : Stored_Interpretation;
      Down      : Down_Interpretation;
      Tipe      : Type_Info;
      Index     : Type_Info;
      Deep      : Asis.List_Index := 1;
      Dimention : Asis.List_Index;
      List      : Asis.Association_List
        := Record_Component_Associations (Element);
   begin
      D.Pop (Resolver.Stack, Down);

      if Down.Kind = An_Expression then
         Set_Expression_Type (Element, Down.Expression_Type);
         Tipe := Down.Expression_Type;
      elsif Down.Kind = A_Subaggregate then
         Tipe := Down.Array_Type;
         Deep := Down.Deep;
      else
         raise Internal_Error;
      end if;

      if not Extension and then Is_Array (Tipe) then

         Dimention := Array_Dimention (Tipe);
         Index     := Get_Array_Index_Type (Tipe, Deep);

         if Deep = Dimention then
            Down := Up_Expression (Get_Array_Element_Type (Tipe));
         else
            Down := (A_Subaggregate, Tipe, Deep + 1);
         end if;

         for I in reverse List'Range loop
            D.Push (Resolver.Stack, Down);
            declare
               Choises : Asis.Element_List :=
                 Record_Component_Choices (List (I));
            begin
               for J in Choises'Range loop
                  if Definition_Kind (Choises (J)) /= An_Others_Choice then
                     D.Push (Resolver.Stack, Up_Expression (Index));
                  end if;
               end loop;
            end;
         end loop;

         if Could_Be_Positional_Array_Aggregate (Element) then
            R.Record_To_Array_Aggregate (Element, True);
         else
            R.Record_To_Array_Aggregate (Element, False);
         end if;

      else  --  is record aggregate
         declare
            Fields : Component_Info_List :=
              Needed_Components (List, Tipe);
            Index  : Asis_Natural := Fields'Last;
            Expr   : Type_Info;
         begin
            for I in reverse List'Range loop
               Expr :=
                 Type_Of_Declaration (Fields (Index).Declaration, Element);

               if Fields (Index).Processed then
                  D.Push (Resolver.Stack, (Kind => A_Skip));
               else
                  D.Push (Resolver.Stack, Up_Expression (Expr));
               end if;

               declare
                  Choises : Asis.Element_List :=
                    Record_Component_Choices (List (I));
                  Other   : Boolean := False;
               begin
                  for J in reverse Choises'Range loop
                     if Definition_Kind (Choises (J)) /= An_Others_Choice then
                        D.Push (Resolver.Stack,
                          (A_Declaration, Fields (Index).Declaration));
                        Index := Index - 1;
                     else
                        Other := True;
                     end if;
                  end loop;

                  if Choises'Length = 0 or Other then
                     Index := Index - 1;
                  end if;
               end;
            end loop;
         end;

         if Extension then
            Get (Resolver.Store, Element, Store);
            if Length (Store) /= 1 then
               raise Internal_Error;
            end if;
            Get (Store, 1, Stored);
            D.Push (Resolver.Stack, To_Down_Interpretation (Stored.Down));
            Destroy (Store);
         end if;
      end if;
   end Aggregate;

   ---------------------
   -- Array_Dimention --
   ---------------------

   function Array_Dimention (Tipe : Type_Info) return Asis.List_Index is
      use Asis.Definitions;
      Def  : Asis.Definition := Get_Type_Def (Tipe);
   begin
      if Definition_Kind (Def) = A_Formal_Type_Definition then
         case Formal_Type_Kind (Def) is
            when A_Formal_Unconstrained_Array_Definition =>
               return Index_Subtype_Definitions (Def)'Length;
            when A_Formal_Constrained_Array_Definition =>
               return Discrete_Subtype_Definitions (Def)'Length;
            when others =>
               raise Internal_Error;
         end case;
      else
         case Type_Kind (Def) is
            when An_Unconstrained_Array_Definition =>
               return Index_Subtype_Definitions (Def)'Length;
            when A_Constrained_Array_Definition =>
               return Discrete_Subtype_Definitions (Def)'Length;
            when others =>
               raise Internal_Error;
         end case;
      end if;
   end Array_Dimention;

   ----------------
   -- Assignment --
   ----------------

   procedure Assignment
     (Resolver : in out Down_Resolver;
      Element  : in out Asis.Element)
   is
      Down      : Down_Interpretation;
   begin
      D.Pop (Resolver.Stack, Down);
      D.Push (Resolver.Stack, Down);
      D.Push (Resolver.Stack, Down);
   end Assignment;

   -------------------------
   -- Attribute_Reference --
   -------------------------

   procedure Attribute_Reference
     (Resolver : in out Down_Resolver;
      Element  : in     Asis.Element)
   is
      use Asis.Gela.Errors;
      use Asis.Expressions;

      Down   : Down_Interpretation;
      Kind   : Attribute_Kinds := Attribute_Kind (Element);
   begin
      case Kind is
         when Not_An_Attribute =>
            raise Internal_Error;

         when An_Access_Attribute =>
            Access_Attribute_Reference (Resolver, Element);

         when A_Base_Attribute |
           A_Class_Attribute =>

            D.Pop  (Resolver.Stack, Down);
            D.Push (Resolver.Stack, (Kind => A_Skip));
            D.Push (Resolver.Stack, Down);

         when A_First_Attribute |
           A_Last_Attribute |
           A_Range_Attribute  =>

            First_Attribute_Reference (Resolver, Element);

         when A_Length_Attribute =>

            Length_Attribute_Reference (Resolver, Element);

         when An_Address_Attribute |
           An_Adjacent_Attribute |
           An_Aft_Attribute |
           An_Alignment_Attribute |
           A_Bit_Order_Attribute |
           A_Body_Version_Attribute |
           A_Callable_Attribute |
           A_Caller_Attribute |
           A_Ceiling_Attribute |
           A_Component_Size_Attribute |
           A_Compose_Attribute |
           A_Constrained_Attribute |
           A_Copy_Sign_Attribute |
           A_Count_Attribute |
           A_Definite_Attribute |
           A_Delta_Attribute |
           A_Denorm_Attribute |
           A_Digits_Attribute |
           An_Exponent_Attribute |
           An_External_Tag_Attribute |
           A_First_Bit_Attribute |
           A_Floor_Attribute |
           A_Fore_Attribute |
           A_Fraction_Attribute |
           An_Identity_Attribute |
           An_Image_Attribute |
           An_Input_Attribute |
           A_Last_Bit_Attribute |
           A_Leading_Part_Attribute |
           A_Machine_Attribute |
           A_Machine_Emax_Attribute |
           A_Machine_Emin_Attribute |
           A_Machine_Mantissa_Attribute |
           A_Machine_Overflows_Attribute |
           A_Machine_Radix_Attribute |
           A_Machine_Rounding_Attribute |
           A_Machine_Rounds_Attribute |
           A_Max_Attribute |
           A_Max_Size_In_Storage_Elements_Attribute |
           A_Min_Attribute |
           A_Mod_Attribute |
           A_Model_Attribute |
           A_Model_Emin_Attribute |
           A_Model_Epsilon_Attribute |
           A_Model_Mantissa_Attribute |
           A_Model_Small_Attribute |
           A_Modulus_Attribute |
           A_Partition_ID_Attribute |
           A_Pos_Attribute |
           A_Position_Attribute |
           A_Pred_Attribute |
           A_Priority_Attribute |
           A_Read_Attribute |
           A_Remainder_Attribute |
           A_Round_Attribute |
           A_Rounding_Attribute |
           A_Safe_First_Attribute |
           A_Safe_Last_Attribute |
           A_Scale_Attribute |
           A_Scaling_Attribute |
           A_Signed_Zeros_Attribute |
           A_Size_Attribute |
           A_Small_Attribute |
           A_Storage_Pool_Attribute |
           A_Storage_Size_Attribute |
           A_Stream_Size_Attribute |
           A_Succ_Attribute |
           A_Tag_Attribute |
           A_Terminated_Attribute |
           A_Truncation_Attribute |
           An_Unbiased_Rounding_Attribute |
           An_Unchecked_Access_Attribute |
           A_Val_Attribute |
           A_Valid_Attribute |
           A_Value_Attribute |
           A_Version_Attribute |
           A_Wide_Image_Attribute |
           A_Wide_Value_Attribute |
           A_Wide_Wide_Image_Attribute |
           A_Wide_Wide_Value_Attribute |
           A_Wide_Wide_Width_Attribute |
           A_Wide_Width_Attribute |
           A_Width_Attribute |
           An_Output_Attribute |
           A_Write_Attribute =>

            Simple_Attribute_Reference (Resolver, Element);

         when others =>
            raise Internal_Error;
      end case;
   end Attribute_Reference;

   --------------------
   -- Check_Implicit --
   --------------------

   procedure Check_Implicit
     (Resolver : in out Down_Resolver;
      Element  : in out Asis.Element;
      Control  : in out Traverse_Control)
   is
      Down   : Down_Interpretation;
   begin
      D.Pop (Resolver.Stack, Down);
      if Down.Kind = An_Expression then
         Check_Implicit (Resolver.Implicit, Resolver.Store, Element, Down);
      elsif Down.Kind = A_Skip then
         Control := Abandon_Children;
         return;
      end if;
      D.Push (Resolver.Stack, Down);
   end Check_Implicit;

   --------------------------
   -- Explicit_Dereference --
   --------------------------

   procedure Explicit_Dereference
     (Resolver : in out Down_Resolver;
      Element  : in     Asis.Element)
   is
      use Asis.Gela.Errors;

      Set    : Stored_Set;
      Item   : Stored_Interpretation;
      Down   : Down_Interpretation;
      Next   : Down_Interpretation;
      Found  : Boolean := False;

   begin

      Get (Resolver.Store, Element, Set);
      D.Pop (Resolver.Stack, Down);

      for I in 1 .. Length (Set) loop
         Get (Set, I, Item);

         if (Down.Kind = A_Subprogram_Reference and then
               Item.Kind = A_Subprogram_Reference and then
               Is_Equal (Item.Result_Type, Down.Access_Type))
           or else
           (Down.Kind = An_Expression and then
              Item.Kind /= A_Subprogram_Reference and then
              (Is_Expected_Type (Down.Expression_Type, Item.Result_Type) or
               Is_Expected_Type (Item.Result_Type, Down.Expression_Type)))
         then

            if Found then
               Report (Element, Error_Ambiguous_Interprentation);
            else
               Found := True;
               Next := To_Down_Interpretation (Item.Down);
            end if;

            if Down.Kind = An_Expression then
               Set_Expression_Type (Element, Down.Expression_Type);
            end if;
         elsif Down.Kind /= An_Expression and
           Down.Kind /= A_Subprogram_Reference
         then

            raise Internal_Error;

         end if;

      end loop;

      if not Found then
         Report (Element, Error_No_Interprentation);
      end if;

      D.Push (Resolver.Stack, Next);
      Destroy (Set);

   end Explicit_Dereference;

   -------------------------------
   -- First_Attribute_Reference --
   -------------------------------

   procedure First_Attribute_Reference
     (Resolver : in out Down_Resolver;
      Element  : in     Asis.Element)
   is
      use Asis.Gela.Errors;
      use Asis.Expressions;

      Store  : Stored_Set;
      Stored : Stored_Interpretation;
      Down   : Down_Interpretation;
      Tipe   : Type_Info;
      List   : constant Asis.Element_List :=
        Attribute_Designator_Expressions (Element);
   begin
      Get (Resolver.Store, Element, Store);
      D.Pop (Resolver.Stack, Down);

      if Down.Kind = An_Expression then
         Set_Expression_Type (Element, Down.Expression_Type);
         Tipe := Down.Expression_Type;
      elsif Down.Kind = A_Range then
         Tipe := Down.Range_Type;
      else
         raise Internal_Error;
      end if;

      for I in reverse 1 .. List'Length loop
         Get (Store, I, Stored);
         Down := To_Down_Interpretation (Stored.Down);
         D.Push (Resolver.Stack, Down);
      end loop;

      Get (Store, List'Length + 1, Stored);
      Down := To_Down_Interpretation (Stored.Down);

      D.Push (Resolver.Stack, (Kind => A_Skip));
      D.Push (Resolver.Stack, Down);
      Destroy (Store);
   end First_Attribute_Reference;

   -------------------
   -- Function_Call --
   -------------------

   procedure Function_Call
     (Resolver : in out Down_Resolver;
      Element  : in out Asis.Element)
   is
      use Asis.Gela.Errors;

      Down    : Down_Interpretation;
      Store   : Stored_Set;
      Stored  : Stored_Interpretation;
      Name    : Stored_Interpretation;
      Result  : Type_Info;
      Found   : Natural := 0;
      Success : Boolean;
      Formal  : List_Index;
      Params  : Asis.Association_List := Get_Call_Parameters (Element);

   begin  --  Down_Function_Call
      D.Pop (Resolver.Stack, Down);
      Get (Resolver.Store, Element, Store);

      if Down.Kind = An_Expression then
         Result := Down.Expression_Type;
         Set_Expression_Type (Element, Down.Expression_Type);
      end if;

      if Down.Kind = A_Procedure_Call then
         for I in 1 .. Length (Store) loop
            Get (Store, I, Stored);

            if Stored.Kind = A_Procedure_Call then
               Found := Found + 1;

               if Found = 1 then
                  Name := Stored;
               end if;
            end if;
         end loop;
      elsif Down.Kind = A_Family_Member then
         Name.Kind := A_Family;
         Found := 1;
      elsif Down.Kind = An_Expression then
         declare
            Names : Up_Interpretation_Set := Create;
            Next  : Up_Interpretation;
         begin
            for I in 1 .. Length (Store) loop
               Get (Store, I, Stored);

               if Stored.Kind /= A_Procedure_Call
                 and then Is_Expected_Type (Stored.Result_Type, Result)
               then
                  Add (Names, Up_Expression (Stored.Result_Type));
               end if;
            end loop;

            Select_Prefered (Names);

            for J in 1 .. Length (Names) loop
               Get (Names, J, Next);

               for I in 1 .. Length (Store) loop
                  Get (Store, I, Stored);

                  if Stored.Kind /= A_Procedure_Call
                    and then Is_Equal (Stored.Result_Type,
                                       Next.Expression_Type)
                  then
                     Found := Found + 1;

                     if Found = 1 then
                        Name := Stored;
                     end if;
                  end if;
               end loop;
            end loop;

            Destroy (Names);
         end;
      end if;

      if Found = 0 then
         Report (Element, Error_No_Interprentation);
      else
         if Found > 1 then
            Report (Element, Error_Ambiguous_Interprentation);
         end if;

         case Name.Kind is
            when An_Array =>
               Push_Array_Indexes (Resolver, Name.Down.Expression_Type);
               D.Push (Resolver.Stack,
                 Up_Expression (Name.Down.Expression_Type));
               R.Function_To_Indexed_Component (Element);
            when A_Slice =>
               Push_Array_Indexes (Resolver, Name.Down.Expression_Type);
               D.Push (Resolver.Stack,
                       Up_Expression (Name.Down.Expression_Type));
               R.Function_To_Slice (Element);
            when A_Family =>
               declare
                  use Asis.Declarations;
                  Tipe  : Type_Info := Type_From_Discrete_Def
                    (Entry_Family_Definition (Down.Declaration), Element);
               begin
                  D.Push (Resolver.Stack, Up_Expression (Tipe));
                  D.Push (Resolver.Stack,
                          (A_Declaration, Down.Declaration));
                  if Element_Kind (Element) = A_Statement then
                     R.Procedure_To_Indexed_Entry_Call (Element);
                  else
                     R.Function_To_Indexed_Component (Element);
                  end if;
               end;
            when A_Function_Call | A_Procedure_Call =>
               declare
                  Tipe    : Type_Info;
                  Profile : Asis.Parameter_Specification_List :=
                              Get_Profile (Name.Down);
               begin
                  for Index in reverse Params'Range loop
                     Find_Formal_Index
                       (Params, Index, Profile, Formal, Success);

                     if not Success then
                        raise Internal_Error;
                     end if;

                     if Name.Real_Types = null
                       or else Is_Not_Type (Name.Real_Types (Formal))
                     then
                        Tipe := Get_Parameter_Type
                          (Name.Down, Profile, Formal, Element);
                     else
                        Tipe := Name.Real_Types (Formal);
                     end if;

                     Down := (An_Expression, Tipe);
                     D.Push (Resolver.Stack, Down);

                     if not Is_Nil (Get_Formal_Parameter (Params, Index)) then
                        Down := (A_Declaration, Profile (Formal));
                        D.Push (Resolver.Stack, Down);
                     end if;
                  end loop;

                  Down := To_Down_Interpretation (Name.Down);
                  D.Push (Resolver.Stack, Down);

                  if (Down.Kind = A_Declaration or Down.Kind = A_Family_Member)
                    and then Declaration_Kind (Down.Declaration) in
                    An_Entry_Declaration .. An_Entry_Body_Declaration
                  then
                     Replace.Procedure_To_Entry_Call (Element);
                  end if;
               end;
            when A_Type_Conversion =>
               Down := To_Down_Interpretation (Name.Down);
               D.Push (Resolver.Stack, Down);
               D.Push (Resolver.Stack, (Kind => A_Skip));
               R.Function_To_Type_Conversion (Element);
            when others =>
               raise Internal_Error;
         end case;

         Set_Expression_Type (Element, Result);
      end if;

      Destroy (Store);
   end Function_Call;

   --------------------------------
   -- Length_Attribute_Reference --
   --------------------------------

   procedure Length_Attribute_Reference
     (Resolver : in out Down_Resolver;
      Element  : in     Asis.Element)
   is
      use Asis.Gela.Errors;
      use Asis.Expressions;

      Store  : Stored_Set;
      Stored : Stored_Interpretation;
      Down   : Down_Interpretation;
      List   : constant Asis.Element_List :=
        Attribute_Designator_Expressions (Element);
   begin
      Get (Resolver.Store, Element, Store);
      D.Pop (Resolver.Stack, Down);

      if Down.Kind /= An_Expression then
         raise Internal_Error;
      end if;

      Set_Expression_Type (Element, XASIS.Types.Universal_Integer);

      for I in reverse 1 .. List'Length loop
         Get (Store, I, Stored);
         Down := To_Down_Interpretation (Stored.Down);
         D.Push (Resolver.Stack, Down);
      end loop;

      Get (Store, List'Length + 1, Stored);
      Down := To_Down_Interpretation (Stored.Down);

      D.Push (Resolver.Stack, (Kind => A_Skip));
      D.Push (Resolver.Stack, Down);
      Destroy (Store);
   end Length_Attribute_Reference;

   ----------------
   -- Membership --
   ----------------

   procedure Membership
     (Resolver : in out Down_Resolver;
      Element  : in out Asis.Element)
   is
      Store  : Stored_Set;
      Stored : Stored_Interpretation;
      Down   : Down_Interpretation;
      Kind   : Asis.Expression_Kinds := Expression_Kind (Element);
   begin
      Get (Resolver.Store, Element, Store);
      D.Pop (Resolver.Stack, Down);

      if Length (Store) /= 1 then
         raise Internal_Error;
      end if;

      Get (Store, 1, Stored);

      if Kind in An_In_Range_Membership_Test .. A_Not_In_Range_Membership_Test
      then
         Down := To_Down_Interpretation (Stored.Down);
      else
         Down := (Kind => A_Skip);
      end if;

      D.Push (Resolver.Stack, Down);

      Down := Up_Expression (Stored.Result_Type);
      D.Push (Resolver.Stack, Down);

      Set_Expression_Type (Element, XASIS.Types.Boolean);

      Destroy (Store);
   end Membership;

   ------------------------
   -- Push_Array_Indexes --
   ------------------------

   procedure Push_Array_Indexes
     (Resolver : in out Down_Resolver;
      Tipe     : in     Type_Info)
   is
      Index : Type_Info;
   begin
      for I in reverse 1 .. Array_Dimention (Tipe) loop
         Index := Get_Array_Index_Type (Tipe, I);
         D.Push (Resolver.Stack, Up_Expression (Index));
      end loop;
   end Push_Array_Indexes;

   --------------------------
   -- Qualified_Expression --
   --------------------------

   procedure Qualified_Expression
     (Resolver : in out Down_Resolver;
      Element  : in out Asis.Element)
   is
      Down    : Down_Interpretation;
      Store   : Stored_Set;
      Stored  : Stored_Interpretation;
   begin
      D.Pop (Resolver.Stack, Down);

      if Down.Kind = An_Expression then
         Set_Expression_Type (Element, Down.Expression_Type);
      end if;

      Get (Resolver.Store, Element, Store);

      if Length (Store) /= 1 then
         raise Internal_Error;
      end if;

      Get (Store, 1, Stored);

      if Stored.Kind = An_Array then
         D.Push (Resolver.Stack, Up_Expression (Stored.Result_Type));
      else
         D.Push (Resolver.Stack, To_Down_Interpretation (Stored.Down));
      end if;

      D.Push (Resolver.Stack, (Kind => A_Skip));
      Destroy (Store);
   end Qualified_Expression;

   ------------------------
   -- Selected_Component --
   ------------------------

   procedure Selected_Component
     (Resolver : in out Down_Resolver;
      Element  : in     Asis.Element)
   is
      use Asis.Gela.Errors;

      Down    : Down_Interpretation;
      Next    : Down_Interpretation;
      Store   : Stored_Set;
      Stored  : Stored_Interpretation;
      Found   : Boolean := False;
   begin
      D.Pop (Resolver.Stack, Down);
      if Is_Expanded_Name (Element) then
         D.Push (Resolver.Stack, Down);
         D.Push (Resolver.Stack, (Kind => A_Skip));
         return;
      end if;

      Get (Resolver.Store, Element, Store);

      for I in 1 .. Length (Store) loop
         Get (Store, I, Stored);

         case Stored.Kind is

            when A_Component =>
               if Down.Kind = An_Expression and then
                 Is_Expected_Type (Stored.Result_Type, Down.Expression_Type)
               then

                  if Found then
                     Report (Element, Error_Ambiguous_Interprentation);
                  else
                     Next := (A_Declaration, Stored.Component);
                     D.Push (Resolver.Stack, Next);
                     Next := To_Down_Interpretation (Stored.Down);
                     D.Push (Resolver.Stack, Next);
                     Found := True;
                     Set_Expression_Type (Element, Down.Expression_Type);
                  end if;

               end if;

            when A_Function_Call =>
               if Down.Kind = A_Declaration then
--                 Is_Equal (Stored.Result_Type, Down.Declaration) then

                  if Found then
                     Report (Element, Error_Ambiguous_Interprentation);
                  else
                     D.Push (Resolver.Stack, Down);
                     Next := To_Down_Interpretation (Stored.Down);
                     D.Push (Resolver.Stack, Next);
                     Found := True;
                  end if;

               end if;

            when A_Subprogram_Reference =>
               if Down.Kind = A_Prefixed_View and then
                 Is_Equal (Stored.Component, Down.Declaration)
               then

                  if Found then
                     Report (Element, Error_Ambiguous_Interprentation);
                  else
                     Next := (A_Declaration, Stored.Component);
                     D.Push (Resolver.Stack, Next);
                     Next := To_Down_Interpretation (Stored.Down);
                     D.Push (Resolver.Stack, Next);
                     Found := True;
                  end if;

               end if;

            when others =>
               raise Internal_Error;
         end case;
      end loop;
      Destroy (Store);
   end Selected_Component;

   -------------------------
   -- Set_Expression_Type --
   -------------------------

   procedure Set_Expression_Type
     (Element : Asis.Expression;
      Tipe    : Type_Info)
   is
      Decl : Asis.Declaration := Get_Declaration (Tipe);
   begin
      --  if Is_Declaration (Tipe) and not Is_Anonymous_Access (Tipe)
      if not Is_Nil (Decl) then
         Set_Expression_Type (Element, Decl);
      end if;
   end Set_Expression_Type;

   -------------------------
   -- Set_Expression_Type --
   -------------------------

   procedure Set_Expression_Type
     (Element : Asis.Expression;
      Tipe    : Asis.Element)
   is
      use Asis.Elements;
      use Asis.Gela.Elements;
   begin
      case Element_Kind (Tipe) is
         when A_Declaration =>
            Set_Corresponding_Expression_Type
              (Expression_Node'Class (Element.all), Tipe);
         when others =>
            raise Internal_Error;
      end case;
   end Set_Expression_Type;

   --------------------------------
   -- Simple_Attribute_Reference --
   --------------------------------

   procedure Simple_Attribute_Reference
     (Resolver : in out Down_Resolver;
      Element  : in     Asis.Element)
   is
      use Asis.Gela.Errors;
      use Asis.Expressions;

      Store  : Stored_Set;
      Stored : Stored_Interpretation;
      Down   : Down_Interpretation;
   begin
      Get (Resolver.Store, Element, Store);
      D.Pop (Resolver.Stack, Down);

      if Down.Kind = An_Expression then
         Set_Expression_Type (Element, Down.Expression_Type);
      elsif Down.Kind /= A_Declaration and Down.Kind /= An_Attribute_Function
      then
         raise Internal_Error;
      end if;

      if Length (Store) = 1 then
         Get (Store, 1, Stored);
         Down := To_Down_Interpretation (Stored.Down);
      else
         raise Internal_Error;
      end if;

      D.Push (Resolver.Stack, (Kind => A_Skip));
      D.Push (Resolver.Stack, Down);
      Destroy (Store);
   end Simple_Attribute_Reference;

end Asis.Gela.Overloads.Walk.Down;



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
