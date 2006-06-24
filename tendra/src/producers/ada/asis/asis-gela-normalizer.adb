with Asis.Gela.Lists;
with Asis.Gela.Errors;
with Asis.Gela.Iterator;
with Asis.Gela.Elements;
with Asis.Gela.Unit_Utils;
with Asis.Gela.Element_Utils;
with Asis.Gela.Elements.Decl;
with Asis.Gela.Elements.Defs;
with Asis.Gela.Elements.Stmt;
with Asis.Gela.Elements.Clause;
with Asis.Gela.Elements.Helpers;
with Asis.Gela.Normalizer.Utils;
with Asis.Gela.Elements.Defs.Sub;
with Asis.Gela.Elements.Defs.Rng;
with Asis.Gela.Elements.Clause.Rep;
with Asis.Gela.Elements.Defs.Types;
with Asis.Gela.Elements.Defs.Formal;

package body Asis.Gela.Normalizer is

   procedure Pre_Operation
     (Element : in out Asis.Element;
      Control : in out Traverse_Control;
      State   : in out State_Information);

   procedure Post_Operation
     (Element : in out Asis.Element;
      Control : in out Traverse_Control;
      State   : in out State_Information);

   procedure Normalize_Expression
     (Element : in out Asis.Element;
      Control : in out Traverse_Control;
      State   : in out State_Information);

   package Iterator is new Asis.Gela.Iterator (State_Information);

   procedure Normalize_Declaration (Element : in out Asis.Declaration);
   procedure Normalize_Definition (Element : Asis.Definition);
   procedure Normalize_Clause (Element : in out Asis.Clause);
   procedure Normalize_Statement (Element : in out Asis.Statement);

   ----------------------
   -- Normalize_Clause --
   ----------------------

   procedure Normalize_Clause (Element : in out Asis.Clause) is

      ---------------------
      -- Set_Clause_Name --
      ---------------------

      procedure Set_Clause_Name
        (Element   : Asis.Clause;
         Component : Boolean := False)
      is
         use Asis.Gela.Elements.Clause;
         use Lists.Primary_Identifier_Lists;
         Name : constant Asis.Element :=
           Representation_Clause_Name (Element.all);
      begin
         if Is_List (Name.all) then --  in List_Node then
            if Component then
               Set_Representation_Clause_Name
                 (Component_Clause_Node (Element.all),
                  Element_Utils.To_Unit_Name (Name));
            else
               Set_Representation_Clause_Name
                 (Representation_Clause_Node (Element.all),
                  Element_Utils.To_Unit_Name (Name));
            end if;
         end if;
      end Set_Clause_Name;

      ---------------
      -- RR_Clause --
      ---------------

      procedure RR_Clause (Element : Asis.Clause) is
         use Lists.Primary_Clause_Lists;
         use Asis.Gela.Elements.Clause.Rep;

         Comp    : Asis.Element;
         Item    : constant Record_Representation_Clause_Ptr :=
           Record_Representation_Clause_Ptr (Element);
         Clauses : constant List := List (Component_Clauses_List (Item.all));
      begin

         Looking_For_Mod_Clause :
            for I in 1 .. Length (Clauses.all) loop
               Comp := Get_Item (Clauses, I);
               if Representation_Clause_Kind (Comp.all) =
                 A_Record_Representation_Clause
               then
                  if I = 1 then
                     Set_Mod_Clause_Expression (Item.all, Comp);
                  else
                     Errors.Report
                       (Item => Comp,
                        What => Errors.Error_Syntax_Misplaced_Mod_Clause);
                  end if;
               end if;
            end loop Looking_For_Mod_Clause;

         Comp := Mod_Clause_Expression (Element.all);

         if Assigned (Comp) then
            Remove (Clauses.all, Comp);
            Set_Mod_Clause_Expression
              (Item.all, Mod_Clause_Expression (Comp.all));
         end if;
      end RR_Clause;

      ---------------
      -- At_Clause --
      ---------------

      procedure Check_Clause_Name (Element : in out Asis.Clause) is
         Name : constant Asis.Element :=
           Representation_Clause_Name (Element.all);
         Kind : constant Asis.Expression_Kinds :=
           Expression_Kind (Name.all);
         Rep  : constant Asis.Representation_Clause_Kinds :=
           Representation_Clause_Kind (Element.all);
      begin
         if Rep = An_Attribute_Definition_Clause then
            if Kind = An_Attribute_Reference then
               return;
            end if;

            Utils.Normalize_Enumeration_Rep_Clause (Element);
         end if;

         if Kind /= An_Identifier and Kind /= An_Operator_Symbol
         then
            Errors.Report
              (Item => Name,
               What => Errors.Error_Syntax_Expected_Direct_Name);

         end if;
      end Check_Clause_Name;

   begin  -- Normalize_Clause

      case Clause_Kind (Element.all) is
         when A_Representation_Clause =>

            Set_Clause_Name (Element);

            case Representation_Clause_Kind (Element.all) is
               when Not_A_Representation_Clause =>
                  null;
               when A_Record_Representation_Clause =>
                  RR_Clause (Element);
               when An_Attribute_Definition_Clause |
                 An_At_Clause =>

                  Check_Clause_Name (Element);

               when An_Enumeration_Representation_Clause =>
                  --  goes to An_Attribute_Definition_Clause
                  null;

            end case;

         when A_Component_Clause =>
            Set_Clause_Name (Element, True);
         when others =>
            null;
      end case;
   end Normalize_Clause;

   ---------------------------
   -- Normalize_Declaration --
   ---------------------------

   procedure Normalize_Declaration (Element : in out Asis.Declaration) is
      use Asis.Gela.Elements.Decl;
   begin
      Utils.Set_Names (Element);

      case Declaration_Kind (Element.all) is
         when An_Entry_Body_Declaration =>
            declare
               procedure Split_Specification is
                  new Utils.Split_Function_Specification
                    (Entry_Body_Declaration_Node,
                     Set_Result_Profile => Set_Entry_Index_Specification);

               procedure Normalize_Handled_Statements is
                  new Utils.Normalize_Handled_Statements
                    (Entry_Body_Declaration_Node,
                     Set_Statements         => Set_Body_Statements,
                     Set_Exception_Handlers => Set_Body_Exception_Handlers);

               procedure Check_Back_Identifier is
                  new Utils.Check_Back_Identifier
                    (Entry_Body_Declaration_Node);
            begin
               Split_Specification (Element);
               Normalize_Handled_Statements (Element);
               Check_Back_Identifier (Element);
            end;

         when A_Formal_Function_Declaration =>
            declare
               procedure Split_Specification is
                  new Utils.Split_Function_Specification
                    (Formal_Function_Declaration_Node);
            begin
               Split_Specification (Element);
               Utils.Set_Default_Kind (Element);
            end;

         when A_Formal_Object_Declaration | A_Parameter_Specification =>
            Utils.Set_Mode_Kind (Element);

         when A_Formal_Package_Declaration_With_Box =>
            declare
               procedure Set_Generic_Unit_Names is new
                 Utils.Set_Generic_Unit_Names
                   (Formal_Package_Declaration_With_Box_Node);
            begin
               Set_Generic_Unit_Names (Element);
            end;

         when A_Formal_Procedure_Declaration =>
            declare
               procedure Split_Specification is
                  new Utils.Split_Procedure_Specification
                    (Formal_Procedure_Declaration_Node);
            begin
               Split_Specification (Element);
               Utils.Set_Default_Kind (Element);
            end;

         when A_Function_Body_Declaration =>
            declare
               procedure Split_Specification is
                  new Utils.Split_Function_Specification
                    (Function_Body_Declaration_Node);

               procedure Normalize_Handled_Statements is
                  new Utils.Normalize_Handled_Statements
                    (Function_Body_Declaration_Node,
                     Set_Statements         => Set_Body_Statements,
                     Set_Exception_Handlers => Set_Body_Exception_Handlers);

               procedure Check_Back_Identifier is
                  new Utils.Check_Back_Identifier
                    (Function_Body_Declaration_Node);
            begin
               Split_Specification (Element);
               Normalize_Handled_Statements (Element);
               Check_Back_Identifier (Element);
            end;

         when A_Function_Body_Stub =>
            declare
               procedure Split_Specification is
                  new Utils.Split_Function_Specification
                    (Function_Body_Stub_Node);
            begin
               Split_Specification (Element);
            end;

         when A_Function_Declaration =>
            declare
               procedure Split_Specification is
                  new Utils.Split_Function_Specification
                    (Function_Declaration_Node);
            begin
               Split_Specification (Element);
            end;

         when A_Function_Instantiation =>
            declare
               Parameter_Profile : Asis.Element;
               Result_Profile    : Asis.Expression;

               procedure Set_Parameter_Profile
                 (Node    : in out Function_Instantiation_Node;
                  Element : in     Asis.Element)
               is
               begin
                  Parameter_Profile := Element;
               end Set_Parameter_Profile;

               procedure Set_Result_Profile
                 (Node    : in out Function_Instantiation_Node;
                  Element : in     Asis.Element)
               is
               begin
                  Result_Profile := Element;
               end Set_Result_Profile;

               procedure Split_Specification is
                  new Utils.Split_Function_Specification
                 (Function_Instantiation_Node);

               procedure Set_Generic_Unit_Names is new
                 Utils.Set_Generic_Unit_Names
                   (Function_Instantiation_Node);
            begin
               Split_Specification (Element);
               Utils.Check_Empty_Profile (Parameter_Profile);
               Utils.Check_Empty_Result (Result_Profile);
               Set_Generic_Unit_Names (Element);
            end;

         when A_Function_Renaming_Declaration =>
            declare
               procedure Split_Specification is
                  new Utils.Split_Function_Specification
                    (Function_Renaming_Declaration_Node);
            begin
               Split_Specification (Element);
            end;

         when A_Generic_Function_Declaration =>
            declare
               procedure Split_Specification is
                  new Utils.Split_Function_Specification
                    (Generic_Function_Declaration_Node);
            begin
               Split_Specification (Element);
            end;

         when A_Generic_Function_Renaming_Declaration =>
            declare
               Parameter_Profile : Asis.Element;
               Result_Profile    : Asis.Expression;

               procedure Set_Parameter_Profile
                 (Node    : in out Generic_Function_Renaming_Declaration_Node;
                  Element : in     Asis.Element)
               is
               begin
                  Parameter_Profile := Element;
               end Set_Parameter_Profile;

               procedure Set_Result_Profile
                 (Node    : in out Generic_Function_Renaming_Declaration_Node;
                  Element : in     Asis.Element)
               is
               begin
                  Result_Profile := Element;
               end Set_Result_Profile;

               procedure Split_Specification is
                  new Utils.Split_Function_Specification
                    (Generic_Function_Renaming_Declaration_Node);
            begin
               Split_Specification (Element);
               Utils.Check_Empty_Profile (Parameter_Profile);
               Utils.Check_Empty_Result (Result_Profile);
               Utils.Check_Empty_Generic (Element);
            end;

         when A_Generic_Package_Declaration =>
            declare
               procedure Split_Specification is
                  new Utils.Split_Package_Specification
                    (Generic_Package_Declaration_Node);
            begin
               Split_Specification (Element);
            end;

         when A_Generic_Package_Renaming_Declaration =>
            Utils.Check_Empty_Generic (Element);
