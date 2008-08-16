with Asis.Elements;
with Asis.Gela.Utils;
with Asis.Gela.Errors;
with Asis.Expressions;
with Asis.Definitions;
with Asis.Declarations;
with Asis.Gela.Replace;
with Asis.Gela.Overloads.Attr;
with Ada.Unchecked_Deallocation;

with XASIS.Types;
with XASIS.Utils;

package body Asis.Gela.Overloads.Types is

--   use Asis.Elements;
   use XASIS.Utils;
   use Asis.Gela.Classes;

   generic
      with function Pass (Item : Type_Info) return Boolean;
      Xor_Logic : in Boolean := False;
   procedure Constrain_To
     (Set     : in out Up_Interpretation_Set;
      Impl    : in out Implicit_Set;
      Element : in     Asis.Element);

   function Is_Tagged_Non_Limited (Info : Type_Info) return Boolean;

   function Has_Type
     (Item   : Up_Interpretation;
      Mark   : Classes.Type_Info) return Boolean;

   ---------
   -- Add --
   ---------

   procedure Add
     (Container : in out Stored_Set;
      Item      : in     Stored_Interpretation)
   is
   begin
      R.Append (Container.List, Item);
      Container.Length := Container.Length + 1;
   end Add;

   ---------
   -- Add --
   ---------

   procedure Add
     (Container : in out Up_Interpretation_Set;
      Item      : in     Up_Interpretation)
   is
   begin
      L.Append (Container.Items.all, Item);
      Container.Length := Container.Length + 1;
   end Add;

   --------------------
   -- Check_Implicit --
   --------------------

   procedure Check_Implicit
     (Set     : in out Implicit_Set;
      Store   : in out Stored_Sets;
      Element : in out Asis.Element;
      Down    : in out Down_Interpretation)
   is
      use Implicit_Nodes;
      use Asis.Gela.Replace;
      Index  : Cursor := First (Set.all);
      Node   : Implicit_Node;
      Found  : Boolean := False;
      St     : Stored_Set;
      Stored : Stored_Interpretation;
   begin
      if Down.Kind /= An_Expression then
         return;
      end if;

      while Has_Element (Index) loop
         Node := Implicit_Nodes.Element (Index);

         if Is_Equal (Node.Key, Element) then
            if not Found and then
              Is_Expected_Type (Node.Return_Type, Down.Expression_Type)
            then
               Found := True;
               if Node.Is_Call then
                  Expression_To_Function_Call (Element);
                  St := Create;
                  Stored.Kind := A_Function_Call;
                  Stored.Result_Type := Node.Return_Type;
                  Stored.Down := Node.Down;
                  Add (St, Stored);
                  Put (Store, Element, St);
               else  --  implicit dereference
                  Down := To_Down_Interpretation (Node.Down);
               end if;
            end if;

            Delete (Set.all, Index);
         else
            Index := Next (Index);
         end if;
      end loop;
   end Check_Implicit;

   ----------------
   -- Check_Name --
   ----------------

   function Check_Name (Name : Up_Interpretation) return Boolean is
   begin
      case Name.Kind is
         when An_Identifier =>
            raise Internal_Error;
         when A_Declaration =>
            return Check_Callable_Name (Name.Declaration);
         when A_Family_Member |
           A_Subprogram_Reference |
           An_Attribute_Function |
           A_Prefixed_View
           =>
            return True;
         when An_Expression =>
            return Is_Subprogram_Access (Name.Expression_Type);
         when others =>
            return False;
      end case;
   end Check_Name;

   ------------------
   -- Constrain_To --
   ------------------

   procedure Constrain_To
     (Set     : in out Up_Interpretation_Set;
      Impl    : in out Implicit_Set;
      Element : in     Asis.Element)
   is
      Item   : Up_Interpretation;
      Passed : Boolean;
      Index  : L.Cursor;
   begin
      Expand_Expression (Set, Impl, Element);
      Index := L.First (Set.Items.all);

      while L.Has_Element (Index) loop
         Item   := L.Element (Index);
         Passed := False;

         case Item.Kind is
            when An_Expression =>
               Passed := Xor_Logic xor Pass (Item.Expression_Type);
            when An_Identifier =>
               raise Internal_Error;
            when A_Box =>
               Passed := not Xor_Logic;
            when A_Declaration |
              A_Prefixed_View |
              A_Family_Member |
              A_Range |
              A_String_Type |
              A_Procedure_Call |
              A_Subprogram_Reference |
              A_General_Access |
              An_Object_Access |
              A_Subprogram_Access |
              An_Array_Aggregate |
              A_Subaggregate |
              A_Record_Aggregate |
              An_Extension_Aggregate |
              An_Attribute_Function |
              A_Boolean |
              A_Type |
              A_Skip =>
               null;
         end case;

         if Passed then
            Index := L.Next (Index);
         else
            L.Delete (Set.Items.all, Index);
            Set.Length := Set.Length - 1;
         end if;
      end loop;

      Set.Index := 0;
   end Constrain_To;

   -------------------------------
   -- Constrain_To_Access_Types --
   -------------------------------

   procedure Constrain_To_Access is
      new Constrain_To (Is_Access);

   procedure Constrain_To_Access_Types
     (Set     : in out Up_Interpretation_Set;
      Impl    : in out Implicit_Set;
      Element : in     Asis.Element)
      renames Constrain_To_Access;

   --------------------------------
   -- Constrain_To_Boolean_Types --
   --------------------------------

   procedure Constrain_To_Boolean is
      new Constrain_To (Is_Boolean);

   procedure Constrain_To_Boolean_Types
     (Set     : in out Up_Interpretation_Set;
      Impl    : in out Implicit_Set;
      Element : in     Asis.Element)
   renames Constrain_To_Boolean;

   ------------------------
   -- Constrain_To_Calls --
   ------------------------

   procedure Constrain_To_Calls
     (Set     : in out Up_Interpretation_Set)
   is

      function Is_Procedure (Decl : Asis.Declaration) return Boolean is
         use Asis.Elements;
      begin
         case Declaration_Kind (Decl) is
            when A_Procedure_Declaration |
              A_Procedure_Body_Declaration |
              A_Procedure_Renaming_Declaration |
              An_Entry_Declaration =>
               return True;
            when others =>
               return False;
         end case;
      end Is_Procedure;

      Item   : Up_Interpretation;
      Index  : L.Cursor;
   begin
      Resolve_Identifier (Set);
      Index := L.First (Set.Items.all);

      while L.Has_Element (Index) loop
         Item := L.Element (Index);

         if Item.Kind = A_Procedure_Call then
            Index := L.Next (Index);
         elsif Item.Kind = A_Declaration and then
           Parameterless (Item.Declaration) and then
           Is_Procedure (Item.Declaration)
         then
            Index := L.Next (Index);
         elsif Item.Kind = A_Family_Member
           and then XASIS.Utils.Is_Entry_Family (Item.Declaration)
           and then Is_Empty_Profile (Get_Profile (Item.Declaration))
         then
            Index := L.Next (Index);
         elsif Item.Kind = A_Prefixed_View and then
           Is_Empty_Profile (Get_Profile (Item)) and then
           Is_Procedure (Item.Declaration)
         then
            Index := L.Next (Index);
         else
            L.Delete (Set.Items.all, Index);
            Set.Length := Set.Length - 1;
         end if;
      end loop;

      Set.Index := 0;
   end Constrain_To_Calls;

   ---------------------------------
   -- Constrain_To_Discrete_Types --
   ---------------------------------

   procedure Constrain_To_Discrete is
      new Constrain_To (Is_Discrete);

   procedure Constrain_To_Discrete_Types
     (Set     : in out Up_Interpretation_Set;
      Impl    : in out Implicit_Set;
      Element : in     Asis.Element)
      renames Constrain_To_Discrete;

   --------------------------------
   -- Constrain_To_Integer_Types --
   --------------------------------

   procedure Constrain_To_Integer is
      new Constrain_To (Is_Integer);

   procedure Constrain_To_Integer_Types
     (Set     : in out Up_Interpretation_Set;
      Impl    : in out Implicit_Set;
      Element : in     Asis.Element)
      renames Constrain_To_Integer;

   ------------------------------------
   -- Constrain_To_Non_Limited_Types --
   ------------------------------------

   procedure Constrain_To_Non_Limited is
      new Constrain_To (Is_Limited, True);

   procedure Constrain_To_Non_Limited_Types
     (Set     : in out Up_Interpretation_Set;
      Impl    : in out Implicit_Set;
      Element : in     Asis.Element)
      renames Constrain_To_Non_Limited;

   --------------------------------
   -- Constrain_To_Numeric_Types --
   --------------------------------

   procedure Constrain_To_Numeric is
      new Constrain_To (Is_Numeric);

   procedure Constrain_To_Numeric_Types
     (Set     : in out Up_Interpretation_Set;
      Impl    : in out Implicit_Set;
      Element : in     Asis.Element)
      renames Constrain_To_Numeric;

   ------------------------------
   -- Constrain_To_Real_Types --
   ------------------------------

   procedure Constrain_To_Real is
      new Constrain_To (Is_Real);

   procedure Constrain_To_Real_Types
     (Set     : in out Up_Interpretation_Set;
      Impl    : in out Implicit_Set;
      Element : in     Asis.Element)
      renames Constrain_To_Real;

   -------------------------------
   -- Constrain_To_Tagged_Types --
   -------------------------------

   procedure Constrain_To_Tagged is
      new Constrain_To (Is_Tagged);

   procedure Constrain_To_Tagged_Types
     (Set     : in out Up_Interpretation_Set;
      Impl    : in out Implicit_Set;
      Element : in     Asis.Element)
      renames Constrain_To_Tagged;

   -------------------------------------------
   -- Constrain_To_Tagged_Non_Limited_Types --
   -------------------------------------------

   procedure Constrain_To_Tagged_Non_Limited is
      new Constrain_To (Is_Tagged_Non_Limited);

   procedure Constrain_To_Tagged_Non_Limited_Types
     (Set     : in out Up_Interpretation_Set;
      Impl    : in out Implicit_Set;
      Element : in     Asis.Element)
      renames Constrain_To_Tagged_Non_Limited;

   ------------------------
   -- Constrain_To_Range --
   ------------------------

   procedure Constrain_To_Range
     (Set     : in out Up_Interpretation_Set;
      Impl    : in out Implicit_Set;
      Element : in     Asis.Element;
      Tipe    : in     Classes.Type_Info)
   is
      Item   : Up_Interpretation;
      Index  : L.Cursor := L.First (Set.Items.all);
   begin
      while L.Has_Element (Index) loop
         Item := L.Element (Index);

         if Item.Kind = A_Range
           and then Is_Expected_Type (Item.Range_Type, Tipe)
         then
            Index := L.Next (Index);
         else
            L.Delete (Set.Items.all, Index);
            Set.Length := Set.Length - 1;
         end if;
      end loop;

      Set.Index  := 0;
   end Constrain_To_Range;

   ---------------------------------
   -- Constrain_To_Discrete_Range --
   ---------------------------------

   procedure Constrain_To_Discrete_Range
     (Set     : in out Up_Interpretation_Set;
      Impl    : in out Implicit_Set;
      Element : in     Asis.Element)
   is
      Item   : Up_Interpretation;
      Index  : L.Cursor := L.First (Set.Items.all);
   begin
      while L.Has_Element (Index) loop
         Item := L.Element (Index);

         if Item.Kind = A_Range and then Is_Discrete (Item.Range_Type) then
            Index := L.Next (Index);
         else
            L.Delete (Set.Items.all, Index);
            Set.Length := Set.Length - 1;
         end if;
      end loop;

      Set.Index  := 0;
   end Constrain_To_Discrete_Range;

   -----------------------------------
   -- Constrain_To_Expected_Profile --
   -----------------------------------

   procedure Constrain_To_Expected_Profile
     (Set     : in out Up_Interpretation_Set;
      Profile : in     Asis.Declaration;
      Place   : in     Asis.Element;
      Empty   : in     Boolean := False)
   is
      use Asis.Gela.Utils;
      use Asis.Declarations;

      function Get_Name (Element : Asis.Element) return Asis.Defining_Name is
      begin
         if Element_Kind (Element.all) = A_Statement then
            return Accept_Entry_Direct_Name (Profile.all);
         else
            return Names (Profile) (1);
         end if;
      end Get_Name;

      Name   : constant Asis.Element := Get_Name (Profile);
      Item   : Up_Interpretation;
      Index  : L.Cursor;
   begin
      Resolve_Identifier (Set);
      Index := L.First (Set.Items.all);

      while L.Has_Element (Index) loop
         Item := L.Element (Index);

         if ((Item.Kind = A_Declaration or Item.Kind = A_Prefixed_View)
             and then not XASIS.Utils.Is_Entry_Family (Item.Declaration))
           or (Item.Kind = A_Family_Member
             and then XASIS.Utils.Is_Entry_Family (Item.Declaration))
         then
            declare
               List : constant Asis.Defining_Name_List :=
                 Names (Item.Declaration);
            begin
               if (List'Length > 0
                   and then Are_Type_Conformant
                     (Name, List (1), Place,
                      Right_Is_Prefixed_View => Item.Kind = A_Prefixed_View))
                 or else
                  (Empty and then Get_Profile (Item.Declaration)'Length = 0)
               then
                  Index := L.Next (Index);
               else
                  L.Delete (Set.Items.all, Index);
                  Set.Length := Set.Length - 1;
               end if;
            end;
         else
            L.Delete (Set.Items.all, Index);
            Set.Length := Set.Length - 1;
         end if;
      end loop;

      Set.Index  := 0;
   end Constrain_To_Expected_Profile;

   -----------------------
   -- Constrain_To_Type --
   -----------------------

   procedure Constrain_To_Type
     (Set     : in out Up_Interpretation_Set;
      Impl    : in out Implicit_Set;
      Element : in     Asis.Element;
      Tipe    : in     Type_Info)
   is
      Item   : Up_Interpretation;
      Index  : L.Cursor;
   begin
      Expand_Expression (Set, Impl, Element);
      Index := L.First (Set.Items.all);

      while L.Has_Element (Index) loop
         Item := L.Element (Index);

         if Has_Type (Item, Tipe) then
            Index := L.Next (Index);
         else
            L.Delete (Set.Items.all, Index);
            Set.Length := Set.Length - 1;
         end if;
      end loop;

      Set.Index  := 0;
   end Constrain_To_Type;

   ------------
   -- Create --
   ------------

   function Create return Implicit_Set is
   begin
      return new Implicit_Nodes.List;
   end Create;


   ------------
   -- Create --
   ------------

   function Create return Up_Interpretation_Set is
   begin
      return (new L.List, 0, 0, L.No_Element);
   end Create;

   ------------
   -- Create --
   ------------

   function Create return Stored_Set is
   begin
      return new Stored_Set_Node;
   end Create;

   ------------
   -- Create --
   ------------

   function Create return Stored_Sets is
   begin
      return new S.List;
   end Create;

   -----------------
   -- Dereference --
   -----------------

   function Dereference (Tipe : Type_Info) return Up_Interpretation is
   begin
      if Is_Subprogram_Access (Tipe) then
         return (A_Subprogram_Reference, Tipe);
      elsif Is_Object_Access (Tipe) then
         return Up_Expression (Destination_Type (Tipe));
      else
         raise Internal_Error;
      end if;
   end Dereference;

   -------------
   -- Destroy --
   -------------

   procedure Destroy (Set : in out Implicit_Set) is
      use Implicit_Nodes;
      procedure Free is
         new Ada.Unchecked_Deallocation (List, Implicit_Set);
   begin
      Clear (Set.all);
      Free (Set);
   end Destroy;

   -------------
   -- Destroy --
   -------------

   procedure Destroy (Set : in out Up_Interpretation_Set) is
      procedure Free is
         new Ada.Unchecked_Deallocation (L.List, L_List_Access);
   begin
      L.Clear (Set.Items.all);
      Free (Set.Items);
   end Destroy;

   -------------
   -- Destroy --
   -------------

   procedure Destroy (Set : in out Stored_Set) is
      procedure Free is
         new Ada.Unchecked_Deallocation (Stored_Set_Node, Stored_Set);

      procedure Free is
         new Ada.Unchecked_Deallocation (Type_Infos, Type_Infos_Access);

      Stored : Stored_Interpretation;
   begin
      for I in 1 .. Length (Set) loop
         Get (Set, I, Stored);

         if Stored.Real_Types /= null then
            Free (Stored.Real_Types);
         end if;
      end loop;

      R.Clear (Set.List);
      Free (Set);
   end Destroy;

   -------------
   -- Destroy --
   -------------

   procedure Destroy (Set : in out Stored_Sets) is
      procedure Free is
         new Ada.Unchecked_Deallocation (S.List, Stored_Sets);
   begin
      S.Clear (Set.all);
      Free (Set);
   end Destroy;

   ---------------------
   -- Expand_Implicit --
   ---------------------

   procedure Expand_Implicit
     (Set         : in out Up_Interpretation_Set;
      Impl        : in out Implicit_Set;
      Element     : in     Asis.Element;
      Dereference : in     Boolean;
      Force       : in     Boolean := False)
   is
      use Asis.Elements;
      use Asis.Expressions;

      procedure Add_Expr
        (Tipe : Type_Info;
         Old  : Boolean := False;
         Call : Boolean := False;
         Down : Up_Interpretation := (Kind => A_Skip)) is
      begin
         if Dereference and then Is_Object_Access (Tipe) then
            declare
               Dest : constant Type_Info := Destination_Type (Tipe);
               Node : Implicit_Node;
            begin
               Add (Set, Up_Expression (Dest));
               Node.Key         := Element;

               if Call then
                  Node.Down     := Down;
               else
                  Node.Down     := Up_Expression (Tipe);
               end if;

               Node.Return_Type := Dest;
               Node.Is_Call     := Call;
               Implicit_Nodes.Append (Impl.all, Node);

               if Force then
                  return;
               end if;
            end;
         end if;

         if not Old then
            Add (Set, Up_Expression (Tipe));

            if Call then
               declare
                  Node : Implicit_Node;
               begin
                  Node.Key         := Element;
                  Node.Down        := Down;
                  Node.Return_Type := Tipe;
                  Node.Is_Call     := True;
                  Implicit_Nodes.Append (Impl.all, Node);
               end;
            end if;
         end if;
      end Add_Expr;

      procedure Add_Decl
        (Decl : in     Asis.Declaration;
         Keep :    out Boolean)
      is
         Subtipe : Asis.Definition;
         Tipe    : Type_Info := Type_Of_Declaration (Decl, Element);
      begin
         if not Is_Not_Type (Tipe) then
            Add_Expr (Tipe);
            Keep := False;
         elsif Parameterless (Decl) then
            Subtipe := Get_Result_Subtype (Decl);

            if not Assigned (Subtipe) then
               --  Parameterless procedure
               Keep := True;
            else
               Tipe := Type_From_Indication (Subtipe, Element);

               Add_Expr (Tipe, Call => True, Down => (A_Declaration, Decl));

               if Force then
                  Keep := False;
               else
                  Keep := True;
               end if;
            end if;
         else
            Keep := True;
         end if;
      end Add_Decl;

      Index : L.Cursor := L.First (Set.Items.all);
      Count : Positive := 1;
      Last  : Natural := Length (Set);
      Item  : Up_Interpretation;
      Keep  : Boolean;
   begin
      while Count <= Last loop
         Item := L.Element (Index);

         if Item.Kind = An_Identifier then
            L.Delete (Set.Items.all, Index);
            Last       := Last - 1;
            Set.Length := Set.Length - 1;

            declare
               Decl : Asis.Declaration;
               List : constant Asis.Defining_Name_List :=
                 Corresponding_Name_Definition_List (Item.Identifier);
            begin
               for I in List'Range loop
                  Decl := Enclosing_Element (List (I));
                  Add_Decl (Decl, Keep);

                  if Keep then
                     Add (Set, (A_Declaration, Decl));
                  end if;
               end loop;
            end;
         elsif Item.Kind = A_Declaration then
            Add_Decl (Item.Declaration, Keep);

            if Keep then
               Index := L.Next (Index);
               Count := Count + 1;
            else
               L.Delete (Set.Items.all, Index);
               Last       := Last - 1;
               Set.Length := Set.Length - 1;
            end if;
         elsif Item.Kind = An_Expression then
            Add_Expr (Item.Expression_Type, Old => True);
            Index := L.Next (Index);
            Count := Count + 1;
         elsif Item.Kind = A_Subprogram_Reference or
           Item.Kind = A_Prefixed_View
         then
            if Is_Empty_Profile (Get_Profile (Item)) then
               declare
                  Result : constant Up_Interpretation :=
                    Get_Result_Profile (Item, Element);
               begin
                  if Result.Kind = An_Expression then
                     Add_Expr (Result.Expression_Type,
                       Call => True, Down => Item);
                  end if;
               end;
            end if;

            Index := L.Next (Index);
            Count := Count + 1;
         else
            Index := L.Next (Index);
            Count := Count + 1;
         end if;
      end loop;

      Set.Index  := 0;
   end Expand_Implicit;

   -------------------
   -- Expand_Prefix --
   -------------------

   procedure Expand_Prefix
     (Set     : in out Up_Interpretation_Set;
      Impl    : in out Implicit_Set;
      Element : in     Asis.Element) is
   begin
      Expand_Implicit (Set, Impl, Element, True);
   end Expand_Prefix;

   --------------------------
   -- Expand_Function_Call --
   --------------------------

   procedure Expand_Expression
     (Set     : in out Up_Interpretation_Set;
      Impl    : in out Implicit_Set;
      Element : in     Asis.Element) is
   begin
      Expand_Implicit (Set, Impl, Element, False);
   end Expand_Expression;

   -----------------------------
   -- Expand_Attribute_Prefix --
   -----------------------------

   procedure Expand_Attribute_Prefix
     (Set         : in out Up_Interpretation_Set;
      Impl        : in out Implicit_Set;
      Element     : in     Asis.Element;
      Dereference : in     Boolean := True) is
   begin
      Expand_Implicit (Set, Impl, Element, Dereference, True);
   end Expand_Attribute_Prefix;

   ---------
   -- Get --
   ---------

   procedure Get
     (Set   : in out Up_Interpretation_Set;
      Index : in     Positive;
      Item  :    out Up_Interpretation) is
   begin
      if Index not in 1 .. Set.Length then
         raise Constraint_Error;
      elsif Set.Index = 0 then
         Set.Index := 1;
         Set.Pos := L.First (Set.Items.all);
      end if;

      loop
         if Set.Index = Index then
            Item := L.Element (Set.Pos);
            return;
         elsif Set.Index = Set.Length then
            Set.Index := 1;
            Set.Pos := L.First (Set.Items.all);
         else
            Set.Index := Set.Index + 1;
            Set.Pos := L.Next (Set.Pos);
         end if;
      end loop;
   end Get;

   ---------
   -- Get --
   ---------

   procedure Get
     (Set   : in out Stored_Set;
      Index : in     Positive;
      Item  :    out Stored_Interpretation) is
   begin
      if Index not in 1 .. Set.Length then
         raise Constraint_Error;
      elsif Set.Index = 0 then
         Set.Index := 1;
         Set.Pos   := R.First (Set.List);
      end if;

      loop
         if Set.Index = Index then
            Item := R.Element (Set.Pos);
            return;
         elsif Set.Index = Set.Length then
            Set.Index := 1;
            Set.Pos   := R.First (Set.List);
         else
            Set.Index := Set.Index + 1;
            Set.Pos := R.Next (Set.Pos);
         end if;
      end loop;
   end Get;

   ---------
   -- Get --
   ---------

   procedure Get
     (Set  : in     Stored_Sets;
      Key  : in     Asis.Element;
      Item :    out Stored_Set)
   is
      Next : aliased Stored_Set;
   begin
      Item := null;

      while S.Iterate (Set.all, Next'Access) loop
         if Asis.Elements.Is_Equal (Next.Key, Key) then
            if Item = null then
               S.Delete_First (Set.all, Item);
            else
               S.Delete_Next (Set.all, Item, Next);
            end if;

            Item := Next;
            return;
         end if;

         Item := Next;
      end loop;

      raise Internal_Error;
   end Get;

   --------------
   -- Get_Next --
   --------------

   function Get_Next (Left : Stored_Set) return Stored_Set is
   begin
      return Left.Next;
   end Get_Next;

   ------------------------
   -- Get_Parameter_Type --
   ------------------------

   function Get_Parameter_Type
     (Name    : Up_Interpretation;
      Profile : Asis.Parameter_Specification_List;
      Index   : List_Index;
      Place   : Asis.Element) return Classes.Type_Info
   is
      Tipe : Classes.Type_Info;
   begin
      if XASIS.Utils.Is_Parameter_Specification (Profile (Index)) then
         Tipe := Type_Of_Declaration (Profile (Index), Place);
      else
         Tipe := Type_From_Declaration (Profile (Index), Place);

         if Name.Kind = An_Attribute_Function and then
           (Name.Attr_Kind = A_Read_Attribute
            or Name.Attr_Kind = A_Write_Attribute
            or Name.Attr_Kind = An_Input_Attribute
            or Name.Attr_Kind = An_Output_Attribute)
         then
            if Index = 1 then
               Set_Class_Wide (Tipe);
               Set_Access (Tipe, True);
            elsif Name.Class_Wide then
               Set_Class_Wide (Tipe);
            end if;
         end if;
      end if;

      return Tipe;
   end Get_Parameter_Type;

   -----------------
   -- Get_Profile --
   -----------------

   function Get_Profile
     (Name : Up_Interpretation) return Asis.Parameter_Specification_List
   is
      use Asis.Definitions;
      use Asis.Declarations;
   begin
      case Name.Kind is

         when A_Declaration | A_Family_Member =>
            return XASIS.Utils.Get_Profile (Name.Declaration);

         when An_Expression =>
            if Is_Subprogram_Access (Name.Expression_Type) then
               return Subprogram_Parameters (Name.Expression_Type);
            else
               raise Internal_Error;
            end if;

         when A_Subprogram_Reference =>
            if Is_Subprogram_Access (Name.Access_Type) then
               return Subprogram_Parameters (Name.Access_Type);
            else
               raise Internal_Error;
            end if;

         when An_Attribute_Function =>
            return Attr.Get_Profile (Name.Prefix, Name.Attr_Kind);

         when A_Prefixed_View =>
            declare
               List : constant Asis.Parameter_Specification_List :=
                 XASIS.Utils.Get_Profile (Name.Declaration);
               Result : constant Asis.Parameter_Specification_List
                 (1 .. List'Length - 1) :=
                 List (2 .. List'Last);
            begin
               if Names (List (1))'Length > 1 then
                  raise Unimplemented;
               end if;

               return Result;
            end;
         when others =>
            raise Internal_Error;

      end case;
   end Get_Profile;

   ------------------------
   -- Get_Result_Profile --
   ------------------------

   function Get_Result_Profile
     (Name  : Up_Interpretation;
      Place : Asis.Element) return Up_Interpretation
   is
      use Asis.Elements;
      use Asis.Definitions;
      use Asis.Declarations;
      Result : Up_Interpretation;
   begin
      case Name.Kind is

         when A_Declaration | A_Prefixed_View =>
            case Declaration_Kind (Name.Declaration) is
               when A_Function_Declaration |
                    A_Function_Body_Declaration |
                    A_Function_Renaming_Declaration |
                    A_Function_Body_Stub |
                    A_Function_Instantiation |
                    A_Formal_Function_Declaration =>

                  Result := Up_Expression (
                    Type_From_Indication (
                      Get_Result_Subtype (Name.Declaration), Place));

               when A_Procedure_Declaration |
                    A_Procedure_Body_Declaration |
                    A_Procedure_Renaming_Declaration |
                    An_Entry_Declaration |
                    A_Procedure_Body_Stub |
                    A_Procedure_Instantiation |
                    A_Formal_Procedure_Declaration =>

                  Result := (Kind => A_Procedure_Call);

               when others =>
                  raise Internal_Error;
            end case;

         when A_Family_Member =>
            Result := (Kind => A_Procedure_Call);

         when An_Expression =>
            if Is_Procedure_Access (Name.Expression_Type) then
               Result := (Kind => A_Procedure_Call);
            elsif Is_Function_Access (Name.Expression_Type) then
               Result := Up_Expression (
                 Function_Result_Type (Name.Expression_Type));
            else
               raise Internal_Error;
            end if;

         when A_Subprogram_Reference =>
            if Is_Procedure_Access (Name.Access_Type) then
               Result := (Kind => A_Procedure_Call);
            elsif Is_Function_Access (Name.Access_Type) then
               Result := Up_Expression (
                 Function_Result_Type (Name.Access_Type));
            else
               raise Internal_Error;
            end if;

         when An_Attribute_Function =>
            return Attr.Get_Result_Profile (Name.Prefix,
                                            Name.Attr_Kind,
                                            Name.Class_Wide,
                                            Place);

         when others =>
            raise Internal_Error;

      end case;
      return Result;
   end Get_Result_Profile;

   --------------
   -- Get_Type --
   --------------

   function Get_Type
     (Set    : Up_Interpretation_Set;
      Mark   : Type_Info) return Up_Interpretation
   is
      Item  : Up_Interpretation;
      Index : L.Cursor := L.First (Set.Items.all);
   begin
      while L.Has_Element (Index) loop
         Item := L.Element (Index);

         if Has_Type (Item, Mark) then
            return Item;
         end if;

         Index := L.Next (Index);
      end loop;

      raise Internal_Error;
   end Get_Type;

   ------------------------
   -- Has_Interpretation --
   ------------------------

   function Has_Interpretation
     (Set   : Up_Interpretation_Set;
      Item  : Asis.Element) return Boolean
   is
      use Asis.Gela.Errors;
   begin
      if Length (Set) = 0 then
         Report (Item, Error_No_Interprentation);
         return False;
      elsif Length (Set) > 1 then
         Report (Item, Error_Ambiguous_Interprentation);
      end if;
      return True;
   end Has_Interpretation;

   --------------
   -- Has_Type --
   --------------

   function Has_Type
     (Item   : Up_Interpretation;
      Mark   : Type_Info) return Boolean
   is
   begin
      case Item.Kind is
         when An_Expression =>
            if Is_Expected_Type (Item.Expression_Type, Mark) then
               return True;
            end if;
         when A_String_Type =>
            if Is_String (Mark) then
               return True;
            end if;
         when A_General_Access =>
            if Is_General_Access (Mark) then
               return True;
            end if;
         when A_Subprogram_Access =>
            if Is_Subprogram_Access (Mark) and then
               Conform_Access_Type (Item.Profile, Mark)
            then
               return True;
            end if;
         when An_Array_Aggregate =>
            if Is_Array (Mark) then
               return True;
            end if;
         when A_Record_Aggregate =>
            if not Is_Limited (Mark) and then
              (Is_Untagged_Record (Mark) or else Is_Tagged (Mark))
            then
               return True;
            end if;
         when An_Extension_Aggregate =>
            if not Is_Limited (Mark) and then Is_Tagged (Mark) then
               return True;
            end if;
         when A_Boolean =>
            if Is_Boolean (Mark) then
               return True;
            end if;
         when An_Object_Access =>
            if Is_Object_Access (Mark) and then
              Is_Covered (Item.Object_Type, Destination_Type (Mark)) then
               return True;
            end if;
         when others =>
            null;
      end case;
      return False;
   end Has_Type;

   --------------
   -- Has_Type --
   --------------

   function Has_Type
     (Set    : Up_Interpretation_Set;
      Mark   : Type_Info) return Boolean
   is
      Item  : Up_Interpretation;
      Index : L.Cursor := L.First (Set.Items.all);
   begin
      while L.Has_Element (Index) loop
         Item := L.Element (Index);

         if Has_Type (Item, Mark) then
            return True;
         end if;

         Index := L.Next (Index);
      end loop;
      return False;
   end Has_Type;

   -----------
   -- Image --
   -----------

   function Image (Set : Up_Interpretation_Set) return Wide_String is
      use type W.Unbounded_Wide_String;
      Result   : Unbounded_Wide_String;
      Index    : L.Cursor := L.First (Set.Items.all);
      New_Line : constant Wide_String := (1 => Wide_Character'Val (10));
   begin
      for I in 1 .. Length (Set) loop
         if I /= 1 then
            Result := Result & New_Line;
         end if;

         Result := Result & Positive'Wide_Image (I) & " " &
           Image (L.Element (Index));
         Index := L.Next (Index);
      end loop;

      return W.To_Wide_String (Result);
   end Image;

   -----------
   -- Image --
   -----------

   function Image (Object : Interpretation) return Wide_String is
--      use Asis.Elements;
      Kind : constant Wide_String :=
        Interpretation_Kinds'Wide_Image (Object.Kind) & " ";
   begin
      case Object.Kind is
         when An_Expression =>
            return Kind & Debug_Image (Object.Expression_Type);
         when An_Identifier =>
            return Kind & Debug_Image (Object.Identifier);
         when A_Declaration | A_Family_Member =>
            return Kind & Debug_Image (Object.Declaration);
         when A_Subprogram_Access =>
            return Kind & Debug_Image (Object.Profile);
         when An_Object_Access =>
            return Kind & Debug_Image (Object.Object_Type);
         when A_Subprogram_Reference =>
            return Kind & Debug_Image (Object.Access_Type);
         when A_Range =>
            return Kind & Debug_Image (Object.Range_Type);
         when A_Type =>
            return Kind & Debug_Image (Object.Type_Info);
         when A_Subaggregate =>
            return Kind & Debug_Image (Object.Array_Type) &
              Asis.List_Index'Wide_Image (Object.Deep);
         when An_Attribute_Function =>
            return Kind & Debug_Image (Object.Prefix) & " " &
              Asis.Attribute_Kinds'Wide_Image (Object.Attr_Kind);
         when others =>
            return Kind;
      end case;
   end Image;

   ---------------------------
   -- Is_Tagged_Non_Limited --
   ---------------------------

   function Is_Tagged_Non_Limited (Info : Type_Info) return Boolean is
   begin
      return Is_Tagged (Info) and then not Is_Limited (info);
   end Is_Tagged_Non_Limited;

   ------------
   -- Length --
   ------------

   function Length (Set   : Up_Interpretation_Set) return Natural is
   begin
      return Set.Length;
   end Length;

   ------------
   -- Length --
   ------------

   function Length (Set   : Stored_Set) return Natural is
   begin
      return Set.Length;
   end Length;

   ---------
   -- Put --
   ---------

   procedure Put
     (Set  : in out Stored_Sets;
      Key  : in     Asis.Element;
      Item : in     Stored_Set)
   is
   begin
      Item.Key := Key;
      S.Prepend (Set.all, Item);
   end Put;

   ------------------------
   -- Resolve_Identifier --
   ------------------------

   procedure Resolve_Identifier
     (Set    : in out Up_Interpretation_Set)
   is
      use Asis.Elements;
      use Asis.Expressions;

      Index : L.Cursor := L.First (Set.Items.all);
      Item  : Up_Interpretation;
   begin
      while L.Has_Element (Index) loop
         Item := L.Element (Index);

         if Item.Kind = An_Identifier then
            L.Delete (Set.Items.all, Index);
            Set.Length := Set.Length - 1;

            declare
               List : constant Asis.Defining_Name_List :=
                 Corresponding_Name_Definition_List (Item.Identifier);
            begin
               for I in List'Range loop
                  Add (Set, (A_Declaration, Enclosing_Element (List (I))));
               end loop;
            end;
         else
            Index := L.Next (Index);
         end if;
      end loop;

      Set.Index := 0;
   end Resolve_Identifier;

   ---------------------
   -- Select_Prefered --
   ---------------------

   procedure Select_Prefered (Set : in out Up_Interpretation_Set) is
      Has_Root_Int  : Boolean := False;
      Has_Root_Real : Boolean := False;
      Decl  : Asis.Declaration;
      Index : L.Cursor := L.First (Set.Items.all);
      Item  : Up_Interpretation;
      Tipe  : Type_Info;
   begin
      while L.Has_Element (Index) loop
         Item := L.Element (Index);

         if Item.Kind = An_Expression or Item.Kind = A_Range then
            if Item.Kind = An_Expression then
               Tipe := Item.Expression_Type;
            else
               Tipe := Item.Range_Type;
            end if;

            Decl := Get_Declaration (Tipe);

            if Is_Equal (Decl, XASIS.Types.Root_Integer) then
               Has_Root_Int := True;
            elsif Is_Equal (Decl, XASIS.Types.Root_Real) then
               Has_Root_Real := True;
            end if;
         end if;

         Index := L.Next (Index);
      end loop;

      if not Has_Root_Int and not Has_Root_Real then
         return;
      end if;

      Index := L.First (Set.Items.all);

      while L.Has_Element (Index) loop
         Item := L.Element (Index);

         if Item.Kind = An_Expression or Item.Kind = A_Range then
            if Item.Kind = An_Expression then
               Tipe := Item.Expression_Type;
            else
               Tipe := Item.Range_Type;
            end if;

            Decl := Get_Declaration (Tipe);

            if Is_Equal (Decl, XASIS.Types.Root_Integer) then
               Index := L.Next (Index);
            elsif Has_Root_Int and then Is_Integer (Tipe) then
               L.Delete (Set.Items.all, Index);
               Set.Length := Set.Length - 1;
            elsif Is_Equal (Decl, XASIS.Types.Root_Real) then
               Index := L.Next (Index);
            elsif Has_Root_Real and then Is_Real (Tipe) then
               L.Delete (Set.Items.all, Index);
               Set.Length := Set.Length - 1;
            else
               Index := L.Next (Index);
            end if;
         else
            Index := L.Next (Index);
         end if;
      end loop;

      Set.Index := 0;
   end Select_Prefered;

   --------------
   -- Set_Next --
   --------------

   procedure Set_Next (Left, Next : Stored_Set) is
   begin
      Left.Next := Next;
   end Set_Next;

   ----------------------------
   -- To_Down_Interpretation --
   ----------------------------

   function To_Down_Interpretation
     (Item : Up_Interpretation) return Down_Interpretation
   is
   begin
      if Item.Kind in Up_Only_Kinds then
         raise Internal_Error;
      end if;

      return Down_Interpretation (Item);
   end To_Down_Interpretation;

   -------------------
   -- Up_Expression --
   -------------------

   function Up_Expression
     (Expression_Type : Asis.Element;
      Place           : Asis.Element)
      return Up_Interpretation
   is
      use Asis.Elements;
      Tipe : Type_Info;
   begin
      case Element_Kind (Expression_Type) is
         when A_Declaration =>
            case Declaration_Kind (Expression_Type) is
               when An_Ordinary_Type_Declaration
                 | A_Private_Type_Declaration
                 | A_Formal_Type_Declaration
                 | A_Subtype_Declaration =>
                  Tipe := Type_From_Declaration (Expression_Type, Place);
               when others =>
                  raise Unimplemented;
            end case;
         when A_Definition =>
            case Definition_Kind (Expression_Type) is
               when A_Type_Definition
                 | A_Subtype_Indication
                 | A_Discrete_Subtype_Definition
                 =>
                  Tipe := Type_From_Indication (Expression_Type, Place);
               when others =>
                  raise Unimplemented;
            end case;
         when An_Expression =>
            case Expression_Kind (Expression_Type) is
               when An_Identifier
                 | A_Selected_Component
                 | An_Attribute_Reference
                 =>
                  Tipe := Type_From_Subtype_Mark (Expression_Type, Place);
               when others =>
                  raise Unimplemented;
            end case;
         when others =>
            raise Unimplemented;
      end case;

      return (An_Expression, Tipe);
   end Up_Expression;

   -------------------
   -- Up_Expression --
   -------------------

   function Up_Expression (Info : Type_Info) return Up_Interpretation is
   begin
      return (An_Expression, Info);
   end Up_Expression;

end Asis.Gela.Overloads.Types;



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
