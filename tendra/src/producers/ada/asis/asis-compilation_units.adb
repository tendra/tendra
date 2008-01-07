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

package body Asis.Compilation_Units is

   -------------------------------
   -- Attribute_Value_Delimiter --
   -------------------------------

   function Attribute_Value_Delimiter return Wide_String is
   begin
      return ",";
   end Attribute_Value_Delimiter;

   ----------------------
   -- Attribute_Values --
   ----------------------

   function Attribute_Values
     (Compilation_Unit : in Asis.Compilation_Unit;
      Attribute        : in Wide_String)
      return Wide_String
   is
   begin
      if Assigned (Compilation_Unit) then
         return "";
--         return Attribute_Values (Compilation_Unit.all, Attribute);
      else
         return "";
      end if;
   end Attribute_Values;

   -------------------------
   -- Can_Be_Main_Program --
   -------------------------

   function Can_Be_Main_Program
     (Compilation_Unit : in Asis.Compilation_Unit)
      return Boolean
   is
   begin
      if Assigned (Compilation_Unit) then
         return Can_Be_Main_Program (Compilation_Unit.all);
      else
         return False;
      end if;
   end Can_Be_Main_Program;

   --------------------------------------
   -- Compilation_Command_Line_Options --
   --------------------------------------

   function Compilation_Command_Line_Options
     (Compilation_Unit : in Asis.Compilation_Unit)
      return Wide_String
   is
   begin
      if Assigned (Compilation_Unit) then
         return Compilation_Command_Line_Options (Compilation_Unit.all);
      else
         return "";
      end if;
   end Compilation_Command_Line_Options;

   -----------------------------
   -- Compilation_Unit_Bodies --
   -----------------------------

   function Compilation_Unit_Bodies
     (The_Context : in Asis.Context)
      return Asis.Compilation_Unit_List is
   begin
      if Assigned (The_Context) then
         return Compilation_Unit_Bodies (The_Context.all);
      else
         return Nil_Compilation_Unit_List;
      end if;
   end Compilation_Unit_Bodies;

   ---------------------------
   -- Compilation_Unit_Body --
   ---------------------------

   function Compilation_Unit_Body
     (Name        : in Wide_String;
      The_Context : in Asis.Context)
      return Asis.Compilation_Unit is
   begin
      if Assigned (The_Context) then
         return Compilation_Unit_Body (Name, The_Context.all);
      else
         return Nil_Compilation_Unit;
      end if;
   end Compilation_Unit_Body;

   -----------------------
   -- Compilation_Units --
   -----------------------

   function Compilation_Units
     (The_Context : in Asis.Context)
      return Asis.Compilation_Unit_List
   is
   begin
      if Assigned (The_Context) then
         return Context_Compilation_Units (The_Context.all);
      else
         return Nil_Compilation_Unit_List;
      end if;
   end Compilation_Units;

   ------------------------
   -- Corresponding_Body --
   ------------------------

   function Corresponding_Body
     (Library_Item : in Asis.Compilation_Unit)
      return Asis.Compilation_Unit
   is
   begin
      Check_Nil_Unit (Library_Item, "Corresponding_Body");
      return Corresponding_Body (Library_Item.all);
   end Corresponding_Body;

   ------------------------
   -- Corresponding_Body --
   ------------------------

   function Corresponding_Body
     (Library_Item : in Asis.Compilation_Unit;
      The_Context  : in Asis.Context)
      return Asis.Compilation_Unit
   is
   begin
      if Assigned (The_Context) then
         return Corresponding_Body (Library_Item, The_Context.all);
      else
         return Nil_Compilation_Unit;
      end if;
   end Corresponding_Body;

   ----------------------------
   -- Corresponding_Children --
   ----------------------------

   function Corresponding_Children
     (Library_Unit : in Asis.Compilation_Unit)
      return Asis.Compilation_Unit_List is
   begin
      Check_Nil_Unit (Library_Unit, "Corresponding_Children");
      return Corresponding_Children (Library_Unit.all);
   end Corresponding_Children;

   ----------------------------
   -- Corresponding_Children --
   ----------------------------

   function Corresponding_Children
     (Library_Unit : in Asis.Compilation_Unit;
      The_Context  : in Asis.Context)
      return Asis.Compilation_Unit_List is
   begin
      if Assigned (The_Context) then
         return Corresponding_Children (Library_Unit, The_Context.all);
      else
         return Nil_Compilation_Unit_List;
      end if;
   end Corresponding_Children;

   -------------------------------
   -- Corresponding_Declaration --
   -------------------------------

   function Corresponding_Declaration
     (Library_Item : in Asis.Compilation_Unit)
      return Asis.Compilation_Unit is
   begin
      Check_Nil_Unit (Library_Item, "Corresponding_Declaration");
      return Corresponding_Declaration (Library_Item.all);
   end Corresponding_Declaration;

   -------------------------------
   -- Corresponding_Declaration --
   -------------------------------

   function Corresponding_Declaration
     (Library_Item : in Asis.Compilation_Unit;
      The_Context  : in Asis.Context)
      return Asis.Compilation_Unit is
   begin
      if Assigned (The_Context) then
         return Corresponding_Declaration (Library_Item, The_Context.all);
      else
         return Nil_Compilation_Unit;
      end if;
   end Corresponding_Declaration;

   --------------------------------------
   -- Corresponding_Parent_Declaration --
   --------------------------------------

   function Corresponding_Parent_Declaration
     (Library_Unit : in Asis.Compilation_Unit)
      return Asis.Compilation_Unit is
   begin
      Check_Nil_Unit (Library_Unit, "Corresponding_Parent_Declaration");
      return Corresponding_Parent_Declaration (Library_Unit.all);
   end Corresponding_Parent_Declaration;

   --------------------------------------
   -- Corresponding_Parent_Declaration --
   --------------------------------------

   function Corresponding_Parent_Declaration
     (Library_Unit : in Asis.Compilation_Unit;
      The_Context  : in Asis.Context)
      return Asis.Compilation_Unit is
   begin
      if Assigned (The_Context) then
         return Corresponding_Parent_Declaration
                  (Library_Unit, The_Context.all);
      else
         return Nil_Compilation_Unit;
      end if;
   end Corresponding_Parent_Declaration;

   ---------------------------------------
   -- Corresponding_Subunit_Parent_Body --
   ---------------------------------------

   function Corresponding_Subunit_Parent_Body
     (Subunit : in Asis.Compilation_Unit)
      return Asis.Compilation_Unit
   is
   begin
      Check_Nil_Unit (Subunit, "Corresponding_Subunit_Parent_Body");
      return Corresponding_Subunit_Parent_Body (Subunit.all);
   end Corresponding_Subunit_Parent_Body;

   ---------------------------------------
   -- Corresponding_Subunit_Parent_Body --
   ---------------------------------------

   function Corresponding_Subunit_Parent_Body
     (Subunit     : in Asis.Compilation_Unit;
      The_Context : in Asis.Context)
      return Asis.Compilation_Unit
   is
   begin
      if Assigned (The_Context) then
         return Corresponding_Subunit_Parent_Body
                  (Subunit, The_Context.all);
      else
         return Nil_Compilation_Unit;
      end if;
   end Corresponding_Subunit_Parent_Body;

   -----------------
   -- Debug_Image --
   -----------------

   function Debug_Image
     (Compilation_Unit : in Asis.Compilation_Unit)
      return Wide_String
   is
   begin
      if Assigned (Compilation_Unit) then
         return "Debug_Image";
      else
         return "[null]";
      end if;
   end Debug_Image;

   -------------------------
   -- Enclosing_Container --
   -------------------------

   function Enclosing_Container
     (Compilation_Unit : in Asis.Compilation_Unit)
     return Asis.Ada_Environments.Containers.Container
   is
      use Asis.Ada_Environments.Containers;
      List : constant Container_List :=
        Defining_Containers (Enclosing_Context (Compilation_Unit));
   begin
      return List (List'First);
   end Enclosing_Container;

   -----------------------
   -- Enclosing_Context --
   -----------------------

   function Enclosing_Context
     (Compilation_Unit : in Asis.Compilation_Unit)
      return Asis.Context is
   begin
      Check_Nil_Unit (Compilation_Unit, "Enclosing_Context");
      return Enclosing_Context (Compilation_Unit.all);
   end Enclosing_Context;

   ------------
   -- Exists --
   ------------

   function Exists (Compilation_Unit : in Asis.Compilation_Unit) return Boolean
   is
      Kind : constant Asis.Unit_Kinds := Unit_Kind (Compilation_Unit);
   begin
      if Kind = Not_A_Unit or
        Kind = A_Nonexistent_Declaration or
        Kind = A_Nonexistent_Body then

         return False;
      else
         return True;
      end if;
   end Exists;

   -------------------
   -- Has_Attribute --
   -------------------

   function Has_Attribute
     (Compilation_Unit : in Asis.Compilation_Unit;
      Attribute        : in Wide_String)
      return Boolean
   is
   begin
      if Assigned (Compilation_Unit) then
         return False;
--         return Has_Attribute (Compilation_Unit.all, Attribute);
      else
         return False;
      end if;
   end Has_Attribute;

   ----------------------
   -- Is_Body_Required --
   ----------------------

   function Is_Body_Required
     (Compilation_Unit : in Asis.Compilation_Unit)
      return Boolean
   is
   begin
      if Assigned (Compilation_Unit) then
         return Is_Body_Required (Compilation_Unit.all);
      else
         return False;
      end if;
   end Is_Body_Required;

   --------------
   -- Is_Equal --
   --------------

   function Is_Equal
     (Left  : in Asis.Compilation_Unit;
      Right : in Asis.Compilation_Unit)
      return Boolean
   is
   begin
      return Unique_Name (Left) = Unique_Name (Right);
   end Is_Equal;

   ------------------
   -- Is_Identical --
   ------------------

   function Is_Identical
     (Left  : in Asis.Compilation_Unit;
      Right : in Asis.Compilation_Unit)
      return Boolean
   is
      type Comp_Unit_Node_Ptr is access all Compilation_Unit_Node'Class;
   begin
      return Comp_Unit_Node_Ptr (Left) = Comp_Unit_Node_Ptr (Right);
   end Is_Identical;

   ------------
   -- Is_Nil --
   ------------

   function Is_Nil (Right : in Asis.Compilation_Unit)
      return Boolean is
   begin
      return not Assigned (Right);
   end Is_Nil;

   ------------
   -- Is_Nil --
   ------------

   function Is_Nil (Right : in Asis.Compilation_Unit_List)
      return Boolean is
   begin
      return Right'Length = 0;
   end Is_Nil;

   ------------------------------
   -- Library_Unit_Declaration --
   ------------------------------

   function Library_Unit_Declaration
     (Name        : in Wide_String;
      The_Context : in Asis.Context)
      return Asis.Compilation_Unit is
   begin
      if Assigned (The_Context) then
         return Library_Unit_Declaration (Name, The_Context.all);
      else
         return Nil_Compilation_Unit;
      end if;
   end Library_Unit_Declaration;

   -------------------------------
   -- Library_Unit_Declarations --
   -------------------------------

   function Library_Unit_Declarations
     (The_Context : in Asis.Context)
      return Asis.Compilation_Unit_List is
   begin
      if Assigned (The_Context) then
         return Library_Unit_Declarations (The_Context.all);
      else
         return Nil_Compilation_Unit_List;
      end if;
   end Library_Unit_Declarations;

   -----------------
   -- Object_Form --
   -----------------

   function Object_Form
     (Compilation_Unit : in Asis.Compilation_Unit)
      return Wide_String
   is
   begin
      if Assigned (Compilation_Unit) then
         return Object_Form (Compilation_Unit.all);
      else
         return "";
      end if;
   end Object_Form;

   -----------------
   -- Object_Name --
   -----------------

   function Object_Name
     (Compilation_Unit : in Asis.Compilation_Unit)
      return Wide_String
   is
   begin
      if Assigned (Compilation_Unit) then
         return Object_Name (Compilation_Unit.all);
      else
         return "";
      end if;
   end Object_Name;

   --------------
   -- Subunits --
   --------------

   function Subunits
     (Parent_Body : in Asis.Compilation_Unit)
      return Asis.Compilation_Unit_List
   is
   begin
      Check_Nil_Unit (Parent_Body, "Subunits");
      return Subunits (Parent_Body.all);
   end Subunits;

   --------------
   -- Subunits --
   --------------

   function Subunits
     (Parent_Body : in Asis.Compilation_Unit;
      The_Context : in Asis.Context)
      return Asis.Compilation_Unit_List is
   begin
      if Assigned (The_Context) then
         return Subunits (Parent_Body, The_Context.all);
      else
         return Nil_Compilation_Unit_List;
      end if;
   end Subunits;

   ---------------
   -- Text_Form --
   ---------------

   function Text_Form
     (Compilation_Unit : in Asis.Compilation_Unit)
      return Wide_String
   is
   begin
      if Assigned (Compilation_Unit) then
         return Text_Form (Compilation_Unit.all);
      else
         return "";
      end if;
   end Text_Form;

   ---------------
   -- Text_Name --
   ---------------

   function Text_Name (Compilation_Unit : in Asis.Compilation_Unit)
      return Wide_String is
   begin
      if Assigned (Compilation_Unit) then
         return Text_Name (Compilation_Unit.all);
      else
         return "";
      end if;
   end Text_Name;

   -----------------
   -- Unique_Name --
   -----------------

   function Unique_Name
     (Compilation_Unit : in Asis.Compilation_Unit)
      return Wide_String
   is
   begin
      if Assigned (Compilation_Unit) then
         return Unique_Name (Compilation_Unit.all);
      else
         return "";
      end if;
   end Unique_Name;

   ----------------
   -- Unit_Class --
   ----------------

   function Unit_Class
     (Compilation_Unit : in Asis.Compilation_Unit)
      return Asis.Unit_Classes is
   begin
      if Assigned (Compilation_Unit) then
         return Unit_Class (Compilation_Unit.all);
      else
         return Not_A_Class;
      end if;
   end Unit_Class;

   --------------------
   -- Unit_Full_Name --
   --------------------

   function Unit_Full_Name
     (Compilation_Unit : in Asis.Compilation_Unit)
      return Wide_String
   is
   begin
      if Assigned (Compilation_Unit) then
         return Unit_Full_Name (Compilation_Unit.all);
      else
         return "";
      end if;
   end Unit_Full_Name;

   ---------------
   -- Unit_Kind --
   ---------------

   function Unit_Kind
     (Compilation_Unit : in Asis.Compilation_Unit)
      return Asis.Unit_Kinds is
   begin
      if Assigned (Compilation_Unit) then
         return Unit_Kind (Compilation_Unit.all);
      else
         return Not_A_Unit;
      end if;
   end Unit_Kind;

   -----------------
   -- Unit_Origin --
   -----------------

   function Unit_Origin
     (Compilation_Unit : in Asis.Compilation_Unit)
      return Asis.Unit_Origins is
   begin
      if Assigned (Compilation_Unit) then
         return Unit_Origin (Compilation_Unit.all);
      else
         return Not_An_Origin;
      end if;
   end Unit_Origin;

end Asis.Compilation_Units;



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