--            Utils.Set_Defining_Unit_Name (Element);

         when A_Generic_Procedure_Declaration =>
            declare
               procedure Split_Specification is
                  new Utils.Split_Procedure_Specification
                    (Generic_Procedure_Declaration_Node);
            begin
               Split_Specification (Element);
            end;

         when A_Generic_Procedure_Renaming_Declaration =>
            declare
               Parameter_Profile : Asis.Element;

               procedure Set_Parameter_Profile
                 (Node    : in out Generic_Procedure_Renaming_Declaration_Node;
                  Element : in     Asis.Element)
               is
               begin
                  Parameter_Profile := Element;
               end Set_Parameter_Profile;

               procedure Split_Specification is
                  new Utils.Split_Procedure_Specification
                    (Generic_Procedure_Renaming_Declaration_Node);
            begin
               Split_Specification (Element);
               Utils.Check_Empty_Profile (Parameter_Profile);
               Utils.Check_Empty_Generic (Element);
            end;

         when A_Package_Body_Declaration =>
            declare
               procedure Normalize_Handled_Statements is
                  new Utils.Normalize_Handled_Statements
                    (Package_Body_Declaration_Node,
                     Set_Statements         => Set_Body_Statements,
                     Set_Exception_Handlers => Set_Body_Exception_Handlers);

               procedure Check_Back_Identifier is
                  new Utils.Check_Back_Identifier
                    (Package_Body_Declaration_Node);
            begin
