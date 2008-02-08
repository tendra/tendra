with Asis.Elements;
with Asis.Gela.Errors;
with Asis.Statements;
with Asis.Expressions;
with Asis.Definitions;
with Asis.Declarations;
with Asis.Gela.Classes;
with Asis.Gela.Visibility;
with XASIS.Utils;
with XASIS.Types;

with Ada.Wide_Text_IO;
package body Asis.Gela.Overloads.Walk.Up is

   use Asis.Elements;
   use Asis.Gela.Classes;

   function Check_Array_Aggregate
     (Params  : Asis.Association_List) return Boolean;

   function Check_Type_Conversion (Name : Up_Interpretation) return Boolean;

   function Get_Array_Element_Type
     (Tipe : Type_Info) return Up_Interpretation;

   function Find_Task_Visible_Item
     (Definition : Asis.Definition;
      Name       : Program_Text) return Asis.Declaration;

   procedure Attribute_Reference_Value
     (Resolver : in out Up_Resolver;
      Element  : in     Asis.Element;
      Tipe     : in     Asis.Declaration);

   procedure Attribute_Reference_Value
     (Resolver : in out Up_Resolver;
      Element  : in     Asis.Element;
      Tipe     : in     Asis.Declaration;
      Store    : in out Stored_Set);

   procedure Attribute_Reference_Function
     (Resolver : in out Up_Resolver;
      Element  : in     Asis.Element);

   procedure Access_Attribute_Reference
     (Resolver  : in out Up_Resolver;
      Element   : in     Asis.Element;
      Unchecked : in     Boolean := False);

   procedure Class_Attribute
     (Resolver : in out Up_Resolver;
      Element  : in     Asis.Element);

   procedure Identity_Attribute_Reference
     (Resolver : in out Up_Resolver;
      Element  : in     Asis.Element);

   procedure First_Attribute_Reference
     (Resolver : in out Up_Resolver;
      Element  : in     Asis.Element;
      Store    : in out Stored_Set;
      Is_Range : in     Boolean := False);

   function Allow_Implicit_Dereference (Element : Asis.Element) return Boolean;
   function Allow_Parameterless_Call (Element : Asis.Element) return Boolean;

   function Get_Call_Prefix (Element : Asis.Element )
     return Asis.Element;

   function Subprograms_Of_Ancestor
     (Tipe   : Type_Info;
      Target : Type_Info;
      Ident  : Asis.Identifier) return Asis.Defining_Name_List;

   function Subprograms_Of_Ancestors
     (Ancestors   : Asis.Name_List;
      Target      : Type_Info;
      Ident       : Asis.Identifier) return Asis.Defining_Name_List;

   --------------------------------
   -- Access_Attribute_Reference --
   --------------------------------

   procedure Access_Attribute_Reference
     (Resolver  : in out Up_Resolver;
      Element   : in     Asis.Element;
      Unchecked : in     Boolean := False)
   is
      Prefix : Up_Interpretation_Set;
      Item   : Up_Interpretation;
      Result : Up_Interpretation_Set := Create;
      Store  : Stored_Set := Create;
      Stored : Stored_Interpretation;
   begin
      U.Pop (Resolver.Stack, Prefix);
      Resolve_Identifier (Prefix);

      if Length (Prefix) > 0 then
         Get (Prefix, 1, Item);
      end if;

      if Length (Prefix) > 0 and then
        not Unchecked and then
        Item.Kind = A_Declaration and then
        Is_Subprogram (Item.Declaration)
      then  --  Subprogram access
         for I in 1 .. Length (Prefix) loop
            Get (Prefix, I, Item);

            if Item.Kind = A_Declaration and then
               Is_Subprogram (Item.Declaration)
            then
               Stored.Down := Item;
               Add (Store, Stored);
               Item := (Kind    => A_Subprogram_Access,
                        Profile => Item.Declaration);
               Add (Result, Item);
            end if;
         end loop;
      elsif Has_Interpretation (Prefix, Element) then
         Stored.Down := Item;
         Add (Store, Stored);
         Item := (Kind => A_General_Access);
         Add (Result, Item);
      end if;

      Destroy (Prefix);
      U.Push (Resolver.Stack, Result);
      Put (Resolver.Store, Element, Store);
   end Access_Attribute_Reference;

   ---------------
   -- Aggregate --
   ---------------

   procedure Aggregate
     (Resolver  : in out Up_Resolver;
      Element   : in     Asis.Element;
      Extension : in     Boolean := False)
   is
      use Asis.Expressions;

      Set    : Up_Interpretation_Set;
      Store  : Stored_Set;
      Stored : Stored_Interpretation;
      Result : Up_Interpretation_Set := Create;
      Item   : Up_Interpretation;
      Expr   : Asis.Element;
      List   : constant Asis.Association_List
        := Record_Component_Associations (Element);
   begin
      for I in reverse List'Range loop
         U.Pop (Resolver.Stack, Set);
         Expand_Expression (Set, Resolver.Implicit,
           Component_Expression (List (I)));
         Destroy (Set);
      end loop;

      if Could_Be_Record_Aggregate (Element, Extension) then
         if Extension then
            Expr := Extension_Aggregate_Expression (Element);
            Store := Create;
            U.Pop (Resolver.Stack, Set);
            if Is_Subtype_Mark (Expr) then
               Resolve_Identifier (Set);
               if Has_Interpretation (Set, Expr) then
                  Get (Set, 1, Stored.Down);
                  Add (Store, Stored);
               end if;
            else
               Constrain_To_Tagged_Non_Limited_Types
                 (Set, Resolver.Implicit, Expr);
               if Has_Interpretation (Set, Element) then
                  Get (Set, 1, Stored.Down);
                  Add (Store, Stored);
               end if;
            end if;

            Put (Resolver.Store, Element, Store);
            Destroy (Set);
            Item := (Kind => An_Extension_Aggregate);
         else
            Item := (Kind => A_Record_Aggregate);
         end if;

         Add (Result, Item);
      end if;

      if not Extension and then
        (Could_Be_Positional_Array_Aggregate (Element) or else
         Could_Be_Named_Array_Aggregate (Element))
      then
         Item := (Kind => An_Array_Aggregate);
         Add (Result, Item);
      end if;

      U.Push (Resolver.Stack, Result);
   end Aggregate;

   ----------------
   -- Allocation --
   ----------------

   procedure Allocation
     (Resolver  : in out Up_Resolver;
      Element   : in     Asis.Element;
      From_Expr : in     Boolean := False)
   is
      Set    : Up_Interpretation_Set;
      Result : Up_Interpretation_Set := Create;
      Item   : Up_Interpretation;
      Next   : Up_Interpretation;
      Ind    : Asis.Subtype_Indication;
   begin
      if From_Expr then
         U.Pop (Resolver.Stack, Set);
         Expand_Expression (Set, Resolver.Implicit, Element);
         if Has_Interpretation (Set, Element) then
            Get (Set, 1, Item);

            if Item.Kind = An_Expression then
               Next := (Kind        => An_Object_Access,
                        Object_Type => Item.Expression_Type);
               Add (Result, Next);
            end if;
         end if;
         Destroy (Set);
      else
         Ind := Asis.Expressions.Allocator_Subtype_Indication (Element);
         Item := (Kind        => An_Object_Access,
                  Object_Type => Type_From_Indication (Ind, Element));
         Add (Result, Item);
      end if;

      U.Push (Resolver.Stack, Result);
   end Allocation;

   --------------------------------
   -- Allow_Implicit_Dereference --
   --------------------------------

   function Allow_Implicit_Dereference (Element : Asis.Element) return Boolean
   is
   begin
      case Attribute_Kind (Element) is
         when
           A_Callable_Attribute |
           A_Component_Size_Attribute |
           A_Constrained_Attribute |
           A_First_Attribute |
           An_Identity_Attribute |
           A_Last_Attribute |
           A_Length_Attribute |
           A_Range_Attribute |
           A_Storage_Size_Attribute |
           A_Tag_Attribute |
           A_Terminated_Attribute |
           A_Valid_Attribute =>

            return True;
         when others =>
            return False;
      end case;
   end Allow_Implicit_Dereference;

   ------------------------------
   -- Allow_Parameterless_Call --
   ------------------------------

   function Allow_Parameterless_Call (Element : Asis.Element) return Boolean
   is
   begin
      case Attribute_Kind (Element) is
         when An_Access_Attribute |
           An_Address_Attribute |
           A_Body_Version_Attribute |
           A_Partition_ID_Attribute |
           A_Version_Attribute =>
            return False;
         when others =>
            return True;
      end case;
   end Allow_Parameterless_Call;

   ----------------
   -- Assignment --
   ----------------

   procedure Assignment
     (Resolver  : in out Up_Resolver;
      Element   : in     Asis.Element)
   is
      use Asis.Statements;

      Result     : Up_Interpretation_Set := Create;
      Left       : Up_Interpretation_Set;
      Right      : Up_Interpretation_Set;
      Left_Item  : Up_Interpretation;
   begin
      U.Pop (Resolver.Stack, Right);
      U.Pop (Resolver.Stack, Left);

      Expand_Expression (Right, Resolver.Implicit,
        Assignment_Expression (Element));

      Constrain_To_Non_Limited_Types (Left, Resolver.Implicit,
        Assignment_Variable_Name (Element));

      for I in 1 .. Length (Left) loop
         Get (Left, I, Left_Item);
         if Left_Item.Kind = An_Expression and then
            Has_Type (Right, Left_Item.Expression_Type) then
            Add (Result, Left_Item);
         end if;
      end loop;
      U.Push (Resolver.Stack, Result);
      Destroy (Right);
      Destroy (Left);
   end Assignment;

   -------------------------
   -- Attribute_Reference --
   -------------------------

   procedure Attribute_Reference
     (Resolver : in out Up_Resolver;
      Element  : in     Asis.Element)
   is
      use Asis.Expressions;

      Kind   : constant Attribute_Kinds := Attribute_Kind (Element);
      Set    : Up_Interpretation_Set;
      Store  : Stored_Set;
      Stored : Stored_Interpretation;
   begin

      --  Attribute expressions
      if Kind = A_First_Attribute or
        Kind = A_Last_Attribute or
        Kind = A_Length_Attribute or
        Kind = A_Range_Attribute
      then
         declare
            List   : constant Asis.Element_List :=
              Attribute_Designator_Expressions (Element);
         begin
            Store := Create;
            for I in List'Range loop
               U.Pop (Resolver.Stack, Set);
               Constrain_To_Integer_Types (Set, Resolver.Implicit, List (I));
               if Has_Interpretation (Set, Element) then
                  Get (Set, 1, Stored.Down);
               else
                  Stored.Down := (Kind => A_Skip);
               end if;
               Add (Store, Stored);
               Destroy (Set);
            end loop;
         end;
      end if;

      --  Attribute identificator
      U.Pop (Resolver.Stack, Set);
      Destroy (Set);

      case Kind is
         when Not_An_Attribute =>
            raise Internal_Error;

         when An_Access_Attribute =>
            Access_Attribute_Reference (Resolver, Element);

         when An_Address_Attribute =>

            Attribute_Reference_Value
              (Resolver, Element, XASIS.Types.System_Address);

         when An_Adjacent_Attribute |
           A_Ceiling_Attribute |
           A_Compose_Attribute |
           A_Copy_Sign_Attribute |
           An_Exponent_Attribute |
           A_Floor_Attribute |
           A_Fraction_Attribute |
           An_Image_Attribute |
           An_Input_Attribute |
           A_Leading_Part_Attribute |
           A_Machine_Attribute |
           A_Machine_Rounding_Attribute |
           A_Max_Attribute |
           A_Min_Attribute |
           A_Mod_Attribute |
           A_Model_Attribute |
           A_Pos_Attribute |
           A_Pred_Attribute |
           A_Remainder_Attribute |
           A_Round_Attribute |
           A_Rounding_Attribute |
           A_Scaling_Attribute |
           A_Succ_Attribute |
           A_Truncation_Attribute |
           An_Unbiased_Rounding_Attribute |
           A_Val_Attribute |
           A_Value_Attribute |
           A_Wide_Image_Attribute |
           A_Wide_Value_Attribute |
           A_Wide_Wide_Image_Attribute |
           A_Wide_Wide_Value_Attribute |
           An_Output_Attribute |
           A_Read_Attribute |
           A_Write_Attribute =>

            Attribute_Reference_Function (Resolver, Element);

         when An_Aft_Attribute |
           An_Alignment_Attribute |
           A_Component_Size_Attribute |
           A_Count_Attribute |
           A_Digits_Attribute |
           A_First_Bit_Attribute |
           A_Fore_Attribute |
           A_Last_Bit_Attribute |
           A_Machine_Emax_Attribute |
           A_Machine_Emin_Attribute |
           A_Machine_Mantissa_Attribute |
           A_Machine_Radix_Attribute |
           A_Max_Size_In_Storage_Elements_Attribute |
           A_Model_Emin_Attribute |
           A_Model_Mantissa_Attribute |
           A_Modulus_Attribute |
           A_Partition_ID_Attribute |
           A_Position_Attribute |
           A_Scale_Attribute |
           A_Size_Attribute |
           A_Storage_Size_Attribute |
           A_Stream_Size_Attribute |
           A_Wide_Wide_Width_Attribute |
           A_Wide_Width_Attribute |
           A_Width_Attribute =>

            Attribute_Reference_Value
              (Resolver, Element, XASIS.Types.Universal_Integer);

         when A_Bit_Order_Attribute =>

            Attribute_Reference_Value
              (Resolver, Element, XASIS.Types.System_Bit_Order);

         when A_Body_Version_Attribute |
           An_External_Tag_Attribute |
           A_Version_Attribute =>

            Attribute_Reference_Value
              (Resolver, Element, XASIS.Types.String);

         when A_Callable_Attribute |
           A_Constrained_Attribute |
           A_Definite_Attribute |
           A_Denorm_Attribute |
           A_Machine_Overflows_Attribute |
           A_Machine_Rounds_Attribute |
           A_Signed_Zeros_Attribute |
           A_Terminated_Attribute |
           A_Valid_Attribute =>

            Attribute_Reference_Value
              (Resolver, Element, XASIS.Types.Boolean);

         when A_Caller_Attribute =>

            Attribute_Reference_Value
              (Resolver, Element, XASIS.Types.Task_Id);

         when A_Delta_Attribute |
           A_Model_Epsilon_Attribute |
           A_Model_Small_Attribute |
           A_Safe_First_Attribute |
           A_Safe_Last_Attribute |
           A_Small_Attribute =>

            Attribute_Reference_Value
              (Resolver, Element, XASIS.Types.Universal_Real);

         when A_Storage_Pool_Attribute =>

            Attribute_Reference_Value
              (Resolver, Element, XASIS.Types.Root_Storage_Pool);

         when A_Tag_Attribute =>

            Attribute_Reference_Value
              (Resolver, Element, XASIS.Types.Tag);

         when A_Class_Attribute =>
            Class_Attribute (Resolver, Element);

         when A_Base_Attribute =>

            null;  --  Ignore 'Base for overload resolution

         when An_Unchecked_Access_Attribute =>

            Access_Attribute_Reference (Resolver, Element, True);

         when An_Identity_Attribute =>
            Identity_Attribute_Reference (Resolver, Element);

         when A_Length_Attribute =>

            Attribute_Reference_Value
              (Resolver, Element, XASIS.Types.Universal_Integer, Store);

         when A_First_Attribute |
           A_Last_Attribute =>

            First_Attribute_Reference (Resolver, Element, Store);

         when A_Range_Attribute =>

            First_Attribute_Reference (Resolver, Element, Store, True);

         when A_Priority_Attribute =>
            Attribute_Reference_Value (Resolver, Element, XASIS.Types.Integer);

         when others =>
            raise Unimplemented;
      end case;

   end Attribute_Reference;

   ----------------------------------
   -- Attribute_Reference_Function --
   ----------------------------------

   procedure Attribute_Reference_Function
     (Resolver : in out Up_Resolver;
      Element  : in     Asis.Element)
   is
      Kind   : constant Attribute_Kinds := Attribute_Kind (Element);
      Set    : Up_Interpretation_Set;
      Result : Up_Interpretation_Set := Create;
      Store  : Stored_Set := Create;
      Stored : Stored_Interpretation;
   begin
      --  Attribute prefix
      U.Pop (Resolver.Stack, Set);
      Resolve_Identifier (Set);

      if Has_Interpretation (Set, Element) then
         Get (Set, 1, Stored.Down);

         if Stored.Down.Kind = A_Declaration then
            Add (Result, (Kind       => An_Attribute_Function,
                          Prefix     => Stored.Down.Declaration,
                          Attr_Kind  => Kind,
                          Class_Wide => False));
            Add (Store, Stored);
         elsif Stored.Down.Kind = A_Type then
            Add (Result,
                 (Kind       => An_Attribute_Function,
                  Prefix     => Get_Declaration (Stored.Down.Type_Info),
                  Attr_Kind  => Kind,
                  Class_Wide => Is_Class_Wide (Stored.Down.Type_Info)));
            Add (Store, Stored);
         end if;
      end if;

      Destroy (Set);
      U.Push (Resolver.Stack, Result);
      Put (Resolver.Store, Element, Store);
   end Attribute_Reference_Function;

   -------------------------------
   -- Attribute_Reference_Value --
   -------------------------------

   procedure Attribute_Reference_Value
     (Resolver : in out Up_Resolver;
      Element  : in     Asis.Element;
      Tipe     : in     Asis.Declaration)
   is
      Store  : Stored_Set := Create;
   begin
      Attribute_Reference_Value (Resolver, Element, Tipe, Store);
   end Attribute_Reference_Value;

   -------------------------------
   -- Attribute_Reference_Value --
   -------------------------------

   procedure Attribute_Reference_Value
     (Resolver : in out Up_Resolver;
      Element  : in     Asis.Element;
      Tipe     : in     Asis.Declaration;
      Store    : in out Stored_Set)
   is
      Set    : Up_Interpretation_Set;
      Result : Up_Interpretation_Set := Create;
      Stored : Stored_Interpretation;
   begin
      --  Attribute prefix
      U.Pop (Resolver.Stack, Set);
      if not Allow_Parameterless_Call (Element) then
         Resolve_Identifier (Set);
      else
         Expand_Attribute_Prefix (Set, Resolver.Implicit,
           Asis.Expressions.Prefix (Element),
           Allow_Implicit_Dereference (Element));
      end if;

      if Has_Interpretation (Set, Element) then
         Get (Set, 1, Stored.Down);
         Add (Result, Up_Expression (Tipe, Element));
         Add (Store, Stored);
      end if;

      Destroy (Set);
      U.Push (Resolver.Stack, Result);
      Put (Resolver.Store, Element, Store);
   end Attribute_Reference_Value;

   ---------------------------
   -- Check_Array_Aggregate --
   ---------------------------

   function Check_Array_Aggregate
     (Params  : Asis.Association_List) return Boolean is
   begin
      for I in Params'Range loop
         if not Is_Nil (Get_Formal_Parameter (Params, I)) then
            return False;
         end if;
      end loop;
      return Params'Length > 0;
   end Check_Array_Aggregate;

   ------------------
   -- Check_Family --
   ------------------

   function Check_Family (Name : Up_Interpretation) return Boolean is
   begin
      return Name.Kind = A_Declaration and then
        XASIS.Utils.Is_Entry_Family (Name.Declaration);
   end Check_Family;

   ---------------------------
   -- Check_Type_Conversion --
   ---------------------------

   function Check_Type_Conversion (Name : Up_Interpretation) return Boolean is
   begin
      if Name.Kind = A_Type then
         return True;
      elsif Name.Kind /= A_Declaration or else
        not Is_Type_Declaration (Name.Declaration)
      then
         return False;
      end if;
      return True;
   end Check_Type_Conversion;

   ---------------------
   -- Class_Attribute --
   ---------------------

   procedure Class_Attribute
     (Resolver : in out Up_Resolver;
      Element  : in     Asis.Element)
   is
      Set    : Up_Interpretation_Set;
      Item   : Up_Interpretation;
      Result : Up_Interpretation_Set := Create;
      Store  : Stored_Set := Create;
      Stored : Stored_Interpretation;
      Tipe   : Type_Info;
   begin
      --  Attribute prefix
      U.Pop (Resolver.Stack, Set);
      Resolve_Identifier (Set);

      for I in 1 .. Length (Set) loop
         Get (Set, I, Item);

         if Item.Kind = A_Declaration then
            Tipe := Type_From_Declaration (Item.Declaration, Element);
            Set_Class_Wide (Tipe);
            Add (Result, (A_Type, Tipe));
            Stored.Down := Item;
            Stored.Result_Type := Tipe;
            Add (Store, Stored);
         end if;
      end loop;

      U.Push (Resolver.Stack, Result);
      Put (Resolver.Store, Element, Store);
      Destroy (Set);
   end Class_Attribute;

   --------------------------
   -- Explicit_Dereference --
   --------------------------

   procedure Explicit_Dereference
     (Resolver : in out Up_Resolver;
      Element  : in     Asis.Element)
   is
      Set    : Up_Interpretation_Set;
      Store  : Stored_Set := Create;
      Stored : Stored_Interpretation;
      Result : Up_Interpretation_Set := Create;
      Item   : Up_Interpretation;
   begin
      U.Pop (Resolver.Stack, Set);
      Constrain_To_Access_Types (Set, Resolver.Implicit,
        Asis.Expressions.Prefix (Element));

      for I in 1 .. Length (Set) loop
         Get (Set, I, Item);
         Stored.Down := Item;

         if Item.Kind /= An_Expression then
            raise Internal_Error;
         end if;

         Item := Dereference (Item.Expression_Type);

         case Item.Kind is
            when A_Subprogram_Reference =>
               Stored.Kind        := A_Subprogram_Reference;
               Stored.Result_Type := Item.Access_Type;
            when An_Expression =>
               Stored.Kind := A_Function_Call;
               Stored.Result_Type := Item.Expression_Type;
            when others =>
               raise Internal_Error;
         end case;

         Add (Store, Stored);
         Add (Result, Item);
      end loop;
      U.Push (Resolver.Stack, Result);
      Put (Resolver.Store, Element, Store);
      Destroy (Set);
   end Explicit_Dereference;

   ----------------------------
   -- Find_Task_Visible_Item --
   ----------------------------

   function Find_Task_Visible_Item
     (Definition : Asis.Definition;
      Name       : Program_Text) return Asis.Declaration
   is
      use Asis.Definitions;
      List     : constant Asis.Declarative_Item_List :=
        Visible_Part_Items (Definition);
      Def_Name : Asis.Defining_Name;
   begin
      for I in List'Range loop
         Def_Name := XASIS.Utils.Get_Defining_Name (List (I), Name);
         if Assigned (Def_Name) then
            return List (I);
         end if;
      end loop;
      return Nil_Element;
   end Find_Task_Visible_Item;

   -------------------------------
   -- First_Attribute_Reference --
   -------------------------------

   procedure First_Attribute_Reference
     (Resolver : in out Up_Resolver;
      Element  : in     Asis.Element;
      Store    : in out Stored_Set;
      Is_Range : in     Boolean := False)
   is
      use Asis.Gela.Errors;
      use Asis.Expressions;

      N      : constant List_Index := 1;
      Tipe   : Type_Info;
      Set    : Up_Interpretation_Set;
      Item   : Up_Interpretation;
      Result : Up_Interpretation_Set := Create;
      Stored : Stored_Interpretation;
      List   : constant Asis.Element_List :=
        Attribute_Designator_Expressions (Element);
   begin
      --  Attribute prefix
      U.Pop (Resolver.Stack, Set);
      Expand_Attribute_Prefix (Set, Resolver.Implicit,
        Asis.Expressions.Prefix (Element));
      Stored.Down := (Kind => A_Skip);

      for I in 1 .. Length (Set) loop
         Get (Set, I, Item);

         if Item.Kind = A_Declaration then
            Tipe := Type_From_Declaration (Item.Declaration, Element);
         end if;

         if (Item.Kind = An_Expression and then
               Is_Array (Item.Expression_Type)) or
           (Item.Kind = A_Declaration and then Is_Array (Tipe))
         then
            if List'Length = 1 then
               null; --  FIXME N := Calculate (List (1));
            end if;

            if Item.Kind = An_Expression then
               Tipe := Get_Array_Index_Type (Item.Expression_Type, N);
            else
               Tipe := Get_Array_Index_Type (Tipe, N);
            end if;

            if Is_Range then
               Add (Result, (A_Range, Tipe));
            else
               Add (Result, Up_Expression (Tipe));
            end if;

            Stored.Down := Item;

         elsif Item.Kind = A_Declaration and then Is_Scalar (Tipe) then
            if List'Length /= 0 then
               Report (Element, Error_Syntax_Index_Exists);
            end if;

            if Is_Range then
               Add (Result, (A_Range, Tipe));
            else
               Add (Result, Up_Expression (Tipe));
            end if;

            Stored.Down := Item;
         end if;
      end loop;

      Add (Store, Stored);
      Destroy (Set);
      U.Push (Resolver.Stack, Result);
      Put (Resolver.Store, Element, Store);
   end First_Attribute_Reference;

   -------------------
   -- Function_Call --
   -------------------

   procedure Function_Call
     (Resolver : in out Up_Resolver;
      Element  : in     Asis.Element)
   is

      function Check_Parameter
        (Profile : Asis.Parameter_Specification_List;
         Index   : List_Index := 1;
         Set     : Up_Interpretation_Set)
         return Boolean;

      function Check_Parameters
        (Profile : in     Asis.Parameter_Specification_List;
         Index   : in     List_Index := 1) return Boolean;

      function Check_Defaults
        (Profile : in     Asis.Parameter_Specification_List) return Boolean;

      Result : Up_Interpretation_Set := Create;
      Store  : Stored_Set := Create;
      Stored : Stored_Interpretation;
      Name   : Up_Interpretation;
      Tipe   : Up_Interpretation;
      Names  : Up_Interpretation_Set;
      Params : constant Asis.Association_List :=
         Get_Call_Parameters (Element);
      Sets   : Up_Interpretation_Set_Array (1 .. Params'Length);

      --------------------
      -- Check_Defaults --
      --------------------

      function Check_Defaults
        (Profile : in     Asis.Parameter_Specification_List)
         return Boolean
      is
         use Asis.Declarations;
         Formal : List_Index;
         Found  : Boolean;
         Set    : array (Profile'Range) of Natural := (others => 0);
         Fake_Profile : Boolean := False;
      begin
         if Profile'Length >= 1
           and then not XASIS.Utils.Is_Parameter_Specification (Profile (1))
         then
            Fake_Profile := True;
         end if;

         for I in Params'Range loop
            Find_Formal_Index (Params, I, Profile, Formal, Found);

            if not Found then
               return False;
            end if;

            Set (Formal) := Set (Formal) + 1;
         end loop;

         for I in Set'Range loop
            if Set (I) < Asis.Declarations.Names (Profile (I))'Length
              and then (Fake_Profile
                        or else Is_Nil (Initialization_Expression
                                        (Profile (I))))
            then
               return False;
            end if;
         end loop;

         return True;
      end Check_Defaults;

      -----------------
      -- Check_Array --
      -----------------

      function Check_Array (Name : Up_Interpretation) return Boolean is
      begin
         if Name.Kind = An_Expression then
            return Is_Array (Name.Expression_Type, Params'Length);
         end if;
         return False;
      end Check_Array;

      ---------------------
      -- Check_Parameter --
      ---------------------

      function Check_Parameter
        (Profile : Asis.Parameter_Specification_List;
         Index   : List_Index := 1;
         Set     : Up_Interpretation_Set)
         return Boolean
      is
         Item : Up_Interpretation;
         Info : constant Type_Info :=
           Get_Parameter_Type (Name, Profile, Index, Element);
      begin
         if Has_Type (Set, Info) then

            if Is_Universal (Info) or Is_Class_Wide (Info) then
               Item := Get_Type (Set, Info);

               if Item.Kind = An_Expression then
                  if Stored.Real_Types = null then
                     Stored.Real_Types := new Type_Infos (Profile'Range);
                  end if;

                  Stored.Real_Types (Index) := Item.Expression_Type;
               end if;
            end if;

            return True;
         end if;

         return False;
      end Check_Parameter;

      ----------------------
      -- Check_Parameters --
      ----------------------

      function Check_Parameters
        (Profile : Asis.Parameter_Specification_List;
         Index   : List_Index := 1) return Boolean
      is
         Found  : Boolean;
         Formal : List_Index;
      begin
         if Index = 1 and then not Check_Defaults (Profile) then
            return False;
         end if;

         if Index > Params'Last then
            return True;
         end if;

         Find_Formal_Index (Params, Index, Profile, Formal, Found);

         if not Found then
            return False;
         end if;

         if Check_Parameter (Profile, Formal, Sets (Positive (Index))) then
            if Check_Parameters (Profile, Index + 1) then
               return True;
            end if;
         end if;

         return False;
      end Check_Parameters;

      -------------------------
      -- Check_Array_Indexes --
      -------------------------

      function Check_Array_Indexes return Boolean is
         Item  : Up_Interpretation;
         Tipe  : Type_Info;
         Found : Boolean;
      begin
         for J in Sets'Range loop
            Tipe  := Get_Array_Index_Type
              (Name.Expression_Type, Asis.List_Index (J));
            Found := False;

            for I in 1 .. Length (Sets (J)) loop
               Get (Sets (J), I, Item);

               if Item.Kind = An_Expression and then
                  Is_Expected_Type (Item.Expression_Type, Tipe)
               then
                  Found := True;
                  exit;
               end if;
            end loop;
            if not Found then
               return False;
            end if;
         end loop;
         return True;
      end Check_Array_Indexes;

      ------------------------
      -- Check_Family_Index --
      ------------------------

      function Check_Family_Index return Boolean is
         use Asis.Declarations;

         Tipe  : constant Type_Info := Type_From_Discrete_Def
           (Entry_Family_Definition (Name.Declaration), Element);
         Item  : Up_Interpretation;
      begin
         for I in 1 .. Length (Sets (1)) loop
            Get (Sets (1), I, Item);

            if Item.Kind = An_Expression
              and then Is_Expected_Type (Item.Expression_Type, Tipe)
            then
               return True;
            end if;
         end loop;

         return False;
      end Check_Family_Index;

      ------------------------
      -- Compare_Preference --
      ------------------------

      procedure Compare_Preference
        (New_Decl : in     Asis.Declaration;
         Old_Decl : in     Asis.Declaration;
         New_Pref : in out Boolean;
         Old_Pref : in out Boolean)
      is
         use XASIS.Types;

         New_Param : constant Asis.Parameter_Specification_List
           := XASIS.Utils.Get_Profile (New_Decl);
         Old_Param : constant Asis.Parameter_Specification_List
           := XASIS.Utils.Get_Profile (Old_Decl);
         New_Type  : constant Type_Info :=
           Type_Of_Declaration (New_Param (1), Element);
         Old_Type  : constant Type_Info :=
           Type_Of_Declaration (Old_Param (1), Element);
      begin
         if Is_Integer (New_Type) and then Is_Integer (New_Type) then
            if Is_Equal (Get_Declaration (Old_Type), Root_Integer) then
               Old_Pref := True;
            elsif Is_Equal (Get_Declaration (New_Type), Root_Integer) then
               New_Pref := True;
            end if;
         elsif Is_Real (New_Type) and then Is_Real (New_Type) then
            if Is_Equal (Get_Declaration (Old_Type), Root_Real) then
               Old_Pref := True;
            elsif Is_Equal (Get_Declaration (New_Type), Root_Real) then
               New_Pref := True;
            end if;
         end if;
      end Compare_Preference;

      ----------------------------
      -- Check_Prefered_And_Add --
      ----------------------------

      procedure Check_Prefered_And_Add
        (Result : in out Up_Interpretation_Set;
         Tipe   : in     Up_Interpretation;
         Store  : in out Stored_Set;
         Stored : in     Stored_Interpretation)
      is
         Count : Natural := 0;
         Item  : Stored_Interpretation;
         Next  : Up_Interpretation;
         Info  : constant Type_Info := Tipe.Expression_Type;
         New_Is_Prefered : Boolean := False;
         Old_Is_Prefered : Boolean := False;
         Fixed_Result    : Up_Interpretation_Set;
         Fixed_Store     : Stored_Set;
      begin
         if not Has_Type (Result, Info) then
            Add (Result, Tipe);
            Add (Store, Stored);
            return;
         end if;

         for I in 1 .. Length (Store) loop
            Get (Store, I, Item);

            if Item.Kind = A_Function_Call
              and then Item.Down.Kind = A_Declaration
              and then Is_Equal (Item.Result_Type, Info)
            then
               Compare_Preference
                 (Stored.Down.Declaration,
                  Item.Down.Declaration,
                  New_Is_Prefered,
                  Old_Is_Prefered);
            end if;
         end loop;

         if not (New_Is_Prefered or Old_Is_Prefered) then
            Add (Result, Tipe);
            Add (Store, Stored);
            return;
         elsif New_Is_Prefered and Old_Is_Prefered then
            raise Internal_Error;
         elsif Old_Is_Prefered then
            return;
         end if;

         Fixed_Result := Create;
         Fixed_Store  := Create;

         for I in 1 .. Length (Store) loop
            Get (Store, I, Item);

            if Item.Kind = A_Function_Call
              and then Item.Down.Kind = A_Declaration
              and then Is_Equal (Item.Result_Type, Info)
            then
               New_Is_Prefered := False;

               Compare_Preference
                 (Stored.Down.Declaration,
                  Item.Down.Declaration,
                  New_Is_Prefered,
                  Old_Is_Prefered);

               if New_Is_Prefered then
                  Count := Count + 1;
               else
                  Add (Fixed_Store, Item);
               end if;
            else
               Add (Fixed_Store, Item);
            end if;
         end loop;

         for I in 1 .. Length (Result) loop
            Get (Result, I, Next);

            if Count > 0
              and then Next.Kind = An_Expression
              and then Is_Equal (Next.Expression_Type, Info)
            then
               Count := Count - 1;
            else
               Add (Fixed_Result, Next);
            end if;
         end loop;

         Destroy (Result);
         Destroy (Store);
         Result := Fixed_Result;
         Store  := Fixed_Store;
         Add (Result, Tipe);
         Add (Store, Stored);
      end Check_Prefered_And_Add;

      -----------------------
      -- Check_Slice_Index --
      -----------------------

      function Check_Slice_Index return Boolean is
         Item : Up_Interpretation;
         Tipe : constant Type_Info :=
           Get_Array_Index_Type (Name.Expression_Type);
      begin
         for I in 1 .. Length (Sets (1)) loop
            Get (Sets (1), I, Item);

            if Item.Kind = A_Range and then
               Is_Expected_Type (Item.Range_Type, Tipe)
            then
               return True;
            end if;
         end loop;
         return False;
      end Check_Slice_Index;

      ----------------------------
      -- Is_Universal_Access_Eq --
      ----------------------------

      function Is_Universal_Access_Eq (Op : Asis.Declaration) return Boolean is
         Name : constant Asis.Defining_Name := Asis.Declarations.Names (Op)(1);
         Tipe : Asis.Definition;
         Decl : Asis.Declaration;
      begin
         if Defining_Name_Kind (Name) = A_Defining_Operator_Symbol and then
           Is_Part_Of_Implicit (Op)
         then
            Tipe := Asis.Declarations.Corresponding_Type (Op);

            if Assigned (Tipe) then
               Decl := Enclosing_Element (Tipe);

               return Is_Equal (Decl, XASIS.Types.Universal_Access);
            end if;
         end if;

         return False;
      end Is_Universal_Access_Eq;

      function Check_Universal_Access_Eq  --  ARM 4.5.2 (9.1/2)
        (Name : Up_Interpretation) return Boolean
      is
         Prefix : Asis.Expression;
      begin
         if Name.Kind /= A_Declaration or else
           not Is_Universal_Access_Eq (Name.Declaration)
         then
            return True;
         end if;

         if not Is_Anonymous_Access (Stored.Real_Types (1))
           and then not Is_Anonymous_Access (Stored.Real_Types (2))
         then
            return False;
         end if;

         Prefix := Asis.Expressions.Prefix (Element);

         if Expression_Kind (Prefix) = A_Selected_Component and then
           Is_Expanded_Name (Prefix)
         then
            return True;
         end if;

         --  TODO rest of rule
         return True;
      end Check_Universal_Access_Eq;

   begin  --  Up_Function_Call
      for I in reverse Sets'Range loop
         U.Pop (Resolver.Stack, Sets (I));
         Expand_Expression (Sets (I), Resolver.Implicit,
           Get_Actual_Parameter (Params, Asis.List_Index (I)));
      end loop;

      U.Pop (Resolver.Stack, Names);
      Expand_Prefix (Names, Resolver.Implicit,
        Get_Call_Prefix (Element));

      for I in 1 .. Length (Names) loop
         Get (Names, I, Name);

         if Check_Name (Name)
           and then Check_Parameters (Get_Profile (Name))
           and then Check_Universal_Access_Eq (Name)
         then
            Tipe := Get_Result_Profile (Name, Element);
            Stored.Down := Name;

            case Tipe.Kind is
               when A_Procedure_Call =>
                  Stored.Kind := A_Procedure_Call;
                  Add (Result, Tipe);
                  Add (Store, Stored);

               when An_Expression =>
                  Stored.Kind := A_Function_Call;
                  Stored.Result_Type := Tipe.Expression_Type;

                  if Is_Boolean (Tipe.Expression_Type) then
                     Check_Prefered_And_Add (Result, Tipe, Store, Stored);
                  else
                     Add (Result, Tipe);
                     Add (Store, Stored);
                  end if;
               when others =>
                  raise Internal_Error;
            end case;

            Stored.Real_Types := null;

         elsif Check_Array_Aggregate (Params) then
            if Check_Array (Name) then
               if Params'Length = 1 and then Check_Slice_Index then
                  Tipe := Name;
                  Add (Result, Tipe);

                  Stored.Kind := A_Slice;
                  Stored.Down := Name;
                  Stored.Result_Type := Tipe.Expression_Type;
                  Add (Store, Stored);
               elsif Check_Array_Indexes then
                  Tipe := Get_Array_Element_Type (Name.Expression_Type);
                  Add (Result, Tipe);

                  Stored.Kind := An_Array;
                  Stored.Down := Name;
                  Stored.Result_Type := Tipe.Expression_Type;
                  Add (Store, Stored);
               end if;
            elsif Params'Length = 1 and then Check_Family (Name)
              and then Check_Family_Index
            then
               Add (Result, (A_Family_Member, Name.Declaration));
            elsif Params'Length = 1 and then Check_Type_Conversion (Name) then
               declare
                  use Asis.Gela.Errors;
                  Found : Natural := 0;
                  Item  : Up_Interpretation;
               begin
                  Select_Prefered (Sets (1));  --  Hope Names'length=1

                  for J in 1 .. Length (Sets (1)) loop
                     Get (Sets (1), J, Item);

                     if Item.Kind = An_Expression then
                        Found := Found + 1;
                        Stored.Down := Item;
                     end if;
                  end loop;

                  if Found /= 0 then
                     if Found > 1 then
                        Report (Element, Error_Ambiguous_Interprentation);
                     end if;

                     Stored.Kind := A_Type_Conversion;

                     if Name.Kind = A_Declaration then
                        Stored.Result_Type :=
                          Type_From_Declaration (Name.Declaration, Element);
                     else
                        Stored.Result_Type := Name.Type_Info;
                     end if;

                     Add (Result, Up_Expression (Stored.Result_Type));
                     Add (Store, Stored);
                  end if;
               end;
            end if;
         end if;
      end loop;

      for I in Sets'Range loop
         Destroy (Sets (I));
      end loop;
      Destroy (Names);

      U.Push (Resolver.Stack, Result);
      Put (Resolver.Store, Element, Store);
   end Function_Call;

   ----------------------------
   -- Get_Array_Element_Type --
   ----------------------------

   function Get_Array_Element_Type
     (Tipe : Type_Info) return Up_Interpretation
   is
   begin
      return Up_Expression (Get_Array_Element_Type (Tipe));
   end Get_Array_Element_Type;

   ---------------------
   -- Get_Call_Prefix --
   ---------------------

   function Get_Call_Prefix (Element : Asis.Element )
     return Asis.Element
   is
   begin
      if Expression_Kind (Element) = A_Function_Call then
         return Asis.Expressions.Prefix (Element);
      elsif Statement_Kind (Element) = A_Procedure_Call_Statement then
         return Asis.Statements.Called_Name (Element);
      else
         raise Internal_Error;
      end if;
   end Get_Call_Prefix;

   ----------------------------------
   -- Identity_Attribute_Reference --
   ----------------------------------

   procedure Identity_Attribute_Reference
     (Resolver : in out Up_Resolver;
      Element  : in     Asis.Element)
   is
      function Is_Exception (Item : Asis.Declaration) return Boolean is
         Kind : constant Asis.Declaration_Kinds := Declaration_Kind (Item);
      begin
         return Kind = An_Exception_Declaration or else
           Kind = An_Exception_Renaming_Declaration;
      end Is_Exception;

      Set    : Up_Interpretation_Set;
      Item   : Up_Interpretation;
      Result : Up_Interpretation_Set := Create;
      Store  : Stored_Set := Create;
      Stored : Stored_Interpretation;
      Tipe   : Asis.Declaration;
   begin
      --  Attribute prefix
      U.Pop (Resolver.Stack, Set);
      Expand_Attribute_Prefix (Set, Resolver.Implicit,
        Asis.Expressions.Prefix (Element));

      if Has_Interpretation (Set, Element) then
         Get (Set, 1, Item);
         Stored.Down := Item;
         if Item.Kind = A_Declaration and then
           Is_Exception (Item.Declaration)
         then
            Tipe := XASIS.Types.Exception_Id;
         else
            Tipe := XASIS.Types.Task_Id;
         end if;
         Add (Result, Up_Expression (Tipe, Element));
      else
         Stored.Down := (Kind => A_Skip);
      end if;
      Add (Store, Stored);

      Destroy (Set);
      U.Push (Resolver.Stack, Result);
      Put (Resolver.Store, Element, Store);
   end Identity_Attribute_Reference;

   ----------------
   -- Membership --
   ----------------

   procedure Membership
     (Resolver  : in out Up_Resolver;
      Element   : in     Asis.Element)
   is
      use Asis.Gela.Errors;
      Left   : Up_Interpretation_Set;
      Right  : Up_Interpretation_Set;
      Tipe   : Type_Info;
      Kind   : constant Asis.Expression_Kinds := Expression_Kind (Element);
      Item   : Up_Interpretation;
      Store  : Stored_Set := Create;
      Stored : Stored_Interpretation;
      Found  : Boolean := False;
      Failed : Boolean := False;
   begin
      U.Pop (Resolver.Stack, Right);
      U.Pop (Resolver.Stack, Left);
      Expand_Expression (Left, Resolver.Implicit,
        Asis.Expressions.Membership_Test_Expression (Element));

      Resolve_Identifier (Right);

      if Kind in An_In_Range_Membership_Test .. A_Not_In_Range_Membership_Test
      then
         for I in 1 .. Length (Right) loop
            Get (Right, I, Item);

            if Item.Kind /= A_Range then
               raise Internal_Error;
            end if;
            Tipe := Item.Range_Type;
            Stored.Down := Item;
            for J in 1 .. Length (Left) loop
               Get (Left, J, Item);
               if Item.Kind = An_Expression and then
                 Is_Expected_Type (Item.Expression_Type, Tipe)
               then
                  if Found then
                     Report (Element, Error_Ambiguous_Interprentation);
                  else
                     Stored.Result_Type := Item.Expression_Type;
                     Add (Store, Stored);
                     Found := True;
                  end if;
               end if;
            end loop;
         end loop;
      else
         if Length (Right) = 1 then
            Get (Right, 1, Item);

            if Item.Kind = A_Declaration then
               Tipe := Type_From_Declaration (Item.Declaration, Element);
               Failed := Is_Not_Type (Tipe);
               Stored.Down := Item;
            elsif Item.Kind = A_Type then
               Tipe := Item.Type_Info;
               Failed := Is_Not_Type (Tipe);
               Stored.Down := Item;
            else
               Failed := True;
            end if;
         else
            Failed := True;
         end if;

         if Failed then
            Report (Element, Error_No_Interprentation);
         elsif Is_Tagged (Tipe) then
            for J in 1 .. Length (Left) loop
               Get (Left, J, Item);
               if Item.Kind = An_Expression and then
                 (Is_Covered (Item.Expression_Type, Tipe) or else
                 Is_Covered (Tipe, Item.Expression_Type))
               then
                  if Found then
                     Report (Element, Error_Ambiguous_Interprentation);
                  else
                     Stored.Result_Type := Item.Expression_Type;
                     Add (Store, Stored);
                     Found := True;
                  end if;
               end if;
            end loop;
         else
            for J in 1 .. Length (Left) loop
               Get (Left, J, Item);

               if Item.Kind = An_Expression and then
                 Is_Expected_Type (Item.Expression_Type, Tipe)
               then
                  if Found then
                     Report (Element, Error_Ambiguous_Interprentation);
                  else
                     Stored.Result_Type := Item.Expression_Type;
                     Add (Store, Stored);
                     Found := True;
                  end if;
               end if;
            end loop;
         end if;
      end if;

      Destroy (Left);
      Destroy (Right);

      if Failed or not Found then
         Left := Create;
         U.Push (Resolver.Stack, Left);
      else
         Push_Single (Resolver, Up_Expression (XASIS.Types.Boolean, Element));
      end if;

      Put (Resolver.Store, Element, Store);
   end Membership;

   -------------------------------
   -- Operator_Symbol_Or_String --
   -------------------------------

   procedure Operator_Symbol_Or_String
     (Resolver : in out Up_Resolver;
      Element  : in     Asis.Element)
   is
      Set  : Up_Interpretation_Set;
      Kind : constant Asis.Operator_Kinds :=
        XASIS.Utils.Operator_Kind (Asis.Expressions.Name_Image (Element));
   begin
      if Kind = Not_An_Operator then
         Push_Single (Resolver, (Kind => A_String_Type));
      else
         Push_Single (Resolver, (An_Identifier, Element), Resolve => True);
         U.Pop (Resolver.Stack, Set);
         Add (Set, (Kind => A_String_Type));
         U.Push (Resolver.Stack, Set);
      end if;
   end Operator_Symbol_Or_String;

   -----------------
   -- Push_Single --
   -----------------

   procedure Push_Single
     (Resolver : in out Up_Resolver;
      Item     : in     Up_Interpretation;
      Resolve  : in     Boolean := False)
   is
      Set : Up_Interpretation_Set := Create;
   begin
      Add (Set, Item);
      if Resolve then
         Resolve_Identifier (Set);
      end if;
      U.Push (Resolver.Stack, Set);
   end Push_Single;

   --------------------------
   -- Qualified_Expression --
   --------------------------

   procedure Qualified_Expression
     (Resolver  : in out Up_Resolver;
      Element   : in     Asis.Element)
   is
      Set    : Up_Interpretation_Set;
      Prefix : Up_Interpretation_Set;
      Tipe   : Type_Info;
      Store  : Stored_Set := Create;
      Stored : Stored_Interpretation;
      Result : Up_Interpretation_Set := Create;
      Item   : Up_Interpretation;
   begin
      U.Pop (Resolver.Stack, Set);
      U.Pop (Resolver.Stack, Prefix);

      Resolve_Identifier (Prefix);

      if Has_Interpretation (Prefix, Element) then
         Get (Prefix, 1, Item);

         if Item.Kind = A_Declaration and then
           Is_Type_Declaration (Item.Declaration)
         then
            Tipe := Type_From_Declaration (Item.Declaration, Element);
            Constrain_To_Type
              (Set,
               Resolver.Implicit,
               Asis.Expressions.Converted_Or_Qualified_Expression (Element),
               Tipe);

            if Has_Interpretation (Set, Element) then
               Get (Set, 1, Item);
               if Item.Kind = An_Expression then
                  Stored.Kind := A_Function_Call;
                  Stored.Result_Type := Tipe;
                  Stored.Down := Item;
                  Add (Store, Stored);
                  Add (Result, Up_Expression (Tipe));
               elsif Item.Kind = A_Record_Aggregate
                 or Item.Kind = A_String_Type
               then
                  Stored.Kind := An_Array;
                  Stored.Result_Type := Tipe;
                  Add (Store, Stored);
                  Add (Result, Up_Expression (Tipe));
               end if;
            end if;
         end if;
      end if;

      U.Push (Resolver.Stack, Result);
      Put (Resolver.Store, Element, Store);
      Destroy (Set);
      Destroy (Prefix);
   end Qualified_Expression;

   ------------------------
   -- Selected_Component --
   ------------------------

   procedure Selected_Component
     (Resolver : in out Up_Resolver;
      Element  : in     Asis.Element)
   is
      use XASIS.Utils;
      use Asis.Declarations;
      Set    : Up_Interpretation_Set;
      Prefix : Up_Interpretation_Set;
      Result : Up_Interpretation_Set;
      Item   : Up_Interpretation;
      Ident  : Asis.Identifier;
      Store  : Stored_Set;
      Stored : Stored_Interpretation;
      Decl   : Asis.Declaration;
      Def    : Asis.Definition;
      Found  : Boolean;
   begin
      if Is_Expanded_Name (Element) then
         Drop_One (Resolver);
         return;
      end if;

      U.Pop (Resolver.Stack, Set);

      if Length (Set) /= 1 then
         raise Internal_Error;
      else
         Get (Set, 1, Item);

         if Item.Kind /= An_Identifier then
            raise Internal_Error;
         end if;
      end if;

      Ident := Item.Identifier;
      U.Pop (Resolver.Stack, Prefix);
      Expand_Prefix (Prefix, Resolver.Implicit,
        Asis.Expressions.Prefix (Element));

      Result := Create;
      Store  := Create;

      for I in 1 .. Length (Prefix) loop
         Get (Prefix, I, Item);

         case Item.Kind is

            when An_Expression =>
               Found := False;

               if Is_Composite (Item.Expression_Type) and then
                 not Is_Array (Item.Expression_Type) then

                  Decl := Find_Component
                    (Item.Expression_Type, Name_Image (Ident));

                  if not Is_Nil (Decl) then
                     Stored.Kind := A_Component;
                     Stored.Down := Item;
                     Stored.Result_Type := Type_Of_Declaration (Decl, Element);
                     Stored.Component := Decl;
                     Add (Result, Up_Expression (Stored.Result_Type));
                     Add (Store, Stored);
                     Found := True;
                  elsif Is_Task (Item.Expression_Type)
                    or Is_Protected (Item.Expression_Type)
                  then
                     Def := Get_Type_Def (Item.Expression_Type);
                     Decl := Find_Task_Visible_Item (Def, Name_Image (Ident));

                     if not Is_Nil (Decl) then
                        Add (Result, (A_Declaration, Decl));
                        Stored.Kind := A_Function_Call;
                        Stored.Down := Item;
                        Add (Store, Stored);
                        Found := True;
                     end if;
                  end if;
               end if;

               if not Found and then
                 (Is_Tagged (Item.Expression_Type) or
                  Is_Class_Wide (Item.Expression_Type))
               then
                  declare
                     Not_Wide : constant Type_Info :=
                       Drop_Class (Item.Expression_Type);

                     List : constant Asis.Defining_Name_List :=
                       XASIS.Utils.Unique
                         (Subprograms_Of_Ancestor (Tipe   => Not_Wide,
                                                   Target => Not_Wide,
                                                   Ident  => Ident));
                     Decl : Asis.Declaration;
                  begin
                     for J in List'Range loop
                        Decl := Enclosing_Element (List (J));
                        Add (Result, (A_Prefixed_View, Decl));
                        Stored.Kind := A_Subprogram_Reference;
                        Stored.Down := Item;
                        Stored.Component := Decl;
                        Add (Store, Stored);
                     end loop;
                  end;
               end if;
            when A_Declaration =>
               case Declaration_Kind (Item.Declaration) is
                  when A_Single_Task_Declaration |
                    A_Single_Protected_Declaration |
                    A_Protected_Body_Declaration |
                    A_Task_Body_Declaration =>

                     Decl := Item.Declaration;

                     if Declaration_Kind (Decl) = A_Protected_Body_Declaration
                       or Declaration_Kind (Decl) = A_Task_Body_Declaration
                     then
                        Decl := Corresponding_Declaration (Decl);
                     end if;

                     Def := Object_Declaration_View (Decl);
                     Decl := Find_Task_Visible_Item (Def, Name_Image (Ident));

                     if not Is_Nil (Decl) then
                        Add (Result, (A_Declaration, Decl));
                        Stored.Kind := A_Function_Call;
                        Stored.Down := Item;
                        Add (Store, Stored);
                     end if;

                  when others =>
                     null;
               end case;

            when others =>
               raise Internal_Error;

         end case;
      end loop;

      U.Push (Resolver.Stack, Result);
      Destroy (Prefix);
      Destroy (Set);
      Put (Resolver.Store, Element, Store);
   end Selected_Component;

   -------------------
   -- Short_Circuit --
   -------------------

   procedure Short_Circuit
     (Resolver  : in out Up_Resolver;
      Element   : in     Asis.Element)
   is
      use Asis.Expressions;

      Result     : Up_Interpretation_Set := Create;
      Left       : Up_Interpretation_Set;
      Right      : Up_Interpretation_Set;
      Left_Item  : Up_Interpretation;
   begin
      U.Pop (Resolver.Stack, Right);
      U.Pop (Resolver.Stack, Left);

      Expand_Expression (Right, Resolver.Implicit,
        Short_Circuit_Operation_Right_Expression (Element));

      Constrain_To_Boolean_Types (Left, Resolver.Implicit,
        Short_Circuit_Operation_Left_Expression (Element));

      for I in 1 .. Length (Left) loop
         Get (Left, I, Left_Item);
         if Left_Item.Kind = An_Expression and then
            Has_Type (Right, Left_Item.Expression_Type) then
            Add (Result, Left_Item);
         end if;
      end loop;

      U.Push (Resolver.Stack, Result);
      Destroy (Right);
      Destroy (Left);
   end Short_Circuit;

   ------------------
   -- Simple_Range --
   ------------------

   procedure Simple_Range
     (Resolver : in out Up_Resolver;
      Element  : in     Asis.Element)
   is
      Result     : Up_Interpretation_Set := Create;
      Left       : Up_Interpretation_Set;
      Right      : Up_Interpretation_Set;
      Left_Item  : Up_Interpretation;
      Right_Item : Up_Interpretation;
      Tipe       : Type_Info;
   begin
      U.Pop (Resolver.Stack, Right);
      U.Pop (Resolver.Stack, Left);

      Expand_Expression (Right, Resolver.Implicit,
        Asis.Definitions.Upper_Bound (Element));

      Expand_Expression (Left, Resolver.Implicit,
        Asis.Definitions.Lower_Bound (Element));

      for I in 1 .. Length (Left) loop
         Get (Left, I, Left_Item);

         for J in 1 .. Length (Right) loop
            Get (Right, J, Right_Item);

            if Right_Item.Kind = An_Expression and then
              Left_Item.Kind = An_Expression
            then
               Tipe := Type_Of_Range (Left_Item.Expression_Type,
                                      Right_Item.Expression_Type);
               if not Is_Not_Type (Tipe) then
                  Add (Result, (A_Range, Tipe));
               end if;
            end if;
         end loop;
      end loop;
      U.Push (Resolver.Stack, Result);
      Destroy (Right);
      Destroy (Left);
   end Simple_Range;

   -----------------------------
   -- Subprograms_Of_Ancestor --
   -----------------------------

   function Subprograms_Of_Ancestor
     (Tipe   : Type_Info;
      Target : Type_Info;
      Ident  : Asis.Identifier) return Asis.Defining_Name_List
   is
      use Asis.Gela.Visibility;

      function Fit (Name : Defining_Name) return Boolean is
         Decl : constant Asis.Declaration := Enclosing_Element (Name);
         List : constant Asis.Parameter_Specification_List :=
           XASIS.Utils.Get_Profile (Decl);
      begin
         if List'Length = 0 then
            return False;
         end if;

         declare
            Info : Type_Info := Type_Of_Declaration (List (1), Ident);
         begin
            if Is_Anonymous_Access (Info) then
               Info := Destination_Type (Info);
            end if;

            return Is_Equal (Target, Info) or else
              (Is_Class_Wide (Info) and then
               Is_Covered (Target, Class_Wide => Info));
         end;
      end Fit;

      Decl    : constant Asis.Declaration := Get_Declaration (Tipe);
      Parents : constant Asis.Name_List := XASIS.Utils.Get_Ancestors (Decl);
      List    : constant Asis.Element_List :=
        Subprograms_Of_Ancestors (Parents, Target, Ident);
      Found   : Asis.Element_List := Lookup_In_Parent_Region (Ident, Decl);
      Index   : Asis.ASIS_Natural := 0;
   begin
      for J in Found'Range loop
         if Fit (Found (J)) then
            Index := Index + 1;
            Found (Index) := Found (J);
         end if;
      end loop;

      return Found (1 .. Index) & List;
   end Subprograms_Of_Ancestor;

   ------------------------------
   -- Subprograms_Of_Ancestors --
   ------------------------------

   function Subprograms_Of_Ancestors
     (Ancestors   : Asis.Name_List;
      Target      : Type_Info;
      Ident       : Asis.Identifier) return Asis.Defining_Name_List
   is
   begin
      if Ancestors'Length = 0  then
         return Asis.Nil_Element_List;
      else
         declare
            Tipe : constant Type_Info := Type_From_Subtype_Mark
              (Ancestors (Ancestors'Last), Ident);
            List : constant Asis.Element_List :=
              Subprograms_Of_Ancestor (Tipe, Target, Ident);
         begin
            if Ancestors'First = Ancestors'Last  then
               return List;
            else
               return Subprograms_Of_Ancestors
                 (Ancestors (Ancestors'First .. Ancestors'Last - 1),
                  Target,
                  Ident) & List;
            end if;
         end;
      end if;
   end Subprograms_Of_Ancestors;

end Asis.Gela.Overloads.Walk.Up;


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
