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

      procedure Remove_From_List
        (List : in out Compilation_Unit_List;
         From : in     List_Index;
         Unit : in     Compilation_Unit);

      function Append
        (List : in Compilation_Unit_List_Access;
         Unit : in Compilation_Unit)
         return Compilation_Unit_List_Access;

      function Append
        (List  : in Compilation_Unit_List_Access;
         Units : in Compilation_Unit_List)
         return Compilation_Unit_List_Access;

      --  Tree_Node  --
      type Tree_Node is
        new Ada.Finalization.Limited_Controlled with private;

      type Tree_Node_Access is access all Tree_Node;

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

      function Append_Parent
        (This : in Tree_Node_Access;
         Unit : in Compilation_Unit)
         return Tree_Node_Access;

      procedure Add_Thread
        (This      : in     Tree_Node_Access;
         To_Node   : in     Tree_Node_Access;
         From_Tree : in out Tree_Node_Access);

      function Add_Child
        (This      : in Tree_Node_Access;
         Node      : in Tree_Node_Access;
         Spec_Unit : in Compilation_Unit)
         return Tree_Node_Access;

      function Add_Child_Body
        (This      : in Tree_Node_Access;
         Node      : in Tree_Node_Access;
         Spec_Unit : in Compilation_Unit;
         Body_Unit : in Compilation_Unit;
         Skip_Spec : in Boolean := False)
         return Tree_Node_Access;

      procedure Glue_Nodes
        (This    : in Tree_Node_Access;
         Node    : in Tree_Node_Access;
         To_Node : in Tree_Node_Access);

      procedure Glue_Nodes_Checked
        (This    : in Tree_Node_Access;
         Node    : in Tree_Node_Access;
         To_Node : in Tree_Node_Access);

      procedure Clear
        (This : in out Tree_Node);

      function Find
        (This : in Tree_Node;
         Unit : in Compilation_Unit)
         return Tree_Node_Access;

      type Orders is (Ascending, Descending);

      procedure Check
        (This        : in Tree_Node_Access;
         Order       : in Orders;
         The_Context : in Asis.Context);

      function Generate_Relationship
        (This       : in Tree_Node_Access;
         Limit_List : in Utils.Compilation_Unit_List_Access;
         List_Last  : in ASIS_Integer;
         Order      : in Orders)
         return Relationship;

      function Is_Skip_Spec
        (This : in Tree_Node_Access)
         return Boolean;

      procedure Skip_Spec
        (This  : in Tree_Node_Access;
         Value : in Boolean);

      function Nexts
        (This : in Tree_Node_Access)
         return Tree_Node_Array_Access;

      function Spec
        (This : in Tree_Node_Access)
         return Compilation_Unit;

      Use_Error : exception;

   private

      type Unit_Node is record
         Unit : Compilation_Unit;
         Node : Tree_Node_Access;
      end record;

      type Unit_Node_Array is array (Positive range <>) of Unit_Node;
      type Unit_Node_Array_Access is access all Unit_Node_Array;

      type Tree_Node is
        new Ada.Finalization.Limited_Controlled with record
         Self : Tree_Node_Access := Tree_Node'Unchecked_Access;

         --  ссылка на предыдущий елемент
         Prev  : Tree_Node_Access := null;
         Prevs : Tree_Node_Array_Access := null;

         --  модуль_компиляции
         Unit      : Compilation_Unit := Nil_Compilation_Unit;
         Unit_Body : Compilation_Unit := Nil_Compilation_Unit;
         Skip_Spec : Boolean := False;

         Added      : Boolean := False;
         Consistent : Boolean := True;

         --  последующие елементы 0-х
         Next : Tree_Node_Array_Access := null;

         --  список окончания "ветвей",
         --  для быстрого изымания оных
         --  а не перебором всех ветвей
         --  заполняет только корневой елемент
         Last_Nodes : Tree_Node_Array_Access := null;

         --  сортированный список всех
         --  елементов для быстрого
         --  определения наличия елемента
         --  в списке
         --  заполняет только корневой елемент
         Units : Unit_Node_Array_Access := null;

         --  список циклических зависимостей
         Circular       : Compilation_Unit_List_Access := null;
         Circular_Added : Boolean := False;

         --  список пропавших юнитов
         Missing       : Compilation_Unit_List_Access := null;
         Missing_Added : Boolean := False;

         --  список несоглассованных юнитов
         Inconsistent       : Compilation_Unit_List_Access := null;
         Inconsistent_Added : Boolean := False;
      end record;

      procedure Finalize
        (This : in out Tree_Node);

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
       (Utils.Tree_Node, Utils.Tree_Node_Access);

   function Get_Ancestors
     (List        : in Asis.Compilation_Unit_List;
      The_Context : in Asis.Context)
      return Utils.Tree_Node_Access;

   function Get_Descendants
     (List        : in Asis.Compilation_Unit_List;
      The_Context : in Asis.Context)
      return Utils.Tree_Node_Access;

   function Get_Supporters
     (List        : in Asis.Compilation_Unit_List;
      The_Context : in Asis.Context)
      return Utils.Tree_Node_Access;

   function Get_Dependents
     (List        : in Asis.Compilation_Unit_List;
      The_Context : in Asis.Context)
      return Utils.Tree_Node_Access;

   function Get_Compilation_Unit
     (Target : in Asis.Element)
      return Asis.Compilation_Unit;

   function Have_With
     (Library : in Compilation_Unit;
      Unit    : in Compilation_Unit)
      return Boolean;

   -------------------------
   --  Elaboration_Order  -- *
   -------------------------

   function Elaboration_Order
     (Compilation_Units : in Asis.Compilation_Unit_List;
      The_Context       : in Asis.Context)
      return Relationship
   is
   begin
      Asis.Implementation.Set_Status
        (Not_Implemented_Error, "Elaboration_Order not implemented");
      raise Asis.Exceptions.ASIS_Failed;

      return Nil_Relationship;
   end Elaboration_Order;

   ---------------------------------
   --  Semantic_Dependence_Order  -- *
   ---------------------------------

   function Semantic_Dependence_Order
     (Compilation_Units : in Asis.Compilation_Unit_List;
      Dependent_Units   : in Asis.Compilation_Unit_List;
      The_Context       : in Asis.Context;
      Relation          : in Asis.Relation_Kinds)
      return Relationship
   is
      Current_Unit_Kind : Asis.Unit_Kinds;

      procedure Check_Compilation_Unit
         (Unit    : in Compilation_Unit;
          Message : in Wide_String);

      procedure Normalize
         (List   : in     Asis.Compilation_Unit_List;
          Result : in     Utils.Compilation_Unit_List_Access;
          Last   :    out ASIS_Integer);

      procedure Clear;

      -- Check_Compilation_Unit --
      procedure Check_Compilation_Unit
         (Unit    : in Compilation_Unit;
          Message : in Wide_String)
      is
      begin
         Current_Unit_Kind := Unit_Kind (Unit);

         if Current_Unit_Kind = Not_A_Unit
            or else Current_Unit_Kind = A_Nonexistent_Declaration
            or else Current_Unit_Kind = A_Nonexistent_Body
            or else Current_Unit_Kind = A_Configuration_Compilation
         then
            Asis.Implementation.Set_Status
              (Data_Error, "Semantic_Dependence_Order "
               & Message & " invalid " & Unit_Full_Name (Unit));

            raise Asis.Exceptions.ASIS_Inappropriate_Compilation_Unit;
         end if;

         if not Asis.Ada_Environments.Is_Equal
           (Enclosing_Context (Unit), The_Context)
         then
            Asis.Implementation.Set_Status
              (Data_Error, "Semantic_Dependence_Order "
               & Message & " invalid context " & Unit_Full_Name (Unit));

            raise Asis.Exceptions.ASIS_Inappropriate_Compilation_Unit;
         end if;
      end Check_Compilation_Unit;

      Compilation_Units_Last : ASIS_Integer := 0;

      Normalized_Compilation_Units :
         Utils.Compilation_Unit_List_Access := null;

      Dependent_Units_Last : ASIS_Integer := 0;

      Normalized_Dependent_Units :
         Utils.Compilation_Unit_List_Access := null;

      -- Normalize --
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

            if Assigned (Unit)
               and then Unit_Kind (Unit) /= An_Unknown_Unit
            then
               if not Utils.In_List (Result, Last, Unit) then
                  Last := Last + 1;
                  Result (Last) := List (Index);
               end if;
            end if;
         end loop;
      end Normalize;

      Tree : Utils.Tree_Node_Access := null;

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
           (Compilation_Units (Index), "Compilation_Unit");
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
            Check_Compilation_Unit (Dependent_Units (Index), "Dependent_Unit");
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

            Utils.Check (Tree, Utils.Ascending, The_Context);
            declare
               Relation : Relationship := Utils.Generate_Relationship
                  (Tree, null, 0, Utils.Ascending);
            begin
               Clear;
               return Relation;
            end;

         when Descendants =>
            Tree := Get_Descendants
              (Normalized_Compilation_Units
                 (1 .. Compilation_Units_Last), The_Context);

            Utils.Check (Tree, Utils.Ascending, The_Context);
            declare
               Relation : Relationship := Utils.Generate_Relationship
                 (Tree, Normalized_Dependent_Units,
                  Dependent_Units_Last, Utils.Descending);
            begin
               Clear;
               return Relation;
            end;

         when Supporters =>
            Tree := Get_Supporters
              (Normalized_Compilation_Units (1 .. Compilation_Units_Last),
               The_Context);

            Utils.Check (Tree, Utils.Descending, The_Context);

            declare
               Relation : Relationship := Utils.Generate_Relationship
                 (Tree, null, 0, Utils.Descending);
            begin
               Clear;
               return Relation;
            end;

         when Dependents =>
            Tree := Get_Dependents
              (Normalized_Compilation_Units (1 .. Compilation_Units_Last),
               The_Context);

            Utils.Check (Tree, Utils.Ascending, The_Context);

            declare
               Relation : Relationship := Utils.Generate_Relationship
                 (Tree, Normalized_Dependent_Units,
                  Dependent_Units_Last, Utils.Descending);
            begin
               Clear;
               return Relation;
            end;

         when Family =>
            Clear;

            Asis.Implementation.Set_Status
              (Not_Implemented_Error,
               "Semantic_Dependence_Order not implemented");
            raise Asis.Exceptions.ASIS_Failed;

         when Needed_Units =>
            Clear;

            Asis.Implementation.Set_Status
              (Not_Implemented_Error,
               "Semantic_Dependence_Order not implemented");
            raise Asis.Exceptions.ASIS_Failed;
      end case;

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
      return Utils.Tree_Node_Access
   is
      use Utils;

      Unit  : Compilation_Unit;
      Kinds : Unit_Kinds;

      Result   : Tree_Node_Access := null;
      Tmp_Tree : Tree_Node_Access := null;
      Node     : Tree_Node_Access := null;

      function Append_Node
        (Unit : in Compilation_Unit)
         return Boolean;

      procedure Retrive_Declarations;

      -- Append_Node --
      function Append_Node
        (Unit : in Compilation_Unit)
         return Boolean
      is
      begin
         if Result /= null then
            Node := Find (Result.all, Unit);
         else
            Node := null;
         end if;

         if Node /= null then
            Add_Thread (Result, Node, Tmp_Tree);
            return True;
         else
            Tmp_Tree := Append_Parent (Tmp_Tree, Unit);
            return False;
         end if;
      end Append_Node;

      -- Retrive_Declarations --
      procedure Retrive_Declarations is begin
         while Unit_Kind (Unit) in
           A_Procedure .. A_Generic_Package_Renaming
         loop
            if Append_Node (Unit) then
               return;
            end if;

            Unit := Corresponding_Parent_Declaration (Unit);
         end loop;

         if not Is_Nil (Unit) then
            if Append_Node (Unit) then
               return;
            end if;

            --  add Standart as root
            if Append_Node
              (Library_Unit_Declaration ("Standard", The_Context))
            then
               return;
            end if;
         end if;
      end Retrive_Declarations;

   begin
      for Index in List'Range loop
         if Tmp_Tree /= null then
            Asis.Implementation.Set_Status
              (Asis.Errors.Internal_Error,
               "Bug (or inapropriate use) detected in "
               & "Asis.Compilation_Units.Relations.Semantic_Dependence_Order"
               & " (Ancestors)");

            raise Asis.Exceptions.ASIS_Failed;
         end if;

         Unit := List (Index);

         if Result = null
           or else Find (Result.all, Unit) = null
         then
            Kinds := Unit_Kind (Unit);

            if Kinds in A_Subunit then
               Asis.Implementation.Set_Status
                 (Data_Error, "Subunit not valid for Ancestors request "
                  & Unit_Full_Name (Unit));

               raise Asis.Exceptions.ASIS_Inappropriate_Compilation_Unit;

            elsif Kinds in A_Library_Unit_Body then
               Tmp_Tree := new Tree_Node;
               Unit := Corresponding_Parent_Declaration (Unit, The_Context);
               Retrive_Declarations;
            else
               Tmp_Tree := new Tree_Node;
               Retrive_Declarations;
            end if;

            if Result = null then
               Result   := Tmp_Tree;
               Tmp_Tree := null;
            end if;
         end if;
      end loop;

      Deallocate (Tmp_Tree);
      return Result;
   exception
      when others =>
         Deallocate (Tmp_Tree);
         Deallocate (Result);
         raise;
   end Get_Ancestors;

   ---------------------
   -- Get_Descendants --
   ---------------------

   function Get_Descendants
     (List        : in Asis.Compilation_Unit_List;
      The_Context : in Asis.Context)
      return Utils.Tree_Node_Access
   is
      use Utils;

      Result      : Tree_Node_Access := new Tree_Node;
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
         Children_List : Asis.Compilation_Unit_List :=
           Corresponding_Children (Target, The_Context);
         Exist_Node : Utils.Tree_Node_Access := null;

         -- Process --
         function Process
            (Index : in List_Index)
            return Boolean
         is
         begin
            if Is_Nil (Unit) then
               return False;
            end if;

            Kinds      := Unit_Kind (Unit);
            Exist_Node := Find (Result.all, Unit);

            if Exist_Node /= null then
               Glue_Nodes (Result, Node, Exist_Node);
               Second_Unit := Nil_Compilation_Unit;

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
                 and then not Is_Identical (Second_Unit, Unit) then
                  Exist_Node := Add_Child_Body
                    (Result, Node, Unit, Second_Unit);

                  Remove_From_List (Children_List, Index + 1, Second_Unit);
               else
                  Exist_Node := Add_Child (Result, Node, Unit);
               end if;

            elsif Kinds in A_Library_Unit_Body then
               Second_Unit := Corresponding_Declaration (Unit, The_Context);

               if not Is_Nil (Second_Unit)
                  and then not Is_Identical (Second_Unit, Unit)
               then
                  Exist_Node := Add_Child_Body
                    (Result, Node, Second_Unit, Unit);

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
      Declarations_List := new Asis.Compilation_Unit_List (1 .. List'Length);

      for Index in List'Range loop
         Unit  := List (Index);
         Kinds := Unit_Kind (Unit);

         --  eliminate A_Subunit
         if Kinds not in A_Subunit then
            if Kinds in A_Library_Unit_Body then
               --  get declaration (spec+body)
               Unit  := Corresponding_Declaration (Unit);
               Kinds := Unit_Kind (Unit);
            end if;

            if Kinds = A_Package
              or else Kinds = A_Generic_Package
              or else Kinds = A_Package_Instance
            then
               if not In_List
                 (Declarations_List, Declarations_Last, Unit)
               then
                  Declarations_Last := Declarations_Last + 1;
                  Declarations_List (Declarations_Last) := Unit;
               end if;
            end if;
         end if;
      end loop;

      for Index in 1 .. Declarations_Last loop
         Unit := Declarations_List (Index);

         if Find (Result.all, Unit) = null then
            Second_Unit := Corresponding_Body (Unit, The_Context);

            if not Is_Identical (Second_Unit, Unit) then
               Retrive
                 (Unit, Add_Child_Body (Result, null, Unit, Second_Unit));
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
      return Utils.Tree_Node_Access
   is
      use Utils;

      Unit  : Compilation_Unit;
      Kinds : Unit_Kinds;

      Result : Tree_Node_Access := new Tree_Node;
      Node   : Tree_Node_Access := null;

      Std : Compilation_Unit := Library_Unit_Declaration ("Standard", The_Context);

      procedure Append_Standart
        (Node : in Tree_Node_Access);

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
        (Unit : in Compilation_Unit;
         Node : in Tree_Node_Access);

      procedure Check_10_1_1_26c_26b
        (Unit : in Compilation_Unit;
         Node : in Tree_Node_Access);

      -- Append_Standart --
      procedure Append_Standart
        (Node : in Tree_Node_Access)
      is
         Exist_Node : Tree_Node_Access;
      begin
         Exist_Node := Find (Result.all, Std);

         if Exist_Node = null then
            Exist_Node := Add_Child (Result, Node, Std);
         else
            if Node /= null then
               Glue_Nodes_Checked (Result, Node, Exist_Node);
            end if;
         end if;
      end Append_Standart;

      -- Retrive --
      procedure Retrive
        (Unit       : in Compilation_Unit;
         Node       : in Tree_Node_Access;
         First_Node : in Boolean := False)
      is
      begin
         if Is_Nil (Unit) then
            return;
         end if;

         Kinds := Unit_Kind (Unit);

         if Kinds in A_Nonexistent_Declaration .. An_Unknown_Unit then
            Append_Standart (Node);

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
         Parent     : Compilation_Unit;
         vNode      : Tree_Node_Access := Node;
         Exist_Node : Tree_Node_Access;
      begin
         if not First_Node then
            Exist_Node := Find (Result.all, Unit);

            if Exist_Node = null then
               vNode := Add_Child (Result, vNode, Unit);

               if Is_Identical (Unit, Std) then
                  return;
               end if;

               Check_10_1_1_26c_26b (Unit, vNode);
               Retrive_With_Clause (Unit, vNode);
            else
               if vNode /= null then
                  Glue_Nodes_Checked (Result, vNode, Exist_Node);
                  return;
               end if;
            end if;
         else
            if Is_Identical (Unit, Std) then
               return;
            end if;

            Check_10_1_1_26c_26b (Unit, vNode);
            Retrive_With_Clause (Unit, vNode);
         end if;

         Parent := Corresponding_Parent_Declaration (Unit, The_Context);

         while Unit_Kind (Parent) in
           A_Procedure .. A_Generic_Package_Renaming
         loop
            Exist_Node := Find (Result.all, Parent);

            if Exist_Node = null then
               vNode := Add_Child (Result, vNode, Parent);
               Check_10_1_1_26c_26b (Parent, vNode);
               Retrive_With_Clause (Parent, vNode);
            else
               if vNode /= null then
                  Glue_Nodes_Checked (Result, vNode, Exist_Node);
                  return;
               end if;
            end if;

            Parent := Corresponding_Parent_Declaration (Parent, The_Context);
         end loop;

         Retrive (Parent, vNode);
      end Retrive_Declarations;

      -- Retrive_Body --
      procedure Retrive_Body
        (Unit       : in Compilation_Unit;
         Node       : in Tree_Node_Access;
         First_Node : in Boolean)
      is
         Exist_Node : Tree_Node_Access := Node;
      begin
         if not First_Node then
            Exist_Node := Find (Result.all, Unit);

            if Exist_Node = null then
               Exist_Node := Add_Child (Result, Node, Unit);
               Check_10_1_1_26c_26b (Unit, Exist_Node);
               Retrive_With_Clause (Unit, Exist_Node);
            else
               if Node /= null then
                  Glue_Nodes_Checked (Result, Node, Exist_Node);
                  return;
               end if;
            end if;
         else
            Check_10_1_1_26c_26b (Unit, Node);
            Retrive_With_Clause (Unit, Node);
         end if;

         Retrive
           (Corresponding_Parent_Declaration (Unit, The_Context),
            Exist_Node);
      end Retrive_Body;

      --  Retrive_Subunit  --
      procedure Retrive_Subunit
        (Unit : in Compilation_Unit;
         Node : in Tree_Node_Access)
      is
         Parent     : Compilation_Unit;
         vNode      : Tree_Node_Access := Node;
         Exist_Node : Tree_Node_Access;
      begin
         Check_10_1_1_26c_26b (Unit, null);
         Retrive_With_Clause (Unit, null);
         Parent := Corresponding_Subunit_Parent_Body (Unit);

         while Unit_Kind (Parent) in A_Subunit loop
            Exist_Node := Find (Result.all, Parent);

            if Exist_Node = null then
               vNode := Add_Child (Result, vNode, Parent);
               Check_10_1_1_26c_26b (Parent, vNode);
               Retrive_With_Clause (Parent, vNode);
            else
               if vNode /= null then
                  Glue_Nodes_Checked (Result, vNode, Exist_Node);
                  return;
               end if;
            end if;

            Parent := Corresponding_Subunit_Parent_Body (Parent);
         end loop;

         Retrive (Parent, vNode);
      end Retrive_Subunit;

      -- Retrive_With_Clause --
      procedure Retrive_With_Clause
        (Unit : in Compilation_Unit;
         Node : in Tree_Node_Access)
      is
         With_List : constant Asis.Context_Clause_List :=
           Asis.Elements.Context_Clause_Elements (Unit);

         Internal_Unit : Compilation_Unit;
      begin
         for Index in With_List'Range loop
            if Clause_Kind (With_List (Index).all) = A_With_Clause then

               Internal_Unit := Get_Compilation_Unit (With_List (Index));

               --  Send warning if null !!!
               if not Is_Nil (Internal_Unit) then
                  Retrive (Internal_Unit, Node);
               end if;
            end if;
         end loop;
      end Retrive_With_Clause;

      -- Check_10_1_1_26c_26b --
      procedure Check_10_1_1_26c_26b
        (Unit : in Compilation_Unit;
         Node : in Tree_Node_Access)
      is
         --  10.1.1 (26.c)
         --  10.1.1 (26.b)

         Except : Compilation_Unit := Library_Unit_Declaration
            ("Ada.Exceptions", The_Context);

         Sys : Compilation_Unit := Library_Unit_Declaration
            ("System", The_Context);

         Is_Except : Boolean;
         Is_Sys    : Boolean;

         type State_Information is record
            Exceptions : Boolean := False;
            System     : Boolean := False;
         end record;

         Control : Traverse_Control := Continue;
         State   : State_Information;

         procedure Pre_Operation
           (Element : in     Asis.Element;
            Control : in out Traverse_Control;
            State   : in out State_Information)
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
            State   : in out State_Information)
         is
         begin
            null;
         end Post_Operation;

         procedure Check_Choice_Iterator is new
           Asis.Iterator.Traverse_Element
             (State_Information, Pre_Operation, Post_Operation);

      begin
         Is_Except := Is_Identical (Unit, Except);
         Is_Sys    := Is_Identical (Unit, Sys);

         Check_Choice_Iterator
           (Asis.Elements.Unit_Declaration (Unit), Control, State);

         if State.Exceptions then
            Retrive (Except, Node);
         end if;

         if State.System then
            Retrive (Sys, Node);
         end if;
      end Check_10_1_1_26c_26b;

   begin
      for Index in List'Range loop
         Unit := List (Index);

         if Find (Result.all, Unit) = null then
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
      return Utils.Tree_Node_Access
   is
      use Utils;

      Result : Tree_Node_Access := new Tree_Node;

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
         Exist_Node := Find (Result.all, Unit);
         Kinds      := Unit_Kind (Unit);

         if Kinds in A_Procedure .. A_Generic_Package then
            if Exist_Node /= null then
               Glue_Nodes_Checked (Result, Node, Exist_Node);

               if not Is_Skip_Spec (Exist_Node) then
                  Glued := Append (Glued, Exist_Node);
               else
                  Skip_Spec (Exist_Node, False);
               end if;
            else
               Second_Unit := Corresponding_Body (Unit, The_Context);
               Exist_Node  := Add_Child_Body (Result, Node, Unit, Second_Unit);
            end if;

         elsif Kinds in A_Library_Unit_Body then
            if Exist_Node /= null then
               Glue_Nodes_Checked (Result, Node, Exist_Node);
               Glued := Append (Glued, Exist_Node);
            else
               Second_Unit := Corresponding_Declaration (Unit, The_Context);

               if not Is_Nil (Second_Unit)
                  and then not Is_Identical (Second_Unit, Unit)
               then
                  Exist_Node := Find (Result.all, Second_Unit);

                  if Exist_Node /= null then
                     Glue_Nodes_Checked (Result, Node, Exist_Node);
                     Glued := Append (Glued, Exist_Node);
                  else
                     Exist_Node := Add_Child_Body
                        (Result, Node, Second_Unit, Unit, True);
                  end if;
               else
                  Exist_Node := Add_Child (Result, Node, Unit);
               end if;
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

      -- Have_Except --
      function Have_Except
        (Unit : in Compilation_Unit)
        return Boolean
      is
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

         procedure Post_Operation
           (Element : in     Asis.Element;
            Control : in out Traverse_Control;
            State   : in out Boolean)
         is
         begin
            null;
         end Post_Operation;

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

         procedure Post_Operation
           (Element : in     Asis.Element;
            Control : in out Traverse_Control;
            State   : in out Boolean)
         is
         begin
            null;
         end Post_Operation;

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
         Exist_Node : Tree_Node_Access := null;
         Glued      : Tree_Node_Array_Access := null;
      begin
         if Is_Nil (Unit) then
            return;
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

                  Kinds := Unit_Kind (Children);
                  Exist_Node := Find (Result.all, Children);

                  if Exist_Node /= null then
                     Glue_Nodes_Checked (Result, Node, Exist_Node);
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
                           Exist_Node := Add_Child_Body
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
                           Exist_Node := Add_Child_Body
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
                  if Have_With (Library, Unit) then
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
         begin
            if Next /= null then
               for Index in Next'Range loop
                  Next_Node := Next (Index);

                  if Glued = null
                    or else not Utils.In_List
                      (Glued, Glued.all'Last, Next_Node)
                  then
                     if not Is_Skip_Spec (Next_Node) then
                        Retrive (Spec (Next_Node), Next_Node);
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
      for Index in List'Range loop
         Unit := List (Index);

         if Find (Result.all, Unit) = null then
            Kinds := Unit_Kind (Unit);

            if Kinds in A_Procedure .. A_Generic_Package_Renaming
            then
               Body_Unit := Corresponding_Body (Unit, The_Context);

               if not Is_Identical (Body_Unit, Unit) then
                  Retrive (Unit, Add_Child_Body
                           (Result, null, Unit, Body_Unit, True));
               else
                  Retrive (Unit, Add_Child (Result, null, Unit));
               end if;
            end if;
         end if;
      end loop;

      return Result;
   exception
      when others =>
         Deallocate (Result);
         raise;
   end Get_Dependents;

   --------------------------
   -- Get_Compilation_Unit --
   --------------------------

   function Get_Compilation_Unit
     (Target : in Asis.Element)
      return Asis.Compilation_Unit
   is
      use Utils;
      Names : constant Asis.Name_List := Asis.Clauses.Clause_Names (Target);

      Declaration : Asis.Element;
      Unit        : Asis.Compilation_Unit;
      Result_List : Compilation_Unit_List_Access := null;
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
            Unit := Asis.Elements.Enclosing_Compilation_Unit (Declaration);

            if Unit_Kind (Unit) in
              A_Procedure .. A_Generic_Package_Renaming
            then
               Result_List := Append (Result_List, Unit);
            end if;
         end if;
      end loop;

      if Result_List = null then
         return Nil_Compilation_Unit;
      end if;

--        if Result_List.all'Length > 1 then
--           --  Send WARNING !!!
--        end loop;

      declare
         Result : Asis.Compilation_Unit :=
           Result_List.all (Result_List.all'First);
      begin
         Deallocate (Result_List);
         return Result;
      end;
   end Get_Compilation_Unit;

   ---------------
   -- Have_With --
   ---------------

   function Have_With
     (Library : in Compilation_Unit;
      Unit    : in Compilation_Unit)
      return Boolean
   is
      With_List : constant Asis.Context_Clause_List :=
        Asis.Elements.Context_Clause_Elements (Library);

      Internal_Unit : Compilation_Unit;
   begin
      for Index in With_List'Range loop
         if Clause_Kind (With_List (Index).all) = A_With_Clause then

            Internal_Unit := Get_Compilation_Unit (With_List (Index));

            if not Is_Nil (Internal_Unit)
              and then Is_Identical (Internal_Unit, Unit)
            then
               return True;
            end if;
         end if;
      end loop;

      return False;
   end Have_With;

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
         if List = null then
            return False;
         end if;

         for Index in 1 .. Last loop
            if List (Index) = Node then
               return True;
            end if;
         end loop;

         return False;
      end In_List;

      -------------------
      -- Append_Parent --
      -------------------

      function Append_Parent
        (This : in Tree_Node_Access;
         Unit : in Compilation_Unit)
         return Tree_Node_Access
      is
         Node : Tree_Node_Access;
      begin
         if Is_Nil (This.Unit) then
            This.Unit := Unit;

            This.Last_Nodes := Add_Node (This.Last_Nodes, This.Self);
            This.Units      := Add_Node_Ordered (This.Units, This.Self);
            return This;
         end if;

         if This.Prev /= null
            or else Find (This.all, Unit) /= null
         then
            raise Use_Error;
         end if;

         Node := new Tree_Node;

         Node.Unit := Unit;
         This.Prev := Node.Self;
         Node.Next := Add_Node (Node.Next, This.Self);

         Node.Last_Nodes := This.Last_Nodes;
         This.Last_Nodes := null;

         Node.Units := This.Units;
         This.Units := null;
         Node.Units := Add_Node_Ordered (Node.Units, Node.Self);

         return Node;
      end Append_Parent;

      ----------------
      -- Add_Thread --
      ----------------

      procedure Add_Thread
        (This      : in     Tree_Node_Access;
         To_Node   : in     Tree_Node_Access;
         From_Tree : in out Tree_Node_Access)
      is
      begin
         if Is_Nil (From_Tree.Unit)
           or else Is_Nil (This.Unit)
         then
            --  empty tree(s)
            raise Use_Error;
         end if;

         if From_Tree.Prev /= null
           or else This.Prev /= null
         then
            --  not root
            raise Use_Error;
         end if;

         for Index in From_Tree.Units.all'Range loop
            if Find (This.all, From_Tree.Units.all (Index).Unit) /= null then
               raise Use_Error;
            end if;
         end loop;

         To_Node.Next := Add_Node (To_Node.Next, From_Tree.Self);

         for Index in From_Tree.Last_Nodes.all'Range loop
            This.Last_Nodes := Add_Node
              (This.Last_Nodes, From_Tree.Last_Nodes.all (Index));
         end loop;

         Deallocate (From_Tree.Last_Nodes);

         for Index in From_Tree.Units.all'Range loop
            This.Units := Add_Node_Ordered
              (This.Units, From_Tree.Units.all (Index).Node);
         end loop;

         Deallocate (From_Tree.Units);
         From_Tree := null;
      end Add_Thread;

      ---------------
      -- Add_Child --
      ---------------

      function Add_Child
        (This      : in Tree_Node_Access;
         Node      : in Tree_Node_Access;
         Spec_Unit : in Compilation_Unit)
         return Tree_Node_Access
      is
      begin
         if This.Prev /= null then
            --  not root
            raise Use_Error;
         end if;

         declare
            New_Node : Tree_Node_Access := new Tree_Node;
         begin
            New_Node.Unit := Spec_Unit;

            if Node = null then
               This.Next     := Add_Node (This.Next, New_Node.Self);
               New_Node.Prev := This.Self;
            else
               Node.Next     := Add_Node (Node.Next, New_Node.Self);
               New_Node.Prev := Node.Self;
            end if;

            This.Units := Add_Node_Ordered (This.Units, New_Node.Self);
            return New_Node;
         end;
      end Add_Child;

      -- Add_Child_Body --
      function Add_Child_Body
        (This      : in Tree_Node_Access;
         Node      : in Tree_Node_Access;
         Spec_Unit : in Compilation_Unit;
         Body_Unit : in Compilation_Unit;
         Skip_Spec : in Boolean := False)
         return Tree_Node_Access
      is
      begin
         if This.Prev /= null then
            --  not root
            raise Use_Error;
         end if;

         declare
            New_Node : Tree_Node_Access := new Tree_Node;
         begin
            New_Node.Unit      := Spec_Unit;
            New_Node.Unit_Body := Body_Unit;
            New_Node.Skip_Spec := Skip_Spec;

            if Node = null then
               This.Next     := Add_Node (This.Next, New_Node.Self);
               New_Node.Prev := This.Self;
            else
               Node.Next     := Add_Node (Node.Next, New_Node.Self);
               New_Node.Prev := Node.Self;
            end if;

            This.Units := Add_Node_Ordered (This.Units, New_Node.Self);
            return New_Node;
         end;
      end Add_Child_Body;

      ----------------
      -- Glue_Nodes --
      ----------------

      procedure Glue_Nodes
        (This    : in Tree_Node_Access;
         Node    : in Tree_Node_Access;
         To_Node : in Tree_Node_Access)
      is
      begin
         if This.Prev /= null then
            --  not root
            raise Use_Error;
         end if;

         To_Node.Next := Add_Node (To_Node.Next, Node.Self);
      end Glue_Nodes;

      ------------------------
      -- Glue_Nodes_Checked --
      ------------------------

      procedure Glue_Nodes_Checked
        (This    : in Tree_Node_Access;
         Node    : in Tree_Node_Access;
         To_Node : in Tree_Node_Access)
      is
         Circular  : Compilation_Unit_List_Access := null;
         Prev_Node : Tree_Node_Access;
      begin
         if This.Prev /= null then
            --  not root
            raise Use_Error;
         end if;

         if To_Node.Prev = Node then
            return;
         end if;

         if To_Node.Prevs /= null
            and then In_List (To_Node.Prevs, To_Node.Prevs'Last, Node)
         then
            return;
         end if;

         Prev_Node := Node.Prev;

         while Prev_Node /= null loop
            if Prev_Node = To_Node then
               if Circular /= null then
                  for Index in reverse Circular.all'Range loop
                     Node.Circular := Append (Node.Circular, Circular (Index));
                  end loop;

                  Node.Circular := Append (Node.Circular, Node.Unit);

                  Deallocate (Circular);
               else
                  --  2 pair (self and parent)
                  Node.Circular := Append
                    (Node.Circular, (Prev_Node.Unit, Node.Unit));
               end if;

               return;
            end if;

            Circular := Append (Circular, Prev_Node.Unit);
            Prev_Node := Prev_Node.Prev;
         end loop;

         if Circular /= null then
            Deallocate (Circular);
         end if;

         Node.Next     := Add_Node (Node.Next, To_Node.Self);
         To_Node.Prevs := Add_Node (To_Node.Prevs, Node.Self);
      end Glue_Nodes_Checked;

      -----------
      -- Clear --
      -----------

      procedure Deallocate is
        new Ada.Unchecked_Deallocation
          (Tree_Node, Tree_Node_Access);

      procedure Clear
        (This : in out Tree_Node)
      is
         Node : Tree_Node_Access;
      begin
         if This.Next /= null then
            for Index in This.Next.all'Range loop
               Node := This.Next.all (Index);
               if Node /= null then
                  Clear (Node.all);
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

         Deallocate (This.Last_Nodes);
         Deallocate (This.Units);
         Deallocate (This.Circular);
         Deallocate (This.Missing);
         Deallocate (This.Inconsistent);
      end Clear;

      -----------
      -- Check --
      -----------

      procedure Check
        (This        : in Tree_Node_Access;
         Order       : in Orders;
         The_Context : in Asis.Context)
      is
         Kinds, Parent_Kinds : Unit_Kinds;
         Perent_Unit         : Compilation_Unit;

         procedure Check_Consistent
           (Node : in Tree_Node_Access);

         function Set_Inconsistent
           (Node  : in Tree_Node_Access;
            Prev  : in Tree_Node_Access;
            List  : in Compilation_Unit_List_Access)
            return Compilation_Unit_List_Access;

         procedure Check_Missing
           (Node      : in Tree_Node_Access;
            Prev_Node : in Tree_Node_Access);

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
            if not Is_Inconsistent (Node.Unit) then
               Node.Consistent := False;

               if Is_Source_Changed (Node.Unit) then
                  Node.Inconsistent := Append
                    (Node.Inconsistent, (Nil_Compilation_Unit, Node.Unit));
               else
                  if Order = Ascending then
                     Prev_Node := Node.Prev;
                  else
                     Prev_Node := Node.Next (Node.Next.all'First);
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
            end if;

            if not Is_Nil (Node.Unit_Body) then
               if not Node.Consistent then
                  Node.Inconsistent := Append
                    (Node.Inconsistent, (Node.Unit, Node.Unit_Body));
               else
                  if not Is_Inconsistent (Node.Unit_Body) then
                     if Is_Source_Changed (Node.Unit_Body) then
                        Node.Inconsistent := Append
                          (Node.Inconsistent,
                           (Nil_Compilation_Unit, Node.Unit_Body));
                     else
                        Node.Inconsistent := Append
                          (Node.Inconsistent,
                           (Node.Unit_Body, Node.Unit_Body));
                     end if;
                  end if;
               end if;
            end if;

            if not Node.Consistent then
               if Order = Ascending then
                  if Node.Next /= null then
                     for Index in Node.Next.all'Range loop
                        Node.Inconsistent := Set_Inconsistent
                          (Node.Next.all (Index), Node, Node.Inconsistent);
                     end loop;
                  end if;
               else
                  if Node.Prev /= null then
                     Node.Inconsistent := Set_Inconsistent
                       (Node.Prev, Node, Node.Inconsistent);
                  end if;

                  if Node.Prevs /= null then
                     for Index in Node.Prevs.all'Range loop
                        Node.Inconsistent := Set_Inconsistent
                          (Node.Prevs.all (Index), Node, Node.Inconsistent);
                     end loop;
                  end if;
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
               Node.Inconsistent (Node.Inconsistent'First) := Prev.Unit;
               Result := Append (Result, Node.Inconsistent.all);
               return Result;
            end if;

            if not Is_Nil (Node.Unit) then
               Kinds        := Unit_Kind (Node.Unit);
               Parent_Kinds := Unit_Kind (Prev.Unit);

               if Kinds in A_Procedure .. A_Generic_Package_Renaming then
                  if Parent_Kinds in
                    A_Procedure .. A_Generic_Package_Renaming
                  then
                     Node.Consistent := False;
                     Result := Append (Result, (Prev.Unit, Node.Unit));
                  end if;
               else
                  if Parent_Kinds in
                    A_Procedure_Body .. A_Protected_Body_Subunit
                  then
                     Node.Consistent := False;
                     Result := Append (Result, (Prev.Unit, Node.Unit));
                  end if;
               end if;

               if not Is_Nil (Node.Unit_Body) then
                  if not Node.Consistent then
                     Result := Append (Result, (Node.Unit, Node.Unit_Body));
                  else
                     if not Is_Inconsistent (Node.Unit_Body) then
                        if Is_Source_Changed (Node.Unit_Body) then
                           Result := Append
                             (Result, (Nil_Compilation_Unit, Node.Unit_Body));
                        else
                           Result := Append
                             (Result, (Node.Unit_Body, Node.Unit_Body));
                        end if;
                     end if;
                  end if;
               end if;
            end if;

            if Order = Ascending then
               if Node.Next /= null then
                  for Index in Node.Next.all'Range loop
                     Node.Inconsistent := Set_Inconsistent
                       (Node.Next.all (Index), This, Node.Inconsistent);
                  end loop;
               end if;
            else
               if Node.Prev /= null then
                  Node.Inconsistent := Set_Inconsistent
                    (Node.Prev, This, Node.Inconsistent);
               end if;

               if Node.Prevs /= null then
                  for Index in Node.Prevs.all'Range loop
                     Node.Inconsistent := Set_Inconsistent
                       (Node.Prevs.all (Index), This, Node.Inconsistent);
                  end loop;
               end if;
            end if;

            return Result;
         end Set_Inconsistent;

         -- Check_Missing --
         procedure Check_Missing
           (Node      : in Tree_Node_Access;
            Prev_Node : in Tree_Node_Access)
         is
         begin
            if Node.Missing /= null then
               return;
            end if;

            if Prev_Node /= null
              and then not Is_Nil (Prev_Node.Unit)
            then
               Perent_Unit  := Prev_Node.Unit;
               Parent_Kinds := Unit_Kind (Perent_Unit);

               if Parent_Kinds = A_Nonexistent_Declaration
                 or else Parent_Kinds = A_Nonexistent_Body  then
                  Node.Missing := Append
                    (Node.Missing, (Node.Unit, Perent_Unit));
               end if;

               if not Is_Nil (Node.Unit_Body) then
                  if Kinds = A_Nonexistent_Declaration then
                     Node.Missing := Append
                       (Node.Missing, (Node.Unit_Body, Node.Unit));
                  else
                     if not Is_Nil (Prev_Node.Unit_Body) then
                        Perent_Unit := Prev_Node.Unit_Body;
                     end if;

                     Parent_Kinds := Unit_Kind (Perent_Unit);

                     if Parent_Kinds = A_Nonexistent_Declaration
                       or else Parent_Kinds = A_Nonexistent_Body
                     then
                        Node.Missing := Append
                          (Node.Missing, (Node.Unit_Body, Perent_Unit));
                     end if;
                  end if;
               end if;
            end if;
         end Check_Missing;

         procedure Asc
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

               Check_Missing (Node, Node.Prev);
            end if;

            if Node.Next /= null then
               for Index in Node.Next.all'Range loop
                  Asc (Node.Next.all (Index));
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

               if Node.Next /= null then
                  for Index in Node.Next.all'Range loop
                     Check_Missing (Node, Node.Next (Index));
                  end loop;
               end if;
            end if;

            if Node.Prev /= null then
               Desc (Node.Prev);
            end if;

            if Node.Prevs /= null then
               for Index in Node.Prevs.all'Range loop
                  Desc (Node.Prevs.all (Index));
               end loop;
            end if;
         end Desc;

      begin
         if Order = Ascending then
            Asc (This);
         else
            Desc (Find (This.all, Library_Unit_Declaration
              ("Standard", The_Context)));
         end if;
      end Check;

      ---------------------------
      -- Generate_Relationship --
      ---------------------------

      function Generate_Relationship
        (This       : in Tree_Node_Access;
         Limit_List : in Utils.Compilation_Unit_List_Access;
         List_Last  : in ASIS_Integer;
         Order      : in Orders)
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

         procedure Process_Asc
           (Node : in Tree_Node_Access);

         procedure Process_Dsc
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

               Inconsistent_List := Append
                 (Inconsistent_List, Node.Inconsistent.all);
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

               for Index in Node.Circular.all'Range loop
                  Circular_List := Append
                    (Circular_List, Node.Circular.all (Index));

                  if Index < Node.Circular.all'Last then
                     Circular_List := Append
                       (Circular_List, Node.Circular.all (Index + 1));
                  else
                     Circular_List := Append
                       (Circular_List, Node.Circular.all (1));
                  end if;
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

         -- Process_Asc --
         procedure Process_Asc
           (Node : in Tree_Node_Access)
         is
            Internal_Node : Tree_Node_Access := Node;
         begin
            while Internal_Node /= null loop
               if not Is_Nil (Internal_Node.Unit) then
                  if Internal_Node.Added then
                     return;
                  end if;

                  Internal_Node.Added := True;

                  if Internal_Node.Consistent then
                     Consistent_List := Append
                       (Consistent_List, Internal_Node.Unit);
                  end if;

                  Genegate_Inconsistent (Internal_Node);
                  Genegate_Missing      (Internal_Node);
                  Genegate_Circular     (Internal_Node);
               end if;

               Internal_Node := Internal_Node.Prev;
            end loop;
         end Process_Asc;

         -- Process_Dsc --
         procedure Process_Dsc
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

               if not Is_Nil (Node.Unit_Body)
                 and then Is_Inconsistent (Node.Unit_Body)
               then
                  Add_To_Consistent (Node.Unit_Body);
               end if;
            end if;

            Genegate_Inconsistent (Node);
            Genegate_Missing      (Node);
            Genegate_Circular     (Node);

            if Node.Next /= null then
               for Index in Node.Next.all'Range loop
                  Process_Dsc (Node.Next.all (Index));
               end loop;
            end if;
         end Process_Dsc;

      begin
         if Order = Ascending then
            if Is_Nil (This.Unit)  then
               return Nil_Relationship;
            end if;

            declare
               Lasts : Tree_Node_Array_Access := This.Last_Nodes;
            begin
               for Index in Lasts.all'Range loop
                  Process_Asc (Lasts.all (Index));
               end loop;
            end;
         else
            if not Is_Nil (This.Unit) then
               Process_Dsc (This);
            else
               if This.Next = null then
                  return Nil_Relationship;
               end if;

               for Index in This.Next.all'Range loop
                  Process_Dsc (This.Next.all (Index));
               end loop;
            end if;
         end if;

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

      ----------
      -- Spec --
      ----------

      function Spec
        (This : in Tree_Node_Access)
         return Compilation_Unit
      is
      begin
         return This.Unit;
      end Spec;

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
        (This : in out Tree_Node)
      is
      begin
         Clear (This);
      end Finalize;

      ----------
      -- Find --
      ----------

      function Find
        (This : in Tree_Node;
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

      ----------------------
      -- Add_Node_Ordered --
      ----------------------

      function Add_Node_Ordered
        (List : in Unit_Node_Array_Access;
         Node : in Tree_Node_Access)
         return Unit_Node_Array_Access
      is
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
         Process (Node.Unit);

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