--               Utils.Set_Defining_Unit_Name (Element);
               Normalize_Handled_Statements (Element);
               Check_Back_Identifier (Element);
            end;

         when A_Package_Body_Stub | A_Task_Body_Stub | A_Protected_Body_Stub =>
            null;
--            Utils.Set_Defining_Unit_Name (Element);

         when A_Package_Declaration =>
            declare
               procedure Split_Specification is
                  new Utils.Split_Package_Specification
                    (Package_Declaration_Node, Package_Specification);
            begin
               Split_Specification (Element);
            end;

         when A_Package_Instantiation |
           A_Formal_Package_Declaration =>

            declare
               procedure Set_Generic_Unit_Names is new
                 Utils.Set_Generic_Unit_Names
                   (Package_Instantiation_Node);
            begin
               Set_Generic_Unit_Names (Element);
            end;

         when A_Package_Renaming_Declaration =>
            null;
--            Utils.Set_Defining_Unit_Name (Element);

         when A_Private_Type_Declaration | A_Private_Extension_Declaration =>
            declare
               procedure Set_Trait_Kind is new
                 Utils.Set_Trait_Kind (Private_Type_Declaration_Node);
            begin
               Set_Trait_Kind (Element);
            end;

         when A_Procedure_Body_Declaration =>
            declare
               procedure Split_Specification is
                  new Utils.Split_Procedure_Specification
                    (Procedure_Body_Declaration_Node);

               procedure Normalize_Handled_Statements is
                  new Utils.Normalize_Handled_Statements
                    (Procedure_Body_Declaration_Node,
                     Set_Statements         => Set_Body_Statements,
                     Set_Exception_Handlers => Set_Body_Exception_Handlers);

               procedure Check_Back_Identifier is
                  new Utils.Check_Back_Identifier
                    (Procedure_Body_Declaration_Node);
            begin
               Split_Specification (Element);
               Normalize_Handled_Statements (Element);
               Check_Back_Identifier (Element);
            end;

         when A_Procedure_Body_Stub =>
            declare
               procedure Split_Specification is
                  new Utils.Split_Procedure_Specification
                    (Procedure_Body_Stub_Node);
            begin
               Split_Specification (Element);
            end;

         when A_Procedure_Declaration =>
            declare
               procedure Split_Specification is
                  new Utils.Split_Procedure_Specification
                    (Procedure_Declaration_Node);
            begin
               Split_Specification (Element);
            end;

         when A_Procedure_Instantiation =>
            declare
               Parameter_Profile : Asis.Element;

               procedure Set_Parameter_Profile
                 (Node    : in out Procedure_Instantiation_Node;
                  Element : in     Asis.Element)
               is
               begin
                  Parameter_Profile := Element;
               end Set_Parameter_Profile;

               procedure Split_Specification is
                  new Utils.Split_Procedure_Specification
                    (Procedure_Instantiation_Node);

               procedure Set_Generic_Unit_Names is new
                 Utils.Set_Generic_Unit_Names
                   (Procedure_Instantiation_Node);
            begin
               Split_Specification (Element);
               Utils.Check_Empty_Profile (Parameter_Profile);
               Set_Generic_Unit_Names (Element);
            end;

         when A_Procedure_Renaming_Declaration =>
            declare
               procedure Split_Specification is
                  new Utils.Split_Procedure_Specification
                    (Procedure_Renaming_Declaration_Node);
            begin
               Split_Specification (Element);
            end;

         when A_Protected_Body_Declaration =>
            declare
               procedure Check_Back_Identifier is
                  new Utils.Check_Back_Identifier
                    (Protected_Body_Declaration_Node, Get_Identifier);
            begin
               Check_Back_Identifier (Element);
            end;

         when A_Single_Task_Declaration | A_Single_Protected_Declaration =>
            declare
               function Task_Compound_Name
                 (Element : Single_Task_Declaration_Node)
                 return Asis.Element
               is
                  use Asis.Gela.Elements.Defs;
                  Def : constant Asis.Element :=
                    Object_Declaration_View (Element);
                  Tsk : constant Task_Definition_Ptr :=
                    Task_Definition_Ptr (Def);
               begin
                  if Tsk = null then
                     return Asis.Nil_Element;
                  else
                     return Get_Identifier (Tsk.all);
                  end if;
               end Task_Compound_Name;

               procedure Check_Back_Identifier is
                  new Utils.Check_Back_Identifier
                 (Single_Task_Declaration_Node, Task_Compound_Name);
            begin
               Check_Back_Identifier (Element);
            end;

         when A_Task_Body_Declaration =>
            declare
               procedure Normalize_Handled_Statements is
                  new Utils.Normalize_Handled_Statements
                    (Task_Body_Declaration_Node,
                     Set_Statements         => Set_Body_Statements,
                     Set_Exception_Handlers => Set_Body_Exception_Handlers);

               procedure Check_Back_Identifier is
                  new Utils.Check_Back_Identifier
                    (Task_Body_Declaration_Node);
            begin
               Normalize_Handled_Statements (Element);
               Check_Back_Identifier (Element);
            end;

         when A_Task_Type_Declaration | A_Protected_Type_Declaration =>
            declare
               function Task_Compound_Name
                 (Element : Task_Type_Declaration_Node)
                 return Asis.Element
               is
                  use Asis.Gela.Elements.Defs;
                  Def : constant Asis.Element :=
                    Type_Declaration_View (Element);
                  Tsk : Task_Definition_Node renames
                    Task_Definition_Node (Def.all);
               begin
                  return Get_Identifier (Tsk);
               end Task_Compound_Name;

               procedure Check_Back_Identifier is
                  new Utils.Check_Back_Identifier
                 (Task_Type_Declaration_Node, Task_Compound_Name);
            begin
               Check_Back_Identifier (Element);
            end;

         when A_Constant_Declaration =>
            if not Assigned (Initialization_Expression (Element.all)) then
               Utils.To_Deferred_Constant (Element);
            end if;

         when others =>
            null;
      end case;
   end Normalize_Declaration;

   --------------------------
   -- Normalize_Definition --
   --------------------------

   procedure Normalize_Definition (Element : Asis.Definition) is
      use Asis.Gela.Elements.Defs;
   begin
      case Definition_Kind (Element.all) is
         when A_Private_Type_Definition | A_Private_Extension_Definition =>
            declare
               procedure Set_Trait_Kind is new
                 Utils.Set_Trait_Kind (Private_Type_Definition_Node);
            begin
               Set_Trait_Kind (Element);
            end;

         when A_Record_Definition =>
            declare
               procedure Normalize_Component_List is new
                 Utils.Normalize_Component_List (Record_Definition_Node);
            begin
               Normalize_Component_List (Element);
            end;

         when A_Tagged_Private_Type_Definition =>
            declare
               procedure Set_Trait_Kind is new
                 Utils.Set_Trait_Kind (Tagged_Private_Type_Definition_Node);
            begin
               Set_Trait_Kind (Element);
            end;

         when A_Task_Definition | A_Protected_Definition =>
            declare
               procedure Set_Has_Private is new
                 Utils.Set_Has_Private (Task_Definition_Node);
            begin
               Set_Has_Private (Element);
            end;

         when A_Variant =>
            declare
               procedure Normalize_Component_List is new
                 Utils.Normalize_Component_List (Variant_Node);
            begin
               Normalize_Component_List (Element);
            end;

         when A_Type_Definition =>
            case Type_Definition_Kind (Element.all) is
               when An_Access_Type_Definition =>
                  Utils.Normalize_Access_Type (Element);

               when A_Tagged_Record_Type_Definition =>
                  declare
                     use Asis.Gela.Elements.Defs.Types;

                     procedure Set_Trait_Kind is new
                       Utils.Set_Trait_Kind (Tagged_Record_Type_Node);
                  begin
                     Set_Trait_Kind (Element);
                  end;

               when others =>
                  null;
            end case;  --  Type_Definition_Kind

         when A_Formal_Type_Definition =>
            case Formal_Type_Definition_Kind (Element.all) is
               when A_Formal_Access_Type_Definition =>
                  Utils.Normalize_Formal_Access_Type (Element);

               when A_Formal_Unconstrained_Array_Definition =>
                  declare
                     use Asis.Gela.Elements.Defs.Types;
                     use Asis.Gela.Elements.Defs.Formal;

                     procedure Set_Formal_Array is new
                       Utils.Set_Formal_Array
                         (Formal_Unconstrained_Array_Node,
                          Unconstrained_Array_Node);
                  begin
                     Set_Formal_Array (Element);
                  end;

               when A_Formal_Constrained_Array_Definition =>
                  declare
                     use Asis.Gela.Elements.Defs.Types;
                     use Asis.Gela.Elements.Defs.Formal;

                     procedure Set_Formal_Array is new
                       Utils.Set_Formal_Array
                         (Formal_Constrained_Array_Node,
                          Constrained_Array_Node,
                          Set_Discrete_Subtype_Definitions,
                          Discrete_Subtype_Definitions_List);
                  begin
                     Set_Formal_Array (Element);
                  end;

               when A_Formal_Derived_Type_Definition =>
                  declare
                     use Asis.Gela.Elements.Defs.Formal;

                     procedure Set_Trait_Kind is new
                       Utils.Set_Trait_Kind (Formal_Derived_Type_Node);
                  begin
                     Set_Trait_Kind (Element);
                  end;

               when A_Formal_Private_Type_Definition =>
                  declare
                     use Asis.Gela.Elements.Defs.Formal;

                     procedure Set_Trait_Kind is new
                       Utils.Set_Trait_Kind (Formal_Private_Type_Node);
                  begin
                     Set_Trait_Kind (Element);
                  end;

               when A_Formal_Tagged_Private_Type_Definition =>
                  declare
                     use Asis.Gela.Elements.Defs.Formal;

                     procedure Set_Trait_Kind is new
                       Utils.Set_Trait_Kind (Formal_Tagged_Private_Type_Node);
                  begin
                     Set_Trait_Kind (Element);
                  end;

               when others =>
                  null;
            end case;  --  Formal_Type_Definition_Kind

         when A_Discrete_Range =>
            case Discrete_Range_Kind (Element.all) is
               when A_Discrete_Range_Attribute_Reference =>
                  declare
                     use Asis.Gela.Elements.Defs.Rng;
                     procedure Drop_Range_Attr_Reference is new
                       Utils.Drop_Range_Attr_Reference
                         (Discrete_Range_Attribute_Reference_Node);
                  begin
                     Drop_Range_Attr_Reference (Element);
                  end;

               when A_Discrete_Simple_Expression_Range =>
                  Utils.Set_Start_Position
                    (Element, Lower_Bound (Element.all));

               when others =>
                  null;
            end case;

         when A_Discrete_Subtype_Definition =>
            case Discrete_Range_Kind (Element.all) is
               when A_Discrete_Range_Attribute_Reference =>
                  declare
                     use Asis.Gela.Elements.Defs.Sub;
                     procedure Drop_Range_Attr_Reference is new
                       Utils.Drop_Range_Attr_Reference
                         (S_Discrete_Range_Attribute_Reference_Node);
                  begin
                     Drop_Range_Attr_Reference (Element);
                  end;

               when A_Discrete_Subtype_Indication =>
                  declare
                     use Asis.Gela.Elements.Defs.Sub;
                     procedure Drop_Range_Subtype_Indication is new
                       Utils.Drop_Range_Subtype_Indication
                         (S_Discrete_Subtype_Indication_Node);
                  begin
                     Drop_Range_Subtype_Indication (Element);
                  end;

               when others =>
                  null;
            end case;

         when A_Constraint =>
            case Constraint_Kind (Element.all) is
               when A_Range_Attribute_Reference =>
                  Utils.Set_Start_Position
                    (Element, Range_Attribute (Element.all));

               when A_Simple_Expression_Range =>
                  Utils.Set_Start_Position
                    (Element, Lower_Bound (Element.all));

               when others =>
                  null;
            end case;

         when others =>
            null;
      end case;
   end Normalize_Definition;

   --------------------------
   -- Normalize_Expression --
   --------------------------

   procedure Normalize_Expression
     (Element : in out Asis.Element;
      Control : in out Traverse_Control;
      State   : in out State_Information)
   is
   begin
      case Expression_Kind (Element.all) is
         when An_Attribute_Reference =>
            Utils.Normalize_Attribute_Reference (Element);

         when A_Function_Call =>
            Utils.Normalize_Function_Call (Element, Control, State);

         when A_Qualified_Expression =>
            Utils.Normalize_Qualified_Expression (Element);

         when A_Record_Aggregate =>
            Utils.Normalize_Record_Aggregate (Element, Control, State);

         when others =>
            null;
      end case;
   end Normalize_Expression;

   -------------------------
   -- Normalize_Statement --
   -------------------------

   procedure Normalize_Statement (Element : in out Asis.Statement) is
      use Asis.Gela.Elements.Stmt;

      function Stmt_Names (Element : Asis.Statement) return Asis.Element_List
      is
      begin
         return (1 => Statement_Identifier (Element.all));
      end Stmt_Names;

      function Accept_Names (Element : Asis.Statement) return Asis.Element_List
      is
      begin
         return (1 => Accept_Entry_Direct_Name (Element.all));
      end Accept_Names;

      function Accept_Back_Identifier (Element : Accept_Statement_Node)
                                      return Asis.Element
      is
         use Asis.Gela.Elements.Helpers;
         Node : constant Handled_Statements_Ptr :=
           Handled_Statements_Ptr (Handled_Statements (Element));
      begin
         if Node = null then
            return Nil_Element;
         else
            return Get_Identifier (Node.all);
         end if;
      end Accept_Back_Identifier;

      Node   : Asis.Gela.Elements.Statement_Node
        renames Asis.Gela.Elements.Statement_Node (Element.all);
      Labels : constant Asis.Element :=
        Asis.Gela.Elements.Label_Names_List (Node);
   begin
      if Assigned (Labels) then
         Utils.Set_Start_Position (Element, Labels);
      end if;

      case Statement_Kind (Element.all) is
         when An_Accept_Statement =>
            declare
               procedure Normalize_Handled_Statements is
                  new Utils.Normalize_Handled_Statements
                 (Accept_Statement_Node,
                  Handled_Statements,
                  Set_Accept_Body_Statements,
                  Set_Accept_Body_Exception_Handlers);

               procedure Check_Back_Identifier is
                  new Utils.Check_Back_Identifier
                 (Accept_Statement_Node,
                  Accept_Back_Identifier,
                  Set_Is_Name_Repeated,
                  Accept_Names);
            begin
               Normalize_Handled_Statements (Element);
               Check_Back_Identifier (Element);
            end;

         when A_Block_Statement =>
            declare
               procedure Normalize_Handled_Statements is
                  new Utils.Normalize_Handled_Statements
                 (Block_Statement_Node,
                  Handled_Statements,
                  Set_Block_Statements,
                  Set_Block_Exception_Handlers);

               procedure Check_Back_Identifier is
                  new Utils.Check_Back_Identifier
                 (Block_Statement_Node,
                  Back_Identifier,
                  Set_Is_Name_Repeated,
                  Stmt_Names);

               Node : Block_Statement_Node renames
                 Block_Statement_Node (Element.all);

               Items : constant Asis.Element :=
                 Block_Declarative_Items_List (Node);
            begin
               Normalize_Handled_Statements (Element);
               Check_Back_Identifier (Element);
               Set_Is_Declare_Block (Node, Assigned (Items));
            end;

         when A_Loop_Statement |
           A_While_Loop_Statement |
           A_For_Loop_Statement =>
            declare
               procedure Check_Back_Identifier is
                  new Utils.Check_Back_Identifier
                 (Loop_Statement_Node,
                  Back_Identifier,
                  Set_Is_Name_Repeated,
                  Stmt_Names);
            begin
               Check_Back_Identifier (Element);
            end;

         when A_Procedure_Call_Statement =>
            Utils.Normalize_Procedure_Call (Element);

