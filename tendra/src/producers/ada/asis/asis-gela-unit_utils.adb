with Asis.Gela.Units;  use Asis.Gela.Units;
with Asis.Gela.Lists;
with Asis.Gela.Library;
with Asis.Gela.Contexts;
with Asis.Gela.Normalizer;
with Asis.Gela.Element_Utils;

package body Asis.Gela.Unit_Utils is

   ---------------
   -- Add_Child --
   ---------------

   procedure Add_Child
     (The_Unit    : Compilation_Unit;
      The_Child   : Compilation_Unit)
   is
      Parent  : Any_Compilation_Unit_Node renames
        Any_Compilation_Unit_Node (The_Unit.all);

      Child : Any_Compilation_Unit_Node renames
        Any_Compilation_Unit_Node (The_Child.all);
   begin
      Add_To_Corresponding_Children (Parent, The_Child);
      Set_Corresponding_Parent_Declaration (Child, The_Unit);
   end Add_Child;

   ----------------
   -- Add_Pragma --
   ----------------

   procedure Add_Pragma
     (The_Unit   : Asis.Element;
      The_Pragma : Asis.Element;
      To_Clause  : Boolean := False)
   is
      use Lists.Primary_Clause_Lists;

      Unit : Any_Compilation_Unit_Node renames
        Any_Compilation_Unit_Node (The_Unit.all);
      Clauses : List := List (Context_Clause_Elements_List (Unit));
   begin
      Normalizer.Normalize_Pragma
        (The_Pragma, Asis.Compilation_Unit (The_Unit));

      if To_Clause then
         if Clauses = null then
            Clauses := new List_Node;
            Set_Context_Clause_Elements (Unit, Asis.Element (Clauses));
         end if;

         Add (Clauses.all, The_Pragma);
      else
         Add_To_Compilation_Pragmas (Unit, The_Pragma);
      end if;
   end Add_Pragma;

   -----------------
   -- Add_Subunit --
   -----------------

   procedure Add_Subunit
     (The_Unit    : Compilation_Unit;
      The_Subunit : Compilation_Unit)
   is
      Parent  : Any_Compilation_Unit_Node renames
        Any_Compilation_Unit_Node (The_Unit.all);

      Subunit : Any_Compilation_Unit_Node renames
        Any_Compilation_Unit_Node (The_Subunit.all);
   begin
      Add_To_Subunits (Parent, The_Subunit);
      Set_Corresponding_Subunit_Parent_Body (Subunit, The_Unit);
   end Add_Subunit;

   -----------------
   -- Compilation --
   -----------------

   function Compilation
     (The_Unit : Compilation_Unit) return Compilations.Compilation
   is
      Unit : Any_Compilation_Unit_Node renames
        Any_Compilation_Unit_Node (The_Unit.all);
   begin
      return Compilation (Unit);
   end Compilation;

   ------------------------------
   -- Is_Compilation_Unit_Body --
   ------------------------------

   function Is_Compilation_Unit_Body
     (The_Unit : Asis.Compilation_Unit)
      return Boolean
   is
      Kind : constant Unit_Kinds := Unit_Kind (The_Unit.all);
   begin
      return Kind in A_Procedure_Body .. A_Protected_Body_Subunit;
   end Is_Compilation_Unit_Body;

   -----------------------------
   -- Is_Configuration_Pragma --
   -----------------------------

   function Is_Configuration_Pragma
     (Kind : Pragma_Kinds)
      return Boolean
   is
      List : constant array (Positive range <>) of Pragma_Kinds :=
        (An_Assertion_Policy_Pragma,
         A_Detect_Blocking_Pragma,
         A_Discard_Names_Pragma,
         A_Locking_Policy_Pragma,
         A_Normalize_Scalars_Pragma,
         A_Partition_Elaboration_Policy_Pragma,
         A_Priority_Specific_Dispatching_Pragma,
         A_Profile_Pragma,
         A_Queuing_Policy_Pragma,
         A_Restrictions_Pragma,
         A_Reviewable_Pragma,
         A_Suppress_Pragma,
         A_Task_Dispatching_Policy_Pragma,
         An_Unsuppress_Pragma);
   begin
      for I in List'Range loop
         if List (I) = Kind then
            return True;
         end if;
      end loop;
      return False;
   end Is_Configuration_Pragma;

   ----------------------------
   -- Is_Program_Unit_Pragma --
   ----------------------------

   function Is_Program_Unit_Pragma
     (Kind : Pragma_Kinds)
      return Boolean
   is
      List : constant array (Positive range <>) of Pragma_Kinds :=
        (An_All_Calls_Remote_Pragma,
         A_Convention_Pragma,
         An_Elaborate_Body_Pragma,
         An_Export_Pragma,
         An_Import_Pragma,
         An_Inline_Pragma,
         A_Preelaborate_Pragma,
         A_Pure_Pragma,
         A_Remote_Call_Interface_Pragma,
         A_Remote_Types_Pragma,
         A_Shared_Passive_Pragma,
         An_Unknown_Pragma);
   begin
      for I in List'Range loop
         if List (I) = Kind then
            return True;
         end if;
      end loop;
      return False;
   end Is_Program_Unit_Pragma;

   ---------------------------
   -- Make_Nonexistent_Unit --
   ---------------------------

   function Make_Nonexistent_Unit
     (The_Context    : Context;
      Full_Unit_Name : Program_Text;
      Unit_Kind      : Unit_Kinds)
      return Compilation_Unit
   is
      Result : constant Any_Compilation_Unit_Ptr :=
        new Any_Compilation_Unit_Node;
   begin
      Set_Unit_Kind (Result.all, Unit_Kind);
      Set_Unit_Class (Result.all, Not_A_Class);
      Set_Unit_Origin (Result.all, Not_An_Origin);
      Set_Enclosing_Context (Result.all, The_Context);
      Set_Corresponding_Declaration (Result.all, Compilation_Unit (Result));
      Set_Corresponding_Body (Result.all, Compilation_Unit (Result));
      Set_Unit_Full_Name (Result.all, Full_Unit_Name);

      return  Compilation_Unit (Result);
   end Make_Nonexistent_Unit;

   ----------------------------
   -- Make_Limited_View_Unit --
   ----------------------------

   function Make_Limited_View_Unit
     (The_Context : Context;
      Declaration : Compilation_Unit) return Compilation_Unit
   is
      Name   : constant Wide_String := Unit_Full_Name (Declaration.all);
      Result : constant Any_Compilation_Unit_Ptr :=
        new Any_Compilation_Unit_Node;
   begin
      Set_Unit_Kind (Result.all, An_Unknown_Unit);
      Set_Unit_Class (Result.all, Unit_Class (Declaration.all));
      Set_Unit_Origin (Result.all, An_Implementation_Unit);
      Set_Enclosing_Context (Result.all, The_Context);
      Set_Corresponding_Declaration (Result.all, Declaration);
      Set_Unit_Full_Name (Result.all, Name);
      Set_Unique_Name (Compilation_Unit (Result));

      return  Compilation_Unit (Result);
   end Make_Limited_View_Unit;

   ---------------------------
   -- Remove_Context_Clause --
   ---------------------------

   procedure Remove_Context_Clause
     (The_Unit : Compilation_Unit;
      Element  : Asis.Element)
   is
      use Asis.Gela.Lists;
      Unit  : Any_Compilation_Unit_Node renames
        Any_Compilation_Unit_Node (The_Unit.all);
      Items : constant Asis.Element := Context_Clause_Elements_List (Unit);
      List  : Primary_Clause_Lists.List :=
        Primary_Clause_Lists.List (Items);
   begin
      Primary_Clause_Lists.Remove (List.all, Element);
   end Remove_Context_Clause;

   --------------
   -- Set_Body --
   --------------

   procedure Set_Body
     (The_Unit    : Compilation_Unit;
      The_Body    : Compilation_Unit)
   is
      Decl : Any_Compilation_Unit_Node renames
        Any_Compilation_Unit_Node (The_Unit.all);

      Impl : Any_Compilation_Unit_Node renames
        Any_Compilation_Unit_Node (The_Body.all);
   begin
      Set_Corresponding_Body (Decl, The_Body);
      Set_Corresponding_Declaration (Impl, The_Unit);
   end Set_Body;

   -----------------------------
   -- Set_Can_Be_Main_Program --
   -----------------------------

   procedure Set_Can_Be_Main_Program
     (Unit : Compilation_Unit)
   is
      The_Unit : Any_Compilation_Unit_Node renames
        Any_Compilation_Unit_Node (Unit.all);
   begin
      if Unit_Kind (Unit.all) = A_Procedure_Body and then
        Parameter_Profile (Unit_Declaration (Unit.all).all)'Length = 0
      then
         Set_Can_Be_Main_Program (The_Unit, True);
      else
         Set_Can_Be_Main_Program (The_Unit, False);
      end if;
   end Set_Can_Be_Main_Program;

   ---------------------
   -- Set_Compilation --
   ---------------------

   procedure Set_Compilation
     (The_Unit    : Compilation_Unit;
      Compilation : Compilations.Compilation)
   is
      Unit : Any_Compilation_Unit_Node renames
        Any_Compilation_Unit_Node (The_Unit.all);
   begin
      Set_Compilation (Unit, Compilation);
   end Set_Compilation;

   ------------------------------------------
   -- Set_Compilation_Command_Line_Options --
   ------------------------------------------

   procedure Set_Compilation_Command_Line_Options
     (Unit : Compilation_Unit)
   is
   begin
      null;
   end Set_Compilation_Command_Line_Options;

   --------------------------
   -- Set_Is_Body_Required --
   --------------------------

   procedure Set_Is_Body_Required
     (Unit : Compilation_Unit)
   is
      The_Unit : Any_Compilation_Unit_Node renames
        Any_Compilation_Unit_Node (Unit.all);
   begin
      if Unit_Kind (Unit.all) = A_Package or
        Unit_Kind (Unit.all) = A_Generic_Package
      then
         Set_Is_Body_Required (The_Unit, True);
      else
         Set_Is_Body_Required (The_Unit, False);
      end if;
   end Set_Is_Body_Required;

   ---------------------
   -- Set_Object_Form --
   ---------------------

   procedure Set_Object_Form
     (Unit : Compilation_Unit)
   is
   begin
      null;
   end Set_Object_Form;

   ---------------------
   -- Set_Object_Name --
   ---------------------

   procedure Set_Object_Name
     (Unit : Compilation_Unit)
   is
      The_Unit : Any_Compilation_Unit_Node renames
        Any_Compilation_Unit_Node (Unit.all);
   begin
      Set_Object_Name (The_Unit, Text_Name (Unit.all) & ".o");
   end Set_Object_Name;

   -----------------------
   -- Set_Separate_Name --
   -----------------------

   procedure Set_Separate_Name
     (Unit : Compilation_Unit)
   is
      The_Unit : Any_Compilation_Unit_Node renames
        Any_Compilation_Unit_Node (Unit.all);
      Name     : constant Asis.Program_Text :=
        Element_Utils.Compound_Name_Image (Separate_Name (The_Unit));
   begin
      Set_Separate_Name_Image (The_Unit, Name);
   end Set_Separate_Name;

   -------------------
   -- Set_Text_Form --
   -------------------

   procedure Set_Text_Form
     (Unit : Compilation_Unit)
   is
   begin
      null;
   end Set_Text_Form;

   -------------------
   -- Set_Text_Name --
   -------------------

   procedure Set_Text_Name
     (Unit : Compilation_Unit)
   is
      The_Unit : Any_Compilation_Unit_Node renames
        Any_Compilation_Unit_Node (Unit.all);

      Ctx : constant Asis.Context := Enclosing_Context (Unit.all);
   begin
      Set_Text_Name (The_Unit, Current_File (Ctx.all));
   end Set_Text_Name;

   ---------------------
   -- Set_Unique_Name --
   ---------------------

   procedure Set_Unique_Name
     (Unit : Compilation_Unit)
   is
      The_Unit : Any_Compilation_Unit_Node renames
        Any_Compilation_Unit_Node (Unit.all);

      Name : constant Wide_String :=
        Unit_Full_Name (Unit.all) & "/" &
        Unit_Kinds'Wide_Image (Unit_Kind (Unit.all));
   begin
      Set_Unique_Name (The_Unit, Name);
   end Set_Unique_Name;

   --------------------
   -- Set_Unit_Class --
   --------------------

   procedure Set_Unit_Class
     (Unit       : in Compilation_Unit;
      Is_Private : in Boolean)
   is
      The_Unit : Any_Compilation_Unit_Node renames
        Any_Compilation_Unit_Node (Unit.all);

      Is_Subunit : constant Boolean := Unit_Kind (Unit.all) in A_Subunit;
      Is_Body    : constant Boolean :=
        Unit_Kind  (Unit.all) in A_Library_Unit_Body;
      Is_Subprogram : constant Boolean :=
        Unit_Kind (Unit.all) in A_Subprogram_Body;
      Full_Name     : constant Wide_String := Unit_Full_Name (Unit.all);
      Has_Decl      : constant Boolean := Library.Has_Declaration (Full_Name);
      Result        : Asis.Unit_Classes;
   begin
      if Is_Subunit then
         Result := A_Separate_Body;
      elsif Is_Private then
         Result := A_Private_Declaration;
      else
         if Is_Body then
            if Is_Subprogram and not Has_Decl then
               Result := A_Public_Declaration_And_Body;
            else
               Result := A_Public_Body;
            end if;
         else
            Result := A_Public_Declaration;
         end if;
      end if;
      Set_Unit_Class (The_Unit, Result);
   end Set_Unit_Class;

   ------------------------
   -- Set_Unit_Full_Name --
   ------------------------

   procedure Set_Unit_Full_Name
     (Unit : Compilation_Unit)
   is
      The_Unit : Any_Compilation_Unit_Node renames
        Any_Compilation_Unit_Node (Unit.all);

      Decl       : constant Asis.Element := Unit_Declaration (Unit.all);
      Name       : constant Asis.Element := Names (Decl.all) (1);
      Image      : constant Wide_String :=
        Element_Utils.Compound_Name_Image (Name);
      Is_Subunit : constant Boolean := Unit_Kind (Unit.all) in A_Subunit;
   begin
      if Is_Subunit then
         Set_Unit_Full_Name (The_Unit,
                             Separate_Name_Image (The_Unit) & "." & Image);
      else
         Set_Unit_Full_Name (The_Unit, Image);
      end if;
   end Set_Unit_Full_Name;

   -------------------
   -- Set_Unit_Kind --
   -------------------

   procedure Set_Unit_Kind
     (Unit : Compilation_Unit)
   is
      The_Unit : Any_Compilation_Unit_Node renames
        Any_Compilation_Unit_Node (Unit.all);

      Is_Subunit : constant Boolean :=
        Assigned (Separate_Name (The_Unit));

      Decl_Kind  : constant Declaration_Kinds :=
        Declaration_Kind (Unit_Declaration (The_Unit).all);

      Ordinary_Kinds : constant array (Declaration_Kinds) of Unit_Kinds :=
        (A_Function_Body_Declaration              => A_Function_Body,
         A_Function_Declaration                   => A_Function,
         A_Function_Instantiation                 => A_Function_Instance,
         A_Generic_Function_Declaration           => A_Generic_Function,
         A_Generic_Package_Declaration            => A_Generic_Package,
         A_Generic_Procedure_Declaration          => A_Generic_Procedure,
         A_Package_Body_Declaration               => A_Package_Body,
         A_Package_Declaration                    => A_Package,
         A_Package_Instantiation                  => A_Package_Instance,
         A_Procedure_Body_Declaration             => A_Procedure_Body,
         A_Procedure_Declaration                  => A_Procedure,
         A_Procedure_Instantiation                => A_Procedure_Instance,
         A_Package_Renaming_Declaration           => A_Package_Renaming,
         A_Procedure_Renaming_Declaration         => A_Procedure_Renaming,
         A_Function_Renaming_Declaration          => A_Function_Renaming,
         A_Generic_Package_Renaming_Declaration   =>
           A_Generic_Package_Renaming,
         A_Generic_Procedure_Renaming_Declaration =>
           A_Generic_Procedure_Renaming,
         A_Generic_Function_Renaming_Declaration  =>
           A_Generic_Function_Renaming,
         others                                   => Not_A_Unit);

      Subunit_Kinds : constant array (Declaration_Kinds) of Unit_Kinds :=
        (A_Function_Body_Declaration  => A_Function_Body_Subunit,
         A_Package_Body_Declaration   => A_Package_Body_Subunit,
         A_Procedure_Body_Declaration => A_Procedure_Body_Subunit,
         A_Task_Body_Declaration      => A_Task_Body_Subunit,
         A_Protected_Body_Declaration => A_Protected_Body_Subunit,
         others                       => Not_A_Unit);

   begin
      if Is_Subunit then
         Set_Unit_Kind (The_Unit, Subunit_Kinds (Decl_Kind));
      else
         Set_Unit_Kind (The_Unit, Ordinary_Kinds (Decl_Kind));
      end if;
   end Set_Unit_Kind;

   ---------------------
   -- Set_Unit_Origin --
   ---------------------

   procedure Set_Unit_Origin
     (Unit : Compilation_Unit)
   is
      The_Unit : Any_Compilation_Unit_Node renames
        Any_Compilation_Unit_Node (Unit.all);
   begin
      if Library.Is_Predefined_Unit (Text_Name (The_Unit)) then
         Set_Unit_Origin (The_Unit, A_Predefined_Unit);
      else
         Set_Unit_Origin (The_Unit, An_Application_Unit);
      end if;
   end Set_Unit_Origin;

   --------------------------
   -- Set_Unit_Declaration --
   --------------------------

   procedure Set_Unit_Declaration
     (Unit        : Compilation_Unit;
      Declaration : Asis.Element)
   is
      The_Unit : Any_Compilation_Unit_Node renames
        Any_Compilation_Unit_Node (Unit.all);
   begin
      Set_Unit_Declaration (The_Unit, Declaration);
   end Set_Unit_Declaration;

end Asis.Gela.Unit_Utils;



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
