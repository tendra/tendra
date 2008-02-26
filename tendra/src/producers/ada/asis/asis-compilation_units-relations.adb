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

------------------------------------------------------------------------------
--                      Implementation restriction                          --
--             not implemented Inconsistent list generation                 --
------------------------------------------------------------------------------

with Ada.Finalization;
with Ada.Unchecked_Deallocation;
with System;

with Asis.Errors;             use Asis.Errors;
with Asis.Exceptions;
with Asis.Implementation;
with Asis.Elements;
with Asis.Ada_Environments;
with Asis.Clauses;
with Asis.Expressions;
with Asis.Iterator;
with Ada.Wide_Text_IO;

package body Asis.Compilation_Units.Relations is

   package Utils is

      --  Compilation_Unit_List_Access  --
      type Compilation_Unit_List_Access is
        access all Compilation_Unit_List;

      procedure Deallocate is
        new Ada.Unchecked_Deallocation
          (Compilation_Unit_List, Compilation_Unit_List_Access);

      function In_List
        (List : in Compilation_Unit_List_Access;
         Last : in ASIS_Integer;
         Unit : in Compilation_Unit)
         return Boolean;

      function Append
        (List : in Compilation_Unit_List_Access;
         Unit : in Compilation_Unit)
         return Compilation_Unit_List_Access;

      function Append
        (List  : in Compilation_Unit_List_Access;
         Units : in Compilation_Unit_List)
         return Compilation_Unit_List_Access;

      procedure Remove_From_List
        (List : in out Compilation_Unit_List_Access;
         Unit : in     Compilation_Unit);

      procedure Remove_From_List
        (List : in out Compilation_Unit_List;
         From : in     List_Index;
         Unit : in     Compilation_Unit);

      -- Tree --
      type Root_Tree is
        new Ada.Finalization.Limited_Controlled with private;

      type Root_Tree_Access is access all Root_Tree;

      type Tree_Node is
        new Ada.Finalization.Limited_Controlled with private;

      type Tree_Node_Access is access all Tree_Node;

      --  Tree_Node_Array  --
      type Tree_Node_Array is array (Positive range <>) of Tree_Node_Access;
      type Tree_Node_Array_Access is access all Tree_Node_Array;

      procedure Deallocate is
        new Ada.Unchecked_Deallocation
          (Tree_Node_Array, Tree_Node_Array_Access);

      function Append
        (List : in Tree_Node_Array_Access;
         Node : in Tree_Node_Access)
         return Tree_Node_Array_Access;

      function In_List
        (List : in Tree_Node_Array_Access;
         Last : in Natural;
         Node : in Tree_Node_Access)
         return Boolean;

      -- Root_Tree --
      type Orders is (Ascending, Descending);

      procedure Dependence_Order
        (This  : in Root_Tree_Access;
         Order : in Orders);

      function Add_Child
        (This : in Root_Tree_Access;
         Node : in Tree_Node_Access;
         Unit : in Compilation_Unit)
         return Tree_Node_Access;

      function Add_Child
        (This      : in Root_Tree_Access;
         Node      : in Tree_Node_Access;
         Spec_Unit : in Compilation_Unit;
         Body_Unit : in Compilation_Unit;
         Skip_Spec : in Boolean := False)
         return Tree_Node_Access;

      function Add_Subunit
        (This : in Root_Tree_Access;
         Node : in Tree_Node_Access;
         Unit : in Compilation_Unit)
         return Tree_Node_Access;

      procedure Append
        (This : in Root_Tree_Access;
         Unit : in Compilation_Unit);

      procedure Glue_Nodes
        (This    : in Root_Tree_Access;
         Node    : in Tree_Node_Access;
         To_Node : in Tree_Node_Access);

      procedure Glue_Nodes_Checked
        (This    : in Root_Tree_Access;
         Node    : in Tree_Node_Access;
         To_Node : in Tree_Node_Access);

      procedure Set_Parent
        (This   : in Root_Tree_Access;
         Node   : in Tree_Node_Access;
         Parent : in Tree_Node_Access);

      procedure Clear
        (This : in out Root_Tree);

      procedure Add_Body_Dependents
        (This    : in Root_Tree_Access;
         Node    : in Tree_Node_Access;
         To_Node : in Tree_Node_Access);

      function Find
        (This : in Root_Tree_Access;
         Unit : in Compilation_Unit)
         return Tree_Node_Access;

      procedure Check
        (This        : in Root_Tree_Access;
         The_Context : in Asis.Context);

      function Generate_Relationship
        (This       : in Root_Tree_Access;
         Limit_List : in Utils.Compilation_Unit_List_Access;
         List_Last  : in ASIS_Integer)
         return Relationship;

      function Create_Elaboration_Tree
        (This        : in Root_Tree_Access;
         The_Context : in Asis.Context)
         return Root_Tree_Access;

      function Is_Child
        (This : in Root_Tree_Access;
         Node : in Tree_Node_Access)
        return Boolean;

      function Is_Have_Circular_Dependences
        (This : in Root_Tree_Access)
         return Boolean;

      -- Tree_Node --
      function Is_Skip_Spec
        (This : in Tree_Node_Access)
         return Boolean;

      procedure Skip_Spec
        (This  : in Tree_Node_Access;
         Value : in Boolean);

      function Nexts
        (This : in Tree_Node_Access)
         return Tree_Node_Array_Access;

      function Get_Spec
        (This : in Tree_Node_Access)
         return Compilation_Unit;

      function Get_Body
        (This : in Tree_Node_Access)
         return Compilation_Unit;

      Use_Error : exception;

   private

      -- Tree_Node --
      type Extended_Boolean is (Unknown, Extended_True, Extended_False);

      type Tree_Node is
        new Ada.Finalization.Limited_Controlled with record
         Self : Tree_Node_Access := Tree_Node'Unchecked_Access;

         --  ссылка на предыдущие елементы
         Prevs : Tree_Node_Array_Access := null;

         --  последующие елементы
         Next : Tree_Node_Array_Access := null;

         --  модуль_компиляции
         Unit      : Compilation_Unit := Nil_Compilation_Unit;
         Unit_Body : Compilation_Unit := Nil_Compilation_Unit;
         Skip_Spec : Boolean := False;

         Added      : Boolean := False;

         Consistent      : Boolean := True;
         Body_Consistent : Boolean := True;

         --  зависимости тела (with)
         Body_Dependences : Tree_Node_Array_Access := null;

         --  список циклических зависимостей
         Circular       : Compilation_Unit_List_Access := null;
         Circular_Added : Boolean := False;

         --  список пропавших юнитов
         Missing       : Compilation_Unit_List_Access := null;
         Missing_Added : Boolean := False;

         --  список несоглассованных юнитов
         Inconsistent       : Compilation_Unit_List_Access := null;
         Inconsistent_Added : Boolean := False;

         Elaborated      : Boolean := False;
         Body_Elaborated : Boolean := False;

         Internal_Pure           : Extended_Boolean := Unknown;
         Internal_Preelaborate   : Extended_Boolean := Unknown;
         Internal_Spec_With_Body : Extended_Boolean := Unknown;
      end record;

      procedure Finalize
        (This : in out Tree_Node);

      function Is_Pure
        (This : in Tree_Node_Access)
         return Boolean;

      function Is_Preelaborate
        (This : in Tree_Node_Access)
         return Boolean;

      function Is_Elaborate_Body
        (This : in Tree_Node_Access)
         return Boolean;

      procedure Retrive_Pragmas
        (This : in Tree_Node_Access);

      -- Root_Tree --

      type Unit_Node is record
         Unit : Compilation_Unit;
         Node : Tree_Node_Access;
      end record;

      type Unit_Node_Array is array (Positive range <>) of Unit_Node;
      type Unit_Node_Array_Access is access all Unit_Node_Array;

      type Root_Tree is
        new Ada.Finalization.Limited_Controlled with record
         Self  : Root_Tree_Access := Root_Tree'Unchecked_Access;

         Order : Orders := Descending;
         Next  : Tree_Node_Array_Access := null;

         --  сортированный список всех
         --  елементов для быстрого
         --  определения наличия елемента
         --  в списке
         Units : Unit_Node_Array_Access := null;

         Last_Node : Tree_Node_Access := null;
      end record;

      procedure Finalize
        (This : in out Root_Tree);

      -- Additional --
      procedure Deallocate is
        new Ada.Unchecked_Deallocation
          (Tree_Node, Tree_Node_Access);

      procedure Deallocate is
        new Ada.Unchecked_Deallocation
          (Unit_Node_Array, Unit_Node_Array_Access);

      type Positive_Access is access all Positive;

      function Add_Node
        (List : in Tree_Node_Array_Access;
         Node : in Tree_Node_Access)
         return Tree_Node_Array_Access;

      procedure Remove
        (List : in out Tree_Node_Array_Access;
         Node : in     Tree_Node_Access);

      function Remove
        (List : in Tree_Node_Array_Access;
         Node : in Tree_Node_Access)
         return Tree_Node_Array_Access;

      function Add_Node_Ordered
        (List : in Unit_Node_Array_Access;
         Node : in Tree_Node_Access)
         return Unit_Node_Array_Access;

      function Find
        (List  : in Unit_Node_Array_Access;
         Unit  : in Compilation_Unit;
         From  : in Positive;
         To    : in Positive;
         Index : in Positive_Access)
         return Boolean;

      function Compare
        (Left  : in Compilation_Unit;
         Right : in Compilation_Unit)
         return Integer;

      function Is_Inconsistent
        (Unit : in Compilation_Unit)
         return Boolean;

      function Is_Source_Changed
        (Unit : in Compilation_Unit)
         return Boolean;

   end Utils;

   procedure Deallocate is
     new Ada.Unchecked_Deallocation
       (Utils.Root_Tree, Utils.Root_Tree_Access);

   procedure Check_Compilation_Unit
     (Unit        : in Compilation_Unit;
      The_Context : in Asis.Context;
      Message     : in Wide_String);

   procedure Normalize
     (List   : in     Asis.Compilation_Unit_List;
      Result : in     Utils.Compilation_Unit_List_Access;
      Last   :    out ASIS_Integer);

   function Get_Ancestors
     (List        : in Asis.Compilation_Unit_List;
      The_Context : in Asis.Context)
      return Utils.Root_Tree_Access;

   function Get_Descendants
     (List        : in Asis.Compilation_Unit_List;
      The_Context : in Asis.Context)
      return Utils.Root_Tree_Access;

   function Get_Supporters
     (List        : in Asis.Compilation_Unit_List;
      The_Context : in Asis.Context)
      return Utils.Root_Tree_Access;

   function Get_Dependents
     (List        : in Asis.Compilation_Unit_List;
      The_Context : in Asis.Context)
      return Utils.Root_Tree_Access;

   function Get_Family
     (List        : in Asis.Compilation_Unit_List;
      The_Context : in Asis.Context)
      return Utils.Root_Tree_Access;

   function Get_Needed_Units
     (List        : in Asis.Compilation_Unit_List;
      The_Context : in Asis.Context)
      return Utils.Root_Tree_Access;

   procedure Get_Subunits
     (Tree        : in Utils.Root_Tree_Access;
      Unit        : in Compilation_Unit;
      Node        : in Utils.Tree_Node_Access;
      The_Context : in Asis.Context);

   function Get_Compilation_Unit
     (Unit        : in Compilation_Unit;
      Target      : in Asis.Element;
      Number      : in List_Index;
      The_Context : in Asis.Context)
      return Asis.Compilation_Unit;

   function Have_With
     (Library     : in Compilation_Unit;
      Unit        : in Compilation_Unit;
      The_Context : in Asis.Context)
      return Boolean;

   type Check_10_1_1_26c_26b_Information is record
      Exceptions : Boolean := False;
      System     : Boolean := False;
   end record;

   function Check_10_1_1_26c_26b
     (Unit        : in Compilation_Unit;
      The_Context : in Asis.Context)
      return Check_10_1_1_26c_26b_Information;

   ----------------------------
   -- Check_Compilation_Unit --
   ----------------------------

   procedure Check_Compilation_Unit
     (Unit        : in Compilation_Unit;
      The_Context : in Asis.Context;
      Message     : in Wide_String)
   is
      Kind : Asis.Unit_Kinds;
   begin
      Kind := Unit_Kind (Unit);

      if Kind = Not_A_Unit
         or else Kind = A_Nonexistent_Declaration
         or else Kind = A_Nonexistent_Body
         or else Kind = A_Configuration_Compilation
      then
         Asis.Implementation.Set_Status
           (Data_Error, Message & " invalid unit " & Unit_Full_Name (Unit));

         raise Asis.Exceptions.ASIS_Inappropriate_Compilation_Unit;
      end if;

      if not Asis.Ada_Environments.Is_Equal
        (Enclosing_Context (Unit), The_Context)
      then
         Asis.Implementation.Set_Status
           (Data_Error, Message & " invalid unit's context "
            & Unit_Full_Name (Unit));

         raise Asis.Exceptions.ASIS_Inappropriate_Compilation_Unit;
      end if;
   end Check_Compilation_Unit;

   ---------------
   -- Normalize --
   ---------------

   procedure Normalize
     (List   : in     Asis.Compilation_Unit_List;
      Result : in     Utils.Compilation_Unit_List_Access;
      Last   :    out ASIS_Integer)
   is
      Unit : Compilation_Unit;
   begin
      Last := 0;

      for Index in List'Range loop
         Unit := List (Index);

         if not Is_Nil (Unit)
            and then Unit_Kind (Unit) /= An_Unknown_Unit
         then
            if not Utils.In_List (Result, Last, Unit) then
               Last := Last + 1;
               Result (Last) := List (Index);
            end if;
         end if;
      end loop;
   end Normalize;

   -------------------------
   --  Elaboration_Order  --
   -------------------------

   function Elaboration_Order
     (Compilation_Units : in Asis.Compilation_Unit_List;
      The_Context       : in Asis.Context)
      return Relationship
   is
      procedure Clear;

      Tree           : Utils.Root_Tree_Access := null;
      Elaborate_Tree : Utils.Root_Tree_Access := null;

      Compilation_Units_Last : ASIS_Integer := 0;

      Normalized_Compilation_Units :
         Utils.Compilation_Unit_List_Access := null;

      -- Clear --
      procedure Clear is
      begin
         Deallocate (Tree);
         Deallocate (Elaborate_Tree);
         Utils.Deallocate (Normalized_Compilation_Units);
      end Clear;
   begin
      if Compilation_Units = Nil_Compilation_Unit_List then
         return Nil_Relationship;
      end if;

      for Index in Compilation_Units'Range loop
         Check_Compilation_Unit
           (Compilation_Units (Index), The_Context,
            "Elaboration_Order:Compilation_Unit");
      end loop;

      Normalized_Compilation_Units := new
        Asis.Compilation_Unit_List (1 .. Compilation_Units'Length);

      Normalized_Compilation_Units.all := (others => Nil_Compilation_Unit);

      Normalize (Compilation_Units,
                 Normalized_Compilation_Units,
                 Compilation_Units_Last);

      Tree := Get_Needed_Units
         (Normalized_Compilation_Units (1 .. Compilation_Units_Last),
          The_Context);

      Utils.Check (Tree, The_Context);

      if Utils.Is_Have_Circular_Dependences (Tree) then
         Clear;

         Asis.Implementation.Set_Status
           (Data_Error, "Elaboration_Order - "
            & "Circular semantic dependence detected, can not create "
            & "elaboration order");

         raise Asis.Exceptions.ASIS_Failed;
      end if;

      Elaborate_Tree := Utils.Create_Elaboration_Tree (Tree, The_Context);

      declare
         Relation : Relationship := Utils.Generate_Relationship
            (Elaborate_Tree, null, 0);
      begin
         Clear;
         return Relation;
      end;

   exception
      when others =>
         Clear;
         raise;
   end Elaboration_Order;

   ---------------------------------
   --  Semantic_Dependence_Order  --
   ---------------------------------

   function Semantic_Dependence_Order
     (Compilation_Units : in Asis.Compilation_Unit_List;
      Dependent_Units   : in Asis.Compilation_Unit_List;
      The_Context       : in Asis.Context;
      Relation          : in Asis.Relation_Kinds)
      return Relationship
   is
      procedure Clear;

      Compilation_Units_Last : ASIS_Integer := 0;

      Normalized_Compilation_Units :
         Utils.Compilation_Unit_List_Access := null;

      Dependent_Units_Last : ASIS_Integer := 0;

      Normalized_Dependent_Units :
         Utils.Compilation_Unit_List_Access := null;

      Tree : Utils.Root_Tree_Access := null;

      procedure Clear is begin
         Deallocate (Tree);
         Utils.Deallocate (Normalized_Compilation_Units);
         Utils.Deallocate (Normalized_Dependent_Units);
      end Clear;

   begin
      if Compilation_Units = Nil_Compilation_Unit_List then
         return Nil_Relationship;
      end if;

      for Index in Compilation_Units'Range loop
         Check_Compilation_Unit
           (Compilation_Units (Index), The_Context,
            "Semantic_Dependence_Order:Compilation_Unit");
      end loop;

      Normalized_Compilation_Units := new
        Asis.Compilation_Unit_List (1 .. Compilation_Units'Length);

      Normalized_Compilation_Units.all := (others => Nil_Compilation_Unit);

      Normalize (Compilation_Units,
                 Normalized_Compilation_Units,
                 Compilation_Units_Last);

      --  Dependent_Units are ignored unless the Relation
      --  is Descendants or Dependents
      if (Relation = Descendants or else Relation = Dependents)
         and then Dependent_Units /= Nil_Compilation_Unit_List
      then
         for Index in Dependent_Units'Range loop
            Check_Compilation_Unit
               (Dependent_Units (Index), The_Context,
                "Semantic_Dependence_Order:Dependent_Unit");
         end loop;

         Normalized_Dependent_Units := new
           Asis.Compilation_Unit_List (1 .. Dependent_Units'Length);

         Normalized_Dependent_Units.all := (others => Nil_Compilation_Unit);

         Normalize (Dependent_Units,
                    Normalized_Dependent_Units,
                    Dependent_Units_Last);
      end if;

      case Relation is
         when Ancestors =>
            Tree := Get_Ancestors
              (Normalized_Compilation_Units (1 .. Compilation_Units_Last),
               The_Context);

         when Descendants =>
            Tree := Get_Descendants
              (Normalized_Compilation_Units
                 (1 .. Compilation_Units_Last), The_Context);

         when Supporters =>
            Tree := Get_Supporters
              (Normalized_Compilation_Units (1 .. Compilation_Units_Last),
               The_Context);

         when Dependents =>
            Tree := Get_Dependents
              (Normalized_Compilation_Units (1 .. Compilation_Units_Last),
               The_Context);

         when Family =>
            Tree := Get_Family
              (Normalized_Compilation_Units (1 .. Compilation_Units_Last),
               The_Context);

         when Needed_Units =>
            Tree := Get_Needed_Units
              (Normalized_Compilation_Units (1 .. Compilation_Units_Last),
               The_Context);
      end case;

      Utils.Check (Tree, The_Context);
      declare
         Relation : Relationship := Utils.Generate_Relationship
            (Tree, Normalized_Dependent_Units, Dependent_Units_Last);
      begin
         Clear;
         return Relation;
      end;

   exception
      when others =>
         Clear;
         raise;
   end Semantic_Dependence_Order;

   -------------------
   -- Get_Ancestors --
   -------------------

   function Get_Ancestors
     (List        : in Asis.Compilation_Unit_List;
      The_Context : in Asis.Context)
      return Utils.Root_Tree_Access
   is
      use Utils;

      Unit  : Compilation_Unit;
      Kinds : Unit_Kinds;

      Result : Root_Tree_Access := new Root_Tree;

      procedure Append_Node
        (Unit : in     Compilation_Unit;
         Node : in out Tree_Node_Access);

      procedure Retrive
        (Unit : in Compilation_Unit;
         Node : in Tree_Node_Access);

      -- Append_Node --
      procedure Append_Node
        (Unit : in     Compilation_Unit;
         Node : in out Tree_Node_Access)
      is
         Exist_Node : Tree_Node_Access;
      begin
         Exist_Node := Find (Result, Unit);

         if Exist_Node /= null then
            Glue_Nodes (Result, Node, Exist_Node);
            Node := null;
         else
            Node := Add_Child (Result, Node, Unit);
         end if;
      end Append_Node;

      -- Retrive --
      procedure Retrive
        (Unit : in Compilation_Unit;
         Node : in Tree_Node_Access)
      is
         Internal_Node : Tree_Node_Access := Node;
         Internal_Unit : Compilation_Unit := Unit;
      begin
         while Unit_Kind (Internal_Unit) in
           A_Procedure .. A_Generic_Package_Renaming
         loop
            Append_Node (Internal_Unit, Internal_Node);
            if Internal_Node = null then
               return;
            end if;

            Internal_Unit := Corresponding_Parent_Declaration (Internal_Unit);
         end loop;

         if not Is_Nil (Internal_Unit) then
            Append_Node (Internal_Unit, Internal_Node);
            if Internal_Node = null then
               return;
            end if;

            --  add Standart as root
            Append_Node
               (Library_Unit_Declaration ("Standard", The_Context),
                Internal_Node);
         end if;
      end Retrive;

   begin
      Dependence_Order (Result, Ascending);

      for Index in List'Range loop
         Unit := List (Index);

         if Find (Result, Unit) = null then
            Kinds := Unit_Kind (Unit);

            if Kinds in A_Subunit then
               Asis.Implementation.Set_Status
                 (Data_Error, "Subunit not valid for Ancestors request "
                  & Unit_Full_Name (Unit));

               raise Asis.Exceptions.ASIS_Inappropriate_Compilation_Unit;

            elsif Kinds in A_Library_Unit_Body then
               Unit := Corresponding_Parent_Declaration (Unit, The_Context);
            end if;

            Retrive (Unit, null);
         end if;
      end loop;

      return Result;
   exception
      when others =>
         Deallocate (Result);
         raise;
   end Get_Ancestors;

   ---------------------
   -- Get_Descendants --
   ---------------------

   function Get_Descendants
     (List        : in Asis.Compilation_Unit_List;
      The_Context : in Asis.Context)
      return Utils.Root_Tree_Access
   is
      use Utils;

      Result      : Root_Tree_Access := new Root_Tree;
      Unit        : Compilation_Unit;
      Second_Unit : Compilation_Unit;
      Kinds       : Unit_Kinds;

      procedure Retrive
        (Target : in Compilation_Unit;
         Node   : in Utils.Tree_Node_Access);

      -- Retrive --
      procedure Retrive
        (Target : in Compilation_Unit;
         Node   : in Utils.Tree_Node_Access)
      is
         function Process
           (Index : in List_Index)
            return Boolean;

         Exist_Node : Utils.Tree_Node_Access := null;

         Children_List : Asis.Compilation_Unit_List :=
            Corresponding_Children (Target, The_Context);

         -- Process --
         function Process
           (Index : in List_Index)
            return Boolean
         is
         begin
            Kinds       := Unit_Kind (Unit);
            Exist_Node  := Find (Result, Unit);
            Second_Unit := Nil_Compilation_Unit;

            if Exist_Node /= null then
               Glue_Nodes (Result, Node, Exist_Node);

               if Kinds in A_Procedure .. A_Generic_Package then
                  Second_Unit := Corresponding_Body (Unit, The_Context);

               elsif Kinds in A_Library_Unit_Body then
                  Second_Unit := Corresponding_Declaration (Unit, The_Context);
               end if;

               if not Is_Nil (Second_Unit)
                 and then not Is_Identical (Second_Unit, Unit)
               then
                  Remove_From_List (Children_List, Index + 1, Second_Unit);
               end if;

               return False;
            end if;

            if Kinds in
              A_Procedure_Instance .. A_Generic_Package_Renaming
            then
               Exist_Node := Add_Child (Result, Node, Unit);

            elsif Kinds in A_Procedure .. A_Generic_Package then
               Second_Unit := Corresponding_Body (Unit, The_Context);

               if not Is_Nil (Second_Unit)
                 and then not Is_Identical (Second_Unit, Unit)
               then
                  Exist_Node := Add_Child (Result, Node, Unit, Second_Unit);
                  Remove_From_List (Children_List, Index + 1, Second_Unit);
               else
                  Exist_Node := Add_Child (Result, Node, Unit);
               end if;

            elsif Kinds in A_Library_Unit_Body then
               Second_Unit := Corresponding_Declaration (Unit, The_Context);

               if not Is_Nil (Second_Unit)
                  and then not Is_Identical (Second_Unit, Unit)
               then
                  Exist_Node := Add_Child (Result, Node, Second_Unit, Unit);

                  Remove_From_List (Children_List, Index + 1, Second_Unit);
                  Unit := Second_Unit;
               else
                  Exist_Node := Add_Child (Result, Node, Unit);
               end if;

            else
               Exist_Node := Add_Child (Result, Node, Unit);
            end if;

            return True;
         end Process;

      begin
         for Index in Children_List'Range loop
            Unit := Children_List (Index);

            if not Is_Nil (Unit) then
               if Process (Index) then
                  Kinds := Unit_Kind (Unit);

                  if Kinds = A_Package
                    or else Kinds = A_Generic_Package
                    or else Kinds = A_Package_Instance
                  then
                     Retrive (Unit, Exist_Node);
                  end if;
               end if;
            end if;
         end loop;
      end Retrive;

      Declarations_List :
        Utils.Compilation_Unit_List_Access := null;

      Declarations_Last : ASIS_Integer := 0;

   begin
      Dependence_Order (Result, Descending);

      Declarations_List := new Asis.Compilation_Unit_List (1 .. List'Length);

      for Index in List'Range loop
         Unit  := List (Index);
         Kinds := Unit_Kind (Unit);

         if Kinds in A_Subunit then
            Asis.Implementation.Set_Status
              (Data_Error, "Subunit not valid for Descendants request "
               & Unit_Full_Name (Unit));
         end if;

         if Kinds in A_Library_Unit_Body then
            Unit  := Corresponding_Declaration (Unit);
            Kinds := Unit_Kind (Unit);
         end if;

         if Kinds = A_Package
           or else Kinds = A_Generic_Package
           or else Kinds = A_Package_Instance
         then
            if not In_List (Declarations_List, Declarations_Last, Unit) then
               Declarations_Last := Declarations_Last + 1;
               Declarations_List (Declarations_Last) := Unit;
            end if;
         end if;
      end loop;

      for Index in 1 .. Declarations_Last loop
         Unit := Declarations_List (Index);

         if Find (Result, Unit) = null then
            Second_Unit := Corresponding_Body (Unit, The_Context);

            if not Is_Nil (Second_Unit)
              and then not Is_Identical (Second_Unit, Unit)
            then
               Retrive (Unit, Add_Child (Result, null, Unit, Second_Unit));
            else
               Retrive (Unit, Add_Child (Result, null, Unit));
            end if;
         end if;
      end loop;

      Deallocate (Declarations_List);
      return Result;

   exception
      when others =>
         Deallocate (Declarations_List);
         Deallocate (Result);
         raise;
   end Get_Descendants;

   --------------------
   -- Get_Supporters --
   --------------------

   function Get_Supporters
     (List        : in Asis.Compilation_Unit_List;
      The_Context : in Asis.Context)
      return Utils.Root_Tree_Access
   is
      use Utils;

      Unit  : Compilation_Unit;
      Kinds : Unit_Kinds;

      Result : Root_Tree_Access := new Root_Tree;
      Node   : Tree_Node_Access := null;

      Std : Compilation_Unit :=
        Library_Unit_Declaration ("Standard", The_Context);

      procedure Append_Unit
        (Unit : in     Compilation_Unit;
         Node : in out Tree_Node_Access);

      procedure Retrive
        (Unit       : in Compilation_Unit;
         Node       : in Tree_Node_Access;
         First_Node : in Boolean := False);

      procedure Retrive_Declarations
        (Unit       : in Compilation_Unit;
         Node       : in Tree_Node_Access;
         First_Node : in Boolean);

      procedure Retrive_Body
        (Unit       : in Compilation_Unit;
         Node       : in Tree_Node_Access;
         First_Node : in Boolean);

      procedure Retrive_Subunit
        (Unit : in Compilation_Unit;
         Node : in Tree_Node_Access);

      procedure Retrive_With_Clause
        (Unit     : in Compilation_Unit;
         Node     : in Tree_Node_Access;
         For_Body : in Boolean := False);

      procedure Check_10_1_1_26c_26b
        (Unit     : in Compilation_Unit;
         Node     : in Tree_Node_Access;
         For_Body : in Boolean := False);

      -- Append_Unit --
      procedure Append_Unit
        (Unit : in     Compilation_Unit;
         Node : in out Tree_Node_Access)
      is
         Exist_Node : Tree_Node_Access;
      begin
         Exist_Node := Find (Result, Unit);

         if Exist_Node = null then
            Node := Add_Child (Result, Node, Unit);
         else
            if Node /= null then
               Glue_Nodes_Checked (Result, Node, Exist_Node);
               Node := null;
            end if;
         end if;
      end Append_Unit;

      -- Retrive --
      procedure Retrive
        (Unit       : in Compilation_Unit;
         Node       : in Tree_Node_Access;
         First_Node : in Boolean := False)
      is
         Internal_Node : Tree_Node_Access := Node;
      begin
         if Is_Nil (Unit) then
            return;
         end if;

         Kinds := Unit_Kind (Unit);

         if Kinds in A_Nonexistent_Declaration .. An_Unknown_Unit then
            Append_Unit (Std, Internal_Node);

         elsif Kinds in A_Subunit then
            Retrive_Subunit (Unit, Node);

         elsif Kinds in A_Procedure_Body .. A_Package_Body then
            Retrive_Body (Unit, Node, First_Node);

         else
            Retrive_Declarations (Unit, Node, First_Node);
         end if;
      end Retrive;

      -- Retrive_Declarations --
      procedure Retrive_Declarations
        (Unit       : in Compilation_Unit;
         Node       : in Tree_Node_Access;
         First_Node : in Boolean)
      is
         Parent         : Compilation_Unit;
         Internal_Node  : Tree_Node_Access := Node;
      begin
         if not First_Node then
            Append_Unit (Unit, Internal_Node);

            if Internal_Node = null then
               return;
            end if;
         end if;

         if Is_Identical (Unit, Std) then
            return;
         end if;

         Check_10_1_1_26c_26b (Unit, Internal_Node);
         Retrive_With_Clause (Unit, Internal_Node);

         Parent := Corresponding_Parent_Declaration (Unit, The_Context);

         while Unit_Kind (Parent) in
           A_Procedure .. A_Generic_Package_Renaming
         loop
            Append_Unit (Parent, Internal_Node);

            if Internal_Node = null
               or else Is_Identical (Unit, Std)
            then
               return;
            end if;

            Check_10_1_1_26c_26b (Parent, Internal_Node);
            Retrive_With_Clause (Parent, Internal_Node);

            Parent := Corresponding_Parent_Declaration (Parent, The_Context);
         end loop;

         Retrive (Parent, Internal_Node);
      end Retrive_Declarations;

      -- Retrive_Body --
      procedure Retrive_Body
        (Unit       : in Compilation_Unit;
         Node       : in Tree_Node_Access;
         First_Node : in Boolean)
      is
         Internal_Node : Tree_Node_Access := Node;
      begin
         if not First_Node then
            Append_Unit (Unit, Internal_Node);

            if Internal_Node = null then
               return;
            end if;
         end if;

         Check_10_1_1_26c_26b (Unit, Internal_Node, True);
         Retrive_With_Clause (Unit, Internal_Node, True);

         Retrive
           (Corresponding_Parent_Declaration (Unit, The_Context),
            Internal_Node);
      end Retrive_Body;

      --  Retrive_Subunit  --
      procedure Retrive_Subunit
        (Unit : in Compilation_Unit;
         Node : in Tree_Node_Access)
      is
         Parent : Compilation_Unit;
         vNode  : Tree_Node_Access := Node;
      begin
         Check_10_1_1_26c_26b (Unit, null, True);
         Retrive_With_Clause (Unit, null, True);

         Parent := Corresponding_Subunit_Parent_Body (Unit);

         while Unit_Kind (Parent) in A_Subunit loop
            Append_Unit (Unit, vNode);

            if vNode = null then
               return;
            end if;

            Check_10_1_1_26c_26b (Parent, vNode, True);
            Retrive_With_Clause (Parent, vNode, True);

            Parent := Corresponding_Subunit_Parent_Body (Parent);
         end loop;

         Retrive (Parent, vNode);
      end Retrive_Subunit;

      -- Retrive_With_Clause --
      procedure Retrive_With_Clause
        (Unit     : in Compilation_Unit;
         Node     : in Tree_Node_Access;
         For_Body : in Boolean := False)
      is
         With_List : constant Asis.Context_Clause_List :=
           Asis.Elements.Context_Clause_Elements (Unit);

         Internal_Unit : Compilation_Unit;
         Exist_Node    : Tree_Node_Access;
      begin
         for Index in With_List'Range loop
            if Clause_Kind (With_List (Index).all) = A_With_Clause then

               Internal_Unit := Get_Compilation_Unit
                  (Unit, With_List (Index), Index, The_Context);

               if not Is_Nil (Internal_Unit) then
                  if not For_Body then
                     Retrive (Internal_Unit, Node);
                  else
                     Exist_Node := Find (Result, Internal_Unit);

                     if Exist_Node = null then
                        Exist_Node := Add_Child (Result, null, Internal_Unit);

                        if Node /= null then
                           Add_Body_Dependents (Result, Exist_Node, Node);
                        end if;

                        Retrive (Internal_Unit, Exist_Node, True);
                     else
                        if Node /= null then
                           Add_Body_Dependents (Result, Exist_Node, Node);
                        end if;
                     end if;
                  end if;
               end if;
            end if;
         end loop;
      end Retrive_With_Clause;

      -- Check_10_1_1_26c_26b --
      procedure Check_10_1_1_26c_26b
        (Unit     : in Compilation_Unit;
         Node     : in Tree_Node_Access;
         For_Body : in Boolean := False)
      is
         procedure Retrive_For_Body
           (Unit : in Compilation_Unit);

         Except : Compilation_Unit := Library_Unit_Declaration
            ("Ada.Exceptions", The_Context);

         Sys : Compilation_Unit := Library_Unit_Declaration
            ("System", The_Context);

         State : Check_10_1_1_26c_26b_Information;

         --  Retrive_For_Body  --
         procedure Retrive_For_Body
           (Unit : in Compilation_Unit)
         is
            Exist_Node : Tree_Node_Access;
         begin
            Exist_Node := Find (Result, Unit);

            if Exist_Node = null then
               Exist_Node := Add_Child (Result, null, Unit);

               if Node /= null then
                  Add_Body_Dependents (Result, Exist_Node, Node);
               end if;

               Retrive (Unit, Exist_Node, True);
            else
               if Node /= null then
                  Add_Body_Dependents (Result, Exist_Node, Node);
               end if;
            end if;
         end Retrive_For_Body;

      begin
         State := Check_10_1_1_26c_26b (Unit, The_Context);

         if State.Exceptions then
            if not For_Body then
               Retrive (Except, Node);
            else
               Retrive_For_Body (Except);
            end if;
         end if;

         if State.System then
            if not For_Body then
               Retrive (Sys, Node);
            else
               Retrive_For_Body (Sys);
            end if;
         end if;
      end Check_10_1_1_26c_26b;

   begin
      Dependence_Order (Result, Ascending);

      for Index in List'Range loop
         Unit := List (Index);

         if Find (Result, Unit) = null then
            Retrive (Unit, null, True);
         end if;
      end loop;

      return Result;
   exception
      when others =>
         Deallocate (Result);
         raise;
   end Get_Supporters;

   --------------------
   -- Get_Dependents --
   --------------------

   function Get_Dependents
     (List        : in Asis.Compilation_Unit_List;
      The_Context : in Asis.Context)
      return Utils.Root_Tree_Access
   is
      use Utils;

      procedure Append_To_Node
         (Unit  : in     Compilation_Unit;
          Node  : in     Tree_Node_Access;
          Glued : in out Tree_Node_Array_Access);

      procedure Post_Operation
        (Element : in     Asis.Element;
         Control : in out Traverse_Control;
         State   : in out Boolean);

      function Have_Except
        (Unit : in Compilation_Unit)
        return Boolean;

      function Have_Sys
        (Unit : in Compilation_Unit)
        return Boolean;

      procedure Retrive
        (Unit : in Compilation_Unit;
         Node : in Tree_Node_Access);

      Result : Root_Tree_Access := new Root_Tree;

      Unit, Body_Unit : Compilation_Unit;

      Kinds : Unit_Kinds;

      Except : Compilation_Unit := Library_Unit_Declaration
         ("Ada.Exceptions", The_Context);

      Sys : Compilation_Unit := Library_Unit_Declaration
         ("System", The_Context);

      procedure Append_To_Node
         (Unit  : in     Compilation_Unit;
          Node  : in     Tree_Node_Access;
          Glued : in out Tree_Node_Array_Access)
      is
         Exist_Node  : Tree_Node_Access := null;
         Second_Unit : Compilation_Unit;
      begin
         Exist_Node := Find (Result, Unit);
         Kinds      := Unit_Kind (Unit);

         if Kinds in A_Procedure .. A_Generic_Package then
            if Exist_Node /= null then
               if Is_Child (Result, Exist_Node) then
                  Set_Parent (Result, Exist_Node, Node);
               else
                  Glue_Nodes_Checked (Result, Node, Exist_Node);
               end if;

               if not Is_Skip_Spec (Exist_Node) then
                  Glued := Append (Glued, Exist_Node);
               else
                  Skip_Spec (Exist_Node, False);
               end if;
            else
               Second_Unit := Corresponding_Body (Unit, The_Context);
               Exist_Node  := Add_Child (Result, Node, Unit, Second_Unit);
            end if;

         elsif Kinds in A_Library_Unit_Body then
            if Exist_Node /= null then
               Add_Body_Dependents (Result, Exist_Node, Node);
            else
               Second_Unit := Corresponding_Declaration (Unit, The_Context);

               if not Is_Nil (Second_Unit)
                  and then not Is_Identical (Second_Unit, Unit)
               then
                  Exist_Node := Find (Result, Second_Unit);

                  if Exist_Node /= null then
                     Add_Body_Dependents (Result, Exist_Node, Node);
                  else
                     Exist_Node := Add_Child
                        (Result, null, Second_Unit, Unit, True);
                     Add_Body_Dependents (Result, Exist_Node, Node);
                  end if;
               else
                  Exist_Node := Add_Child (Result, null, Unit);
                  Add_Body_Dependents (Result, Exist_Node, Node);
               end if;
            end if;

         elsif Kinds in A_Subunit then
            if Exist_Node /= null then
               Add_Body_Dependents (Result, Exist_Node, Node);
            else
               Exist_Node := Add_Child (Result, null, Unit);
               Add_Body_Dependents (Result, Exist_Node, Node);
            end if;

         else
            if Exist_Node /= null then
               Glue_Nodes_Checked (Result, Node, Exist_Node);

               if not Is_Skip_Spec (Exist_Node) then
                  Glued := Append (Glued, Exist_Node);
               else
                  Skip_Spec (Exist_Node, False);
               end if;
            else
               Exist_Node := Add_Child (Result, Node, Unit);
            end if;
         end if;
      end Append_To_Node;

      procedure Post_Operation
        (Element : in     Asis.Element;
         Control : in out Traverse_Control;
         State   : in out Boolean)
      is
      begin
         null;
      end Post_Operation;

      -- Have_Except --
      function Have_Except
        (Unit : in Compilation_Unit)
        return Boolean
      is
         procedure Pre_Operation
           (Element : in     Asis.Element;
            Control : in out Traverse_Control;
            State   : in out Boolean);

         Control : Traverse_Control := Continue;
         State   : Boolean := False;

         procedure Pre_Operation
           (Element : in     Asis.Element;
            Control : in out Traverse_Control;
            State   : in out Boolean)
         is
            use Asis.Elements;
         begin
            if Declaration_Kind (Element) =
              A_Choice_Parameter_Specification
            then
               State   := True;
               Control := Terminate_Immediately;
            end if;
         end Pre_Operation;

         procedure Check_Choice_Iterator is new
           Asis.Iterator.Traverse_Element
             (Boolean, Pre_Operation, Post_Operation);
      begin
         Check_Choice_Iterator
           (Asis.Elements.Unit_Declaration (Unit), Control, State);

         return State;
      end Have_Except;

      -- Have_Sys --
      function Have_Sys
        (Unit : in Compilation_Unit)
        return Boolean
      is
         procedure Pre_Operation
           (Element : in     Asis.Element;
            Control : in out Traverse_Control;
            State   : in out Boolean);

         Control : Traverse_Control := Continue;
         State   : Boolean := False;

         procedure Pre_Operation
           (Element : in     Asis.Element;
            Control : in out Traverse_Control;
            State   : in out Boolean)
         is
            use Asis.Elements;
         begin
            if Expression_Kind (Element) = An_Attribute_Reference
              and then Attribute_Kind (Element) = An_Address_Attribute
            then
               State   := True;
               Control := Terminate_Immediately;
            end if;
         end Pre_Operation;

         procedure Check_Choice_Iterator is new
           Asis.Iterator.Traverse_Element
             (Boolean, Pre_Operation, Post_Operation);

      begin
         Check_Choice_Iterator
           (Asis.Elements.Unit_Declaration (Unit), Control, State);

         return State;
      end Have_Sys;

      -- Retrive --
      procedure Retrive
        (Unit : in Compilation_Unit;
         Node : in Tree_Node_Access)
      is
         use Utils;
         Exist_Node : Tree_Node_Access       := null;
         Glued      : Tree_Node_Array_Access := null;
      begin
         if Is_Nil (Unit) then
            return;
         end if;

         --  subunits  --
         if not Is_Nil (Get_Body (Node)) then
            Get_Subunits (Result, Get_Body (Node), Node, The_Context);
         end if;

         -- childrens --
         declare
            Children_List : Asis.Compilation_Unit_List :=
              Corresponding_Children (Unit, The_Context);
            Children    : Compilation_Unit;
            Second_Unit : Compilation_Unit;
         begin
            for Index in Children_List'Range loop
               Children := Children_List (Index);

               if not Is_Nil (Children) then
                  Second_Unit := Nil_Compilation_Unit;

                  Kinds      := Unit_Kind (Children);
                  Exist_Node := Find (Result, Children);

                  if Exist_Node /= null then
                     if Is_Child (Result, Exist_Node) then
                        Set_Parent (Result, Exist_Node, Node);
                     else
                        Glue_Nodes_Checked (Result, Node, Exist_Node);
                     end if;

                     if not Is_Skip_Spec (Exist_Node) then
                        Glued := Append (Glued, Exist_Node);
                     else
                        Skip_Spec (Exist_Node, False);
                     end if;

                     if Kinds in A_Procedure .. A_Generic_Package then
                        Second_Unit := Corresponding_Body
                          (Children, The_Context);

                     elsif Kinds in A_Library_Unit_Body then
                        Second_Unit := Corresponding_Declaration
                          (Children, The_Context);
                     end if;

                     if not Is_Nil (Second_Unit)
                       and then not Is_Identical (Second_Unit, Children)
                     then
                        Remove_From_List
                          (Children_List, Index + 1, Second_Unit);
                     end if;

                  else
                     if Kinds in
                       A_Procedure_Instance .. A_Generic_Package_Renaming
                     then
                        Exist_Node := Add_Child (Result, Node, Children);

                     elsif Kinds in A_Procedure .. A_Generic_Package then
                        Second_Unit := Corresponding_Body
                          (Children, The_Context);

                        if not Is_Nil (Second_Unit)
                          and then not Is_Identical (Second_Unit, Children)
                        then
                           Exist_Node := Add_Child
                             (Result, Node, Children, Second_Unit);

                           Remove_From_List
                             (Children_List, Index + 1, Second_Unit);
                        else
                           Exist_Node := Add_Child (Result, Node, Children);
                        end if;

                     elsif Kinds in A_Library_Unit_Body then
                        Second_Unit := Corresponding_Declaration
                          (Children, The_Context);

                        if not Is_Nil (Second_Unit)
                          and then not Is_Identical (Second_Unit, Children)
                        then
                           Exist_Node := Add_Child
                             (Result, Node, Second_Unit, Children);

                           Remove_From_List
                             (Children_List, Index + 1, Second_Unit);
                        else
                           Exist_Node := Add_Child (Result, Node, Children);
                        end if;

                     else
                        Exist_Node := Add_Child (Result, Node, Children);
                     end if;
                  end if;
               end if;
            end loop;
         end;

         -- with --
         declare
            Units : Asis.Compilation_Unit_List :=
               Compilation_Units (The_Context);

            Library : Compilation_Unit;
         begin
            for Index in Units'Range loop
               Library := Units (Index);

               if not Is_Nil (Library) then
                  if Have_With (Library, Unit, The_Context) then
                     Append_To_Node (Library, Node, Glued);
                  end if;
               end if;
            end loop;
         end;

         --  Ada.Exceptions  --
         if Is_Identical (Unit, Except) then
            declare
               Units : Asis.Compilation_Unit_List :=
                  Compilation_Units (The_Context);

               Library : Compilation_Unit;
            begin
               for Index in Units'Range loop
                  Library := Units (Index);

                  if not Is_Nil (Library) then
                     if Have_Except (Library) then
                        Append_To_Node (Library, Node, Glued);
                     end if;
                  end if;
               end loop;
            end;
         end if;

         --  System  --
         if Is_Identical (Unit, Sys) then
            declare
               Units : Asis.Compilation_Unit_List :=
                  Compilation_Units (The_Context);

               Library : Compilation_Unit;
            begin
               for Index in Units'Range loop
                  Library := Units (Index);

                  if not Is_Nil (Library) then
                     if Have_Sys (Library) then
                        Append_To_Node (Library, Node, Glued);
                     end if;
                  end if;
               end loop;
            end;
         end if;

         declare
            Next : Tree_Node_Array_Access := Nexts (Node);
            Next_Node : Tree_Node_Access;
            Next_Unit : Compilation_Unit;
         begin
            if Next /= null then
               for Index in Next'Range loop
                  Next_Node := Next (Index);

                  if Glued = null
                    or else not Utils.In_List
                      (Glued, Glued.all'Last, Next_Node)
                  then
                     Next_Unit := Get_Spec (Next_Node);
                     Kinds     := Unit_Kind (Next_Unit);
                     if Kinds in
                       A_Procedure .. A_Generic_Package_Renaming
                     then
                        Retrive (Next_Unit, Next_Node);

                     elsif Kinds in
                       A_Procedure_Body .. A_Package_Body
                     then
                        Get_Subunits
                          (Result, Next_Unit, Next_Node, The_Context);
                     end if;
                  end if;
               end loop;
            end if;
         end;

         Deallocate (Glued);

      exception
         when others =>
            Deallocate (Glued);
            raise;
      end Retrive;

   begin
      Dependence_Order (Result, Descending);

      for Index in List'Range loop
         Unit := List (Index);

         if Find (Result, Unit) = null then
            Kinds := Unit_Kind (Unit);

            if Kinds in A_Procedure .. A_Generic_Package_Renaming then
               Body_Unit := Corresponding_Body (Unit, The_Context);

               if not Is_Identical (Body_Unit, Unit) then
                  Retrive (Unit, Add_Child
                           (Result, null, Unit, Body_Unit, True));
               else
                  Retrive (Unit, null);
               end if;

            elsif Kinds in A_Procedure_Body .. A_Protected_Body_Subunit then
               Get_Subunits
                 (Result, Unit, Add_Child (Result, null, Unit), The_Context);
            end if;
         end if;
      end loop;

      return Result;
   exception
      when others =>
         Deallocate (Result);
         raise;
   end Get_Dependents;

   ----------------
   -- Get_Family --
   ----------------

   function Get_Family
     (List        : in Asis.Compilation_Unit_List;
      The_Context : in Asis.Context)
      return Utils.Root_Tree_Access
   is
      use Utils;

      procedure Retrive
        (Unit : in Compilation_Unit;
         Node : in Tree_Node_Access);

      Result : Root_Tree_Access := new Root_Tree;

      Unit, Body_Unit : Compilation_Unit;

      Kinds : Unit_Kinds;

      -- Retrive --
      procedure Retrive
        (Unit : in Compilation_Unit;
         Node : in Tree_Node_Access)
      is
         use Utils;
         Exist_Node : Tree_Node_Access       := null;
         Glued      : Tree_Node_Array_Access := null;
      begin
         if Is_Nil (Unit) then
            return;
         end if;

         --  subunits  --
         if not Is_Nil (Get_Body (Node)) then
            Get_Subunits (Result, Get_Body (Node), Node, The_Context);
         end if;

         -- childrens --
         declare
            Children_List : Asis.Compilation_Unit_List :=
              Corresponding_Children (Unit, The_Context);
            Children    : Compilation_Unit;
            Second_Unit : Compilation_Unit;
         begin
            for Index in Children_List'Range loop
               Children := Children_List (Index);

               if not Is_Nil (Children) then
                  Second_Unit := Nil_Compilation_Unit;

                  Kinds      := Unit_Kind (Children);
                  Exist_Node := Find (Result, Children);

                  if Exist_Node /= null then
                     Glue_Nodes_Checked (Result, Node, Exist_Node);

                     if Kinds in A_Procedure .. A_Generic_Package then
                        Second_Unit := Corresponding_Body
                          (Children, The_Context);

                     elsif Kinds in A_Library_Unit_Body then
                        Second_Unit := Corresponding_Declaration
                          (Children, The_Context);
                     end if;

                     if not Is_Nil (Second_Unit)
                       and then not Is_Identical (Second_Unit, Children)
                     then
                        Remove_From_List
                          (Children_List, Index + 1, Second_Unit);
                     end if;

                  else
                     if Kinds in
                       A_Procedure_Instance .. A_Generic_Package_Renaming
                     then
                        Exist_Node := Add_Child (Result, Node, Children);

                     elsif Kinds in A_Procedure .. A_Generic_Package then
                        Second_Unit := Corresponding_Body
                          (Children, The_Context);

                        if not Is_Nil (Second_Unit)
                          and then not Is_Identical (Second_Unit, Children)
                        then
                           Exist_Node := Add_Child
                             (Result, Node, Children, Second_Unit);

                           Remove_From_List
                             (Children_List, Index + 1, Second_Unit);
                        else
                           Exist_Node := Add_Child (Result, Node, Children);
                        end if;

                     elsif Kinds in A_Library_Unit_Body then
                        Second_Unit := Corresponding_Declaration
                          (Children, The_Context);

                        if not Is_Nil (Second_Unit)
                          and then not Is_Identical (Second_Unit, Children)
                        then
                           Exist_Node := Add_Child
                             (Result, Node, Second_Unit, Children);

                           Remove_From_List
                             (Children_List, Index + 1, Second_Unit);
                        else
                           Exist_Node := Add_Child (Result, Node, Children);
                        end if;

                     else
                        Exist_Node := Add_Child (Result, Node, Children);
                     end if;
                  end if;
               end if;
            end loop;
         end;

         declare
            Next : Tree_Node_Array_Access := Nexts (Node);
            Next_Node : Tree_Node_Access;
            Next_Unit : Compilation_Unit;
         begin
            if Next /= null then
               for Index in Next'Range loop
                  Next_Node := Next (Index);

                  Next_Unit := Get_Spec (Next_Node);
                  Kinds     := Unit_Kind (Next_Unit);

                  if Kinds in
                     A_Procedure .. A_Generic_Package_Renaming
                  then
                     Retrive (Next_Unit, Next_Node);

                  elsif Kinds in
                    A_Procedure_Body .. A_Package_Body
                  then
                     Get_Subunits
                       (Result, Next_Unit, Next_Node, The_Context);
                  end if;
               end loop;
            end if;
         end;
      end Retrive;

   begin
      Dependence_Order (Result, Descending);

      for Index in List'Range loop
         Unit := List (Index);

         if Find (Result, Unit) = null then
            Kinds := Unit_Kind (Unit);

            if Kinds in A_Procedure .. A_Generic_Package_Renaming then
               Body_Unit := Corresponding_Body (Unit, The_Context);

            elsif Kinds in A_Procedure_Body .. A_Protected_Body_Subunit then
               Body_Unit := Unit;
               Unit      := Corresponding_Declaration (Unit, The_Context);
            end if;

            if not Is_Identical (Body_Unit, Unit) then
               Retrive (Unit, Add_Child (Result, null, Unit, Body_Unit));
            else
               Retrive (Unit, Add_Child (Result, null, Unit));
            end if;
         end if;
      end loop;

      return Result;
   exception
      when others =>
         Deallocate (Result);
         raise;
   end Get_Family;

   ----------------------
   -- Get_Needed_Units --
   ----------------------

   function Get_Needed_Units
     (List        : in Asis.Compilation_Unit_List;
      The_Context : in Asis.Context)
      return Utils.Root_Tree_Access
   is
      use Utils;

      Result : Root_Tree_Access := new Root_Tree;

      Unit, Body_Unit : Compilation_Unit;

      Kinds : Unit_Kinds;

      Std : Compilation_Unit :=
        Library_Unit_Declaration ("Standard", The_Context);

      procedure Append_Unit
        (Unit      : in     Compilation_Unit;
         Node      : in out Tree_Node_Access;
         Unit_Body : in     Compilation_Unit := Nil_Compilation_Unit);

      procedure Retrive
        (Unit     : in Compilation_Unit;
         Node     : in Tree_Node_Access;
         Add_Node : in Boolean := True);

      procedure Retrive_Declarations
        (Unit     : in Compilation_Unit;
         Node     : in Tree_Node_Access;
         Add_Node : in Boolean);

      procedure Retrive_Body
        (Unit     : in Compilation_Unit;
         Node     : in Tree_Node_Access;
         Add_Node : in Boolean);

      procedure Retrive_Subunits
        (Unit : in Compilation_Unit;
         Node : in Tree_Node_Access);

      procedure Retrive_With_Clause
        (Unit     : in Compilation_Unit;
         Node     : in Tree_Node_Access;
         For_Body : in Boolean := False);

      procedure Check_10_1_1_26c_26b
        (Unit     : in Compilation_Unit;
         Node     : in Tree_Node_Access;
         For_Body : in Boolean := False);

      -- Append_Unit --
      procedure Append_Unit
        (Unit      : in     Compilation_Unit;
         Node      : in out Tree_Node_Access;
         Unit_Body : in     Compilation_Unit := Nil_Compilation_Unit)
      is
         Exist_Node : Tree_Node_Access;
      begin
         Exist_Node := Find (Result, Unit);

         if Exist_Node = null then
            if Is_Identical (Unit, Std) then
               Node := Add_Child
                 (Result, Node, Unit, Nil_Compilation_Unit, True);

               Node := null;
            else
               Node := Add_Child (Result, Node, Unit, Unit_Body);
            end if;
         else
            if Node /= null then
               Glue_Nodes_Checked (Result, Node, Exist_Node);
               Node := null;
            end if;
         end if;
      end Append_Unit;

      -- Retrive --
      procedure Retrive
        (Unit     : in Compilation_Unit;
         Node     : in Tree_Node_Access;
         Add_Node : in Boolean := True)
      is
         Internal_Node : Tree_Node_Access := Node;
      begin
         if Is_Nil (Unit) then
            return;
         end if;

         Kinds := Unit_Kind (Unit);

         if Kinds in A_Nonexistent_Declaration .. An_Unknown_Unit then
            null;

         elsif Kinds in A_Subunit then
            declare
               Internal_Unit : Compilation_Unit := Unit;
            begin
               while Unit_Kind (Internal_Unit) in A_Subunit loop
                  Internal_Unit := Corresponding_Subunit_Parent_Body
                     (Internal_Unit, The_Context);
               end loop;

               Retrive_Declarations
                  (Corresponding_Declaration (Internal_Unit, The_Context),
                   Node, Add_Node);
            end;

         elsif Kinds in A_Procedure_Body .. A_Package_Body then
            Retrive_Body (Unit, Node, Add_Node);

         else
            Retrive_Declarations (Unit, Node, Add_Node);
         end if;
      end Retrive;

      -- Retrive_Declarations --
      procedure Retrive_Declarations
        (Unit     : in Compilation_Unit;
         Node     : in Tree_Node_Access;
         Add_Node : in Boolean)
      is
         Parent         : Compilation_Unit;
         Internal_Node  : Tree_Node_Access := Node;
      begin
         Body_Unit := Corresponding_Body (Unit, The_Context);

         if Add_Node then
            if not Is_Identical (Body_Unit, Unit) then
               Append_Unit (Unit, Internal_Node, Body_Unit);
            else
               Append_Unit (Unit, Internal_Node);
            end if;

            if Internal_Node = null then
               return;
            end if;
         end if;

         if Is_Identical (Unit, Std) then
            return;
         end if;

         Check_10_1_1_26c_26b (Unit, Internal_Node);
         Retrive_With_Clause (Unit, Internal_Node);

         if not Is_Nil (Body_Unit) then
            Retrive_Body (Body_Unit, Internal_Node, False);
         end if;

         Parent := Corresponding_Parent_Declaration (Unit, The_Context);

         while Unit_Kind (Parent) in
           A_Procedure .. A_Generic_Package_Renaming
         loop
            Body_Unit := Corresponding_Body (Parent, The_Context);

            if not Is_Identical (Body_Unit, Parent) then
               Append_Unit (Parent, Internal_Node, Body_Unit);
            else
               Append_Unit (Parent, Internal_Node);
            end if;

            if Internal_Node = null then
               return;
            end if;

            Check_10_1_1_26c_26b (Parent, Internal_Node);
            Retrive_With_Clause (Parent, Internal_Node);

            if not Is_Nil (Body_Unit) then
               Retrive_Body (Body_Unit, Internal_Node, False);
            end if;

            Parent := Corresponding_Parent_Declaration (Parent, The_Context);
         end loop;

         Retrive (Parent, Internal_Node);
      end Retrive_Declarations;

      -- Retrive_Body --
      procedure Retrive_Body
        (Unit     : in Compilation_Unit;
         Node     : in Tree_Node_Access;
         Add_Node : in Boolean)
      is
         Internal_Node : Tree_Node_Access := Node;
      begin
         if Is_Nil (Unit) then
            return;
         end if;

         if Add_Node then
            Append_Unit (Unit, Internal_Node);

            if Internal_Node = null then
               return;
            end if;
         end if;

         Check_10_1_1_26c_26b (Unit, Internal_Node, True);
         Retrive_With_Clause (Unit, Internal_Node, True);
         Retrive_Subunits (Unit, Internal_Node);
      end Retrive_Body;

      --  Retrive_Subunits  --
      procedure Retrive_Subunits
        (Unit : in Compilation_Unit;
         Node : in Tree_Node_Access)
      is
         Sub : Asis.Compilation_Unit_List := Subunits (Unit, The_Context);

         Sub_Unit   : Compilation_Unit;
         Exist_Node : Tree_Node_Access;
         vNode      : Tree_Node_Access := Node;
      begin
         for Index in Sub'Range loop
            Sub_Unit := Sub (Index);

            if not Is_Nil (Sub_Unit) then
               Exist_Node := Find (Result, Sub_Unit);
               if Exist_Node = null then
                  Exist_Node := Add_Subunit (Result, Node, Sub_Unit);
                  Check_10_1_1_26c_26b (Unit, Exist_Node, True);
                  Retrive_With_Clause (Unit, Exist_Node, True);

                  Retrive_Subunits (Sub_Unit, Exist_Node);
               else
                  Glue_Nodes (Result, Exist_Node, Node);
               end if;
            end if;
         end loop;
      end Retrive_Subunits;

      -- Retrive_With_Clause --
      procedure Retrive_With_Clause
        (Unit     : in Compilation_Unit;
         Node     : in Tree_Node_Access;
         For_Body : in Boolean := False)
      is
         With_List : constant Asis.Context_Clause_List :=
           Asis.Elements.Context_Clause_Elements (Unit);

         Internal_Unit : Compilation_Unit;
         Exist_Node    : Tree_Node_Access;
      begin
         for Index in With_List'Range loop
            if Clause_Kind (With_List (Index).all) = A_With_Clause then

               Internal_Unit := Get_Compilation_Unit
                  (Unit, With_List (Index), Index, The_Context);

               if not Is_Nil (Internal_Unit) then
                  if not For_Body then
                     Retrive (Internal_Unit, Node);
                  else
                     Exist_Node := Find (Result, Internal_Unit);

                     if Exist_Node = null then
                        Body_Unit := Corresponding_Body
                          (Internal_Unit, The_Context);

                        if not Is_Identical (Body_Unit, Internal_Unit) then
                           Exist_Node := Add_Child
                             (Result, null, Internal_Unit, Body_Unit);
                        else
                           Exist_Node := Add_Child
                             (Result, null, Internal_Unit);
                        end if;

                        if Node /= null then
                           Add_Body_Dependents (Result, Exist_Node, Node);
                        end if;

                        Retrive (Internal_Unit, Exist_Node, False);
                     else
                        if Node /= null then
                           Add_Body_Dependents (Result, Exist_Node, Node);
                        end if;
                     end if;
                  end if;
               end if;
            end if;
         end loop;
      end Retrive_With_Clause;

      -- Check_10_1_1_26c_26b --
      procedure Check_10_1_1_26c_26b
        (Unit     : in Compilation_Unit;
         Node     : in Tree_Node_Access;
         For_Body : in Boolean := False)
      is
         procedure Retrive_For_Body
           (Unit : in Compilation_Unit);

         Except : Compilation_Unit := Library_Unit_Declaration
            ("Ada.Exceptions", The_Context);

         Sys : Compilation_Unit := Library_Unit_Declaration
            ("System", The_Context);

         State : Check_10_1_1_26c_26b_Information;

         --  Retrive_For_Body  --
         procedure Retrive_For_Body
           (Unit : in Compilation_Unit)
         is
            Exist_Node : Tree_Node_Access;
         begin
            Exist_Node := Find (Result, Unit);

            if Exist_Node = null then
               Body_Unit := Corresponding_Body (Unit, The_Context);

               if not Is_Identical (Body_Unit, Unit) then
                  Exist_Node := Add_Child (Result, null, Unit, Body_Unit);
               else
                  Exist_Node := Add_Child (Result, null, Unit);
               end if;

               if Node /= null then
                  Add_Body_Dependents (Result, Exist_Node, Node);
               end if;

               Retrive (Unit, Exist_Node, False);
            else
               if Node /= null then
                  Add_Body_Dependents (Result, Exist_Node, Node);
               end if;
            end if;
         end Retrive_For_Body;

      begin
         State := Check_10_1_1_26c_26b (Unit, The_Context);

         if State.Exceptions then
            if not For_Body then
               Retrive (Except, Node);
            else
               Retrive_For_Body (Except);
            end if;
         end if;

         if State.System then
            if not For_Body then
               Retrive (Sys, Node);
            else
               Retrive_For_Body (Sys);
            end if;
         end if;
      end Check_10_1_1_26c_26b;

   begin
      Dependence_Order (Result, Ascending);

      for Index in List'Range loop
         Unit := List (Index);

         if Find (Result, Unit) = null then
            Retrive (Unit, null);
         end if;
      end loop;

      return Result;

   exception
      when others =>
         Deallocate (Result);
         raise;
   end Get_Needed_Units;

   --------------------
   --  Get_Subunits  --
   --------------------

   procedure Get_Subunits
     (Tree        : in Utils.Root_Tree_Access;
      Unit        : in Compilation_Unit;
      Node        : in Utils.Tree_Node_Access;
      The_Context : in Asis.Context)
   is
      use Utils;
      Sub : Asis.Compilation_Unit_List := Subunits (Unit, The_Context);

      Sub_Unit   : Compilation_Unit;
      Exist_Node : Tree_Node_Access;
   begin
      for Index in Sub'Range loop
         Sub_Unit := Sub (Index);

         if not Is_Nil (Sub_Unit) then
            Exist_Node := Find (Tree, Sub_Unit);
            if Exist_Node = null then
               Exist_Node := Add_Child (Tree, Node, Sub_Unit);
               Get_Subunits (Tree, Sub_Unit, Exist_Node, The_Context);
            else
               Glue_Nodes (Tree, Node, Exist_Node);
            end if;
         end if;
      end loop;
   end Get_Subunits;

   --------------------------
   -- Get_Compilation_Unit --
   --------------------------

   function Get_Compilation_Unit
     (Unit        : in Compilation_Unit;
      Target      : in Asis.Element;
      Number      : in List_Index;
      The_Context : in Asis.Context)
      return Asis.Compilation_Unit
   is
      use Utils;
      Names : constant Asis.Name_List := Asis.Clauses.Clause_Names (Target);

      Declaration   : Asis.Element;
      Internal_Unit : Asis.Compilation_Unit;
      Result_List   : Compilation_Unit_List_Access := null;
   begin
      for Index in Names'Range loop
         if Expression_Kind (Names (Index).all) = An_Identifier then
            Declaration := Asis.Expressions.Corresponding_Name_Declaration
              (Names (Index));
         else
            --  A_Selected_Component
            Declaration := Asis.Expressions.Corresponding_Name_Declaration
              (Asis.Expressions.Selector (Names (Index)));
         end if;

         if Assigned (Declaration) then
            Internal_Unit :=
              Asis.Elements.Enclosing_Compilation_Unit (Declaration);

            if Unit_Kind (Internal_Unit) in
              A_Procedure .. A_Generic_Package_Renaming
            then
               Result_List := Append (Result_List, Internal_Unit);
            end if;
         end if;
      end loop;

      if Result_List = null then
         return Nil_Compilation_Unit;
      end if;

      if Result_List.all'Length > 1 then
         Ada.Wide_Text_IO.Put_Line
            ("[Warning] Founded more then one unit for one with_clause "
             & "in unit " & Unit_Full_Name (Unit) & " clause number "
             & List_Index'Wide_Image (Number));
      end if;

      declare
         Result : Asis.Compilation_Unit :=
           Result_List.all (Result_List.all'First);
      begin
         Deallocate (Result_List);

         if Is_Nil (Result) then
            Ada.Wide_Text_IO.Put_Line
               ("[Warning] Unit for with_clause in unit "
               & Unit_Full_Name (Unit) & " clause number "
               & List_Index'Wide_Image (Number) & " not found");
         else
            if Unit_Kind (Result) in A_Procedure_Body .. A_Package_Body then
               Result := Corresponding_Declaration (Result, The_Context);
            end if;
         end if;

         return Result;
      end;
   end Get_Compilation_Unit;

   ---------------
   -- Have_With --
   ---------------

   function Have_With
     (Library     : in Compilation_Unit;
      Unit        : in Compilation_Unit;
      The_Context : in Asis.Context)
      return Boolean
   is
      With_List : constant Asis.Context_Clause_List :=
        Asis.Elements.Context_Clause_Elements (Library);

      Internal_Unit : Compilation_Unit;
   begin
      for Index in With_List'Range loop
         if Clause_Kind (With_List (Index).all) = A_With_Clause then

            Internal_Unit := Get_Compilation_Unit
               (Library, With_List (Index), Index, The_Context);

            if not Is_Nil (Internal_Unit)
              and then Is_Identical (Internal_Unit, Unit)
            then
               return True;
            end if;
         end if;
      end loop;

      return False;
   end Have_With;

   --------------------------
   -- Check_10_1_1_26c_26b --
   --------------------------

   function Check_10_1_1_26c_26b
     (Unit        : in Compilation_Unit;
      The_Context : in Asis.Context)
      return Check_10_1_1_26c_26b_Information
   is
      --  10.1.1 (26.c)
      --  10.1.1 (26.b)

      procedure Pre_Operation
        (Element : in     Asis.Element;
         Control : in out Traverse_Control;
         State   : in out Check_10_1_1_26c_26b_Information);

      procedure Post_Operation
        (Element : in     Asis.Element;
         Control : in out Traverse_Control;
         State   : in out Check_10_1_1_26c_26b_Information);

      Except : Compilation_Unit := Library_Unit_Declaration
         ("Ada.Exceptions", The_Context);

      Sys : Compilation_Unit := Library_Unit_Declaration
         ("System", The_Context);

      Is_Except : Boolean;
      Is_Sys    : Boolean;

      Control : Traverse_Control := Continue;
      State   : Check_10_1_1_26c_26b_Information;

      procedure Pre_Operation
        (Element : in     Asis.Element;
         Control : in out Traverse_Control;
         State   : in out Check_10_1_1_26c_26b_Information)
      is
         use Asis.Elements;
      begin
         if not Is_Except
           and then Declaration_Kind (Element) =
           A_Choice_Parameter_Specification
         then
            State.Exceptions := True;
         end if;

         if not Is_Sys
           and then Expression_Kind (Element) = An_Attribute_Reference
           and then Attribute_Kind (Element) = An_Address_Attribute
         then
            State.System := True;
         end if;
      end Pre_Operation;

      procedure Post_Operation
        (Element : in     Asis.Element;
         Control : in out Traverse_Control;
         State   : in out Check_10_1_1_26c_26b_Information)
      is
      begin
         null;
      end Post_Operation;

      procedure Check_Choice_Iterator is new
        Asis.Iterator.Traverse_Element
          (Check_10_1_1_26c_26b_Information, Pre_Operation, Post_Operation);

   begin
      Is_Except := Is_Identical (Unit, Except);
      Is_Sys    := Is_Identical (Unit, Sys);

      Check_Choice_Iterator
        (Asis.Elements.Unit_Declaration (Unit), Control, State);

      return State;
   end Check_10_1_1_26c_26b;

   ------------
   --  Utils --
   ------------

   package body Utils is

      -------------
      -- In_List --
      -------------

      function In_List
        (List : in Tree_Node_Array_Access;
         Last : in Natural;
         Node : in Tree_Node_Access)
         return Boolean
      is
      begin
         for Index in 1 .. Last loop
            if List (Index) = Node then
               return True;
            end if;
         end loop;

         return False;
      end In_List;

      ----------------------
      -- Dependence_Order --
      ----------------------

      procedure Dependence_Order
        (This  : in Root_Tree_Access;
         Order : in Orders)
      is
      begin
         This.Order := Order;
      end Dependence_Order;

      ---------------
      -- Add_Child --
      ---------------

      function Add_Child
        (This : in Root_Tree_Access;
         Node : in Tree_Node_Access;
         Unit : in Compilation_Unit)
         return Tree_Node_Access
      is
         Kinds : Unit_Kinds;
      begin
         if Is_Nil (Unit) then
            return Node;
         end if;

         declare
            New_Node : Tree_Node_Access := new Tree_Node;
         begin
            Kinds := Unit_Kind (Unit);

            if Kinds in A_Procedure .. A_Generic_Package_Renaming
              or else Kinds = A_Nonexistent_Declaration
            then
               New_Node.Unit := Unit;
            else
               New_Node.Unit_Body := Unit;
            end if;

            if Node = null then
               This.Next := Add_Node (This.Next, New_Node.Self);
            else
               Node.Next      := Add_Node (Node.Next, New_Node.Self);
               New_Node.Prevs := Add_Node (New_Node.Prevs, Node.Self);
            end if;

            This.Units := Add_Node_Ordered (This.Units, New_Node.Self);
            return New_Node;
         end;
      end Add_Child;

      -- Add_Child --
      function Add_Child
        (This      : in Root_Tree_Access;
         Node      : in Tree_Node_Access;
         Spec_Unit : in Compilation_Unit;
         Body_Unit : in Compilation_Unit;
         Skip_Spec : in Boolean := False)
         return Tree_Node_Access
      is
         Kinds : Unit_Kinds;
      begin
         if Is_Nil (Spec_Unit)
           and then Is_Nil (Body_Unit)
         then
            return Node;
         end if;

         if not Is_Nil (Spec_Unit) then
            Kinds := Unit_Kind (Spec_Unit);

            if Kinds not in A_Procedure .. A_Generic_Package_Renaming
              and then Kinds = A_Nonexistent_Declaration
            then
               Asis.Implementation.Set_Status
                 (Data_Error, "Add_Child - "
                  & "invalid unit specification "
                  & Unit_Full_Name (Spec_Unit));

               raise Asis.Exceptions.ASIS_Failed;
            end if;
         end if;

         if not Is_Identical (Spec_Unit, Body_Unit) then
            if not Is_Nil (Body_Unit) then
               Kinds := Unit_Kind (Body_Unit);

               if Kinds in A_Procedure .. A_Generic_Package_Renaming
                 or else Kinds = A_Nonexistent_Declaration
               then
                  Asis.Implementation.Set_Status
                    (Data_Error, "Add_Child - "
                     & "invalid unit body " & Unit_Full_Name (Body_Unit));

                  raise Asis.Exceptions.ASIS_Failed;
               end if;
            end if;
         end if;

         declare
            New_Node : Tree_Node_Access := new Tree_Node;
         begin
            New_Node.Unit := Spec_Unit;

            if not Is_Identical (Spec_Unit, Body_Unit) then
               New_Node.Unit_Body := Body_Unit;
            end if;

            New_Node.Skip_Spec := Skip_Spec;

            if Node = null then
               This.Next := Add_Node (This.Next, New_Node.Self);
            else
               Node.Next      := Add_Node (Node.Next, New_Node.Self);
               New_Node.Prevs := Add_Node (New_Node.Prevs, Node.Self);
            end if;

            This.Units := Add_Node_Ordered (This.Units, New_Node.Self);
            return New_Node;
         end;
      end Add_Child;

      -----------------
      -- Add_Subunit --
      -----------------

      function Add_Subunit
        (This : in Root_Tree_Access;
         Node : in Tree_Node_Access;
         Unit : in Compilation_Unit)
         return Tree_Node_Access
      is
         Kinds : Unit_Kinds;
      begin
         if Is_Nil (Unit) then
            return Node;
         end if;

         Kinds := Unit_Kind (Unit);

         if Kinds not in
           A_Procedure_Body_Subunit .. A_Protected_Body_Subunit
         then
            Asis.Implementation.Set_Status
              (Data_Error, "Add_Subunit - "
               & "invalid subunit " & Unit_Full_Name (Unit));

            raise Asis.Exceptions.ASIS_Failed;
         end if;

         declare
            New_Node : Tree_Node_Access := new Tree_Node;
         begin
            New_Node.Unit_Body := Unit;

            if Node = null then
               This.Next := Add_Node (This.Next, New_Node.Self);
            else
               Node.Prevs    := Add_Node (Node.Prevs, New_Node.Self);
               New_Node.Next := Add_Node (New_Node.Next, Node.Self);
            end if;

            This.Units := Add_Node_Ordered (This.Units, New_Node.Self);
            return New_Node;
         end;
      end Add_Subunit;

      ------------
      -- Append --
      ------------

      procedure Append
        (This : in Root_Tree_Access;
         Unit : in Compilation_Unit)
      is
      begin
         if Is_Nil (Unit) then
            return;
         end if;

         if Find (This, Unit) /= null then
            Asis.Implementation.Set_Status
              (Asis.Errors.Internal_Error,
               "Elaboration order dublicate unit: " & Unit_Full_Name (Unit));

            raise Asis.Exceptions.ASIS_Failed;
         end if;

         declare
            Kinds : Unit_Kinds;
            New_Node : Tree_Node_Access := new Tree_Node;
         begin
            Kinds := Unit_Kind (Unit);

            if Kinds in A_Procedure .. A_Generic_Package_Renaming
              or else Kinds = A_Nonexistent_Declaration
            then
               New_Node.Unit := Unit;
            else
               New_Node.Unit_Body := Unit;
            end if;

            if This.Last_Node = null then
               This.Next := Add_Node (This.Next, New_Node.Self);
            else
               This.Last_Node.Next := Add_Node
                  (This.Last_Node.Next, New_Node.Self);

               New_Node.Prevs := Add_Node
                  (New_Node.Prevs, This.Last_Node.Self);
            end if;

            This.Last_Node := New_Node;
            This.Units := Add_Node_Ordered (This.Units, New_Node.Self);
         end;
      end Append;

      ----------------
      -- Glue_Nodes --
      ----------------

      procedure Glue_Nodes
        (This    : in Root_Tree_Access;
         Node    : in Tree_Node_Access;
         To_Node : in Tree_Node_Access)
      is
      begin
         if To_Node.Prevs /= null
            and then In_List (To_Node.Prevs, To_Node.Prevs'Last, Node)
         then
            return;
         end if;

         Node.Next     := Add_Node (Node.Next, To_Node.Self);
         To_Node.Prevs := Add_Node (To_Node.Prevs, Node.Self);
      end Glue_Nodes;

      ------------------------
      -- Glue_Nodes_Checked --
      ------------------------

      procedure Glue_Nodes_Checked
        (This    : in Root_Tree_Access;
         Node    : in Tree_Node_Access;
         To_Node : in Tree_Node_Access)
      is
         Circular  : Compilation_Unit_List_Access := null;
         Prev_Node : Tree_Node_Access := null;
      begin
         if To_Node.Prevs /= null then
            Prev_Node := To_Node.Prevs (To_Node.Prevs.all'First);

            if In_List (To_Node.Prevs, To_Node.Prevs'Last, Node) then
               return;
            end if;
         end if;

         while Prev_Node /= null loop
            if Prev_Node = To_Node then
               if Circular /= null then

                  for Index in reverse Circular.all'Range loop
                     Node.Circular := Append (Node.Circular, Circular (Index));
                  end loop;

                  Node.Circular := Append (Node.Circular, Node.Unit);
                  Node.Circular := Append
                    (Node.Circular, Circular (Circular.all'Last));

                  Deallocate (Circular);
               else
                  --  2 pair (self and parent)
                  Node.Circular := Append
                    (Node.Circular,
                     (Prev_Node.Unit, Node.Unit, Prev_Node.Unit));
               end if;

               return;
            end if;

            Circular := Append (Circular, Prev_Node.Unit);

            if Prev_Node.Prevs /= null then
               Prev_Node := Prev_Node.Prevs (Prev_Node.Prevs.all'First);
            else
               Prev_Node := null;
            end if;
         end loop;

         if Circular /= null then
            Deallocate (Circular);
         end if;

         Node.Next     := Add_Node (Node.Next, To_Node.Self);
         To_Node.Prevs := Add_Node (To_Node.Prevs, Node.Self);
      end Glue_Nodes_Checked;

      -------------------------
      -- Add_Body_Dependents --
      -------------------------

      procedure Add_Body_Dependents
        (This    : in Root_Tree_Access;
         Node    : in Tree_Node_Access;
         To_Node : in Tree_Node_Access)
      is
      begin
         Node.Body_Dependences := Add_Node (Node.Body_Dependences, To_Node);
      end Add_Body_Dependents;

      --------------
      -- Is_Child --
      --------------

      function Is_Child
        (This : in Root_Tree_Access;
         Node : in Tree_Node_Access)
        return Boolean
      is
      begin
         if This.Next /= null then
            return In_List (This.Next, This.Next'Last, Node);
         else
            return False;
         end if;
      end Is_Child;

      ----------------
      -- Set_Parent --
      ----------------

      procedure Set_Parent
        (This   : in Root_Tree_Access;
         Node   : in Tree_Node_Access;
         Parent : in Tree_Node_Access)
      is
      begin
         Parent.Next := Add_Node (Parent.Next, Node.Self);
         Node.Prevs  := Add_Node (Node.Prevs, Parent.Self);
      end Set_Parent;

      -----------
      -- Clear --
      -----------

      procedure Clear
        (This : in out Root_Tree)
      is
      begin
         Finalize (This);
      end Clear;

      -----------
      -- Check --
      -----------

      procedure Check
        (This        : in Root_Tree_Access;
         The_Context : in Asis.Context)
      is
         Kinds, Parent_Kinds : Unit_Kinds;
         Order : Orders;

         procedure Check_Consistent
           (Node : in Tree_Node_Access);

         function Set_Inconsistent
           (Node  : in Tree_Node_Access;
            Prev  : in Tree_Node_Access;
            List  : in Compilation_Unit_List_Access)
            return Compilation_Unit_List_Access;

         procedure Check_Body_Consistent
            (Node : in Tree_Node_Access);

         procedure Check_Missing
           (Node : in Tree_Node_Access);

         procedure Asc
           (Node : in Tree_Node_Access);

         procedure Desc
           (Node : in Tree_Node_Access);

         -- Check_Consistent --
         procedure Check_Consistent
           (Node : in Tree_Node_Access)
         is
            Prev_Node : Tree_Node_Access;
         begin
            if Is_Inconsistent (Node.Unit) then
               return;
            end if;

            Node.Consistent := False;

            if Is_Source_Changed (Node.Unit) then
               Node.Inconsistent := Append
                 (Node.Inconsistent, (Nil_Compilation_Unit, Node.Unit));
            else
               Prev_Node := null;

               if Order = Ascending then
                  if Node.Prevs /= null then
                     Prev_Node := Node.Prevs (Node.Prevs.all'First);
                  end if;
               else
                  if Node.Next /= null then
                     Prev_Node := Node.Next (Node.Next.all'First);
                  end if;
               end if;

               if Prev_Node /= null
                 and then not Is_Nil (Prev_Node.Unit)
               then
                  Node.Inconsistent := Append
                    (Node.Inconsistent, (Prev_Node.Unit, Node.Unit));
               else
                  Node.Inconsistent := Append
                    (Node.Inconsistent, (Node.Unit, Node.Unit));
               end if;
            end if;

            if Order = Ascending then
               if Node.Next /= null then
                  for Index in Node.Next.all'Range loop
                     Node.Inconsistent := Set_Inconsistent
                       (Node.Next.all (Index), Node, Node.Inconsistent);
                  end loop;
               end if;
            else
               if Node.Prevs /= null then
                  for Index in Node.Prevs.all'Range loop
                     Node.Inconsistent := Set_Inconsistent
                       (Node.Prevs.all (Index), Node, Node.Inconsistent);
                  end loop;
               end if;
            end if;
         end Check_Consistent;

         -- Set_Inconsistent --
         function Set_Inconsistent
           (Node  : in Tree_Node_Access;
            Prev  : in Tree_Node_Access;
            List  : in Compilation_Unit_List_Access)
            return Compilation_Unit_List_Access
         is
            Result : Compilation_Unit_List_Access := List;
         begin
            if not Node.Consistent
              and then Node.Inconsistent /= null
            then
               if Is_Nil
                  (Node.Inconsistent (Node.Inconsistent'First))
               then
                  Result := Append
                     (Result, (Nil_Compilation_Unit, Node.Unit));
               end if;

               Node.Inconsistent (Node.Inconsistent'First) := Prev.Unit;
               Result := Append (Result, Node.Inconsistent.all);
               Deallocate (Node.Inconsistent);
               return Result;
            end if;

            if not Is_Nil (Node.Unit) then
               Node.Consistent := False;
               Result := Append (Result, (Prev.Unit, Node.Unit));
            end if;

            if Order = Ascending then
               if Node.Next /= null then
                  for Index in Node.Next.all'Range loop
                     Result := Set_Inconsistent
                       (Node.Next.all (Index), Node, Result);
                  end loop;
               end if;
            else
               if Node.Prevs /= null then
                  for Index in Node.Prevs.all'Range loop
                     Result := Set_Inconsistent
                       (Node.Prevs.all (Index), Node, Result);
                  end loop;
               end if;
            end if;

            return Result;
         end Set_Inconsistent;

         -- Check_Body_Consistent --
         procedure Check_Body_Consistent
            (Node : in Tree_Node_Access)
         is
            procedure Check_Body
               (Target : in Tree_Node_Access);

            Prev_Unit : Compilation_Unit;

            -- Check_Body --
            procedure Check_Body
               (Target : in Tree_Node_Access)
            is
            begin
               if not Is_Nil (Target.Unit_Body) then
                  Prev_Unit := Target.Unit_Body;

                  if not Target.Body_Consistent then
                     Node.Body_Consistent := False;

                     Node.Inconsistent := Append
                        (Node.Inconsistent, (Prev_Unit, Node.Unit_Body));
                  end if;
               end if;
            end Check_Body;

         begin
            if not Is_Nil (Node.Unit_Body) then
               if not Node.Consistent then
                  Node.Body_Consistent := False;

                  Node.Inconsistent := Append
                    (Node.Inconsistent, (Node.Unit, Node.Unit_Body));
               end if;

               if not Is_Inconsistent (Node.Unit_Body) then
                  Node.Body_Consistent := False;

                  if Is_Source_Changed (Node.Unit_Body) then
                     Node.Inconsistent := Append
                       (Node.Inconsistent,
                         (Nil_Compilation_Unit, Node.Unit_Body));
                  else
                     Node.Inconsistent := Append
                       (Node.Inconsistent, (Node.Unit_Body, Node.Unit_Body));
                  end if;
               end if;

               if Node.Body_Dependences /= null then
                  for Index in Node.Body_Dependences.all'Range loop
                     Prev_Unit := Node.Body_Dependences (Index).Unit;

                     if not Is_Inconsistent (Prev_Unit) then
                        Node.Body_Consistent := False;

                        Node.Inconsistent := Append
                          (Node.Inconsistent, (Prev_Unit, Node.Unit_Body));
                     end if;
                  end loop;
               end if;

               if Unit_Kind (Node.Unit_Body) in A_Subunit then
                  if Order = Ascending then
                     if Node.Next /= null then
                        Check_Body (Node.Next (Node.Next'First));
                     end if;
                  else
                     if Node.Prevs /= null then
                        Check_Body (Node.Prevs (Node.Prevs'First));
                     end if;
                  end if;
               end if;
            end if;

            if Order = Ascending then
               if Node.Next /= null then
                  for Index in Node.Next.all'Range loop
                     Check_Body_Consistent (Node.Next.all (Index));
                  end loop;
               end if;
            else
               if Node.Prevs /= null then
                  for Index in Node.Prevs.all'Range loop
                     Check_Body_Consistent (Node.Prevs.all (Index));
                  end loop;
               end if;
            end if;
         end Check_Body_Consistent;

         -- Check_Missing --
         procedure Check_Missing
           (Node : in Tree_Node_Access)
         is
            procedure Check_Missing
              (Node   : in Tree_Node_Access;
               Target : in Tree_Node_Access)
            is
            begin
               if Target = null
                 or else Is_Nil (Target.Unit)
               then
                  return;
               end if;

               Parent_Kinds := Unit_Kind (Target.Unit);

               if Parent_Kinds = A_Nonexistent_Declaration then
                  Node.Missing := Append
                    (Node.Missing, (Node.Unit, Target.Unit));
               end if;
            end Check_Missing;

         begin
            if Node.Missing /= null then
               return;
            end if;

            if Order = Ascending then
               if Node.Next /= null then
                  for Index in Node.Next.all'Range loop
                     Check_Missing (Node, Node.Next (Index));
                  end loop;
               end if;
            else
               if Node.Prevs /= null then
                  for Index in Node.Prevs.all'Range loop
                     Check_Missing (Node, Node.Prevs (Index));
                  end loop;
               end if;
            end if;

            if Is_Nil (Node.Unit_Body) then
               return;
            end if;

            if Unit_Kind (Node.Unit) = A_Nonexistent_Declaration then
               Node.Missing := Append
                 (Node.Missing, (Node.Unit_Body, Node.Unit));
            end if;

            if Node.Body_Dependences /= null then
               for Index in Node.Body_Dependences.all'Range loop
                  Parent_Kinds :=
                    Unit_Kind (Node.Body_Dependences (Index).Unit);

                  if Parent_Kinds = A_Nonexistent_Declaration then
                     Node.Missing := Append
                       (Node.Missing,
                        (Node.Unit_Body,
                         Node.Body_Dependences (Index).Unit));
                  end if;
               end loop;
            end if;

            if Unit_Kind (Node.Unit_Body) in A_Subunit then
               if Order = Ascending then
                  if Node.Next /= null then
                     if Unit_Kind
                       (Node.Next (Node.Next'First).Unit_Body) =
                       A_Nonexistent_Body
                     then
                        Node.Missing := Append
                          (Node.Missing,
                           (Node.Unit_Body,
                            Node.Next (Node.Next'First).Unit_Body));
                     end if;
                  end if;
               else
                  if Node.Prevs /= null then
                     if Unit_Kind
                       (Node.Prevs (Node.Prevs'First).Unit_Body) =
                       A_Nonexistent_Body
                     then
                        Node.Missing := Append
                          (Node.Missing,
                           (Node.Unit_Body,
                            Node.Prevs (Node.Prevs'First).Unit_Body));
                     end if;
                  end if;
               end if;
            end if;
         end Check_Missing;

         -- Asc --
         procedure Asc
           (Node : in Tree_Node_Access)
         is
         begin
            if Node = null then
               return;
            end if;

            if not Is_Nil (Node.Unit) then
               if Node.Consistent then
                  Check_Consistent (Node);
               end if;

               Check_Missing (Node);
            end if;

            if Node.Prevs /= null then
               for Index in Node.Prevs.all'Range loop
                  Asc (Node.Prevs.all (Index));
               end loop;
            end if;
         end Asc;

         -- Desc --
         procedure Desc
           (Node : in Tree_Node_Access)
         is
         begin
            if Node = null then
               return;
            end if;

            if not Is_Nil (Node.Unit) then
               Kinds := Unit_Kind (Node.Unit);

               if Node.Consistent then
                  Check_Consistent (Node);
               end if;

               Check_Missing (Node);
            end if;

            if Node.Next /= null then
               for Index in Node.Next.all'Range loop
                  Desc (Node.Next (Index));
               end loop;
            end if;
         end Desc;

         Std_Node : Tree_Node_Access;
      begin
         Order := This.Order;

         if This.Order = Ascending then
            Std_Node := Find
              (This, Library_Unit_Declaration ("Standard", The_Context));

            if Std_Node /= null then
               if Std_Node.Next /= null then
                  for Index in Std_Node.Next.all'Range loop
                     Asc (Std_Node.Next (Index));
                  end loop;

                  for Index in Std_Node.Next.all'Range loop
                     Check_Body_Consistent (Std_Node.Next (Index));
                  end loop;
               end if;
            end if;

         else
            if This.Next /= null then
               for Index in This.Next.all'Range loop
                  Desc (This.Next (Index));
               end loop;

               for Index in This.Next.all'Range loop
                  Check_Body_Consistent (This.Next (Index));
               end loop;
            end if;
         end if;
      end Check;

      ---------------------------
      -- Generate_Relationship --
      ---------------------------

      function Generate_Relationship
        (This       : in Root_Tree_Access;
         Limit_List : in Utils.Compilation_Unit_List_Access;
         List_Last  : in ASIS_Integer)
         return Relationship
      is
         Consistent_List   : Compilation_Unit_List_Access := null;
         Inconsistent_List : Compilation_Unit_List_Access := null;
         Missing_List      : Compilation_Unit_List_Access := null;
         Circular_List     : Compilation_Unit_List_Access := null;

         Consistent_Length   : Asis.ASIS_Natural := 0;
         Inconsistent_Length : Asis.ASIS_Natural := 0;
         Missing_Length      : Asis.ASIS_Natural := 0;
         Circular_Length     : Asis.ASIS_Natural := 0;

         procedure Genegate_Inconsistent
           (Node : in Tree_Node_Access);

         procedure Genegate_Circular
           (Node : in Tree_Node_Access);

         procedure Genegate_Missing
           (Node : in Tree_Node_Access);

         procedure Process
           (Node : in Tree_Node_Access);

         -- Genegate_Inconsistent --
         procedure Genegate_Inconsistent
           (Node : in Tree_Node_Access)
         is
         begin
            if Node.Inconsistent /= null
              and then not Node.Inconsistent_Added
            then
               Node.Inconsistent_Added := True;

               if Inconsistent_List = null then
                  Inconsistent_List := Append
                     (Inconsistent_List, Node.Inconsistent.all);
               else
                  if not Is_Nil (Node.Inconsistent (Node.Inconsistent'First))
                    and then Is_Inconsistent
                      (Node.Inconsistent (Node.Inconsistent'First))
                  then
                     Node.Inconsistent (Node.Inconsistent'First) :=
                        Node.Inconsistent (Node.Inconsistent'First + 1);
                  end if;

                  Inconsistent_List := Append
                     (Inconsistent_List, Node.Inconsistent.all);
               end if;
            end if;
         end Genegate_Inconsistent;

         -- Genegate_Circular --
         procedure Genegate_Circular
           (Node : in Tree_Node_Access)
         is
         begin
            if Node.Circular /= null
              and then not Node.Circular_Added
            then
               Node.Circular_Added := True;

               for Index in
                  Node.Circular.all'First .. Node.Circular.all'Last - 1
               loop
                  Circular_List := Append
                    (Circular_List, (Node.Circular.all (Index),
                                     Node.Circular.all (Index + 1))
                    );
               end loop;
            end if;
         end Genegate_Circular;

         -- Genegate_Missing --
         procedure Genegate_Missing
           (Node : in Tree_Node_Access)
         is
         begin
            if Node.Missing /= null
              and then not Node.Missing_Added
            then
               Node.Missing_Added := True;

               Missing_List := Append (Missing_List, Node.Missing.all);
            end if;
         end Genegate_Missing;

         -- Process --
         procedure Process
           (Node : in Tree_Node_Access)
         is
            -- Add_To_Consistent --
            procedure Add_To_Consistent
               (Unit : in Compilation_Unit)
            is
            begin
               if Limit_List /= null then
                  if In_List (Limit_List, List_Last, Unit) then
                     Consistent_List := Append (Consistent_List, Unit);
                  end if;
               else
                  Consistent_List := Append (Consistent_List, Unit);
               end if;
            end Add_To_Consistent;
         begin
            if Node.Added then
               return;
            end if;

            Node.Added := True;

            if Node.Consistent then
               if not Node.Skip_Spec
                  and then not Is_Nil (Node.Unit)
               then
                  Add_To_Consistent (Node.Unit);
               end if;

               if Node.Body_Consistent
                 and then not Is_Nil (Node.Unit_Body)
               then
                  Add_To_Consistent (Node.Unit_Body);
               end if;
            end if;

            Genegate_Inconsistent (Node);
            Genegate_Missing      (Node);
            Genegate_Circular     (Node);

            if Node.Next /= null then
               for Index in Node.Next.all'Range loop
                  Process (Node.Next.all (Index));
               end loop;
            end if;
         end Process;

      begin
         if This.Next = null then
            return Nil_Relationship;
         end if;

         for Index in This.Next.all'Range loop
            Process (This.Next.all (Index));
         end loop;

         if Consistent_List /= null then
            Consistent_Length := Consistent_List.all'Length;
         end if;

         if Inconsistent_List /= null then
            Inconsistent_Length := Inconsistent_List.all'Length;
         end if;

         if Missing_List /= null then
            Missing_Length := Missing_List.all'Length;
         end if;

         if Circular_List /= null then
            Circular_Length := Circular_List.all'Length;
         end if;

         declare
            Result : Relationship
              (Consistent_Length, Inconsistent_Length,
               Missing_Length, Circular_Length);
         begin
            if Consistent_List /= null then
               Result.Consistent := Consistent_List.all;
            end if;

            if Inconsistent_List /= null then
               Result.Inconsistent := Inconsistent_List.all;
            end if;

            if Missing_List /= null then
               Result.Missing := Missing_List.all;
            end if;

            if Circular_List /= null then
               Result.Circular := Circular_List.all;
            end if;

            Deallocate (Consistent_List);
            Deallocate (Inconsistent_List);
            Deallocate (Missing_List);
            Deallocate (Circular_List);

            return Result;
         end;

      exception
         when others =>
            Deallocate (Consistent_List);
            Deallocate (Inconsistent_List);
            Deallocate (Missing_List);
            Deallocate (Circular_List);
            raise;
      end Generate_Relationship;

      ----------------------------------
      -- Is_Have_Circular_Dependences --
      ----------------------------------

      function Is_Have_Circular_Dependences
        (This : in Root_Tree_Access)
         return Boolean
      is
         function Process
           (Node : in Tree_Node_Access)
            return Boolean;

         Result : Boolean := False;

         -- Process --
         function Process
           (Node : in Tree_Node_Access)
            return Boolean
         is
            Result : Boolean := False;
         begin
            if Node.Circular /= null then
               return True;
            else
               if Node.Next /= null then
                  for Index in Node.Next.all'Range loop
                     Result := Process (Node.Next.all (Index));
                     exit when Result;
                  end loop;
               end if;
            end if;
            return Result;
         end Process;

      begin
         if This.Next /= null then
            for Index in This.Next.all'Range loop
               Result := Process (This.Next.all (Index));
               exit when Result;
            end loop;
         end if;

         return Result;
      end Is_Have_Circular_Dependences;

      -----------------------------
      -- Create_Elaboration_Tree --
      -----------------------------

--      A_Partition_Elaboration_Policy_Pragma,   --  H.6 (3)
--      A_Preelaborable_Initialization_Pragma,   --  7.6 (5)

      function Create_Elaboration_Tree
        (This        : in Root_Tree_Access;
         The_Context : in Asis.Context)
         return Root_Tree_Access
      is
         procedure Process_Pure_Spec
           (Node : in Tree_Node_Access);

         procedure Process_Pure_Body
            (Node : in Tree_Node_Access);

         procedure Process_Preelaborate_Spec
           (Node : in Tree_Node_Access);

         procedure Process_Preelaborate_Body
           (Node : in Tree_Node_Access);

         procedure Process_Spec
           (Node : in Tree_Node_Access);

         procedure Process_Body
            (Node : in Tree_Node_Access);

         procedure Elab_Spec
           (Node : in Tree_Node_Access);

         procedure Elab_Body
           (Node      : in Tree_Node_Access;
            All_Bodys : in Boolean := False;
            Only_Body : in Boolean := True);

         procedure Elab_Subunits
           (Node      : in Tree_Node_Access;
            All_Bodys : in Boolean);

         procedure Elab_Pragmed_Bodys
           (Node : in Tree_Node_Access;
            Unit : in Compilation_Unit);

         procedure Append_Inconsistent
           (Node : in Tree_Node_Access);

         Result : Root_Tree_Access := new Root_Tree;

         Root_Node : Tree_Node_Access;

         Std : Compilation_Unit :=
            Library_Unit_Declaration ("Standard", The_Context);

         --  for circular elaboration order
         Elaboration_Line : Compilation_Unit_List_Access := null;

         procedure Elab_Spec
            (Node : in Tree_Node_Access)
         is
         begin
            if not Node.Elaborated
              and then Node.Consistent
              and then not Is_Nil (Node.Unit)
            then
               if Elaboration_Line /= null then
                  -- test circular --
                  if In_List
                     (Elaboration_Line, Elaboration_Line.all'Last, Node.Unit)
                  then
                     Node.Circular :=  Append
                        (Node.Circular, Elaboration_Line.all);
                     return;
                  end if;
               end if;

               Elaboration_Line := Append
                  (Elaboration_Line, Node.Unit);

               if Node.Next /= null then
                  for Index in Node.Next.all'Range loop
                     Elab_Spec (Node.Next (Index));
                  end loop;
               end if;

               Elab_Pragmed_Bodys (Node, Node.Unit);

               Append (Result, Node.Unit);
               Node.Elaborated := True;
               Remove_From_List (Elaboration_Line, Node.Unit);
            end if;

            if Is_Elaborate_Body (Node) then
               --  An_Elaborate_Body_Pragma --  10.2.1(22)
               Elab_Body (Node);
            end if;
         end Elab_Spec;

         -- Elab_Body --
         procedure Elab_Body
           (Node      : in Tree_Node_Access;
            All_Bodys : in Boolean := False;
            Only_Body : in Boolean := True)
         is
            Unit : Compilation_Unit := Node.Unit_Body;
         begin
            if Node.Body_Elaborated then
               Elab_Subunits (Node, All_Bodys);
               return;
            end if;

            if not Node.Body_Consistent
              or else Is_Nil (Unit)
            then
               return;
            end if;

            if Only_Body
              and then Unit_Kind (Unit) not in
              A_Procedure_Body .. A_Package_Body
            then
               return;
            end if;

            if not Only_Body
              and then Unit_Kind (Unit) not in A_Subunit
            then
               Elab_Subunits (Node, All_Bodys);
               return;
            end if;

            if Elaboration_Line /= null then
               -- test circular --
               if In_List
                 (Elaboration_Line, Elaboration_Line.all'Last, Unit)
               then
                  Node.Circular :=  Append
                    (Node.Circular, Elaboration_Line.all);
                  return;
               end if;
            end if;

            Elaboration_Line := Append (Elaboration_Line, Unit);

            if Node.Body_Dependences /= null then
               for Index in Node.Body_Dependences.all'Range loop
                  Elab_Spec (Node.Body_Dependences (Index));
               end loop;
            end if;

            Elab_Pragmed_Bodys (Node, Unit);

            if All_Bodys then
               if Node.Body_Dependences /= null then
                  for Index in Node.Body_Dependences.all'Range loop
                     Elab_Body (Node.Body_Dependences (Index), True, True);
                  end loop;
               end if;
            end if;

            Append (Result, Unit);
            Node.Body_Elaborated := True;
            Remove_From_List (Elaboration_Line, Unit);

            Elab_Subunits (Node, All_Bodys);
         end Elab_Body;

         -- Elab_Subunits --
         procedure Elab_Subunits
           (Node      : in Tree_Node_Access;
            All_Bodys : in Boolean)
         is
            Next_Node : Tree_Node_Access;
         begin
            if not Node.Body_Elaborated then
               return;
            end if;

            if Node.Prevs /= null then
               for Index in Node.Prevs.all'Range loop
                  Next_Node := Node.Prevs (Index);

                  if Unit_Kind (Next_Node.Unit_Body) in
                    A_Procedure_Body_Subunit .. A_Protected_Body_Subunit
                  then
                     Elab_Body (Next_Node, All_Bodys, False);
                  end if;
               end loop;
            end if;
         end Elab_Subunits;

         -- Elab_Pragmed_Bodys --
         procedure Elab_Pragmed_Bodys
           (Node : in Tree_Node_Access;
            Unit : in Compilation_Unit)
         is
            --  An_Elaborate_Pragma     --  10.2.1(20)
            --  An_Elaborate_All_Pragma --  10.2.1(21)

            use Asis.Elements;
            With_List : constant Asis.Context_Clause_List :=
               Context_Clause_Elements (Unit, True);

            El : Element;
            Internal_Unit : Compilation_Unit;
         begin
            for Index in With_List'Range loop
               El := With_List (Index);

               if Element_Kind (El) = A_Pragma then
                  if Pragma_Kind (El) = An_Elaborate_Pragma then
                     Internal_Unit := Get_Compilation_Unit
                        (Unit, With_List (Index), Index, The_Context);

                     Elab_Body (Find (Result, Internal_Unit));

                  elsif Pragma_Kind (El) = An_Elaborate_All_Pragma then
                     Internal_Unit := Get_Compilation_Unit
                        (Unit, With_List (Index), Index, The_Context);

                     Elab_Body (Find (Result, Internal_Unit), True);
                  end if;
               end if;
            end loop;
         end Elab_Pragmed_Bodys;

         -- Process_Pure_Spec --
         procedure Process_Pure_Spec
            (Node : in Tree_Node_Access)
         is
            --  A_Pure_Pragma --  10.2.1(14)
         begin
            if not Node.Elaborated
              and then not Is_Nil (Node.Unit)
            then
               if Is_Pure (Node) then
                  Elab_Spec (Node);
               end if;
            end if;

            if Node.Prevs /= null then
               for Index in Node.Prevs.all'Range loop
                  Process_Pure_Spec (Node.Prevs (Index));
               end loop;
            end if;
         end Process_Pure_Spec;

         -- Process_Pure_Body --
         procedure Process_Pure_Body
            (Node : in Tree_Node_Access)
         is
            --  A_Pure_Pragma --  10.2.1(14)
         begin
            if Is_Pure (Node) then
               Elab_Body (Node);
            end if;

            if Node.Prevs /= null then
               for Index in Node.Prevs.all'Range loop
                  Process_Pure_Body (Node.Prevs (Index));
               end loop;
            end if;
         end Process_Pure_Body;

         -- Process_Preelaborate_Spec --
         procedure Process_Preelaborate_Spec
           (Node : in Tree_Node_Access)
         is
            --  A_Preelaborate_Pragma --  10.2.1(3)
         begin
            if not Node.Elaborated
              and then not Is_Nil (Node.Unit)
            then
               if Is_Preelaborate (Node) then
                  Elab_Spec (Node);
               end if;
            end if;

            if Node.Prevs /= null then
               for Index in Node.Prevs.all'Range loop
                  Process_Preelaborate_Spec (Node.Prevs (Index));
               end loop;
            end if;
         end Process_Preelaborate_Spec;

         -- Process_Preelaborate_Body --
         procedure Process_Preelaborate_Body
           (Node : in Tree_Node_Access)
         is
            --  A_Preelaborate_Pragma --  10.2.1(3)
         begin
            if Is_Preelaborate (Node) then
               Elab_Body (Node);
            end if;

            if Node.Prevs /= null then
               for Index in Node.Prevs.all'Range loop
                  Process_Preelaborate_Body (Node.Prevs (Index));
               end loop;
            end if;
         end Process_Preelaborate_Body;

         -- Process_Spec --
         procedure Process_Spec
            (Node : in Tree_Node_Access)
         is
         begin
            if not Node.Elaborated
              and then not Is_Nil (Node.Unit)
            then
               Elab_Spec (Node);
            end if;

            if Node.Prevs /= null then
               for Index in Node.Prevs.all'Range loop
                  Process_Spec (Node.Prevs (Index));
               end loop;
            end if;
         end Process_Spec;

         -- Process_Body --
         procedure Process_Body
            (Node : in Tree_Node_Access)
         is
         begin
            Elab_Body (Node);

            if Node.Prevs /= null then
               for Index in Node.Prevs.all'Range loop
                  Process_Body (Node.Prevs (Index));
               end loop;
            end if;
         end Process_Body;

         -- Append_Inconsistent --
         procedure Append_Inconsistent
           (Node : in Tree_Node_Access)
         is
         begin
            if Node.Inconsistent /= null then
               Result.Next (Result.Next'First).Inconsistent :=
                 Append (Result.Next (Result.Next'First).Inconsistent,
                         Node.Inconsistent.all);
            end if;

            if Node.Prevs /= null then
               for Index in Node.Prevs.all'Range loop
                  Append_Inconsistent (Node.Prevs (Index));
               end loop;
            end if;
         end Append_Inconsistent;

      begin
         Root_Node := Find (This, Std);
         Root_Node.Elaborated := True;

         Append (Result, Std);

         if Root_Node.Prevs = null then
            return Result;
         end if;

         for Index in Root_Node.Prevs.all'Range loop
            Deallocate (Elaboration_Line);
            Process_Pure_Spec (Root_Node.Prevs (Index));
         end loop;

         for Index in Root_Node.Prevs.all'Range loop
            Deallocate (Elaboration_Line);
            Process_Pure_Body (Root_Node.Prevs (Index));
         end loop;

         for Index in Root_Node.Prevs.all'Range loop
            Deallocate (Elaboration_Line);
            Process_Preelaborate_Spec (Root_Node.Prevs (Index));
         end loop;

         for Index in Root_Node.Prevs.all'Range loop
            Deallocate (Elaboration_Line);
            Process_Preelaborate_Body (Root_Node.Prevs (Index));
         end loop;

         for Index in Root_Node.Prevs.all'Range loop
            Deallocate (Elaboration_Line);
            Process_Spec (Root_Node.Prevs (Index));
         end loop;

         for Index in Root_Node.Prevs.all'Range loop
            Deallocate (Elaboration_Line);
            Process_Body (Root_Node.Prevs (Index));
         end loop;

         --  inconsistent
         for Index in Root_Node.Prevs.all'Range loop
            Append_Inconsistent (Root_Node.Prevs (Index));
         end loop;

         return Result;
      exception
         when others =>
            Deallocate (Result);
            raise;
      end Create_Elaboration_Tree;

      -------------
      -- Is_Pure --
      -------------

      function Is_Pure
        (This : in Tree_Node_Access)
         return Boolean
      is
      begin
         if This.Internal_Pure = Unknown then
            Retrive_Pragmas (This);
         end if;

         if This.Internal_Pure = Extended_True then
            return True;
         else
            return False;
         end if;
      end Is_Pure;

      ---------------------
      -- Is_Preelaborate --
      ---------------------

      function Is_Preelaborate
        (This : in Tree_Node_Access)
         return Boolean
      is
      begin
         if This.Internal_Preelaborate = Unknown then
            Retrive_Pragmas (This);
         end if;

         if This.Internal_Preelaborate = Extended_True then
            return True;
         else
            return False;
         end if;
      end Is_Preelaborate;

      -----------------------
      -- Is_Elaborate_Body --
      -----------------------

      function Is_Elaborate_Body
        (This : in Tree_Node_Access)
         return Boolean
      is
      begin
         if This.Internal_Spec_With_Body = Unknown then
            Retrive_Pragmas (This);
         end if;

         if This.Internal_Spec_With_Body = Extended_True then
            return True;
         else
            return False;
         end if;
      end Is_Elaborate_Body;

      ---------------------
      -- Retrive_Pragmas --
      ---------------------

      procedure Retrive_Pragmas
        (This : in Tree_Node_Access)
      is
      begin
         if Is_Nil (This.Unit) then
            return;
         end if;

         declare
            Pragma_List : constant Asis.Pragma_Element_List :=
               Asis.Elements.Corresponding_Pragmas
                  (Asis.Elements.Unit_Declaration (This.Unit));
         begin
            for Index in Pragma_List'Range loop
               if Pragma_Kind (Pragma_List (Index).all) = A_Pure_Pragma then
                  This.Internal_Pure := Extended_True;
               end if;

               if Pragma_Kind (Pragma_List (Index).all) =
                 A_Preelaborate_Pragma
               then
                  This.Internal_Preelaborate := Extended_True;
               end if;

               if Pragma_Kind (Pragma_List (Index).all) =
                 An_Elaborate_Body_Pragma
               then
                  This.Internal_Spec_With_Body := Extended_True;
               end if;

            end loop;
         end;

         if This.Internal_Pure = Unknown then
            This.Internal_Pure := Extended_False;
         end if;

         if This.Internal_Preelaborate = Extended_True then
            This.Internal_Preelaborate := Extended_False;
         end if;

         if This.Internal_Spec_With_Body = Unknown then
            This.Internal_Spec_With_Body := Extended_False;
         end if;
      end Retrive_Pragmas;

      ------------------
      -- Is_Skip_Spec --
      ------------------

      function Is_Skip_Spec
        (This : in Tree_Node_Access)
         return Boolean
      is
      begin
         return This.Skip_Spec;
      end Is_Skip_Spec;

      ---------------
      -- Skip_Spec --
      ---------------

      procedure Skip_Spec
        (This  : in Tree_Node_Access;
         Value : in Boolean)
      is
      begin
         This.Skip_Spec := Value;
      end Skip_Spec;

      --------------
      -- Get_Spec --
      --------------

      function Get_Spec
        (This : in Tree_Node_Access)
         return Compilation_Unit
      is
      begin
         return This.Unit;
      end Get_Spec;

      --------------
      -- Get_Body --
      --------------

      function Get_Body
        (This : in Tree_Node_Access)
         return Compilation_Unit
      is
      begin
         return This.Unit_Body;
      end Get_Body;

      -----------
      -- Nexts --
      -----------

      function Nexts
        (This : in Tree_Node_Access)
         return Tree_Node_Array_Access
      is
      begin
         return This.Next;
      end Nexts;

      --------------
      -- Finalize --
      --------------

      procedure Finalize
        (This : in out Root_Tree)
      is
         Node : Tree_Node_Access;
      begin
         if This.Next /= null then
            for Index in This.Next.all'Range loop
               Node := This.Next.all (Index);
               if Node /= null then
                  Deallocate (Node);
               end if;
            end loop;

            Deallocate (This.Next);
         end if;

         Deallocate (This.Units);
      end Finalize;

      -- Finalize --
      procedure Finalize
        (This : in out Tree_Node)
      is
         Node : Tree_Node_Access;
      begin
         if This.Next /= null then
            for Index in This.Next.all'Range loop
               Node := This.Next.all (Index);
               if Node /= null then
                  Deallocate (Node);
               end if;
            end loop;

            Deallocate (This.Next);
         end if;

         if This.Prevs /= null then
            for Index in This.Prevs.all'Range loop
               Remove (This.Prevs (Index).Next, This.Self);
            end loop;

            Deallocate (This.Prevs);
         end if;

         Deallocate (This.Circular);
         Deallocate (This.Missing);
         Deallocate (This.Inconsistent);
         Deallocate (This.Body_Dependences);
      end Finalize;

      ----------
      -- Find --
      ----------

      function Find
        (This : in Root_Tree_Access;
         Unit : in Compilation_Unit)
         return Tree_Node_Access
      is
         Index : aliased Positive;
      begin
         if This.Units = null then
            return null;
         end if;

         if Find
           (This.Units, Unit, 1, This.Units.all'Last, Index'Unchecked_Access)
         then
            return This.Units.all (Index).Node;
         else
            return null;
         end if;
      end Find;

      ------------
      -- Append --
      ------------

      function Append
        (List : in Tree_Node_Array_Access;
         Node : in Tree_Node_Access)
         return Tree_Node_Array_Access
      is
      begin
         return Add_Node (List, Node);
      end Append;

      --------------
      -- Add_Node --
      --------------

      function Add_Node
        (List : in Tree_Node_Array_Access;
         Node : in Tree_Node_Access)
         return Tree_Node_Array_Access
      is
         Array_Access : Tree_Node_Array_Access := List;
      begin
         if Array_Access = null then
            Array_Access := new Tree_Node_Array (1 .. 1);
         else
            declare
               Tmp_Array : Tree_Node_Array_Access :=
                 new Tree_Node_Array (1 .. Array_Access.all'Length + 1);
            begin
               Tmp_Array (1 .. Array_Access.all'Length) := Array_Access.all;
               Deallocate (Array_Access);
               Array_Access := Tmp_Array;
            end;
         end if;

         Array_Access.all (Array_Access.all'Last) := Node;
         return Array_Access;
      end Add_Node;

      ------------
      -- Remove --
      ------------

      procedure Remove
        (List : in out Tree_Node_Array_Access;
         Node : in     Tree_Node_Access)
      is
      begin
         if List = null or else Node = null then
            return;
         end if;

         for Index in List'Range loop
            if List (Index) = Node then
               List (Index) := null;
               return;
            end if;
         end loop;
      end Remove;

      -- Remove --
      function Remove
        (List : in Tree_Node_Array_Access;
         Node : in Tree_Node_Access)
         return Tree_Node_Array_Access
      is
         Internal_List : Tree_Node_Array_Access := List;
      begin
         if Internal_List = null
           or else Node = null
         then
            return Internal_List;
         end if;

         for Index in List'Range loop
            if Internal_List (Index) = Node then
               if List'Length = 1 then
                  Deallocate (Internal_List);
                  return null;
               else
                  declare
                     New_Arry : constant Tree_Node_Array_Access :=
                        new Tree_Node_Array (1 .. List'Length - 1);
                  begin
                     New_Arry (1 .. Index - 1) := List (1 .. Index - 1);

                     New_Arry (Index .. New_Arry'Last) :=
                       List (Index + 1 .. List'Last);

                     Deallocate (Internal_List);
                     return New_Arry;
                  end;
               end if;
            end if;
         end loop;

         return List;
      end Remove;

      ----------------------
      -- Add_Node_Ordered --
      ----------------------

      function Add_Node_Ordered
        (List : in Unit_Node_Array_Access;
         Node : in Tree_Node_Access)
         return Unit_Node_Array_Access
      is
         procedure Process
           (Unit : Compilation_Unit);

         Array_Access : Unit_Node_Array_Access := List;
         Index : aliased Positive;

         procedure Process
           (Unit : Compilation_Unit)
         is
         begin
            if Array_Access = null then
               Array_Access := new Unit_Node_Array (1 .. 1);
               Array_Access.all (1) := (Unit, Node);
            else
               if Find
                 (Array_Access, Unit,
                  1, Array_Access.all'Last, Index'Unchecked_Access)
               then
                  raise Use_Error;
               end if;

               declare
                  Tmp_Array : Unit_Node_Array_Access :=
                    new Unit_Node_Array (1 .. Array_Access.all'Length + 1);
               begin
                  Tmp_Array (1 .. Index - 1) :=
                    Array_Access.all (1 .. Index - 1);

                  Tmp_Array (Index) := (Unit, Node);

                  Tmp_Array (Index + 1 .. Tmp_Array.all'Last) :=
                    Array_Access.all (Index .. Array_Access.all'Last);

                  Deallocate (Array_Access);
                  Array_Access := Tmp_Array;
               end;
            end if;
         end Process;

      begin
         if not Is_Nil (Node.Unit) then
            Process (Node.Unit);
         end if;

         if not Is_Nil (Node.Unit_Body) then
            Process (Node.Unit_Body);
         end if;

         return Array_Access;
      end Add_Node_Ordered;

      ----------
      -- Find --
      ----------

      function Find
        (List  : in Unit_Node_Array_Access;
         Unit  : in Compilation_Unit;
         From  : in Positive;
         To    : in Positive;
         Index : in Positive_Access)
         return Boolean
      is
         L, H, I : Natural;
         C       : Integer;
         Result  : Boolean := False;

      begin
         L := From;
         H := To;

         while L <= H loop
            I := (L + H) / 2;
            C := Compare (List.all (I).Unit, Unit);

            if C < 0 then
               L := I + 1;
            else
               H := I - 1;

               if C = 0 then
                  Result := True;
                  L      := I;
               end if;
            end if;
         end loop;

         Index.all := L;
         return Result;
      end Find;

      -------------
      -- Compare --
      -------------

      function Compare
        (Left  : in Compilation_Unit;
         Right : in Compilation_Unit)
         return Integer
      is
         use Asis;
         use System;
      begin
         if Left.all'Address < Right.all'Address then
            return -1;

         elsif Left.all'Address > Right.all'Address then
            return 1;

         else
            return 0;
         end if;
      end Compare;

      -------------
      -- In_List --
      -------------

      function In_List
        (List : in Compilation_Unit_List_Access;
         Last : in ASIS_Integer;
         Unit : in Compilation_Unit)
         return Boolean
      is
      begin
         for Index in 1 .. Last loop
            if Asis.Compilation_Units.Is_Identical (List (Index), Unit) then
               return True;
            end if;
         end loop;

         return False;
      end In_List;

      ----------------------
      -- Remove_From_List --
      ----------------------

      procedure Remove_From_List
        (List : in out Compilation_Unit_List_Access;
         Unit : in     Compilation_Unit)
      is
      begin
         if List = null then
            return;
         end if;

         for Index in List'Range loop
            if Is_Identical (List (Index), Unit) then
               if List'Length = 1 then
                  Deallocate (List);
               else
                  declare
                     Internal : constant Compilation_Unit_List_Access :=
                        new Compilation_Unit_List (1 .. List'Length - 1);
                  begin
                     Internal (1 .. Index - 1) := List (1 .. Index - 1);

                     Internal (Index .. Internal'Last) :=
                       List (Index + 1 .. List'Last);

                     Deallocate (List);
                     List := Internal;
                  end;
               end if;

               exit;
            end if;
         end loop;
      end Remove_From_List;

      -- Remove_From_List --
      procedure Remove_From_List
        (List : in out Compilation_Unit_List;
         From : in     List_Index;
         Unit : in     Compilation_Unit)
      is
      begin
         for Index in From .. List'Last loop
            if Is_Identical (List (Index), Unit) then
               List (Index) := Nil_Compilation_Unit;
               return;
            end if;
         end loop;
      end Remove_From_List;

      ------------
      -- Append --
      ------------

      function Append
        (List : in Compilation_Unit_List_Access;
         Unit : in Compilation_Unit)
         return Compilation_Unit_List_Access
      is
         Result : Compilation_Unit_List_Access := List;
      begin
         if Result = null then
            Result := new Compilation_Unit_List (1 .. 1);
         else
            declare
               Tmp_Array : Compilation_Unit_List_Access :=
                 new Compilation_Unit_List (1 .. Result.all'Length + 1);
            begin
               Tmp_Array (1 .. Result.all'Length) := Result.all;
               Deallocate (Result);
               Result := Tmp_Array;
            end;
         end if;

         Result.all (Result.all'Last) := Unit;
         return Result;
      end Append;

      -- Append --
      function Append
        (List  : in Compilation_Unit_List_Access;
         Units : in Compilation_Unit_List)
         return Compilation_Unit_List_Access
      is
         Result : Compilation_Unit_List_Access := List;
      begin
         if Result = null then
            Result := new Compilation_Unit_List (1 .. Units'Length);
            Result.all := Units;
         else
            declare
               Tmp_Array : Compilation_Unit_List_Access :=
                 new Compilation_Unit_List
                   (1 .. Result.all'Length + Units'Length);
            begin
               Tmp_Array (1 .. Result.all'Length) := Result.all;
               Tmp_Array (Result.all'Length + 1 .. Tmp_Array'Last) := Units;
               Deallocate (Result);
               Result := Tmp_Array;
            end;
         end if;

         return Result;
      end Append;

      ---------------------
      -- Is_Inconsistent --
      ---------------------

      function Is_Inconsistent
        (Unit : in Compilation_Unit)
         return Boolean
      is
      begin
         return True;
      end Is_Inconsistent;

      -----------------------
      -- Is_Source_Changed --
      -----------------------

      function Is_Source_Changed
        (Unit : in Compilation_Unit)
         return Boolean
      is
      begin
         return False;
      end Is_Source_Changed;

   end Utils;

end Asis.Compilation_Units.Relations;

------------------------------------------------------------------------------
--  Copyright (c) 2006, Maxim Reznik, Andry Ogorodnik
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