--         goes into overloads.resolve
--         when A_Selective_Accept_Statement =>
--            Utils.Normalize_Selective_Accept (Element);

         when others =>
            null;
      end case;
   end Normalize_Statement;

   --------------------
   -- Post_Operation --
   --------------------

   procedure Post_Operation
     (Element : in out Asis.Element;
      Control : in out Traverse_Control;
      State   : in out State_Information)
   is
   begin
      State.Parent := Enclosing_Element (Element.all);
      case Element_Kind (Element.all) is
         when A_Definition =>
            case Definition_Kind (Element.all) is
               when A_Type_Definition =>
                  case Type_Definition_Kind (Element.all) is
                     when An_Enumeration_Type_Definition =>
                        Utils.Set_Enum_Positions
                          (Enumeration_Literal_Declarations (Element.all));

                     when others =>
                        null;
                  end case;  --  Type_Definition_Kind
               when others =>
                  null;
            end case;
         when others =>
            null;
      end case;
   end Post_Operation;

   -------------------
   -- Pre_Operation --
   -------------------

   procedure Pre_Operation
     (Element : in out Asis.Element;
      Control : in out Traverse_Control;
      State   : in out State_Information)
   is
   begin
      if Assigned (Element)
        and then Element_Kind (Element.all) /= Not_An_Element
      then
         --  For error reporting
         Element_Utils.Set_Enclosing_Compilation_Unit (Element, State.Unit);
         Element_Utils.Set_Enclosing_Element (Element, State.Parent);
      end if;

      case Element_Kind (Element.all) is
         when A_Pragma =>
            Element_Utils.Set_Pragma_Kind (Element);
         when A_Declaration =>
            Normalize_Declaration (Element);
         when A_Definition =>
            Normalize_Definition (Element);
         when An_Expression =>
            Normalize_Expression (Element, Control, State);
         when A_Statement =>
            Normalize_Statement (Element);
         when A_Clause =>
            Normalize_Clause (Element);
         when others =>
            null;
      end case;

      if Assigned (Element)
        and then Element_Kind (Element.all) /= Not_An_Element
      then
         Element_Utils.Set_Enclosing_Compilation_Unit (Element, State.Unit);
         Element_Utils.Set_Enclosing_Element (Element, State.Parent);
         State.Parent := Element;
      end if;
   end Pre_Operation;

   ---------
   -- Run --
   ---------

   procedure Run (Unit : Asis.Compilation_Unit) is
      use Asis.Gela.Unit_Utils;
      State   : State_Information;
      Control : Traverse_Control := Continue;
      Store   : Asis.Element;
   begin
      State.Unit := Unit;
      declare
         List : constant Asis.Element_List :=
           Context_Clause_Elements (Unit.all, True);
      begin
         for I in List'Range loop
            State.Parent := Asis.Nil_Element;
            Store := List (I);
            Iterator.Walk_Element_And_Free (Store, Control, State);
            pragma Assert (Is_Equal (Store, List (I)));
         end loop;
      end;

      Store := Unit_Declaration (Unit.all);
      Iterator.Walk_Element_And_Free (Store, Control, State);
      pragma Assert (Is_Equal (Store, Unit_Declaration (Unit.all)));

      Set_Unit_Kind (Unit);
      Set_Separate_Name (Unit);
      Set_Unit_Full_Name (Unit);
      Set_Unique_Name (Unit);
      Set_Unit_Class (Unit);
      Set_Unit_Origin (Unit);
      Set_Can_Be_Main_Program (Unit);
      Set_Is_Body_Required (Unit);
      Set_Text_Name (Unit);
      Set_Text_Form (Unit);
      Set_Object_Name (Unit);
      Set_Object_Form (Unit);
      Set_Compilation_Command_Line_Options (Unit);
   end Run;

   ----------------------
   -- Normalize_Pragma --
   ----------------------

   procedure Normalize_Pragma
     (Element : Asis.Pragma_Element;
      Unit    : Asis.Compilation_Unit)
   is
      State   : State_Information;
      Control : Traverse_Control := Continue;
      Store   : Asis.Element := Element;
   begin
      State.Unit := Unit;
      Iterator.Walk_Element (Store, Control, State, False);
   end Normalize_Pragma;

end Asis.Gela.Normalizer;


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
