with XASIS.Utils;
with XASIS.Types;
with Asis.Elements;
with Asis.Statements;
with Asis.Definitions;
with Asis.Declarations;
with Asis.Expressions;
with Asis.Gela.Errors;
with Asis.Gela.Classes;
with Asis.Gela.Replace;
with Asis.Gela.Instances;
with Asis.Gela.Inheritance;
with Asis.Gela.Elements.Decl;
with Asis.Gela.Elements.Defs;
with Asis.Gela.Element_Utils;

package body Asis.Gela.Implicit.Decl is

   use XASIS.Utils;
   use Asis.Elements;

   procedure Process_Subtype (Element : Asis.Element);
   procedure Process_Subtype_Indication (Element : Asis.Element);
   procedure Process_Pragma (Element : Asis.Pragma_Element);
   procedure Process_Subprogram_Decl
     (Decl  : Asis.Declaration;
      Point : in out Visibility.Point);
   procedure Set_Is_Dispatching (Decl : Asis.Declaration);
   procedure Process_Renaming (Decl : Asis.Declaration);
   procedure Process_Derived (Tipe : Asis.Type_Definition);
   procedure Process_Rep_Clause (Element : Asis.Clause);
   procedure Process_Exit (Element : Asis.Statement);
   procedure Process_Procedure_Call (Call : Asis.Expression);
   procedure Process_Accept (Stmt : Asis.Expression);

   function Is_Primitive
     (Oper : Asis.Defining_Name;
      Tipe : Classes.Type_Info) return Boolean;

   ------------------
   -- Is_Primitive --
   ------------------

   function Is_Primitive
     (Oper : Asis.Defining_Name;
      Tipe : Classes.Type_Info) return Boolean
   is
      use Asis.Elements;
      Decl   : Asis.Declaration := Classes.Get_Declaration (Tipe);
      Funct  : Asis.Declaration := Enclosing_Element (Oper);
      Parent : Asis.Element := Enclosing_Element (Funct);
   begin
      if not Is_Equal (Parent, Enclosing_Element (Decl)) then
         return False;
      end if;

      return Declaration_Kind (Parent) = A_Package_Declaration
        or else not Is_Nil (Element_Utils.Override (Oper));
   end Is_Primitive;

   -------------
   -- Process --
   -------------

   procedure Process
     (Element : in     Asis.Element;
      Point   : in out Visibility.Point)
   is
   begin
      -- if Is_Part_Of_Implicit (Element) then
      --   return;
      -- end if;

      case Element_Kind (Element) is

         when A_Definition =>
            case Definition_Kind (Element) is
               when A_Subtype_Indication =>
                  Process_Subtype_Indication (Element);
               when A_Type_Definition =>
                  case Type_Kind (Element) is
                     when A_Derived_Type_Definition
                       | A_Derived_Record_Extension_Definition =>
                        Process_Derived (Element);
                     when others =>
                        null;
                  end case;
               when others =>
                  null;
            end case;

         when A_Declaration =>
            case Declaration_Kind (Element) is
               when A_Subtype_Declaration =>
                  Process_Subtype (Element);

               when An_Ordinary_Type_Declaration
                 | A_Private_Type_Declaration
                 | A_Formal_Type_Declaration =>
                  Implicit.Make_Operations (Element, Point);
                  Inheritance.Make_Inherited_Subprograms (Element, Point);

               when A_Private_Extension_Declaration =>
                  Inheritance.Make_Inherited_Subprograms (Element, Point);

               when A_Generic_Instantiation =>
                  Instances.Make_Instance_Declaration (Element, Point);

               when A_Procedure_Declaration
                 | A_Function_Declaration
                 | A_Formal_Procedure_Declaration
                 | A_Formal_Function_Declaration
                 =>
                  Process_Subprogram_Decl (Element, Point);

               when A_Procedure_Renaming_Declaration
                 | A_Function_Renaming_Declaration
                 =>
                  Process_Subprogram_Decl (Element, Point);
                  Process_Renaming (Element);

               when An_Object_Renaming_Declaration
                 | An_Exception_Renaming_Declaration
                 | A_Package_Renaming_Declaration
                 | A_Generic_Package_Renaming_Declaration
                 | A_Generic_Procedure_Renaming_Declaration
                 | A_Generic_Function_Renaming_Declaration
                 =>
                  Process_Renaming (Element);

               when others =>
                  null;
            end case;

         when A_Pragma =>
            Process_Pragma (Element);

         when A_Clause =>
            case Clause_Kind (Element) is
               when A_Representation_Clause =>
                  Process_Rep_Clause (Element);
               when others =>
                  null;
            end case;

         when A_Statement =>
            case Statement_Kind (Element) is
               when An_Exit_Statement =>
                  Process_Exit (Element);
               when A_Procedure_Call_Statement =>
                  Process_Procedure_Call (Element);
               when An_Accept_Statement =>
                  Process_Accept (Element);
               when others =>
                  null;
            end case;

         when others =>
            null;
      end case;
   end Process;

   ---------------------
   -- Process_Derived --
   ---------------------

   procedure Process_Derived (Tipe : Asis.Type_Definition) is
      use Asis.Definitions;
      use Asis.Gela.Classes;

      function Root_Type
        (Info             : Type_Info;
         Stop_On_Rep_Item : Boolean)
        return Asis.Declaration
      is
         Decl   : Asis.Declaration := Get_Declaration (Info);
         Parent : Type_Info := Parent_Type (Info);
      begin
         if Stop_On_Rep_Item
           and then XASIS.Utils.Has_Representation_Item (Decl)
         then
            return Decl;
         elsif Is_Not_Type (Parent) then
            return Decl;
         else
            return Root_Type (Parent, Stop_On_Rep_Item);
         end if;
      end Root_Type;

      Decl   : Asis.Declaration := Asis.Elements.Enclosing_Element (Tipe);
      Parent : Asis.Subtype_Indication := Parent_Subtype_Indication (Tipe);
      Info   : Type_Info := Type_From_Indication (Parent, Decl);
      First  : Asis.Declaration := Get_Declaration (Info);
   begin
      Element_Utils.Set_Derived_Type
        (Tipe,
         Parent => First,
         Root   => Root_Type (Info, False),
         Struct => Root_Type (Info, True));
   end Process_Derived;

   ------------------
   -- Process_Exit --
   ------------------

   procedure Process_Exit (Element : Asis.Statement) is
      use Asis.Statements;
      use Asis.Expressions;

      Name : Asis.Expression := Exit_Loop_Name (Element);
      Stmt : Asis.Statement;
   begin
      if Assigned (Name) then
         Stmt := Corresponding_Name_Declaration (Name);
      else
         Stmt := Element;
         while Assigned (Stmt)
           and then Statement_Kind (Stmt) not in
           A_Loop_Statement .. A_For_Loop_Statement
         loop
            Stmt := Enclosing_Element (Stmt);
         end loop;
      end if;

      Element_Utils.Set_Corresponding_Statement
        (Stmt   => Element,
         Target => Stmt);
   end Process_Exit;

   ----------------------------
   -- Process_Procedure_Call --
   ----------------------------

   procedure Process_Procedure_Call (Call : Asis.Expression) is
      use Asis.Statements;
      Name : Asis.Expression := Called_Name (Call);
      Decl : Asis.Declaration := Selected_Name_Declaration (Name, False);
   begin
      Element_Utils.Set_Called_Function (Call, Decl, False);
   end Process_Procedure_Call;

   --------------------
   -- Process_Accept --
   --------------------

   procedure Process_Accept (Stmt : Asis.Expression) is
      use Asis.Statements;
      Name : Asis.Expression := Accept_Entry_Direct_Name (Stmt);
      Decl : Asis.Declaration := Selected_Name_Declaration (Name, False);
   begin
      Element_Utils.Set_Called_Function (Stmt, Decl, False);
   end Process_Accept;

   --------------------
   -- Process_Pragma --
   --------------------

   procedure Process_Pragma (Element : Asis.Pragma_Element) is

      Args   : constant Asis.Association_List :=
        Pragma_Argument_Associations (Element.all);

      function Get_Def_Names
        (Names : Asis.Element_List;
         Prev  : Asis.Element_List) return Asis.Element_List
      is
         use Asis.Elements;
         use Asis.Expressions;

         First : constant Asis.List_Index := Names'First;
         List  : Asis.Element_List :=
           Corresponding_Name_Definition_List (Names (First));
      begin
         for I in List'Range loop
            List (I) := Enclosing_Element (List (I));
         end loop;

         if Names'Length = 1 then
            return Prev & List;
         else
            return Get_Def_Names (Names (First + 1 .. Names'Last),
                                  Prev & List);
         end if;
      end Get_Def_Names;

      function Get_Names
        (Allow_Empty : Boolean := False;
         Multiply    : Boolean := False;
         Arg_Index   : Asis.ASIS_Natural := 0;
         Arg_Name    : Asis.Program_Text := "")
        return Asis.Element_List
      is
         use Asis.Gela.Errors;

         Index  : Asis.List_Index;
         Decl   : Asis.Declaration;
         Formal : Asis.Expression;
         Result : Asis.Element_List (Args'Range);
      begin
         if Args'Length = 0 then
            if not Allow_Empty then
               Report (Element, Error_Bad_Pragma_Argument);
            else
               Decl := Enclosing_Element (Element.all);
            end if;

            return (1 => Decl);
         elsif Arg_Index /= 0 then
            Index := Arg_Index;

            if Arg_Name /= "" then
               for I in Args'Range loop
                  Formal := Formal_Parameter (Args (I).all);

                  if Assigned (Formal)
                    and then Named_By (Formal, Arg_Name)
                  then
                     Index := I;

                     exit;
                  end if;
               end loop;
            end if;

            if Index not in Args'Range then
               Report (Element, Error_Bad_Pragma_Argument);
            elsif Multiply then
               return Get_Def_Names
                 ((1 => Actual_Parameter (Args (Index).all)),
                  Asis.Nil_Element_List);
            else
               Decl := XASIS.Utils.Selected_Name_Declaration
                 (Actual_Parameter (Args (Index).all), False);
            end if;

            return (1 => Decl);
         elsif Multiply then
            for I in Args'Range loop
               Result (I) := Actual_Parameter (Args (I).all);
            end loop;

            return Get_Def_Names (Result, Asis.Nil_Element_List);
         else
            for I in Args'Range loop
               Result (I) := XASIS.Utils.Selected_Name_Declaration
                 (Actual_Parameter (Args (I).all), False);
            end loop;

            return Result;
         end if;
      end Get_Names;

      procedure Add_Pragma (List : Asis.Element_List) is
      begin
         for I in List'Range loop
            Element_Utils.Add_Pragma (List (I), Element);
         end loop;
      end Add_Pragma;
   begin
      case Pragma_Kind (Element.all) is
         when An_Atomic_Pragma
           | An_Atomic_Components_Pragma
           | A_Volatile_Pragma
           | A_Volatile_Components_Pragma
           | A_Controlled_Pragma
           | An_Elaborate_Pragma
           | An_Elaborate_All_Pragma
           | An_Inspection_Point_Pragma
           | An_Interrupt_Handler_Pragma
           | A_Pack_Pragma
           | A_Preelaborable_Initialization_Pragma
           | An_Unchecked_Union_Pragma
           =>
            Add_Pragma (Get_Names);

         when An_All_Calls_Remote_Pragma
           | An_Elaborate_Body_Pragma
           | A_Preelaborate_Pragma
           | A_Pure_Pragma
           | A_Remote_Call_Interface_Pragma
           | A_Remote_Types_Pragma
           | A_Shared_Passive_Pragma
           =>
            Add_Pragma (Get_Names (Allow_Empty => True));

         when An_Asynchronous_Pragma
           | An_Inline_Pragma
           | A_No_Return_Pragma
           =>
            Add_Pragma (Get_Names (Multiply    => True));

         when An_Attach_Handler_Pragma =>
            Add_Pragma (Get_Names (Arg_Index   => 1));

         when A_Convention_Pragma
           | An_Export_Pragma
           | An_Import_Pragma
           =>
            Add_Pragma (Get_Names (Arg_Name  => "Entity",
                                   Arg_Index => 2,
                                   Multiply  => True));

         when A_Discard_Names_Pragma =>
            if Args'Length > 0 then
               Add_Pragma (Get_Names);
            else
               null;   --  Turn on pragma aggregation. TODO
            end if;

         when A_Suppress_Pragma =>
            if Args'Length > 1 then
               Add_Pragma (Get_Names (Arg_Index => 2));
            end if;

         when An_Assert_Pragma
           | An_Assertion_Policy_Pragma
           | A_Detect_Blocking_Pragma
           | An_Interrupt_Priority_Pragma
           | A_Priority_Pragma
           | A_Linker_Options_Pragma
           | A_List_Pragma
           | A_Page_Pragma
           | An_Optimize_Pragma
           | A_Locking_Policy_Pragma
           | A_Normalize_Scalars_Pragma
           | A_Partition_Elaboration_Policy_Pragma
           | A_Priority_Specific_Dispatching_Pragma
           | A_Profile_Pragma
           | A_Queuing_Policy_Pragma
           | A_Relative_Deadline_Pragma
           | A_Restrictions_Pragma
           | A_Reviewable_Pragma
           | A_Storage_Size_Pragma
           | A_Task_Dispatching_Policy_Pragma
           | An_Unsuppress_Pragma
           | An_Implementation_Defined_Pragma
           | An_Unknown_Pragma
           | Not_A_Pragma
           =>
            null;
      end case;
   end Process_Pragma;

   ----------------------
   -- Process_Renaming --
   ----------------------

   procedure Process_Renaming (Decl : Asis.Declaration) is
      use Asis.Elements;
      use Asis.Declarations;
      use Asis.Gela.Elements.Decl;

      Result : Asis.Expression := Renamed_Entity (Decl);
      Base   : Asis.Declaration :=
        Selected_Name_Declaration (Result, False);
   begin
      if Declaration_Kind (Base) in A_Renaming_Declaration then
         Result := Corresponding_Base_Entity (Base);
      end if;

      case Declaration_Kind (Decl) is
         when A_Procedure_Renaming_Declaration
           | A_Function_Renaming_Declaration
           =>
            Set_Corresponding_Base_Entity
              (Procedure_Renaming_Declaration_Node'Class (Decl.all), Result);

         when An_Object_Renaming_Declaration
           | An_Exception_Renaming_Declaration
           | A_Package_Renaming_Declaration
           | A_Generic_Package_Renaming_Declaration
           | A_Generic_Procedure_Renaming_Declaration
           | A_Generic_Function_Renaming_Declaration
           =>
            Set_Corresponding_Base_Entity
              (Base_Renaming_Declaration_Node'Class (Decl.all), Result);

         when others =>
            null;
      end case;
   end Process_Renaming;

   ------------------------
   -- Process_Rep_Clause --
   ------------------------

   procedure Process_Rep_Clause (Element : Asis.Clause) is
      use Asis.Gela.Elements;

      Name : Asis.Expression :=
        Representation_Clause_Name (Element.all);
      Decl : Asis.Declaration :=
        Selected_Name_Declaration (Name, True);
   begin
      if Assigned (Decl) then
         Add_To_Corresponding_Representation_Clauses
           (Declaration_Node'Class (Decl.all), Element);
      end if;
   end Process_Rep_Clause;

   ---------------------
   -- Process_Subtype --
   ---------------------

   procedure Process_Subtype (Element : Asis.Element) is
      use Asis.Definitions;
      use Asis.Declarations;
      use Asis.Expressions;
      use Asis.Gela.Elements.Decl;

      Ind  : Asis.Definition := Type_Declaration_View (Element);
      Mark : Asis.Expression := Asis.Definitions.Subtype_Mark (Ind);
      Decl : Asis.Declaration;
      Ptr  : constant Subtype_Declaration_Ptr :=
        Subtype_Declaration_Ptr (Element);
   begin
      Decl := Selected_Name_Declaration (Mark, True);

      if Assigned (Decl) then
         Set_Corresponding_Last_Subtype (Ptr.all, Decl);
         Set_Corresponding_First_Subtype (Ptr.all,
                                          Corresponding_First_Subtype (Decl));

         if Declaration_Kind (Element) = A_Subtype_Declaration then
            Ind := Type_Declaration_View (Element);

            if not Is_Nil (Subtype_Constraint (Ind)) then
               Set_Corresponding_Last_Constraint (Ptr.all, Decl);
            else
               Set_Corresponding_Last_Constraint (Ptr.all,
                 Corresponding_Last_Constraint (Decl));
            end if;
         else
            Set_Corresponding_Last_Constraint (Ptr.all,
              Corresponding_Last_Constraint (Decl));
         end if;
      end if;
   end Process_Subtype;

   -----------------------------
   -- Process_Subprogram_Decl --
   -----------------------------

   procedure Process_Subprogram_Decl
     (Decl  : Asis.Declaration;
      Point : in out Visibility.Point)
   is
      use Asis.Elements;
      use Asis.Declarations;
      use Asis.Gela.Classes;

      procedure Add_Operator (Decl : Asis.Declaration;
                              Info : Type_Info)
      is
         Def : Asis.Definition := Get_Type_Def (Info);
      begin
         Element_Utils.Add_Type_Operator (Def, Decl);
      end Add_Operator;

      Info : Type_Info;
      Name : Asis.Defining_Name  := Names (Decl) (1);
      Kind : Asis.Operator_Kinds := Operator_Kind (Name);
   begin
      Set_Is_Dispatching (Decl);

      if Kind = An_Equal_Operator then
         Info := Type_From_Indication (Result_Subtype (Decl), Decl);

         if Is_Equal (Get_Declaration (Info), XASIS.Types.Boolean) then
            Make_Not_Equal_Operator (Decl, Point);
         end if;
      end if;

      if Kind /= Not_An_Operator then
         declare
            Profile : Asis.Parameter_Specification_List :=
              Parameter_Profile (Decl);
            First   : Type_Info;
            Second  : Type_Info;
         begin
            Info := Type_From_Indication (Result_Subtype (Decl), Decl);

            if Is_Primitive (Name, Info) then
               Add_Operator (Decl, Info);
            end if;

            First := Type_Of_Declaration (Profile (1), Decl);

            if not Is_Equal (First, Info)
              and then Is_Primitive (Name, First)
            then
               Add_Operator (Decl, First);
            end if;

            if Profile'Length = 2 then
               Second := Type_Of_Declaration (Profile (2), Decl);

               if not Is_Equal (Second, Info)
                 and then not Is_Equal (Second, First)
                 and then Is_Primitive (Name, Second)
               then
                  Add_Operator (Decl, Second);
               end if;
            end if;
         end;
      end if;
   end Process_Subprogram_Decl;

   --------------------------------
   -- Process_Subtype_Indication --
   --------------------------------

   procedure Process_Subtype_Indication (Element : Asis.Element) is
      use Asis.Gela.Errors;
      Mark : Asis.Subtype_Mark :=
        Asis.Definitions.Subtype_Mark (Element);
   begin
      if Expression_Kind (Mark) = A_Function_Call then
         declare
            use Asis.Definitions;
            use Asis.Gela.Errors;
            use Asis.Gela.Elements.Defs;

            Subtipe : Asis.Subtype_Mark := Asis.Expressions.Prefix (Mark);
         begin
            if not Is_Nil (Subtype_Constraint (Element)) then
               Report (Element, Error_Syntax_Too_Many_Constraints);
            end if;
            Replace.Function_To_Constraint (Mark);
            Set_Subtype_Mark
              (Subtype_Indication_Ptr (Element).all, Subtipe);
            Element_Utils.Set_Enclosing_Element (Subtipe, Element);
            Set_Subtype_Constraint
              (Subtype_Indication_Ptr (Element).all, Mark);
            Element_Utils.Set_Enclosing_Element (Mark, Element);
         end;
      end if;
   end Process_Subtype_Indication;

   ------------------------
   -- Set_Is_Dispatching --
   ------------------------

   procedure Set_Is_Dispatching (Decl : Asis.Declaration) is
      use Asis.Elements;
      use Asis.Gela.Classes;
      use Asis.Declarations;

      Parent      : Asis.Element := Enclosing_Element (Decl);
      Is_Dispatch : Boolean := False;

      --------------------------
      -- Find_Tagged_Argument --
      --------------------------

      function Find_Tagged_Argument (Decl : Asis.Declaration) return Boolean is

         -----------
         -- Check --
         -----------

         function Check (Info : Type_Info) return Boolean is
         begin
            return Is_Tagged (Info)
              and then Is_Equal (Enclosing_Element (Get_Declaration (Info)),
                                 Parent);
         end Check;

         Info : Type_Info;
         List : constant Asis.Parameter_Specification_List :=
           Parameter_Profile (Decl);
      begin
         for I in List'Range loop
            Info := Type_Of_Declaration (List (I), Decl);

            if Check (Info) then
               return True;
            end if;
         end loop;

         case Declaration_Kind (Decl) is
            when A_Function_Declaration
              | A_Function_Renaming_Declaration =>

               Info := Type_From_Indication (Result_Subtype (Decl), Decl);

               return Check (Info);
            when others =>
               return False;
         end case;
      end Find_Tagged_Argument;

      -----------------------------
      -- Is_Override_Dispatching --
      -----------------------------

      function Is_Override_Dispatching
        (Decl : Asis.Declaration) return Boolean
      is
         Name     : Asis.Defining_Name_List := Names (Decl);
         Override : Asis.Defining_Name := Element_Utils.Override (Name (1));
      begin
         if not Assigned (Override) then
            return False;
         end if;

         return Is_Dispatching_Operation (Enclosing_Element (Override));
      end Is_Override_Dispatching;

      use Asis.Gela.Elements.Decl;
   begin
      case Declaration_Kind (Parent) is
         when A_Package_Declaration
           | A_Generic_Package_Declaration =>
            Is_Dispatch := Find_Tagged_Argument (Decl);

         when others =>
            Is_Dispatch := Is_Override_Dispatching (Decl);
      end case;

      case Declaration_Kind (Decl) is
         when A_Procedure_Declaration
           | A_Function_Declaration =>

            Set_Is_Dispatching_Operation
              (Procedure_Declaration_Node'Class (Decl.all),
               Is_Dispatch);

         when A_Procedure_Renaming_Declaration
           | A_Function_Renaming_Declaration =>

            Set_Is_Dispatching_Operation
              (Procedure_Renaming_Declaration_Node'Class (Decl.all),
               Is_Dispatch);

         when others =>
            null;
      end case;
   end Set_Is_Dispatching;

end Asis.Gela.Implicit.Decl;


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
